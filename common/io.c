/* $Id: io.c,v 45.3 1997/09/20 03:42:19 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Input/Output definitions. */

/* This file contains some of the definitions that were formerly made
   in io.c.  Specifically, this file contains only the input/output
   definitions that are needed by xp (as well as pb). (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <stdarg.h>       /* va_list */
#include <string.h>       /* strlen */

#ifndef P2_NDEBUG
#include "error.h"        /* assertion_failed() */
#endif /* P2_NDEBUG */

#include "io.h"           /* SPRINT_BUF_SIZE */
#include "string-util.h"  /* delete_trailing_space() */
#include "type.h"
#include "util.h"         /* FALSE */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

int print_liner_pragma = FALSE; /* Used in print_ptree2. (BJG) */

/*****************************************************************************/
/*                  Print a string to the end of a string.                   */
/*****************************************************************************/

/* Unformatted. */

void
esprint (char *s1, size_t *len1, const char *s2, size_t len2)
{
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (s1 != NULL && s2 != NULL
      && (*len1 != strlen(s1) || len2 != strlen(s2)))
    assertion_failed("inconsistent string lengths in sprint");
#endif /* P2_NEDEBUG */
  {
    size_t len = *len1 + len2;
    if (len > SPRINT_BUF_SIZE)
      assertion_failed("string length %u > SPRINT_BUF_SIZE %u",
                       len, SPRINT_BUF_SIZE);
  }
#endif /* NDEBUG */

  strcpy(&s1[*len1], s2);
  *len1 = *len1 + len2;
}

/* Formatted. */

/* Note that the use of this procedure should be avoided, since it
   makes two calls to strlen, including one to strlen(s1), which can be
   quite slow. (JAT) */

void
esprintf (char *s1, const char *format, ...)
{
  va_list args;
  char    s2[SPRINT_BUF_SIZE];
  size_t  len1;

#ifndef NDEBUG
  if (s1 == NULL || format == NULL)
    assertion_failed("NULL string passed to esprintf");
#endif /* NDEBUG */

  va_start(args, format);
  vsprintf(s2, format, args);
  va_end(args);
  len1 = strlen(s1); /* Slow. */
  esprint(s1, &len1, s2, strlen(s2));
}

/*****************************************************************************/
/*                  Print a string to stdout or to the end of a string.      */
/*****************************************************************************/

/*
   If s1 == NULL, print s2 to stdout.
   If s1 != NULL, append s2 to the end of s1, and modify len1.
*/

void
print2 (char *s1, size_t *len1, const char *s2, size_t len2)
{
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (s1 != NULL && s2 != NULL
      && (*len1 != strlen(s1) || len2 != strlen(s2)))
    assertion_failed("inconsistent string lengths in print");
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
    
  if (s1 == NULL)
    fputs(s2, stdout);
  else
    esprint(s1, len1, s2, len2);
}

void
print1 (char *s1, size_t *len1, const char *s2)
{
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (s1 != NULL && *len1 != strlen(s1))
    assertion_failed("inconsistent string lengths in sprint");
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */

  if (s1 == NULL)
    fputs(s2, stdout);
  else
    esprint(s1, len1, s2, strlen(s2));
}

void
printf1 (char *s1, size_t *len1, const char *format, ...)
{
  va_list args;
  char    s2[SPRINT_BUF_SIZE];

#ifndef NDEBUG
  if (s1 == NULL || format == NULL)
    assertion_failed("NULL string passed to printf1");
#endif /* NDEBUG */

  va_start(args, format);
  vsprintf(s2, format, args);
  va_end(args);
  print1(s1, len1, s2);
}

/*****************************************************************************/
/*                  Assertions                                               */
/*****************************************************************************/

/* Call assertion_failed if the string s contains a non-printing character. */
/* This routine has proven useful for detecting memory errors. (JAT) */

void
assert_all_chars_printable (const char *s)
{
#ifndef NDEBUG
  int i = 0;
  char c;

  while ((c = *s) != '\0') {
    if ((c > 126) || ((c < 32) && (c != '\n') && (c != '\t') && (c != '\f')))
      assertion_failed("non-printing char %d at index %d in string %s",
        c, i, s);
    i++;
    s++;
  }
#endif /* NDEBUG */
}

/*****************************************************************************/
/*                  Print parse trees                                        */
/*****************************************************************************/

static void
print_ptree2 (char *s, size_t *len, const NODE *n)
{
  static int last_line_number_printed = 1;

#ifndef NDEBUG
  assert_node_valid(n);
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (s != NULL && *len != strlen(s))
    assertion_failed("inconsistent string lengths in print_ptree2");
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
    
  if (n != NULL) {
    if (n->narg == 0 && n->ident != NULL && n->ident->name != NULL) {
      char *name = n->ident->name;
      size_t name_len = strlen(name);
      if (name_len > 0) {
        char c = name[name_len-1];

        /* This code gets executed for pb & ddl.  print_liner_pragma
           is FALSE for xp, which has no pragma line directives. (BJG) */
        if (print_liner_pragma
            && (s == NULL)
            && (n->line_number != 0)
            && (n->line_number != last_line_number_printed)) { 
          last_line_number_printed = n->line_number;
          printf("\n#pragma liner I %d\n", last_line_number_printed);
        }

        print2(s, len, name, name_len);
        /* Add a newline after semi-colon or left or right brace. */
        if (c == ';' || c == '{' || c == '}') {
          print2(s, len, "\n", 1);
        }
        /* Add a space if the string does not end with a newline. */
        else if (c != '\n') {
          print2(s, len, " ", 1);
        }
      }
    }
    else {
      int j;
#ifndef NDEBUG
      if ((n->narg < 0) || (n->narg > MAX_NODE_ARG))
        assertion_failed("illegal node narg value = %d", n->narg);
#endif /* NDEBUG */
      for (j = 0; j < n->narg; j++)
        print_ptree2(s, len, n->arg[j]);
    }
  }
}

