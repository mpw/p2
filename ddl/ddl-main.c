/* $Id: ddl-main.c,v 45.0 1997/09/19 05:41:00 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Main block of ddl. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <string.h>     /* strcpy() */

#include "error.h"      /* calling_error() */
#include "getopt.h"     /* getopt_long() */
#include "lex.h"        /* yyparse() */
#include "main.h"       /* print_help_information() */
#include "util.h"       /* machine_setup() */
#include "version.h"    /* version_string */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

/* P2 version defined in version.c */

extern char *version_string;

/* Declarations for command line long-option processing. */

static const struct option long_options[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) { name,has_arg,flag,val },
#include "ddl-options.h"
#undef CMD_LINE_OPTION
};

static const char *options_help[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) help,
#include "ddl-options.h"
#undef CMD_LINE_OPTION
};

/*****************************************************************************/
/*                  Main.                                                    */
/*****************************************************************************/

void
main (int argc, char *argv[])
{
  int command_line_arg;
  int unused;

  /* Machine specific initialization. (JAT) */

  machine_setup();

  /* Error initialization. */

  program_name = "ddl";

  /* Set defaults */

  yydebug = 0;
  min_warning_priority = DRC_MIN_WARNING_PRIORITY + 2;

  /* Parse command line arguments. */

  while ((command_line_arg
          = getopt_long(argc, argv, "dhvw", long_options, &unused)) != -1) {
    switch (command_line_arg) {
    case 'd':
      yydebug = 1;
      break;
    case 'h':
      print_help_information(long_options, options_help);
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      printf("p2 version %s\n", version_string);
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      min_warning_priority = 1; /* Enable all warnings. */
      break;
    case '?':
      calling_error("illegal or unrecognized option");
      break;
    }
  }

  if (optind == argc) 
    calling_error("ddl takes exactly one argument");
  
  /* Parse input file name and open input file. */

  parse_input_file_name(argv[optind], file_name);

  yyin = fopen(file_name, "r");
  if (yyin == NULL)
    error("Can't open file %s\n", file_name);

  /* Parse. */

  if (yyparse() != 0)
    error("parsing failed");

  /* Exit. */

  exit(EXIT_SUCCESS);
}
