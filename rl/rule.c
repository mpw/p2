/* $Id: rule.c,v 45.0 1997/09/19 05:46:11 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h> /* strcat */
#include "rl.h"

/******************** rule.c *************************
   this file has most, if not all, of the functions associated
   with the storage and processing of rules.  The primary data
   structure is a list of rule declarations, headed by the
   variable rule_list.  RULE is the element type stored on this 
   list.

   the interesting fields of RULE are:

   name   -  name of the rule
   next   -  next rule on the rule-list
   first  -  list of CEs associated with this rule
   no_elements - number of condition elements (positive and negative)
   ruleno - internally assigned numeric identifier of rules
   action  -  list of actions associated with this rule

   A list of condition elements is associated with each rule (whose
   list head is RULE.first).  There is one CE element (of type ELEMENT)
   per CE.  Among the interesting fields of ELEMENT are:

   name  - name of container referenced in CE
   cont  - a pointer to the CONT declaration of this container
   neg   - is this CE negated?
   first - pointer to list of clauses
   negtest - a string containing the name of the filter for 
           negated CEs (to be added into compcurs declarations).
           (This is the test to perform for negated condition elements)

   Every clause of a CE is represented on a list of CLAUSE instances.
   Among the interesting fields of CLAUSE are:

   name  - name of field referenced
   relop - string that contains the comparison relation.  In the 
           case of implied equality (i.e., ^field value), relop is
           the null string.
   v     - type of value to compare: CONStant, VARiable, DISJunction
   cons  - string containing constant or variable name; not used
           for disjunctions
   first - list of constants for disjunctions; not used for CONS or 
           VAR clauses.

   A disjunction of constants is a list of constants of type DISJ.
   Nothing special here.

   Every rule has a list of actions, represented by a list of
   elements of type ACTION.  Among the interesting fields of
   ACTION are:

   name  - type of operation to be performed (UPD, REM, ...)
   what  - the first argument of the operation, usually reserved
           to be the name (or some identifier) of a container
   first - list of additional arguments (of type ARG).

   Elements of type ARG have the following structure:

   name  - name of additional argument (usually a field name)
   node  - a parse tree that represents some expression (e.g.,
           constants, compute, etc.).

   Parse trees are NODEs of trees, which have no particularly
   novel shape.  A NODE consists of:

   name  - a constant or variable name
   nodetype - type of node: CONS_NODE, VAR_NODE, UFUNC, etc.
   down[] - pointers to siblings.

***************************************************************/

/* global variables */

PRED_PTR   include_list = 0;  /* list of external routine include files */
PAIR_PTR   bind_list;
RULE_PTR   rule_list = 0;
int        no_rules  = 1;


/**************** data structure operations **************************

   the following return handles to their respective elements:

   new_rule(n) - registers new rule with name n

   new_element(r,n,b) - registers new CE element over container (or
                   shadow if b==TRUE) with name n;  NOTE: all positive
                   CEs appear on r's rule list BEFORE any negative CEs
   new_clause(e,f,r,v,k) - adds new clause to element e; clause is 
                   over field f with relop r, valuetype v, and valuestring k
   new_disj(c,k) - add constant k to the disjuction list of clause c 

   new_action(r,a,w) - registers new action a with first argument w
                    to rule r
   new_arg(a,n,g) - registers new argument to action a with name n and
                    node-parsetree g
   new_node(v,t,p0,p1,p2) - creates new node with value v of type t 
                   and children p0..p2

*************************************************************/

RULE_PTR new_rule ( char *name )
{
RULE_PTR r = (RULE_PTR) malloc(sizeof(RULE));
RULE_PTR rr;

   strcpy(r->name, name);
   r->first = 0;
   r->no_elements = 0;
   r->ruleno = no_rules++;
   if (!rule_list)
      rule_list = r;
   else {
      for (rr = rule_list; rr->next; rr = rr->next);
      rr->next = r;
   }
   r->next =   0;
   r->action = 0;
   return r;
}

/* all positive CEs appear on an element list before
   any negative CEs; order is chronological appearance */

ELEMENT_PTR
new_element (RULE_PTR r, char *name, BOOLEAN neg)
{
  ELEMENT_PTR e = (ELEMENT_PTR) malloc(sizeof(ELEMENT));
  ELEMENT_PTR ee;

  strcpy(e->name, name);
  e->cont = find_container(e->name);
  e->neg = neg;
  e->first = 0;
#if 1
  e->next = 0;
#endif

  if (neg) {
    if (!r->first)
      r->first = e;
    else
    {
      for (ee = r->first; ee->next; ee = ee->next);
      ee->next = e;
    }
  }
  else
  {
    if (!r->first)
      r->first = e;
    else
    {
      for (ee = r->first; ee->next && !ee->next->neg; ee = ee->next);
      e->next = ee->next;
      ee->next = e;
    }
  }

  strcpy(e->negtest,"");  /* set by print_negated_tests */
  r->no_elements++;
  return e;
}

CLAUSE_PTR
new_clause (ELEMENT_PTR e, char *fld, char *relop, VALTYPE v, char *cons )
{
  CLAUSE_PTR c = (CLAUSE_PTR) malloc(sizeof(CLAUSE));
  CLAUSE_PTR cc;

  strcpy(c->name, fld);
  strcpy(c->relop, relop);
  c->v = v;
  strcpy(c->cons, cons);
  if (!e->first) 
    e->first = c;
  else
  {
    for (cc = e->first; cc->next; cc = cc->next);
    cc->next = c;
  }
  c->next = 0;
  return c;
}

DISJ_PTR new_disj( CLAUSE_PTR c, char *cons )
{
DISJ_PTR d = (DISJ_PTR) malloc(sizeof(DISJ));

   strcpy(d->name, cons);
   d->next = c->first;
   c->first = d;
   return d;
}

