/* $Id: op-tab.h,v 45.1 1997/09/23 12:54:08 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Definitions relating to special operations. */
/* Especially, the enumeration of special operations. */

#ifndef INCLUDE_OP_TAB_H
#define INCLUDE_OP_TAB_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "type.h" /* UND */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_NUM_OPS   HIGHEST_ADHOC_OP /* Max number of operations. */
#define MAX_OP_PARAM  6   /* Max number of operation arguments. */
#define CONSTNAME_LEN 25  /* Max length of operation number constant. */
#define PROC_LEN      100 /* Max length of C header declaration. */
#define OPARGLIST_LEN 100 /* Max length of argument list for default calls */

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

#define FOREACH_OPERATION(X) \
  for (X = op_tab; X->op_num != 0; X++) 

#define FOREACH_OPERATION_INDEX(X) \
  for (X = 0; op_tab[X].op_num != 0; X++)

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Realm classes. */
/* Get rid of TOP, TOPLINK, and BOTTOM (JAT) */

typedef enum {
  MIN_RCLASS = 0,       /* Must be zero, rclass is used as array index (JAT). */
  DS = MIN_RCLASS,      /* Data structure */
  TOP,                  /* Conceptual layer */
  MEM,                  /* Memory */
  LINK,                 /* Links */
  TOPLINK,              /* Conceptual Link layer */
  MAX_RCLASS = TOPLINK,
  BOTTOM                /* used internally for the bottom layer */
} RCLASS;

/* Why do we call the minima and maxima LOWEST and HIGHEST rather than
   MIN and MAX??? (JAT) */

/* Built in operations. */

typedef enum {
  LAYER_STMT = UND+1,
  LOWEST_OP,
  ABORT_XACT_OP = LOWEST_OP,
  ADVC_OP,
  ADVP_OP,
  ADV_OP,
  ALLOC_OP,
  VARALLOC_OP,
  BEGIN_XACT_OP,
  C_VERBATIM_OP,
  C_PUT_OP_VEC_OP,
  CLOSE_CONT_OP,
  CLOSE_SCHEMA_OP,
  COMMIT_XACT_OP,
  CHECKPOINT_CONT_OP,
  CHECKPOINT_SCHEMA_OP,
  CONNECT_OP,
  DDLHINT_OP,
  DELETE_OP,
  DELETE_CURS_OP,
  DISCONNECT_OP,
  ENDC_OP,
  ENDP_OP,
  END_ADV_OP,
  END_REV_OP,
  FOREACHC_OP,
  FOREACHL_OP,
  FOREACHP_OP,
  FOREACH_OP,
  GETREC_OP,
  INIT_CONT_OP,
  INIT_CURS_OP,
  INIT_SCHEMA_OP,
  INSERT_OP,
  VARINSERT_OP,
  IREF_OP,
  K_VERBATIM_OP,
  K_PUT_OP_VEC_OP,
  LOPTIMIZE_OP,
  L_VERBATIM_OP,
  OPEN_CONT_OP,
  OPEN_CONT_NUMBER_OP,
  OPEN_SCHEMA_OP,
  OPTIMIZE_OP,
  OVERFLOW_OP,
  VAROVERFLOW_OP,
  POS_OP,
  QUERY_OP,
  REF_OP,
  RELATED_OP,
  RESETC_OP,
  RESETP_OP,
  RESET_END_OP,
  RESET_START_OP,
  REV_OP,
  ROFEACH_OP,
  S_VERBATIM_OP,
  S_PUT_OP_VEC_OP,
  SWAP_OP,
  SYNC_CONT_OP,
  UPD_OP,
  XFORM_OP,
  HIGHEST_OP = XFORM_OP
} SPECIAL_OP;

/* Adhoc operations. */

typedef enum { 
  LOWEST_ADHOC_OP = HIGHEST_OP+1, 
  CARDINALITY_OP = LOWEST_ADHOC_OP,
  CONT_ID_OP,
  CURS_ID_OP,
  DELETED_OP,
  REFCOUNT_OP,
  SERIAL_NUMBER_OP,
  TID_OP,
  TIMESTAMP_OP,
  HIGHEST_ADHOC_OP = TIMESTAMP_OP
} ADHOCS_OP;

/* Special operation description. */
/* This struct is used to represent information
   relavant to a special (aka cursor) operation. */

typedef struct {
    char   *name;                  /* Name of op. */
    int    user;                   /* TRUE iff op is callable by the user. */
    int    is_void;                /* TRUE/FALSE if op returns void/(NODE *) */
    int    expr;                   /* TRUE/FALSE if op is expr/stmt. */
    int    proceduralize;          /* TRUE iff op is proceduralizable. */
    int    verbatim;
    int    has_container_arg;
    int    print_local_vars;
    int    print_return;             /* Should xp print return stmt? */
    int    delete_operation;
    int    indirect_container;       /* Add an extra level of indirection. */
    int    op[MAX_RCLASS+1];         /* Is op in realm? */
    int    num_arg;                  /* Number of arguments taken by op. */
    ACLASS param[MAX_OP_PARAM];      /* ACLASS of each argument taken by op. */
    int    op_num;                   /* op num (different from index aka id) */
    char   constname[CONSTNAME_LEN]; /* name of the operation number */
    char   proc[PROC_LEN];           /* C header declaration */
    char   oparglist[OPARGLIST_LEN]; /* argument list for default calls */
} OP_DESC;

/*****************************************************************************/
/*                  External declarations and function prototypes            */
/*****************************************************************************/

#if 0
extern OP_DESC std_op_tab[];
#else
extern OP_DESC op_tab[MAX_NUM_OPS];
#endif

#endif /* INCLUDE_OP_TAB_H */
