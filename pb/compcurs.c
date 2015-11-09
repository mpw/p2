/* $Id: compcurs.c,v 45.2 1997/09/19 22:14:21 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* compcurs definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>            /* NULL, sprintf() */
#include <string.h>           /* strchr() */

#include "call-down.h"        /* call_level() */
#include "compcurs.h"         /* CP_TABLE */
#include "data-type.h"        /* post_and() */
#include "error.h"            /* assertion_failed() */
#include "io.h"               /* SPRINT_BUF_SIZE */
#include "lex.h"              /* MAX_IDENT_LEN */
#include "pb-actions.h"       /* pre_opt_cursor_declaration() */
#include "pb-type.h"          /* ptree_has_expected_ctype() */
#include "pb-xform.h"         /* new_struct(), MCURSOR */
#include "qopt.h"             /* MAX_QOPT_COST */
#include "string-util.h"      /* replace_string_inplace() */
#include "type.h"             /* NODE */
#include "typex.h"            /* unify_te(), unify_another_te() */
#include "util.h"             /* BOOLEAN */
#include "xform.h"            /* TE */
#include "xmalloc.h"          /* xmalloc() */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

/* These strings are used to hide the strings "deleted" and "$"
   in order to temporarily disable the special interpretation of
   these strings in other parts of pb. (JAT) */

#define DELETED_HIDDEN_STRING "P2_deleted_"
#define CURSOR_REF_HIDDEN_STRING "P2_cursor_ref_"

/* Print the cursor-predicate table as a comment in the generated .c code. */

#define PRINT_CP_TABLE_AS_COMMENT 0

/*****************************************************************************/
/*                  Identifier list parse tree management.                   */
/*****************************************************************************/

#ifndef NDEBUG
inline static void
assert_identifier_list_valid (NODE *identifier_list)
{
  if (identifier_list != NULL) {
    int narg = identifier_list->narg;
    if (narg != 0 && narg != 3)
      assertion_failed("identifier_list->narg == %d", narg);
    if (narg == 3 && strcmp(identifier_list->arg[1]->ident->name, ",") != 0)
      assertion_failed("identifier_list->arg[1]->ident->name != \",\"");
  }
}
#endif /* NDEBUG */

/* Given an identifier list.
   Copy each identifier in the list into a separate entry in identifiers.
   Return the total number of identifiers. */

/* Note that the order of identifiers in identifiers will be the opposite
   of the order of identifiers in identifier list.
   For example, if identifier_list = a, b, c
   then identifiers[] = { c, b, a } (JAT) */

static int
get_num_identifiers (NODE *identifier_list, char *identifiers[])
{
#ifndef NDEBUG
  assert_identifier_list_valid(identifier_list);
#endif /* NDEBUG */

  if (identifier_list == NULL)
    return(0);
  else if (identifier_list->narg == 0) {
    identifiers[0] = identifier_list->ident->name;
    return(1);
  }
  else {
    identifiers[0] = identifier_list->arg[2]->ident->name;
    identifiers++;
    return(1 + get_num_identifiers(identifier_list->arg[0], identifiers));
  }
}

/*****************************************************************************/
/*                  Composite cursor member symbol table lookup.             */
/*****************************************************************************/

static ENTRY *
compcurs_symlist_lookup (NODE *compcurs, char *member_name)
{
  ENTRY *e = symlist_lookup(compcurs->ident->ctype->ident->members,
                            member_name);
#ifndef NDEBUG
  if (e == NULL)
    assertion_failed("compcurs member not found");
#endif /* NDEBUG */
  return(e);
}

/*****************************************************************************/
/*                  Clause parsing.                                          */
/*****************************************************************************/

/* Given a pointer to a predicate, return the next clause in the
   predicate, and update the pointer. */

static char *
get_clause (char **pp)
{
  char *c; /* Clause. */
  char *t;

  if (**pp == '\0')
    return(NULL);

  /* Skip leading blanks. */
  while (**pp == ' ')
    (*pp)++;
  c = *pp;

  while (!(**pp == '&' && *((*pp)+1) == '&')) {
    if (**pp == '\0')
      break;
    else
      (*pp)++;
  }

  t = (*pp);
  if (**pp != '\0')
    *pp += 2;

  /* Eliminate trailing blanks. */
  delete_trailing_space(t);

  if (strcmp(c, "") == 0)
    parse_error("expected value");

  return(c);
}

/* If the cursor curs1 appears in the array of num_curs cursors
   curs2[], return its position.  Otherwise, return -1. */

static int
get_curs_pos (char *curs1, int num_curs, char *curs2[])
{
  int i;

  for (i = 0; i < num_curs; i++)
    if (strcmp(curs1, curs2[i]) == 0)
      return(i);
  return(-1);
}

/* Given a predicate.
   Copy each cursor in the predicate into a separate entry in curs.
   Return the total number of cursors. */

static int
get_num_curs (char *predicate, char *curs[])
{
  int num_curs = 0;
  char *dollar;
  int i;

  if (predicate == NULL)
    return(0);
  else
    dollar = strchr(predicate, '$');

  while (dollar != NULL) {
    int len = identifier_span(dollar+1);
    char *s = (char *) xmalloc_atomic(len+1);
    memcpy(s, dollar+1, len);
    s[len] = '\0';

    i = get_curs_pos(s, num_curs, curs);
    if (i == -1) {
      if (num_curs > MAX_NUM_LINK_CURS)
        parse_error("predicate references %d cursors, maximum is %d",
                    num_curs, MAX_NUM_LINK_CURS);
      else {
        curs[num_curs] = s;
        num_curs++;
      }
    }
    dollar = strchr(dollar+1+len, '$');
  }

  return(num_curs);
}

/* Return TRUE if curs1[] is equal to curs2[]. */

inline static BOOLEAN
curs_equality (int num_curs1, int num_curs2,
               char *curs1[], char *curs2[])
{
  int i;

  if (num_curs1 != num_curs2)
    return(FALSE);

  for (i = 0; i < num_curs1; i++)
    if (get_curs_pos(curs1[i], num_curs2, curs2) == -1)
      return(FALSE);
  return(TRUE);
}

/* Compute the following set differences:
     curs3 = curs1[] - curs2[].
     curs4 = curs2[] - curs1[]. */

inline static void
curs_difference (int num_curs1, int num_curs2, int *num_curs3, int *num_curs4,
                 char *curs1[], char *curs2[], char *curs3[], char *curs4[])
{
  int i;

  (*num_curs3) = 0;
  for (i = 0; i < num_curs1; i++)
    if (get_curs_pos(curs1[i], num_curs2, curs2) == -1)
      curs3[(*num_curs3)++] = curs1[i];

  (*num_curs4) = 0;
  for (i = 0; i < num_curs2; i++)
    if (get_curs_pos(curs2[i], num_curs1, curs1) == -1)
      curs4[(*num_curs4)++] = curs2[i];
}

/* Given a clause, return TRUE iff the clause is structured.
   A clause is structured iff it has the form:
     $identifier.identifier relational_operator nonblank_char_seq
*/

static BOOLEAN
structured_clause (char *clause)
{
  if (clause[0] != '$')
    return(FALSE);
  clause++;
  clause += identifier_span(clause);
  if (clause[0] != '.')
    return(FALSE);
  clause++;
  clause += identifier_span(clause);
  while (clause[0] == ' ')
    clause++;
  clause += relational_operator(clause);
  while (clause[0] == ' ')
    clause++;
  while (clause[0] != '\0') {
    if (clause[0] == ' ')
      return(FALSE);
    clause++;
  }
  return(TRUE);
}

/* Given a clause, return TRUE iff the clause is an explicit link clause. */

static BOOLEAN
explicit_link_clause (char *clause)
{
  char *link = "P2_foo";
  int len;
  char identifier[MAX_IDENT_LEN];

  len = identifier_span(clause);
  strncpy(identifier, clause, len);
  identifier[len] = '\0';
  while (link[0] != '\0') {
    len = identifier_span(link);
    if (strncmp(identifier, link, len) == 0)
      return(TRUE);
    link += len;
    link += identifier_complement_span(link);
  }
  return(FALSE);
}

/*****************************************************************************/
/*                  Get parent and child curs.                               */
/*****************************************************************************/

#if 1

