/* $Id: odlist.h,v 45.0 1997/09/19 05:46:40 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct odlist_annote {
  struct odlist_annote  *next;
  int cont_id;
  char   *cont_name;

  char ofield[MAX_IDENT_LEN];             /* name of key field */

  /* Added by xform. (DSB) */
  /* These are here, rather than a curs_state structure, because the
     curs_state structure (cs) is not available in xform. (JAT) */

  VOID_FUNC             bi;               /* bounds impact function */
  OP_TAB                *typeptr;         /* type_table entry for this type */
  char                  *ofield_type;     /* name of key field's type */
};

