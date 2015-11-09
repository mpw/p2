/* $Id: xp-main.c,v 45.1 1997/09/19 07:51:58 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Main block of xp. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* printf() */
#include <stdlib.h>       /* EXIT_SUCCESS */
#include <string.h>       /* strcpy() */

#include "error.h"        /* calling_error() */
#include "getopt.h"       /* getopt_long() */
#include "gen-layerdef.h" /* gen_layerdef() */
#include "lex.h"          /* yyparse() */
#include "main.h"         /* print_help_information() */
#include "op-tab.h"       /* MAX_OP_PARAM */
#include "rlist.h"        /* min_special_op, max_special_op */
#include "seen.h"         /* seen */
#include "type.h"         /* init_type_system() */
#include "version.h"      /* version_string */
#include "xp-actions.h"   /* enable_hierarchy_comments */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

/* Declarations for command line long-option processing. */

static const struct option long_options[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) { name,has_arg,flag,val },
#include "xp-options.h"
#undef CMD_LINE_OPTION
};

static const char *options_help[] =
{
#define CMD_LINE_OPTION(name,has_arg,flag,val,help) help,
#include "xp-options.h"
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

  program_name = "xp";

  /* Set defaults. */

  yydebug = 0;
  enable_hierarchy_comments = 0;
  min_warning_priority = DRC_MIN_WARNING_PRIORITY + 2;

  while ((command_line_arg
          = getopt_long(argc, argv, "cdhvw", long_options, &unused)) != -1) {
    switch (command_line_arg) {
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
      printf("xp version %s\n", version_string);
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
    calling_error("xp takes exactly one argument");

  /* Parse input file name and open input file. */

  {
    char layer_name[MAX_IDENT_LEN];
    char *s;

    strcpy(layer_name, argv[optind]);
    s = strrchr(layer_name, '.');
    if (s != NULL) {
      *s++ = '\0';
      if (strcmp(s, "xp") != 0)
        calling_error("illegal file name extension %s", s);
    }
    sprintf(file_name, "%s.nxp", layer_name);
    sprintf(cdef_name, "%s.cdef", layer_name);
    sprintf(kdef_name, "%s.kdef", layer_name);

    yyin = fopen(file_name, "r");
    if (yyin == NULL)
      error("Can't open file %s", file_name);
  }

  /* Find minimum and maximum layer operation numbers. */ 

  {
    int i;

    min_special_op = max_special_op = op_tab[0].op_num;

    for(i = 0; op_tab[i].op_num; i++)
    {
      if (min_special_op > op_tab[i].op_num)
        min_special_op = op_tab[i].op_num;
      else if (max_special_op < op_tab[i].op_num)
        max_special_op = op_tab[i].op_num;
#ifndef NDEBUG
      /* Make sure operation table initialization values are in the
         legal range. */
      if (op_tab[i].num_arg < 0 || op_tab[i].num_arg > MAX_OP_PARAM)
        error("operation %s: number of arguments %d must be in range 1...%d",
              op_tab[i].name, op_tab[i].num_arg, MAX_OP_PARAM);
      if (strlen(op_tab[i].constname) >= CONSTNAME_LEN)
        error("operation %s: length of operation number constant > %d",
              op_tab[i].name, CONSTNAME_LEN);
      if (strlen(op_tab[i].proc) > PROC_LEN)
        error("operation %s: length of operation argument list > %d",
              op_tab[i].name, PROC_LEN);
      if (strlen(op_tab[i].oparglist) > OPARGLIST_LEN)
        error("operation %s: length of operation argument list > %d",
              op_tab[i].name, OPARGLIST_LEN);
#endif      
    }
  }

  /* Initialize. */

  init_type_system();
  member_ctype = UNDEFINED_CTYPE;

  {
    int q;
    for(q = 0; q < MAX_NUM_OPS+1; q++)
      seen[q] = FALSE;
  }
  
  /* Parse. */

  if (yyparse() != 0)
    error("parsing failed");

  /* Report. */

  have_all_operations_been_seen();

  /* Generate layerdef. */

  gen_layerdef();

  /* Exit. */

  exit(EXIT_SUCCESS);
}
