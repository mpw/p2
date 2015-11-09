/* $Id: log.h,v 45.1 1997/09/28 11:39:02 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

struct P2_LAYER_ANNOTE {
  struct P2_LAYER_ANNOTE *next;
  int cont_id;
  char *cont_name;

  char ofield[20];

  /* Added by xform. */

  char delete_op[10];
  char delete_curs_op[10];
  char init_curs_op[10];
  char insert_op[10];
  char pos_op[10];
  char swap_op[10];

  char close_cont_op[10];
  char init_cont_op[10];
  char open_cont_op[10];
  char overflow_op[10];

  char checkpoint_schema_op[10];
  char close_schema_op[10];
  char init_schema_op[10];
  char open_schema_op[10];

  char abort_xact_op[10];
  char begin_xact_op[10];
  char commit_xact_op[10];
  char init_rba_op[10];

  OP_LIST *default_curs_op_list;
  OP_LIST *default_cont_op_list;

#if 0
  P2_OP_NAME_VEC op_name_vec;
#endif
};
