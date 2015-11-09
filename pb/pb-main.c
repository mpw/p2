/* $Id: pb-main.c,v 45.0 1997/09/19 05:45:56 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Main block of pb. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <string.h>     /* strcpy() */

#include "drc.h"        /* init_drc() */
#include "error.h"      /* calling_error() */
#include "getopt.h"     /* getopt_long() */
#include "lex.h"        /* yyparse() */
#include "main.h"       /* print_help_information() */
#include "pb-type.h"    /* init_pb_type_system() */
#include "type.h"       /* init_type_system() */
#include "typex.h"      /* print_typex() */
#include "util.h"       /* machine_setup() */
#include "version.h"    /* version_string */
#include "xmalloc.h"    /* XMALLOC_STATS, xmalloc_stats_report() */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

int enable_hierarchy_comments;

/* Declarations for command line long-option processing. */

static const struct option long_options[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) { name,has_arg,flag,val },
#include "pb-options.h"
#undef CMD_LINE_OPTION
};

static const char *options_help[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) help,
#include "pb-options.h"
#undef CMD_LINE_OPTION
};

/*****************************************************************************/
/*                  Main.                                                    */
/*****************************************************************************/

int
main (int argc, char *argv[])
{
  int command_line_arg;
  int unused;

  /* Machine specific initialization. (JAT) */

  machine_setup();

  /* Error initialization. */

  program_name = "pb";

  /* Set defaults. */

  attr_file_name[0] = '\0';
  yydebug = 0;
  enable_hierarchy_comments = 0;

  /* Don't print most warnings, including drc warnings. */
  min_warning_priority = DRC_MIN_WARNING_PRIORITY + 2;

  /* Parse command line arguments. */

  while ((command_line_arg
          = getopt_long(argc, argv, "a:cdhvw", long_options, &unused)) != -1) {
    switch (command_line_arg) {
    case 'a':
      strcpy(attr_file_name, optarg);
      break;
    case 'c':
      enable_hierarchy_comments = 1;
      break;
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
    calling_error("pb takes exactly one argument");
  
  /* Parse input file name and open input file. */

  parse_input_file_name(argv[optind], file_name);

  yyin = fopen(file_name, "r");
  if (yyin == NULL)
    error("Can't open file %s", file_name);

  /* Initialize */

  init_type_system();
  init_pb_type_system();
  init_drc();

  /* Parse. */

  if (yyparse() != 0)
    error("parsing failed");

  /* Report. */

#if 0
  /* Do not delete. */
  /* Currently un-used, but retain for debugging purposes. (JAT) */

  if (scope != 0)
     parse_error("nonzero scope at end-of-file");

  printf("\n");
  printf("#if 0\n");
  printf("\nSymbols\n");
  print_symbols();
  printf("\n");
  printf("#endif\n");
  fflush(stdout);

  printf("\n");
  printf("#if 0\n");
  printf("\nType Expressions\n");
  print_typex();
  printf("\n");
  printf("#endif\n");
  fflush(stdout);
#endif
#if XMALLOC_STATS
  xmalloc_stats_report();
#endif

  /* Exit. */

  exit(EXIT_SUCCESS);
}
