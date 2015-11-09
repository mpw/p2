/* $Id: hashcmp.h,v 45.0 1997/09/19 05:46:26 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct hashcmp_annote {
  struct hashcmp_annote *next;             /* pointer to next annotation */
  int    cont_id;
  char   *cont_name;

  char                  ofield[20];        /* name of key field */

  /* Added by xform */

  char                  hfield[20];        /* name of hash field */
  SHORT_FUNC            hashcmp;           /* hash comparison function */
  char                  hashcmp_name[100]; /* name of hashcmp function */
  BOOL_FUNC             is_literal;        /* is literal function */
};
