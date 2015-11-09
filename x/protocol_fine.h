/* $Id: protocol_fine.h,v 45.0 1997/09/19 05:46:46 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct protocol_fine_annote {
  struct protocol_fine_annote *next;
  int cont_id;
  char *cont_name;
};
