/* $Id: pb-xform.c,v 45.2 1997/09/19 22:14:49 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* Type expression transformation definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>   /* assert() */
#include <stdio.h>    /* NULL */
#include <string.h>   /* strlen() */

#include "error.h"    /* assertion_failed() */
#include "pb-type.h"  /* ctypematch1() */
#include "pb-xform.h" /* FOREACH_MEMBER */
#include "type.h"     /* OTH */
#include "xform.h"    /* TE */
#include "xmalloc.h"  /* xmalloc_atomic() */

/************************************************************************/ 
/*              general struct utilities                                */
/************************************************************************/ 
 
/* We should move these someplace else, say pb/type.c??? (JAT) */
/* Then again, maybe we should get rid of or rename this entire file,
   since it really doesn't have anything to do with type
   transformation??? (JAT) */

IDENT *
lookup_struct (char *name)
{
  ENTRY *e = symtab_lookup(symtab[OTH], name);
  if (e == NULL)
    return(NULL);
  else
    return(e->ident);
}

IDENT *
new_struct (char *name, BOOLEAN add_to_symtab)
{
  CTYPE *c = STRUCT_CTYPE;
  IDENT *i = new_ident(SUE, name, c, NULL, FALSE);
  c->ident = i;
  if (add_to_symtab)
  {
#ifndef NDEBUG
    ENTRY *e = symtab_lookup(symtab[SUE], name);
    if (e != NULL && e->ident->scope == scope)
      assertion_failed("struct %s already exists in scope", name);
#endif /* NDEBUG */
    add_ident_to_symtab1(symtab[SUE], i);
  }
  return(i);
}

/* Add a new member to a structure.

   typex  Type expression whose root identifies the layer that is
            adding this member.
   str    struct to which the new member will be added.
   name   Name of the new member.
   ctype  Type of the new member.
   ident  If new member is struct, then handle to that struct.
            NULL otherwise.
*/

IDENT *
new_member (TE *typex, IDENT *str, char *name, CTYPE *ctype, IDENT *ident)
  /* TE was added to include layer numbers. (DSB) */
{
  char *layered_name = (char *) xmalloc_atomic(strlen(name)+10);
  IDENT *i;

  /* Tack layer number onto layered_name. */
  sprintf(layered_name, "%s%d", name, typex->layerno);

  i = new_ident1(MBR, layered_name, ctype, NULL, FALSE);
  if (ident != NULL)
    i->ctype->ident = ident;

  /* Add newly created member i to member symlist for struct str. */
  add_ident_to_symlist(&str->members, i);
  return(i);
}

IDENT *
new_global (TE *typex, char *name, CTYPE *ctype, IDENT *ident)
     /* TE was added to include layer numbers. (DSB) */
{
  char *layered_name = (char *) xmalloc_atomic(strlen(name)+10);
  IDENT *i;

  /* Tack layer number onto layered_name. */
  sprintf(layered_name, "%s%d", name, typex->layerno);
  i = new_ident1(OTH, layered_name, ctype, NULL, FALSE);
  i->ctype->ident = ident;

  /* Add newly created member i to symtab OTH. */
  add_ident_to_symtab1(symtab[OTH], i);
  return(i);
}

void
copy_member (IDENT *ident, MCURSOR *mcurs)
{
  IDENT *i = new_ident1(MBR, name_of(mcurs), ctype_of(mcurs),
                        members_of(mcurs), FALSE);
  add_ident_to_symlist(&ident->members, i);
}

/************************************************************************/
/*              Is member of                                            */
/************************************************************************/

/* This routine returns TRUE if field f is a member of structure s.
   FALSE otherwise. */

BOOLEAN
is_member_of (IDENT *s, char *f)
{
  MCURSOR *mcurs = new_mcursor(s);
  char    field[MAX_IDENT_LEN];
  char    *p;

#ifndef NDEBUG
  if (!(aggregate_ctype(s->ctype)))
    assertion_failed("arg 1 to is_member_of must be an aggregate");
#endif /* NDEBUG */

  if (s->members == NULL)
    return(FALSE);

  /* The string f is a field designator, but it also might include index
     offsets, such as in "next2[4]".  We need to strip off the string "[4]"
     in order to do the membership test comparison.  The first step is to
     strip is part of the field string off (DSB). */

  strcpy(field, f);
  p = strchr(field, '[');
  if (p)
    *p = '\0';

  /* Search the list of fields */

  FOREACH_MEMBER(mcurs) {
    if (strcmp(name_of(mcurs),field) == 0)
      return(TRUE);
  }
  return(FALSE);
}

/************************************************************************/ 
/*              general member cursor utilities                         */
/************************************************************************/ 

