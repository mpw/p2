/* $Id: adhoc-arg.c,v 45.0 1997/09/19 05:46:58 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* ADHOC_ARG definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>     /* NULL */
#include <string.h>    /* strcpy() */

#include "adhoc-arg.h" /* ADHOC_ARG */
#include "error.h"     /* error() */
#include "op-tab.h"    /* OP_DESC */
#include "xmalloc.h"   /* xmalloc() */

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

ADHOC_ARG *adhoc_arg; /* List of arguments for adhocs. */

/************************************************************************/
/*              ADHOC_ARG utilities.                                   */
/************************************************************************/

ADHOC_ARG *
append_arg (ADHOC_ARG *l, char *name)
{
  ADHOC_ARG *head = l;
  ADHOC_ARG *p = (ADHOC_ARG *) xmalloc(sizeof(ADHOC_ARG));

  strcpy(p->name,name);
  p->next = NULL;
  if (l) { 
    while(l->next != NULL)
      l = l->next;
    l->next = p; 
  }
  else
    head = p;
  return(head);
}

static int
chk_arg (char *name, ACLASS cl)
{
  switch (cl) {
  /* These 4 cases can be refined later */
  case(PAR):
  case(FIE):
  case(IDE):
  case(EXP):
    return(1);
  case(CON):
    return(!strncmp("container", name, 9)); 
  case(CUR):
    return(!strncmp("cursor", name, 6)); 
  case(STR):
    return((*name == '"') && (name[sizeof(name)-1] == '"')); 
  case(ERR):
    return(0);
  case(OTH):
    return(1);
  case(VPR):
    return(!strncmp("vp", name, 2));
  default:
   return(0);  
  }
}

void
verify_args (ADHOC_ARG *l, char *name)
{
  int narg,i;
  ADHOC_ARG *h;
  OP_DESC p;

  p = op_tab[getindxop(getop(name))];
  narg = p.num_arg;
  for(h=l, i=0; h ; h=h->next, i++);
  if (i != narg)
    error("%s expected %d arguments; called with %d.",p.name,narg,i);
  else
    for(h=l, i=0; h; h=h->next, i++)
      if (!chk_arg(h->name, p.param[i]))
        error("Argument %d did not match: %s, %d",
              i, h->name, (int) p.param[i]);
}

