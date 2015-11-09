/* $Id: pb-type.c,v 45.4 1997/09/24 05:12:03 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Type system definitions. */

/* This file contains definitions needed by the type system.
   Specifically, this file contains of all of the definitions that were
   formerly contained in type.c, and are not now contained in ctype.c.
   That is, all of the type system routines that are not needed by xp. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>       /* assert() */
#include <stdio.h>        /* NULL */
#include <stdlib.h>       /* size_t */
#include <string.h>       /* memset */

#include "data-type.h"    /* str_hash() */
#include "error.h"        /* parse_error() */
#include "io.h"           /* SPRINT_BUF_SIZE */
#ifndef NDEBUG
#include "op-id.h"        /* P2_MAX_OP_ID */
#endif
#include "op-tab.h"       /* op_tab */
#include "pb-io.h"        /* pclass_string() */
#include "pb-type.h"      /* INT_CTYPE */
#include "pb-xform.h"     /* MCURSOR */
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* new_ctype(), CTYPE, NODE */
#include "util.h"         /* BOOLEAN */
#include "xmalloc.h"      /* xmalloc_atomic() */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_HASH_TABLE_SIZE     256

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

static DECL    decl_stack[MAX_SCOPE_DEPTH];  /* Declaration stack. */

/*****************************************************************************/
/*                  Scope management.                                        */
/*****************************************************************************/

/*

Effectively, what these two procedures (save_symtab and
restore_symtab) do is delete all of the symbols that were declared in
the child (inner) scope.  I could do this by looking through the
symbol table, and deleting all of the symbols that were declared with
scope equal to that of the child scope.  Since all of these symbols
will be at the front of the symbol table, this would be relatively
inexpensive.

Instead of this, however, I save in old_first, the symtab as it
existed in the parent (outer) scope before the child scope was
entered, and merely restore this.

Also, in order to simplify the task of getting formal parameters into
the symtab associated with their function body, I save in new_first a
pointer to a symtab containing all of the symbols that that are in the
child scope but weren't in it's parent. (JAT)

*/

/* Save the existing symbol table and push scope. */

void
push_scope (BOOLEAN resurrect)
{
  int i;

  scope++;
  if (scope == MAX_SCOPE_DEPTH)
    parse_error("scope stack overflow");

  if (!resurrect)
    for (i = 0; i < MAX_OCLASS+1; i++)
      if (symtab[i]->scope_depth != 1) {
        size_t size_in_bytes = symtab[i]->size * sizeof(SYMLIST *);
        memset((void *) symtab[i]->table[scope], 0, size_in_bytes);
      }
}

/* Pop scope and restore the previously saved symbol table. */

void
pop_scope (void)
{
  if (scope-- == 0)
    parse_error("scope stack underflow");
}

void
clear_dtype (void)
{
  decl->name = NULL;
  decl->pname = NULL;
  decl->dtype = EMPTY_CTYPE;
  decl->saved = FALSE;
}

void
clear_btype (void)
{
  clear_dtype();
  decl->sclass = UND;
#if 0
  decl->eclass = UND;
#endif
  decl->btype = EMPTY_CTYPE;
  decl->supp = NULL;
  decl->attribute = NULL;
  decl->initializer = NULL;
}

void
clear_decl (void)
{
  clear_btype();
#if 1
  decl->eclass = UND;
#endif
  decl->qclass = UND;
  decl->symlist = NULL; /* Formerly: decl->symtab = &symtab[OTH]; */
  decl->declared_but_unprinted_labels = NULL;
  decl->declared_but_unprinted = NULL;
  decl->verbatim_ptree = NULL;
  decl->cont_name = NULL;
  decl->typex_name = NULL;
  decl->op_vec_ptree = NULL;
}

/* Set decl btype. */
/* In order to set qclass properly, this should be the ONLY place
   where we assign decl->btype. (JAT) */

void
set_btype (CTYPE *ctype)
{
  assert_ctype_valid(ctype);
  decl->btype = ctype;
  (*decl->btype->stype)[0]->qclass = decl->qclass;
  decl->qclass = UND;
  assert_ctype_valid(decl->btype);
}

