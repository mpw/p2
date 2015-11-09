/* $Id: xp-string-util.h,v 45.0 1997/09/19 05:47:06 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* String processing utility declarations. */

#ifndef INCLUDE_XP_STRING_UTIL_H
#define INCLUDE_XP_STRING_UTIL_H

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    append_digit(char *s);
void    escape_quotes(char *s);
char    last_nonspace_char(char *s, int len);

#endif /* INCLUDE_XP_STRING_UTIL_H */
