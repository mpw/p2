/* $Id: op-id.h,v 45.0 1997/09/19 05:40:50 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_OP_ID_H
#define INCLUDE_OP_ID_H

/* We want to be able to #include (NOT !#include) this file in .xp files.
   Thus, this file should contain ONLY CPP code (e.g. #define),
   this file should contain NO C code (e.g. typedef). (JAT) */

/* Log op_id numbers.

   These are analogous to pb/pb-type.c:op_list_match() numbers, these
   are NOT analogous to common/op-tab.h:SPECIAL_OP numbers.

   The definitions of the log op_id numbers are here, in a header file
   in the directory common/, because they are needed in both the
   layers x/log{,_transient}.xp (which writes op_ids to the log) and a
   paces file paces/P2_log-manager.p2 (which reads op_ids from the
   log).

   We generate operation vectors for schemas, but we don't want the
   operation vector manager to use the op_list_match() number of these
   schema operations (as it does for cursor operations), because this
   might clash with the op_list_match() number of a cursor operation.

   Thus, we use LARGE numbers so that these won't conflict with other
   operations.

   We would use NEGATIVE numbers so that these won't conflict with
   other operations, but the log manager reserves negative numbers to
   distinguish str from int upd(). */

/* These have the P2_ prefix, because this file is included in
   paces/P2_op-vec-manager.h, which is one of the files that P2
   automatically includes in all files, and thus these are visible to
   the user. */

/* Maximum legal operation identifier. */
#define P2_MAX_OP_ID                  100

/* Operations other than P2 special operations. */
#define P2_LOG_INIT_RBA_OP            1
#define P2_LOG_XACT_MANAGER_ANCHOR_OP 2

/* Log record, operation field, bit flags. */
#define P2_LOG_STR_UPD_OP             0x8000
#define P2_LOG_CONT_OP                0x4000
#define P2_LOG_SCHEMA_OP              0x2000
#define P2_LOG_OTHER_OP               0x1000

#define P2_LOG_NON_CURS_OP (P2_LOG_CONT_OP | P2_LOG_SCHEMA_OP | P2_LOG_OTHER_OP)

#define P2_LOG_OP                     0x00FF
#define P2_LOG_FLAGS                  0xF000

#endif /* INCLUDE_OP_ID_H */