ACTION_PTR new_action ( RULE_PTR r, ACTTYPE action, char *what )
{
ACTION_PTR a = (ACTION_PTR) malloc(sizeof(ACTION));
ACTION_PTR aa;

   a->name = action;
   strcpy(a->what,what);
   a->first = 0;
   if (!r->action)
      r->action = a;
   else {
      for (aa = r->action; aa->next; aa = aa->next );
      aa->next = a;
   }
   a->next = 0;
   return a;
}

ARG_PTR new_arg ( ACTION_PTR a, char *name, NODE_PTR arg )
{
ARG_PTR ar = (ARG_PTR) malloc(sizeof(ARG));
ARG_PTR aa;

   strcpy(ar->name, name);
   ar->node = arg;
   if (!a->first)
      a->first = ar;
   else {
      for (aa = a->first; aa->next; aa = aa->next );
      aa->next = ar;
   }
   ar->next = 0;
   return ar;
}

NODE_PTR new_node ( char *value, NODETYPE t, 
           NODE_PTR p0, NODE_PTR p1, NODE_PTR p2 ) 
{
NODE_PTR a = (NODE_PTR) malloc(sizeof(NODE));

   strcpy(a->name, value);
   a->nodetype = t;
   a->down[0] = p0;
   a->down[1] = p1;
   a->down[2] = p2;
   return a;
}


/********** bind utilities ************************************

   bind utilities maintain a list of (inappropriately named)
   PAIR elements.  The original idea was to maintain a list
   of (variable-name,variable-expr) pairs, which paired the
   name of an ops5 variable with the cursor expression that
   was used to reference its value.  Along the way, some more
   fields were added, but the name PAIR was not changed.

   the head of a bind-list is bind_list.  Among the interesting
   PAIR fields are:

   var - name of ops5 variable
   expr - the cursor expression that defines the value of this variable
   cont - name of the container that expr references
   used - boolean indicating whether this variable was referenced in 
          the predicate of any negated CE (again, all of this info
          is local to a single rule)

   init_bind() - initializes the bind_list
   bind(v,e,c) - creates a new element to bind for variable v, 
                 expression e, and container c
   find_bind(v) - returns handle to bind PAIR element that has
                  variable v; 0 is returned if not found.
   clear_used() - clears all used flags on current list
   set_used(e)  - sets the used flag of bind elements if their
                  variable is referenced in a given CE (e)

***************************************************************/

void init_bind ( void ) 
{
   bind_list = 0;
}

void bind( char *v, char *e, char *c ) 
{
PAIR_PTR p = (PAIR_PTR) malloc(sizeof(PAIR));

   strcpy(p->var, v);
   strcpy(p->expr, e);
   strcpy(p->cont, c);
   p->used = FALSE;
   p->next = bind_list;
   bind_list = p;
}

PAIR_PTR find_bind ( char *v )
{
PAIR_PTR p;

   foreach_pair(p) {
      if (strcmp(p->var, v)==0)
         return p;
   }
   return 0;
}

void clear_used ( void )
{
PAIR_PTR p;

   foreach_pair(p)
      p->used = FALSE;
}

/* set_used(e) - set's the used flag for each bind-pair if
   the bind-pair element has been referenced in the given
   condition element */

void set_used ( ELEMENT_PTR e )
{
PAIR_PTR    x;
CLAUSE_PTR  c;

   foreach_clause(c,e) {
      if (c->v == VAR) {
         x = find_bind(c->cons);
         if (!x) {
            fprintf(stderr, "cannot locate %s\n", c->cons);
            exit(1);
         }
         x->used = TRUE;
      }
   }
}


/************** P2 query generators *****************************

   print_assignments(r) - prints a set of assignment statements
           that are needed to evaluate negated predicates.  this
           function is used internally by print_negated_tests only.
   print_negated_tests(r) - for a given rule r, this function
           generates the boolean functions that are to be evaluated
           for testing negated CEs.  negated CEs are merely a filter
           that eliminates otherwise joinable objects
   make_positive_query(r,q,e) - this is the heart of the translator.
           given rule r, it returns in q a P2 query that corresponds
           to the predicate on the rhs of rule r.  e is a handle to
           a condition element; if not 0, it is to be treated as a
           positive CE (whether or not it actually is).  This strange
           parameter is needed when shadow objects are dominant.
   print_negated_variables(r) - when shadow cursors are declared,
           their predicates reference global variables.  This routine
           prints the decls of the global variables for rule r.
   make_negative_query(e,q,r) - creates a string q for (negated) CE e and 
           rule r that contains the predicate on a cursor that is to 
           evaluate the leaps test for negation.
   print_shadow_cursors(r) - print the P2 definition of the container
           and shadow cursors that are used in evaluating negated
           condition elements.  These cursors are referenced in the
           boolean procs generated by print_negated_tests.
   print_rule_head(r) - prints the head of rule r in ops5 format.
           used strictly for generating comments.
   print_cursor_typedefs() - prints the typedefs for all P2 cursors
           to be used in a leaps program/rule set.

*******************************************************************/   
static void print_assignments ( RULE_PTR r )
{
PAIR_PTR x;
char     *y;

    foreach_pair(x) {
       if (x->used) {
          y = 3+x->expr;
          printf("   %s_%d = %c->%s;\n", x->var,r->ruleno, x->expr[1], y);
       }
    }
}

/* call after make_positive_query - we need the bind list to be
   initialized */

#define MAX_NAME_ARRAY 20
NAME name_array[MAX_NAME_ARRAY];

static void print_negated_funcs(char name, char *C, char *S, 
                                RULE_PTR r, int k)
{
char comma = '(';
int  i;

   printf("\nBOOLEAN %c%d_%d(", name, r->ruleno, k);
   comma = ' ';
   for ( i = 0; i<MAX_NAME_ARRAY; i++ ) {
      if (strcmp(name_array[i],"")!=0) {
         printf("%c %s_cursor *%c", comma, name_array[i], (char) 'a'+i);
         comma = ',';
      }
   }
   printf(" )\n{\n");

   print_assignments(r);

   printf("   foreach(%s%d_%d) { return FALSE; }\n", C, r->ruleno, k );
   printf("   foreach(%s%d_%d) { return FALSE; }\n", S, r->ruleno, k );
   printf("   return TRUE;\n");
   printf("}\n\n");
}

