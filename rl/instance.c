/* $Id: instance.c,v 45.0 1997/09/19 05:46:05 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/********************************************************
   this file is used primarily for generating procedures 
   for rule fire and instances.  One of the big tasks of
   organizing a leaps rule set is determining the ordering
   of rule firings.  This is accomplished by sorting rules
   on the number of CEs of the rule, its original position
   in the rule set, and object that is bound/dominant.

   A special sort structure (SORT) was defined for this purpose.
   A sort array of 10000 elements is declared; should be sufficient
   for all but gargantuan rule sets. (DSB)

*********************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "rl.h"

typedef struct sorted {
   int  cont;           /* container number */
   int  ruleno;         /* rule number */
   int  no_ces;         /* number of condition elements in given rule */
   int  bind_position;  /* 1 <= bind position <= no_ces */
}  SORT, *SORT_PTR;

#define MAX_ARRAY  10000 /* max # of rules * max # of CEs per rule */

SORT array[MAX_ARRAY];
int  avail = 0;


/********************** rule ordering functions *****************

   orderfunc() - used by Unix qsort to sort rules 
   print_array() - strictly used for debugging
   order_rules() - used to order rules ala leaps
   find_rule(cx, rx, bx) - returns index in array to the rule for
           container index cs, ruleno rx, bind position bx.
   print_first_rule() - prints the declaration of the first-rule array.

******************************************************************/

/* This routine is not prototyped, because this routine is passed
   as the fourth argument to qsort(), and the prototype of qsort
   expects its fourth argument to be not prototyped. (JAT) */

int
orderfunc (i, j)
  SORT_PTR i;
  SORT_PTR j;
{
  int diff;

  diff = i->cont - j->cont;
  if (diff)
    return(diff);
  diff = j->no_ces - i->no_ces;
  if (diff)
    return(diff);
  diff = i->ruleno - j->ruleno;
  if (diff)
    return(diff);
  return(i->bind_position - j->bind_position);
}

void
print_array (void)
{
  int k;
  CONT_PTR c;
  char     *n;
  char     tmp[100];

  printf("\nsorted array\n\n");
  for (k=0; k < avail; k++) {
    tmp[0] = '\0';
    n = tmp;
    foreach_container(c) {
      if (c->cont_num == array[k].cont) {
        n = c->name;
        break;
      }
      if (c->shadow_num == array[k].cont) {
        sprintf(tmp,"shadow_%s", c->name);
        n = tmp;
        break;
      }
    }
    
    printf("%15s %5d %5d %5d\n",n, array[k].no_ces,
           array[k].ruleno, array[k].bind_position);
  }
}

void
order_rules (void) 
{
  RULE_PTR    r;
  ELEMENT_PTR e;
  int         no_ces;
  int         pos;

  foreach_rule(r) {
    no_ces = 0;
    foreach_element(e,r) no_ces++;

    pos = 0;
    foreach_element(e,r) {
      pos++;
      if (e->neg)
        array[avail].cont       = e->cont->shadow_num;
      else
        array[avail].cont       = e->cont->cont_num;
      array[avail].ruleno        = r->ruleno;
      array[avail].no_ces        = no_ces;
      array[avail].bind_position = pos;
      avail++;
      if (avail >= MAX_ARRAY) {
        fprintf(stderr, "array size exceeded\n");
        exit(1);
      }
    }
  }
  qsort((char*)array, avail, sizeof(SORT), orderfunc);
}

int
find_rule (int cont, int ruleno, int bind)
{
  int k;

  for (k = 0; k < avail; k++) {
    if (array[k].cont == cont &&
        array[k].ruleno == ruleno &&
        array[k].bind_position == bind)
      return k; 
  }
  fprintf(stderr,"cannot find next rule for rule #%d bind %d\n",
          ruleno, bind);
  exit(1);
} 

int
skip_rule (int cont, int ruleno, int bind)
{
  int k;

  for(k = find_rule(cont, ruleno, bind)+ 1; k < avail; k++) {
    if (ruleno != array[k].ruleno)
      return k;
  }
  return k;
}

/* find_first_rule returns -1 if the input container is
   never referenced on the right hand side of a rule */

static int
find_first_rule (int cont)
{
  int k;

  for (k=0; k<avail; k++) {
    if (array[k].cont == cont)
      return k;
  }
  return -1;
}

