/* $Id: data-type.c,v 45.1 1997/09/19 07:50:39 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Data type definitions. */
/* Query parsing and processing definitions. */
/* Analogous to paces/P2.c */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdio.h>            /* NULL */
#include <string.h>           /* strcmp() */

#include "data-type.h"        /* BOUNDS */
#include "error.h"            /* error() */
#include "io.h"               /* SPRINT_BUF_SIZE */
#include "lex.h"              /* WHITESPACE_CHARACTERS, relational_operator() */
#include "limits.h"           /* WORD_BIT */
#include "op-tab.h"           /* OP_TAB */
#include "pb-type.h"          /* symtab_lookup() */
#include "pb-xform.h"         /* init_mcursor() */
#include "string-util.h"      /* replace_string(), copy_string() */
#include "typex.h"            /* top_node() */
#include "util.h"             /* VOID_FUNC */
#include "xmalloc.h"          /* xfree() */
#include "xform.h"            /* TE */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

OP_TAB type_tab[] = {
      { "int",
        sizeof(int),
        bounds_impact_int,
        is_literal_int,
        (SHORT_FUNC) 0, "",
        int_hash, "P2_int_hash",
        {
        {"==", "P2_f == P2_v"},  
        {"!=", "P2_f != P2_v"},
        {">",  "P2_f >  P2_v"},
        {">=", "P2_f >= P2_v"},
        {"<",  "P2_f <  P2_v"},
        {"<=", "P2_f <= P2_v"},
        {"",   ""}} /* Terminator. */
      },
      { "str",
        100,
        bounds_impact_str,
        is_literal_str,
        str_hashcmp, "P2_str_hashcmp", 
        str_hash, "P2_str_hash",
        {
        {"==", "strcmp(P2_f,P2_v) == 0"},  
        {"!=", "strcmp(P2_f,P2_v) != 0"},
        {">",  "strcmp(P2_f,P2_v) >  0"},
        {">=", "strcmp(P2_f,P2_v) >= 0"},
        {"<",  "strcmp(P2_f,P2_v) <  0"},
        {"<=", "strcmp(P2_f,P2_v) <= 0"},
        {"",   ""}} /* Terminator. */
      },
      /* Terminates with null below. */
      { "",
        0,
        (VOID_FUNC) 0,
        (BOOL_FUNC) 0,
        (SHORT_FUNC) 0, "",
        (UNSIGNED_FUNC) 0, "",
        { { "", "" } }
      } 
    };

/*****************************************************************************/
/*                  Predicate manupulation.                                  */
/*****************************************************************************/

/* pre_and(p1,p2) sets p1 = p2 && p1 if p1 is nonull else p1 = p2 */

void
pre_and (char *p1, const char *p2)
{
#if 0
  char temp[ARG_STR_LEN];

  if (strcmp(p1, "") == 0 || strcmp(p1, "1") == 0)
    strcpy(p1, p2);
  else {
    strcpy(temp, p2);
    strcat(temp, " && ");
    strcat(temp, p1);
    if (strlen(temp) >= ARG_STR_LEN)
      error("predicate string too long");
    strcpy(p1, temp);
  }
#else
  if (p1[0] == '\0' || strcmp(p1, "1") == 0)
    strcpy(p1, p2);
  else {
    char *t = copy_string(p1);
    strcpy(p1, p2);
    strcat(p1, " && ");
    strcat(p1, t);
    xfree(t);
  }
#endif
}

/* post_and(p1,p2) sets p1 = p1 && p2 if p1 is nonull else p1 = p2 */

void
post_and (char *p1, const char *p2)
{
  if (p1[0] == '\0' || strcmp(p1,"1") == 0)
    strcpy(p1, p2);
  else {
    strcat(p1, " && ");
    strcat(p1, p2);
  }
}

/* pre_or(p1,p2) sets p1 = p2 || p1 if p1 is nonull else p1 = p2 */

void
pre_or (char *p1, const char *p2)
{
#if 0
  char temp[ARG_STR_LEN];

  if (strcmp(p1, "") == 0)
    strcpy(p1, p2);
  else {
    strcpy(temp, p2);
    strcat(temp, " || ");
    strcat(temp, p1);
    if (strlen(temp) >= ARG_STR_LEN)
      error("predicate string too long");
    strcpy(p1, temp);
  }
#else
  if (p1[0] == '\0')
    strcpy(p1, p2);
  else {
    char *t = copy_string(p1);
    strcpy(p1, p2);
    strcat(p1, " || ");
    strcat(p1, t);
    xfree(t);
  }
#endif
}

/* post_or(p1,p2) sets p1 = p1 || p2 if p1 is non-NULL else p1 = p2 */

void
post_or (char *p1, const char *p2)
{
  if (p1[0] == '\0')
    strcpy(p1, p2);
  else {
    strcat(p1, " || ");
    strcat(p1, p2);
  }
}

/* nest(p1) sets p1 = (p1) if p1 is non-NULL else p1 = null; */

void
nest (char *p1)
{
  char temp[ARG_STR_LEN];

  if (p1[0] == '\0')
    return;
  else {
    strcpy(temp, "(");
    strcat(temp, p1);
    strcat(temp, ")");
    if (strlen(temp) >= ARG_STR_LEN)
      error("predicate string too long");
    strcpy(p1, temp);
  }
}