void print_negated_tests( RULE_PTR r )
{
ELEMENT_PTR e;
PAIR_PTR    p;
int         k = 0;
int         i;
int         index;
char        t1[100], t2[100];
char        space[5];

   foreach_element(e,r) {
      k++;
      if (!e->neg) 
         continue;

      clear_used();
      set_used(e);
      for ( i = 0; i<MAX_NAME_ARRAY; i++) strcpy(name_array[i],"");

      foreach_pair(p) {
         if (p->used) {
            index = p->expr[1] - 'a';
            strcpy(name_array[index], p->cont);
         }
      }

      print_negated_funcs('N',"C","S",r,k);    
      if (negation_optimization)
         print_negated_funcs('V',"CC","SS",r,k);    

      /* now determine the call to this procedure */

      sprintf(t1," (N%d_%d(", r->ruleno, k);
      strcpy(space,"");

      for ( i = 0; i<MAX_NAME_ARRAY; i++ ) {
         if (strcmp(name_array[i],"")!=0) {
            sprintf(t2,"%s&$%c",space,(char) 'a'+i);
            strcat(t1,t2);
            strcpy(space,",");
         }
      }
      strcat(t1, ")) ");
      strcpy(e->negtest, t1);
   }
}

/* ele - make element identified by ele positive (even if it 
   isn't).  This is useful in defining predicates for dominant
   objects that are over negated containers */

int make_positive_query ( RULE_PTR r, char *query , ELEMENT_PTR ele)
{
ELEMENT_PTR e;
CLAUSE_PTR  c;
DISJ_PTR    d;
PAIR_PTR    x;
char        tmp[200];
char        curs[10];
char        rel[10];
char        and[5];
char        or[5];
char        nextelementline[25];
int         kk;
int         num_of_ces = 0;
BOOLEAN     printed_something;

   *query = '\0';
   init_bind();
   strcpy(curs,"$a");
   strcpy(and,"");
   strcpy(nextelementline,"");
   printed_something = FALSE;
   

   kk = 0;
   foreach_element(e,r) {
      kk++;
      if (e->neg && e != ele)
         continue;

      num_of_ces++;
      if (printed_something) {
         strcat(query,nextelementline);
         strcpy(nextelementline,"\\\n        ");
         printed_something = FALSE;
      }

      foreach_clause(c,e) {
         if (strcmp(c->relop,"")==0)
            strcpy(rel,"==");
         else
            strcpy(rel, c->relop);
         if (strcmp(c->relop,"<>")==0)
            strcpy(rel,"!=");

         switch(c->v) {
         case VAR:
            x = find_bind(c->cons);
            if (x) {
               sprintf(tmp," %s.%s %s %s ", curs, c->name, rel, x->expr);
               strcat(query,and);
               printed_something = TRUE;
               strcpy(and,"&&");
               strcat(query,tmp);
            } else {
               if (strcmp(c->relop,"")==0) {
                  sprintf(tmp,"%s.%s", curs, c->name);
                  bind(c->cons, tmp, e->name);
               } else 
                  fprintf(stderr, "rule %s, element %s: cannot create query", r->name,
                          e->name);
            }
            break;
         case CONS:
            if (is_numeric_cons(c->cons[0]))
               sprintf(tmp, " %s.%s %s %s ", curs, c->name, rel, c->cons);
            else
               if (string_optimization)
                  sprintf(tmp, " %s.%s %s RL_%s ", curs, c->name, rel, c->cons);
               else
                  sprintf(tmp, " %s.%s %s '%s' ", curs, c->name, rel, c->cons);
            strcat(query,and);
            printed_something = TRUE;
            strcpy(and,"&&");
            strcat(query,tmp);
            break;
         case DIS:
            strcat(query,and);
            printed_something = TRUE;
            strcpy(and,"&&");
            strcpy(or,"");
            strcat(query, " (");
            foreach_disj(d,c) {
               if (is_numeric_cons(d->name[0]))
                  sprintf(tmp,"%s(%s.%s==%s)", or, curs, c->name,d->name );
               else
               if (string_optimization)
                  sprintf(tmp,"%s(%s.%s==RL_%s)", or, curs, c->name,d->name );
               else
                  sprintf(tmp,"%sstrcmp(%s.%s,\'%s\')==0", or, curs, c->name,d->name );
               strcat(query,tmp);
               strcpy(or,"||");
            }
            strcat(query,") ");
            break;
         }
      }
      curs[1]++;
   }

   /* finally, add on negated tests */

   foreach_element(e,r) {
      if (e->neg) {
         strcat(query, and);
         strcat(query, e->negtest);
      }
   }

   return num_of_ces;
}


/* print_negated_variables can be called immediately after 
   make_positive_query().  The bind list is initialized */

void print_negated_variables ( RULE_PTR r )
{
PAIR_PTR   p;
FIELD_PTR  f;

   foreach_pair(p) {
      f = find_field(find_container(p->cont),p->expr + 3);
      if (!f) {
         fprintf(stderr, "can't find field %s in rule %s\n",p->expr+3, r->name);
      } else {
         switch (f->ftype) {
         case UNKNOWN: 
         default:
              fprintf(stderr,"ERROR: don't know type of %s in rule %s\n",
                     p->var, r->name);
              break;
         case INT:  
              printf("int %s_%d;\n",p->var, r->ruleno);
              break;
         case REAL:
              printf("float %s_%d;\n",p->var, r->ruleno);
              break;
         case STR:
              if (string_optimization)
                 printf("int %s_%d;\n",p->var, r->ruleno);
              else
                 printf("char *%s_%d;\n",p->var, r->ruleno);
              break;
         }
      }
   }
   printf("\n");
}

