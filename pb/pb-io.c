/* $Id: pb-io.c,v 45.3 1997/09/23 05:42:17 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Input/Output definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdarg.h>       /* va_list, ap */
#include <stdio.h>        /* NULL, vsprintf(), fputs() */
#include <stdlib.h>       /* size_t */
#include <string.h>       /* strlen() */

#include "error.h"        /* assertion_failed() */
#include "io.h"           /* print1() */
#include "lex.h"          /* MAX_IDENT_LEN */
#include "op-tab.h"       /* RCLASS */
#include "pb-io.h"
#include "pb-type.h"
#include "string-util.h"  /* delete_trailing_space1() */
#include "type.h"         /* ACLASS, IDENT */
#include "util.h"         /* BOOLEAN */
#include "xmalloc.h"      /* xmalloc_atomic() */

/*****************************************************************************/
/*                  Print strings understood by C                            */
/*****************************************************************************/

/* These routines return strings understood by C.
   Thus, these routines are called when generating C code. */

static char *
sclass_string1 (SCLASS sclass)
{
  switch (sclass) {
  case UND: return("");
  case TDF: return("typedef");
  case EXT: return("extern");
  case STA: return("static");
  case AUT: return("auto");
  case REG: return("register");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable sclass, value = %d", sclass);
#endif
    return(NULL);
  }
}

static char *
uclass_string (UCLASS uclass)
{
  switch (uclass) {
  case UND: return("");
  case SIG: return("signed");
  case UNS: return("unsigned");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable uclass, value = %d", uclass);
#endif
    return(NULL);
  }
}

/*****************************************************************************/
/*                  Print strings understood by the user                     */
/*****************************************************************************/

/* These routines return strings understood by the user
   (and not necessarily by C).
   Thus, these routines are called when printing messages for the user. */

static char *
qclass_string (QCLASS qclass)
{
  switch (qclass)
  {
    case CTQ: return("const");
    case VTQ: return("volatile");
    case UND: return("");
    default:
#ifndef NDEBUG
      assertion_failed("nonprintable qclass, value = %d", qclass);
#endif
      return(NULL);
  }
}

char *
sclass_string (SCLASS sclass)
{
  switch (sclass) {
  case UND: return("undefined");
  case SPE: return("special");
  default:  return(sclass_string1(sclass));
  }
}

static char *
pclass_string1 (PCLASS pclass, IDENT *i)
{
  char *s = (char *) xmalloc_atomic(MAX_IDENT_LEN+10);

  switch (pclass) {
  case CON:
  case GCON:
  case CUR:
  case GCUR:
  case KCUR:
  case SCH:
  case STR:
#ifndef NDEBUG
    if (i == NULL || i->ctype == NULL || i->ctype->ident == NULL
        || i->ctype->ident->name == NULL)
      assertion_failed("structure has incomplete ctype");
#endif
    sprintf(s, "struct %s", i->ctype->ident->name);
    return(s);
  case UNI:
#ifndef NDEBUG
    if (i == NULL || i->ctype == NULL || i->ctype->ident == NULL
        || i->ctype->ident->name == NULL)
      assertion_failed("union has incomplete ctype");
#endif
    sprintf(s, "union %s", i->ctype->ident->name);
    return(s);
  case VOI: return("void");
#if 0
  case CTQ: return("const");
  case VTQ: return("volatile");
#endif
  case CHA: return("char");
  case VCHA: return("char");
  case SHO: return("short");
  case ENU:
#ifndef NDEBUG
    if (i == NULL || i->ctype == NULL || i->ctype->ident == NULL
        || i->ctype->ident->name == NULL)
      assertion_failed("enumeration has incomplete ctype");
#endif
    sprintf(s, "enum %s", i->ctype->ident->name);
    return(s);
  case IN:   return("int");
  case LON:  return("long");
  case LLON: return("long long");
  case FLO:  return("float");
  case DOU:  return("double");
  case LDOU: return("long double");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable pclass, value = %d", pclass);
#endif
    return(NULL);
  }
}

char *
pclass_string (PCLASS pclass, IDENT *i)
{
  switch (pclass) {
  case TDF: return("typedef");
  case FUN: return("function");
  case ARR: return("array");
  case PTR: return("pointer");
  case PAR: return("parse tree");
  default:  return(pclass_string1(pclass, i));
  }
}

