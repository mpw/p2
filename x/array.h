/* $Id: array.h,v 45.0 1997/09/19 05:46:16 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct array_annote {
  struct array_annote *next;
  int    cont_id;
  char   *cont_name;

  char   size[MAX_IDENT_LEN]; /* Number of elements in array: a string */
  char   size_minus_one[25];  /* Maximum legal array index: an integer */
};
