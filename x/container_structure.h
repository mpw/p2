/* $Id: container_structure.h,v 45.0 1997/09/19 05:46:18 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct container_structure_annote {
  struct container_structure_annote *next;
  int cont_id;
  char *cont_name;

  char structure[MAX_IDENT_LEN];
};