/*****************************************************************************/
/*                  Bind predicate                                           */
/*****************************************************************************/

/* Replace all cursor references in place. */
/* Works both for normal and composite cursor member cursor references. */

/*
   Replacements are as follows:
   Old String   New String
   ----------   ----------
     "$."       "(cursor).obj->"
     "$:"       "(cursor)."
     "$"        "(cursor)"
     "$foo."    "(cursor . foo).obj->"
     "$foo:"    "(cursor . foo)."
     "$foo"     "(cursor . foo)"
*/
/* This routine does not handle partition. (DSB) */

void
replace_cursor_refs (const TE *te, char *cursor, char *expanded_predicate)
{
/* 
   Case 1: Clause NOT of the form $b.w, but rather of the form $.w
   (i.e. NULL member_cursor_alias).
   Cursor name may or may not contain a "."

   Input:
     cursor = "c"
                1 (s1 == NULL)
     expanded_predicate = "x == $.w"
                                24 (s3 == s4)
   Internal:
     len = 0
     member_cursor_alias = ""
     expanded_cursor = "c"

   Output:
     expanded_predicate = "x == (c).obj->w"
*/
/*
   Case 2: Clause of the form $b.w (i.e. non-NULL member_cursor_alias b).
   Cursor name does NOT contain a "." (i.e., a cursor argument (*P2_curs0)
   to a proceduralized special operation).

   Input:
     cursor = "(*P2_curs0)"
                          1 (s1 == NULL)
     expanded_predicate = "(*P2_curs0).v == $b.w"
                                            234

   Problem:
     We don't know what cursor (*P2_curs0) refers to (e.g., $a, $b, $c).
     (Can't assume it refers to $b)
   Solution:
     * Put a "composite cursor struct" _kcur pointer in every composite
         cursor member cursor.

   Internal:
     len != 0
     member_cursor_alias = "b"
     expanded_cursor = "(*P2_curs0).kcur->b"

   Output:
     expanded_predicate = ???
*/
/*
   Case 3: Clause of the form $b.w (i.e. non-NULL member_cursor_alias b).
   Cursor name contains a "." (composite cursor member cursor).

   Input:
     cursor = "( * c ) . b"
                       1
     expanded_predicate = "(( * c ) . a).obj->v == $b.w"
                                                   234
   Internal:
     len != 0
     member_cursor_alias = "b"
     expaned_cursor = "( * c ) . b"

   Output:
     expanded_predicate = "(( * c ) . a).obj->v = (( * c ) . b).obj->w"
*/
  
  char *s1, *s2, *s3, *s4;
  int  len;                                /* length of cursor alias */
  char member_cursor_alias[MAX_IDENT_LEN]; /* cursor alias (e.g. a in $a.w) */
  char composite_cursor[MAX_IDENT_LEN];    /* cursor prefix before last '.' */
  char expanded_cursor[ARG_STR_LEN];       /* expanded cursor */
  char sold[MAX_IDENT_LEN+10];
  char snew[MAX_IDENT_LEN+10];

  assert(te != NULL);

  /* s1 = the position of the last '.' in cursor or
     NULL if cursor does not contain a '.' */
  s1 = strrchr(cursor, '.');

  /* foreach member_cursor_alias */
  s2 = strchr(expanded_predicate, '$');
  while (s2 != NULL) {
    s3 = s2+1;
    s4 = s3 + identifier_span(s3);
    if (s4 == NULL)
      s4 = s3 + strlen(s3);
    len = s4-s3;
    assert(len < MAX_IDENT_LEN);
    strncpy(member_cursor_alias, s3, len);
    member_cursor_alias[len] = '\0';

    if (len == 0) {
      /* Case 1 */
      strcpy(expanded_cursor, cursor);
    }
    else if (s1 == NULL) {
      /* Case 2 */
      if (te_requires_kcur(top_node(te)))
        /* kcur layer present. */
        /* expanded_cursor = (cursor).kcur->member_cursor_alias */
        sprintf(expanded_cursor, "(%s).kcur->%s", cursor, member_cursor_alias);
      else {
        /* kcur layer not present. */
        /* Can not expand cursor. */
        error("typex requires kcur layer");
      }
    }
    else {
      /* Case 3 */
      /* composite_cursor = the prefix of cursor preceeding the last '.' */
      strncpy(composite_cursor, cursor, s1-cursor);
      composite_cursor[s1-cursor] = '\0';
      /* expanded_cursor = composite_cursor . member_cursor_alias */
      sprintf(expanded_cursor, "%s.%s", composite_cursor, member_cursor_alias);
    }

    switch (s4[0]) {
    case '.':
      sprintf(sold, "$%s.", member_cursor_alias);
      sprintf(snew, "(%s).obj->", expanded_cursor);
      break;
    case ':':
      sprintf(sold, "$%s:", member_cursor_alias);
      sprintf(snew, "(%s).", expanded_cursor);
      break;
    default:
      sprintf(sold, "$%s", member_cursor_alias);
      sprintf(snew, "(%s)", expanded_cursor);
    }

    replace_string_inplace1(s2, sold, snew, 1);
    s2 = strchr(s4, '$');
  }
}

/* Bind the $ references in predicate to the given cursor.
   If predicate is the empty string, then return "1" */

#define POST_AND 1

