/* $Id: container.c,v 45.0 1997/09/19 05:46:04 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "rl.h"

/********************* container.c *****************************
  this file has most (if not all) of the functions that deal
  with containers.  A single list of containers is maintained,
  rooted at the variable container_list.  Each element of the
  list is of type CONT.

  Among CONT fields that are interesting are:

  name       -  name of container
  first      -  points to a list of field declarations
  has_shadow -  a shadow is maintained for CE over containers that
                are negated
  pos_pred   -  a list of predicates that are to be indexed on containers
  neg_pred   -  a list of predicates that are to be indexed on shadow
                containers
  cont_num   -  an internal number that identifies the container
                (container names are too long).

             the following are initialized by new_container and
             set by add_attribute_indices

  must_scan  -  is there a rule that requires us to scan the container?
  pos_index  -  list of fields to index on positive container
  neg_index  -  list of fields to index on shadow container

  Associated with each element of type CONT is a list of fields
  of type FIELD.  Among FIELD fields that are interesting are:

  name       -  name of container
  num        -  internally assigned number identifier for field
  ftype      -  type of field (INT, REAL, STR)
  size       -  size of char array (if field is STR)

******************************************************************/

int  predicate_index_number;

CONT_PTR  container_list = 0;    /* list of containers */
int       field_num = 1;


/************ container operations *******************

  new_container(n) - registers a new container with name 'n', 
                     returns handle c. initially, it is assumed that 
                     a container has no shadow.
  make_shadow(c)   - given handle c to container, flag that c has a
                     shadow.
  find_container(n) - returns handle to definition of container 'n'.

*****************************************/

CONT_PTR
new_container (char *name)
{
  CONT_PTR n = (CONT_PTR) malloc(sizeof(CONT));
  CONT_PTR nn;

  strcpy(n->name, name);
  n->first      = 0;
  n->has_shadow = FALSE;
  n->cont_num   = 0;  /* assigned in print_container_decls */
  n->shadow_num = 0;  /* assigned in print_container_decls */
  if (!container_list)
    container_list = n;
  else {
    for (nn = container_list; nn->next ; nn = nn->next);
    nn->next = n;
  }
  n->next       = 0;
  n->pos_pred   = 0;
  n->neg_pred   = 0;
  n->pos_must_scan  = FALSE;
  n->neg_must_scan  = FALSE;
  n->pos_index  = 0;
  n->neg_index  = 0;
  field_num     = 1; 
  return n;
}

CONT_PTR
find_container (char *name)
{
  CONT_PTR c;

  foreach_container(c) {
    if (strcmp(c->name, name)==0)
      return c;
  }
  return 0;
}

void
make_shadow (CONT_PTR c)
{
   c->has_shadow = TRUE;
}


/******************* field operations **********************

   new_field(c,n) - registers new field 'n' in container with handle c,
                    returns handle to field element.  initially, 
                    the type of a field is UNKNOWN
   make_type(f,t,s) - declare field (with handle f) to be of type t
                    and size s (if t == STR)
   find_field(c,n) - return handle to field 'n' of container 'c'

*************************************************************/

FIELD_PTR
new_field (CONT_PTR c, char *name)
{
  FIELD_PTR  f = (FIELD_PTR) malloc(sizeof(FIELD));
  FIELD_PTR  ff;

  strcpy(f->name, name);
  f->num = field_num++;
  f->ftype = UNKNOWN;
  if (!c->first)
    c->first = f;
  else {
    for (ff = c->first; ff->next; ff = ff->next);
    ff->next = f;
  }
  f->next = 0;
  return f;
}

FIELD_PTR
find_field (CONT_PTR c, char *name)
{
  FIELD_PTR f;

  foreach_field(f,c) {
    if (strcmp(f->name,name)==0)
      return f;
  }
  return 0;
}

void
make_type (FIELD_PTR f, FIELDTYPE t, int size)
{
  f->ftype = t;
  f->size  = size;
}


/************************** predicate index routines ************

   new_predicate(c,s,p) add predicate p to the list of indexable
       predicates over container c.  (If s == TRUE, then the predicate
       is added to the shadow container).  The predicate lists maintained
       for shadows and containers do not contain duplicate predicates.

*****************************************************************/