static void make_negative_query ( ELEMENT_PTR e, char *query , RULE_PTR r)
{
CLAUSE_PTR c;
DISJ_PTR   d;
FIELD_PTR  f;
char       tmp[100];
char       junk[100];
char       rel[10];
char       and[10];
char       or[10];
PAIR_PTR   x;
int        ruleno = r->ruleno;

    *query = '\0';
    strcpy(and,"");
    strcpy(or, "");

    foreach_clause(c,e) {
       if (strcmp(c->relop,"")==0)
          strcpy(rel,"==");
       else
          strcpy(rel, c->relop);
       if (strcmp(c->relop,"<>")==0)
          strcpy(rel,"!=");

       switch (c->v) {
       case CONS:
          if (is_numeric_cons(c->cons[0])) 
             sprintf(tmp," $.%s %s %s ", c->name, rel, c->cons );
          else
          if (string_optimization)
             sprintf(tmp," $.%s %s RL_%s ", c->name, rel, c->cons );
          else
             sprintf(tmp," $.%s %s '%s' ", c->name, rel, c->cons );
          break;
       case VAR:
          x = find_bind(c->cons);
          if (!x) {
             fprintf(stderr,"cannot locate %s\n", c->cons);
             exit(1);
          }
          f = find_field(find_container(x->cont), x->expr +3);
          if (!f)
             fprintf(stderr,"cannot find field %s in rule #%d\n", 
                     x->expr+3, ruleno);
          else {
             switch (f->ftype) {
             case INT:
             case REAL:
                  sprintf(tmp," $.%s %s %s_%d ", 
                          c->name, rel, c->cons, ruleno );
                  break; 
             case STR:
#if 0
                  if (string_optimization)
                     sprintf(tmp," $.%s %s %s_%d ", 
                             c->name, rel, c->cons, ruleno );
                  else
                     sprintf(tmp," $.%s %s *%s_%d ", 
                             c->name, rel, c->cons, ruleno );
#else
                  sprintf(tmp," $.%s %s %s_%d ", 
                             c->name, rel, c->cons, ruleno );
#endif
                  break;
              default:
                  fprintf(stderr,"unknown field type");
                  break;
            }
         }
         break;
       case DIS:
          strcpy(tmp," (");
          foreach_disj(d,c) {
             if (is_numeric_cons(d->name[0]))
                sprintf(junk,"$.%s==%s", c->name, d->name);
             else
                sprintf(junk,"$.%s=='%s'", c->name, d->name);
             strcat(tmp,or);
             strcpy(or,"||");
             strcat(tmp,junk);
          }
          strcat(tmp,") ");
          break;
       }
       strcat(query,and);
       strcpy(and,"&&");
       strcat(query,tmp);
   }
}

/* print_shadow_cursors can be called after make_positive_query,
   since it depends on the contents of bind-list */

void print_shadow_cursors ( RULE_PTR r )
{
ELEMENT_PTR e;
char        query[1000];
int         k = 0;

   foreach_element(e,r){
      k++;
      if (!e->neg)
         continue;
      printf("cursor <cont_%s>", e->name);
      make_negative_query(e,query,r);
      if (strcmp(query,"")!=0)
         printf(" where \"%s\"",query);
      printf("\n   C%d_%d;\n",r->ruleno, k);

      printf("cursor <shadow_%s>", e->name);
      if (strcmp(query,"")==0)
         printf(" where \"$._ts > dom_timestamp\"");
      else
         printf(" where \"%s && $._ts > dom_timestamp\"", query);
      printf("\n   S%d_%d;\n",r->ruleno, k);

      if (negation_optimization) {
         printf("cursor <cont_%s>", e->name);
         if (strcmp(query,"")==0)
            printf(" where \"$._ts >= last_timestamp\"");
         else
            printf(" where \"%s && $._ts >= last_timestamp\"",query);
         printf("\n   CC%d_%d;\n",r->ruleno, k);

         printf("cursor <shadow_%s>", e->name);
         if (strcmp(query,"")==0)
            printf(" where \"$._ts >= last_timestamp\"");
         else
            printf(" where \"%s && $._ts >= last_timestamp\"", query);
         printf("\n   SS%d_%d;\n",r->ruleno, k);
      }
   }
}

void print_rule_head ( RULE_PTR r )
{
ELEMENT_PTR e;
CLAUSE_PTR  c;
DISJ_PTR    d;

   foreach_element(e,r) {
      if (e->neg)
         printf("   - (%s ", e->name);
      else
         printf("   (%s ", e->name);
      foreach_clause(c,e) {
         switch(c->v) {
         case VAR:
            printf("^%s %s <%s> ", c->name, c->relop, c->cons);
            break;
         case CONS:
            printf("^%s %s %s ", c->name, c->relop, c->cons);
            break;
         case DIS:
            printf("^%s <<", c->name);
            foreach_disj(d,c) {
               printf(" %s ", d->name );
            }
            printf(">> ");
            break;
         }
      }
      printf(" )\n");
   }
}

#define EMPTY_NEGATED "\"\""

