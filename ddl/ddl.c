/* $Id: ddl.c,v 45.0 1997/09/19 05:41:01 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>       /* printf() */
#include <stdlib.h>      /* size_t */
#include <string.h>      /* strcat() */

#include "ddl.h"         /* LISTNODE */
#include "xmalloc.h"     /* xmalloc() */
#include "string-util.h" /* eval_expr() */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_BUF_SIZE    1000                 /* maximum buffer size */
#define FIRST_EQN       100                  /* first equation number */
#define NULL_LIST       (LISTNODE *) -1      /* end of list marker */

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Link equations together. */

typedef struct eqn_node_struct {  
  struct eqn_node_struct *next;
  char                   name[MAX_IDENT_LEN];
  LISTNODE               *node;
} EQN_NODE;

/*****************************************************************************/
/*                  Globals                                                  */
/*****************************************************************************/

/* Counters for assigning numbers to type equations and their components. */

#if 0
int eqn_num  = FIRST_EQN;
int comp_num = 0;
#endif

EQN_NODE *equation_list = NULL; /* List of type-equations. */
char target_layer[MAX_IDENT_LEN]; /* See print_path (DSB). */

/*****************************************************************************/
/*                  listnode utilities                                       */
/*****************************************************************************/

LISTNODE *
new_node (char *s)
{
  LISTNODE *n;

  n = (LISTNODE *) xmalloc(sizeof(LISTNODE));
  strcpy(n->text,s);
  n->next = NULL_LIST;
  return(n);
}

LISTNODE *
new_list (char *s, LISTNODE *l)
{ 
#if 0
  LISTNODE *n, *p;
  n = new_node(s);
  for (p=l; p->next != NULL_LIST; p=p->next);
  p->next = n;
  return(l);
#else
  LISTNODE *n = new_node(s);
  n->next = l;
  return(n);
#endif
}

LISTNODE *
new_list_head (LISTNODE *h, LISTNODE *l)
{
  h->next = l;
  return(h);
}

LISTNODE *
new_list_tail (LISTNODE *l, LISTNODE *n)
{
  LISTNODE *p;

  for (p=l; p->next != NULL_LIST; p=p->next);
  p->next = n;
  return(l);
}

/*****************************************************************************/
/*                  Other utilities                                          */
/*****************************************************************************/

/* Strip-off the identifying and trailing digits of a layer or typex name. */

static void
truncate (char *s, char *c)
{
  char * e;

  e = s + strlen(s) - 1;
  while (*e <= '9' && *e >= '0')
    e--;
  while (s<=e)
    *c++ = *s++;
  *c = '\0';
}

/* Set target_layer to the name of the last layer in the given path name. */

void
print_path (LISTNODE *p)
{
  strcpy(target_layer,"");
  printf("P2_path(");
  do {   
    printf("\"%s\", ", p->text);
    truncate(p->text, target_layer);
    p = p->next;
  } while (p != NULL_LIST);
  printf("\"\")");
}

void
print_expr (LISTNODE *p)
{
#if 0

  LISTNODE *q = p;
  size_t len = 0;
  char *s;
  long e;

  /* Calculate the length of the expr. */
  for (q = p; q != NULL_LIST; q = q->next)
    len = len + strlen(q->text);
  /* Allocate a string buffer. */
  s = (char *) xmalloc(len+1);
  /* Print the expr in the string buffer. */
  *s = '\0';
  for (q = p; q != NULL_LIST; q = q->next) {
    strcat(s, q->text);
    strcat(s, " ");
  }
  printf("\"");
  /* If possible, simplify the expression. */
  if (eval_expr(s, &e))
    printf("%ld", e);
  else
    printf("%s", s);
  printf("\"");

#else

  printf("\"");
  do {   
    printf("%s ", p->text);
    p = p->next;
  } while (p != NULL_LIST);
  printf("\"");

#endif
}

void
print_string_expr (LISTNODE *p)
{
  do {
    printf("\"%s\"", p->text);
    p = p->next;
    if (p != NULL_LIST)
      printf(", ");
  } while (p != NULL_LIST);
}

void
new_equation (char *name, LISTNODE *e)
{
  EQN_NODE  *n = (EQN_NODE *) xmalloc(sizeof(EQN_NODE));

  strcpy(n->name, name);
  n->next       = equation_list;
  n->node       = e;
  equation_list = n;
}

/*****************************************************************************/
/*                  Decompose conceptual.                                    */
/*****************************************************************************/

#define ORDERBY 1
#define GENERIC 1
#define FUNCALL 1

/* Setting TOP2DS_QUALIFY to 1 breaks mlist2,
   but the rest of the paces files seem to work okay. (JAT) */

#define TOP2DS_QUALIFY 0

LISTNODE *
decompose_conceptual (LISTNODE *l)
{
#if ORDERBY
  l = new_list_tail(l, new_node("top2ds"));
  l = new_list_tail(l, new_node("inbetween"));
  /* The orderby retrieval layer (e.g. dlist_stable) must be stable??? (JAT) */
  l = new_list_tail(l, new_node("dlist_stable"));
  l = new_list_tail(l, new_node("malloc"));
  l = new_list_tail(l, new_node("transient"));
#endif

#if !TOP2DS_QUALIFY
  l = new_list_head(new_node("qualify"), l);
#endif
  l = new_list_head(new_node("inbetween"), l);
#if ORDERBY
  l = new_list_head(new_node("orderby_smart"), l);
#endif
#if GENERIC && FUNCALL
  l = new_list_head(new_node("generic_funcall"), l);
#elif FUNCALL
  l = new_list_head(new_node("named_funcall"), l);
#endif
#if GENERIC
  l = new_list_head(new_node("generic"), l);
  l = new_list_head(new_node("init_generic"), l);
#endif
#if TOP2DS_QUALIFY
  l = new_list_head(new_node("top2ds_qualify"), l);
#else
  l = new_list_head(new_node("top2ds"), l);
#endif

  return(l);
}