static PRED_PTR
no_duplicate_predicates (PRED_PTR p, char *pred)
{
  PRED_PTR pp;

  foreach_predicate(pp, p) {
    if (strcmp(pp->name, pred) == 0)
      return pp;
  }
  return 0;
}

PRED_PTR
new_predicate (PRED_PTR *x, char *pred)
{
  PRED_PTR  p = (PRED_PTR) malloc(sizeof(PRED));
  PRED_PTR  pp;

  strcpy(p->name, pred);
  p->first = 0;
  if ((pp = no_duplicate_predicates(*x, pred)))
    return pp;
  if (!(*x))
    *x = p;
  else {
    for (pp = *x; pp->next ; pp = pp->next) ;
    pp->next = p;
  }
  p->next = 0;
  return p;
}


/************************ print routines for fields *************

   print_structs()  - prints the C structures of the record types
                      of leaps containers.
   print_utility_cursors() - prints the P2 declarations of 
                     dominant (d_), action (a_), and validation (v_)
                     cursors.
   print_initialize() - prints the initialize() routine, which initializes
                     all containers, shadows, and their utility cursors.
   print_container_decls() - prints the P2 declaration of all containers
                     and their shadows.
   print_validation_funcs() - prints all validation functions and the
                     vector of such functions.
   print_insert_data_tuple() - prints a cheezy routine for reading
                     in data tuples ** whose values are in the order
                     in which fields were declared **.

******************************************************************/

typedef char STRG[10];

STRG base_types[] = { "ERROR ", 
                      "int   ", 
                      "float ", 
                      "char  " };

static void
print_field_decl (FIELDTYPE type_index, char *name, int size) 
{
  if (string_optimization && type_index == 3) {
    printf("   int %s;\n", name);
  }
  else {
    printf("   %s  %s", base_types[type_index], name);
    if (type_index == STR)
      printf("[%d];\n", size);
    else
      printf(";\n");
  }
}

void
print_structs (void)
{
  CONT_PTR c;
  FIELD_PTR f;

  printf("\n/************ generated record types ***************/\n\n");
  foreach_container(c) {
    printf("\ntypedef struct {\n");
    foreach_field(f,c) {
      print_field_decl(f->ftype, f->name, f->size);
    }
    print_field_decl(INT, "_ts", 0);
    if (!shadow_container)
      print_field_decl(INT, "_df", 0);
    printf("} %s;\n", c->name);
  }
}

void
print_utility_cursors (void)
{
  CONT_PTR  c;

  printf("\n/************ utility cursor decls ***************/\n\n"); 
  foreach_container(c) {
    printf("typedef cursor <cont_%s> %s_cursor;\n", c->name, c->name);
    if (c->has_shadow)
      printf("typedef cursor <shadow_%s> shadow_%s_cursor;\n", 
             c->name, c->name);
  }
  printf("\n\n");
  foreach_container(c) {
    printf("%s_cursor   a_%s;\n\n", c->name, c->name);
    if (shadow_container && c->has_shadow)
      printf("shadow_%s_cursor   a_shadow_%s;\n\n", c->name, c->name);
  }
  printf("\n\n");
}

void
print_initialize (void)
{
  CONT_PTR c;

  printf("void initialize(void)\n{\n");
  if (string_optimization)
    printf("   init_symbol_table();\n");
  if (malloc_optimization)
    printf("   P2_init_fastmalloc();\n");
  printf("   open_cont(stack);\n");
  printf("   init_curs(top);\n");
  printf("   init_curs(active);\n\n");
  foreach_container(c) {
    printf("   open_cont(cont_%s);\n", c->name);
    printf("   init_curs(a_%s);\n\n",c->name); 
    if (shadow_container && c->has_shadow) {
      printf("   open_cont(shadow_%s);\n", c->name);
      printf("   init_curs(a_shadow_%s);\n\n",c->name); 
    }
  }
  printf("}\n");
}

