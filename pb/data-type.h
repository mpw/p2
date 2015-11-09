/* $Id: data-type.h,v 45.0 1997/09/19 05:45:46 jthomas Exp $ */
/* Copyright (C) 1995, The University of Texas at Austin. */

#ifndef INCLUDE_DATA_TYPE_H
#define INCLUDE_DATA_TYPE_H

/* Data type declarations. */
/* Query parsing and processing declarations. */

#include "type.h"  /* IDENT */
#include "util.h"  /* BOOLEAN */
#include "xform.h" /* TE */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define NUM_OP   10              /* number of operations per type */

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Q: If these are local, why aren't they in data-type.c??? (JAT) */
/* A: They aren't local??? (JAT) */

typedef struct {
   BOOLEAN  bottom;              /* -inf/FALSE for lower bound */
   BOOLEAN  top;                 /* +inf/FALSE for upper bound */
   BOOLEAN  inc_lower;           /* inclusive lower bound */
   BOOLEAN  inc_upper;           /* inclusive upper bound */
   BOOLEAN  xlower;              /* expression defines lower bounds */
   BOOLEAN  xupper;              /* expression defines upper bounds */
   char     lower[100];          /* lower bound */
   char     upper[100];          /* upper bound */
} BOUNDS;

/* Rename these to COMPFUNC_xxx. (JAT) */
/* Symbols beginning with a single underscore are reserved by UNIX.
   Symbols beginning with two underscores are reserved by P2 for
   symbols we want to hide from the P2 user. (JAT) */

typedef enum { _EQ, _NEQ, _GT, _GE, _LT, _LE } COMPFUNC;

typedef char OPNAME[100];        /* name of operation */
typedef char CONVERT[100];       /* convert string */

typedef struct {
   OPNAME  name;
   CONVERT cs;
} OP;

typedef struct {
   char       typename[10];
   int        size;              /* length of data item in bytes */
   VOID_FUNC  bounds_impact;     /* bounds impact function */
   BOOL_FUNC  is_literal;        /* test for literal/constant */
   SHORT_FUNC hashcmp;           /* hash comparison function */
   char       hashcmp_name[100]; /* name of hashcmp func.  Never used??? (JAT) */
   UNSIGNED_FUNC hash;
   char       hash_name[100];    /* name of hash func.  Never used??? (JAT) */
   OP         op[NUM_OP];        /* index by COMPFUNC values */
} OP_TAB;

/*****************************************************************************/
/*                  External declarations and function prototypes.           */
/*****************************************************************************/

extern   OP_TAB type_tab[];

char     *bind_predicate(const TE *te, char *cursor, char *obj_type,
                         char *predicate);
char     *bind_predicate1(const TE *te, char *cursor, IDENT *ident,
                          char *predicate);
void     bounds_impact_int(BOUNDS *b, const char *relation, char *value);
void     bounds_impact_str(BOUNDS *b, const char *relation, char *value);
void     define_bounds(const TE *te, BOUNDS *b, char *c, char *p, char *f,
                       VOID_FUNC bi);
void     field_update(const char *format, const char *element, char *res);
OP_TAB   *find_data_type(IDENT *element, char *fieldname);
unsigned int_hash(int i, int size);
unsigned str_hash(const char *str, int size);
void     hashcmp_expand_predicate(char *predicate, char *fld, int ln,
           BOOL_FUNC is_lit, SHORT_FUNC hash, char *op);
short    str_hashcmp(const char *str);
void     init_bounds(BOUNDS *b);
int      intcmp(int a, int b);
BOOLEAN  is_literal_int(const char *str);
BOOLEAN  is_literal_str(const char *str);
void     nest(char *p1);
void     next_clause(char **p, char *clause,
                     char *field, char *relation, char *value);
void     post_and(char *p1, const char *p2);
void     post_or(char *p1, const char *p2);
void     pre_and(char *p1, const char *p2);
void     pre_or(char *p1, const char *p2);
void     replace_cursor_refs(const TE *te, char *cursor,
                             char *expanded_predicate);
void     separate_predicate(char *p, char *fld, BOOLEAN *single, 
           char *ipred, char *rpred);
void     simplify_predicate(char *p, BOUNDS *b, char *f, 
           BOOLEAN adv, char *result);
void     split_predicate(IDENT *prim, char *pred, char *pp, 
           char *sp, char *rp);
int      use_layer(const TE *te, BOUNDS *b, char *c, char *p, char *f,
                   VOID_FUNC bi);

#endif /* INCLUDE_DATA_TYPE_H */