/* print_first_rule assumes that container numbers are
   assigned in order of container list */

void
print_first_rule (void)
{
  CONT_PTR c;
  int      k;

  printf("VOID_FUNC_PTR first_rule[] =\n");
  printf("   { 0,"); 
  foreach_container(c) {
    k = find_first_rule(c->cont_num);
    if (k == -1)
      printf("pop, ");
    else
      printf(" i%d_%c,",array[k].ruleno,'a'-1+array[k].bind_position);
    if (c->has_shadow) {
      k = find_first_rule(c->shadow_num);
      printf(" i%d_%c,",array[k].ruleno,'a'-1+array[k].bind_position);
    }
  }
  printf(" 0};\n\n");
  printf("int rfc = 1;\n\n");
}
    

/**************** print instance utilities *******************

   print_instances() - prints instance procedures
   what_container(r,k) - return handle of positive CE #k in rule r
   print_action(r,a,b) - strictly for comments. prints action a of 
           rule r, with optional banner header b
   printnode(n,b) - print node n optionally in ops5 format b

**************************************************************/

static void
make_instance_string (int n, char *str) 
{
  if (n >= avail || array[n].cont != array[n-1].cont)
    strcpy(str,"pop");
  else
    sprintf(str, "i%d_%c",
            array[n].ruleno, 'a'-1+array[n].bind_position);
}

void
print_instances (void)
{
  RULE_PTR r;
  ELEMENT_PTR e;
  ELEMENT_PTR e1;
  char elecurs;
  char domcurs;
  int  n;
  int  no_positive_ces;
  int  i;
  char comma;
  char nextr[100];
  int  no_ces;
  char curstype[100];
  char skipr[100];
  char chr;

  print_first_rule();
  foreach_rule(r) {

    no_positive_ces = 0;
    foreach_element(e,r) 
      if (!e->neg)
        no_positive_ces++;

    elecurs = 'a'-1;  /* character counter for element number */
    domcurs = 'a'-1;  /* actual cursor that is dominant */

    foreach_element(e,r) {
      elecurs++;
      domcurs++;
      
      printf("void i%d_%c(void)\n", r->ruleno, elecurs);
      if (e->neg) {
        n = find_rule(e->cont->shadow_num, r->ruleno, 
                      (int) elecurs - 'a' + 1) + 1;
        make_instance_string (n, nextr);

        n = skip_rule(e->cont->shadow_num, r->ruleno, 
                      (int) elecurs - 'a' + 1);
        make_instance_string(n, skipr);
      }     
      else {
        n = find_rule(e->cont->cont_num, r->ruleno, 
                      (int) elecurs - 'a' + 1) + 1;
        make_instance_string (n, nextr);
        n = skip_rule(e->cont->cont_num, r->ruleno, 
                      (int) elecurs - 'a' + 1);
        make_instance_string(n, skipr);
      }
      printf("{\n");
      sprintf(curstype, "curs%d_%c", r->ruleno, elecurs);

      printf("   bind(%s, c->%c, active_rule%d, %s, %s_list );\n", 
             curstype, domcurs, r->ruleno, skipr, curstype);

      printf("   if (watch)\n");
      printf("      fprintf(stderr,\"%s. Firing rule %d (%s) ",
             "%d",r->ruleno,r->name);
      foreach_element(e1,r) {
         if (!e1->neg) 
            printf(" %s","%d");
      }
      printf("\\n\",rfc++");
      chr = 'a'-1;
      foreach_element(e1,r) {
         if (!e1->neg || e1 == e) {
            chr++;
            printf(",c->%c._ts",chr);
         }
      }
      printf(");\n");

      printf("   fire_rule%d",r->ruleno);
      no_ces = no_positive_ces;
      comma = '(';
      for (i = 1; i<=no_ces; i++) {
        printf("%c &c->%c", comma, 'a'-1+i);
        comma = ',';
      }
      printf(" );\n");
      printf("   next_rule( %s, %s_list );\n", nextr, curstype);
      printf("}\n\n");

      if (e->neg)
        domcurs--;
    }
  }
}


ELEMENT_PTR
what_container (RULE_PTR r, int count)
{
  ELEMENT_PTR e;

  foreach_element(e,r) {
    if (!e->neg) {
      count--;
      if (!count)
        break;
    }
  }
  return e;
}