char *
bind_predicate1 (const TE *te, char *cursor, IDENT *ident, char *predicate)
{
  char     temp[SPRINT_BUF_SIZE];
  char     clause[ARG_STR_LEN];
  char     field[ARG_STR_LEN];
  char     relation[ARG_STR_LEN];
  char     value[ARG_STR_LEN];
  char     expanded_predicate[SPRINT_BUF_SIZE];
  BOOLEAN  found_type;
  char     *p;
  
#ifndef NDEBUG
  assert(te != NULL);
  assert(predicate != NULL);
#endif /* NDEBUG */

  /* If we have the null predicate, return a normalized null predicate
     (that is, the string "1"). */

  if (predicate[0] == '\0')
    return(copy_string("1"));

  /* This routine should be re-entrant.
     The following test is an easy way to make sure it is:
     We don't have to do anything if the predicate contains no dollar signs.
     (JAT) */
  
  if (strchr(predicate, '$') == NULL)
    return(copy_string(predicate));
  
  /* Convert predicate clause by clause.
     Use string accumulator expanded_predicate. (DSB) */
  
  expanded_predicate[0] = '\0';
  p = predicate;
  while (*p != '\0') {
    next_clause(&p, clause, field, relation, value);
    if (field[0] == '\0' || (field[1] != '.' && field[1] != ':'))
    {
      /*** Uninterpretable clause. ****/

      /* Check for errors. */
      if (strcmp(clause, "= ") == 0)
        parse_error("predicate \"%s\" contains assignment operator (\"=\")",
          predicate);

      /* Add the clause to the expanded_predicate. */
#if POST_AND
      post_and(expanded_predicate, clause);
#else
      pre_and(expanded_predicate, clause);
#endif
    }

    else
    {
      /*** Interpretable clause. ***/
      
      MCURSOR  mcurs;
      char     fld[ARG_STR_LEN];
      BOOLEAN  found_op;
      OP       *o;
      OP_TAB   *r;
      char     *t;

      /*** Find the table row that defines the type of this field. ***/

      init_mcursor(&mcurs, ident);

      strcpy(fld, field+2); /* skip over $. or $: */
      position_member(&mcurs, fld);
      t = type_of(&mcurs);
      found_type = FALSE;
      /* Foreach row in type_tab. */
      for (r = &type_tab[0]; r->typename[0] != '\0'; r++) {
        if (strcmp(t, r->typename) == 0) {
          found_type = TRUE;
          break;
        }
      }
      if (!found_type)
        error("cannot find type %s in op_tab", t);
      
      /* Find the appropriate operation. */

      found_op = FALSE;
      /* Foreach operation. */
      for (o = &r->op[0]; o->name[0] != '\0'; o++) {
        if (strcmp(relation, o->name) == 0)  {
          strcpy(temp, o->cs);
          replace_string(temp, "P2_f", field, temp);
          replace_string(temp, "P2_v", value, temp);
          found_op = TRUE;
          break;
        }
      }
      if (!found_op) 
        error("cannot translate operation %s", relation);

#if POST_AND
      post_and(expanded_predicate, temp);
#else
      pre_and(expanded_predicate, temp);
#endif
    }
  }

  /* Convert all cursor references to their correct string
     ("$." for element references and "$:" for cursor field references).
     (DSB) */

  replace_cursor_refs(te, cursor, expanded_predicate);

  return(copy_string(expanded_predicate));
}

/* Formerly, this routine modified predicate in-place, and returned
   void.  This was a bad idea, however, since once bound, we cannot
   determine the structure of the predicate.  For example,
   define_bounds() and use_layer() return incorrect results for bound
   predicates. (JAT) */

char *
bind_predicate (const TE *te, char *cursor, char *obj_type, char *predicate)
{
  /* Convert name of obj_type into an ident pointer. */
  ENTRY *entry = symtab_lookup(symtab[SUE], obj_type);
  IDENT *ident;

  assert(te != NULL);
  if (entry == NULL)
    error("cannot find obj_type \"%s\" in symbol table", obj_type);
  ident = entry->ident;
  return(bind_predicate1(te, cursor, ident, predicate));
}

/*****************************************************************************/
/*                  Split predicate                                          */
/*****************************************************************************/

/* split_predicate(prim, pred, pp, sp, rp) */

/* This routine splits predicate "pred" into "pp && sp && rp"
   given abstract record type a and partitioning field
   pfield.  pp is predicate over primary fields, 
   sp is predicate over secondary fields and 
   rp is the residual (DSB) */

void
split_predicate (IDENT *prim, char *pred, char *pp, char *sp, char *rp)
{ 
  char   *predicate = pred;
  char   field[ARG_STR_LEN];
  char   relation[ARG_STR_LEN];
  char   value[ARG_STR_LEN];
  char   term[ARG_STR_LEN];

   /* Step 1:  initialize resultant strings */

   *pp = '\0';
   *sp = '\0';
   *rp = '\0';

   /* Step 2:  examine each clause */

   while (*predicate != '\0') {
      next_clause(&predicate, NULL, field, relation, value);
      if (field[0] == '\0') {
         /* uninterpretable clause */

         post_and(rp, value);
      }
      else {
          /* reform predicate */

          sprintf(term, "%s %s %s", field, relation, value);

          /* Add to appropriate predicate.
             The 2+ is needed to skip over the $. characters in field. (DSB) */
 
          if (is_member_of(prim, 2+field))
             post_and(pp,term);
          else
             post_and(sp,term);
      }
   }
   if (*pp == '\0')
      strcpy(pp, "1");
   if (*sp == '\0')
      strcpy(sp, "1");
   if (*rp == '\0')
      strcpy(rp, "1");
}

