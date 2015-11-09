/* $Id: layer-util.c,v 45.0 1997/09/19 05:40:48 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Layer utilities definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>       /* memcpy() */

#include "error.h"        /* error() */
#include "io.h"           /* sprint_ptree() */
#include "string-util.h"  /* identifier_span() */
#include "type.h"         /* NODE */
#include "xmalloc.h"      /* xmalloc_atomic() */

/*****************************************************************************/
/*                  Ceiling log2.                                            */
/*****************************************************************************/

/* This function returns the ceiling of the base 2 log of i. */

int
ceiling_log2 (int i)
{
  int j = 0;
  while (i != 0) {
    i = i >> 1;
    j++;
  }
  return(j);
}

/*****************************************************************************/
/*                  First identifier in string.                              */
/*****************************************************************************/

char *
first_identifier_in_string (const char *s)
{
  int i;
  int n;
  char *t;

  i = identifier_complement_span(s);
  n = identifier_span(&s[i]);

  t = (char *) xmalloc_atomic(n+1);
  memcpy(t, &s[i], n);
  t[n] = '\0';
  return(t);
}

/*****************************************************************************/
/*                  String to cardinality.                                   */
/*****************************************************************************/

CARD
string_to_card (const char *s, const char *layer_name)
{
  switch (s[0]) {
  case 'a':
    return(AT_MOST_ONE);
  case 'o':
    return(ONE);
  case 'm':
    return(MANY);
  default:
    error("unrecognizable cardinality %s on %s", s, layer_name);
  }
  return(ERR);
}

/*****************************************************************************/
/*                  Get ddlhint argument.                                    */
/*****************************************************************************/

void
get_ddlhint_argument (char *a, const NODE *b)
{
  sprint_ptree(a, b);
  remove_char(a, ' ');
  remove_char(a, '"');
}