void
print_action (RULE_PTR r, ACTION_PTR a, BOOLEAN banner)
{
  ELEMENT_PTR e;
  ARG_PTR     g;
  int         i;

  if (banner)
    printf("   /** ");

  switch (a->name) {
  case UPD:
    i = atoi(a->what);
    e = what_container(r, i);
    printf("(modify %d -- %s --",i,e->name);

    foreach_arg(g,a) {
      printf(" ^%s ",g->name);
      printnode(g->node, TRUE);
    }
    printf(")"); 
    break;

  case REM:
    printf("(remove ");
    foreach_arg(g,a) {
      i = atoi(g->name);
      e = what_container(r, i);
      printf("%d -- %s -- ",i,e->name);
    }
    printf(")");
    break;

  case MAK:
    printf("(make %s", a->what);    
    foreach_arg(g,a) {
      printf(" ^%s ",g->name);
      printnode(g->node, TRUE);
    }
    printf(" )");
    break;

  case END:
    printf("(halt)");
    break;

  case OUT:
    printf("(write ");
    foreach_arg(g,a) {
      printnode(g->node, TRUE);
    }
    printf(")");
    break;
  }

  if (banner)
    printf(" **/\n");
}

void
printnode (NODE_PTR n , BOOLEAN ops5format)
{
  PAIR_PTR x;
  char     c;

  switch (n->nodetype) {
  case CONS_NODE:
    printf(" %s", n->name);
    break;

  case VAR_NODE:
    if (ops5format)
      printf(" <%s>", n->name);
    else {
      x = find_bind(n->name);      
      if (!x) {
         fprintf(stderr,"cannot locate %s\n", n->name);
         exit(1);
      }
      c = x->expr[1];
      printf(" %c->%s",c,3+x->expr);
    }
    break;

  case CRLF_NODE:
    if (ops5format)
      printf(" (CRLF)");
    else
      printf(" \\n");
    break;

  case COMPUTE_NODE:
    if (ops5format) {
      printf(" COMPUTE(");
      printnode(n->down[0], TRUE);
      printf(")");
    } else {
      printnode(n->down[0], FALSE);
    }
    break;

  case OPR_NODE:
    printnode(n->down[0], ops5format);
    printf(" %s", n->name);
    printnode(n->down[1], ops5format);
    break;

  case UFUNC_NODE:
    printf(" %s(",n->name);
    /* arguments are listed in reverse order... */
  { NODE_PTR m;
    NODE_PTR last = 0;
    while (last != n->down[0]) {
      for (m = n->down[0]; m->down[0] != last ; m = m->down[0]) ;
      last = m;
      printnode(m,FALSE);
      printf(",");
    }
  }
    printf(" &r )");
    break;
  }
}


/******************** fire rule functions *********************

   insert_into_shadow(e,k,b) - generate the code to insert into
      shadow container.  e is the handle to a CE (presumably
      associated with the given container whose shadow insertion
      is to be performed).  k is a character that is the compcurs
      alias of the cursor that references the record that is to be
      shifted into the shadow container.

      boolean b was added later: if TRUE, it automatically 
      prints the closing } on an insert-shadow call.

   print_rulefires() - prints rule fire routines

***************************************************************/