/* Convert btype to reflect declared uclass and pclass. */
/* Note that btype must have len = 0 or already be arithmetic for this
   conversion to work properly. */

void
arithmetic_btype (UCLASS uclass, PCLASS pclass)
{
#if 0
  decl->btype = new_ctype(1, uclass, pclass, decl->qclass, NULL);
#else
  if (decl->btype->len == 0)
    /* Base type. */
    set_btype(new_ctype(1, uclass, pclass, UND, NULL));
  else
  {
    /* Derrived type. */
    if (uclass != UND)
      decl->btype->uclass = uclass;
    if (pclass != IN)
      (*decl->btype->stype)[0]->pclass = pclass;
  }
#endif
}

void
save_decl (void)
{
  BOOLEAN defaulted = FALSE;
  SYMLIST **symlist;
  unsigned key;
  CTYPE *c;
  ENTRY *e;
  IDENT *i;

  if (decl->name != NULL && !decl->saved)
  {
    /* Only save declaration if it's non-null and hasn't already been saved. */
    if (decl->btype->len == 0)
    {
      /* Declaration has a null btype. */
      parse_warning(1, "%s has no type, assuming int", decl->name);
      c = int_read_only_ctype; /* Assume type to be int. */
    }
    else
    {
      /* Declaration has a non-null btype. */
      c = decl->btype;
    }
    if (decl->dtype->len != 0)
      c = copy_ctype(c);
    append(c, decl->dtype);

    /* Set symlist to the symlist in which decl should be saved. */
    if (decl->symlist != NULL)
      /* Special case: aggregate symlist. */
      symlist = decl->symlist;
    else
    {
      /* Normal case: a bucket in symtab[OTH]. */
      key = str_hash(decl->name, symtab[OTH]->size);
      symlist = &symtab[OTH]->table[scope][key];
    }

    e = symlist_lookup(*symlist, decl->name);
    if (e != NULL && e->ident->scope == scope)
    {
      /* Declaration of a symbol that already exists. */
      /* Modify existing symbol table entry */
      i = e->ident;
      if (!defaulted)
        i->ctype = c;
      if (i->defaulted)
        i->defaulted = defaulted;
      if (i->pname != NULL)
        i->pname = decl->pname;
      if (i->sclass == SPE)
        parse_warning(1, "declaration overrides special op %s", decl->name);
      if (i->sclass == UND || i->sclass == EXT || i->sclass == SPE)
        i->sclass = decl->sclass;
      if (i->supp == NULL)
        i->supp = decl->supp;
      if (i->attribute == NULL)
        i->attribute = decl->attribute;
      if (i->initializer == NULL)
        i->initializer = decl->initializer;
      add_ident_to_symlist(&decl->declared_but_unprinted, i);
    }
    else
    {
      /* Declaration of a new symbol. */
      /* Create a new symbol table entry. */
      i = new_ident(decl->eclass, decl->name, c, NULL, defaulted);
      i->sclass = decl->sclass;
      i->pname = decl->pname;
      i->supp = decl->supp;
      i->attribute = decl->attribute;
      i->initializer = decl->initializer;
      add_ident_to_symlist1(symlist, i);
    }
  }
}

void
push_decl (void)
{
  DECL *parent;

  parent = decl;
  if (decl++ == &decl_stack[MAX_SCOPE_DEPTH])
    parse_error("declaration stack overflow");
  clear_decl();
}

void
pop_decl (void)
{
  DECL *child;

  child = decl;

  if (decl-- == &decl_stack[0])
    parse_error("declaration stack underflow");

#if 1
  /* Inherit declared_but_unprinted. */

  /* The only places where child->eclass == MBR are aggregate declarations.
     There are only two places where we have aggregate declarations.
     We could easily change the calls to pop_decl in these aggregate
     declarations to another call which performs this inheritance
     of declared_but_unprinted.  Do this??? (JAT) */

  if (child->eclass == MBR) {
    ENTRY *e;
    assert(child->declared_but_unprinted_labels == NULL);
    if (child->declared_but_unprinted != NULL)
      for (e = child->declared_but_unprinted->first; e != NULL; e = e->next)
        add_ident_to_symlist(&decl->declared_but_unprinted, e->ident);
  }
#endif
}

