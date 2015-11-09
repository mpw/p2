/* $Id: tpredindx.h,v 45.0 1997/09/19 05:46:54 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct tpredindx_annote {
   struct tpredindx_annote *next;
   int cont_id;
  char   *cont_name;

   char      ts_field[MAX_IDENT_LEN]; /* name of timestamp field */
   char      pred[MAX_IDENT_LEN];     /* name of predicate */
   char      e_proc[MAX_IDENT_LEN];   /* name of empty_procedure */
   char      n_proc[MAX_IDENT_LEN];   /* name of non-empty procedure */

   /* Added by xform */

   OP_TAB    *typeptr;                /* type_table entry for this type */
   VOID_FUNC bi;                      /* bounds impact function */
} ;


struct tpredindx_cstate {
    int id;
    struct tpredindx_cstate *next;

    /* new fields */
    int within; /* true if predindx is within the cursor state predicate */
    char npred[100]; /* new predicate value */
};