/* Given that the parent and child cursor both appear in the composite
   cursor declaration, then they occur in some (left to right) order.
   Assume that the parent cursor is the one that appears first, and
   the child cursor is the one that appears second. (JAT) */

static int
compcurs_compare (char *curs1, char *curs2, CP_TABLE *t)
{
  int curs_pos1 = get_curs_pos(curs1, t->num_curs, t->curs);
  int curs_pos2 = get_curs_pos(curs2, t->num_curs, t->curs);

#ifndef NDEBUG
  if (curs_pos1 == -1 || curs_pos2 == -1)
    assertion_failed("cursor not found");
#endif /* NDEBUG */

  return(curs_pos1 - curs_pos2);
}

static char *
get_parent_curs (CP_TABLE *t, int i)
{
  return ((compcurs_compare(t->row[i]->curs[0], t->row[i]->curs[1], t) < 0)
          ? t->row[i]->curs[0] : t->row[i]->curs[1]);
}

static char *
get_child_curs (CP_TABLE *t, int i)
{
  return ((compcurs_compare(t->row[i]->curs[0], t->row[i]->curs[1], t) < 0)
          ? t->row[i]->curs[1] : t->row[i]->curs[0]);
}

#else

/* Assume that the parent cursor is always curs[0],
   and the child cursor is always curs[1]. */

static char *
get_parent_curs (CP_TABLE *t, int i)
{
  return(t->row[i]->curs[0]);
}

static char *
get_child_curs (CP_TABLE *t, int i)
{
  return(t->row[i]->curs[1]);
}

#endif

/*****************************************************************************/
/*                  Link state argument.                                     */
/*****************************************************************************/

/* Given a compcurs predicate and a cursor predicate table row,
   replace the composite cursor references by link predicate references. */

static void
new_linkpredicate (CP_TABLE *t, int i, char *linkpredicate)
{
  char s[MAX_IDENT_LEN];

  strcpy(linkpredicate, t->row[i]->predicate);

  sprintf(s, "$%s", get_parent_curs(t, i));
  replace_string_inplace(linkpredicate, s, "$p");

  sprintf(s, "$%s", get_child_curs(t, i));
  replace_string_inplace(linkpredicate, s, "$c");
}

/* Allocate a new link state argument. */

static LST_ARG *
new_lst_arg (CP_TABLE *t, int i)
{
  LST_ARG *arg = xmalloc_object(LST_ARG);
  new_linkpredicate(t, i, arg->linkpredicate);
  arg->linklayer = -1;
  arg->linkcost = MAX_QOPT_COST;
  arg->linkname[0] = '\0';
  arg->pcard = MANY;
  arg->ccard = MANY;
  arg->presidual[0] = '\0';
  arg->cresidual[0] = '\0';
  arg->apply[0] = '\0';
  arg->linkannote = NULL;
  arg->special_foreachl = FALSE;
  return(arg);
}

/* Initialize the link state arguments of cursor-predicate table. */

static void
init_lst_arg_of_cp_table (CTYPE *compcurs_ctype, CP_TABLE *t)
{
  int i;
  for (i = 0; i < t->num_rows; i++) {
    if (t->row[i]->num_curs == 2) {
      LST_ARG *lst_arg = new_lst_arg(t, i);
      IDENT *parent_ident, *child_ident;
      CURS_ARG *parent_arg, *child_arg;
      TE *te = t->unified_te;
      ENTRY *e;
      NODE *n;

      /* Parent */

      e = symlist_lookup(compcurs_ctype->ident->members, get_parent_curs(t, i));
      parent_ident = e->ident;
      n = terminal_ident(parent_ident);
      parent_arg = parent_ident->ctype->cctype->arg;
      assert_curs_arg_valid(parent_arg);

      /* Child */

      e = symlist_lookup(compcurs_ctype->ident->members, get_child_curs(t, i));
      child_ident = e->ident;
      n = terminal_ident(child_ident);
      child_arg = child_ident->ctype->cctype->arg;
      assert_curs_arg_valid(child_arg);

      /* Optimize */

      call_level(te, LOPTIMIZE_OP, 3, parent_arg, child_arg, lst_arg);
      t->row[i]->lst_arg = lst_arg;
    }
  }
}

/*****************************************************************************/
/*                  Cursor-predicate table management.                       */
/*****************************************************************************/

/* Given a clause, return the type of the clause. */

static CP_TYPE
get_clause_type (char *clause)
{
  if (structured_clause(clause))
    return(STRUCTURED);
  if (explicit_link_clause(clause))
    return(EXPLICIT_LINK);
  return(UNSTRUCTURED);
}

static void
sort_curs (int num_curs, char *curs[], CP_TABLE *t)
{
  char *src[MAX_NUM_LINK_CURS];
  int i;
  int j = 0;

  memcpy(src, curs, num_curs * sizeof(char *));

  for (i = 0; i < t->num_curs; i++) {
    int pos = get_curs_pos(t->curs[i], num_curs, src);
    if (pos != -1) {
      curs[j] = src[pos];
      j++;
    }
  }
#ifndef NDEBUG
  if (num_curs != j)
    assertion_failed("sort_curs failed");
#endif /* NDEBUG */
}

static void
post_and1 (char **predicate, char *clause)
{
  if ((*predicate) == NULL) {
    (*predicate) = (char *) xmalloc_atomic(MAX_PRED_LEN);
    strcpy((*predicate), clause);
  }
  else
    post_and((*predicate), clause);
}

/* Return TRUE if curs is constant. */

static BOOLEAN
constant (int num_curs, char *curs[], int num_given, char *given[])
{
  int j;
  if (num_curs == 0)
    return(TRUE);
  for (j = 0; j < num_curs; j++)
    if (get_curs_pos(curs[j], num_given, given) == -1)
      return(FALSE);
  return(TRUE);
}

/* Return TRUE if the given row is constant. */

static BOOLEAN
constant_row (int num_given, char *given[], int i, CP_TABLE_ROW *row[])
{
  return(constant(row[i]->num_curs, row[i]->curs, num_given, given));
}

/* Given a clause containing num_curs cursors curs[], and with given type,
   add the clause to cursor-predicate table. */

static void
add_clause1 (int num_curs, char *curs[],
             char *clause, CP_TYPE type, CP_TABLE *t)
{
  int i = 0;
  int j;

  /* Use an existing row. */
  if (type == STRUCTURED || type == UNSTRUCTURED) {
    while(i < t->num_rows) {
      if (curs_equality(num_curs, t->row[i]->num_curs, curs, t->row[i]->curs)
          && t->row[i]->type == type) {
        post_and(t->row[i]->predicate, clause);
        return;
      }
      i++;
    }
  }
  /* Add a new row */
  i = t->num_rows;
  if (i == MAX_NUM_LINK_PRED)
    parse_error("link predicate has too many clauses");
  t->row[i] = xmalloc_object(CP_TABLE_ROW);
  t->row[i]->num_curs = num_curs;
  for (j = 0; j < num_curs; j++)
    t->row[i]->curs[j] = curs[j];
  sort_curs(num_curs, t->row[i]->curs, t);
  strcpy(t->row[i]->predicate, clause);
  t->row[i]->type = type;
  t->num_rows++;
}

/* Add the given clause to cursor-predicate table. */

static void
add_clause (char *clause, CP_TABLE *t)
{
  if (strcmp(clause, "1") != 0) {
    char *curs[MAX_NUM_LINK_CURS];
    int num_curs = get_num_curs(clause, curs);
    CP_TYPE type = get_clause_type(clause);

    add_clause1(num_curs, curs, clause, type, t);
  }
}

/* Given an identifier.  Copy each member in the identifier into a
   separate entry in members.  Return the total number of members. */

static int
get_num_members (CTYPE *compcurs_ctype, char *members[])
{
  int i = 0;
  if (compcurs_ctype->ident->members != NULL) {
    MCURSOR *mcurs = new_mcursor(compcurs_ctype->ident);
    FOREACH_MEMBER(mcurs) {
      members[i] = copy_string(mcurs->pos->ident->name);
      i++;
    }
  }
  return(i);
}

