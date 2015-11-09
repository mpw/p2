/* $Id: compcurs.h,v 45.0 1997/09/19 05:45:45 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* compcurs declarations */

#ifndef INCLUDE_COMPCURS_H
#define INCLUDE_COMPCURS_H

#include "arg.h"   /* LST_ARG */
#include "type.h"  /* NODE */
#include "xform.h" /* TE */

/*****************************************************************************/
/*                   Constants.                                              */
/*****************************************************************************/

#define MAX_NUM_LINK_PRED       50
#define MAX_NUM_LINK_CURS       10

/*****************************************************************************/
/*                   Typedefs.                                               */
/*****************************************************************************/

typedef enum {
  STRUCTURED,
  EXPLICIT_LINK,
  CROSS_PRODUCT,
  UNSTRUCTURED
} CP_TYPE;

typedef struct {
  int          num_curs;                 /* Number of cursors */
  char         *curs[MAX_NUM_LINK_CURS]; /* Cursors */
  CP_TYPE      type;                     /* Predicate type */
  LST_ARG      *lst_arg;                 /* Link state argument */
  char         predicate[MAX_PRED_LEN];  /* Predicate */
} CP_TABLE_ROW;

typedef struct cp_table_struct {
  TE           *unified_te;
  int          num_given;
  char         *given[MAX_NUM_LINK_CURS];
  int          num_curs;
  char         *curs[MAX_NUM_LINK_CURS];
  BOOLEAN      valid;
  char         *valid_predicate[MAX_NUM_LINK_CURS];
  char         *exit_predicate;
  int          num_rows;
  CP_TABLE_ROW *row[MAX_NUM_LINK_PRED];
} CP_TABLE;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

NODE    *compcurs_special_op_nonterm(NODE *op, NODE *params);
void    post_opt_compcurs_declaration(NODE *cursor_container_pair_list_opt,
                                      NODE *given_opt, NODE *valid_opt);
void    pre_opt_compcurs_declaration(void);

#endif /* INCLUDE_COMPCURS_H */
