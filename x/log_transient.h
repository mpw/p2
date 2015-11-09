/* $Id: log_transient.h,v 45.0 1997/09/19 05:46:33 jthomas Exp $ */
/* Copyright (C) 1997 The University of Texas at Austin. */

struct log_transient_annote {
  struct log_transient_annote *next;
  int cont_id;
  char *cont_name;

  char ofield[20];

  /* Added by xform. */

  char delete_op[10];
  char init_curs_op[10];
  char insert_op[10];
  char pos_op[10];
  char swap_op[10];

  char begin_xact_op[10];
  char commit_xact_op[10];
  char abort_xact_op[10];

  OP_LIST *default_op_list;
};
