/* $Id: arg.h,v 45.0 1997/09/19 05:45:42 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* Arguments used for communication between pb and xp */

#ifndef INCLUDE_ARG_H
#define INCLUDE_ARG_H

#include <stdio.h> /* NULL */

#include "lex.h"   /* MAX_IDENT_LEN */
#include "type.h"  /* ARG_STR_LEN */

/************************************************************************/
/*              Typedefs                                                */
/************************************************************************/

/* Cursor. */

typedef struct {
  char expr[ARG_STR_LEN];            /* text of cursor expression */
  char type[MAX_IDENT_LEN];          /* struct name of cursor */
  char cont[ARG_STR_LEN];            /* container expression for cursor */
  char cont_type[MAX_IDENT_LEN];     /* struct name of container type */
  char schema[MAX_IDENT_LEN];        /* name of schema */
  char orig_type[MAX_IDENT_LEN];     /* struct name of original object type */
  char obj_type[MAX_IDENT_LEN];      /* struct name of xformed object type */
  char predicate[ARG_STR_LEN];       /* predicate of cursor */
  char orderby_field[MAX_IDENT_LEN]; /* orderby field (if any). */
       
  BOOLEAN proceduralize_ref; /* TRUE iff ref() operations should be
                                proceduralized.  Currently TRUE only for
                                typex containing the substring "part". */
  int  orderby_direction;    /* orderby direction specified by user.
                                 -1 decreasing,
                                  0 none specified,
                                 +1 increasing */
  int  retrieval_direction;  /* retrieval direction
                                provided by retrieval layer
                                 -1 decreasing,
                                  0 none provided,
                                 +1 increasing */
  int  cost;                 /* used for query optimization */
  int  layer;                /* id of layer to process query */
  int  cursor_id;            /* Zero is error, negative special value */
  int  container_id;         /* Zero is error, negative special value */
  int  funbody;              /* op number of operation being expanded,
                                  MACRO_EXPAND_FUNBODY forces deep macro expand
                                  FUNCALL_EXPAND_FUNBODY forces funcall expand
                                  op for normal mixed macro/funcall */
  OP_LIST *op_list;

/* Link additions */

  BOOLEAN bound;                   /* is cursor bound? */
} CURS_ARG;

/* Container. */

typedef struct {
  char expr[ARG_STR_LEN];          /* text of container expression */
  char type[MAX_IDENT_LEN];        /* struct name of container */
  char orig_type[MAX_IDENT_LEN];   /* struct name of original object type */
  char obj_type[MAX_IDENT_LEN];    /* struct name of xformed object type */
  int  container_id;               /* state id for container */
  int  funbody;
  char schema[MAX_IDENT_LEN];      /* name of schema */
  OP_LIST *op_list;
} CONT_ARG;

/* Schema. */

typedef struct {
  char expr[ARG_STR_LEN];          /* text of record expression */
  OP_LIST *op_list;
} SCH_ARG;

/* Record. */

typedef struct {
  char expr[ARG_STR_LEN];          /* text of record expression */
} REC_ARG;

/* Link state. */

typedef struct {
  char linkpredicate[ARG_STR_LEN]; /* link predicate string */
  int  linklayer;                  /* link layer number */
  int  linkcost;                   /* cost estimate of link traversal */
  char linkname[MAX_IDENT_LEN];    /* name of link to traverse */
  CARD pcard;                      /* # of parent records per child */
  CARD ccard;                      /* # of child records per parent */
  char cresidual[ARG_STR_LEN];     /* child file residual predicate */
  char presidual[ARG_STR_LEN];     /* parent file residual predicate */
  char apply[ARG_STR_LEN];         /* join predicate to apply */
  void *linkannote;                /* pointer to link annotation */
  BOOLEAN special_foreachl;        /* layer-specific foreachl expansion */
} LST_ARG;

/* VPTR_STR is defined in paces/p2.h (BJG) */
/* Also defined in common/ctype.h (JAT) */
/* Why does this need to be defined in three different places??? (JAT) */

#define VPTR_STR "vptr"

/* For arguments that are cast to void pointers. (BJG) */

typedef struct { 
  char expr[ARG_STR_LEN];
  char *type;                         /* Always equal to VPTR_STR (JAT) */
} VPTR_ARG;

#endif /* INCLUDE_ARG_H */