void print_cursor_typedefs ( void )
{
RULE_PTR r;
ELEMENT_PTR e;
ELEMENT_PTR ee;
char    query[1000];
char    negated[100];
int     num_of_ces;
char    curs, domcurs, elecurs;
char    comma;
char    *c;
char    and[6];

   foreach_rule(r) {
      printf("/**************************** rule #%d: %s :\n", 
             r->ruleno, r->name);
      print_rule_head( r );
      printf("    -->  *******************************/\n\n");
      make_positive_query(r,query,0);
      print_negated_variables(r);
      print_shadow_cursors( r );
      print_negated_tests( r ); 

      /* call mpq again, since now we know the text of
         negated queries */
      make_positive_query(r,query,0); 

      /* print #define query now */

      if (strcmp(query,"")==0) 
         printf("#define query_%d\n\n", r->ruleno);
      else
         printf("#define query_%d where \"%s\"\n\n",
                r->ruleno, query);

      domcurs = 'a' - 1;  /* actual dominant cursor in compcurs */
      elecurs = 'a' - 1;  /* character counter for element number */

      /* print #define negated here */

      strcpy(and,"");
      strcpy(negated,"\"");
      foreach_element(e,r) {
         if (e->neg) {
            strcat(negated,and);
            strcat(negated,e->negtest);
            strcpy(and," && ");
         }
      }
      strcat(negated,"\"");
      if (negation_optimization) {
         /* replace 'N' with 'V' */
         for (c = negated; *c != '\0'; c++) {
            if (*c == 'N') *c = 'V';
         }
      }
       
      printf("#define negated_%d %s\n\n", r->ruleno, negated);
      
      /* print cursor typedefs here */

      foreach_element(e,r) {
         elecurs++;
         if (e->neg) {
            make_positive_query(r,query,e);
            if (strcmp(query,"")==0)
               printf("#define query_%d_%c\n\n", r->ruleno, elecurs);
            else
               printf("#define query_%d_%c where \"%s\"\n\n",
                       r->ruleno, elecurs, query);
         }

         /* print cursor typedef here */
         
         printf("typedef compcurs ");

         num_of_ces = 0;
         curs = 'a'-1;
         comma = '<';
         foreach_element(ee,r) {
            if (ee->neg && e != ee)
               continue;
            curs++;
            if (ee->neg) {
               printf("%c %c shadow_%s", comma, curs,ee->name);
            }
            else
               printf("%c %c cont_%s", comma, curs,ee->name);
            comma = ',';
            num_of_ces++;
         }
         printf(" >\n");

         domcurs++;
         printf("   given < %c >\n", domcurs);
      
         if (num_of_ces != 1)  {
            if (!e->neg) {
               printf("   query_%d t%d_%c\n", r->ruleno, num_of_ces, domcurs);
               printf("   valid v%d_%c ", num_of_ces, domcurs);
               if (strcmp(negated,EMPTY_NEGATED)==0)
                  printf("\n");
               else
                  printf(" and negated_%d\n", r->ruleno);
            }
            else {
               printf("   query_%d_%c t%d_%c\n", 
                      r->ruleno, elecurs, num_of_ces, domcurs);
               printf("   valid v%d_%c", num_of_ces, domcurs);
               if (strcmp(negated,EMPTY_NEGATED)==0)
                  printf("\n");
               else
                  printf(" and negated_%d\n", r->ruleno);
            }
         }
         else {
            if (!e->neg) {
               printf("   query_%d\n", r->ruleno);
               if (strcmp(negated,EMPTY_NEGATED)!=0)
                  printf("   valid negated_%d\n",r->ruleno);
            }
            else {
               printf("    query_%d_%c\n", r->ruleno, elecurs);
               if (strcmp(negated,EMPTY_NEGATED)!=0)
                  printf("   valid negated_%d\n",r->ruleno);
            }
         }
         printf("   curs%d_%c;\n\n", r->ruleno, elecurs);
         if (e->neg)
            domcurs--;
      }
   }
}
 
   

/************************ node operations *********************

   the following routines dump their contents into a global
   variable nodecontents.

   sprintnode(n) -  print the contents of parse tree n into nodecontents.
  
*****************************************************************/ 
char nodecontents[1000];

static void spnode ( NODE_PTR n )
{
   strcat(nodecontents, " ");
   switch (n->nodetype) {
   case CONS_NODE:  
      strcat(nodecontents, n->name);
      break;
   case VAR_NODE:
      strcat(nodecontents,"<");
      strcat(nodecontents, n->name);
      strcat(nodecontents,">");
      break;
   default:
      strcat(nodecontents,"DONT_KNOW_HOW_TO_DUMP");
      break;
   }
}

void sprintnode ( NODE_PTR n )
{
   nodecontents[0] = '\0';
   spnode( n );
}


/******************** debugging utilities **********************

    dump_rule_list() - dumps the database of rule structures
    dump_query_list() - prints the queries for each rule

****************************************************************/

void dump_rule_list ( void ) {
RULE_PTR    r;
ACTION_PTR  a;
ARG_PTR     g;

   foreach_rule(r) {
      printf("(p %s\n", r->name);
      print_rule_head( r );
      printf("   -->\n");
      foreach_action(a,r) {
         switch(a->name) {
         case UPD: printf("   (modify %s", a->what);
                   break;
         case REM: printf("   (remove %s", a->what);
                   break;
         case MAK: printf("   (make %s", a->what);
                   break;
         case END: printf("   (halt");
                   break;
         case OUT: printf("   (write ");
         }

         foreach_arg(g,a) {
            sprintnode(g->node);
            printf(" ^%s %s ", g->name, nodecontents);
         }
         printf(" )\n");
      }
      printf(")\n\n");
   }
}

void dump_query_list( void )
{
RULE_PTR r;
char     query[1000];

   foreach_rule(r) {
      printf("(p %s\n", r->name);
      print_rule_head( r );
      make_positive_query( r, query,0 );
      printf("\nquery: %s\n\n",query);
      print_negated_variables( r );
   }
}


/******************* other print utilities ********************

   print_banner(n) - prints a banner with name n
   print_options() - prints list of options chosen for translation
   print_includes() - prints include files
   print_ext_includes() - prints includes for external routines
   print_valids() - prints #define valid predicates needed for the
             input rule set 
   print_forward_refs() - prints forward references - in particular
             instance procs (i#_#)

****************************************************************/
   
void print_banner( char *name )
{
   printf("/************************************\n");
   printf("           %10s\n",name);
   printf("************************************/\n\n");
}

#define PRINT_OPTION(OPTION) if (OPTION) printf("      %s\n", #OPTION)