void
print_finalize (void)
{
  CONT_PTR c;

  printf("void finalize(void)\n{\n");
  printf("   close_cont(stack);\n");
  foreach_container(c) {
    printf("   close_cont(cont_%s);\n", c->name);
    if (shadow_container && c->has_shadow)
      printf("   close_cont(shadow_%s);\n", c->name);
  }
  printf("}\n");
}

static void
print_predindx (PRED_PTR plist, BOOLEAN active)
{
  PRED_PTR p;

  foreach_predicate(p, plist) {
    if (active) {
      predicate_index_number++;
      printf("   lpredindx timestamp is _ts predicate \"%s\" "
             "with activate%d with deactivate%d;\n",
             p->name, predicate_index_number, predicate_index_number);
    }
    else {
      printf("   lpredindx timestamp is _ts predicate \"%s\" with null with null;\n",
             p->name);
    }
  }
}

static void
print_cont_decl (CONT_PTR c, BOOLEAN shadow)
{
  char     *name = c->name;
  PRED_PTR plist = shadow ? c->neg_pred : c->pos_pred;

  if (shadow_container) {
    printf("container < %s > stored_as leaps_x with {\n", name); 
    if (plist && predicate_indices) 
      print_predindx(plist, active_rule_optimization && !shadow);
    
    printf("   llist timestamp is _ts;\n");
    
    if (persistence)
      printf("   persistent file is \"/usr/tmp/rl-file\" with size 5000000;\n");

    if (timestamp_layer)
      printf("   vtimestamp field is _ts counter is global_counter;\n");

    if (shadow) 
      printf("}  shadow_%s;\n\n", name);
    else
      printf("}  cont_%s;\n\n", name);
  }
  else {
    printf("container < %s > stored_as leaps_x with {\n", name);
    if (c->pos_pred && predicate_indices) 
      print_predindx(c->pos_pred, active_rule_optimization);
    if (c->neg_pred && predicate_indices) 
      print_predindx(c->neg_pred, FALSE);

    printf("   lpredindx timestamp is _ts predicate \"(!$._df)\" is null with null;\n");
    printf("   lpredindx timestamp is _ts predicate \"($._df)\"  is null with null;\n");
    
    if (timestamp_layer)
      printf("   vtimestamp field is _ts counter is global_counter;\n");

    printf("}  cont_%s;\n\n", name);
  }
}

void
print_container_decls (void)
{
  CONT_PTR c;
  int      i;
  char     *mem_layer;

  if (persistence)
    mem_layer = "persistent";
  else if (malloc_optimization)
    mem_layer = "transient_fast";
  else
    mem_layer = "transient";

  add_predicate_indices();
  printf("\n/************ generated container declarations ***************/\n\n");

  printf("typex {\n   leaps_x = top2ds_qualify[\n      ");
  if (!shadow_container || predicate_indices)
    printf("lpredindx[");
  if (shadow_container) 
    printf("llist[");
  if (timestamp_layer)
    printf("vtimestamp[");
/*
  if (garbage_collection && !persistence && !malloc_optimization)
    printf("free[delflag[");
*/
  printf("\n      ");
  printf("delflag[malloc[%s]]]", mem_layer);
/*
  if (garbage_collection && !persistence && !malloc_optimization)
    printf("]]");
*/
  if (timestamp_layer)
    printf("]");
  if (shadow_container)
    printf("]");
  if (!shadow_container || predicate_indices)
    printf("]");
  printf(";\n}\n\n");

  predicate_index_number = 0;

  foreach_container(c) { 
    print_cont_decl(c, FALSE);
    if (shadow_container && c->has_shadow)
      print_cont_decl(c, TRUE);
  }

  printf("/************** generated container numbers *******************/\n\n");
  i = 1;
  foreach_container(c) { 
    c->cont_num = i++;
    printf("#define %s_num  %d\n", c->name, c->cont_num);
    if (shadow_container && c->has_shadow) {
      c->shadow_num = i++;
      printf("#define shadow_%s_num  %d\n", c->name, c->shadow_num);
    }
  }
}

