/* $Id: main.h,v 45.0 1997/09/19 05:40:50 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "getopt.h" /* struct option */

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void print_help_information(const struct option long_options[],
                            const char *options_help[]);
void parse_input_file_name(const char *argument, char file_name[]);

#endif /* INCLUDE_MAIN_H */