static void
init_fields_of_cp_table (CTYPE *compcurs_ctype, char *predicate,
                         char *valid_predicate, int num_given, char *given[],
                         CP_TABLE *t)
{
  char *clause;
  int i;

  /* t->given = given */

  t->num_given = num_given;
  memcpy((char *) t->given, (char *) given, num_given * sizeof(char *));

  /* Cursors. */

  t->num_curs = get_num_members(compcurs_ctype, t->curs);
  t->num_rows = 0;
  clause = get_clause(&predicate);
  while (clause != NULL) {
    add_clause(clause, t);
    clause = get_clause(&predicate);
  }

  /* exit_predicate and valid_predicate. */

  for (i = 0; i < t->num_curs; i++)
    t->valid_predicate[i] = NULL;
  t->exit_predicate = NULL;

  t->valid = (valid_predicate != NULL);
  if (t->valid) {
    char *curs[MAX_NUM_LINK_CURS];
    int num_curs;
    char *given[MAX_NUM_LINK_CURS];
    int num_given;

    clause = get_clause(&valid_predicate);
    while (clause != NULL) {
      num_curs = get_num_curs(clause, curs);

      /* given = t->given */
      num_given = t->num_given;   
      memcpy((char *) given, (char *) t->given, num_given * sizeof(char *));

      if (constant(num_curs, curs, num_given, given))
        post_and1(&t->exit_predicate, clause);
      else {
        for (i = 0; i < t->num_curs; i++) {
          given[num_given] = t->curs[i];
          num_given++;

          if (constant(num_curs, curs, num_given, given)) {
            post_and1(&t->valid_predicate[i], clause);
            break;
          }
        }
      }

      clause = get_clause(&valid_predicate);
    }
  }
}

static void
group_rows_in_cp_table (CP_TABLE *t)
{
  CP_TABLE_ROW *src[MAX_NUM_LINK_PRED];
  BOOLEAN deleted[MAX_NUM_LINK_PRED];
  int i;
  int s;
  int r = 0;

  for (i = 0; i < t->num_rows; i++)
    deleted[i] = FALSE;
  memcpy((char *) src, (char *) t->row, t->num_rows * sizeof(char *));

  for (s = 0; s < t->num_rows; s++) {
    if (!deleted[s]) {
      for (i = s; i < t->num_rows; i++)
        if (!deleted[i]
            && ((s == i)
                || curs_equality(src[s]->num_curs, src[i]->num_curs,
                                 src[s]->curs, src[i]->curs))) {
          t->row[r] = src[i];
          r++;
          deleted[i] = TRUE;
        }
    }
  }
}

static void
connected_closure (BOOLEAN connected[], CP_TABLE *t)
{
  int i;
  int curs_pos1, curs_pos2;
  BOOLEAN done;

  do {
    done = TRUE;
    for (i = 0; i < t->num_rows; i++)
      if (t->row[i]->num_curs == 2 &&
        (t->row[i]->type == STRUCTURED
         || t->row[i]->type == EXPLICIT_LINK
         || t->row[i]->type == CROSS_PRODUCT)) {
        curs_pos1 = get_curs_pos(t->row[i]->curs[0], t->num_curs, t->curs);
        curs_pos2 = get_curs_pos(t->row[i]->curs[1], t->num_curs, t->curs);
        if (connected[curs_pos1] && !connected[curs_pos2]) {
          connected[curs_pos2] = TRUE;
          done = FALSE;
        }
        if (!connected[curs_pos1] && connected[curs_pos2]) {
          connected[curs_pos1] = TRUE;
          done = FALSE;
        }
      }
  } while (!done);
}

void
add_cross_products_to_cp_table (CP_TABLE *t)
{
  BOOLEAN connected[MAX_NUM_LINK_CURS];
  int i;

  if (t->num_curs != 0) {
    connected[0] = TRUE;
    for (i = 1; i < t->num_curs; i++)
      connected[i] = FALSE;
    do {
      connected_closure(connected, t);
      i = 1;
      while (i < t->num_curs && connected[i])
        i++;
      if (i != t->num_curs) {
        char *curs[MAX_NUM_LINK_CURS];
        curs[0] = t->curs[0];
        curs[1] = t->curs[i];
        add_clause1(2, curs, "1", CROSS_PRODUCT, t);
        connected[i] = TRUE;
      }
    } while (i != t->num_curs);
  }
}

static int
row_compare (int row1, int row2, CP_TABLE *t)
{
  int i = 0;
  int num_curs1 = t->row[row1]->num_curs;
  int num_curs2 = t->row[row2]->num_curs;

  while (i < num_curs1 && i < num_curs2) {
    int pos1 = get_curs_pos(t->row[row1]->curs[i], t->num_curs, t->curs);
    int pos2 = get_curs_pos(t->row[row2]->curs[i], t->num_curs, t->curs);
    if (pos1 < pos2)
      return(-1);
    else if (pos1 > pos2)
      return(1);
    i++;
  }
  if (i == num_curs1 && i != num_curs2)
    return(-1);
  else if (i != num_curs1 && i == num_curs2)
    return(1);
  return(0);
}

void
sort_cp_table (CP_TABLE *t)
{
  /* Selection sort. */
  int row1, row2, row_min;

  for (row1 = 0; row1 < t->num_rows; row1++) {
    row_min = row1;
    for (row2 = row1+1; row2 < t->num_rows; row2++)
      if (row_compare(row_min, row2, t) > 0)
        row_min = row2;
    if (row_min != row1) {
      CP_TABLE_ROW *temp = t->row[row_min];
      /* Shift t->row[row1+1], ..., t->row[row_min] */
      for (row2 = row_min; row2 > row1; row2--)
        t->row[row2] = t->row[row2-1];
      t->row[row1] = temp;
    }
  }
}

void
move_constant_rows_of_cp_table (CP_TABLE *t)
{
  CP_TABLE_ROW *src[MAX_NUM_LINK_PRED];
  BOOLEAN moved[MAX_NUM_LINK_PRED];
  int i;
  int r = 0;

  for (i = 0; i < t->num_rows; i++)
    moved[i] = FALSE;
  memcpy((char *) src, (char *) t->row, t->num_rows * sizeof(char *));

  /* Move constant rows */
  for (i = 0; i < t->num_rows; i++)
    if (constant_row(t->num_given, t->given, i, src)) {
      t->row[r] = src[i];
      r++;
      moved[i] = TRUE;
    }

  /* Move non-constant (ie non-moved) rows */
  for (i = 0; i < t->num_rows; i++)
    if (!moved[i]) {
      t->row[r] = src[i];
      r++;
    }
}

/* Create type expression for composite cursor. */

static TE *
get_unified_te (CTYPE *compcurs_ctype, CP_TABLE *t)
{
  TE *unified_te = NULL;
  ENTRY *e;
  CTYPE *ctype;
  TE *te1, *te2;
  int id1, id2;
  int i;

  if (t->num_curs == 1) {
    e = symlist_lookup(compcurs_ctype->ident->members, t->curs[0]);
    ctype = e->ident->ctype;
    te1 = ctype->cctype->te;

    unified_te = te1;
  }
  else if (t->num_curs >= 2) {
    e = symlist_lookup(compcurs_ctype->ident->members, t->curs[0]);
    ctype = e->ident->ctype;
    te1 = ctype->cctype->te;
    id1 = ctype->cctype->container_id;

    e = symlist_lookup(compcurs_ctype->ident->members, t->curs[1]);
    ctype = e->ident->ctype;
    te2 = ctype->cctype->te;
    id2 = ctype->cctype->container_id;
    unified_te = unify_te(te1, id1, te2, id2);

    for (i = 2; i < t->num_curs; i++) {
      e = symlist_lookup(compcurs_ctype->ident->members, t->curs[i]);
      ctype = e->ident->ctype;
      te1 = ctype->cctype->te;
      id1 = ctype->cctype->container_id;
      unified_te = unify_another_te(unified_te, te1, id1);
    }
  }
  return(unified_te);
}

static void
pre_opt_init_cp_table (CTYPE *compcurs_ctype, char *valid_predicate,
                       int num_given, char *given[])
{
  CP_TABLE *t = compcurs_ctype->cctype->cp_table;
  char *predicate = compcurs_ctype->cctype->predicate;

  init_fields_of_cp_table(compcurs_ctype, predicate, valid_predicate,
                          num_given, given, t);
  t->unified_te = get_unified_te(compcurs_ctype, t);
  add_cross_products_to_cp_table(t);
  group_rows_in_cp_table(t);
  sort_cp_table(t);
  move_constant_rows_of_cp_table(t);
}