/*****************************************************************************/
/*                  Separate predicate.                                      */
/*****************************************************************************/

/* separate_predicate(p, fld, single, ipred, rpred)
   factors a predicate p into two parts: given indexed field
   fld, all clauses associated with fld are in ipred, 
   the rest are in rpred.  single is set to true if single
   clause of the form "fld == value" or "fld == variable" (DSB) */

void
separate_predicate (char *p, char *fld, BOOLEAN *single, 
                    char *ipred, char *rpred)
{
  char   *pred = p;
  char   clause[ARG_STR_LEN];
  char   field[ARG_STR_LEN];
  char   relation[ARG_STR_LEN];
  char   value[ARG_STR_LEN];

  /* Step 1: Initialize resultant strings and booleans. */

  strcpy(ipred,"1");
  strcpy(rpred,"1");
  *single = FALSE;

  /* Step 2: Pick off each clause. */

  while(*pred != '\0') {
    next_clause(&pred, clause, field, relation, value);
    if (field[0] == '\0') {
      /* Uninterpretable clause. */
      post_and(rpred, value);
    }
    else {
      /* Interpretable clause. */
      /* Skip over the first two characters (either "$." or "$:")
         to get the name of the field. */
      if (strcmp(fld, field+2) == 0) {
        post_and(ipred, clause);
        *single = *single && (strcmp(relation,"==")==0);
      }
      else {
        post_and(rpred, clause);
      }
    }
  }
}

/*****************************************************************************/
/*                  Base field.                                              */
/*****************************************************************************/

/* basefield(n,r) copies name n into r and trims off trailing digits.
   Returns TRUE if trimming occured this signifies field a field name
   ending in digits. (DSB) */

static BOOLEAN
basefield (const char *n, char *r)
{
  char *end = r + strlen(n) - 1;
  char *start = end;

  strcpy(r, n);
  while (*end >= '0' && *end <= '9')
    *end-- = '\0';
  return(end != start);
}
   
/*****************************************************************************/
/*                  Field update.                                            */
/*****************************************************************************/

/* field_update(f,e,r) returns a copy of string f in string r where
   the name of each augmented field is replaced with field<layerno>.
   The name of the object type whose fields we are to examine is e.
   (DSB) */

void
field_update (const char *format, const char *element, char *res)
{
  char truncname[ARG_STR_LEN];
  char result[ARG_STR_LEN];
  ENTRY *e;
  IDENT *i;
  MCURSOR *mcurs;

  strcpy(result, format);
  e = symtab_lookup(symtab[SUE], element);
  i = e->ident;
  mcurs = new_mcursor(i);
  FOREACH_MEMBER(mcurs) {
    if (basefield(name_of(mcurs), truncname)) {
      strcat(truncname, " ");
      replace_string(result, truncname, name_of(mcurs), result);
    }
  }
  strcpy(res, result);
  xfree(mcurs);
}

/*****************************************************************************/
/*                  New literals.                                            */
/*****************************************************************************/

/* new_lower_literal(b,v,i) sets the lower bound for b given literal
   (i.e. expression) v.  incl is TRUE if the bound includes the value of v
   (i.e., field >= v). (DSB) */
/* new_upper_literal(b,v,i) sets the upper bound in a similar manner. */

static void
new_lower_literal (BOUNDS *b, const char *value, BOOLEAN incl) 
{
  /* Only update lower bounds if nothing has been specified so far. (DSB) */
   
  if (b->lower) {
    b->bottom    = FALSE;
    b->inc_lower = incl;
    b->xlower    = TRUE;
    strcpy(b->lower, value);
  }
}

static void
new_upper_literal (BOUNDS *b, const char *value, BOOLEAN incl) 
{
  /* Only update upper bounds if nothing has been specified so far. (DSB) */
   
  if (b->upper) {
    b->top       = FALSE;
    b->inc_upper = incl;
    b->xupper    = TRUE;
    strcpy(b->upper, value);
  }
}

/* new_lower(b,v,i,u) sets the lower bound for b given value v.
   incl is TRUE if the bound includes the value of v (i.e., field >= v).
   u is:
    u == -1 if b->lower < value
    u ==  0 if b->lower == value
    u == +1 if b->lower > value 
   (DSB) */
/* new_upper(b,v,i,u) sets the upper bound in a similar manner. (DSB) */

static void
new_lower (BOUNDS *b, const char *value, BOOLEAN incl, int update) 
{
  /* Update lower bounds if (a) there is no bound
     set or (b) there is a literal or (c) a more
     restrictive lower bound has been given (update == -1) (DSB) */
   
  if (b->lower || b->xlower || update == -1) {
    b->bottom    = FALSE;
    b->inc_lower = incl;
    b->xlower    = FALSE;
    strcpy(b->lower, value);
  }
}

void
new_upper (BOUNDS *b, char *value, BOOLEAN incl, int update) 
{
  /* Update upper bounds if (a) there is no bound
     set or (b) there is a literal or (c) a more
     restrictive upper bound has been given (update == 1) (DSB) */
   
  if (b->upper || b->xupper || update == 1) {
    b->top       = FALSE;
    b->inc_upper = incl;
    b->xupper    = FALSE;
    strcpy(b->upper, value);
  }
}

