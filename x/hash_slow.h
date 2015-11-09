/* $Id: hash_slow.h,v 45.0 1997/09/19 05:46:25 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct hash_slow_annote {
  struct hash_slow_annote *next;
  int cont_id;
  char   *cont_name;

  char   ofield[MAX_IDENT_LEN];         /* name of key field */
  char   size[MAX_IDENT_LEN];           /* number of buckets */
  char   hash_function[MAX_IDENT_LEN];  /* name of hash function */

  /* Added by ddlhint */

  VOID_FUNC               bi;            /* bounds impact function */
  OP_TAB                  *typeptr;      /* type_table entry for this type */
  char                    *ofield_type;  /* name of key field's type */
};
