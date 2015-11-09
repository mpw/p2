/* $Id: log_tid_hack.h,v 45.0 1997/09/19 05:46:32 jthomas Exp $ */
/* Copyright (C) 1997 The University of Texas at Austin. */

struct log_tid_hack_annote {
  struct log_tid_hack_annote *next;
  int cont_id;
  char *cont_name;

  char ofield[20];

  /* Added by xform. */

  char insert_op[10];
  char delete_op[10];
  char swap_op[10];
  char pos_op[10];
#if defined(TID_HACK) || defined(TID_CHECK)
  char tid_op[10];
#endif
#ifdef TID_HACK
  char adv_op[10];
  char end_adv_op[10];
  char reset_start_op[10];
#endif

  OP_LIST *default_op_list;
};
