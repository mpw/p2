/* $Id: delflag_forarray.h,v 45.0 1997/09/19 05:46:20 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct delflag_forarray_annote {
  struct delflag_forarray_annote *next;
  int cont_id;
  char   *cont_name;

  char deltype[20];       /* either "many" or "few" */
};
