/* $Id: layer-util.h,v 45.0 1997/09/19 05:40:48 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_LAYER_UTIL_H
#define INCLUDE_LAYER_UTIL_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "type.h" /* CARD */

/*****************************************************************************/
/*                  Macros                                                   */
/*****************************************************************************/

#define FOREACH_ANNOTATION \
  for (te->annotation = te->first_annotation;  \
       te->annotation != NULL; \
       te->annotation = te->annotation->next)

/* xp never calls NONTERM at xp runtime, instead xp emits code that
   calls NONTERM at pb runtime.  Thus, move this definition to a pb
   source file. (JAT) */
#if 0
#define NONTERM(x) \
  P2_result = nonterm(UNT, NULL, 2, P2_result, x)
#elif 0
#define NONTERM(x) \
  P2_r = (x); \
  P2_result = nonterm(UNT, NULL, 2, P2_result, P2_r)
#else
#define NONTERM(x) \
  P2_r = (x); \
  P2_result = (P2_result == 0) ? P2_r : nonterm(UNT, NULL, 2, P2_result, P2_r)
#endif

#if 0
/* Documented but unused. (JAT) */
#define find_type(t,n) \
  t = &type_tab[0]; \
  while(t->typename[0] != NULL && strcmp(t->typename,n) != 0) \
    t++; \
  if (t->typename[0] == 0) \
    error("unrecognizable type name %s in indx annotation", n);
#endif

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

int     ceiling_log2(int i);
char    *first_identifier_in_string(const char *s);
void    get_ddlhint_argument(char *a, const NODE *b);
CARD    string_to_card(const char *s, const char *layer_name);

#endif /* INCLUDE_LAYER_UTIL_H */
