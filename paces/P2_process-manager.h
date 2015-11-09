/* $Id: P2_process-manager.h,v 45.7 1997/09/29 03:50:15 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_PROCESS_H
#define INCLUDE_P2_PROCESS_H

/* Ideally, this interface should include only the functionality
   actually needed by P2, e.g. in P2_lock_manager.p2.  In practice,
   this interface includes some additional functionality that is not
   currently needed by P2, e.g. P2_join_process(), which is very
   useful for paces files, e.g. lock?? and process??, which must
   (without using mmap_shared) synchronize with their children
   e.g. before printing output (so that output appears in the correct
   order) or forking new children (to limit the number of currently
   active children). (JAT) */

/* Each process implementation (e.g., unix, pthread) has a separate
   implementation file (e.g., paces/P2_process-unix.c,
   paces/P2_process-pthread.c).  Formerly, each implementation had an
   analogous separate header file.  Unfortunately, this caused symbol
   undefined/redifined problems in the various stages of the P2
   compilation, because P2_cpp.h ignores #include directives.  By
   putting all the implementations in a single file, we eliminate the
   #include directives, and P2_cpp.h finds all of the
   definitions. (JAT) */

/* It is tempting to try to put the process definitions into leyers.
   The problem is that the other managers, e.g.,
   paces/P2_xact_manager.{p2,h} need to know THE process definitions,
   and these managers are compiled before we know the application's
   type expression. (JAT) */

#if !defined(P2_PROCESS_UNIPROCESS) \
    && !defined(P2_PROCES_UNIX) \
    && !defined(P2_PROCESS_PTHREAD)
#if 0
#define P2_PROCESS_UNIPROCESS
#elif 1
#define P2_PROCESS_UNIX
#elif 0
#define P2_PROCESS_PTHREAD
#endif
#endif

/*****************************************************************************/
/*                  Uniprocess.                                              */
/*****************************************************************************/

#if defined(P2_PROCESS_UNIPROCESS)

/*** Includes. ***/

#include <unistd.h>                 /* sleep() */

/*** Processes. ***/

#define P2_PROCESS_ID               int
#define P2_my_process_id            1
#define P2_PROCESS_ID_VALID(p)      1

#define P2_init_process()           1
#define P2_delete_process()         1
#define P2_get_process_id()         1

#define P2_fork_process() \
  P2_runtime_error("Can't P2_fork_process() in P2_process-uniprocess")
#define P2_join_process(p) \
  P2_runtime_error("Can't P2_join_process() in P2_process-uniprocess")
#define P2_sleep_process(t)         sleep(t)
#define P2_wakeup_process(p) \
  P2_runtime_error("Can't P2_wakeup_process() in P2_process-uniprocess")
#define P2_disable_wakeup_process() \
  P2_runtime_error("Can't P2_disable_wakeup_process() in P2_process-uniprocess")

/*** Semaphores. ***/

/* It would be better if we could define-away semaphores entirely in
   P2_process-uniprocess.  For example, we'd like P2_SEMAPHORE_ID foo
   to result in no declaration (instead of an int declaration), and
   P2_init_semaphore() to yield no expression (instead of the
   expression "1") */

#define P2_SEMAPHORE_ID int

#define P2_init_semaphore(s, c)     1
#define P2_lock_semaphore(s)        1
#define P2_trylock_semaphore(s)     1
#define P2_unlock_semaphore(s)      1
#define P2_delete_semaphore(s)      1

#elif defined(P2_PROCESS_UNIX)

/*****************************************************************************/
/*                  UNIX (heavyweight) processes.                            */
/*****************************************************************************/

/*** Includes. ***/

#include <sys/types.h>              /* pid_t */

/*** Processes. ***/

/* Definitions. */

#define P2_PROCESS_ID               pid_t
extern P2_PROCESS_ID                P2_my_process_id;

/* pid 0 = swapper/scheduler, 1 = init, 2 = pagedaemon. */
#define P2_PROCESS_ID_VALID(p)      ((p) > 2)

#ifndef NDEBUG
/* Every time, call getpid() and make sure it equals cached
   P2_my_process_id. */