/*****************************************************************************/
/*                  Routines for integers (int).                             */
/*****************************************************************************/

/*
   Routines for integers

   intcmp(a,b) returns: -1 if a < b
                         0 if a = b
                        +1 if a > b

   int_lower(b,lower,v) returns intcmp(lower,v) plus
       checks to see if there is a lower bounds

   int_upper(b,upper,v) returns intcmp(upper,v)...
 */

int
intcmp (int a, int b)
{
  if (a==b)
    return(0);
  if (a<b)
    return(-1);
  else return(1);
}

static int
int_lower (const BOUNDS *b, int lower, int v)
{
  if (b->lower)
    return(-1);
  else 
    return(intcmp(lower,v));
}

static int
int_upper (const BOUNDS *b, int upper, int v)
{
  if (b->top)
    return(-1);
  else
    return(intcmp(upper,v));
}

BOOLEAN
is_literal_int (const char *str)
{
  /* Assume that str is a literal of an integer if it
     contains only digits and/or a negative sign. (DSB) */

  return(strlen(str) == integer_span(str));
}

unsigned
int_hash (int i, int size)
{
  unsigned hash = (abs(i*59) % size);
  assert(hash < size);
  return(hash);
}

void
bounds_impact_int (BOUNDS *b, const char *relation, char *value)
{
  int     lower = 0;  /* Initialization of these variables is done */
  int     upper = 0;  /* To keep gcc from issuing warnings (DSB) */
  int     val =   0;
  BOOLEAN literal;
  const char *p;
  OP_TAB  *r;
  OP      *o;

  /* Step 1: set upper and lower values */
  
  if (!b->bottom)
    lower = atoi(b->lower);
  if (!b->top)
    upper = atoi(b->upper);
  
  /* Step 2: determine if value is a literal (i.e, an expression).
     for integers this means only digits and  minus sign */

  p       = value;
  literal = FALSE;
  if (*p == '-')
    p++;
  while (*p != '\0')
  {
    if (*p < '0' || *p > '9')
    {
      literal = TRUE;
      break;
    }
    p++;
  }
  if (!literal)
    val = atoi(value);
  
  /* Step 3: make sure that the relation is ligitimate */

  r = &type_tab[0];
  while (r->typename[0] != '\0' && strcmp(r->typename, "int") != 0)
    r++;
  if (r->typename[0] == '\0')
    error("cannot find int type in type_table");

  o = r->op;
  while (o->name[0] != '\0' && strcmp(o->name, relation) != 0)
    o++;
  if (o->name[0] == '\0')
    error("unrecognizable int operation %s", relation);
  
  /* Step 4: now update bounds */
  
  p = relation;
  if (literal)
  {
    switch (*p++) {
    case '=':
      new_lower_literal(b,value,TRUE);
      new_upper_literal(b,value,TRUE);
      break;
               
    case '>':
      if (*p == '=')
        new_lower_literal(b,value,TRUE);
      else 
        new_lower_literal(b,value,FALSE);
      break;
               
    case '<':
      if (*p == '=')
        new_upper_literal(b,value,TRUE);
      else 
        new_upper_literal(b,value,FALSE);
      break;
               
    case '!':
      /* != doesn't restrict ranges */
      break;
    }
  }
  else
  {
    switch (*p++) {
      case '=':
        new_lower(b,value,TRUE,int_lower(b,lower,val));
        new_upper(b,value,TRUE,int_upper(b,upper,val));
        break;
   
      case '>':
        if (*p == '=')
          new_lower(b,value,TRUE,int_lower(b,lower,val));
        else 
          new_lower(b,value,FALSE,int_lower(b,lower,val));
        break;
                 
      case '<':
        if (*p == '=')
          new_upper(b,value,TRUE,int_upper(b,upper,val));
        else 
          new_upper(b,value,FALSE,int_upper(b,upper,val));
        break;
                 
      case '!':
        /* != doesn't restrict ranges */
        break;
    }
  }
}

/*****************************************************************************/
/*                  Routines for strings (str).                              */
/*****************************************************************************/

/*
   Routines for strings

   strcmp(a,b) returns: -1 if a < b
                         0 if a = b
                        +1 if a > b
   defined in <string.h>

   str_lower(b,v) returns strcmp(lower,v) plus
       checks to see if there is a lower bounds

   str_upper(b,v) returns strcmp(upper,v)...
 */

static int
str_lower (const BOUNDS *b, const char* v)
{
  if (b->bottom)
    return(-1);
  else 
    return(strcmp(b->lower,v));
}

static int
str_upper (const BOUNDS *b, const char* v)
{
  if (b->top)
    return(-1);
  else
    return(strcmp(b->upper,v));
}

BOOLEAN
is_literal_str (const char *str)
{
  /* Assume that str is a literal of a string if it
     begins with a quote and ends with a quote. (DSB) */

  if (str[0] == '"')
    if (str[strlen(str)-1] == '"')
      return(TRUE);
  return(FALSE);
}

short
str_hashcmp (const char *str)
{
  int   a = 0;
  short *s = (short *) str;

  while (!(*(char *)(s) == '\0' || *((char *)(s) + 1) == '\0'))
    a +=  *s++;
  a += *(char *) s;
  return(0x377 & a);
}

