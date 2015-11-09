/* $Id: xp-io.c,v 45.3 1997/09/20 03:43:58 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Input/Output definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>          /* fputs() */
#include <stdarg.h>         /* va_list */
#include <stdlib.h>         /* size_t */
#include <string.h>         /* strcpy() */

#include "error.h"          /* error(), assert() */
#include "io.h"             /* SPRINT_BUF_SIZE */
#include "string-util.h"    /* last_char(), char_occurrences() */
#include "lex.h"            /* MAX_IDENT_LEN */
#include "util.h"           /* BOOLEAN */
#include "xp-string-util.h" /* last_char(), char_occurrences() */

/************************************************************************/
/*              Local Variables.                                        */
/************************************************************************/

static int xstart_nesting_depth = 0;  /* "%{" aka xstart nesting depth */ 

/************************************************************************/
/*              Global Variables.                                       */
/************************************************************************/

char    ctoken_line[MAX_IDENT_LEN];   /* ctoken accumulator */
int     brace_nesting_depth = 0;      /* "{" and "%{" nesting depth. */ 

/************************************************************************/
/*              out.                                                    */
/************************************************************************/

/* The procedure attempts to print newline characters at reasonable
   places to heuristically (1) make code more readable, and
   (2) keep lines from growing to an unreasonable length. */

static void
out1 (char *s, int len)
{
  char c = last_nonspace_char(s, len);
  if (c == ';' || c == '{' || c == '}')
    /* Print s followed by a newline character. */
    puts(s);
  else {
    /* Print s followed by a single space character. */
    fputs(s, stdout);
    fputs(" ", stdout);
  }
}

/* Emit code. */

/* Previously, in addition to this routine, we also provided an
   extraneous routine with identical functionality to this one, and its
   own non-standard quoting rules (for example, %% was # and \" was ').
   I deleted this extraneous routine, and all references to it.
   Do NOT introduce another extraneous routine, or non-standard
   quoting rules. (JAT) */

/* This procedure attempts to concatinate together into a single call,
   calls of the form PREFIX1 ... SUFFIX1 */
#define PREFIX1 "NONTERM(terminal_string1(\""
#define SUFFIX1 "\"));"

void
out (char *format, ...)
{
  va_list args;

  static char line0[SPRINT_BUF_SIZE+10] = { '\0' };
  char line1[MAX_IDENT_LEN+10];
  static BOOLEAN flag0 = FALSE; /* line0 == PREFIX1 ... SUFFIX1 */
  BOOLEAN flag1;                /* line1 == PREFIX1 ... SUFFIX1 */
  static size_t len0;           /* length of line0 */
  size_t len1;                  /* length of line1 */
  
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  assert(len0 == strlen(line0));
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */

  va_start(args, format);
  vsprintf(line1, format, args);
  va_end(args);

  len1 = strlen(line1);
  assert(len1 <= MAX_IDENT_LEN);
  flag1 = ((strncmp(line1, PREFIX1, strlen(PREFIX1)) == 0)
           && (strncmp(line1+len1-strlen(SUFFIX1), SUFFIX1, strlen(SUFFIX1)) == 0)
           && (char_occurrences(line1, '%') == 0));

  if (flag0 && flag1) {
    /* Concatinate line0 and line1 together into a single call. */
    assert(len0+len1-strlen(PREFIX1 SUFFIX1) <= SPRINT_BUF_SIZE);
    strcpy(line0+len0-strlen(SUFFIX1), line1+strlen(PREFIX1));
    len0 = len0+len1-strlen(PREFIX1 SUFFIX1);
  }
  else if (flag1) {
    /* Copy line1 to line0 */
    strcpy(line0, line1);
    len0 = len1;
    flag0 = TRUE;
  }
  else {
    /* Output line0 and line1 */
    out1(line0, len0);
    out1(line1, len1);
    line0[0] = '\0';
    len0 = 0;
    flag0 = FALSE;
  }
}

/************************************************************************/
/*              Jettison.                                               */
/************************************************************************/

/* Clear the ctoken_line buffer. */

void
jettison (void)
{
  if (ctoken_line[0] != '\0') {
     out("NONTERM(terminal_string1(\"%s\"));", ctoken_line);
     ctoken_line[0]='\0';
  }
}

/************************************************************************/
/*              x_header and x_trailer.                                 */
/************************************************************************/

/* Bookkeepping routines for parsing %{ and %} */

void
x_header (BOOLEAN nested)
{
  if (nested) {
     brace_nesting_depth++;
     out("{");
  }
  if (++xstart_nesting_depth > 1)
    error("%%{ nested too deep");
}

void
x_trailer (BOOLEAN nested)
{
  if (nested) {
     brace_nesting_depth--;
     out("}");
  }
  jettison();
  xstart_nesting_depth--;
}

