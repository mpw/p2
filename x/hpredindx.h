/* $Id: hpredindx.h,v 45.0 1997/09/19 05:46:27 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct hpredindx_annote {
  struct hpredindx_annote *next;
  int cont_id;
  char   *cont_name;

  /* Filled in by ddlhint */
  char       ts_field[MAX_IDENT_LEN];  /* name of timestamp field */
  char       xpred[MAX_PRED_LEN];      /* predicate to index */
  char       e_proc[20];               /* name of empty procedure */
  char       n_proc[20];               /* name of nonempty procedure */
  char       hint[20];                 /* if nonblank, use reset
                                              optimization */

  char       hash_field[MAX_IDENT_LEN]; /* hash field */
  char       size[10];                  /* # of buckets */

  /* Added by xform */
  OP_TAB     *ts_typeptr;               /* type_table entry for _ts */
  VOID_FUNC  ts_bi;                     /* bounds impact function */
  OP_TAB     *hash_typeptr;             /* same for hash field  */
  VOID_FUNC  hash_bi;         
};


struct hpredindx_cstate {
  int id;
  int layerno;
  struct hpredindx_cstate *next;

  /* New fields. */

  BOUNDS  b;                               /* bounds of predicate */
  char    reduced_predicate[MAX_PRED_LEN]; /* cursor predicate with xpred
                                              removed */
  char    reduced[MAX_PRED_LEN];           /* reduced_predicate with timestamp
                                              qulification removed */
  int     layer_can_be_used;      /* = MAX_QOPT_COST if layer can't be
                                     used for query processing.
                                     = -n; if layer can be used for
                                     query processing.  n == the number
                                     of clauses in the indexed predicate.
                                     The greater the number of clauses
                                     in the predicate, the more attractive
                                     this layer becomes. */
  int     which_case;             /* which case for retrieval */
  char    hash_pred[MAX_PRED_LEN];/* predicate value to hash */
};

