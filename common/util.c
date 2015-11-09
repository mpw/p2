/* $Id: util.c,v 45.0 1997/09/19 05:40:56 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Definitions that are used everywhere and don't belong anywhere else. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* NULL */

/*****************************************************************************/
/*                  Machine setup.                                           */
/*****************************************************************************/

#if HAVE_SYS_SYSMIPS_H

/* Disable the automatic fixup of unaligned accesses on ULTRIX. (JAT) */
#include <sys/syscall.h>
#include <sys/sysmips.h>
extern int syscall();

#endif /* HAVE_SYS_SYSMIPS_H */

void machine_setup (void)
{
#if HAVE_SYS_SYSMIPS_H
  /* Disable address fixups for this process (inherited by any children).
      Where a fixup would have occured, you will get a SIGBUS.
      See comp.unix.ultrix_Common_Frequently_Asked_Questions. (JAT) */
#if ASSERTION_FAILED
  if (syscall(SYS_sysmips, MIPS_FIXADE, 0, NULL, NULL, NULL) == -1)
    assertion_failed("syscall failed");
#else
  syscall(SYS_sysmips, MIPS_FIXADE, 0, NULL, NULL, NULL);
#endif
#endif
}