#define P2_get_process_id1()        P2_get_process_id_unix()
#define P2_get_process_id()         P2_get_process_id_unix()
#else /* NDEBUG */
/* Only the first time, call getpid().  Subsequent times, return
   cached P2_my_process_id. */
#define P2_get_process_id1()        getpid()
#define P2_get_process_id()         P2_my_process_id
#endif /* NDEBUG */

#define P2_init_process()           P2_init_process_unix()
#define P2_delete_process()         P2_delete_process_unix()
#define P2_fork_process()           P2_fork_process_unix()
#define P2_join_process(p)          P2_join_process_unix(p)
#define P2_sleep_process(t)         P2_sleep_process_unix(t)
#define P2_wakeup_process(p)        P2_wakeup_process_unix(p)
#define P2_disable_wakeup_process() P2_disable_wakeup_process_unix()

/* Prototypes. */

void          P2_init_process_unix(void);
void          P2_delete_process_unix(void);
P2_PROCESS_ID P2_fork_process_unix(void);
int           P2_join_process_unix(P2_PROCESS_ID p);
unsigned      P2_sleep_process_unix(unsigned t);
int           P2_wakeup_process_unix(P2_PROCESS_ID p);
int           P2_disable_wakeup_process_unix(void);
#ifndef NDEBUG
P2_PROCESS_ID P2_get_process_id_unix(void);
#endif

/*** Semaphores. ***/

/* Definitions. */

typedef struct {
  int id;
} P2_SEMAPHORE_ID_UNIX;

#define P2_SEMAPHORE_ID             P2_SEMAPHORE_ID_UNIX

#define P2_init_semaphore(s, c)     P2_init_semaphore_unix((s), (c))
#define P2_lock_semaphore(s)        P2_lock_semaphore_unix(s)
#define P2_trylock_semaphore(s)     P2_trylock_semaphore_unix(s)
#define P2_unlock_semaphore(s)      P2_unlock_semaphore_unix(s)
#define P2_delete_semaphore(s)      P2_delete_semaphore_unix(s)

/* Prototypes. */

int           P2_init_semaphore_unix(P2_SEMAPHORE_ID *s, int c);
int           P2_lock_semaphore_unix(P2_SEMAPHORE_ID *s);
int           P2_trylock_semaphore_unix(P2_SEMAPHORE_ID *s);
int           P2_unlock_semaphore_unix(P2_SEMAPHORE_ID *s);
int           P2_delete_semaphore_unix(P2_SEMAPHORE_ID *s);

#elif defined(P2_PROCESS_PTHREAD)

/*****************************************************************************/
/*                  POSIX Threads.                                           */
/*****************************************************************************/

/*** Includes. ***/

#include <pthread.h>

/*** Processes. ***/

#define P2_PROCESS_ID               pthread_t
#define P2_my_process_id            pthread_self()

#define P2_PROCESS_ID_VALID(p)      1

#define P2_get_process_id1()        pthread_self()
#define P2_get_process_id()         pthread_self()

#define P2_init_process()           P2_init_process_pthread()
#define P2_delete_process()         /* Nothing??? (JAT) */
#define P2_fork_process()           /* pthread_create(...) */
#define P2_join_process(p)          
#define P2_sleep_process(t)         
#define P2_wakeup_process(p)        
#define P2_disable_wakeup_process() 

/* Prototypes. */
void P2_init_process_pthread(void);

/*** Semaphores. ***/

#define P2_SEMAPHORE_ID             sem_t

#define P2_init_semaphore(s, c)     sem_init(s, 0, c)
#define P2_lock_semaphore(s)        sem_wait(s)
#define P2_trylock_semaphore(s)     sem_trywait(s)
#define P2_unlock_semaphore(s)      sem_post(s)
#define P2_delete_semaphore(s)      sem_destroy(s)

#else

/*****************************************************************************/
/*                  None.                                                    */
/*****************************************************************************/

  Must define a process model

#endif /* P2_PROCESS_... */

#endif /* INCLUDE_P2_PROCESS_H */