/* If decl has a parent, return the parent.  Otherwise, return NULL. */

DECL *
parent_decl (void)
{
  DECL *parent = decl;
  return((parent-- == &decl_stack[0]) ? NULL : parent);
}

/*****************************************************************************/
/*                  Add to declared_but_unprinted.                           */
/*****************************************************************************/

static void
add_ident_to_declared_but_unprinted (IDENT *ident)
{

  /* Only add ident to decl->declared_but_unprinted if the identifier
     has not been defaulted, and if it is a aggregate member, then it
     is itself an aggregate declaration (if it is an aggregate member,
     but it is not itself an aggregate declaration, then it will be
     printed as an aggregate member). */

  if (!ident->defaulted
      && (decl->eclass != MBR || ident->eclass == SUE))
    add_ident_to_symlist(&decl->declared_but_unprinted, ident);
}

static void
add_ident_to_declared_but_unprinted_labels (IDENT *ident)
{
  add_ident_to_symlist(&decl->declared_but_unprinted_labels, ident);
}

/*****************************************************************************/
/*                  Symbol list.                                             */
/*****************************************************************************/

/* Add ident to the FRONT of symlist. */

static BOOLEAN
varchar_ctype (const CTYPE *c)
{
#if 1
  return (c != NULL
          && c->len == 2
          && ((*c->stype)[0]->pclass == ARR || (*c->stype)[0]->pclass == PTR)
          && (*c->stype)[1]->pclass == VCHA);
#else
  return(0);
#endif
}

void
add_ident_to_symlist (SYMLIST **symlist, IDENT *ident)
{
  ENTRY *e = xmalloc_object(ENTRY);
  ENTRY *t;

  e->ident = ident;
  if ((*symlist) == NULL)
  {
    /* Symlist is NULL. */
    e->next = NULL;
    e->prev = NULL;
    (*symlist) = xmalloc_object(SYMLIST);
    (*symlist)->first = e;
    (*symlist)->last = e;
  }
  else
  {
    /* Symlist is non-NULL. */
    t = (*symlist)->first;
#if 1
    /* This will find attempts to add a non-varchar string ident to
       symlist AFTER a varchar string ident has already been added,
       and cause ident to be added after the varchar string ident(s). */
    /* The intent of this code is to cause all struct fields of
       varchar string ctype to appear at the END of the struct
       (beginning of the symlist), after all fields of non-variable length. */
    if (t != NULL
        && t->ident != NULL
        && varchar_ctype(t->ident->ctype)
        && !varchar_ctype(ident->ctype))
    {
      /* Symlist CONTAINS an ident of varchar string ctype. */
      while(t->next != NULL && varchar_ctype(t->next->ident->ctype))
        t = t->next;
      e->next = t->next;
      e->prev = t;
      t->next = e;
      if (e->next != NULL)
        e->next->prev = e;
      if ((*symlist)->last == t)
        (*symlist)->last = e;
    }
    else
#endif
    {
      /* Symlist does NOT contain an ident of varchar string ctype. */
      e->prev = NULL;
      e->next = t;
      (*symlist)->first = e;
      if (t == NULL)
        (*symlist)->last = e;
      else
        t->prev = e;
    }
  }
}

/* Add ident to the FRONT of symlist, and (if ident is not defaulted)
  add ident to the symlist decl->declared_but_unprinted
  (in order to cause the eventual printing of the declaration of ident). */

void
add_ident_to_symlist1 (SYMLIST **symlist, IDENT *ident)
{
  add_ident_to_symlist(symlist, ident);
  add_ident_to_declared_but_unprinted(ident);
}