unsigned
str_hash (const char *str, int size)
{
  /* For comments, see analogous routine P2_str_hash() in paces/P2.c  (JAT) */
  unsigned hash = 0;
#if 1
  while (*str)
  {
    hash = hash << 1 ^ (*str);
    str++;
  }
#else
  unsigned high_bits = ( ~((unsigned)(~0) >> 4 ));
  while (*str)
  {
    hash = (hash << 4) + *str;
    str++;
    if ((high_bits = hash & high_bits) != 0)
      hash ^= high_bits >> 24;
    hash &= ~high_bits;
  }
#endif
  hash = hash % size;
  assert(hash < size);
  return(hash);
}

void
bounds_impact_str (BOUNDS *b, const char *relation, char *value)
{
  BOOLEAN literal;
  const char *p;
  OP_TAB  *r;
  OP      *o;

  /* Step 1: Determine if value is a literal (i.e, an expression). 
     For strings, this means the first character of value
     is an apostrophe. */

  if (*value == '\'')
  {
    literal = FALSE;
    replace_char(value,'\'','"');
  }
  else
    literal = TRUE;
  
  /* Step 2: Make sure that the relation is ligitimate. */

  r = &type_tab[0];
  while (r->typename[0] != '\0' && strcmp(r->typename,"str") != 0)
    r++;
  if (r->typename[0] == '\0')
    error("cannot find string type in type_table");

  o = r->op;
  while (o->name[0] != '\0' && strcmp(o->name,relation) != 0)
    o++;
  if (o->name[0] == '\0')
    error("unrecognizable string operation %s", relation);
  
  /* Step 4: Update bounds. */
  
  p = relation;
  if (literal)
  {
    switch (*p++) {
    case '=':
      new_lower_literal(b,value,TRUE);
      new_upper_literal(b,value,TRUE);
      break;
               
    case '>':
      if (*p == '=')
        new_lower_literal(b,value,TRUE);
      else 
        new_lower_literal(b,value,FALSE);
      break;
      
    case '<':
      if (*p == '=')
        new_upper_literal(b,value,TRUE);
      else 
        new_upper_literal(b,value,FALSE);
      break;
      
    case '!':
      /* != doesn't restrict ranges */
      break;
    }
  }
  else
  {
    switch (*p++) {
      case '=':
        new_lower(b,value,TRUE,str_lower(b,value));
        new_upper(b,value,TRUE,str_upper(b,value));
        break;
   
      case '>':
        if (*p == '=')
          new_lower(b,value,TRUE,str_lower(b,value));
        else 
          new_lower(b,value,FALSE,str_lower(b,value));
        break;
                 
      case '<':
        if (*p == '=')
          new_upper(b,value,TRUE,str_upper(b,value));
        else 
          new_upper(b,value,FALSE,str_upper(b,value));
        break;
                 
      case '!':
        /* != doesn't restrict ranges */
        break;
    }
  }
}

/*****************************************************************************/
/*                  Next clause                                              */
/*****************************************************************************/

/* Return the next term of a P2 conjunctive predicate.  If the term is
   structured, then field, relation, and value point respectively to
   strings containing the field, relation, and value.  If the term is
   unstructured, then field and relation are null and value points to
   the entire string. (DSB) */

/*

   predicate            field           relation        value

   $.x == $a.y          x               ==              $a.y
   $.x == foo           x               ==              foo
   $a.y == $.x          x               ==              $a.y
   $a.y == $b.z                                         $a.y == $b.z

*/

static char *
next_clause1 (char *predicate, char *field, char *relation, char *value)
{
  char *p = predicate + whitespace_span(predicate);
  char *f1, *f2, *r1, *r2, *v1, *v2;
  int interpreted = 0;
  int len;

  f1 = p;
  if (f1[0] == '$' && (f1[1] == '.' || f1[1] == ':')) {
    f2 = f1+2 + identifier_span(f1+2);
    if (f1+2 != f2) {
      r1 = f2 + whitespace_span(f2);
      r2 = r1 + relational_operator(r1);
      if (r1 != r2) {
        v1 = r2 + whitespace_span(r2);
        v2 = find_space(v1);
        if (v2 == NULL)
          v2 = v1 + strlen(v1);
        p = v2;
        interpreted = 1;
      }
    }
  }
  else {
    v1 = f1;
    v2 = find_space(v1);
    if (v2 != NULL) {
      r1 = v2 + whitespace_span(v2);
      r2 = r1 + relational_operator(r1);
      if (r1 != r2) {
        f1 = r2 + whitespace_span(r2);
        if (f1[0] == '$' && (f1[1] == '.' || f1[1] == ':')) {
          f2 = f1+2 + identifier_span(f1+2);
          if (f1+2 != f2) {
            p = f2;
            interpreted = -1;
          }
        }
      }
    }
  }

  if (interpreted != 0) {
    len = f2-f1;
    strncpy(field, f1, len);
    field[len] = '\0';

    len = r2-r1;
    strncpy(relation, r1, len);
    relation[len] = '\0';

    if (interpreted == -1) {
      if (relation[0] == '>')
        relation[0] = '<';
      else if (relation[0] == '<')
        relation[0] = '>';
    }
  }
  else {
    field[0] = '\0';
    relation[0] = '\0';
    v1 = p;
    v2 = find_space(v1);
    if (v2 == NULL)
      v2 = v1 + strlen(v1);
    else {
      v2 = v2 + whitespace_span(v2);
      if (relational_operator(v2)) {
        v2 = find_space(v2);
        if (v2 == NULL)
          parse_error("expected value");
        v2 = v2 + whitespace_span(v2);
        v2 = find_space(v2);
        if (v2 == NULL)
          v2 = v1 + strlen(v1);
      }
    }
    p = v2;
  }

  len = v2-v1;
  strncpy(value, v1, len);
  value[len] = '\0';
  if (value[0] == '\'')
    replace_char(value, '\'', '"');

#ifndef NDEBUG
  if (p == NULL)
    assertion_failed("p == NULL");
#endif

  /* Skip over spaces and ampersands. */
  /* Replace this with skip of trailing space and a check for && (JAT) */
  while (*p != '\0' && (*p == ' ' || *p == '&'))
    p++;

  return(p);
}

