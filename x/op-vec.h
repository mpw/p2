/* $Id: op-vec.h,v 1.2 1997/09/25 15:54:03 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_OP_VEC_H
#define INCLUDE_OP_VEC_H

/* Included by x/init_generic.xp, x/log.xp, x/log_transient.xp */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "print-log.h" /* P2_PRINT_LOG */

/*****************************************************************************/
/*                  Call P2_put_op_vec()                                     */
/*****************************************************************************/

/* These two macros (P2_OP_NAME_VEC_INITIALIZER and P2_PUT_OP_VEC) are */
/* always used together.  Is there a good way to combine them into a */
/* single macro (i.e. eliminate P2_OP_NAME_VEC_INITIALIZER)??? */

#if defined(P2_PRINT_LOG)
#define P2_OP_NAME_VEC_INITIALIZER \
  char op_name_vec[20]; \
  char initializer[P2_MAX_OP_ID * 100]; \
  size_t len = 0; \
  int t; \
  sprintf(op_name_vec, "P2_temp%d", other_id_counter++); \
  initializer[0] = '\0'; \
  print2(initializer, &len, "{", 1); \
  for (t = 0; t < op_list->size; t++) \
  { \
    print2(initializer, &len, "\"", 1); \
    print1(initializer, &len, op_list->tuple[t].op); \
    print2(initializer, &len, "\",", 2); \
  } \
  print2(initializer, &len, "\"\"}", 2);
#else /* P2_PRINT_LOG */
#define P2_OP_NAME_VEC_INITIALIZER
#endif /* P2_PRINT_LOG */

#if defined(P2_PRINT_LOG)
#define P2_PUT_OP_VEC(ID, OP_VEC) \
    { \
      P2_OP_NAME_VEC %v.op_name_vec = %v.initializer; \
      P2_put_op_vec(ID, OP_VEC, %v.op_name_vec); \
    }
#else /* P2_PRINT_LOG */
#define P2_PUT_OP_VEC(ID, OP_VEC) \
    P2_put_op_vec(ID, OP_VEC);
#endif /* P2_PRINT_LOG */

#endif /* INCLUDE_OP_VEC_H */