ENTRY *
symlist_lookup (const SYMLIST *symlist, const char *name)
{
  ENTRY *e;

  if (symlist != NULL)
    for (e = symlist->first; e != NULL; e = e->next) {
      if (strcmp(e->ident->name, name) == 0)
        return(e);
    }
  return(NULL);
}

/*****************************************************************************/
/*                  Symbol table.                                            */
/*****************************************************************************/

void
add_ident_to_symtab (SYMTAB *symtab, IDENT *ident)
{
  unsigned key = str_hash(ident->name, symtab->size);
  add_ident_to_symlist(&symtab->table[scope][key], ident);
}

/* Add ident to the front of symtab, and (if ident is not defaulted)
   add ident to the symlist decl->declared_but_unprinted
   (in order to cause the eventual printing of the declaration of ident). */

void
add_ident_to_symtab1 (SYMTAB *symtab, IDENT *ident)
{
  add_ident_to_symtab(symtab, ident);
  add_ident_to_declared_but_unprinted(ident);
}

void
add_label_to_symtab (char *name)
{
  unsigned key = str_hash(name, symtab[LAB]->size);
  ENTRY *e = symtab_lookup(symtab[LAB], name);
  if (e == NULL) {
    IDENT *i = new_ident(LAB, name, NULL, NULL, FALSE);
    i->scope = 1; /* All labels (except for GNU local labels) have scope 1. */
    add_ident_to_symlist(&symtab[LAB]->table[scope][key], i);
  }
}

/* GNU addition: local labels */

void
add_label_to_symtab1 (char *name)
{
  IDENT *i = new_ident(LAB, name, NULL, NULL, FALSE);
  add_ident_to_symtab(symtab[LAB], i);
  add_ident_to_declared_but_unprinted_labels(i);
}

ENTRY *
symtab_lookup (const SYMTAB *symtab, const char *name)
{
  unsigned key = str_hash(name, symtab->size);
  int i = scope;
  ENTRY *e;

  do {
    e = symlist_lookup(symtab->table[i][key], name);
    i--;
  } while (e == NULL && i >= 0);

  return(e);
}

/*****************************************************************************/
/*                  Initialize the type system.                              */
/*****************************************************************************/

/* Add all USER CALLABLE special operations to the symbol table. */

static void
add_special_ops_to_symtab (void)
{
  CTYPE *c = function_void_read_only_ctype;
  int j;

  for (j = 0; op_tab[j].name != NULL; j++)
    if (op_tab[j].user) {
      IDENT *i = new_ident1(FUN, op_tab[j].name, c, NULL, FALSE);
      add_ident_to_symtab(symtab[OTH], i);
      i->sclass = SPE;
    }
}

void
init_pb_type_system (void)
{
  int size;
  int size_in_bytes;
  int scope_depth;
  int i;

  for (i = 0; i < MAX_OCLASS+1; i++) {
    switch (i) {
    case OTH:
    case ENC:
    case SUE:
    case LAB:
      size = MAX_HASH_TABLE_SIZE;
      scope_depth = MAX_SCOPE_DEPTH;
      break;
    default:
      size = 1;
      scope_depth = 1;
      break;
    }
    size_in_bytes = size * sizeof(SYMLIST *);
    symtab[i] = xmalloc_object(SYMTAB);
    symtab[i]->table = (SYMLIST ***) xmalloc(scope_depth * sizeof(SYMLIST **));
    for (scope = 0; scope < scope_depth; scope++) {
#if XMALLOC_DEBUG
      {
        char comment_string[20];
        sprintf(comment_string, "SYMLIST*%d", size_in_bytes);
        symtab[i]->table[scope]
          = (SYMLIST **) xmalloc1(size_in_bytes, comment_string);
      }
#else
      symtab[i]->table[scope] = (SYMLIST **) xmalloc(size_in_bytes);
#endif
    }
    memset((void *) symtab[i]->table[0], 0, size_in_bytes);
    symtab[i]->size = size;
    symtab[i]->scope_depth = scope_depth;
  }

  scope = 0;
  decl = &decl_stack[0];
  clear_decl();
  add_special_ops_to_symtab();
}

