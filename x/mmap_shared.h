/* $Id: mmap_shared.h,v 45.0 1997/09/19 05:46:38 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct mmap_shared_annote {
  struct mmap_shared_annote *next;
  int    cont_id;
  char   *cont_name;

  char   filename[MAX_IDENT_LEN];  
  char   size[MAX_IDENT_LEN];
  char   f[10];
};