void
insert_into_shadow (ELEMENT_PTR e, char k, BOOLEAN last_brace)
{
char *push;
  if (e->cont->has_shadow) {
    printf("   {  %s r;\n", e->name);
    printf("      getrec(*%c,r);\n",k);

    if (!timestamp_layer) {
      /* this is timestamp of deletion (where updates
         are modeled by deletion followed by insertion) */

      printf("      r._ts =  global_counter++;\n");
    }

    if (inline_ops) {
      printf("      insert(a_shadow_%s,r);\n",e->name);
      if (shadow_optimization) 
         push = "push_wl_end";
      else
         push = "push_end";
      printf("      %s(a_shadow_%s.obj, a_shadow_%s._ts, shadow_%s_num);\n",
             push, e->name, e->name, e->name);
    }
    else
      printf("      insert_shadow_%s(&r);\n",e->name);
    if (last_brace)
      printf("   }\n");
  }
}

  void print_updates (char *tab, char *lhs)
  {
    c = find_container(e->name);
    foreach_arg(g,a) {
      found = FALSE;
      foreach_field(f,c) {
        if (strcmp(g->name,f->name)==0) {
          found = TRUE;
          break;
        }
      }
      if (!found) {
        fprintf(stderr,"unknown field %s in container %s\n", 
                g->name, e->name);
        continue;
      }
    if (f->ftype == STR) {
      switch(g->node->nodetype) {
      case CONS_NODE: 
        if (string_optimization)
          printf("%s%s.%s = RL_%s;\n",
                 tab, lhs, g->name,g->node->name);
        else
          printf("%sstrcpy(%s.%s,\"%s\");\n", 
                 tab, lhs, g->name,g->node->name);
        break;
      case UFUNC_NODE:
        if (string_optimization) {
          printf("%s%s.%s = add_unique_symbol(",tab, lhs, g->name);
          printnode(g->node, FALSE);
          printf(");\n");
        } else {
          printf("%sstrcpy(%s.%s,", tab, lhs, g->name);
          printnode(g->node, FALSE);
          printf(");\n");
        }
        break;
      case VAR_NODE:
        if (string_optimization) {
           printf("%s%s.%s = ", tab, lhs, g->name);
           printnode(g->node, FALSE);
           printf(";\n");
        }
        else {
           printf("%sstrcpy(%s.%s,", tab, lhs, g->name);
           printnode(g->node, FALSE);
           printf(");\n");
        }
        break;
      default:
        printf("%s%s.%s = ", tab, lhs, g->name);
        printnode(g->node,FALSE);
        printf(";\n");
      }
    } else {
      printf("%s%s.%s = ", tab, lhs, g->name);
      printnode(g->node,FALSE);
      printf(";\n");
    }
  }

}
void
print_rulefires (void)
{
  RULE_PTR r;
  ELEMENT_PTR e;
  ACTION_PTR  a;
  ARG_PTR     g;
  CONT_PTR    c;
  FIELD_PTR   f;
  PAIR_PTR    x;
  BOOLEAN     found;
  char     comma;
  char     k;
  char     query[1000]; 
  int      i;
  char     chr;
  char     *push;



printf("\n/*************** fire rule procs *****************/\n\n");
foreach_rule(r) {

  printf("/**************************** rule %s :\n", r->name);
  print_rule_head(r);
  printf("    -->  *******************************/\n\n");

  make_positive_query(r,query,0);
  printf("void fire_rule%d", r->ruleno);
  comma = '(';
  k = 'a';
  foreach_element(e,r) {
    if (!e->neg) {
      printf("%c %s_cursor *%c", comma, e->name, k);
      k++;
      comma = ',';
    }
  }
  printf(" )\n");
  printf("{\n");

  foreach_action(a,r) {
    switch (a->name) {
    case UPD:
      print_action(r,a,TRUE);
      i = atoi(a->what);
      e = what_container(r, i);
      k = 'a'-1+i;

      printf("   {  %s r;\n", e->name);
      if (!e->cont->has_shadow) {
        /* to match the timestamps generated by leaps,
           increment the counter before every modification;
           see also REM.  The test for the shadow condition
           precludes incrementing the counter three times per modification */
        printf("      global_counter++;\n");
      }
      printf("      getrec(*%c,r);\n", k);
      if (e->cont->has_shadow) {
        if (shadow_optimization) 
           push = "push_wl_end";
        else
           push = "push_wl";
        if (!timestamp_layer)
           printf("      r._ts =  global_counter++;\n");
        if (inline_ops) { 
           printf("      insert(a_shadow_%s,r);\n", e->name);
           printf("      %s(a_shadow_%s.obj, a_shadow_%s._ts, shadow_%s_num);\n"
                   ,push, e->name, e->name, e->name);
       }
        else
          printf("      insert_shadow_%s(&r);\n", e->name);
      }
      print_updates("      ", "r");
      if (!timestamp_layer) {
        if (e->cont->has_shadow)
          printf("      r._ts =  global_counter++;\n");
        else
          printf("      r._ts =  global_counter++;\n");
      }
      if (inline_ops) {
        printf("      insert(a_%s,r);\n", e->name);
        printf("      push_wl( a_%s.obj, a_%s._ts, %s_num );\n",
             e->name, e->name, e->name);
      }
      else
        printf("      insert_%s(&r);\n", e->name);
      if (!timestamp_layer)
        printf("      %c->_ts = global_counter;\n",k);
      if (inline_ops) 
        printf("      delete(*%c);\n", k);
      else 
        printf("      delete_%s(%c);\n", e->name, k);
      printf("   }\n\n");
      break;
      
    case REM:
      print_action(r,a,TRUE);
      foreach_arg(g,a) {
        i = atoi(g->name);
        e = what_container(r, i);
        k = 'a'-1+i;

        insert_into_shadow(e,k,TRUE);
        if (!timestamp_layer && !e->cont->has_shadow)
          printf("   %c->_ts = global_counter++;\n",k);
        else
          printf("   %c->_ts = global_counter;\n",k);
        if (inline_ops) 
          printf("   delete(*%c);\n\n", k);
        else 
          printf("   delete_%s(%c);\n\n", e->name, k);
      }
      break;

    case MAK:
      print_action(r,a,TRUE);
      c = find_container(a->what);
      printf("   { %s r;\n", a->what);
      foreach_field(f,c) {
        found = FALSE;
        foreach_arg(g,a) {
          if (strcmp(f->name,g->name)==0) {
            found = TRUE;
            break;
          }
        }
        if (!found) {
          if (f->ftype == STR)
            if (string_optimization)
              printf("     r.%s = RL_nil;\n",f->name);
            else
              printf("     strcpy(r.%s,NILSTR);\n",f->name);
          else
            printf("     r.%s = NILVAL;\n",f->name);
        }
        else {
          if (f->ftype == STR) {
            if (g->node->nodetype == CONS_NODE) {
              if (string_optimization)
                printf("     r.%s = RL_%s;\n",
                       f->name,g->node->name);
              else
                printf("     strcpy(r.%s,\"%s\");\n",
                       f->name,g->node->name);
            } else {
              if (string_optimization) {
                printf("     r.%s = ", f->name);
                printnode(g->node, FALSE);
                printf(";\n");
              }
              else {
                printf("     strcpy(r.%s,", f->name);
                printnode(g->node, FALSE);
                printf(");\n");
              }
            }
          } else {
            printf("     r.%s = ",f->name);
            printnode(g->node, FALSE);
            printf(";\n");
          }
        }
      }

      if (!timestamp_layer)
        printf("     r._ts =  global_counter++;\n");

      if (inline_ops) {
        printf("     insert(a_%s,r);\n", a->what);
        printf("     push_wl(a_%s.obj, a_%s._ts, %s_num);\n",
                     a->what, a->what, a->what);
      }
      else
        printf("     insert_%s(&r);\n", a->what);
      printf("   }\n\n");
      break;

    case END:
      print_action(r,a,TRUE);
      printf("   printf(\"OPS5c terminated via halt statement.\\n\");\n");
      printf("   printf(\"OPS5c terminated via halt statement.\\n\");\n");
      printf("   exit(0);\n");
      break;

    case OUT:
      print_action(r,a,TRUE);
      printf("   printf(\"");
      foreach_arg(g,a) {
        switch (g->node->nodetype) {
        case CONS_NODE:
          printf(" %s", g->node->name);
          break;
        case VAR_NODE:
          x = find_bind(g->node->name);
          if (!x) {
             fprintf(stderr,"cannot locate %s\n", g->node->name);
             exit(1);
          }
          chr = x->expr[1];
          e = what_container(r, (int) chr - 'a' + 1);
          f = find_field(e->cont, 3+x->expr);
          if (f->ftype == STR) 
            printf(" %s","%s");
          else
            printf(" %s","%d");
          break;
        case CRLF_NODE:
          printf("\\n");
          break;
        case COMPUTE_NODE:
          printf(" %s", "%d");
          break;
        default:
          fprintf(stderr,"unknown write token in rule %s\n",
                  r->name);
        }
      }
      printf("\"");
      foreach_arg(g,a) {
        switch (g->node->nodetype) {
        case CONS_NODE:
          break;
        case VAR_NODE:
          x = find_bind(g->node->name);
          if (!x) {
             fprintf(stderr,"cannot locate %s\n", g->node->name);
             exit(1);
          }
          chr = x->expr[1];
          e = what_container(r, (int) chr - 'a' + 1);
          f = find_field(e->cont, 3+x->expr);
#if 0
          if (f->ftype == STR && string_optimization)
            printf(", *%c->%s",chr,3+x->expr);
          else
            printf(", %c->%s",chr,3+x->expr);
#else
          printf(", %c->%s",chr,3+x->expr);
#endif
          break;
        case COMPUTE_NODE:
          printf(", ");
          printnode(g->node,FALSE);
          break;
        default:
          break;
        }
      }
      
      printf(");\n\n");
      break;

    default:
      fprintf(stderr,"unrecognized action"); exit(1);
    }
  }
  printf("}\n\n");
}
}