/*****************************************************************************/
/*                  Unnamed structures, unions, and enumerations.            */
/*****************************************************************************/

char *
new_unnamed_sue_name (void)
{
  static int unnamed_sue_counter = 0;
  char *s = (char *) xmalloc_atomic(strlen(UNNAMED_SUE_NAME) + 10);

  sprintf(s, "P2_%s%d", UNNAMED_SUE_NAME, unnamed_sue_counter++);
  return(s);
}

/* Formerly, P2 supported only the declaration of a single container
type at a time (via the container_type keyword), rather than
declarations of container instances (via the container keyword), it
was clear what to name the transformed_element, cursor, and container
structures.  These structures were named based on the container type name.

Now that P2 supports declarations of container instances, it is not
clear what to name these structures.  We could name them after the
name of an instance, but this is awkward because if we are declaring
multiple instances (with the same element type and type expression),
we want all of the instances to share the same structures, but it is
not clear how to derrive the structure names from the instance names
(do we, for example, use the first instance name, or the last, or a
combination of all the names?)  Also, because of the structure of the
PB grammar, we need to decide on the name of the structures before we
even see the instances.

Thus, we name the transformed_element, cursor, and container
structures as a combination of the type specifier and a uniquifying
number.  If we constructed the name with a single sprintf (which we
don't because type_specifier is a parse tree rather than a string),
the sprintf would look like:

sprintf(s, "%s%d", type_specifier, container_counter++)

*/

char *
new_container_name (NODE *type_specifier)
{
  static int container_counter = 0;
  size_t len = 0;
  char   s[SPRINT_BUF_SIZE];

  s[0] = '\0';
  print_ptree1(s, &len, type_specifier);
  /* Replace spaces with underscores.
     In case, for example, type_specifier is "struct foo" */
  replace_char(s, ' ', '_');
  printf1(s, &len, "%d", container_counter++);
  return(copy_string(s));
}

/*****************************************************************************/
/*                  Concatinate symlists.                                    */
/*****************************************************************************/

/* Optimize this??? (JAT) */

#if 0
void
concat_symlist (SYMLIST **dest, SYMLIST *src)
{
  ENTRY *e;

  for (e = src->first; e != NULL; e = e->next)
    add_ident_to_symlist(dest, e->ident);
}
#endif

/*****************************************************************************/
/*                  Deep and shallow copies.                                 */
/*****************************************************************************/

void
copy_symlist (SYMLIST **dest, SYMLIST *src)
{
  ENTRY *e;

  if (src != NULL) {
    (*dest) = NULL;
    for (e = src->last; e != NULL; e = e->prev)
      add_ident_to_symlist(dest, e->ident);
  }
}

#define ALLOW_EMPTY_STRUCTS 1

IDENT *
copy_ident (IDENT *src)
{
  IDENT *dest;

  if (src == NULL)
    return(NULL);
  dest = (IDENT *) xmalloc_ident(STR);
  memcpy((char *) dest, (char *) src, sizeof_ident(src->eclass));
  dest->ctype = copy_ctype1(src->ctype, FALSE);
  if (dest->members != NULL) {
#if !ALLOW_EMPTY_STRUCTS
    dest->ctype->ident = dest;
#endif
    copy_symlist(&dest->members, src->members);
  }
#if ALLOW_EMPTY_STRUCTS
  if (aggregate_ctype(dest->ctype))
    dest->ctype->ident = dest;
#endif
  return(dest);
}

static NODE *
copy_node (NODE *src)
{
  NODE *dest;

  if (src == NULL)
    return(NULL);
  dest = (NODE *) xmalloc_node(src->narg);
  memcpy((char *) dest, (char *) src, sizeof_node(src->narg));
  return(dest);
}

NODE *
copy_ptree (NODE *src)
{
  NODE *dest;
  int i;

  dest = copy_node(src);
  if (src != NULL && src->narg != 0) {
    assert_node_valid(src);
    for (i = 0; i < src->narg; i++)
      dest->arg[i] = copy_ptree(src->arg[i]);
  }
  return(dest);
}

