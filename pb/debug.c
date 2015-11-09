/* $Id: debug.c,v 45.2 1997/09/19 22:14:26 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* This file contains declarations that are useful to pb developers
   for debugging, but not useful for pb users.  Many of these
   routines print pb data structures in human-readable form. (JAT)

   These routines may be called from the debugger (eg call print_symbols()).
   These routines should not be called from P2 source code--normally any
   call to these routines in the P2 source code will be #ifdef'ed out. (JAT) */

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>   /* NULL, printf() */
#include <stdlib.h>  /* size_t */

#include "error.h"   /* ??? */
#include "io.h"      /* print1() */
#include "pb-io.h"   /* sclass_string() */
#include "pb-type.h"
#include "type.h"    /* CTYPE, IDENT */
#include "util.h"    /* MIN */
#include "xmalloc.h" /* xmalloc_atomic() */

#ifndef NDEBUG

/************************************************************************/
/*              Print the symbol table.                                 */
/************************************************************************/

/* Field width constants. */

#define BOOLEAN_FWIDTH 5
#define CTYPE_FWIDTH   20
#define EXPR_FWIDTH    35
#define INDENT_FWIDTH  4
#define SCLASS_FWIDTH  10
#define SCOPE_FWIDTH   2

/* Print the type of an expression or identifier. */

static void
sprint_ctype (char *s, const CTYPE *c)
{
  size_t j = 0;
  size_t len = 0;

  s[0] = '\0';
  while (j < c->len) {
    print1(s, &len, pclass_enum_const_string((*c->stype)[j]->pclass));
    j++;
    /* Print a space between pclass enum constant strings. */
    if (j < c->len)
      print2(s, &len, " ", 1);
  }
}

/* Front-end for sprint_ctype() */
/* Only used for debugging. (JAT) */

void
print_ctype (const CTYPE *c)
{
  char s[SPRINT_BUF_SIZE];
  sprint_ctype(s, c);
  printf("%s\n", s);
  fflush(stdout);
}

static char *
eclass_string (ECLASS eclass)
{
  switch (eclass) {
  case UND: return("UND");
  case OTH: return("OTH");
  case TDF: return("TDF");
  case FUN: return("FUN");
  case VAR: return("VAR");
  case CON: return("CON");
  case GCON: return("GCON");
  case CUR: return("CUR");
  case GCUR: return("GCUR");
  case KCUR: return("KCUR");
  case SCH: return("SCH");
  case ENC: return("ENC");
  case SUE: return("SUE");
  case MBR: return("MBR");
  case LAB: return("LAB");
  case TYP: return("TYP");
  case UNT: return("UNT");
  default:
    assertion_failed("nonprintable eclass = %d", eclass);
    return(NULL);
  }
}

static void
print_type (const IDENT *i)
{
  char s[10*MAX_CTYPE_LEN];

  switch (i->eclass) {
  case UND:
  case OTH:
  case TDF:
  case FUN:
  case CON:
  case GCON:
  case CUR:
  case GCUR:
  case KCUR:
  case SCH:
  case VAR:
  case ENC:
  case SUE:
  case MBR:
    sprint_ctype(s, i->ctype);
    assert_all_chars_printable(s);
    printf("eclass = %s        indirect_only = %-*s  ctype = %-*s",
           eclass_string(i->eclass),
           BOOLEAN_FWIDTH,
           (i->ctype->cctype != NULL && i->ctype->cctype->indirect_only)
             ? "TRUE" : "FALSE",
           CTYPE_FWIDTH,
           s);
    break;
  case LAB:
    printf("eclass = %s          %-*s",
           eclass_string(i->eclass), BOOLEAN_FWIDTH + CTYPE_FWIDTH + 2, "");
    break;
  case TYP:
    sprint_ctype(s, i->ctype);
    assert_all_chars_printable(s);
    printf("              indirect_only = %-*s  ctype = %-*s",
           BOOLEAN_FWIDTH,
           (i->ctype->cctype != NULL && i->ctype->cctype->indirect_only)
             ? "TRUE" : "FALSE",
           CTYPE_FWIDTH,
           s);
    break;
  case UNT:
    printf("(untyped)");
    break;
  default:
    printf("error");
  }
}


