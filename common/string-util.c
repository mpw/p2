/* $Id: string-util.c,v 45.4 1997/09/20 03:42:22 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* String processing utility definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>  /* assert() */
#include <stdio.h>   /* NULL */
#include <string.h>  /* strstr(), strcpy() */
#include <math.h>    /* strtol() */

#include "error.h"   /* IDENTIFIER_CHARACTER, assertion_failed() */
#include "io.h"      /* SPRINT_BUF_SIZE, assert_all_chars_printable() */
#include "type.h"    /* ARG_STR_LEN */
#include "util.h"    /* BOOLEAN */
#include "xmalloc.h" /* xmalloc_atomic() */

/*****************************************************************************/
/*                  Assertions                                               */
/*****************************************************************************/

/* Make sure string is "valid". */

void
assert_string_valid (const char *s)
{
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (s != NULL)
  {
    /* The two longest strings that I can think of. (JAT) */
    assert(strlen(s) < P2_MAX(SPRINT_BUF_SIZE, ARG_STR_LEN));
    assert_all_chars_printable(s);
  }
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
}

/* Make sure string is non-NULL, has a non-zero length, and is "valid". */

void
assert_string_nonempty_and_valid (const char *s)
{
  assert(s != NULL);
  assert(strlen(s) > 0);
  assert_string_valid(s);
}

/*****************************************************************************/
/*                  Last character.                                          */
/*****************************************************************************/

char
last_char (const char *s)
{
  return(*(s + strlen(s) - 1));
}

/*****************************************************************************/
/*                  Delete Trailing Space.                                   */
/*****************************************************************************/

/* Only write a null character if necessary, this way we will
   not get an error if s is a string constant with no trailing space. */

/*
   Arguments:
     s is the beginning of the string.
     len is the length of the string.
     (s[len] == '\0').
*/

void
delete_trailing_space1 (char *s, size_t *len)
{
  if (s != NULL)
  {
    char *t = &s[(*len)];

    /* Upon termination, len will be the length of s */

    while ((*len) > 0 && *(t-1) == ' ')
    {
      t--;
      (*len)--;
    }

    if (*t != '\0')
      *t = '\0';
  }
}

/*
   Argument:
     s is the end of the string
     (*s == '\0').
*/

void
delete_trailing_space (char *s)
{
  while (*(s-1) == ' ')
    s--;

  if (*s != '\0')
    *s = '\0';
}

/*****************************************************************************/
/*                  Remove character.                                        */
/*****************************************************************************/

/* remove_char(s,c) - s is a string that contains zero or more copies
   of character c.  remove_char removes c from string s.  This routine
   is useful in processing ddlhints.  see bintree.xp */

void
remove_char (char *s, char c)
{
  char *last = s;

  while (*s != '\0')
  {
    if (*s == c)
    {
      s++;
      continue;
    }
    *last++ = *s++;
  }
  *last = '\0';
}

/*****************************************************************************/
/*                  Replace character.                                       */
/*****************************************************************************/

/* replace_char(s,c1,c2) - s is a string that contains zero or more
   copies of character c.  replace_char replaces each instance of c1
   with c2.  This routine is useful in processing strings.  see
   *_str() routines. (DSB) */

void
replace_char (char *s, char c1, char c2)
{
  while (*s != '\0')
  {
    if (*s == c1)
      *s = c2;
    s++;
  }
}

/*****************************************************************************/
/*                  Replace string.                                          */
/*****************************************************************************/

/* Delete from string s the substring of length len.
   That is:
     s[0] = s1[0] = s[len]
     s[1] = s1[1] = s[len+1]
     s[2] = s1[2] = s[len+2]
     ...
     s[?] = s1[?] = '\0'
   Thus, delete_string(s, 2) with s = "abc" sets s = "bc"
   (JAT)
*/

void
delete_string (char *s, size_t len)
{
  char *s1 = s + len;
  
  while (*s1 != '\0')
    *s++ = *s1++;
  *s = '\0';
}

