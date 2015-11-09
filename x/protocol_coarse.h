/* $Id: protocol_coarse.h,v 45.0 1997/09/19 05:46:45 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct protocol_coarse_annote {
  struct protocol_coarse_annote *next;
  int cont_id;
  char *cont_name;
};