void
print_ptree1 (char *s, size_t *len, const NODE *n)
{
  if (n != NULL) {
    print_ptree2(s, len, n);
    delete_trailing_space1(s, len);
  }
}

void
esprint_ptree (char *s, const NODE *n)
{
  /* Must function correctly when n == NULL,
     so that caller does not have to check for this condition. */
  if (n != NULL) {
    /* Only do something if n != terminal(UNT, "", NULL) */
    if (n->narg != 0 || n->ident != NULL || strcmp(n->ident->name, "") != 0) {
      size_t len = strlen(s);
      print_ptree1(s, &len, n);
    }
  }
}

/* Print to string. */

void
sprint_ptree (char *s, const NODE *n)
{
  s[0] = '\0';
  esprint_ptree(s, n);
}

/* Print to stdout. */

void
print_ptree (const NODE *n)
{
  /* Must function correctly when n == NULL,
     so that caller does not have to check for this condition. */
  if (n != NULL) {
    /* Only do something if n != terminal(UNT, "", NULL) */
    if (n->narg != 0 || n->ident != NULL || strcmp(n->ident->name, "") != 0) {
      size_t len = 0;
      print_ptree1(NULL, &len, n);
    }
  }
  fflush(stdout);
}

/*****************************************************************************/
/*                  enum constant strings                                    */
/*****************************************************************************/

char *
qclass_enum_const_string (QCLASS qclass)
{
  switch (qclass)
  {
    case CTQ: return("CTQ");
    case VTQ: return("VTQ");
    case UND: return("UND");
    default:
#ifndef NDEBUG
      assertion_failed("nonprintable qclass, value = %d", qclass);
#endif /* NDEBUG */
      return(NULL);
  }
}

static char *
uclass_enum_const_string (UCLASS uclass)
{
  switch (uclass) {
  case UND: return("UND");
  case SIG: return("SIG");
  case UNS: return("UNS");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable uclass, value = %d", uclass);
#endif /* NDEBUG */
    return(NULL);
  }
}

char *
pclass_enum_const_string (PCLASS pclass)
{
  switch (pclass) {
  case UND: return("UND");
  case OTH: return("OTH");
  case TDF: return("TDF");
  case FUN: return("FUN");
  case CON: return("CON");
  case GCON: return("GCON");
  case CUR: return("CUR");
  case GCUR: return("GCUR");
  case KCUR: return("KCUR");
  case SCH: return("SCH");
  case STR: return("STR");
  case UNI: return("UNI");
  case VOI: return("VOI");
#if 0
  case CTQ: return("CTQ");
  case VTQ: return("VTQ");
#endif
  case ARR: return("ARR");
  case PTR: return("PTR");
  case CHA: return("CHA");
  case VCHA: return("VCHA");
  case SHO: return("SHO");
  case ENU: return("ENU");
  case IN:  return("IN");
  case LON: return("LON");
  case LLON: return("LLON");
  case FLO: return("FLO");
  case DOU: return("DOU");
  case LDOU: return("LDOU");
  default:
#ifndef NDEBUG
    assertion_failed("nonprintable pclass, value = %d", pclass);
#endif /* NDEBUG */
    return(NULL);
  }
}

/*****************************************************************************/
/*                  sprint ctype as a new ctype call                         */
/*****************************************************************************/

/* Given a string and a ctype, print into the string a call to
   new_ctype that (if compiled and executed) would create a ctype
   identical to the original ctype. */

void
sprint_ctype_as_new_ctype_call (char *s, const CTYPE *ctype)
{
  PTYPE *ptype;
  size_t len = 0;
  int i;

  s[0] = '\0';

  /* Special cases. */

  if (ctypematch1(ctype, int_read_only_ctype, TRUE)) {
    print1(s, &len, "int_read_only_ctype");
  }

  /* Normal case. */

  else {
    printf1(s, &len, "new_ctype(%d, %s",
            ctype->len, uclass_enum_const_string(ctype->uclass));
    for (i = 0; i < ctype->len; i++)
    {
      ptype = (*ctype->stype)[i];
      assert(ptype != NULL);
      /* pclass */
      print2(s, &len, ", ", 2);
      print1(s, &len, pclass_enum_const_string(ptype->pclass));
      /* qclass */
      print2(s, &len, ", ", 2);
      print1(s, &len, qclass_enum_const_string(ptype->qclass));
      /* supp */
      print2(s, &len, ", ", 2);
      if (ptype->supp == NULL)
        print2(s, &len, "NULL", 4);
      else
        print_ptree1(s, &len, ptype->supp);
    }
    print2(s, &len, ")", 1);
  }
}
