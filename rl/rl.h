/* $Id: rl.h,v 45.0 1997/09/19 05:46:10 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#if USE_DB_MALLOC_PACKAGE

/* DB malloc */
#include "malloc.h"

#else

/* UNIX malloc */
#include <malloc.h>

#endif /* USE_DB_MALLOC_PACKAGE */

#include <stdio.h>
#include <stdlib.h>

#define CONSTLEN   50           /* length of constant */
#define MAXCHILD   3            /* maximum number of children per node */
#define NAMELEN    40           /* length of an identifier name */
#define PREDLEN    200          /* length of a predicate index */
#define RELLEN     5            /* length of a rel-op */

#define foreach_rule(r)      for (r = rule_list; r; r = r->next)
#define foreach_element(e,r) for (e = r->first; e; e = e->next)
#define foreach_clause(c,e)  for (c = e->first; c; c = c->next)
#define foreach_disj(d,c)    for (d = c->first; d; d = d->next)
#define foreach_action(a,r)  for (a = r->action; a; a = a->next)
#define foreach_arg(g,a)     for (g = a->first; g; g = g->next)

#define foreach_container(c) for (c = container_list; c; c = c->next)
#define foreach_field(f,c)   for (f = c->first; f; f = f->next)
#define foreach_pair(p)      for (p = bind_list; p; p = p->next)

#define foreach_predicate(p,first) \
                             for (p = first; p; p = p->next)

#define is_numeric_cons(n) (n >= '0' && n <= '9')

/* Boolean. */
/* Define FALSE, TRUE, and BOOLEAN if not already defined (eg by AIX) */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef BOOLEAN
#define BOOLEAN int
#endif

#define MIN_STRING_SIZE 4       /* Minimum string_size */
                                /* (as computed by max_string_length). */
                                /* Must be large enough to accommidate the */
                                /* largest constant we put into the */
                                /* symbol_table (e.g. strlen(nil)+1) (JAT) */

typedef enum { UNKNOWN, INT, REAL, STR } FIELDTYPE;
typedef enum { CONS, VAR, DIS } VALTYPE;
typedef enum { CONS_NODE, VAR_NODE, CRLF_NODE, COMPUTE_NODE, 
               OPR_NODE, UFUNC_NODE } NODETYPE;
typedef enum { UPD, REM, MAK, END, OUT } ACTTYPE;

typedef char NAME[NAMELEN];
typedef char EXPR[PREDLEN];

typedef struct field {
   NAME         name;           /* container name */
   int          num;            /* field number */
   FIELDTYPE    ftype;          /* field type */
   int          size;           /* array size - if field is char array */
   struct field *next;          /* next field */
} FIELD, *FIELD_PTR;

typedef struct pred {
   char        name[PREDLEN];   /* predicate to index */
   struct pred *next;           /* next predicate to index */
   struct pred *first;          /* for active rule list */
} PRED, *PRED_PTR;

typedef struct cont {
   NAME        name;            /* container name */
   FIELD_PTR   first;           /* first field of container */
   BOOLEAN     has_shadow;      /* does container have a shadow? */
   struct cont *next;           /* next container */
   PRED_PTR    pos_pred;        /* predicates to index on positive cont */
   PRED_PTR    neg_pred;        /* predicates to index on negative cont */
   BOOLEAN     pos_must_scan;   /* are we forced to scan cont by some 
                                     rule? */
   BOOLEAN     neg_must_scan;   /* are we forced to scan shadow by some
                                     rule? */
   PRED_PTR    pos_index;       /* list of fields to index on pos cont */
   PRED_PTR    neg_index;       /* list of fields to index on neg cont */
   int         cont_num;        /* container number */
   int         shadow_num;      /* shadow number */
} CONT, *CONT_PTR;

typedef char TEXT[200];

typedef struct strlst {
   TEXT         name;
   struct strlst *next;         /* next string */
} STRLIST, *STRLIST_PTR;
   
typedef struct dsj {
   char        name[CONSTLEN];  /* name of constant */
   struct dsj  *next;           /* next disjunct */
} DISJ, *DISJ_PTR;

typedef struct clause {
   NAME        name;            /* name of field */
   char        relop[RELLEN];   /* comparison relation */
   VALTYPE     v;               /* does clause reference variable? */
   char        cons[CONSTLEN];  /* v==VAR { name of variable } 
                                   v==CONS { name of constant } 
                                   v==DIS { not defined }*/
   DISJ_PTR    first;           /* first in a list of constants */
   struct clause *next;         /* next clause in condition element */
} CLAUSE, *CLAUSE_PTR;


typedef struct cele {
   NAME        name;            /* name of container */
   CONT_PTR    cont;            /* pointer to container definition */
   BOOLEAN     neg;             /* is condition element negative? */
   CLAUSE_PTR  first;           /* first clause of condition element;
                                   if null, predicate is empty container*/
   EXPR        negtest;         /* string containing predicate of 
                                   negated CE test */
   struct cele *next;           /* next condition element of rule */
}  ELEMENT, *ELEMENT_PTR;


typedef struct node {
   char        name[CONSTLEN];  /* text value of node */
   NODETYPE    nodetype;        /* type of node */
   struct node *down[MAXCHILD]; /* children of node */
} NODE, *NODE_PTR;

