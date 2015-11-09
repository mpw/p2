/* $Id: rlist.c,v 45.2 1997/09/19 22:15:12 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* RLIST definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>   /* NULL */
#include <string.h>  /* strcpy() */

#ifndef NDEBUG
#include "error.h"   /* assertion_failed() */
#endif /* NDEBUG */

#include "lex.h"     /* MAX_IDENT_LEN */
#include "op-tab.h"  /* op_tab, DS, RCLASS */
#include "rlist.h"   /* RLIST */
#include "util.h"    /* BOOLEAN */
#include "xmalloc.h" /* xmalloc() */

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

char    layer_name[MAX_IDENT_LEN]; /* Name of layer. */
RCLASS  layer_realm;               /* Pointer to layer's realm type. */
RLIST   *params_rlist;             /* Pointer to list of realm params. */

int     max_special_op;
int     min_special_op;

int     path[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/************************************************************************/
/*              RLIST utilities.                                        */
/************************************************************************/

RLIST *
tackon_rlist_node (RLIST *l, RLIST *n)
{
  RLIST *head = l;
  
  while (l->next != NULL)
    l = l->next;
  l->next = n;
  return(head);
}

RLIST *
new_rlist_node (int i)
{
  RLIST *p;
  
  p = (RLIST*) xmalloc(sizeof(RLIST));
  p->type = i;
  p->next = NULL;
  return(p);
}

char *
rclass_str (RCLASS rclass)
{
  switch (rclass) {
  case DS:      return("DS");
  case MEM:     return("MEM");
  case TOP:     return("TOP");
  case TOPLINK: return("TOPLINK");
  case LINK:    return("LINK");
  case BOTTOM:  return("BOTTOM");
  default:
#ifndef NDEBUG
    assertion_failed("illegal rclass %d", rclass);
#endif /* NDEBUG */
    return(NULL);
  }
}

void
print_realm_list (FILE *fp, RLIST *i)
{
  if (i == NULL) {
    fprintf(fp,"0");
    return;
  }
  while (i != NULL) {
    fprintf(fp, "%s", rclass_str(i->type));
    i = i->next;
    if (i != NULL)
      fprintf(fp, ", ");
  }
}

int
count_params (RLIST *i)
{
  int cnt = 0;
  
  while (i != NULL) {
    i = i->next;
    cnt++;
  }
  return(cnt);
}

/************************************************************************/
/*              call_below                                              */
/************************************************************************/

BOOLEAN
call_below (SPECIAL_OP op, int param)
{
  RLIST *p = params_rlist;
  
  if (p == NULL)
    return(FALSE);
  else {
    int i;
    for (i = 0; i < param; i++)
      p = p->next;
    if (p->type == BOTTOM) 
      return(FALSE);
    return(op_exists_in_realm(op, p->type));
  }
}

/************************************************************************/
/*              Operation exists in realm.                              */
/************************************************************************/

/* Find the first op_tab entry that defines the given operation in the
   given realm, and return the index of that entry.  If no such entry
   exists, return NIL. */

/* Essentually, this routine converts from a SPECIAL_OP constant to an
   op_tab entry. */

int
op_exists_in_realm (int operation, RCLASS realm)
{
  int i;

#ifndef NDEBUG
#if MIN_RCLASS > 0
  if (realm < MIN_RCLASS || realm > MAX_RCLASS)
#else /* MIN_RCLASS */
  if (realm > MAX_RCLASS)
#endif /* MIN_RCLASS */
    assertion_failed("Illegal paramater value, rclass = %d", realm);
  if (operation < min_special_op || operation > max_special_op)
    assertion_failed("Illegal paramater value, operation = %d", operation);
#endif /* NDEBUG */

  FOREACH_OPERATION_INDEX(i) { 
    if (op_tab[i].op_num == operation) 
      if(op_tab[i].op[realm])
        return(1);
  }
  return(0);
}
