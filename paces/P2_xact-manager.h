/* $Id: P2_xact-manager.h,v 45.0 1997/09/19 05:42:45 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_TRANSACTION_MANAGER_H
#define INCLUDE_P2_TRANSACTION_MANAGER_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

/* P2 will automatically #include this file in every file.  Thus, we
   want to #include as few additional files as possible in this file.
   We don't want to include P2_paces.h, which defines BOOLEAN, so
   we'll use int instead. (JAT) */

#include "P2_process-manager.h" /* P2_PROCESS_ID */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

/* Maximum number of concurrent transactions. */
#define P2_MAX_XACT 100

/* Generate procedures to print the transaction manager anchor. */
#if 1
#ifndef P2_PRINT_XACT
#define P2_PRINT_XACT
#endif /* P2_PRINT_XACT */
#endif

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/*** Log sequence number (LSN).  ***/

/* Should probably be defined in P2_log-manager.h, but then we'd have
   non-heirarchical dependencies: this file (P2_log-manager.h) would
   depend on P2_log-manager.h for P2_LSN and P2_xact-manager.h would
   depend on this file (P2_log-manager.h) for P2_XACT_ID. (JAT) */

/* The primary key of a log record.  Monotonic: can be cast as
   unsigned 8-byte integers that increase monotonically.
   See Gray and Reuter, 1993, p. 499. */

typedef unsigned P2_LSN_INDEX;
typedef void *P2_LSN_RBA;

typedef struct {
  P2_LSN_INDEX index;       /* Sequence number of log file. */
  P2_LSN_RBA rba;           /* relative byte address (offset) in file. */
} P2_LSN;

/*** Transaction Identifier. ***/

/* Transaction identifiers should be structures or at least long,
   unsigned integers, but the log manager stores transaction
   identifiers in a P2 container, and the only data types that P2
   currently supports are int and str. (JAT) */
/* Can't we make this an unsigned anyway??? (JAT) */
#if 0
typedef int P2_XACT_ID;
#else
typedef unsigned P2_XACT_ID;
#endif

/*** Transaction status. ***/

typedef enum {
  P2_XACT_NONE = 1,         /* unrecoverable do, not in a transaction */
  P2_MIN_XACT_STATUS = P2_XACT_NONE,
  P2_XACT_DO,               /* recoverable do */
  P2_XACT_UNDO,             /* abort */
  P2_XACT_REDO,             /* recover */
  P2_MAX_XACT_STATUS = P2_XACT_REDO
} P2_XACT_STATUS;

/*** Transaction control block. ***/
/* Gray & Reuter call this TransCB, pp. 506, 588-589 */
/* Can not contain process id, since more than one process can be
   active in a transaction (even though a process can not be active in
   more than one transaction). */
/* The log manager and the transaction manager [co-operate to]
   maintain the addresses of the first and last log records of the
   transaction (min and max LSN). Gray & Reuter, p. 586 */

typedef struct P2_xact_cb {
  P2_XACT_ID xact_id;       /* This transaction's id. */
#if 0
  P2_XACT_STATUS status;    /* active,prepared,{committ,abort}{ing,ed} p. 589 */
#endif
  P2_LSN min_lsn;           /* LSN of transaction's first log record. */
  P2_LSN max_lsn;           /* LSN of transaction's most recent record. */
#if 0
  /* cycle field is currently unused. */
  struct P2_xact_cb *cycle; /* Used by deadlock detector */
#endif
} P2_XACT_CB;

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

extern const P2_LSN P2_NULL_LSN;

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

extern P2_XACT_ID P2_my_xact_id;
extern P2_XACT_ID P2_my_xact_status;
extern P2_LSN P2_low_water;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

/* These routines should not be called directly. (JAT) */

P2_LSN         P2_get_max_lsn(void);
P2_XACT_ID     P2_get_xact_id(void);
P2_XACT_STATUS P2_get_xact_status(void);
#if 0
void           P2_init_xact_cb(P2_XACT_STATUS status);
#else
void           P2_init_xact_cb(void);
#endif
P2_LSN         P2_log_transaction(P2_LSN new_lsn);
int            P2_null_lsn(P2_LSN lsn);
void           P2_set_xact_status(P2_XACT_STATUS status);
int            P2_status_valid(P2_XACT_STATUS status);
int            P2_xact_id_valid(P2_XACT_ID xact_id);
void           P2_xact_manager_abort_xact(void);
void           P2_xact_manager_begin_xact(void);
void           P2_xact_manager_commit_xact(void);
void           P2_xact_manager_checkpoint_schema(void);

#if defined(P2_PRINT_XACT)
void           P2_print_xact_anchor(void);
#endif /* P2_PRINT_XACT */

#endif /* INCLUDE_P2_TRANSACTION_MANAGER_H */