char *
aclass_string (ACLASS aclass)
{
  switch (aclass) {
  case CON: return("container");
  case GCON: return("generic container");
  case CUR: return("cursor");
  case GCUR: return("generic cursor");
  case KCUR: return("composite cursor");
  case SCH: return("schema");
  case STR: return("structure");
  case VPR: return("void pointer (void *)");
  case PAR: return("parse tree");
  case FIE: return("field");
  case IDE: return("identifier");
  case EXP: return("expression");
  case LST: return("link state");
  default:
    return(NULL);
  }
}

char *
direction_string (int direction)
{
  switch (direction) {
  case -1: return("descending");
  case  0: return("");
  case  1: return("ascending");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable direction, value = %d", direction);
#endif
    return(NULL);
  }
}

/*****************************************************************************/
/*                  enum constant strings                                    */
/*****************************************************************************/

char *
rclass_enum_const_string (RCLASS rclass)
{
  switch (rclass) {
  case DS:  return("DS");
  case TOP: return("TOP");
  case MEM: return("MEM");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable rclass, value = %d", rclass);
#endif
    return(NULL);
  }
}

/*****************************************************************************/
/*                  Print declarations.                                      */
/*****************************************************************************/

void
sprint_decl3 (char *s, size_t *len, int j, IDENT *i)
{
  char *leftp, *rightp;
  PTYPE *ptype;
  PCLASS pclass;
  QCLASS qclass;

  if (j == 0)
  {
    /* Normal cases. */

    if (i->pname != NULL)
      print1(s, len, i->pname);
    else if (i->name != NULL)
      print1(s, len, i->name);

    /* Special case for printing error messages
       where i has a ctype, but not a name. (JAT) */

    delete_trailing_space1(s, len);
  }
  else if (j > 0)
  {
    j--;
    {
      ptype = (*i->ctype->stype)[j];
      assert_ptype_valid(ptype);
      pclass = ptype->pclass;
      qclass = ptype->qclass;
      if ((j == 0)
          || (pclass == PTR)
          || (pclass == (*i->ctype->stype)[j-1]->pclass)
#if 0
          || ((*i->ctype->stype)[j-1]->pclass == CTQ)
          || ((*i->ctype->stype)[j-1]->pclass == VTQ)
#endif
         )
      {
        /* Don't print (redundant or illegal) parenthesis. */
        leftp = "";
        rightp = "";
      }
      else
      {
        /* Print (possibly redundant) parenthesis. */
        leftp = "(";
        rightp = ")";
      }
      /* Print derrived type. */
      switch (pclass)
      {
      case FUN: 
        print1(s, len, leftp);
        sprint_decl3(s, len, j, i);
        print1(s, len, rightp);
        /* Don't print redundant function declaration parenthesis. */
        if (j == i->ctype->len-2 || (*i->ctype->stype)[j+1]->pclass != FUN) {
          print2(s, len, " ( ", 3);
          print_ptree1(s, len, ptype->supp);
          print2(s, len, " )", 2);
        }
        break;
      case ARR:
        print1(s, len, leftp);
        sprint_decl3(s, len, j, i);
        print1(s, len, rightp);
        print2(s, len, "[", 1);
        print_ptree1(s, len, ptype->supp);
        print2(s, len, "]", 1);
        break;
      case PTR:
        print2(s, len, "*", 1);
        /* Print type qualifier. */
        if (qclass != UND)
        {
          print1(s, len, qclass_string(qclass));
          print2(s, len, " ", 1);
        }
        print1(s, len, leftp);
        sprint_decl3(s, len, j, i);
        print1(s, len, rightp);
        break;
#if 0
      case CTQ:
      case VTQ:
        /* Here, I assume that type qualifiers do not
           need to be parenthesized (JAT) */
        print1(s, len, pclass_string1(pclass, i));
        print2(s, len, " ", 1);
        sprint_decl3(s, len, j, i);
        break;
#endif
      default:
#ifndef NDEBUG
        assertion_failed("nonprintable derrived type pclass value = %d", pclass);
#endif
        break;
      }
    }    
  }
}

