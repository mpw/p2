/* $Id: cppgen.c,v 45.1 1997/09/19 07:44:07 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Generate cpp-command-only files from .h files */
/* That is, extract all and only lines beginning with the sharp sign (#),
   possibly containing a line continuation (Backslash-Newlines). */
/* Re-write this as a shell script??? (JAT) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* EXIT_SUCCESS */

/************************************************************************/
/*              Main.                                                   */
/************************************************************************/

void
main()
{
  int cpp_line = 0;
  int c1 = getc(stdin);
  int c0 = '\n';

  while (c1 != EOF) {
    if (!cpp_line)
      cpp_line = (c0 == '\n' && c1 == '#');
    if (cpp_line) {
      putc(c1, stdout);
      if (c1 == '\n')
        cpp_line = (c0 == '\\');
    }
    c0 = c1;
    c1 = getc(stdin);
  }

  /* Exit. */
  exit(EXIT_SUCCESS);
}