void
next_clause (char **p, char *clause, char *field, char *relation, char *value)
{
  *p = next_clause1(*p, field, relation, value);

  if (clause != NULL) {
    if (field[0] == '\0')
      strcpy(clause, value);
    else
      sprintf(clause, "%s %s %s", field, relation, value);

    /* Transform single quote aka apostrophe (') to double quote (")
       This transformation is performed by next_clause()
       for interpreted, but not uninterpreted clauses. */

    replace_char(clause, '\'', '"');
  }
}

/*****************************************************************************/
/*                  Bounds.                                                  */
/*****************************************************************************/

/* init_bounds(b) initializes the range retrieval
   region b to [-infinity, +infinity]. (DSB) */

void
init_bounds (BOUNDS *b)
{
  b->bottom    = TRUE;
  b->top       = TRUE;
  b->inc_lower = TRUE;
  b->inc_upper = TRUE;
  b->xlower    = FALSE;
  b->xupper    = FALSE;
  b->lower[0]  = '\0';
  b->upper[0]  = '\0';
}

/* define_bounds(b,c,p,f,bi) initializes bounds structure b
   for P2 predicate p and field f.  bi is the bounds_impact
   function for field f. (DSB) */

void
define_bounds (const TE *te, BOUNDS *b, char *c, char *p, char *f, VOID_FUNC bi)
{
  char       *pred = p;
  char       targetfield[ARG_STR_LEN];
  char       field[ARG_STR_LEN];
  char       relation[ARG_STR_LEN];
  char       value[ARG_STR_LEN];

  assert(te != NULL);

  /* Step 1: f is simply the name of a field.
     We must put the alias "$." in front of it */
  
  strcpy(targetfield,"$.");
  strcat(targetfield,f);
  
  /* Step 2: Initialize the bounds */
  
  init_bounds(b);
  
  /* Step 3: Foreach term of the predicate, if the term is
     structured, check to see if it is of the relevant field.
     If so, update the bounds. */
  
  while (*pred != '\0') {
    next_clause(&pred, NULL, field, relation, value);
    if (field[0] == '\0')
      continue;
    if (strcmp(field,targetfield) == 0)
      (*bi)(b,relation,value);
  }

  /* Replace any composite cursor references that may appear in the
     upper and lower bounds strings.  We have to check for a non-null
     cursor, because this routine may be called either from optimize
     (where the cursor is defined) and elsewhere (where it isn't).
     (JAT) */

  if (*c != '\0') {
    replace_cursor_refs(te, c, b->lower);
    replace_cursor_refs(te, c, b->upper);
  }
}

/*****************************************************************************/
/*                  Simplify predicate.                                      */
/*****************************************************************************/

/* simplify_predicate(p,b,f,a,r) is used to compute the predicate for
  end_adv and end_rev functions for layers that order their records.
  p is the selection predicate and b is its bounds for field f.  a is
  TRUE if the predicate for end_adv is to be computed, FALSE
  otherwise.  r is the buffer in which the reduced predicate is to be
  used.  This predicate is to be applied inside the FOREACH
  loop. (DSB) */

void
simplify_predicate (char *p, BOUNDS *b, char *f, BOOLEAN adv, char *result)
{
  char targetfield[ARG_STR_LEN];
  char field[ARG_STR_LEN];
  char relation[ARG_STR_LEN];
  char value[ARG_STR_LEN];

  char *last_pos;
  char *curr_pos;

  /* Step 1: f is simply the name of a field.  We must
     put the alias "$." in front of it */
  
  strcpy(targetfield,"$.");
  strcat(targetfield,f); 
  
  /* Step 2: copy the predicate */
  
  strcpy(result,p);
  
  /* Step 3: find the term that has the upper (lower) value
     referenced in the bounds structure - this is
     the term that we want to eliminate */

  curr_pos = result;
  while (*curr_pos != '\0') {
    last_pos = curr_pos;
    next_clause(&curr_pos, NULL, field, relation, value);
    if (field[0]=='\0')
      continue;
    if (strcmp(field,targetfield) == 0) {
      if (!adv && strcmp(b->upper,value) == 0) {
        if (*curr_pos != '\0') {
          strcpy(last_pos,"1 && ");
          strcat(last_pos,curr_pos);
        }
        else 
          strcpy(last_pos,"1");
        break;
      }
      else
        if (adv && strcmp(b->lower,value) == 0) {
          if (*curr_pos == '\0') 
            strcpy(last_pos, "1");
          else
            strcpy(last_pos, curr_pos);
          break;
        }
    }
  }
}

