/* $Id: lex.h,v 45.0 1997/09/19 05:40:49 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Lexer declarations. */
/* This file should include declarations shared by
   ddl/ddl-lex.l, pb/pb-lex.l, and xp/xp-lex.l (JAT) */

#ifndef INCLUDE_LEX_H
#define INCLUDE_LEX_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdio.h>       /* FILE */

#include "type.h"        /* NODE */
#include "token-queue.h" /* add_token_queue() */

/*****************************************************************************/
/*                  External declarations.                                   */
/*****************************************************************************/

/* From .l and .y files. (JAT) */

extern size_t yyleng;
extern YYTEXT_DECLARATION;

extern FILE *yyin;
extern int  yydebug;

int yyparse(void);

/* The .c file generated from a flex source file calls, but never
   declares isatty().  This extern declaration suppressed the warning
   that would occur without this declaration. (JAT) */

extern int isatty (int fildes);

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_IDENT_LEN 500   /* Max length of ident or string constant. */

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

/* Character set predicates. */

#define IDENTIFIER_CHARACTER(c) \
  (((c) >= 'a' && (c) <= 'z') \
   || ((c) >= 'A' && (c) <= 'Z') \
   || ((c) >= '0' && (c) <= '9') \
   || ((c) == '_'))

#define INTEGER_CHARACTER(c) \
  (((c) >= '0' && (c) <= '9') \
   || ((c) == '-'))

#define WHITESPACE_CHARACTER(c) \
  ((c) == ' ' || (c) == '\n' || (c) == '\t' || (c) == '\f')

/* Lexer actions. */

#define RETURN_NODE_TOKEN(x, ctype) \
  node_token(&yylval.n, (char *) yytext, yyleng, ctype); \
  return(x);

#define RETURN_STRING_TOKEN(x) \
  string_token(yylval.str, (char *) yytext, yyleng); \
  return(x);

#define RETURN_NUMERIC_TOKEN(x) \
  add_token_queue((char *) yytext, yyleng); \
  return(x);

#define RETURN_WHITESPACE_TOKEN(x) \
  add_token_queue(x, strlen(x));
  
/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    node_token(NODE **dest, const char *src, int len, const CTYPE *ctype);
void    string_token(char *dest, const char *src, int len);
int     relational_operator(const char *s);

#endif /* INCLUDE_LEX_H */