/*****************************************************************************/
/*                  Manipulate ctypes.                                       */
/*****************************************************************************/

void
reduce (CTYPE *c, PCLASS pclass)
{
  int i = 0;
  
#ifndef NDEBUG
  if (read_only_ctype(c))
    assertion_failed("read only ctype passed to reduce");
#endif /* NDEBUG */

  /* An empty ctype doesn't match any pclass */
  if (c->len == 0)
    parse_error("%s expected", pclass_string(pclass, NULL));

  /* Check to see if (*c->p)[0]->pclass matches the given pclass. */
  if (!pclassmatch1(c, &i, pclass))
    parse_error("%s where %s expected",
                pclass_string((*c->stype)[0]->pclass, c->ident),
                pclass_string(pclass, NULL));

  /* Shift left. */
  while (i < (c->len)-1) {
    (*c->stype)[i] = (*c->stype)[i+1];
    i++;
  }
  c->len--;

#ifndef NDEBUG
  assert_ctype_valid(c);
#endif /* NDEBUG */
}

/*****************************************************************************/
/*                  isaTYPE.                                                 */
/*****************************************************************************/

/* This routine is called by the lexer to determine if the symbol with
the given name has been declared as a typedef in the current scope. */

BOOLEAN
isaTYPE (char *name)
{
  ENTRY *e = symtab_lookup(symtab[OTH], name);
  return(e != NULL && (e->ident->eclass == TDF || e->ident->eclass == SCH));
}

/*****************************************************************************/
/*                  ident, ptree, and symbol have expected type.             */
/*****************************************************************************/

void
ident_has_expected_ctype (IDENT *ident,
                          CTYPE *expected_ctype, char *expected_ctype_name)
{
  if (ident == NULL || ident->ctype == NULL
      || !ctypematch(ident->ctype, expected_ctype))
    parse_error("%s is not a %s", ident->name, expected_ctype_name);
}

void
ptree_has_expected_ctype (NODE *ptree,
                          CTYPE *expected_ctype, char *expected_ctype_name)
{
  if (ptree == NULL || ptree->ident == NULL || ptree->ident->ctype == NULL
      || !ctypematch(ptree->ident->ctype, expected_ctype)) {
    char s[MAX_IDENT_LEN];
    sprint_ptree(s, ptree);
    parse_error("%s is not a %s", s, expected_ctype_name);
  }
}

static IDENT *
symbol_has_expected_ctype (ENTRY *entry, char *symbol_name,
                           CTYPE *expected_ctype, char *expected_ctype_name)
{
  IDENT *ident;

  if (entry == NULL)
    parse_error("undefined symbol %s where %s expected",
                symbol_name, expected_ctype_name);
  ident = entry->ident;
  ident_has_expected_ctype(ident, expected_ctype, expected_ctype_name);
  return(ident);
}

IDENT *
symlist_symbol_has_expected_ctype (SYMLIST *symlist, char *symbol_name,
                                   CTYPE *expected_ctype,
                                   char *expected_ctype_name)
{
  ENTRY *entry = symlist_lookup(symlist, symbol_name);
  IDENT *ident = symbol_has_expected_ctype(entry, symbol_name,
                   expected_ctype, expected_ctype_name);
  return(ident);
}

#if 0
/* Unused. (JAT) */
IDENT *
symtab_symbol_has_expected_ctype (SYMTAB *symtab, char *symbol_name,
                                  CTYPE *expected_ctype,
                                  char *expected_ctype_name)
{
  ENTRY *entry = symtab_lookup(symtab, symbol_name);
  IDENT *ident = symbol_has_expected_ctype(entry, symbol_name,
                                           expected_ctype, expected_ctype_name);
  return(ident);
}
#endif

/*****************************************************************************/
/*                  Init schema definition.                                  */
/*****************************************************************************/

