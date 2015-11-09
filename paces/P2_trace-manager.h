/* $Id: P2_trace-manager.h,v 45.0 1997/09/19 05:42:41 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Tracing routines. */

#ifndef INCLUDE_P2_TRACE_MANAGER_H
#define INCLUDE_P2_TRACE_MANAGER_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

/* P2 will automatically #include this file in every file.  Thus, we
   want to #include as few additional files as possible in this file.
   We don't want to include P2_paces.h, which defines BOOLEAN, so
   we'll use int instead. (JAT) */

#include <time.h>                 /* time_t */
#include "P2_lock-manager.h"      /* P2_LOCK_MODE */
#include "P2_process-manager.h"   /* P2_SEMAPHORE_ID */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

#define P2_PROCESS_ID_LABEL_SIZE 100

/*****************************************************************************/
/*                  Global Variables.                                        */
/*****************************************************************************/

time_t P2_trace_init_time;
P2_SEMAPHORE_ID P2_trace_semaphore;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

char *P2_boolean_string(int x);
void P2_delete_trace_manager(void);
void P2_init_trace_manager(void);
void P2_label_process_id(const char *label);
char *P2_lock_mode_string(P2_LOCK_MODE mode);
char *P2_lock_class_string(P2_LOCK_CLASS class);
char *P2_lock_reply_string(P2_LOCK_REPLY reply);
char *P2_lock_status_string(P2_LOCK_STATUS status);
char *P2_process_id_label(P2_PROCESS_ID pid);
void P2_trace(const char *format, ...);
void P2_trace1(const char *format, ...);

#endif /* INCLUDE_P2_TRACE_MANAGER_H */
