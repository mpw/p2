/* $Id: token-queue.c,v 45.1 1997/09/19 07:44:46 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Token queue declarations. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL, sscanf() */
#include <string.h>       /* strncpy() */

#include "error.h"        /* error() */
#include "lex.h"          /* MAX_IDENT_LEN */
#include "string-util.h"  /* whitespace_span() */
#include "util.h"         /* BOOLEAN */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_TOKEN_QUEUE_LEN 10 /* Max length of token queue */

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

#define TOKEN_QUEUE_ADV(x) \
  { (x)++; if ((x) == MAX_TOKEN_QUEUE_LEN) (x) = 0; }

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

static char token_queue[MAX_TOKEN_QUEUE_LEN][MAX_IDENT_LEN];
static int  token_queue_head = 0; /* First empty slot in token queue. */
static int  token_count = 0; /* Total number of tokens seen so far. */

/*****************************************************************************/
/*                  Pragma liner.                                            */
/*****************************************************************************/

/* Return TRUE if token (string) s begins with "#pragma liner %c ",
   FALSE otherwise. */

static BOOLEAN
pragma_liner (const char *s)
{ 
  char x;
  if (sscanf(s, "#pragma liner %c ", &x) > 0) {
    if (x == 'F')
      sscanf(s, "#pragma liner F %s", original_file_name);
    else if (x == 'I')
      sscanf(s, "#pragma liner I %d", &original_line_number);
    else 
      warning(3, "error in pragma definition\n%s", s);
    return(TRUE);
  }
  else
    return(FALSE);
}

/*****************************************************************************/
/*                  Token queue add.                                         */
/*****************************************************************************/

/* Add token (string) s of length len to the token queue. */

void
add_token_queue (const char *s, int len)
{
#ifndef NDEBUG
  assert(strlen(s) == len);
  assert(strlen(s) < MAX_IDENT_LEN);
#endif

  if (!pragma_liner(s)) {
    /* Add non-whitespace token to the token queue. */
    s = s + whitespace_span(s);
    if (s[0] != '\0') {
      strncpy(token_queue[token_queue_head], s, len);
      token_queue[token_queue_head][len] = '\0';
      TOKEN_QUEUE_ADV(token_queue_head);
      token_count++;
    }
  }
}

/*****************************************************************************/
/*                  Token queue report.                                      */
/*****************************************************************************/

void
print_token_queue (void)
{
  if (token_count > 0) {
    int i = token_queue_head;

    fprintf(stderr, "Last %d tokens:\n", (token_count > 10) ? 10 : token_count);

    do {
      if (i < token_count)
        fprintf(stderr, "%s ", token_queue[i]);
      TOKEN_QUEUE_ADV(i);
    } while (i != token_queue_head);

    fprintf(stderr, "\n");
  }
}