void
sprint_decl2 (char *s, size_t *len, IDENT *i)
{
  PTYPE *ptype;
  PCLASS pclass;
  QCLASS qclass;
  ENTRY *e;

#ifndef NDEBUG
  if (i->ctype->len == 0)
    assertion_failed("ctype len value = 0");
#endif

  ptype = base_ptype(i->ctype);
  assert_ptype_valid(ptype);
  pclass = ptype->pclass;
#if 0
  qclass = decl->qclass;
#else
  qclass = ptype->qclass;
#endif  

  /* Print type qualifier. */
  if (qclass != UND)
  {
    print1(s, len, qclass_string(qclass));
#if 0
    /* Reset decl->qclass. */
    decl->qclass = UND;
#endif
    print2(s, len, " ", 1);
  }

  /* Print base type */
  if (!i->defaulted) {
    /* Print base type. */
    print1(s, len, pclass_string1(pclass, i));
    print2(s, len, " ", 1);
  }
  
  if ((pclass == ENU) && (i->ctype->ident == i)) {
    /* Print enum declaration. */
    print2(s, len, "{ ", 2);
    print_ptree1(s, len, i->supp); /* print enumeration body */
    print2(s, len, " }", 2);
  }
  else if ((i->ctype->ident == i) && aggregate_pclass(pclass)) {
    /* Print aggregate declaration. */
    print2(s, len, "{\n", 2);
    if (i->members != NULL)
      for (e = i->members->last; e != NULL; e = e->prev) {
        sprint_decl1(s, len, e->ident, TRUE);
        print2(s, len, "\n", 1);
      }
    print2(s, len, "}", 1);
  }
  else
    /* Print derrived type. */
    sprint_decl3(s, len, (i->ctype->len)-1, i);
  
  if ((pclass != ENU) && (i->supp != NULL)) {
    /* Print bit field */
    print2(s, len, " : ", 3);
    print_ptree1(s, len, i->supp);
  }
  
  if (i->attribute != NULL) {
    /* Print GNU __attribute__ */
    print2(s, len, " ", 1);
    print_ptree1(s, len, i->attribute);
  }

  if (i->initializer != NULL) {
    /* Print initializer */
    print2(s, len, " = ", 3);
    print_ptree1(s, len, i->initializer);
  }
}

/* Print the declaration iff it is worth printing. */

void
sprint_decl1 (char *s, size_t *len, IDENT *i, BOOLEAN print_semicolon)
{
  CTYPE *ctype = i->ctype;

#ifndef NDEBUG
  assert_ctype_valid(ctype);
#endif

  /* We don't want to print anything if i is a forward reference, since
  a forward reference (although creating an entry in the symbol table)
  is not a declaration. */

#ifndef NDEBUG
  if (i->forward)
    assertion_failed("tried to print forward reference %s", i->name);
  if (ctype == NULL)
    assertion_failed("identifier has null ctype");
#endif

  /* Only print something if there is anything worth printing. */
  
  if (!i->defaulted
      || i->sclass != UND
      || ctype->uclass != ERR
      || i->initializer != NULL) {
    
    char *t;

    /* Print sclass (ie storage class, eg register). */
    t = sclass_string1(i->sclass); 
    if (strcmp(t, "") != 0) {
      print1(s, len, t);
      print2(s, len, " ", 1);
    }
    
    /* Print uclass (ie signed/unsigned). */
    t = uclass_string(ctype->uclass);
    if (strcmp(t, "") != 0) {
      print1(s, len, t);
      print2(s, len, " ", 1);
    }
    
    /* Print rest of declaration. */
    sprint_decl2(s, len, i);
    if (print_semicolon)
      print2(s, len, ";", 1);
  }
}

/* Print to string. */

static void
esprint_decl (char *s, IDENT *i)
{
  size_t len = strlen(s);
  sprint_decl1(s, &len, i, TRUE);
  assert_all_chars_printable(s);
}

void
sprint_decl (char *s, IDENT *i)
{
  s[0] = '\0';
  esprint_decl(s, i);
}

/* Print to stdout. */

void
print_decl (IDENT *i)
{
  size_t len = 0;
  sprint_decl1(NULL, &len, i, TRUE);
}

