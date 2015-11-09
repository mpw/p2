/* $Id: P2_lock-manager.h,v 45.0 1997/09/19 05:42:33 jthomas Exp $ */
/* Lock manager from Gray and Reuter. */

#ifndef INCLUDE_P2_LOCK_MANAGER_H
#define INCLUDE_P2_LOCK_MANAGER_H

/* NOTE: this file should only contain definitions that are necessary
   to define and use the exported functions: P2_lock(), P2_unlock(),
   and P2_unlock_class(). (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <time.h>       /* difftime() */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

/* Generate procedures to print the lock manager state. */
#if 0
#ifndef P2_PRINT_LOCK
#define P2_PRINT_LOCK
#endif /* P2_PRINT_LOCK */
#endif

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Note that, for debugging purposes, I have used separate number spaces
   for the enum typedefs to allow easier detection of enum type mismatch.
   For example, an assertion that a P2_LOCK_MODE variable is in the valid
   range for P2_LOCK_MODE will catch an erroneous assignment of a constant
   of type P2_LOCK_CLASS to that variable. */

/* Lock granules. */

typedef enum {
  P2_LOCK_FREE = 10,               /* lock is free, the null mode */
  P2_MIN_LOCK_MODE = P2_LOCK_FREE, 
  P2_LOCK_IS,                      /* intention share lock mode */
  P2_LOCK_S,                       /* shared lock mode */
  P2_LOCK_IX,                      /* intention exclusive lock mode */
  P2_LOCK_U,                       /* update lock mode */
  P2_LOCK_SIX,                     /* share & intention exclusive lock mode */
  P2_LOCK_X,                       /* exclusive lock mode */
  P2_LOCK_WAIT,                    /* lock is in a wait state */
  P2_MAX_LOCK_MODE = P2_LOCK_WAIT
} P2_LOCK_MODE;

/* Lock class (aka duration). */
/* Lock manager recognizes and acts specially for the following lock classes:
   (1) P2_LOCK_INSTANT: P2_unlock() immediately calls unlock.
   (2) P2_LOCK_LONG & P2_LOCK_VERY_LONG: P2_unlock() ignores unlock
         (locks of these classes are ONLY released by P2_unlock_class()). */

typedef enum {
  P2_LOCK_INSTANT = 20,            /* combined lock/unlock operation */
  P2_MIN_LOCK_CLASS = P2_LOCK_INSTANT,
  P2_LOCK_SHORT,                   /* released at the end of operation */
  P2_LOCK_MEDIUM,                  /* released explicitly */
  P2_LOCK_LONG,                    /* held to end of transaction */
  P2_LOCK_VERY_LONG,               /* held across transaction boundaries */
  P2_MAX_LOCK_CLASS = P2_LOCK_VERY_LONG
} P2_LOCK_CLASS;

/* A "lock name" is sometimes called a "lock id".  Gray and Reuter
   define P2_lock_name differently (as a string rather than a number). */
/* Lock names should definitely be hashed. */
typedef int P2_LOCK_NAME;

/* Lock reply: returned by P2_lock(), P2_unlock(), and P2_unlock_class(). */

typedef enum {
  P2_LOCK_OK = 30,
  P2_MIN_LOCK_REPLY = P2_LOCK_OK,
  P2_LOCK_TIMEOUT,
  P2_LOCK_DEADLOCK,
  P2_LOCK_NOT_LOCKED,
  P2_LOCK_REQUEST_OVERFLOW,
  P2_LOCK_HEAD_OVERFLOW,
  P2_MAX_LOCK_REPLY = P2_LOCK_HEAD_OVERFLOW
} P2_LOCK_REPLY;

/* Lock status. */

typedef enum {
  P2_LOCK_GRANTED = 40,
  P2_MIN_LOCK_STATUS = P2_LOCK_GRANTED,
  P2_LOCK_CONVERTING,
  P2_LOCK_WAITING,
  P2_LOCK_DENIED,
  P2_MAX_LOCK_STATUS = P2_LOCK_DENIED
} P2_LOCK_STATUS;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

P2_LOCK_REPLY P2_lock(P2_LOCK_NAME name, P2_LOCK_MODE mode,
                      P2_LOCK_CLASS class, unsigned timeout);
P2_LOCK_REPLY P2_unlock(P2_LOCK_NAME name);
P2_LOCK_REPLY P2_unlock_class(P2_LOCK_CLASS class);

#if defined(P2_PRINT_LOCK)
void P2_print_lock_manager_state(void);
#endif /* P2_PRINT_LOCK */

#endif /* INCLUDE_P2_LOCK_MANAGER_H */
