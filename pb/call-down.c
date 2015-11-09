/* $Id: call-down.c,v 45.3 1997/09/27 09:57:00 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdarg.h>    /* va_list */

#include "call-down.h" /* CASCADE_OP */
#include "error.h"     /* assertion_failed */
#include "type.h"      /* NODE_FUNC */
#include "xform.h"     /* TE */

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

/* Return (NODE *) NULL. */

/* This function was intentionally not prototyped.  This function
   cannot be prototyped, because its address is returned by
   cascade_op, which is prototyped to return a NODE_FUNC, which is
   typedef'ed to a non-prototyped function returning NODE *. (JAT) */

/* Do not declare this function inline--it's address is used. (JAT) */

static NODE *
null_op ()
{
  return(NULL);
}

/* Find a non-NULL operation. */
/* Add check for realm mis-match here? (JAT) */

NODE_FUNC
cascade_op (TE **cascade_te, int opnum)
{
#ifndef NDEBUG
  if (opnum < LOWEST_OP || opnum > HIGHEST_ADHOC_OP)
    assertion_failed("opnum must be in range %d ... %d",
                     LOWEST_OP, HIGHEST_ADHOC_OP);
  if ((*cascade_te) == NULL)
    assertion_failed("NULL te passed to cascade_op");
#endif /* NDEBUG */

  if (!CASCADE_OP(opnum))
  {
    if ((*cascade_te)->layerdef->ops[opnum] == NULL)
      return(&null_op);
  }
  else
  {
    while ((*cascade_te) != NULL
#ifndef NDEBUG
           && (*cascade_te)->layerdef != NULL
#endif /* NDEBUG */
           && (*cascade_te)->layerdef->ops[opnum] == NULL)
      (*cascade_te) = (*cascade_te)->down[0];
  }
    
  if ((*cascade_te) == NULL)
    parse_error("NULL type expression: missing annotation"
                " or realm mis-match?");

#ifndef NDEBUG
  if ((*cascade_te)->layerdef == NULL
      || (*cascade_te)->layerdef->ops[opnum] == NULL)
    assertion_failed("NULL operation");
#endif /* NDEBUG */

  return((*cascade_te)->layerdef->ops[opnum]);
}

/* Call a special operation. */

NODE *
call_level (TE *te, int opnum, int num_arg, ...)
{
  va_list ap;
  TE *cascade_te = te;
  NODE_FUNC f = cascade_op(&cascade_te, opnum);
  void *arg[MAX_OP_PARAM];
  NODE *result = NULL;
  int i;

#ifndef NDEBUG
  assert_te_valid(te);
  assert_te_valid(cascade_te);
  if (MAX_OP_PARAM > 6)
    assertion_failed("MAX_OP_PARAM > 6, need to add some additional cases");
#endif /* NDEBUG */

  va_start(ap, num_arg);
  for (i = 0; i < num_arg; i++)
    arg[i] = va_arg(ap, void*);
  va_end(ap);

  switch (num_arg) {
  case 0:
    result = (*f)(cascade_te);
    break;
  case 1:
    result = (*f)(cascade_te, arg[0]);
    break;
  case 2:
    result = (*f)(cascade_te, arg[0], arg[1]);
    break;
  case 3:
    result = (*f)(cascade_te, arg[0], arg[1], arg[2]);
    break;
  case 4:
    result = (*f)(cascade_te, arg[0], arg[1], arg[2], arg[3]);
    break;
  case 5:
    result = (*f)(cascade_te, arg[0], arg[1], arg[2], arg[3], arg[4]);
    break;
  case 6:
    result = (*f)(cascade_te, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    break;
  default:
#ifndef NDEBUG
    assertion_failed("num_arg = %d > MAX_OP_PARAM = %d",
                     num_arg, MAX_OP_PARAM);
#endif /* NDEBUG */
    break;
  }
  return(result);
}

NODE *
call_down (TE *te, int chimney, int opnum, int num_arg, ...)
{
  va_list ap;
  void *arg[MAX_OP_PARAM];
  NODE *result;
  int i;

#ifndef NDEBUG
  assert_te_valid(te);
  if (MAX_OP_PARAM > 6)
    assertion_failed("MAX_OP_PARAM > 6, need to add some additional cases");
#endif /* NDEBUG */

  va_start(ap, num_arg);
  for (i = 0; i < num_arg; i++)
    arg[i] = va_arg(ap, void*);
  va_end(ap);

  switch (num_arg) {
  case 0:
    result = call_level(te->down[chimney], opnum, num_arg);
    break;
  case 1:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0]);
    break;
  case 2:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0], arg[1]);
    break;
  case 3:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0], arg[1], arg[2]);
    break;
  case 4:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0], arg[1], arg[2], arg[3]);
    break;
  case 5:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0], arg[1], arg[2], arg[3], arg[4]);
    break;
  case 6:
    result = call_level(te->down[chimney], opnum, num_arg,
                        arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    break;
  default:
#ifndef NDEBUG
    assertion_failed("num_arg = %d > MAX_OP_PARAM = %d",
                     num_arg, MAX_OP_PARAM);
#endif /* NDEBUG */
    break;
  }
    
  return(result);
}