static void
post_opt_init_cp_table (CTYPE *compcurs_ctype)
{
  CP_TABLE *t = compcurs_ctype->cctype->cp_table;
  init_lst_arg_of_cp_table(compcurs_ctype, t);
}

/*****************************************************************************/
/*                  Debugging stuff.                                         */
/*****************************************************************************/

#if PRINT_CP_TABLE_AS_COMMENT

char *
cp_type_enum_const_string (CP_TYPE type)
{
  switch (type) {
  case STRUCTURED:
    return("STRUCTURED");
  case EXPLICIT_LINK:
    return("EXPLICIT_LINK");
  case UNSTRUCTURED:
    return("UNSTRUCTURED");
  case CROSS_PRODUCT:
    return("CROSS_PRODUCT");
  }
  return(NULL);
}

void
print_cp_table (CP_TABLE *t)
{
  int i, j;

  printf("Num given: %d\n", t->num_given);
  printf("Given:");
  for (i = 0; i < t->num_given; i++)
    printf(" %s", t->given[i]);
  printf("\n");
  printf("Num_curs: %d\n", t->num_curs);
  printf("Curs:");
  for (i = 0; i < t->num_curs; i++)
    printf(" %s", t->curs[i]);
  printf("\n");
  printf("Valid: %s\n", (t->valid) ? "TRUE" : "FALSE");
  if (t->valid) {
    BOOLEAN clause_printed;

    /* exit_predicate */
    printf("Exit predicate: %s\n", t->exit_predicate);

    /* valid_predicate */
    clause_printed = FALSE;
    printf("Valid predicate: ");
    for (i = 0; i < t->num_curs; i++) {
      if (t->valid_predicate[i] != NULL) {
        if (clause_printed)
          printf(" && ");
        printf("%s", t->valid_predicate[i]);
        clause_printed = TRUE;
      }
    }
    printf("\n");
  }

  for (i = 0; i < t->num_rows; i++) {
    printf("Row %d:\n", i);
    printf("        num_curs: %d\n", t->row[i]->num_curs);
    if (t->row[i]->num_curs != 0) {
      printf("           curs: $");
      j = 0;
      while (j < t->row[i]->num_curs) {
        printf("%s", t->row[i]->curs[j]);
        j++;
        if (j < t->row[i]->num_curs)
          printf(", $");
      }
      printf("\n");
    }
    printf("      predicate: %s\n", t->row[i]->predicate);
    printf("           type: %s\n", cp_type_enum_const_string(t->row[i]->type));
  }
}

#endif /* PRINT_CP_TABLE_AS_COMMENT */

/*****************************************************************************/
/*                  Member nonterminals                                     */
/*****************************************************************************/

/* Given a composite cursor and member, return a nonterminal of the form:
   compcurs dot member. */

static NODE *
compcurs_dot_member (ECLASS eclass, NODE *compcurs, IDENT *member)
{
  CTYPE *ctype = (eclass == UNT) ? NULL : member->ctype;
  return(nonterm(eclass, ctype, 5,
                 terminal_string1("("),
                 compcurs,
                 terminal_string1(")"),
                 dot(),
                 terminal_ident(member)));
}

static char *
compcurs_dot_member_string (NODE *compcurs, char *member_string)
{
  char s[SPRINT_BUF_SIZE];
  size_t len = 0;
  IDENT *member = new_ident1(UNT, member_string, NULL, NULL, FALSE);
  NODE *n = compcurs_dot_member(UNT, compcurs, member);

  s[0] = '\0';
  print_ptree1(s, &len, n);
  /* Remove spaces so that the string may be used in a predicate. */
  remove_char(s, ' ');
  return(copy_string(s));
}

/*****************************************************************************/
/*                  Update given                                            */
/*****************************************************************************/

static void
update_given (int *num_given, char *given[], int i, CP_TABLE *t)
{
  int j;
  for (j = 0; j < t->row[i]->num_curs; j++)
    if (get_curs_pos(t->row[i]->curs[j], (*num_given), given) == -1) {
      given[(*num_given)] = t->row[i]->curs[j];
      (*num_given)++;
    }
}

/*****************************************************************************/
/*                  Compute predicate                                       */
/*****************************************************************************/

static void
compute_predicate (char *predicate,
                   int num_given, char *given[], int *i, CP_TABLE *t)
{
  do {
    if (predicate != NULL && !strcmp(t->row[(*i)]->predicate, "1") == 0)
      post_and(predicate, t->row[(*i)]->predicate);
    (*i)++;
  } while ((*i) < t->num_rows && constant_row(num_given, given, (*i), t->row));
}

/*****************************************************************************/
/*                  Bind compcurs predicate.                                 */
/*****************************************************************************/

/*
   "strcmp((xx.ee).obj->dept_name,\"Biology\") == 0
                                              12 34
    && (xx.ee).obj->deptno == P2_cursor_ref_dd.deptno"
                          12 34             5 6
*/

static void
bind_compcurs_predicate_rhs (NODE *compcurs, char *predicate, CP_TABLE *t)
{
  char *p1, *p2, *p3, *p4, *p5, *p6;
  char *hidden = CURSOR_REF_HIDDEN_STRING;
  int hidden_len = strlen(CURSOR_REF_HIDDEN_STRING);

  p4 = predicate;
  while (1) {
    /* Find space. */
    /* Fragile. */
    p1 = find_space(p4);
    if (p1 == NULL)
      return;
    p2 = p1 + whitespace_span(p1);
    if (relational_operator(p2)) {
      p3 = strchr(p2, ' ');
      if (p3 == NULL)
        return;
      p4 = p3 + whitespace_span(p3);

      if (strncmp(p4, hidden, hidden_len) == 0) {
        char sold[SPRINT_BUF_SIZE]; /* "P2_cursor_ref_member." */
        char snew[SPRINT_BUF_SIZE]; /* "(compcurs.field).obj->" */
        int i;
        char *s;

        p5 = p4 + strlen(CURSOR_REF_HIDDEN_STRING);
        p6 = strchr(p5, '.');
        if (p6 == NULL)
          return;
        strncpy(sold, p4, p6-p4+1);
        sold[p6-p4+1] = '\0';
        for (i = 0;
             (i < t->num_curs) && (strncmp(p5, t->curs[i], p6-p5) != 0);
             i++);
        if (i == t->num_curs) {
          parse_error("illegal cursor %s in compcurs predicate", sold);
        }
        s = compcurs_dot_member_string(compcurs, t->curs[i]);
        sprintf(snew, "(%s).obj->", s);
        replace_string_inplace1(p4, sold, snew, 1);
      }

      /* Find space. */
      /* Fragile. */
      p1 = find_space(p4);
      if (p1 == NULL)
        return;
      p2 = p1 + whitespace_span(p1);
    }
    if (strncmp(p2, "&&", 2) != 0)
      parse_error("expected &&");
    p3 = strchr(p2, ' ');
    if (p3 == NULL)
      return;
    p4 = p3 + whitespace_span(p3);
  }
}

/* Replace $member by CURSOR_REF_HIDDEN_STRING */

static char *
hide_cursor_refs (NODE *compcurs, char *p, CP_TABLE *t)
{
#ifndef NDEBUG
  if (p == NULL)
    assertion_failed("NULL string passed to hide_cursor_refs");
#endif /* NDEBUG */
  
  if (strcmp(p, "") == 0)
    return(p);
  else {
    char predicate[SPRINT_BUF_SIZE];
    strcpy(predicate, p);
    if (compcurs->ident->ctype->ident->members != NULL) {
      MCURSOR *mcurs = new_mcursor(compcurs->ident->ctype->ident);
      FOREACH_MEMBER(mcurs) {
        char cursor_ref[SPRINT_BUF_SIZE];
        char hidden[SPRINT_BUF_SIZE];

        /* Get cursor_ref string. */

        sprintf(cursor_ref, "$%s", mcurs->pos->ident->name);

        /* Get hidden string. */

        sprintf(hidden, "%s%s", CURSOR_REF_HIDDEN_STRING,
                mcurs->pos->ident->name);

        /* Replace cursor_ref string by hidden string. */

        replace_string_inplace(predicate, cursor_ref, hidden);
      }
    }
    return(copy_string(predicate));
  }
}

