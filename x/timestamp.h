/* $Id: timestamp.h,v 45.0 1997/09/19 05:46:52 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct timestamp_annote { 
  struct timestamp_annote *next;
  int cont_id;
  char   *cont_name;

  char countername[MAX_IDENT_LEN]; /* name of counter field */
};