/*****************************************************************************/
/*                  Use layer.                                               */
/*****************************************************************************/

/* use_layer(b,p,f,bi) will return 0 if a layer won't help in
   processing predicate p using field f. 1 is returned if the range is
   not trivial, and 2 is returned if a point qualification is made.
   bi is the bounds impact function for field f and b is the bounds
   structure to use. (DSB) */

int
use_layer (const TE *te, BOUNDS *b, char *c, char *p, char *f, VOID_FUNC bi)
{
  assert(te != NULL);
  define_bounds(te, b, c, p, f, bi);
  if (b->bottom && b->top)
    return(0);
  if (!b->bottom && strcmp(b->lower,b->upper)==0)
    return(2);
  else
    return(1);
}

/*****************************************************************************/
/*                  Routines needed by hashcmp.xp                            */
/*****************************************************************************/

/* The following routines were needed by the hashcmp.xp layer. */

/* So, why are they here??? (JAT) */
/* Move these to hashcmp.xp, in order to reduce false dependencies (JAT) */

/* hashcmp_expand_predicate(p, f, n, i, h, o) expands predicate
   p on field f using layernumber n and is_literal function i
   and hash function h and o is the operation on which to perform
   this transformation.

   Basically, this routine examines predicate p for clauses of 
   the form (f == value) (where o = "==").
   It replaces such clauses with (h == value) && (f == value).
   The idea is that testing (f == value) is expensive,
   while testing (h == value) is not. (DSB) */

void
hashcmp_expand_predicate (char *predicate, char *fld, int ln, 
                          BOOL_FUNC is_lit, SHORT_FUNC hash, char *op)
{
  char   expanded_predicate[ARG_STR_LEN];
  char   field[ARG_STR_LEN];
  char   relation[ARG_STR_LEN];
  char   value[ARG_STR_LEN];
  char   *pred = predicate;
  char   clause[ARG_STR_LEN];
  char   f[ARG_STR_LEN];

  strcpy(f,"$.");
  strcat(f,fld);
  if (predicate[0] == '\0')
    strcpy(predicate, "1");
  if (strcmp(predicate, "1") != 0) {
    expanded_predicate[0] = '\0';
    while (*pred != '\0') {
      next_clause(&pred, clause, field, relation, value);
      if (field[0] == '\0')
        post_and(expanded_predicate, value);
      else {
        if (strcmp(f, field) == 0) {
          /* We have a match--add the hash predicate. */

          /* A bit of optimization here.  If "value" is a literal, then
             we can hash at compile time.  If "value" is not a
             literal, then we don't expand the predicate - we could,
             but we don't have the technology to do so right now .
             Also, if there is no hash function, then skip this
             optimization.  There is no hash function when we are
             dealing with trivial data types like integers. (DSB) */

          if (hash && strcmp(op,relation) == 0 && (*is_lit)(value)) {
            char temp[ARG_STR_LEN];
            char v[ARG_STR_LEN];

            strcpy(v, value);
            remove_char(v,'"');     
            sprintf(temp, "%s%d == %d", f, ln, (*hash)(v));
            post_and(expanded_predicate, temp);
          }
        }
        post_and(expanded_predicate, clause);
      }
    }
    strcpy(predicate, expanded_predicate);
  }
}

OP_TAB *
find_data_type (IDENT *element, char *fieldname)
{
  MCURSOR mcurs;
  char    *typename;
  OP_TAB  *t;

  init_mcursor(&mcurs, element);
  position_member(&mcurs, fieldname);
  typename = type_of(&mcurs);
  for (t = &type_tab[0]; t->typename[0] != '\0'; t++) {
     if (strcmp(t->typename,typename) == 0)
        return(t);
  }
  error("cannot locate type %s", typename);
  return(0);
}

/*****************************************************************************/
/*                  Bind value.                                              */
/*****************************************************************************/

#if 0
/* Subsumed by replace_cursor_refs. (JAT) */

/* bind_value( c, i, o ) - i is a string that contains some
   expression.  i may contain $. references or $xxx. references.
   c is a string that defines a cursor expression.  
   $. is replaced with c.obj->
   $xxx. is replaced with shortened(c).xxx-> 
   Note: this routine doesn't handle partition...
   (DSB)
*/

void
bind_value ( char *cursor, char *input_value, char *output_value )
{
  char expr[MAX_PRED_LEN];
  char tmp[MAX_PRED_LEN];
  char *i;

  if (strchr(input_value, '$') == NULL) {
    strcpy(output_value, input_value);
    return;
  }

  sprintf(tmp, "(%s).obj->", cursor);
  replace_string(input_value, "$.", tmp, output_value);

  if (strchr(output_value, '$') == NULL)
    return;

  strcpy(tmp, cursor);
  i = strrchr(tmp, '.');
  if (i == NULL)
    error("cannot convert $xxx. format");
  *(i+1) = '\0';

  for (i = strchr(output_value, '$'); i != NULL ; i = strchr(i, '$')) {
    while (*i != '\0' && *i != '.')
      i++;
    if (*i == '\0')
      error("cannot convert $xxx. format");
    *i = '^';
  }

  strcpy(expr, output_value);
  replace_string(expr, "$", tmp, output_value);
  strcpy(expr, output_value);
  replace_string(expr, "^", ".obj->", output_value);
}
#endif

