/* $Id: cursor_structure.h,v 45.0 1997/09/19 05:46:19 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct cursor_structure_annote {
  struct cursor_structure_annote *next;
  int cont_id;
  char *cont_name;

  char structure[MAX_IDENT_LEN];
};

