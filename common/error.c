/* $Id: error.c,v 45.0 1997/09/19 05:40:45 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>      /* assert() */
#include <stdarg.h>      /* va_list, va_start(), va_end() */
#include <stdio.h>       /* fprintf(), vfprintf() */
#include <stdlib.h>      /* exit, EXIT_FAILURE */
#include <string.h>      /* strcmp() */

#include "lex.h"         /* MAX_IDENT_LEN */
#include "token-queue.h" /* print_token_queue() */
#include "util.h"        /* BOOLEAN */

/*****************************************************************************/
/*                  Variables                                                */
/*****************************************************************************/

char *program_name;
char original_file_name[MAX_IDENT_LEN] = "";
char file_name[MAX_IDENT_LEN];
int original_line_number = 0;
int line_number;

/*
   Disable all warnings of less than the given priority.
     min_warning_prioirity will DISABLE warnings iff:
       warning priority < min_warning_priority 
     warning will be ENABLED iff
       warning priority >= min_warning_priority
   Thus:
     min_warning_priority = 1 disables warnings of priority 0 (i.e. none).
       All warnings will be enabled.
     min_warning_priority = 2 disables warnings of priority 1 and lower.
       All warnings of priority 2 and higher will be enabled.
     ...

   Note:
     0 is an illegal value for both warning priority and min_warning_priority.
     1 lowest warning priority.
   (JAT)
*/
int min_warning_priority;

/*****************************************************************************/
/*                  Local procedures.                                        */
/*****************************************************************************/

static void
print_error_header (void)
{
  fprintf(stderr, "%s:", program_name);
}

static void
print_parse_error_header (void)
{
  print_error_header();

  if (original_file_name[0] != '\0' || file_name[0] != '\0')
    fprintf(stderr, "%s:",
            (original_file_name[0] != '\0') ? original_file_name : file_name);

  if (original_line_number != 0 || line_number != 0)
    fprintf(stderr, "%d:",
            (original_line_number != 0) ? original_line_number : line_number);

  fprintf(stderr, " ");
}

/*****************************************************************************/
/*                  Global procedures.                                       */
/*****************************************************************************/

/* P2 internal consistency error. */

int
assertion_failed (const char *format, ...)
{
  va_list args;

  print_parse_error_header();
  fprintf(stderr, "assertion failed: ");

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "\n");
  print_token_queue();
  exit(EXIT_FAILURE);
}

/* User error or warning associated with a particular input file,
   but not a particular line. */

int
error (const char *format, ...)
{
  va_list args;

  print_error_header();
  fprintf(stderr, "error: ");

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}

int
warning (int priority, const char *format, ...)
{
  va_list args;

  assert(priority != 0);
  assert(min_warning_priority != 0);
  if (priority >= min_warning_priority) { 
    print_error_header();
    fprintf(stderr, "warning: ");

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
  }
  return(0);
}

/* User error associated with a particular input file and line. */

int
parse_error (const char *format, ...)
{
  va_list args;

  print_parse_error_header();
  if (strcmp(format, "parse error") != 0)
    fprintf(stderr, "parse error: ");

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "\n");
  print_token_queue();
  exit(EXIT_FAILURE);
}

int
parse_warning (int priority, const char *format, ...)
{
  va_list args;

  assert(priority != 0);
  assert(min_warning_priority != 0);
  if (priority >= min_warning_priority) { 
    print_parse_error_header();
    fprintf(stderr, "parse warning: ");

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
    print_token_queue();
  }
  return(0);
}

/* User error caused by running a program with the wrong arguments. */

int
calling_error (const char *format, ...)
{
  va_list       args;

  print_error_header();
  fprintf(stderr, "calling error: ");

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "\n");
  fprintf(stderr, "Usage: %s [options] layer_name[.%s]\n",
          program_name, program_name);
  fprintf(stderr, "For more information, type: %s --help\n",
          program_name);
  exit(EXIT_FAILURE);
}
