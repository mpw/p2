/* $Id: P2_log-manager.h,v 45.3 1997/09/29 03:49:23 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_LOG_MANAGER_H
#define INCLUDE_P2_LOG_MANAGER_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

/* P2 will automatically #include this file in every file.  Thus, we
   want to #include as few additional files as possible in this file.
   We don't want to include P2_paces.h, which defines BOOLEAN, so
   we'll use int instead. (JAT) */

#include "print-log.h"          /* P2_PRINT_LOG */
#include "P2_process-manager.h" /* P2_SEMAPHORE_ID */
#include "P2_xact-manager.h"    /* P2_LSN, P2_XACT_ID */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

/* Include in the log anchor persist_lsn: the LSN of max (most recent)
   record in persistent store aka low-water mark. */
/* As an optimization, we might want to try omitting persist_lsn. */
#if 1
#if !defined(P2_PERSIST_LSN)
#define P2_PERSIST_LSN
#endif /* P2_PERSIST_LSN */
#endif

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

extern int P2_log_manager_initialized;

/* NON-durable transaction log manager (Do NOT flush log at commit). */
extern int P2_log_manager_async;

/*****************************************************************************/
/*                  Recovery Log Records.                                    */
/*****************************************************************************/

/* Must be a multiple of 4 (word-aligned). */
#define P2_LOG_STRUCT_VARCHAR_SIZE 512

/* Operation Identifier: should be in the range 0 ... P2_MAX_OP_ID */
typedef int P2_OP_ID;

/* Operation Code: operation identifier encoded with some other information. */
typedef int P2_OP_CODE;

/* Cursor and Container ID. */
/* An unsigned short is probably sufficient to store cursor and
   container identifiers, but the only data types that P2 currently
   supports are int and str. (JAT) */
/* Unify these into a single type??? (JAT) */
#if 0
typedef unsigned short P2_CURS_ID;
typedef unsigned short P2_CONT_ID;
#else
typedef int P2_CURS_ID;
typedef int P2_CONT_ID;
#endif

/*** Fields for all operations (including transactions) ***/

/* Note: xact_prev_lsn and xact_id are un-used for other operations
   (e.g. init_rba and xact_manager_anchor). */

/* Gray & Reuter, pp. 494, 541 */
#define P2_LOG_FIELDS \
  P2_LSN lsn; \
  P2_LSN prev_lsn; \
  P2_LSN xact_prev_lsn; \
  P2_XACT_ID xact_id; \
  P2_OP_CODE op_code

/* The char field dummy represents fields added by xform.
   The dummy field is necessary, because the cursor operations view
   part of the varchar field v of P2_LOG_STRUCT as structured data
   (obj_id and curs_id), and v appears at the end of the transformed
   element type, after the fields added by xform. */

#define P2_LOG_STRUCT_DUMMY_SIZE 4

/*** Fields for cursor operations. ***/

#define P2_CURS_LOG_FIELDS \
  P2_LOG_FIELDS; \
  char dummy[P2_LOG_STRUCT_DUMMY_SIZE]; \
  P2_CURS_ID curs_id; \
  void *obj_id /* Object address: a HACK. */

/*** Abstract superclass of all operations. ***/

/* The log is declared to have elements of type P2_LOG_STRUCT, but the
   actual objects stored in the log have a different type:

   (1) schema (aka transaction) operations (e.g. begin_xact,
       commit_xact, abort_xact) have the concrete subtype
       P2_XACT_LOG_STRUCT

   (2) cursor operations (insert, delete, swap, upd)
       have one of the concrete subtypes
       P2_{INSERT,DELETE,SWAP,INT_UPD,STR_UPD}_LOG_STRUCT */

/* P2_LOG_STRUCT does NOT contain the dummy field, because
   P2_LOG_STRUCT is passed to xform, which automatically adds the
   fields represented by dummy. */

typedef struct {
  P2_LOG_FIELDS;
  varchar v[P2_LOG_STRUCT_VARCHAR_SIZE];
} P2_LOG_STRUCT;

#define P2_SIZEOF_ELEMENT_LOG_CONT \
  (sizeof(P2_LOG_STRUCT) + P2_LOG_STRUCT_DUMMY_SIZE)

/*** Concrete subtype of transaction (aka schema) operations. ***/

typedef struct {
  P2_LOG_FIELDS;
} P2_XACT_LOG_STRUCT;

/*** Concrete subtype of container operations. ***/

typedef struct {
  P2_LOG_FIELDS;
  char dummy[P2_LOG_STRUCT_DUMMY_SIZE];
  P2_CONT_ID cont_id; /* Container identifier: a small integer. */
  void *cont_obj_id;  /* Container address: a HACK. */
} P2_CONT_LOG_STRUCT;

/*** Concrete subtype of other operations. ***/

/* If you change paces/P2_xact-manager.p2:P2_XACT_ANCHOR, be sure to
   change this declaration. */
/* It is probably better to include the whole P2_XACT_ANCHOR
   structure, rather than its constituent fields, but since P2_XACT_ANCHOR
   currently consists of only a single field, this is simpler. (JAT) */
typedef struct {
  P2_LOG_FIELDS;
  char dummy[P2_LOG_STRUCT_DUMMY_SIZE];
  P2_LSN low_water;
  P2_XACT_ID next_xact_id;
} P2_XACT_MANAGER_ANCHOR_LOG_STRUCT;

/*** Abstract superclass of cursor operations. ***/

/* P2_CURS_LOG_STRUCT DOES contain the dummy field, representing the
   fields added by xform. */