void
init_schema_def (IDENT *sch)
{
  CTYPE  *c;
  IDENT  *i;

  c        = int_read_only_ctype;
  i        = new_ident1(MBR, "initialized", c, NULL, FALSE);
  add_ident_to_symlist(&sch->members, i);
}

/*****************************************************************************/
/*                  Init container definition.                               */
/*****************************************************************************/

void
init_container_def (IDENT *con)
{
  CTYPE  *c;
  IDENT  *i;

  /*** Add basic container fields. ***/

  /* Adding the basic container fields BEFORE fields from non-NULL
     container base type allows the container to be treated as a
     generic container. (JAT) */

  c        = int_read_only_ctype;
  i        = new_ident1(MBR, "initialized", c, NULL, FALSE);
  add_ident_to_symlist(&con->members, i);

  c        = op_vec_read_only_ctype;
  i        = new_ident1(MBR, "op_vec", c, NULL, FALSE);
  add_ident_to_symlist(&con->members, i);
}

/*****************************************************************************/
/*                  Init cursor definition.                                  */
/*****************************************************************************/

/* init_cursor_def defines the basic fields of a cursor.
   If this routine is updated, the array cursor_fields[] in field.c
   must also be updated */

void
init_cursor_def (IDENT *cur, IDENT *ele, IDENT *con)
{
  CTYPE  *c;
  IDENT  *i;

  c        = copy_ctype1(pointer_struct_read_only_ctype, FALSE);
  c->ident = ele;
  i        = new_ident1(MBR, "obj", c, NULL, FALSE);
  add_ident_to_symlist(&cur->members, i);

  if (con == NULL)
    c      = copy_ctype1(pointer_void_read_only_ctype, FALSE);
  else
    c      = copy_ctype1(pointer_container_read_only_ctype, FALSE);
  c->ident = con;
  i        = new_ident1(MBR, "con", c, NULL, FALSE);
  add_ident_to_symlist(&cur->members, i);

  c        = op_vec_read_only_ctype;
  i        = new_ident1(MBR, "op_vec", c, NULL, FALSE);
  add_ident_to_symlist(&cur->members, i);

  c        = copy_ctype1(pointer_struct_read_only_ctype, FALSE);
  c->ident = ele;
  i        = new_ident1(MBR, "restore", c, NULL, FALSE);
  add_ident_to_symlist(&cur->members, i);

  c        = int_read_only_ctype;
  i        = new_ident1(MBR, "inbetween", c, NULL, FALSE);
  add_ident_to_symlist(&cur->members, i);
}

/*****************************************************************************/
/*                  Operation list.                                          */
/*****************************************************************************/

/* Return the position of the given op and field within op_list.
   If they do not appear within op_list, return -1. */
/* Note that returning -1 is fairly common.  For example, even if for
   a given cursor, some operations (e.g., reset_start(), adv(), end_adv())
   appear in op_list, other operations (e.g., foreach()) may not
   appear in op_list. */
/* Note that the field is important, because operations ref(), iref(),
   and upd() are specific to a certain field, and thus the procedure
   that implements ref(cursor, field1) is different from the procedure
   that implements ref(cursor, field2). */

/* Why is this called "match" rather than "lookup"??? (JAT) */

int
op_list_match (const OP_LIST *op_list, const char *op, const char *field)
{
  int t;
  for (t = 0; t < op_list->size; t++)
  {
    if ((strcmp(op_list->tuple[t].op, op) == 0)
        && (field == NULL || op_list->tuple[t].ident == NULL
            || field[0] == '\0' || (op_list->tuple[t].ident)->name == NULL
            || strcmp(field, (op_list->tuple[t].ident)->name) == 0))
      {
        /* In general, we shouldn't have a hard limit on the operation
           identifier.  But, for debugging, we need a limit, so that
           paces/P2_op-vec-manager.p2 can allocate an array of strings
           to hold the names of the operations. */
#ifndef NDEBUG
        if (t > P2_MAX_OP_ID)
          assertion_failed("operation identifier %d > %d:"
            " decrease the number of fields in the element type"
            " or increase the constants P2_MAX_OP_ID in"
            " common/op-id.h",
            t, P2_MAX_OP_ID);
#endif /* NDEBUG */
        return(t);
      }
  }

#if 0
  {
    char s[SPRINT_BUF_SIZE];
    if (field == NULL)
      sprintf(s, "operation %s", op);
    else
      sprintf(s, "operation %s field %s", op, field);
    assertion_failed("op_list_match failed to find %s in op_tab", s);
  }
#endif

  return(-1);
}

