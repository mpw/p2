/* $Id: string-util.h,v 45.0 1997/09/19 05:40:52 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* String processing utility declarations. */

#ifndef INCLUDE_STRING_UTIL_H
#define INCLUDE_STRING_UTIL_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdlib.h> /* size_t */
#include "util.h"   /* BOOLEAN */

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    assert_string_nonempty_and_valid(const char *s);
void    assert_string_valid(const char *s);
int     char_occurrences(const char *s, char c);
char    *copy_string(const char *src);
char    *copy_string1(const char *src, size_t len);
void    delete_string(char *s, size_t len);
void    delete_trailing_space(char *s);
void    delete_trailing_space1(char *s, size_t *len);
BOOLEAN eval_expr(const char *t, long *e);
char    *find_space(const char *s);
int     identifier_complement_span(const char *s);
int     identifier_span(const char *s);
int     integer_span(const char *s);
char    last_char(const char *s);
void    remove_char(char *s, char c);
void    replace_char(char *s, char c1, char c2);
void    replace_string(const char *s, const char *sold, const char *snew,
                       char *result);
int     replace_string_inplace(char *s, const char *sold, const char *snew);
int     replace_string_inplace1(char *s, const char *sold, const char *snew,
                                int m);
int     whitespace_span(const char *s);

#endif /* INCLUDE_STRING_UTIL_H */