static char *
bind_compcurs_predicate (NODE *compcurs, char *predicate, CP_TABLE *t)
{
  char result[SPRINT_BUF_SIZE];
  char s1[MAX_IDENT_LEN+1];
  char *s2;
  MCURSOR *mcurs;
  IDENT *member_ident;
  IDENT *ele_ident;
  char *p;
  int i;

#ifndef NDEBUG
  if (predicate == NULL)
    assertion_failed("NULL string passed to bind_compcurs_predicate");
#endif /* NDEBUG */

  if (strcmp(predicate, "") == 0)
    return(predicate);
  else {

    mcurs = new_mcursor(compcurs->ident->ctype->ident);
    p = hide_cursor_refs(compcurs, predicate, t);
    i = 0;
    strcpy(result, p);
    xfree(p);
    FOREACH_MEMBER(mcurs) {
      bind_compcurs_predicate_rhs(compcurs, result, t);
      sprintf(s1, "%s%s", CURSOR_REF_HIDDEN_STRING, t->curs[i]);
      if (replace_string_inplace(result, s1, "$") > 0) {
        s2 = compcurs_dot_member_string(compcurs, t->curs[i]);
        member_ident = mcurs->pos->ident;
        ele_ident = member_ident->ctype->cctype->ident3->ele;
        p = bind_predicate1(member_ident->ctype->cctype->te,
                            s2, ele_ident, result);
        strcpy(result, p);
        xfree(p);
      }
      i++;
    }
    return(copy_string(result));
  }
}

/*****************************************************************************/
/*                  if predicate node.                                       */
/*****************************************************************************/

static NODE *
if_predicate_node (NODE *compcurs, char *predicate, NODE *ptree, CP_TABLE *t)
{
  NODE *result = ptree;
  if (predicate != NULL
      && predicate[0] != '\0'
      && strcmp(predicate, "1") != 0) {
    char *p = bind_compcurs_predicate(compcurs, predicate, t);

#if 0
    /* No longer necessary, because bind_predicate1() now transforms
       every single quote into a double quote even if it appears in
       an uninterpretable clause. */
    replace_char(p, '\'', '"');
#endif

    result = nonterm(UNT, NULL, 5,
                     terminal_string1("if ("),
                     terminal_string1(p),
                     terminal_string1(") {\n"),
                     ptree,
                     terminal_string1("}\n"));
  }
  return(result);
}

/*****************************************************************************/
/*                  foreachk nonterminal.                                    */
/*****************************************************************************/

/* Convert foreachk into nested foreachl's */
/* Note that given is a superset of t->given */

static NODE *
foreachk_nonterm1 (NODE *compcurs, CP_TABLE *t, NODE *ptree,
                   int num_given, char *given[], int i)
{
#ifndef NDEBUG
  if (i > t->num_rows)
    assertion_failed("i > t->num_rows");
  else
#endif /* NDEBUG */

  if (i == t->num_rows)
    return(ptree);
  else {
    if (constant_row(num_given, given, i, t->row)) {

      /* if (constant) */

      /* How should I bind the predicate??? (JAT) */

      char predicate[MAX_PRED_LEN];
      NODE *n1, *n2, *n3;

      predicate[0] = '\0';
      compute_predicate(predicate, num_given, given, &i, t); /* Modifies i. */
      n1 = foreachk_nonterm1(compcurs, t, ptree, num_given, given, i);
      n2 = if_predicate_node(compcurs, predicate, n1, t);
      n3 = nonterm(UNT, NULL, 2,
             terminal_string1("/* foreachk expanded as if (constant) */\n"),
             n2);
      return(n3);
    }
    else if (t->row[i]->num_curs == 2 && t->row[i]->type == EXPLICIT_LINK) {

      /* if (related) */

      NODE  *related_op;
      IDENT *cursor1, *cursor2;
      NODE  *related_param[3];
      NODE  *n1, *n2, *n3, *n4;
      
      update_given(&num_given, given, i, t);
      n1 = foreachk_nonterm1(compcurs, t, ptree, num_given, given, i+1);

      related_op = terminal_string1("related");
      cursor1 = compcurs_symlist_lookup(compcurs, t->row[i]->curs[0])->ident;
      cursor2 = compcurs_symlist_lookup(compcurs, t->row[i]->curs[1])->ident;
      related_param[0] = compcurs_dot_member(TYP, compcurs, cursor1);
      related_param[1] = compcurs_dot_member(TYP, compcurs, cursor2);
      related_param[2] = (NODE *) t->row[i]->lst_arg;
      n2 = special_op_nonterm1(related_op, related_param, 3, -1,
                               t->unified_te);

      n3 = nonterm(UNT, NULL, 5,
                   terminal_string1("if ("),
                   n2,
                   terminal_string1(") {\n"),
                   n1,
                   terminal_string1("}\n"));

      n4 = nonterm(UNT, NULL, 2,
             terminal_string1("/* foreachk expanded as if (related) */\n"),
             n3);
      return(n4);
    }
    else if (t->row[i]->num_curs == 1) {

      /* foreach */

      NODE *foreach_op;
      IDENT *cursor;
      NODE *foreach_param[2];
      NODE *n1, *n2, *n3;

      update_given(&num_given, given, i, t);
      n1 = foreachk_nonterm1(compcurs, t, ptree, num_given, given, i+1);

      foreach_op = terminal_string1("foreach");
      cursor = compcurs_symlist_lookup(compcurs, t->row[i]->curs[0])->ident;
      foreach_param[0] = compcurs_dot_member(TYP, compcurs, cursor);
      foreach_param[1] = if_predicate_node(compcurs, t->row[i]->predicate,
                                           n1, t);
      n2 = special_op_nonterm1(foreach_op, foreach_param, 2,
                               -1, t->unified_te);
      n3 = nonterm(UNT, NULL, 2,
                   terminal_string1("/* foreachk expanded as foreach */\n"),
                   n2);
      return(n3);
    }
    else if (t->row[i]->num_curs == 2) {

      /* foreachl, foreachp, or foreachc */

      NODE    *foreach_op;
      IDENT   *cursor1;
      IDENT   *cursor2;
      NODE    *foreach_param[4];
      NODE    *n1, *n2, *n3;
      char    *parent_curs = get_parent_curs(t, i);
      char    *child_curs = get_child_curs(t, i);
      BOOLEAN parent_given
                = (get_curs_pos(parent_curs, num_given, given) != -1);
      BOOLEAN child_given
                = (get_curs_pos(child_curs, num_given, given) != -1);

      if (!parent_given && !child_given)
        foreach_op = terminal_string1("foreachl");
      else if (parent_given && !child_given)
        foreach_op = terminal_string1("foreachc");
      else if (!parent_given && child_given)
        foreach_op = terminal_string1("foreachp");
#ifndef NDEBUG
      else
        assertion_failed("both parent and child are given");
#endif

      update_given(&num_given, given, i, t);
      n1 = foreachk_nonterm1(compcurs, t, ptree, num_given, given, i+1);

      cursor1 = compcurs_symlist_lookup(compcurs, parent_curs)->ident;
      cursor2 = compcurs_symlist_lookup(compcurs, child_curs)->ident;
      foreach_param[0] = compcurs_dot_member(TYP, compcurs, cursor1);
      foreach_param[1] = compcurs_dot_member(TYP, compcurs, cursor2);
      foreach_param[2] = (NODE *) t->row[i]->lst_arg;
      foreach_param[3] = if_predicate_node(compcurs, t->row[i]->predicate, n1,
                                           t);
      n2 = special_op_nonterm1(foreach_op, foreach_param, 4, -1,
                               t->unified_te);
      n3 = nonterm(UNT, NULL, 4,
                   terminal_string1("/* foreachk expanded as"),
                   foreach_op,
                   terminal_string1("*/\n"),
                   n2);
      return(n3);
    }
  }
  return(foreachk_nonterm1(compcurs, t, ptree, num_given, given, i+1));
}

/* Replace deleted($member) by DELETED_HIDDEN_STRING */

static char *
hide_deleted (NODE *compcurs, char *p, CP_TABLE *t)
{
  if (strcmp(p, "") == 0)
    return(p);
  else {
    char predicate[SPRINT_BUF_SIZE];
    strcpy(predicate, p);
    if (compcurs->ident->ctype->ident->members != NULL) {
      MCURSOR *mcurs = new_mcursor(compcurs->ident->ctype->ident);
      FOREACH_MEMBER(mcurs) {
        char deleted[SPRINT_BUF_SIZE];
        char hidden[SPRINT_BUF_SIZE];

        /* Get deleted string. */

        sprintf(deleted, "deleted($%s)", mcurs->pos->ident->name);

        /* Get hidden string. */

        sprintf(hidden, "%s%s", DELETED_HIDDEN_STRING,
                mcurs->pos->ident->name);

        /* Replace deleted string by hidden string. */

        replace_string_inplace(predicate, deleted, hidden);
      }
    }
    return(copy_string(predicate));
  }
}

