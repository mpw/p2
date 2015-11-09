/* $Id: error.h,v 45.2 1997/09/19 22:13:30 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Error reporting declarations. */

#ifndef INCLUDE_ERROR_H
#define INCLUDE_ERROR_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "lex.h"    /* MAX_IDENT_LEN */
#include "util.h"   /* BOOLEAN */

/* We explicitly #include <assert.h> here so that we don't have to
   re-write a bunch of other files that #include "paces.h" but don't
   explicitly #include <assert.h> (JAT) */

#include <assert.h>

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

/* Priority of design rule checking warnings. */

#define DRC_MIN_WARNING_PRIORITY 2

/*****************************************************************************/
/*                  External declarations.                                   */
/*****************************************************************************/

extern char *program_name;
extern char original_file_name[MAX_IDENT_LEN];
extern char file_name[MAX_IDENT_LEN];
extern int original_line_number;
extern int line_number;
extern int min_warning_priority;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

/* Return int in case these routines appear in an expression. (JAT) */

int     assertion_failed(const char *format, ...);
int     calling_error(const char *format, ...);
int     error(const char *format, ...);
int     parse_error(const char *format, ...);
int     parse_warning(int priority, const char *format, ...);
int     warning(int priority, const char *format, ...);

#endif /* INCLUDE_ERROR_H */