void print_options ( void ) 
{
   printf("/************************************\n");
   printf("   options selected:\n");

   PRINT_OPTION(active_rule_optimization);
   PRINT_OPTION(string_optimization);
   PRINT_OPTION(leaps_debugging);
   PRINT_OPTION(persistence);
   PRINT_OPTION(garbage_collection);
   PRINT_OPTION(shadow_optimization);
   PRINT_OPTION(inline_ops);
   PRINT_OPTION(malloc_optimization);
   PRINT_OPTION(negation_optimization);
   PRINT_OPTION(predicate_indices);
   PRINT_OPTION(standard_output);
   PRINT_OPTION(timestamp_layer);
   PRINT_OPTION(shadow_container);
   PRINT_OPTION(attribute_indices);

   printf("************************************/\n\n");
}

void print_includes ( void )
{
  printf("#define DEBUG                 %d\n", leaps_debugging);
  printf("#define STRING_OPTIMIZATION   %d\n", string_optimization);
  printf("#define GARBAGE_COLLECTION    %d\n", garbage_collection);
  printf("#define SHADOW_OPTIMIZATION   %d\n", shadow_optimization);
  printf("#define NEGATION_OPTIMIZATION %d\n", negation_optimization);
  printf("#define MALLOC_OPTIMIZATION   %d\n", malloc_optimization);

  printf("\n");

  printf("#include <stdlib.h>\n");
  printf("#include \"leaps.h\"\n");
#if 0
  /* P2_fastmalloc.h is always, automatically included. (JAT) */
  if (malloc_optimization)
    printf("#include \"fastmalloc.h\"\n");
#endif
  printf("\n\n");
}

void print_ext_includes ( void )
{
PRED_PTR p;

   printf("/***************** external files *********************/\n\n");
   foreach_predicate(p, include_list) {
      printf("#include \"%s\"\n", p->name);
   }
}

static void print_repeat ( char *pattern, int max, char skip )
{
char and[50];
char k = 'a';
int  i;

   strcpy(and,"");

   for (i=0; i<max; i++, k++) {
      if (k == skip)
         continue;
      printf("%s", and);
      strcpy(and," and ");
      printf(pattern, k);
   }
}

void
print_valids (void)
{
  RULE_PTR r;
  ELEMENT_PTR e;
  int  max_size = 0;
  int  count, k;
  char c;

  foreach_rule(r)
  {
    count = 0;
    foreach_element(e,r) 
      if (!e->neg)
        count++;
    if (count > max_size)
      max_size = count;
  }
  max_size++;

  printf("\n/*****************  valid defines ****************/\n\n");

  for (c = 'a', count = 1; count <= max_size ; count++, c++) 
    printf("#define t%c \" $%c._ts <= dom_timestamp \"\n", c, c);
  printf("\n\n");

  for (c = 'a', count = 1; count <= max_size ; count++, c++) 
    printf("#define v%c \" (!deleted($%c)) \"\n", c, c);
  printf("\n\n");

  printf("#define and \" && \"\n\n");

  for (k = 1; k <= max_size; k++)
  {
    for (c = 'a', count = 1; count <= k ; count++, c++)
    {
      if (count == 1 && k == 1)
        continue;
      printf("#define t%d_%c and ", k, c);
      print_repeat("t%c",k, c);
      printf("\n");
    }
  }
  printf("\n\n");
       
  for (k = 1; k <= max_size; k++)
  {
    for (c = 'a', count = 1; count <= k ; count++, c++)
    {
      if (count == 1 && k == 1)
        continue;
      printf("#define v%d_%c ", k, c);
      print_repeat("v%c", k, c);
      printf("\n");
    }
  }
  printf("\n\n");
}

void print_forward_refs( void )
{
RULE_PTR r;
ELEMENT_PTR e;
char       domcurs;
char       comma;

   printf("/************* generated forward references ***************/");
   printf("\n\nVOID_FUNC  ");

   foreach_rule(r) {
      domcurs = 'a';
      comma   = ' ';
      foreach_element(e,r) {
         printf("%c i%d_%c", comma, r->ruleno, domcurs++);
         comma = ',';
      }
      if (r->next == 0)
         printf(";\n\n");
      else
         printf(",\n           ");
   }
}
  

/***************** typex routines **************************

   add_predicate_indices() - scans through each rule and each CE
         pulls out constant predicates and adds them to the list
         of predicates associated with the CE's container that
         can be indexed.

         it also keeps track of what rules use a particular predicate
         index.  Miranker says that knowing what rules are active
         is a good filter, and a rule is not active if its
         predicate index has no elements.

   print_active_rules() - prints the activate/deactive rule
         procedures for active rule optimizations.

*************************************************************/
 
void add_predicate_indices ( void )
{
RULE_PTR  r;
ELEMENT_PTR e;
CLAUSE_PTR c;
CONT_PTR   k;
PRED_PTR   p;

char     pred[1000];
char     tmp[100];
char     rel[10];
char     and[5];

   foreach_rule(r) {
      foreach_element(e,r) {
         if (shadow_container) {
            pred[0] = '\0';
            strcpy(and,"");
         } else {
            if (e->neg)
               strcpy(pred,"($._df)");
            else
               strcpy(pred,"(!$._df)");
            strcpy(and,"&&");
         }
         foreach_clause(c,e) {

            if (strcmp(c->relop,"")==0)
               strcpy(rel,"==");
            else 
               strcpy(rel, c->relop);
            if (strcmp(c->relop,"<>")==0)
               strcpy(rel,"!=");

            switch (c->v) {
            case CONS:
                 if (is_numeric_cons(c->cons[0]))
                    sprintf(tmp," $.%s %s %s ", c->name, rel, c->cons);
                 else
                 if (string_optimization)
                    sprintf(tmp," $.%s %s RL_%s ", c->name, rel, c->cons);
                 else
                    sprintf(tmp," $.%s %s '%s' ", c->name, rel, c->cons);
                 strcat(pred,and);
                 strcpy(and,"&&");
                 strcat(pred,tmp);
                 break;
            default:
            case VAR:
                 break;
            case DIS:
                 /* COULD OPTIMIZE HERE BY ADDING IN CONSTANT TESTS */
                 break;
            }
         }
         k = find_container( e->name );
         if (!k) 
            printf("undefined container %s line %d\n", e->name, line_number);
         else {
            if (strcmp(pred,"")!=0) {
               if (e->neg) {
                  /* add predicate to both positive and negative lists */
                  p = new_predicate(&k->pos_pred, pred);
                  p = new_predicate(&k->neg_pred, pred);
                  /* no active rules kept */
               }
               else {
                  p = new_predicate(&k->pos_pred, pred);
                  if (active_rule_optimization) {
                     sprintf(tmp,"active_rule%d", r->ruleno);
                     new_predicate(&p->first, tmp);
                  }
               }
            }
         }
      }
   }
}

