/* $Id: link.c,v 45.0 1997/09/19 05:40:49 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* link definitions */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h> /* strcpy() */

#include "error.h"  /* error() */
#include "link.h"   /* LINKTYPE */
#include "util.h"   /* BOOLEAN */

/*****************************************************************************/
/*                  Helpers.                                                 */
/*****************************************************************************/

/* linkpredicates are conjunctions of clauses of the form:

   join clause:    $p.f # $c.f  |  $c.f # $p.f
   parent clause:  $p.f # value
   child clause:   $c.f # value
   uninterpreted:  <sequence of nonblank chars>

   linkpartition collects all parent clauses and places them in
   parentres; all child clauses are in childres; the remaining
   are in rest. (DSB) */

#if 0

/* This routine temporarily not used--should use it to
    bind predicates. (DSB) */

char *
getfield (char *linkpredicate, char *field, char *array)
{
  char *p = linkpredicate;

  /* Step 1: find end of field. */

  *field = '\0';
  while (*p != ' ' && *p != '[') {
    *field = *p;
    field++;
    p++;
  }
  *field = '\0';

  /* Step 2: find end of 1-D array reference. */

  *array = '\0';
  if (*p == '[') {
    while (*p != ']') {
      *array = *p;
      array++;
      p++;
    }
    *array = ']';
    *(array++) = '\0';
    p++;
  }

  /* Step 3: return current parsing position. */

  return(p);
}

#endif

/* Advance p to the next nonblank character */

static char *
skip_to_nonblank (const char *p)
{
   while (*p == ' ')
      p++;
   /* Explicit cast is necessary, because assignment discards const. */
  return((char *) p);
}

/* copy_to_blank(in, out) - copies characters of in
   to out until a blank is reached.  All subsequent
   blanks of in are stripped.  Postcondition: in is
   positioned at the end of line or the first non-blank
   character; out is positioned on the next character
   to write */

static char *
copy_to_blank (const char *linkpredicate, char **result)
{
  const char *p = linkpredicate;

  while (*p != ' ' && *p != '\0') {
    *(*result) = *p;
    (*result)++;
    p++;
  }
  *(*result) = *p;
  (*result)++;
  return(skip_to_nonblank(p));
}

/* skip_over_and(in) will skip over &&
   and position in on the next nonblank character.
   if in is already at the end of line, in
   is returned as is */

static char *
skip_over_and (const char *p)
{
  /* if end of string, quit */
  if (*p == '\0')
    /* Explicit cast is necessary, because return discards const. */
    return((char *) p);

  if (*p == '&' && *(p+1) == '&') 
    p = skip_to_nonblank(p+2);
  else
    error(" && missing ");

  /* Explicit cast is necessary, because return discards const. */
  return((char *) p);
}

/* cat(out, in) - read characters from in
   until end-of-line and copy them directly
   to out.  out is positioned over the next
   character to write */

static char *
cat (char *destination, const char *str)
{
  while (*str != '\0') {
    *destination = *str;
    destination++;
    str++;
  }
  return(destination);
}

/* post_and2(p1,p2) attaches " && p2" to p1 if
   p1 is nonempty, otherwise sets p1 to p2. */

static void
post_and2 (char **p1, const char *p2, BOOLEAN noand)
{
  if (noand)
    *p1 = cat(*p1,p2);
  else {
    *p1 = cat(*p1, "&& ");
    *p1 = cat(*p1,p2);
  }
  **p1 = '\0';
}

/*****************************************************************************/
/*                  Linkpartition.                                           */
/*****************************************************************************/

void
linkpartition (const char *linkpredicate,
               char *parentres, char *childres, char *rest)
{
  const char *p = linkpredicate;
  char tmpstr[200];
  char *tmp;
  BOOLEAN place_in_rest;
  BOOLEAN first_p = TRUE;
  BOOLEAN first_c = TRUE;
  BOOLEAN first_r = TRUE;
  LINKTYPE which;

  /* Step 1: initialize predicate pointers, values */

  *parentres = '\0';
  *childres  = '\0';
  *rest      = '\0';

  /* Step 2: loop over the linkpartition predicate */

  while (*p != '\0') {

    /* Step 2.1:  strip off blanks */

    if (*p == ' ') {
      p++;
      break;
    }

    /* Step 2.2:  if first term is $c or $p, collect entire clause
       before deciding how to classify it */

    if (*p == '$') {

      /* Step 2.2.1: process $x where x is p or c */

      if (*(p+1) == 'c') 
        strcpy(tmpstr, "$c");
      else
        strcpy(tmpstr, "$p");
      tmp = 2 + tmpstr;

      /* Step 2.2.2: copy the rest */

      p = copy_to_blank(p+2, &tmp);      /* copy field */
      p = copy_to_blank(p, &tmp);        /* copy relation */
      place_in_rest = FALSE;
      if (*p == '$') 
        place_in_rest = (*(p+1) == 'c' && tmpstr[1] == 'p') ||
          (*(p+1) == 'p' && tmpstr[1] == 'c');
      p = copy_to_blank(p, &tmp);   /* copy value    */
      p = skip_to_nonblank(p);
      p = skip_over_and(p);
      *tmp = '\0';

      /* Step 2.2.3: add to appropriate string */

      if (place_in_rest) {
        post_and2(&rest, tmpstr, first_r);
        first_r = FALSE;
      }
      else {
        if (tmpstr[1] == 'c') {
          post_and2(&childres, tmpstr, first_c);
          first_c = FALSE;
        }
        else {
          post_and2(&parentres, tmpstr, first_p);
          first_p = FALSE;
        }
      }
    }

    else { 

      /* Step 2.2.4: skip to the next blank character */

      tmp = tmpstr;
      p = copy_to_blank(p, &tmp);
      p = skip_over_and(p);
      *tmp = '\0';

      /* Step 2.2.5: determine if this should be added to
         the child residual, parent residual,
         or rest */

      which = NONE;
      tmp = tmpstr;
      while ((tmp = strchr(tmp,'$')) != 0) {
        tmp++;
        switch (*tmp) {
        case 'c':
          which = CHILD;
          break;
        case 'p':
          which = PARENT;
          break;
        default:
          break;
        }
      }
      switch (which) {
      case BOTH:
        post_and2(&rest, tmpstr, first_r);
        first_r = FALSE;
        break;
      case PARENT:
      case NONE:
        post_and2(&parentres, tmpstr, first_p);
        first_p = FALSE;
        break;
      default:
        post_and2(&childres, tmpstr, first_c);
        first_c = FALSE;
        break;
      }
    }
  }
}