/* Replace DELETED_HIDDEN_STRING by the expansion of deleted($member) */

static char *
expand_deleted_nonterm (NODE *compcurs, char *p, CP_TABLE *t)
{
#ifndef NDEBUG
  if (p == NULL)
    assertion_failed("NULL string passed to hide_deleted_predicate");
#endif
  
  if (strcmp(p, "") == 0)
    return(p);
  else {
    char predicate[SPRINT_BUF_SIZE];
    strcpy(predicate, p);
    if (compcurs->ident->ctype->ident->members != NULL) {
      MCURSOR *mcurs = new_mcursor(compcurs->ident->ctype->ident);
      FOREACH_MEMBER(mcurs) {
        char hidden[SPRINT_BUF_SIZE];
        char expansion[SPRINT_BUF_SIZE];
        NODE *deleted_op = terminal_string1("deleted");
        NODE *deleted_param[1];
        NODE *n;

        /* Get deleted string. */

        sprintf(hidden, "%s%s", DELETED_HIDDEN_STRING,
                mcurs->pos->ident->name);

        /* Get expansion string. */

        deleted_param[0]
          = compcurs_dot_member(TYP, compcurs, mcurs->pos->ident);
        n = special_op_nonterm1(deleted_op, deleted_param, 1, -1,
                                t->unified_te);
        sprint_ptree(expansion, n);

        /* Replace hidden string by expansion string. */

        replace_string_inplace(predicate, hidden, expansion);
      }
    }
    return(copy_string(predicate));
  }
}

static NODE *
if_not_valid_goto_node (NODE *compcurs, char *predicate,
                        char *label, CP_TABLE *t)
{
  NODE *result = NULL;

  if (predicate != NULL) {
    char *p1 = hide_deleted(compcurs, predicate, t);
    char *p2 = bind_compcurs_predicate(compcurs, p1, t);
    char *p3 = expand_deleted_nonterm(compcurs, p2, t);
    NODE *n1 = nonterm(UNT, NULL, 5,
                       terminal_string1("if(!("),
                       terminal_string1(p3),
                       terminal_string1(")) goto"),
                       terminal_string1(label),
                       terminal_string1(";"));
    result = n1;

    xfree(p1);
    xfree(p2);
  }
  return(result);
}

static int
valid_node1 (NODE *compcurs, CP_TABLE *t,
             int num_given, char *given[], int i,
             int num_valid_node, NODE *valid_node[])
{
  if (i == t->num_rows)
    return(num_valid_node);
  else {
    if (constant_row(num_given, given, i, t->row)) {
      compute_predicate(NULL, num_given, given, &i, t); /* Modifies i. */
      return(valid_node1(compcurs, t,
                         num_given, given, i,
                         num_valid_node, valid_node));
    }
    else if (t->row[i]->num_curs == 2 && t->row[i]->type == EXPLICIT_LINK) {
      update_given(&num_given, given, i, t);
      return(valid_node1(compcurs, t,
                         num_given, given, i,
                         num_valid_node, valid_node));
    }
    else if (t->row[i]->num_curs == 2) {
      int j;
      for (j = 0; j < 2; j++) {
        char *curs = t->row[i]->curs[j];
        BOOLEAN curs_given = (get_curs_pos(curs, num_given, given) != -1);
        if (!curs_given) {
          int pos = get_curs_pos(curs, t->num_curs, t->curs);
          ENTRY *e = symlist_lookup(compcurs->ident->ctype->ident->members,
                                    curs);
          IDENT *member = e->ident;
          char *label
            = new_label_name(loop_id_counter,
                             member->ctype->cctype->cursor_id);
          NODE *n1 = if_not_valid_goto_node(compcurs, t->valid_predicate[pos],
                                            label, t);
          /* Add n1 even if it is NULL (as a place holder). */
          valid_node[num_valid_node] = n1;
          num_valid_node++;
        }
      }
      update_given(&num_given, given, i, t);
      return(valid_node1(compcurs, t,
                         num_given, given, i,
                         num_valid_node, valid_node));
    }
  }
  return(valid_node1(compcurs, t,
                     num_given, given, i+1,
                     num_valid_node, valid_node));
}

static NODE *
valid_node (NODE *compcurs, CP_TABLE *t, NODE *ptree)
{
  NODE *result;

  if (!t->valid)
    result = ptree;
  else {
    char *given[MAX_NUM_LINK_CURS];
    NODE *valid_node[MAX_NUM_LINK_PRED];
    int num_valid_node;
    int i;

    /* Add (possibly un-necessary) braces. */
    char *exit_label = new_exit_label_name(loop_id_counter);
    NODE *n1 = if_not_valid_goto_node(compcurs, t->exit_predicate,
                                      exit_label, t);
    result = nonterm(UNT, NULL, 4,
                     terminal_string1("{"),
                     ptree,
                     terminal_string1("}"),
                     n1);

    /* given = t->given */
    memcpy((char *) given, (char *) t->given, t->num_given * sizeof(char *));

    /* Get valid nodes. */
    num_valid_node
      = valid_node1(compcurs, t, t->num_given, given, 0, 0, valid_node);

    /* Add all valid nodes other than the last (inner-most) to the ptree. */
    for (i = 0; i < num_valid_node-1; i++)
      result = nonterm(UNT, NULL, 2, result, valid_node[i]);
  }
  return(result);
}

static NODE *
foreachk_nonterm (NODE *compcurs, CP_TABLE *t, NODE *ptree)
{
  char *given[MAX_NUM_LINK_CURS];
  NODE *n1, *n2;
  NODE *result;
  char *exit_label;

  /* Increment loop_id_counter. */
  loop_id_counter++;
  enable_continue_labels = t->valid;

  n1 = valid_node(compcurs, t, ptree);

  /* given = t->given */
  memcpy((char *) given, (char *) t->given, t->num_given * sizeof(char *));

  n2 = foreachk_nonterm1(compcurs, t, n1, t->num_given, given, 0);
  exit_label = new_exit_label_name(loop_id_counter);
  result = nonterm(UNT, NULL, 3,
                   n2,
                   terminal_string1(exit_label),
                   terminal_string1(":;"));

  enable_continue_labels = FALSE;
  return(result);
}

/*****************************************************************************/
/*                  Compcurs special operation nonterminal node.             */
/*****************************************************************************/

/*
   advk()
   endk()
   foreachk()
   initk()    initialize all non-given cursors
   resetk()
*/

