/* $Id: P2_process-unix.c,v 45.2 1997/09/26 03:43:34 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#if defined(HAVE_CONFIG_H)
#include "config.h"             /* UNION_SEMUN, SYSTEM_V_SIGNALS */
#endif

#include "P2_process-manager.h" /* P2_PROCESS_UNIX, P2_SEMAPHORE_ID */

#if defined(P2_PROCESS_UNIX)

#include <assert.h>             /* assert() */
#include <errno.h>              /* EINTR */
#include <signal.h>             /* SIGALRM */
#include <sys/types.h>          /* waitpid() */
#include <sys/ipc.h>            /* IPC_NOWAIT */
#include <sys/sem.h>            /* struct sembuf */
#include <sys/wait.h>           /* waitpid() */
#include <unistd.h>             /* alarm() */

#include "P2_xact-manager.h"    /* P2_XACT_ID */

#if defined(DEBUG)
/* For debugging. */
#include <stdio.h>              /* printf(), fflush() */
#endif /* DEBUG */

/* TRACE */
#if 0
#if !defined(TRACE)
#define TRACE
#endif /* TRACE */
#endif

/* Use newer (POSIX) signal handling functions (i.e. sigaction(),
   sigsuspend(), and sigprocmask()) instead of obsolete (ANSI C)
   signal handling functions (i.e. signal(), sigpause(), and sighold()) */
#if 1
#if defined(POSIX_SIGNALS)
#define POSIX_SIGNALS
#endif /* POSIX_SIGNALS */
#endif

/*****************************************************************************/
/*                  Global variables.                                        */
/*****************************************************************************/

/* Process identifier cache. */
P2_PROCESS_ID P2_my_process_id = 0;

#if 0
/* For debugging. */
P2_SEMAPHORE_ID P2_debug_semaphore;
#endif

#if defined(POSIX_SIGNALS)
static sigset_t sigalrm_mask;
struct sigaction sigalrm_sigaction;
#endif /* POSIX_SIGNALS */

/*****************************************************************************/
/*                  Processes.                                               */
/*****************************************************************************/

static void
sigalrm_handler ()
{
  /* The SIGALRM signal handler doesn't have to do anything. */

#if defined(TRACE)
  P2_trace("sigalrm_handler() invoked");
#endif /* TRACE */

#if defined(DEBUG)
  /* For debugging. */
  printf("%u. sigalrm_handler()\n", P2_my_process_id);
  fflush(stdout);
#endif /* DEBUG */

#if 0
  /* For debugging. */
  if (P2_unlock_semaphore(&P2_debug_semaphore) < 0)
    P2_runtime_perror("Can not unlock debug semaphore");
#endif

  /* This return should unblock the handled signal and
     continue the process at the point it was interrupted. */
}

void
P2_init_process_unix (void)
{
  /* Setup the signal_handler--override the default behavior, which
     for most signals, is to terminate. */

#if !defined(POSIX_SIGNALS)
  void *f;
#endif /* POSIX_SIGNALS */

#if defined(POSIX_SIGNALS)
  /* Set signal masks */
  if (sigemptyset(&sigalrm_mask) == -1)
    P2_runtime_perror("P2_init_process_unix: sigsemptyset() failed");
  if (sigaddset(&sigalrm_mask, SIGALRM) == -1)
    P2_runtime_perror("P2_init_process_unix: sigaddset() failed");
#endif /* POSIX_SIGNALS */

#if defined(POSIX_SIGNALS)
  /* Use sigaction() */
  /* Get old sigaction. */
  if (sigaction(SIGALRM, NULL, &sigalrm_sigaction) == -1)
    P2_runtime_perror("P2_init_process_unix: sigaction() failed");
  /* Modify sigaction. */
  /* Use SIG_IGN instead of sigalrm_handler()??? (JAT) */
  sigalrm_sigaction.sa_handler = sigalrm_handler;
  sigalrm_sigaction.sa_flags = 0;
  /* Set new sigaction. */
  if (sigaction(SIGALRM, &sigalrm_sigaction, NULL) == -1)
    P2_runtime_perror("P2_init_process_unix: sigaction() failed");
#else
  /* Use signal() */
  f = signal(SIGALRM, sigalrm_handler);
  if (f == sigalrm_handler)
    P2_runtime_error("P2_init_process_unix: SIGALRM handler already setup");
  if (f == SIG_ERR)
    P2_runtime_perror("P2_init_process_unix: signal() failed");
#endif /* POSIX_SIGNALS */

  /* Set process identifier cache. */
  P2_my_process_id = getpid();
  assert(P2_PROCESS_ID_VALID(P2_my_process_id));

#if defined(DEBUG)
  /* For debugging. */
  if (P2_init_semaphore(&P2_debug_semaphore, 0) < 0)
    P2_runtime_perror("Could not initialize process debug semaphore");
#endif /* DEBUG */
}