/* Add an operation to op_list */
/* If operation is a field parameter, m is a member ident.
   Otherwise, m is NULL. */

static void
add_op_list (OP_LIST *op_list, int i, int id, IDENT *ident)
{
  char s[SPRINT_BUF_SIZE];

  op_list->tuple[op_list->size].i = i;
  op_list->tuple[op_list->size].op = op_tab[i].name;
  op_list->tuple[op_list->size].ident = ident;
  if (op_tab[i].param[0] == SCH)
  {
    /* The schema must be the only argument to the special operation. */
    assert(op_tab[i].num_arg == 1);
    sprintf(s, "P2_%s", op_tab[i].name);
  }
  else if (ident == NULL)
    sprintf(s, "P2_%s_id%d", op_tab[i].name, id);
  else
    sprintf(s, "P2_%s_%s_id%d", op_tab[i].name, ident->name, id);
  op_list->tuple[op_list->size].procedure = copy_string(s);
  op_list->size++;
}

/* Return TRUE iff operation has a paramater of the given ACLASS. */

BOOLEAN
op_has_aclass_param (int i, ACLASS aclass)
{
  int j;
  for (j = 0; j < op_tab[i].num_arg; j++) {
    if (op_tab[i].param[j] == aclass)
      return(TRUE);
  }
  return(FALSE);
}

/* Create a new op_list. */

OP_LIST *
new_op_list1 (CTYPE *ctype, IDENT *orig_type, ACLASS aclass, int id)
{
  OP_LIST *op_list = (OP_LIST *) xmalloc(sizeof(OP_LIST));
  MCURSOR *mcurs;
  int i = 0;

  op_list->size = 0;
  while (1) {
    if (op_tab[i].name == NULL)
      return(op_list);
    else
    {
      if (proceduralize_op(i, ctype) && op_has_aclass_param(i, aclass))
      {
        if (op_has_aclass_param(i, FIE) && orig_type != NULL)
        {
          /* Special case: op has a field parameter (e.g., ref(), upd()) */
          /* Iterate over members with supported data types (i.e., int
             or str) in original object type.  Of course, the user may
             declare a member to have a type other than int or str,
             and cast it (or expect P2 to cast it) to int or str, so be
             pretty liberal with the type matching.
             paces/frankw03.p2 is the regression test for this. (JAT) */
          mcurs = new_mcursor(orig_type);
          FOREACH_MEMBER (mcurs)
          {
#if 1
            CTYPE *member_ctype = mcurs->pos->ident->ctype;
            if (ctypematch1(member_ctype, int_read_only_ctype, FALSE)
                || ctypematch1(member_ctype, string_read_only_ctype, FALSE))
#endif
            add_op_list(op_list, i, id, mcurs->pos->ident);
          }
        }
        else
          /* Default case. */
          add_op_list(op_list, i, id, NULL);
      }
      i++;
    }
  }
}

/* Note: orig_type may be NULL, e.g. for aclass = SCH */

OP_LIST *
new_op_list (CTYPE *ctype, IDENT *orig_type, ACLASS aclass)
{
  int id;

  switch (aclass)
  {
  case CUR:
    id = ctype->cctype->cursor_id;
    break;
  case CON:
    id = ctype->cctype->container_id;
    break;
  case SCH:
    id = 0;
    break;
  default:
#ifndef NDEBUG
    assertion_failed("new_op_list called with illegal aclass %s",
      pclass_enum_const_string(aclass));
#endif /* NDEBUG */
     break;
  }
  return(new_op_list1(ctype, orig_type, aclass, id));
}