static int print_active_procs ( PRED_PTR p, char *name, int i )
{
PRED_PTR a;

   i++;
   printf("\n/********* container %s: predicate: %s **************/\n\n",
          name, p->name);
   printf("void activate%d( void )\n{\n", i);
   foreach_predicate(a,p->first) {
      printf("   %s++;\n", a->name);
   }
   printf("}\n\n");

   printf("void deactivate%d( void )\n{\n", i);
   foreach_predicate(a,p->first) {
      printf("   %s--;\n", a->name);
   }
   printf("}\n\n");
   return i;
}

void print_active_rules ( void )
{
RULE_PTR  r;
CONT_PTR  c;
PRED_PTR  p;
PRED_PTR  a;
int       i = 0;
char      tmp[100];

   if (!active_rule_optimization)
      return;

   printf("/************ active rule variables, procs **************/\n\n");
   foreach_rule(r) {
      sprintf(tmp,"active_rule%d", r->ruleno);
      i = 0;
      foreach_container(c) {
         foreach_predicate(p, c->pos_pred) {
            foreach_predicate(a,p->first) {
               if (strcmp(tmp,a->name)==0) 
                  i++;
            }
         }
      }
      printf("int active_rule%d = %d;\n", r->ruleno,i);
   }

   i = 0;
   foreach_container(c) {
      foreach_predicate(p, c->pos_pred) {
         i = print_active_procs(p, c->name,i);
      }
#if 0
      if (c->has_shadow) {
         sprintf(tmp,"shadow_%s", c->name);
         foreach_predicate(p, c->neg_pred) {
            i = print_active_procs(p,tmp,i);
         }
      }
#endif
   }
}


/******** attribute indices stuff ***********/
/******* note: not consistent with -n option *********/

void add_attribute_indices ( void )
{
RULE_PTR r;
ELEMENT_PTR e;
CLAUSE_PTR c;
PAIR_PTR   x;
CONT_PTR   k;
char       query[1000];
BOOLEAN    must_scan = TRUE;
char       curs;

   foreach_rule(r) {
      make_positive_query(r,query,0);
      curs = 'a'-1;
      foreach_element(e,r) {
         if (!e->neg) 
            curs++;
         must_scan = TRUE;
         foreach_clause(c,e) {
            switch (c->v) {
            case VAR:
               if (!((strcmp(c->relop, "")==0) || (strcmp(c->relop,"==")==0)))
                  break;
               x = find_bind(c->cons);
               if (!x) {
                  fprintf(stderr,"cannot locate %s\n", c->cons);
                  exit(1);
               }
               k = find_container(e->name);
               if (e->neg) {
                  new_predicate(&k->neg_index, c->name);
                  must_scan = FALSE;
                  goto out;
               } else {
                  if (x->expr[1] != curs) {
                     new_predicate(&k->pos_index, c->name);
                     must_scan = FALSE;
                     goto out;
                  }
               }
               break;
            case DIS:
            case CONS:
               must_scan = FALSE;
               break;
            }
         }
out:     k = find_container(e->name);
         if (e->neg)
            k->neg_must_scan = k->neg_must_scan || must_scan;
         else
            k->pos_must_scan = k->pos_must_scan || must_scan;
      }
   }
}

void print_attribute_indices ( void )
{
CONT_PTR c;
PRED_PTR p;

   printf("/************ attributes to index \n");
   foreach_container(c) {
      printf("container %s : fields {", c->name);
      foreach_predicate(p, c->pos_index)
         printf(" %s ", p->name);
      printf("}");
      if (c->pos_must_scan)
         printf(" must scan");
      printf("\n");
      if (c->has_shadow) { 
         printf("shadow %s : fields {", c->name);
         foreach_predicate(p, c->neg_index)
            printf(" %s ", p->name);
         printf("}");
         if (c->neg_must_scan)
            printf(" must scan");
         printf("\n");
      }
   }
   printf("*************************************/\n");
}


/************** string constant conversion routines ***********

     max_string_size - scans containers for the maximum string
              length.  This length is used in declaring the size
              of a symbol table element.
     collect_string_constants - scans the predicates and actions
               of all rules and places in symbol_table the list
               of constant strings 
     print_symbol_table - prints the symbol_table in comment format
     generate_symbol_table - generates code to support symbol table

***************************************************************/ 

PRED_PTR symbol_table = 0;         /* list of all string symbols in 
                                      rule set */
int      string_size = 0;          /* maximum length of string */