typedef struct {
  P2_CURS_LOG_FIELDS;
  varchar v[P2_LOG_STRUCT_VARCHAR_SIZE];
} P2_CURS_LOG_STRUCT;

/*** Concrete subtypes. ***/

typedef struct {
  P2_CURS_LOG_FIELDS;
  varchar v[P2_LOG_STRUCT_VARCHAR_SIZE];
} P2_INSERT_LOG_STRUCT;

typedef struct {
  P2_CURS_LOG_FIELDS;
  varchar v[P2_LOG_STRUCT_VARCHAR_SIZE];
} P2_DELETE_LOG_STRUCT;

typedef struct {
  P2_CURS_LOG_FIELDS;
  int int0;
  int int1;
} P2_INT_UPD_LOG_STRUCT;

typedef struct {
  P2_CURS_LOG_FIELDS;
  varchar v[P2_LOG_STRUCT_VARCHAR_SIZE];
} P2_STR_UPD_LOG_STRUCT;

typedef struct {
  P2_CURS_LOG_FIELDS;
  void *obj_id1; /* Object address: a HACK. */
  P2_CURS_ID curs_id1;
} P2_SWAP_LOG_STRUCT;

/* Union */
typedef union {
  P2_XACT_LOG_STRUCT x;
  P2_CONT_LOG_STRUCT k;
  P2_XACT_MANAGER_ANCHOR_LOG_STRUCT a;
  P2_INSERT_LOG_STRUCT i;
  P2_DELETE_LOG_STRUCT d;
  P2_SWAP_LOG_STRUCT s;
  P2_INT_UPD_LOG_STRUCT ui;
  P2_STR_UPD_LOG_STRUCT us;
} P2_LOG_UNION;

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#if 0
/* Un-used. */
#define P2_MAX_LSN_FILE 10000
#define P2_MAX_LSN_RBA  10000
#endif

/*****************************************************************************/
/*                  Recovery Log Anchor.                                     */
/*****************************************************************************/

/* Anchor record used by log manager as base of addressability. */
/* Called log_record_header in Gray & Reuter, pp. 505, 541 */
/*
  P2_LOG_STRUCT *prev; cache of P2_lsn_to_log_struct(prev_lsn)
  P2_LOG_STRUCT *next; cache of P2_lsn_to_log_struct(next_lsn)
*/

typedef struct {
  P2_SEMAPHORE_ID lock; /* Log lock: semaphore regulating log write access. */
  P2_LSN_INDEX index;   /* Sequence number of current log file. */  
  P2_LSN lsn;           /* LSN of next record. */
  P2_LSN prev_lsn;      /* LSN of most recent record. */
  P2_LSN xact_manager_anchor_lsn; /* LSN of xact mgr's most recent checkpoint */
#if defined(P2_PERSIST_LSN)
/* Should persist_lsn be here (in the log manager) or in the
   transaction manager???  (JAT) */
/* "Max LSN recorded in durable storage."
   Called "durable_lsn" in Gray & Reuter, p. 505. */
/* Note: this is NOT the checkpoint lsn. (JAT) */
  P2_LSN persist_lsn;
#endif /* P2_PERSIST_LSN */
} P2_LOG_ANCHOR;

/*****************************************************************************/
/*                  Log struct function.                                     */
/*****************************************************************************/

/* P2_log-manager.p2:P2_foreach_log_struct() maps a function of this type
   over the records of the log. */
/* A return value of 0 represents normal;  non-0 represents non-normal. */
typedef       int P2_LOG_STRUCT_FUNCTION(P2_LOG_STRUCT *x, ...);

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

/* These routines are called from the code generated by the
   log-manager layers. */
/* These routines should not be called directly. (JAT) */

void          P2_delete_log_manager(void);
void          P2_init_log_anchor(void);
void          P2_init_log_manager(void);
P2_LSN        P2_log_insert(P2_LOG_STRUCT *x, int size);
P2_LOG_STRUCT *P2_log_read_lsn(P2_LSN lsn);
P2_LSN        P2_log_read_anchor(void);
void          P2_log_write_anchor(P2_LSN lsn);
void          P2_log_manager_checkpoint_schema(void);
void          P2_log_manager_sync_log(void);
void          P2_log_manager_warm_restart(P2_LOG_STRUCT_FUNCTION *f);
void          P2_undo_xact(P2_LOG_STRUCT_FUNCTION *f);

#if defined(P2_PRINT_LOG)
void          P2_print_log(void);
void          P2_print_log_anchor(void);
#endif /* P2_PRINT_LOG */

#ifndef NDEBUG
int           P2_curs_id_valid(P2_CURS_ID curs_id);
int           P2_cont_id_valid(P2_CONT_ID cont_id);
int           P2_log_struct_valid(P2_LOG_STRUCT *x);
int           P2_lsncmp(P2_LSN lsn1, P2_LSN lsn2);
#endif /* NDEBUG */

#if 0
/* These are now static, and have lost their prefix "P2_". */
P2_LOG_STRUCT *P2_lsn_to_log_struct(P2_LSN lsn);
int           P2_lsn_valid(P2_LSN lsn);
#endif

#if 0
/* These are no longer needed. */
void          P2_log_manager_begin_xact(void);
void          P2_log_manager_commit_xact(void);
void          P2_log_manager_init_xact_cb(P2_XACT_STATUS status);
#endif

/*****************************************************************************/
/*                  Variables for x/log.xp.                                  */
/*****************************************************************************/

// Log record.
extern P2_LOG_UNION P2_log_record;
// Log record sizes.
extern int P2_log_record_size;
extern int P2_log_record_size0;
extern int P2_log_record_size1;

#endif /* INCLUDE_P2_LOG_MANAGER_H */

