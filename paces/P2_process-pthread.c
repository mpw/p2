/* $Id: P2_process-pthread.c,v 45.2 1997/09/28 07:46:29 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#if 0
#include <pthread.h> /* pthread_create() */
#endif

#include "P2_process-manager.h" /* P2_PROCESS_PTHREAD */

#if defined(P2_PROCES_PTHREAD)

/* Once per process initialization. */

void
P2_init_process_pthread (void)
{
  /* On solaris 2.5, threads are not timesliced.  To ensure that our threads
     can run concurrently, we need to increase the concurrency level.
     Butenhof. */
  /* 2 is probably a lower bound on how high we should set the
     concurrency level. (JAT) */
  thr_setconcurrency(2);
}

#endif /* P2_PROCES_PTHREAD */
