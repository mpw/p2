/* $Id: main.c,v 45.0 1997/09/19 05:40:50 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>  /* printf() */
#include <string.h> /* strcat() */

#include "error.h"  /* calling_error() */
#include "getopt.h" /* struct option */

/*****************************************************************************/
/*                  Print help information.                                  */
/*****************************************************************************/

/* Print help descriptions of each command line option. */

void
print_help_information (const struct option long_options[],
                        const char *options_help[])
{
  int i;

  printf("Usage: %s [options] filename[.%s]\n",
         program_name, program_name);
  printf("Options:\n");

  for (i = 0; long_options[i].name != NULL; i++)
  {
    char option_name[80];
    char default_string[80];

    /* Is there a short equivalent? */
    if (long_options[i].flag == NULL)
      sprintf(option_name, "-%c, ", (char) long_options[i].val);
    else
      strcpy(option_name, "");

    /* Format long option name */
    strcat(option_name, "--");
    strcat(option_name, long_options[i].name);

    /* Is this option active by default? */
    if ((long_options[i].flag != NULL)
        && (*long_options[i].flag == long_options[i].val))
      strcpy(default_string, " (default)");
    else
      strcpy(default_string, "");

    printf(" %-26s%s%s\n", option_name, options_help[i], default_string);
  }
}

/************************************************************************/
/*              Parse input file name.                                  */
/************************************************************************/

/* Parse argument into a file name with the correct extension. */

void
parse_input_file_name (const char *argument, char file_name[])
{
  char *s;
  strcpy(file_name, argument);
  s = strrchr(file_name, '.');
  if (s != NULL)
  {
    /* The argument has an extension, make sure it is correct. */
    *s++ = '\0';
    if (strcmp(s, program_name) != 0)
      calling_error("illegal file name extension %s", s);
    strcpy(file_name, argument);
  }
  else 
    /* The argument has no extension, add one. */
    sprintf(file_name, "%s.%s", argument, program_name);
}