static void
print_valid_func (char *name, BOOLEAN shadow)
{
  char tmp[10];

  if (shadow)
    strcpy(tmp, "shadow_");
  else
    strcpy(tmp, "");

  printf("BOOLEAN valid_%s%s(void *o) {\n", tmp, name);
  printf("   pos(a_%s%s, o);\n", tmp, name);
  if (shadow_container)
    printf("   return(!deleted(a_%s%s));\n", tmp, name);
  else
    printf("   return(a_%s._df);\n", name);
  printf("}\n\n");
}


void
print_validation_funcs (void)
{
  CONT_PTR c;

  printf("\n\n/************* generated valid functions **********************/\n\n");
  foreach_container(c) {
    print_valid_func(c->name, FALSE);
    if (c->has_shadow)
      print_valid_func(c->name, TRUE);
  }

  printf("\n\n");
  printf("BOOL_FUNC_PTR valid_vect[ ] = { 0,");
  foreach_container(c) {
    printf(" valid_%s,", c->name);
    if (c->has_shadow)
      printf(" valid_shadow_%s,", c->name);
  }
  printf(" 0 };\n");
}


void
print_insert_data_tuple (void)
{
  CONT_PTR  c;
  FIELD_PTR f;
  int       max_str_fields;
  int       i;
  int       fieldno;

  /* determine maximum number of string fields per container record
     type - this is needed for string_optimization */

  max_str_fields = 0;
  foreach_container(c) {
    foreach_field(f,c) {
      if (f->ftype == STR)
        max_str_fields++;
    }
  }

  printf("void insert_data_tuple (void)\n{\n");
  printf("char      cont_name[TOKEN_LEN];\n");
  printf("char      skip[TOKEN_LEN];\n");
  printf("FIELDNAME fieldname[TOKEN_LEN];\n");
  printf("char      brace[TOKEN_LEN];\n");
  if (string_optimization
      && max_str_fields > 0 /* ANSI C forbids zero-size arrays */)
    printf("string words[%d];\n\n", max_str_fields);
  printf("   sscanf (inp_line, \"(make %s\", cont_name);\n", "%s");
  foreach_container(c) {
    printf("   if (strcmp(cont_name,\"%s\") == 0) {\n",c->name);
    printf("      %s r;\n", c->name);
    printf("      sscanf(inp_line, \"%s ","%s %s");
    foreach_field(f,c) {
      switch (f->ftype) {
      case INT:
        printf("%s ", "%s %d"); 
        break;
      case REAL:
        printf("%s ", "%s %f"); 
        break;
      case STR:
        printf("%s ", "%s %s"); 
        break;
      case UNKNOWN:
      default:
        perror("unknown field type");
      }
    }
    printf("%s\", skip, cont_name", "%s");
    i = 0;
    fieldno = 0;
    foreach_field(f,c) {
      if (f->ftype == STR) {
        if (string_optimization) 
          printf(", fieldname[%d], words[%d]",fieldno++, i++);
        else 
          printf(", fieldname[%d], r.%s",fieldno++,f->name);
      }
      else
        printf(", fieldname[%d], &r.%s",fieldno++,f->name);
    }
    printf(", brace);\n");

    fieldno = 0;
    foreach_field(f,c) {
       printf("      if (strcmp(fieldname[%d], \"^%s\") !=0) input_format_error();\n",
              fieldno++, f->name);
    }
    printf("      if (brace[0] != R_PAREN) input_format_error();\n");

    i = 0;
    if (string_optimization) {
      foreach_field(f,c) {
        if (f->ftype == STR) {
          printf("      r.%s = add_unique_symbol(words[%d]);\n",
                 f->name, i++);
        }
      }
    }

    if (!timestamp_layer)
      printf("      r._ts = global_counter++;\n");

    if (inline_ops)
       printf("      insert(a_%s,r);\n", c->name);
    else
       printf("      insert_%s(&r);\n", c->name);
    printf("      push_wl(a_%s.obj, a_%s._ts, %s_num);\n",
           c->name, c->name, c->name);
    printf("      return;\n");
    printf("   }\n");
  }
  printf("   printf(\"*** unrecognizable make - no action taken***\\n\");\n");
  printf("}\n\n");
}

