/* $Id: malloc_multi.h,v 45.0 1997/09/19 05:46:35 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct malloc_multi_annote {
  struct malloc_multi_annote *next;
  int cont_id;
  char   *cont_name;

  char size[20];
};