/* Print the type and other relevant info associated with an
   identifier (but not an expression). */

static void
print_ident (const IDENT *i)
{
  print_type(i);
  printf("  ");
  switch (i->eclass) {
  case UND:
  case OTH:
  case TDF:
  case FUN:
  case CON:
  case GCON:
  case CUR:
  case GCUR:
  case KCUR:
  case SCH:
  case VAR:
  case ENC:
  case SUE:
  case MBR:
  case LAB:
  case TYP:
    printf("sclass = %-*s  scope = %-*d  defaulted = %s",
           SCLASS_FWIDTH, sclass_string(i->sclass),
           SCOPE_FWIDTH, i->scope,
           (i->defaulted) ? "TRUE" : "FALSE");
    break;
  default:
    printf("error");
  }
}


/* Print symlist indented by string s. */

static void
print_symlist1 (char *s, const SYMLIST *symlist)
{
  PTYPE *ptype;
  PCLASS pclass;
  ENTRY *e;
  if (symlist != NULL) {
    for (e = symlist->last; e != NULL; e = e->prev) {
      printf("%s", s);
      printf("%*s", EXPR_FWIDTH-1, e->ident->name);
      if (e->ident->eclass == LAB)
        printf("   ");
      else
        printf(" : ");
      print_ident(e->ident);
      printf("\n");
      /* if e is an aggregate, print its ident */
      ptype = base_ptype(e->ident->ctype);
      pclass = ptype->pclass;
      if (aggregate_pclass(pclass)) {
        char *t = (char *) xmalloc_atomic(strlen(s) + 1 + INDENT_FWIDTH);
        sprintf(t, "%s%*s", s, INDENT_FWIDTH, "");
        /* If e is its own cident, then print its members. */
        /* We check to see if e is its own ctype->ident, so that
           we only print once the members of each aggregate type. (JAT) */
        if (e->ident->ctype->ident == e->ident) {
          printf("%*s%s%s\n", EXPR_FWIDTH, "", s, "{");
          print_symlist1(t, e->ident->ctype->ident->members);
          printf("%*s%s%s\n", EXPR_FWIDTH, "", s, "}");
        }
        xfree(t);
      }
#if 0
      printf("%s", s);
      printf("%*s", EXPR_FWIDTH-1, "");
      printf("   ");
      sprint_ctype_as_new_ctype_call(s, e->ident->ctype);
      printf("%s", s);
#endif
    }
  }
}

void
print_symlist (const SYMLIST *symlist)
{
  print_symlist1("", symlist);
  fflush(stdout);
}

void
print_symbols (void)
{
  int i, j, k;

  printf("\nSUE symbols:\n");
  for (j = scope; j >= 0 ; j--)
    for (k = 0; k < symtab[SUE]->size; k++)
      print_symlist(symtab[SUE]->table[j][k]);

  printf("\nOTH symbols:\n");
  for (j = scope; j >= 0 ; j--)
    for (k = 0; k < symtab[OTH]->size; k++)
      print_symlist(symtab[OTH]->table[j][k]);

  printf("\nENC symbols:\n");
  for (j = scope; j >= 0 ; j--)
    for (k = 0; k < symtab[ENC]->size; k++)
      print_symlist(symtab[ENC]->table[j][k]);

  printf("\nLAB symbols:\n");
  for (j = scope; j >= 0 ; j--)
    for (k = 0; k < symtab[LAB]->size; k++)
      print_symlist(symtab[LAB]->table[j][k]);

  for (i = 0; i < MAX_OCLASS+1; i++)
    if (i != SUE && i != OTH && i != ENC && i != LAB)
    {
      for (j = P2_MIN(scope, symtab[i]->scope_depth-1); j >= 0 ; j--)
        for (k = 0; k < symtab[i]->size; k++)
          if (symtab[i]->table[j][k] != NULL)
            assertion_failed("%s symbol table non-null", eclass_string(i));
    }
}

#endif /* NDEBUG */
