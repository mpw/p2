/* $Id: llist.h,v 45.0 1997/09/19 05:46:30 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

#include "type.h" /* MAX_PRED_LEN */
#include "util.h" /* MAX_IDENT_LEN */

struct llist_annote {
  struct llist_annote *next;
  int cont_id;
  char   *cont_name;

  char ts_field[MAX_IDENT_LEN]; /* name of timestamp field */

  /* Added by xform */

  OP_TAB    *typeptr;           /* type_table entry for this type */
  VOID_FUNC bi;                 /* bounds impact function */
  char      hint[20];           /* nonempty string if reset 
                                   optimization to be used */
};


struct llist_cstate {
  int id;
  int layerno;
  struct bintree_cstate *next;

  /* New fields. */

  BOUNDS  b;                     /* bounds of predicate */
  char    reduced[MAX_PRED_LEN]; /* simplified predicate applied in query() */
  int     which_case;            /* which case to apply */
};

