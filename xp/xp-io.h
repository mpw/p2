/* $Id: xp-io.h,v 45.0 1997/09/19 05:47:05 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Input/Output declarations. */

#ifndef INCLUDE_XP_IO_H
#define INCLUDE_XP_IO_H

#include "util.h" /* BOOLEAN */

/************************************************************************/
/*              External declarations.                                  */
/************************************************************************/

extern int     brace_nesting_depth;
extern char    ctoken_line[MAX_IDENT_LEN];

/************************************************************************/
/*              Procedure prototypes.                                   */
/************************************************************************/

void    jettison(void);
void    out(char *format, ...);
void    x_header(BOOLEAN nested);
void    x_trailer(BOOLEAN nested);

#endif /* INCLUDE_XP_IO_H */