typedef struct arg {
   NAME        name;            /* name of argument */
   NODE_PTR    node;            /* pointer to node */
   struct arg  *next;           /* next argument */
} ARG, *ARG_PTR;

typedef struct act {
   ACTTYPE     name;            /* action to be taken */
   char        what[NAMELEN];   /* typically, container name */
   ARG_PTR     first;           /* arguments of action */
   struct act  *next;           /* next action of rule */
} ACTION, *ACTION_PTR;

typedef struct rul {
   NAME        name;            /* name of rule */
   ELEMENT_PTR first;           /* first condition element of rule */
   int         no_elements;     /* number of condition elements */
   int         ruleno;          /* rule number */
   struct rul  *next;           /* next rule */
   ACTION_PTR  action;          /* list of rule actions */
}  RULE, *RULE_PTR;

typedef struct pair {
   NAME     var;           /* name of variable */
   NAME     expr;          /* expression of variable */
   NAME     cont;          /* name of container */
   BOOLEAN  used;          /* is this var used in negated ces? */
   struct pair *next;      /* next pair */
} PAIR, *PAIR_PTR;


/* externals from container.c */

extern CONT_PTR  container_list;
extern CONT_PTR  new_container(char *name);
extern CONT_PTR  find_container(char *name);
extern FIELD_PTR new_field(CONT_PTR c, char *name);
extern FIELD_PTR find_field(CONT_PTR c, char *name);
extern void      make_shadow(CONT_PTR c);
extern void      make_type(FIELD_PTR f, FIELDTYPE t, int size);
extern PRED_PTR  new_predicate(PRED_PTR *x, char *pred);
extern void      print_structs(void);
extern void      print_utility_cursors(void);
extern void      print_container_decls (void);
extern void      print_validation_funcs (void);

/* externals from rule.c */

extern PRED_PTR    include_list;
extern RULE_PTR    rule_list;
extern RULE_PTR    new_rule (char *name);
extern ARG_PTR     new_arg(ACTION_PTR a, char *name, NODE_PTR arg);
extern ACTION_PTR  new_action(RULE_PTR r, ACTTYPE action, char *what);
extern NODE_PTR    new_node(char *value, NODETYPE t, 
                            NODE_PTR p0, NODE_PTR p1, NODE_PTR p2);
extern ELEMENT_PTR new_element(RULE_PTR r, char *name, BOOLEAN neg);
extern CLAUSE_PTR  new_clause(ELEMENT_PTR e, char *fld, char *relop,
                              VALTYPE v, char *cons);
extern DISJ_PTR    new_disj(CLAUSE_PTR c, char *cons);
extern void        init_bind (void);
extern void        bind(char *v, char *e, char *c);
extern PAIR_PTR    find_bind(char *v);
extern void        print_var_assignments(RULE_PTR r, char *var);
extern int         make_positive_query(RULE_PTR r, char *query , 
                                        ELEMENT_PTR ele);
extern void        print_negated_variables(RULE_PTR r);
extern void        print_shadow_cursors (RULE_PTR r);
extern void        print_cursor_typedefs(void);
extern void        print_rule_head(RULE_PTR r);
extern void        dump_query_list(void);
extern void        print_banner(char *name);
extern void        print_includes(void);
extern void        print_forward_refs(void);
extern void        sprintnode(NODE_PTR n);
extern void        printnode(NODE_PTR n , BOOLEAN ops5format);
extern void        dump_rule_list(void);
extern void        print_negated_variables(RULE_PTR r);

void add_predicate_indices(void);

/* externals from main.c */

extern FILE *yyin;
extern int  yydebug;
extern int yyerror(char *s);

extern BOOLEAN active_rule_optimization;
extern BOOLEAN string_optimization;
extern BOOLEAN leaps_debugging;
extern BOOLEAN persistence;
extern BOOLEAN garbage_collection;
extern BOOLEAN shadow_optimization;
extern BOOLEAN inline_ops;
extern BOOLEAN malloc_optimization;
extern BOOLEAN negation_optimization;
extern BOOLEAN predicate_indices;
extern BOOLEAN standard_output;
extern BOOLEAN timestamp_layer;
extern BOOLEAN shadow_container;
extern BOOLEAN attribute_indices;

/* externals from leaps.c */

extern BOOLEAN watch;

/* externals from rl-gram.y */

extern BOOLEAN  error_status;
extern int      line_number;

/* externals from instance.c */

extern void print_array (void);
extern void order_rules(void);
extern ELEMENT_PTR what_container (RULE_PTR r, int count);

/* unsorted externals */

extern int  close (int fd);
extern int  yyparse (void);
extern void print_options(void);
extern void print_defines(void);
extern void print_valids(void);
extern void add_attribute_indices(void);
extern void print_attribute_indices(void);
extern void collect_string_constants(void);
extern void generate_symbol_table(void);
extern void print_ext_includes(void);
extern void print_active_rules(void);
extern void print_finalize(void);
extern void print_initialize(void);
extern void print_ins_del_ops(void);
extern void print_insert_data_tuple(void);
extern void print_instances(void);
extern void print_list_headers(void);
extern void print_rulefires(void);
extern int  isatty(int);
extern int  yylex(void);
extern PRED_PTR symbol_table;