void
P2_delete_process_unix (void)
{
#if defined(DEBUG)
  /* For debugging. */
  P2_delete_semaphore((&P2_debug_semaphore) < 0)
    P2_runtime_perror("Could not initialize process debug semaphore");
#endif /* DEBUG */
}

P2_PROCESS_ID
P2_fork_process_unix (void)
{
  P2_PROCESS_ID p = fork();

#ifndef NDEBUG
  if (p < 0)
    /* This is an error. */
    P2_runtime_perror("P2_fork_process_unix: Can not fork process");
#endif
  if (p == 0)
  {
    /* This is the child. */
    /* Set process identifier cache. */
    P2_my_process_id = getpid();
    assert(P2_PROCESS_ID_VALID(P2_my_process_id));
  }
#ifndef NDEBUG
  else
  {
    /* This is the parent. */
    assert(P2_PROCESS_ID_VALID(p));
    assert(P2_PROCESS_ID_VALID(P2_my_process_id));
  }
#endif
  return(p);
}

int
P2_join_process_unix (P2_PROCESS_ID p)
{
  int stat;
  pid_t r;

  assert(P2_PROCESS_ID_VALID(p));
  /* This assertion is probably redundant with assert(P2_PROCESS_ID_VALID(p)),
      but it can't hurt to make it anyway. (JAT) */
  assert(p > (pid_t) 0);

  /*** Call waitpid() and check for errors. ****/

  assert(&stat != 0);
  r = waitpid(p, &stat, 0);
  if (r == -1)
    P2_runtime_perror("P2_join_process_unix:"
                      " Signal delivered to waitpid(%u) calling process", p);
  else if (r != p)
    P2_runtime_error("P2_join_process_unix:"
                     " Status for child process %u not available", p);

  /*** Return the exit status of the child process. ***/

  /* See man wstat(5) */
  /* WIFEXITED(stat) is non-zero if the child exited normally. */
  if (WIFEXITED(stat))
    /* Child exited normally. */
    /* WEXITSTATUS(stat) evaluates to the least significant 8 bits of
       the return code of the child. */
    return(WEXITSTATUS(stat));
  else
  {
    /* Child did not exit normally. */
#ifndef NDEBUG
    /* Some of these macros are not supported by some systems
       (e.g., AIX and Linux) */
#if defined(WIFSIGNALED) \
    && defined(WTERMSIG) \
    && defined(SIG2STR_MAX) \
    && defined(WIFSTOPPED) \
    && defined(WIFCONTINUED) \
    && defined(WCOREDUMP)
    if (WIFSIGNALED(stat))
    {
      int i = WTERMSIG(stat); /* Signal number. */
      char s[SIG2STR_MAX];    /* Signal name string. */
      sig2str(i, s);          /* Translate signal number to name string. */
      P2_runtime_warning("P2_join_process_unix:"
                         " Child terminated due to signal %d (SIG%s)", i, s);
    }
    if (WIFSTOPPED(stat))
      P2_runtime_warning("P2_join_process_unix:"
                         " Child stopped due to signal %d", WSTOPSIG(stat));
    if (WIFCONTINUED(stat))
      P2_runtime_warning("P2_join_process_unix:"
                         " Child has continued");
    if (WCOREDUMP(stat))
      P2_runtime_warning("P2_join_process_unix:"
                         " Core image of the terminated child was created");
#endif
#endif /* NDEBUG */
    P2_runtime_error("P2_join_process_unix:"
                     " Child process %u did not exit normally", p);
    return(-1); /* Suppress warning. */
  }
}

/* Sleep for t seconds or until another process calls wakeup.
   Return unslept time. */
/* Use sigsuspend()??? */

unsigned 
P2_sleep_process_unix (unsigned t)
{
  unsigned r;
#if !defined(POSIX_SIGNALS)
  int s;
#endif /* POSIX_SIGNALS */

#if defined(TRACE)
  P2_trace("P2_sleep_process_unix(%u)", t);
#endif /* TRACE */

#if defined(DEBUG)
  /* For debugging. */
  printf("%u. sleep begin\n", P2_my_process_id);
  fflush(stdout);
#endif /* DEBUG */
  
#ifndef NDEBUG
  if (t == 0)
    P2_runtime_error("P2_sleep_process_unix: time = 0");
#endif

  /* Set alarm. */
  alarm(t);

#if defined(POSIX_SIGNALS)
  /* Use sigsuspend() */
  if (sigsuspend(&sigalrm_mask) == -1)
    P2_runtime_perror("P2_sleep_process_unix: sigsuspend() failed");
#else /* POSIX_SIGNALS */
  /* Use sigpause() */
  /* Enable alarm signal (disabled by P2_disable_wakeup_process_unix() */
#if defined(SYSTEM_V_SIGNALS)
  s = sigpause(SIGALRM);
#else /* SYSTEM_V_SIGNALS */
  s = sigpause(0);
#endif /* SYSTEM_V_SIGNALS */
  if (s >= 0)
    P2_runtime_error("P2_sleep_process_unix: sigpause was not interrupted");
  if (errno != EINTR)
    P2_runtime_perror("P2_sleep_process_unix: sigpause() failed");
#endif /* POSIX_SIGNALS */

  /* r = unslept time, because alarm() returns the amount of time
     previously remaining in the alarm clock of the calling process.
     Note: is there a more elegant way to do this? */
  r = alarm(0);

#if 1 || !defined(POSIX_SIGNALS)
  /* Re-setup the SIGALRM signal handler. */
  if (signal(SIGALRM, sigalrm_handler) == SIG_ERR)
    P2_runtime_perror("P2_sleep_process_unix: signal() failed");
#endif /* POSIX_SIGNALS */

#if defined(DEBUG)
  /* For debugging. */
  printf("%u. sleep end\n", P2_my_process_id);
  fflush(stdout);
#endif /* DEBUG */

#if defined(TRACE)
  P2_trace("P2_sleep_process_unix(%u) returns %d", t, r);
#endif /* TRACE */

  return(r);
}