NODE *
compcurs_special_op_nonterm (NODE *op, NODE *params)
{
  int m = num_params(params);
  NODE *compcurs = nth_param(1, m, params);
  CTYPE *ctype = compcurs->ident->ctype;
  char *name = op->ident->name;
  BOOLEAN foreachk = (strcmp(name, "foreachk") == 0);
  BOOLEAN endk = (strcmp(name, "endk") == 0);
  BOOLEAN resetk = (strcmp(name, "resetk") == 0);
  BOOLEAN initk = (strcmp(name, "initk") == 0);

  NODE *xformed_ptree;
  int j; /* Index over arguments to op. */
  CP_TABLE *t;
  MCURSOR *mcurs;
  NODE *param[MAX_OP_PARAM];

  NODE *n1, *n2;
  NODE *upd_op;
  NODE *member_op;
  NODE *member_param[1];
  IDENT *member_ident;
  
  /* If not a composite cursor special operation, return NULL. */
  if (!actual_matches_formal_param(ctype, KCUR)
      || !(foreachk || endk || resetk || initk))
    return(NULL);

  /* Otherwise, return the appropriate ptree. */
  else {
    xformed_ptree = NULL;
    t = ctype->cctype->cp_table;
    mcurs = new_mcursor(ctype->ident);

    /* Make sure we won't be writing past the end of the param array. (JAT) */
    if (m > MAX_OP_PARAM)
       parse_error("%d arguments to compcurs special op %s exceeds maximum %d",
                   m, op->ident->name, MAX_OP_PARAM);

    /* Fill in param. */
    for (j = 0; j < m; j++) {
      param[j] = nth_param(j+1, m, params);
    }

    /* foreachk() */
    if (foreachk) {
      if (m != 2)
        parse_error("%d arguments to special op foreachk which expects 2", m);
      xformed_ptree = foreachk_nonterm(compcurs, t, param[1]);
    }

    /* endk(), initk(), resetk() */
    else {
      if (m != 1)
        parse_error("%d args to compcurs special op %s which expects 1",
                    m, name);

      else {
        if (endk)
          member_op = terminal_string1("end_adv");
        else if (initk) {
          member_op = terminal_string1("init_curs");
          upd_op = terminal_string1("upd");
        }
        else /* (resetk) */
          member_op = terminal_string1("reset_start");

        FOREACH_MEMBER(mcurs) {
          member_ident = mcurs->pos->ident;
          member_param[0] = compcurs_dot_member(TYP, compcurs, member_ident);
          n1 = special_op_nonterm1(member_op, member_param, 1, -1,
                                   t->unified_te);
          if (initk) {
            if (te_requires_kcur(member_ident->ctype->cctype->te)) {
              /* member.kcur = &(compcurs) */
              n2 = nonterm(UNT, NULL, 4,
                           member_param[0],
                           terminal_string(".kcur = &("),
                           compcurs,
                           terminal_string(");"));
              xformed_ptree = nonterm(UNT, NULL, 3, xformed_ptree, n1, n2);
            }
            else
              xformed_ptree = nonterm(UNT, NULL, 2, xformed_ptree, n1);
          }
          else if (xformed_ptree != NULL && endk)
            /* When xformed_ptree is not NULL and endk(),
               concatinate together the parse trees,
               separated by the logical or operator ("&&"). */
            xformed_ptree = nonterm(TYP, int_read_only_ctype, 3,
                                    xformed_ptree,
                                    terminal_string1("&&"),
                                    n1);
          else
            /* When xformed_ptree is NULL, or operation is not initk()
               or endk(), concatinate together just the parse trees. */
            xformed_ptree = nonterm(UNT, NULL, 2, xformed_ptree, n1);
        } /* FOREACH_MEMBER */
        if (endk)
          xformed_ptree = nonterm(TYP, int_read_only_ctype, 3,
                                  leftp(),
                                  xformed_ptree,
                                  rightp());
      }
    }

#if PRINT_CALL_AS_COMMENT || PRINT_ARGS_AS_COMMENT
    return(special_op_nonterm_comments(op, param, m, -1, NULL, xformed_ptree));
#else
    return(xformed_ptree);
#endif
  }
}

/*****************************************************************************/
/*                  Pairs parse tree management.                             */
/*****************************************************************************/

#ifndef NDEBUG
static void
assert_pair_list_valid  (NODE *pair_list)
{
  /* Make sure pair list is non-NULL */

  if (pair_list == NULL)
    assertion_failed("pair_list is NULL");

  /* Make sure pair list has the correct number of arguments. */

  else {
    int narg = pair_list->narg;

    if (narg != 0 && narg != 2 && narg != 4)
      assertion_failed("pair_list->narg == %d", narg);

    /* If pair list has 4 arguments, make sure the 3rd is a comma. */

    if (narg == 4 && strcmp(pair_list->arg[2]->ident->name, ",") != 0)
      assertion_failed("pair_list->arg[2]->ident->name != \",\"");
  }
}
#endif /* NDEBUG */

static int
num_pairs (NODE *pair_list)
{
#ifndef NDEBUG
  assert_pair_list_valid(pair_list);
#endif /* NDEBUG */

  if (pair_list->narg == 0)
    return(0);
  else if (pair_list->narg == 2)
    return(1);
  else
    return(1 + num_pairs(pair_list->arg[3]));
}

static NODE *
nth_pair (int n, NODE *pair_list)
{
#ifndef NDEBUG
  if (n < 1)
    assertion_failed("argument n to nth_pair < 1");
#endif /* NDEBUG */

  if (n == 1)
    return(pair_list);
  else
    return(nth_pair(n-1, pair_list->arg[3]));
}

/*****************************************************************************/
/*                  Compcurs declaration.                                    */
/*****************************************************************************/

static char *
new_compcurs_name (void)
{
  static int compcurs_counter = 0;
  char   s[MAX_IDENT_LEN+10];

  sprintf(s, "P2_composite_cursor%d", compcurs_counter++);
  return(copy_string(s));
}

/* Have parent inherit from child certain fields that clear_decl()
   will throw away. */

static void
inherit_fields (DECL *parent, DECL *child)
{
  /* declared_but_unprinted */
#if 1
  /* Throw this away */
#else
  concat_symlist(&parent->declared_but_unprinted,
                 child->declared_but_unprinted);
#endif

  /* verbatim_ptree */
  parent->verbatim_ptree
    = nonterm(UNT, NULL, 2, parent->verbatim_ptree, child->verbatim_ptree);

  /* op_vec_ptree */
  parent->op_vec_ptree
    = nonterm(UNT, NULL, 2, parent->op_vec_ptree, child->op_vec_ptree);
}

/* It is (only?) necessary to have this pre-options function,
   because the action for the predicate option modifies decl->btype->ident,
   which would not exist if we didn't first call this function. (JAT) */

void
pre_opt_compcurs_declaration (void)
{
#if 0
  decl->btype = COMPOSITE_CURSOR_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(COMPOSITE_CURSOR_CTYPE);
#endif
  decl->btype->cctype = xmalloc_object(CCTYPE);
  memset((void *) decl->btype->cctype, 0, sizeof(CCTYPE));
  decl->btype->ident = new_struct(new_compcurs_name(), TRUE);
}

static void
pre_opt_member_action (NODE *cursor_container_pair_list_opt)
{
  DECL *parent = decl;
  int m = num_pairs(cursor_container_pair_list_opt);
  int n; /* iterator over pairs. */

  /* Make sure parent is a composite cursor */
  assert(ctypematch1(parent->btype, composite_cursor_read_only_ctype, TRUE));

  push_decl();
  /* foreach pair */
  for (n = 0; n < m; n++) {
    NODE  *pair = nth_pair(n+1, cursor_container_pair_list_opt);
    NODE  *member_curs_ptree = pair->arg[0];
    NODE  *member_cont_ptree = pair->arg[1];

#if 0
    IDENT *member_cont_ident
      = symtab_symbol_has_expected_ctype(symtab[OTH],
          member_cont_ptree->ident->name,
          container_read_only_ctype, "container");

    /* Declare member cursor. */
    member_cont_ptree->ident->ctype = member_cont_ident->ctype;
#else
    ptree_has_expected_ctype(member_cont_ptree,
                             container_read_only_ctype, "container");
#endif

    pre_opt_cursor_declaration(member_cont_ptree);

    /* Save member cursor declaration. */
    decl->symlist = &parent->btype->ident->members;
    decl->name = member_curs_ptree->ident->name;
    save_decl();

    /* Clear declaration. */
    clear_decl();
  }
  pop_decl();
}

/* Add kcur here, by duplicating decl->btype->ident, adding kcur to
   it, and adding it to declared but unprinted. */

static void
add_kcur (DECL *parent)
{
  char curs_type[MAX_IDENT_LEN];
  ENTRY *struct_entry;
  IDENT *struct_ident;
  CTYPE *member_ctype;
  IDENT *member_ident;
  IDENT3 *ident3;  
  
  sprintf(curs_type, "%s_kcur", decl->btype->ident->name);
  /* Look for previously defined _kcur. */
  struct_entry = symtab_lookup(symtab[SUE], curs_type);
  if (struct_entry == NULL)
    struct_entry = symlist_lookup(parent->declared_but_unprinted, curs_type);
  
  if (struct_entry != NULL) {
    /* Found previously defined _kcur, use it. */
    struct_ident = struct_entry->ident;
    decl->btype->ident = struct_ident;
    decl->btype->cctype->ident3 = struct_ident->ctype->cctype->ident3;
  }
  else {
    /* Otherwise, define _kcur. */
    /* _kcurs struct. */
    struct_ident = copy_ident(decl->btype->ident);
    struct_ident->name = copy_string(curs_type);
    decl->btype->ident = struct_ident;
    /* ident3 */
    ident3 = xmalloc_object(IDENT3);
    memcpy(ident3, decl->btype->cctype->ident3, sizeof(IDENT3));
    ident3->cur = struct_ident;
    decl->btype->cctype->ident3 = ident3;
    struct_ident->ctype->cctype->ident3 = ident3;
    /* kcur member */
    member_ctype = pointer_struct_read_only_ctype;
    member_ctype->ident = parent->btype->ident;
    member_ident = new_ident1(MBR, "kcur", member_ctype, NULL, FALSE);
    add_ident_to_symlist(&struct_ident->members, member_ident);
    /* Declare _kcur struct. */
    add_ident_to_symtab(symtab[SUE], struct_ident);
    /* Print _kcur struct. */
    /* Since inherit_fields() throws away member decl's declared_but_unprinted,
       add it to parent's declared_but_unprinted. */
    add_ident_to_symlist(&parent->declared_but_unprinted, struct_ident);
  }
}

