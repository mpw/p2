/* $Id: hash_array_overwrite.h,v 45.0 1997/09/19 05:46:25 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct hash_array_overwrite_annote {
  struct hash_array_overwrite_annote *next;
  int    cont_id;
  char   *cont_name;

  char   ofield[MAX_IDENT_LEN];            /* name of key field */
  char   size[MAX_IDENT_LEN];              /* number of buckets */
  char   hash_function[MAX_IDENT_LEN];     /* name of hash function */
  char   size_minus_one[20];               /* Maximum legal array index. */

  /* Added by ddlhint. */

  VOID_FUNC            bi;                 /* bounds impact function */
  OP_TAB               *typeptr;           /* type_table entry for this type */
  char                 *ofield_type;       /* name of key field's type */
};
