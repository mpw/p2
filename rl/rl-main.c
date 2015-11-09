/* $Id: rl-main.c,v 45.0 1997/09/19 05:46:10 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fcntl.h>  /* O_TRUNC */
#include <stdarg.h> /* va_list, va_start(), va_end() */
#include <string.h> /* strrchr() */

#include "rl.h"

int getopt();

BOOLEAN active_rule_optimization = FALSE;
BOOLEAN string_optimization = FALSE;
BOOLEAN leaps_debugging  = FALSE;
BOOLEAN persistence = FALSE;
BOOLEAN garbage_collection = FALSE;
BOOLEAN shadow_optimization = FALSE;
BOOLEAN inline_ops = FALSE;
BOOLEAN malloc_optimization = FALSE;
BOOLEAN negation_optimization = FALSE;
BOOLEAN predicate_indices = FALSE;
BOOLEAN standard_output = FALSE;
BOOLEAN timestamp_layer = FALSE;
BOOLEAN shadow_container = TRUE;
BOOLEAN attribute_indices = FALSE;

#define FORMFEED printf("\f\n")

int
yyerror (char *s)
{
  error_status = TRUE;
  fprintf(stderr, "rl:%d: %s\n", line_number, s);
  return 0;
}

void
error (char *format, ...)
{
  va_list args;

  fprintf(stderr, "rl: ");

  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "\n");
  exit(1);
}

void
calling_error (char *command)
{
  fprintf(stderr, "Usage: %s [options] file\n", command);
  fprintf(stderr, " file.ops read; file.p2 is generated (see -s option)\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr, " -a active rule optimization\n");
  fprintf(stderr, " -c string constant enumeration optimization\n");
  fprintf(stderr, " -d debugging mode for op code generation\n");
  fprintf(stderr, " -e leaps debugging mode\n");
  fprintf(stderr, " -f persistence\n");
  fprintf(stderr, " -g garbage collection\n");
  fprintf(stderr, " -h shadow stacking optimization\n");
  fprintf(stderr, " -i inline insert and delete operations\n");
  fprintf(stderr, " -l standard leaps options (-achmp)\n");
  fprintf(stderr, " -m malloc optimization\n");
  fprintf(stderr, " -n negation optimization\n");
  fprintf(stderr, " -p add predicate indices\n");
  fprintf(stderr, " -s print to standard output, not file.p2\n");
  fprintf(stderr, " -t include timestamp layer\n");
  fprintf(stderr, " -x add attribute indices\n");
  fprintf(stderr, " -1 no explicit shadow container\n");
  exit(1);
}

int
main (int argc, char *argv[])
{
  char fname[100];
  int input;

  char *c;
  extern int optind;
  int s;

  if (argc == 1)
    calling_error(argv[0]);
  else {
    while ((s = getopt(argc,argv,"acdefghilmnpstwx")) != EOF) {
      switch(s) {
      case 'a':
        active_rule_optimization = TRUE;
        predicate_indices = TRUE;
        break;
      case 'c':
        string_optimization = TRUE;
        break;
      case 'd':
        yydebug = 1;
        break;
      case 'e':
        leaps_debugging = TRUE;
        break;
      case 'f':
        persistence = TRUE;
        break;
      case 'g':
        garbage_collection = TRUE;
        break;
      case 'h':
        shadow_optimization = TRUE;
        break;
      case 'i':
        inline_ops = TRUE;
        break;
      case 'l':
        active_rule_optimization = TRUE;
        malloc_optimization = TRUE;
        predicate_indices = TRUE;
        shadow_optimization = TRUE;
        string_optimization = TRUE;
        break;
      case 'm':
        malloc_optimization = TRUE;
        break;
      case 'n':
        negation_optimization = TRUE;
        break;
      case 'p':
        predicate_indices = TRUE;
        break;
      case 's':
        standard_output = TRUE;
        break;
      case 't':
        timestamp_layer = TRUE;
        break;
      case 'x':
        fprintf(stderr, "indexing option not yet implemented\n");
        break;
      case '1':
        shadow_container = FALSE;
        fprintf(stderr, "-n option not yet debugged\n");
        fprintf(stderr, "cursor_typedefs, rulefires, instances need checking\n");
        exit(1);
      default:
        calling_error(argv[0]);
        break;
      }
    }
  }

  if (optind == argc) 
    calling_error(argv[0]);

  strcpy(fname, argv[optind]);
  c = strrchr(fname, '.');
  if (c != NULL) {
    *c++ = '\0';
    if (strcmp(c, "ops") != 0)
      calling_error(argv[0]);
    strcpy(fname, argv[optind]);
  }
  else
    sprintf(fname, "%s.ops", argv[optind]);

  yyin = fopen(fname, "r");
  if (yyin == NULL)
    error("can't open input file %s", fname);

  strcpy(fname, argv[argc-1]);
  strcat(fname, ".p2");
  if (!standard_output) {
    close(1); 
    input = open(fname, O_TRUNC | O_WRONLY | O_CREAT, 0660);
    if (input != 1)
      error("can't open output file %s", fname);
  }

  yyparse();

  if (error_status == TRUE)
    printf("too many errors, exiting compilation\n");

  print_banner(fname);
  print_options();
  print_includes();
  print_defines();
  FORMFEED;
  print_valids();
  FORMFEED;
  print_forward_refs();
  FORMFEED;
  print_structs();
  FORMFEED;
  if (attribute_indices) {
    add_attribute_indices();
    print_attribute_indices();
  }
  if (string_optimization) {
    collect_string_constants();
    generate_symbol_table();
    FORMFEED;
  }
  print_container_decls();
  FORMFEED;
  print_ext_includes();
  if (active_rule_optimization) {
    print_active_rules();
    FORMFEED;
  }
  print_utility_cursors();
  FORMFEED;
  if (!inline_ops) {
    print_ins_del_ops();
    FORMFEED;
  }
  print_cursor_typedefs();
  FORMFEED;
  print_list_headers();
  print_validation_funcs();
  FORMFEED;
  print_rulefires();
  FORMFEED;
  order_rules();
  print_instances();
  FORMFEED;
  print_insert_data_tuple();
  FORMFEED;
  print_initialize();
  print_finalize();
  FORMFEED;
  printf("\n\n#include \"leaps.c\"\n");

  return 0;
}
