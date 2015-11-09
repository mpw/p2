/* $Id: lpredindx.h,v 45.0 1997/09/19 05:46:34 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct lpredindx_annote {
  struct lpredindx_annote *next;
  int cont_id;
  char   *cont_name;

  /* Filled in by ddlhint */
  char       ts_field[MAX_IDENT_LEN]; /* name of timestamp field */
  char       xpred[MAX_PRED_LEN];     /* predicate to index */
  char       e_proc[MAX_IDENT_LEN];   /* name of empty procedure */
  char       n_proc[MAX_IDENT_LEN];   /* name of nonempty procedure */
  char       hint[20];                /* if nonblank, use reset
                                              optimization */
  /* Added by xform */
  OP_TAB     *typeptr;                /* type_table entry for this type */
  VOID_FUNC  bi;                      /* bounds impact function */
};


struct lpredindx_cstate {
  int id;
  int layerno;
  struct lpredindx_cstate *next;

  /* New fields. */

  BOUNDS  b;                               /* bounds of predicate */
  char    reduced_predicate[MAX_PRED_LEN]; /* cursor predicate with xpred
                                              removed */
  char    reduced[MAX_PRED_LEN];           /* reduced_predicate with timestamp
                                              qualification removed */
  int     layer_can_be_used;      /* = MAX_QOPT_COST if layer can't be
                                     used for query processing.
                                     = -n; if layer can be used for
                                     query processing.  n == the number
                                     of clauses in the indexed predicate.
                                     The greater the number of clauses
                                     in the predicate, the more attractive
                                     this layer becomes. */
  int     which_case;             /* which case for retrieval */
};

