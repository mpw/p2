/* $Id: bintree.h,v 45.0 1997/09/19 05:46:17 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct bintree_annote {
  struct bintree_annote *next;
  int cont_id;
  char   *cont_name;
  char                  ofield[MAX_IDENT_LEN]; /* name of key field */

  /* Added by xform. */

  VOID_FUNC             bi;               /* bounds impact function */
  OP_TAB                *typeptr;         /* type_table entry for this type */
  char                  *ofield_type;     /* type of key field */
};


struct bintree_cstate {
  int id;
  int layerno;
  struct bintree_cstate *next;

  /* New fields. */

  BOUNDS  b;  /* bounds of predicate */
};