/* Add to the beginning of string s the substring snew.
   Thus, in_string(s, "x") with s = "abc" sets s = "xabc".
   (JAT)
*/

static void
in_string (char *s, const char *snew)
{
  int  len = strlen(snew);
  char *s1 = s + strlen(s);
  char *s2 = s1 + len;
  
  /* Shift s right by strlen(snew) (to make spaces for snew). */
  while (s1 >= s)
    *s2-- = *s1--;
  /* Insert snew to at beginning of s (in the spaces created above). */
  while(s <= s2)
    *s++ = *snew++;
}

/* m is the maximum number of replacements to make (or -1 for replace all).
   n is the number of replacements actually made. (JAT) */

int
replace_string_inplace1 (char *s, const char *sold, const char *snew, int m)
{
  int n = 0;
  char *p;
  char *startfrom = s;
  
  while((m == -1 || n < m) && (p = strstr(startfrom,sold)) != NULL)
  {
    n++;
    delete_string(p, strlen(sold));
    in_string(p, snew);
    startfrom = p + strlen(snew);
  }
  return(n);
}

int
replace_string_inplace (char *s, const char *sold, const char *snew)
{
  return(replace_string_inplace1(s, sold, snew, -1));
}

/* Return a copy of the string format with the following enhancements:
   where ever string target appeared in the original version of format,
   string copy replaces it; the result is placed in string res. (DSB) */

/* Modify this procedure so that it doesn't use the temporary buffer r,
   and instead, writes the results directly into result??? (JAT) */

void
replace_string (const char *s, const char *sold, const char *snew, char *result)
{
  char r[SPRINT_BUF_SIZE];
  char *position;
  const char *start = (char *) s;
  int  skip   = strlen(sold);

  /* Step 1: While there is a copy of sold inside result, replace
     sold with replacement: snew [start,position) into result,
     followed by a copy of "snew" (DSB) */

  r[0] = '\0';
  while ((position = strstr(start, sold)))
  {
    strncat(r, start, position-start);
    strcat(r, snew);
    start = position + skip;
#ifndef NDEBUG
#ifndef P2_NEDEBUG
    /* Expensive assertion. */
    if (strlen(r) > SPRINT_BUF_SIZE)
      assertion_failed("result too long");
#endif /* P2_NEDEBUG */
#endif NDEBUG /* NDEBUG */
  }

  /* Step 2: snew the remains of sold. */

  strcat(r, start);
  strcpy(result, r);
}

/*****************************************************************************/
/*                  Copy string.                                             */
/*****************************************************************************/

char *
copy_string1 (const char *src, size_t len)
{
  char *dest;

  if (len == 0)
    return(NULL);
#ifndef NDEBUG
  assert_all_chars_printable(src);
  if (src == NULL)
    assertion_failed("len != 0, but src == NULL");
#endif /* NDEBUG */
  dest = (char *) xmalloc_atomic(len+1);
  strcpy(dest, src);
  return(dest);
}

char *
copy_string (const char *src)
{
  if (src == NULL)
    return(NULL);
  else
    return(copy_string1(src, strlen(src)));
}

/*****************************************************************************/
/*                  Character occurrences.                                   */
/*****************************************************************************/

/* Return the number of occurrences in the given string
   of the given character. */

int
char_occurrences (const char *s, char c)
{
  int i = 0;
  if (s != NULL)
    while (*s != '\0')
    {
      if (*s == c)
        i++;
      s++;
    }
  return(i);
}

/*****************************************************************************/
/*                  Find space.                                              */
/*****************************************************************************/

/* Find a space character NOT embedded in a string constant. */

/* This routine is equivalent to strchr(s, ' '),
   except that it ignores spaces embedded in a string constant. (JAT) */

char *
find_space (const char *s)
{
  while (s != NULL && *s != '\0' && *s != ' ')
  {
    if (*s == '\'')
      s = strchr(s+1, '\'');
    else if (*s == '"')
      s = strchr(s+1, '"');
    s++;
  }
  if (s == NULL || *s == '\0')
    return(NULL);
  else
    /* Explicit cast is necessary, because return discards const. */
    return((char *) s);
}