MCURSOR *
new_mcursor (IDENT *i)
{
  MCURSOR *mcurs;

  mcurs = (MCURSOR *) xmalloc(sizeof(MCURSOR));
  init_mcursor(mcurs, i);
  return(mcurs);
}

/*
   Rename these:
     (1) Add the prefix "mcursor_"
     (2) Eliminate the suffix "_of"

   Create new files:
     mcursor.[ch]

   (JAT)
*/

void
init_mcursor (MCURSOR *mcurs, IDENT *i)
{
  assert(aggregate_ctype(i->ctype));
  mcurs->ident= i;
  mcurs->home = i->members;
  mcurs->pos  = i->members->last;
}

void
mcursor_adv (MCURSOR *mcurs)
{
  mcurs->pos = mcurs->pos->prev;
}

void
mcursor_res (MCURSOR *mcurs)
{
  mcurs->pos = mcurs->home->last;
}

BOOLEAN
mcursor_eof (MCURSOR *mcurs)
{
   return(mcurs->pos != NULL);
}

char *
name_of (MCURSOR *mcurs)
{  
   return(mcurs->pos->ident->name);
}

SYMLIST *
members_of (MCURSOR *mcurs) 
{
   return(mcurs->pos->ident->members);
}

/* Return ctype of current member */

CTYPE *
ctype_of (MCURSOR *mcurs)
{
   return(mcurs->pos->ident->ctype);
}

/* Return "int" or "str" depending on the ctype of current member */

char *
type_of (MCURSOR *mcurs)
{
  CTYPE *ctype = ctype_of(mcurs);

  if (ctypematch1(ctype, int_read_only_ctype, TRUE))
    return("int");
  else if (ctypematch1(ctype, string_read_only_ctype, TRUE))
    return("str");
  else {
    warning(3, "illegal mcursor ctype, field %s must be int or str,"
            " assuming int", name_of(mcurs));
    return("int");
  }
}

void
print_fields(IDENT *i)
{
  MCURSOR *mcurs = new_mcursor(i);

  printf("name of ident: %s\n", i->name);
  FOREACH_MEMBER(mcurs) {
    printf("%s\n", name_of(mcurs));
  }
  printf("\n");
  xfree(mcurs);
}

void
position_member(MCURSOR *mcurs, char *field)
{
  assert(field != 0);
  assert(field[0] != '\0');
  FOREACH_MEMBER(mcurs) {
    if (strcmp(name_of(mcurs),field) == 0)
      return; 
  }
  error("field \"%s\" not a member of aggregate \"%s\"",
        field, mcurs->ident->name);
}

/************************************************************************/
/*              cursor or container state                               */
/************************************************************************/

/*
   The struct KC_STATE is the abstract superclass of the various
   layer-specific cursor and container structs (foo_cstruct and
   foo_kstruct) defined in the layer-specific header files (foo.h)

   new_kc_state() is called in optimize_foo() to allocate a new cursor
   state record for layer foo (foo_cstruct), and then
   lookup_kc_state() is called in subsequent cursor special operations
   to locate this cursor state record.

   new_kc_state() is called in xform_foo() to allocate a new container
   state record for layer foo (foo_kstruct), and then
   lookup_kc_state() is called in subsequent container special
   operations to locate this container state record.
*/

/* Allocate a new cursor or container state record. */

KC_STATE *
new_kc_state (TE *te, int size, int id, BOOLEAN c)
{
  KC_STATE **p = (c) ? &te->cursor_state : &te->container_state;
  KC_STATE *kc;

#if XMALLOC_DEBUG
  {
    char comment_string[20];
    sprintf(comment_string, "KC_STATE%d", size);
    kc = (KC_STATE *) xmalloc1(size, comment_string);
  }
#else
  kc = (KC_STATE *) xmalloc(size);
#endif

  /* Set all the fields of cstate and kstate variable to the value zero. (JAT) */
  memset((char *) kc, 0, size);

  kc->next = *p;
  kc->id = id;
  kc->layerno = te->layerno;
  *p = kc;

  return(kc);
}

/* Locate a previously allocated cursor or container state record. */
/* id is either a cursor or a container id. */

KC_STATE *
lookup_kc_state (TE *te, int id, char *expr, BOOLEAN c)
{
  KC_STATE *kc = (c) ? te->cursor_state : te->container_state;

  while (kc) {
    if (kc->id == id && kc->layerno == te->layerno)
      return(kc);
    kc = kc->next;
  }

#ifndef NDEBUG
  assertion_failed("no %s_state record found for %s = %s, id = %d, "
                   "layerno = %d, layer_name = %s",
                   (c) ? "c" : "k", (c) ? "cursor" : "container",
                   expr, id, te->layerno, te->layer_name);
#endif /* NDEBUG */

  /* Should be an error--no state record found. (DSB) */
  return(NULL);
}

