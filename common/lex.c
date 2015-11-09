/* $Id: lex.c,v 45.0 1997/09/19 05:40:48 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Lexer definitions. */
/* This file should include definitions shared by
   ddl/ddl_lex.l and pb/pb_lex.l (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>      /* strcpy() */

#include "error.h"       /* parse_error() */
#include "token-queue.h" /* add_token_queue() */
#include "lex.h"         /* MAX_IDENT_LEN */

/*****************************************************************************/
/*                  Node token.                                              */
/*****************************************************************************/

void
node_token (NODE **dest, const char *src, int len, const CTYPE *ctype)
{
  NODE *n = terminal(TYP, src, ctype);
  (*dest) = n;
  add_token_queue(src, len);
}

/*****************************************************************************/
/*                  String token.                                            */
/*****************************************************************************/

void
string_token (char *dest, const char *src, int len)
{
  if (len > MAX_IDENT_LEN-1)
    parse_error("identifier or constant too long\n%s", src);
  strcpy(dest, src);
  add_token_queue(src, len);
}

/*****************************************************************************/
/*                  Relational Operator.                                     */
/*****************************************************************************/

/* If the prefix of s is a relational operation,
     == | >= | <= | < | > | !=
   return the length of the relational operation.
   Otherwise return 0.
*/

int
relational_operator (const char *s)
{
  int len = strlen(s);
  if (len >= 2
      && (strncmp(s, "==", 2) == 0
          || strncmp(s, ">=", 2) == 0
          || strncmp(s, "<=", 2) == 0
          || strncmp(s, "!=", 2) == 0))
    return(2);
  else if (len >=1
           && (strncmp(s, "<", 1) == 0
               || strncmp(s, ">", 1) == 0))
    return(1);
  else
    return(0);
}
