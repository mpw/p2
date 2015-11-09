/* $Id: qsort.h,v 45.0 1997/09/19 05:46:47 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct qsort_annote {
  struct qsort_annote *next;
  int cont_id;        
  char   *cont_name;
                      
  char                ofield[20];       /* name of key field */
  char                max_size[20];  
  char                primary_or_secondary[20]; /* primary or secondary key */
                      
  VOID_FUNC           bi;               /* bounds impact function */
  OP_TAB              *typeptr;         /* type_table entry for this type */
  char                *ofield_type;     /* name of key field's type */
};
