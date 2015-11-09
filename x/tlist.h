/* $Id: tlist.h,v 45.0 1997/09/19 05:46:52 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct tlist_annote {
  struct tlist_annote *next;
  int cont_id;
  char   *cont_name;

  char ts_field[MAX_IDENT_LEN]; /* name of timestamp field */

  /* Added by xform */

  OP_TAB    *typeptr;           /* type_table entry for this type */
  VOID_FUNC bi;                 /* bounds impact function */
};
