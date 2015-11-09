/* $Id: predindx.h,v 45.0 1997/09/19 05:46:44 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct predindx_annote {
  struct predindx_annote *next;
  int cont_id;
  char   *cont_name;

  char ofield[MAX_IDENT_LEN]; /* name of key field */

  /* Added by xform. */

  char pred[100]; /* predicate to index */
};

struct predindx_cstate {
  int id;
  int layerno;
  struct predindx_cstate *next;

  /* New fields. */

  int within; /* true if predindx is within the cursor state predicate */
  char npred[100]; /* new predicate value */
};
