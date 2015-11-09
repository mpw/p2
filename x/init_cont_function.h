/* $Id: init_cont_function.h,v 45.0 1997/09/19 05:46:29 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct init_cont_function_annote {
  struct init_cont_function_annote *next;
  int cont_id;
  char *cont_name;

  char function[MAX_IDENT_LEN];
};