/******************* print defines **************/

void
print_defines (void)
{
   printf("/**************** generated #defines *******************/\n\n");
   printf("#define bind( curstype, kdcurs, active_rule, skiprule, alist) \\\n");
   printf("   curstype *c; \\\n");
   if (active_rule_optimization) {
      printf("   if (active_rule) { \\\n");
      if (malloc_optimization)
         printf("      if (!fresh) { P2_PUTSPACE(alist,top.curs); } \\\n");
      else if (garbage_collection)
         printf("      if (!fresh) { free(top.curs); } \\\n");
      printf("      fresh = TRUE; top.current_rule = skiprule; \\\n");
      printf("      skiprule(); return; \\\n");
      printf("      } \\\n");
   }
   printf("   if (fresh) { \\\n");
   if (malloc_optimization) 
      printf("      c = (curstype*) P2_GETSPACE(alist,curstype); \\\n");
   else
      printf("      c = (curstype*) malloc(sizeof(curstype)); \\\n");
   printf("      top.curs = (void*) c;\\\n");
   printf("      initk(*c); \\\n");
   printf("      pos(kdcurs,top.cursor_position); \\\n");
   printf("   } else {  \\\n");
   printf("      c = (curstype *) top.curs; \\\n");
   printf("      goto cnt; \\\n");
   printf("   } \\\n");
   printf("   foreachk(*c) {");
   if (negation_optimization) {
      printf("\\\n      top.last_timestamp = global_counter;\n");
   }
   printf("\n\n");
   printf("#define next_rule( nextrule, alist ) \\\n");
   printf("      return; \\\n");
   if (negation_optimization)
      printf("cnt : last_timestamp = top.last_timestamp; \\\n");
   else
      printf("cnt: ; \\\n");
   printf("   } \\\n");
   if (malloc_optimization) 
      printf("   P2_PUTSPACE(alist, c); \\\n");
   else if (garbage_collection)
      printf("   free(c); \\\n");
   printf("   fresh = TRUE; top.current_rule = nextrule; \\\n");
   printf("   nextrule(); return;");
   printf("\n\n");
}