static void
post_opt_member_action (NODE *cursor_container_pair_list_opt, CP_TABLE *t)
{
  DECL *parent = decl;
  int m = num_pairs(cursor_container_pair_list_opt);
  char predicate[SPRINT_BUF_SIZE];
  char s[MAX_IDENT_LEN+1];
  char *given[MAX_NUM_LINK_CURS];
  int num_given;
  int n; /* iterator over pairs. */

  /* Make sure that the number of pairs is in the allowable range. */

  if (m == 0)
    parse_warning(3, "composite cursor has no member cursors");
  if (m > MAX_NUM_LINK_CURS)
    parse_error("composite cursor has %d member cursors, maximum is %d",
                m, MAX_NUM_LINK_CURS);

  /* given = t->given */
  memcpy((char *) given, (char *) t->given, t->num_given * sizeof(char *));
  num_given = t->num_given;

  push_decl();
  /* foreach pair */
  for (n = 0; n < m; n++) {
    ENTRY *e;
    NODE  *pair = nth_pair(n+1, cursor_container_pair_list_opt);
    NODE  *member_curs_ptree = pair->arg[0];
    NODE  *member_cont_ptree = pair->arg[1];

#if 0
    IDENT *member_cont_ident
      = symtab_symbol_has_expected_ctype(symtab[OTH],
          member_cont_ptree->ident->name,
          container_read_only_ctype, "container");
    member_cont_ptree->ident->ctype = member_cont_ident->ctype;
#else
    /* This test can probably be omitted, since the same test is performed in
       pre_opt_member_action() (JAT) */
    ptree_has_expected_ctype(member_cont_ptree,
                             container_read_only_ctype, "container");
#endif

    decl->symlist = &parent->btype->ident->members;
    decl->name = member_curs_ptree->ident->name;

    /* Declare member cursor. */
    e = symlist_lookup(*(decl->symlist), decl->name);
#if 0
    decl->btype = e->ident->ctype;
    assert_ctype_valid(decl->btype);
#else
    set_btype(e->ident->ctype);
#endif

    given[num_given] = decl->name;
    num_given++;

#if 1
    /* Add constant row predicates to member cursor retrieval predicate. */
    predicate[0] = '\0';
    if (get_curs_pos(decl->name, t->num_given, t->given) == -1) {
      /* This member cursor is not given. */
      int i;
      for (i = 0; i < t->num_rows; i++) {
        if (get_curs_pos(decl->name, t->row[i]->num_curs,
                         t->row[i]->curs) != -1) {
          /* This member cursor appears in this row predicate. */
          if (constant_row(num_given, given, i, t->row)) {
            post_and(predicate, t->row[i]->predicate);
            strcpy(t->row[i]->predicate, "1");
          }
        }
      }
      sprintf(s, "$%s", decl->name);
      replace_string_inplace(predicate, s, "$");
    }
    decl->btype->cctype->predicate = predicate;
#endif

    if (te_requires_kcur(decl->btype->cctype->te))
      /* Add kcur */
      add_kcur(parent);

    /* Set optimization parameters, verbatim_ptree, and op_vec_ptree */
    post_opt_cursor_declaration(member_cont_ptree);

    /* Save member cursor declaration. */
    save_decl();

    inherit_fields(parent, decl);

    /* Clear declaration. */
    clear_decl();
  }
  pop_decl();
}

static void
check_compcurs_predicate (CTYPE *compcurs_ctype)
{
  char *predicate = compcurs_ctype->cctype->predicate;
  char *compcurs_curs[MAX_NUM_LINK_CURS];
  char *predicate_curs[MAX_NUM_LINK_CURS];
  char *predicate_only_curs[MAX_NUM_LINK_CURS];
  char *compcurs_only_curs[MAX_NUM_LINK_CURS];
  int num_compcurs_curs = get_num_members(compcurs_ctype, compcurs_curs);
  int num_predicate_curs = get_num_curs(predicate, predicate_curs);
  int num_compcurs_only_curs;
  int num_predicate_only_curs;

  curs_difference(num_compcurs_curs, num_predicate_curs,
                  &num_compcurs_only_curs, &num_predicate_only_curs,
                  compcurs_curs, predicate_curs,
                  compcurs_only_curs, predicate_only_curs);

  /* Report an error if a cursor appears in the predicate,
     but not in the composite cursor declaration. */

  if (num_predicate_only_curs != 0) {
    char s[SPRINT_BUF_SIZE];
    size_t len = 0;
    int i = 0;

    s[0] = '\0';
    while (i < num_predicate_only_curs) {
      print1(s, &len, predicate_only_curs[i]);
      i++;
      if (i < num_predicate_only_curs)
        print2(s, &len, " ", 1);
    }

    parse_error("compcurs %s predicate \"%s\"\n"
                "references undefined cursor%s %s",
                compcurs_ctype->ident->name,
                predicate,
                (num_predicate_only_curs == 1) ? "" : "s", s);
  }
}

void
post_opt_compcurs_declaration (NODE *cursor_container_pair_list_opt,
                               NODE *given_opt, NODE *valid_opt)
{
  char *valid_predicate;
  NODE *given_cursor_list = (given_opt->narg == 0) ? NULL : given_opt->arg[2];
  char *given[MAX_NUM_LINK_CURS];
  int num_given = get_num_identifiers(given_cursor_list, given);
  int orderby_direction = decl->btype->cctype->orderby_direction;
  CP_TABLE *t;

  /* Initialize members. */
  pre_opt_member_action(cursor_container_pair_list_opt);

  /* Orderby. */
  /* Note: This works by ordering one of the member cursors, which
     works for nested loops (nloops), but probably not for other join
     implementations. (JAT) */
  if (orderby_direction != 0) {
    char *orderby_cursor = decl->btype->cctype->orderby_cursor;
    if (orderby_cursor == NULL)
      error("Empty orderby cursor");
    else {
      ENTRY *e = symlist_lookup(decl->btype->ident->members, orderby_cursor);
      if (e == NULL)
        error("Orderby cursor %s not a member of composite cursor",
              orderby_cursor);
      else {
        char *orderby_field = decl->btype->cctype->orderby_field;
        IDENT *member = e->ident;
        member->ctype->cctype->orderby_field = orderby_field;
        member->ctype->cctype->orderby_direction = orderby_direction;
        assert(member->ctype->cctype->orderby_cursor == NULL);
      }
    }
  }

  /* Valid predicate .*/
  if (valid_opt->narg == 0)
    valid_predicate = NULL;
  else {
    /* Strip quotes. */
    valid_predicate = &(valid_opt->arg[1]->ident->name[1]);
    valid_predicate[strlen(valid_predicate)-1] = '\0';
  }
  /* Cursor-Predicate table. */
  t = decl->btype->cctype->cp_table = xmalloc_object(CP_TABLE);
  pre_opt_init_cp_table(decl->btype, valid_predicate, num_given, given);

  check_compcurs_predicate(decl->btype);
  /* post_opt_member_action initializes the cursor arguments (JAT) */
  post_opt_member_action(cursor_container_pair_list_opt, t);
  /* post_opt_init_cp_table uses the cursor arguments. (JAT) */
  post_opt_init_cp_table(decl->btype);

#if PRINT_CP_TABLE_AS_COMMENT
  printf("/*\n");
  printf("cursor predicate table for %s\n", decl->btype->ident->name);
  print_cp_table(t);
  printf("*/\n");
#endif /* PRINT_CP_TABLE_AS_COMMENT */
}