void max_string_length ( void )
{
CONT_PTR c;
FIELD_PTR f;

   foreach_container(c) {
      foreach_field(f,c) {
         if (f->ftype == STR)
            if (string_size < f->size)
               string_size = f->size;
      }
   }
   if (string_size==0)
      string_size = MIN_STRING_SIZE;
}
     
   
void collect_string_constants ( void )
{
RULE_PTR r;
ELEMENT_PTR e;
CLAUSE_PTR c;
DISJ_PTR d;
FIELD_PTR f;
ACTION_PTR a;
ARG_PTR    g;
CONT_PTR   k;
int        i;

   /* Look for string constants in the rhs and lhs of 
      each rule and add them to the symbol_table (by removing
      duplicates  - always have the nil predicate though */

   new_predicate( &symbol_table, "nil");

   foreach_rule(r) {

      /* lhs */
      foreach_element(e,r) {
         foreach_clause(c,e) {
            f = find_field(e->cont, c->name);
            if (f->ftype != STR)
               continue;
            switch (c->v) {
            case CONS: new_predicate( &symbol_table, c->cons );
                       break;
            case DIS:  foreach_disj(d,c) {
                          if (!is_numeric_cons(d->name[0]))
                             new_predicate( &symbol_table, d->name );
                       }
                       break;
            case VAR:  break;
            }
         }
      }

      /* rhs */
      foreach_action(a,r) {
         switch (a->name) {
         case UPD: i = atoi(a->what);
                   k = (what_container(r,i))->cont;
                   foreach_arg(g,a) {
                      f = find_field( k, g->name );
                      if (f->ftype != STR)
                         continue;
                      new_predicate( &symbol_table, g->node->name );
                   }
                   break;
         case REM:
         case END:
         case OUT: break;
         case MAK: k = find_container(a->what);
                   foreach_arg(g,a) {
                      f = find_field( k, g->name );
                      if (f->ftype != STR)
                         continue;
                      new_predicate( &symbol_table, g->node->name );
                   }
                   break;
         }
      }
   }
}

void print_symbol_table ( void )
{
PRED_PTR p;

   printf("\n\n/****************** symbol table ***********\n\n");
   foreach_predicate(p, symbol_table) {
      printf("   %s\n", p->name);
   }
   printf("\n****************** end symbol table ***********/\n\n");
}

void generate_symbol_table ( void )
{
PRED_PTR p;

   printf("\n\n/****************** symbol table ***********/\n\n");
   max_string_length();
   printf("\ntypedef char string[%d];\n\n", string_size);
   printf("typedef struct {\n");
   printf("   string  name;\n");
   printf("} SYMBOL;\n\n");
   printf("string  *word;\n\n");
   printf("container < SYMBOL > stored_as symbol_x with {\n");
   printf("   bintree key is name;\n");
   printf("} symbol_table;\n\n");
   printf("cursor <symbol_table> where \"$.name == *word\" sym;\n\n");

   foreach_predicate(p, symbol_table) {
      printf("int RL_%s;\n", p->name);
   }

   printf("\n\nint add_symbol( char *n )\n");
   printf("{\n");
   printf("SYMBOL s;\n\n");
   printf("   strcpy(s.name,n);\n");
   printf("   insert(sym,s);\n");
   printf("   return (int) sym.name;\n");
   printf("}\n\n");

   printf("int add_unique_symbol( char *n )\n");
   printf("{\n");
   printf("   word = (string *) n;\n");
   printf("   foreach(sym) { return (int) sym.name; };\n");
   printf("   return add_symbol( n );\n");
   printf("}\n\n");
   
   printf("void init_symbol_table ( void )\n");
   printf("{\n");
   printf("   open_cont( symbol_table );\n");
   printf("   init_curs( sym );\n");
   foreach_predicate(p, symbol_table) {
      printf("   RL_%s = add_symbol(\"%s\");\n", p->name, p->name);
   }
   printf("}\n\n");
}
 
   


/************************************** debugging ************

   main() - Helped debug initial rule sets.
   Probably not useful any more. (DSB)

**************************************************************/

#if DEBUG

void main ( void )
{
RULE_PTR r;
ELEMENT_PTR e;
CLAUSE_PTR c;
ACTION_PTR a;

   r = new_rule("make_L");
   e = new_element(r, "stage", FALSE);
   new_clause(e, "value", "", CONS, "detect_junctions");
   e = new_element(r, "edge", CONS);
   new_clause(e, "p1", "", VAR, "base_point");
   new_clause(e, "p2", "", VAR, "p2");
   new_clause(e, "joined", "", CONS, "false");
   e = new_element(r, "edge", FALSE);
   new_clause(e, "p1", "", VAR, "base_point");
   new_clause(e, "p2", "", VAR, "p3");
   new_clause(e, "p2", "<>", VAR, "p2");
   new_clause(e, "joined", "", CONS, "false");
   e = new_element(r, "edge", TRUE);
   new_clause(e, "p1", "", VAR, "base_point");
   new_clause(e, "p2", "<>", VAR, "p2");
   new_clause(e, "p2", "<>", VAR, "p3");

   a = new_action(r, "make", "junction");
   new_arg(a, "type", new_node("L",CONS_NODE, 0, 0, 0));
   new_arg(a, "base_point", new_node("base_point", VAR_NODE, 0,0,0));
   new_arg(a, "p1", new_node("p2", VAR_NODE, 0,0,0));
   new_arg(a, "p2", new_node("p3", VAR_NODE, 0,0,0));
   a = new_action(r, "modify", "2");
   new_arg(a, "joined", new_node("true", CONS_NODE, 0,0,0));
   a = new_action(r, "modify", "3");
   new_arg(a, "joined", new_node("true", CONS_NODE, 0,0,0));

   r = new_rule("label_L");
   e = new_element(r, "stage", FALSE);
   new_clause(e,"value","",CONS,"labeling");
   e = new_element(r, "junction", FALSE);
   new_clause(e,"type","",CONS,"L");
   new_clause(e,"base_point","",VAR,"p1");
   e = new_element(r, "edge", FALSE);
   new_clause(e,"p1","",VAR,"p1");
   new_clause(e,"p2","",VAR,"p2");
   c = new_clause(e,"label","",DIS,"");
   new_disj(c,"+");   
   new_disj(c,"-");
   e = new_element(r, "edge", FALSE);
   new_clause(e,"p1","",VAR,"p1");
   new_clause(e,"p2","<>",VAR,"p2");
   new_clause(e,"label","",CONS,"nil");

   a = new_action(r, "modify", "4");
   new_arg(a, "label", new_node("B", CONS_NODE, 0,0,0));
   
   dump_query_list();
}
#endif DEBUG