void print_list_headers (void)
{
RULE_PTR r;
ELEMENT_PTR e;
char k;

   if (!malloc_optimization)
      return;

   printf("/********* avail list declarations ****************/\n\n");
   foreach_rule(r) {
      k = 'a' - 1;
      foreach_element(e,r) {
         k++;
         printf("curs%d_%c **curs%d_%c_list = 0;\n", r->ruleno, k, r->ruleno, k);
      }
   }
   printf("\n\n");
}
         
         


/********************** print_ins_del_ops **********************/

static void print_op(char *contname, BOOLEAN shadow)
{
char shad[10];
char *push;

   if (shadow)
      strcpy(shad,"shadow_");
   else
      strcpy(shad,"");

   if (shadow_optimization && shadow)
      push = "push_wl_end";
   else
      push = "push_wl";

   printf("void insert_%s%s (%s *r)\n", shad, contname, contname);
   printf("{\n");
   printf("   insert(a_%s%s,*r);\n", shad, contname);
   printf("   %s( a_%s%s.obj, a_%s%s._ts, %s%s_num );\n",
          push, shad, contname, shad, contname, shad, contname );
   printf("}\n\n");
  
   printf("void delete_%s%s (%s%s_cursor *c)\n", 
           shad, contname, shad,contname);
   printf("{\n");
   printf("   delete(*c);\n");
   printf("}\n\n");
}

    
void print_ins_del_ops (void)
{
CONT_PTR c;

   printf("/************ insertion and deletion operations ********/\n\n");
   foreach_container(c) {
      print_op(c->name, FALSE);
      if (c->has_shadow) {
         print_op(c->name, TRUE);
      }
   }
}