int
P2_wakeup_process_unix (P2_PROCESS_ID p)
{
  int r;

#if defined(TRACE)
  P2_trace("P2_wakeup_process_unix(%u)", p);
#endif /* TRACE */

#if defined(DEBUG)
  /* For debugging. */
  printf("%u. P2_wakeup_process_unix(%u) begin\n", P2_my_process_id, p);
  fflush(stdout);
#endif /* DEBUG */

  r = kill(p, SIGALRM);

#if defined(DEBUG)
  /* For debugging. */
  printf("%u. P2_wakeup_process_unix(%u) end\n", P2_my_process_id, p);
  fflush(stdout);
#endif /* DEBUG */

#if 0
  /* For debugging. */
  if (P2_lock_semaphore(&P2_debug_semaphore) < 0)
    P2_runtime_perror("Can not lock debug semaphore");
#endif

#if defined(TRACE)
  P2_trace("P2_wakeup_process_unix(%u) returns %d", p, r);
#endif /* TRACE */

  return(r);
}

/* Use sigprocmask()??? */

int
P2_disable_wakeup_process_unix (void)
{
#if defined(POSIX_SIGNALS)
  return(sigprocmask(SIG_BLOCK, &sigalrm_mask, NULL));
#else /* POSIX_SIGNALS */
#if defined(SYSTEM_V_SIGNALS)
  return(sighold(SIGALRM));
#else /* SYSTEM_V_SIGNALS */
  return(sigblock(sigmask(SIGALRM)));
#endif /* SYSTEM_V_SIGNALS */
#endif /* POSIX_SIGNALS */
}

#ifndef NDEBUG
P2_PROCESS_ID
P2_get_process_id_unix (void)
{
  P2_PROCESS_ID p = getpid();
  assert(p == P2_my_process_id);
  assert(P2_PROCESS_ID_VALID(p));
  return(p);
}
#endif /* NDEBUG */

/*****************************************************************************/
/*                  Semaphores.                                              */
/*****************************************************************************/

/* Lock operation. */
static struct sembuf op_lock[1] = {
  0, -1, 0 /* Decrement sem[0].  Block if this would make sem[0] < 0 */
};

/* Try lock operation. */
static struct sembuf op_trylock[1] = {
  0, -1, 1 /* Decrement sem[0].  Do not block if this would make sem[0] < 0 */
};

/* Unlock operation. */
static struct sembuf op_unlock[1] = {
  0, 1, 0 /* Increment sem[0]. */
};

int
P2_init_semaphore_unix (P2_SEMAPHORE_ID *s, int c)
{
  UNION_SEMUN arg;
  int r;

  arg.val = c;

  /* Create semaphore: unique IPC channel, 1 semaphore,
     and new & unique entry with access permission bits 0600 */
  if ((s->id = semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0600)) >= 0)
    if ((r = semctl(s->id, 0, SETVAL, arg)) < 0)
      return(r);
  return(s->id);
}

int
P2_lock_semaphore_unix (P2_SEMAPHORE_ID *s)
{
  assert(s->id >= 0);
  return(semop(s->id, op_lock, 1)); 
}

int
P2_trylock_semaphore_unix (P2_SEMAPHORE_ID *s)
{
  assert(s->id >= 0);
  return(semop(s->id, op_trylock, 1)); 
}

int
P2_unlock_semaphore_unix (P2_SEMAPHORE_ID *s)
{
  assert(s->id >= 0);
  return(semop(s->id, op_unlock, 1));
}

int
P2_delete_semaphore_unix (P2_SEMAPHORE_ID *s)
{
  assert(s->id >= 0);
  return(semctl(s->id, 0, IPC_RMID, 0));
}

#endif /* P2_PROCESS_UNIX */
