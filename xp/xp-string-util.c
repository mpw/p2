/* $Id: xp-string-util.c,v 45.3 1997/09/20 03:43:59 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* String processing utility definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>       /* strcat() */
#include "error.h"        /* assert() */
#include "string-util.h"  /* replace_string_inplace() */

/************************************************************************/
/*              Last nonspace character.                                */
/************************************************************************/

/* Returns the null character ('\0') if the string has no nonspace
   characters. */

char
last_nonspace_char (char *s, int len)
{
  char *s0 = &s[len]; /* Last character in s, always the null character */
  char *s1 = s0;      /* Iterates through s */

#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  assert(len == strlen(s));
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
  assert((*s0) == '\0');

  while (len > 0) {
    len--;
    s1--;
    if ((*s1) != ' ' && (*s1) != '\t')
      /* Found a nonspace character, return it. */
      return(*s1);
  }
  /* Couldn't find a nonspace character, return the null character. */
  return(*s0);
}

/************************************************************************/
/*              Append Digit.                                           */
/************************************************************************/

/* If s does not end with a digit, append the digit zero to the end of s. */

void
append_digit (char *s)
{
  char c = last_char(s);
  if (c < '0' || c > '9')
    strcat(s, "0");
}

/************************************************************************/
/*              Escape quotes.                                          */
/************************************************************************/

/* Prepend a slash to all single and double quotes in s. */

void
escape_quotes (char *s)
{
  replace_string_inplace(s, "'", "\'");
  replace_string_inplace(s, "\"", "\\\"");
}
