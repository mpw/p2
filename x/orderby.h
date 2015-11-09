/* $Id: orderby.h,v 1.1 1997/09/29 04:06:08 jthomas Exp $ */
/* Copyright (C) 1997 The University of Texas at Austin. */

struct P2_LAYER_CSTATE {
  int                    id;
  int                    layerno;
  struct P2_LAYER_CSTATE *next;

  OP_TAB                 *typeptr;
  char                   *orderby_field_type;
  int                    retrieval_layer;
  int                    orderby_retrieval_layer;
  int                    orderby_retrieval_cost;
};

#if 0
struct orderby_kstate {
  int                   id;
  int                   layerno;
  struct orderby_kstate *next;

  int                   orderby_cursor_id;
};
#endif

#if 0
struct orderby_annote {
  struct orderby_annote *next;
  int                    cont_id;
  char   *cont_name;
};
#endif