/*****************************************************************************/
/*                  Character span.                                          */
/*****************************************************************************/

/* Return the length of the initial segment of string s which consists
   entirely of identifier, identifier complement (ie non-identifier),
   integer, or whitespace characters. */

#define STRSPN 0

/* This routine is equivalent to strspn(s, IDENTIFIER_CHARACTERS) */

int
identifier_span (const char *s)
{
#if STRSPN
  return(strspn(s, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                   "1234567890_"));
#else
  int i = 0;
  char c;
  while ((c = *s) != '\0' && IDENTIFIER_CHARACTER(c))
  {
    i++;
    s++;
  }
  return(i);
#endif /* STRSPN */
}

/* This routine is equivalent to strcspn(s, IDENTIFIER_CHARACTERS) */

int
identifier_complement_span (const char *s)
{
#if STRSPN
  return(strcspn(s, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                    "1234567890_"));
#else
  int i = 0;
  char c;
  while ((c = *s) != '\0' && !IDENTIFIER_CHARACTER(c))
  {
    i++;
    s++;
  }
  return(i);
#endif /* STRSPN */
}

/* This routine is equivalent to strspn(s, INTEGER_CHARACTERS) */

int
integer_span (const char *s)
{
#if STRSPN
  return(strspn(s, "1234567890-"));
#else
  int i = 0;
  char c;
  while ((c = *s) != '\0' && INTEGER_CHARACTER(c))
  {
    i++;
    s++;
  }
  return(i);
#endif /* STRSPN */
}

/* This routine is equivalent to strspn(s, WHITESPACE_CHARACTERS) */

int
whitespace_span (const char *s)
{
#if STRSPN
  return(strspn(s, " \n\t\f"));
#else
  int i = 0;
  char c;
  while ((c = *s) != '\0' && WHITESPACE_CHARACTER(c))
  {
    i++;
    s++;
  }
  return(i);
#endif /* STRSPN */
}

/*****************************************************************************/
/*                  Evaluate expression.                                     */
/*****************************************************************************/

static BOOLEAN eval_expr1(const char **s, long *e);

static BOOLEAN
get_expr (const char **s, long *e)
{
  const char *s1;

  s1 = *s + whitespace_span(*s);
  /* Explicit cast is necessary to match function prototype. */
  *e = strtol(s1, (char **) s, 0);
  if (s1 != *s)
    return(1);
  else if (*s1 == '(')
  {
    *s = s1+1;
    if (eval_expr1(s, e))
    {
      *s = *s + whitespace_span(*s);
      if (**s == ')')
      {
        *s = *s+1;
        return(1);
      }
    }
  }
  return(0);
}

static BOOLEAN
get_op (const char **s, char *o)
{
  const char *s1;

  s1 = *s + whitespace_span(*s);
  *o = *s1;
  if (*s1 == '+' || *s1 == '-' || *s1 == '*' || *s1 == '/' || *s1 == '%')
  {
    *s = s1+1;
    return(1);
  }
  return(0);
}

static BOOLEAN
eval_expr1 (const char **s, long *e)
{
  if (get_expr(s, e))
  {
    long e1;
    char o;
    while (get_op(s, &o))
    {
      if (get_expr(s, &e1))
        switch(o) {
        case '+':
          *e = *e + e1;
          break;
        case '-':
          *e = *e - e1;
          break;
        case '*':
          *e = *e * e1;
          break;
        case '/':
          *e = *e / e1;
          break;
        case '%':
          *e = *e % e1;
          break;
        }
      else
        return(0);
    }
    return(1);
  }
  return(0);
}

BOOLEAN
eval_expr (const char *t, long *e)
{
  const char *s = (char *) t;
  if (eval_expr1(&s, e))
  {
    s = s + whitespace_span(s);
    if (*s == '\0')
      return(1);
  }
  return(0);
}
