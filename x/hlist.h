/* $Id: hlist.h,v 45.0 1997/09/19 05:46:27 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#include "type.h" /* MAX_PRED_LEN */
#include "util.h" /* MAX_IDENT_LEN */

struct hlist_annote {
  struct llist_annote *next;
  int    cont_id;
  char   *cont_name;

  char                ts_field[MAX_IDENT_LEN];   /* timestamp field */
  char                hash_field[MAX_IDENT_LEN]; /* hash field */
  char                size[10];                  /* # of buckets */

  /** added by xform **/
  OP_TAB              *ts_typeptr;    /* type_table entry for this type */
  VOID_FUNC           ts_bi;          /* bounds impact function */
  char                hint[20];       /* nonempty string if reset 
                                          optimization to be used */
  OP_TAB              *hash_typeptr;  /* type_table entry for hash key */
  VOID_FUNC           hash_bi;        /* hash key's bounds impact func */
};


struct hlist_cstate {
  int id;
  int layerno;
  struct bintree_cstate *next;

  /* New fields. */

  BOUNDS  b;                       /* bounds of predicate */
  char    reduced[MAX_PRED_LEN];   /* simplified pred applied in query() */
  int     which_case;              /* which case to apply */
  char    hash_pred[MAX_PRED_LEN]; /* predicate value to hash */
};

