/* $Id: pb-actions.c,v 45.11 1997/09/24 14:55:48 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* pb parser action definitions. */

/* This file contains routines to implement parse actions called from
   the pb parser.  These routines could be inlined in the pb parser
   bison source file, but putting these routines in a separate file
   (1) simplifies debugging and (2) speeds compilation. (JAT) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>       /* assert() */
#include <stdio.h>        /* NULL, sprintf() */
#include <stdlib.h>       /* size_t */
#include <string.h>       /* strcpy(), strlen() */

#include "arg.h"          /* CURS_ARG */
#include "call-down.h"    /* call_level() */
#include "compcurs.h"     /* compcurs_special_op_nonterm() */
#include "data-type.h"    /* str_hash() */
#include "drc.h"          /* drc() */
#include "error.h"        /* parse_error() */
#include "io.h"           /* SPRINT_BUF_SIZE */
#include "pb-actions.h"
#include "pb-io.h"        /* sprint_decl() */
#include "pb-type.h"      /* clear_decl() */
#include "pb-xform.h"     /* new_struct() */
#include "qopt.h"         /* MAX_QOPT_COST */
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* empty(), decl, DECL, CTYPE, IDENT */
#include "typex.h"        /* TLIST */
#include "util.h"         /* BOOLEAN */
#include "xform.h"        /* PATH */
#include "xmalloc.h"      /* xmalloc() */

/*****************************************************************************/
/*                  Constants                                                */
/*****************************************************************************/

/* Maximum length of a type expression name. */

#define MAX_TYPEX_LEN \
   (MAX_TE_ARG*MAX_PATH_LEN+1)

/* Rather than inlining special operations, proceduralize them
   as calls through op_vec or as calls to named functions. */

#define FUNCALL 1

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

typedef struct {
  NODE *cont_node[MAX_OP_PARAM];
  NODE *icont_node[MAX_OP_PARAM];
  NODE *curs_node[MAX_OP_PARAM];
  NODE *rec_node[MAX_OP_PARAM];
  NODE *vptr_node[MAX_OP_PARAM];
  NODE *int_node[MAX_OP_PARAM];
  NODE *expr_node[MAX_OP_PARAM];
} FORMAL_NODES;

/*****************************************************************************/
/*                  Assertions                                               */
/*****************************************************************************/

void
assert_curs_arg_valid (CURS_ARG *arg)
{
#ifndef NDEBUG
  if (arg == NULL || strcmp(arg->expr, "") == 0)
    assertion_failed("invalid curs arg");
  assert_string_valid(arg->expr);
#endif /* NDEBUG */
}

/*****************************************************************************/
/*                  Function definition actions.                             */
/*****************************************************************************/

void
pre_function_definition_action (void)
{
#if 0
  /* For some reason, this check is too strong,
     and (incorrectly) finds parse errors in correct programs (JAT). */
  if (base_ptype(decl->dtype)->pclass != FUN)
    parse_error("expected a function definition");
#endif

  /* Save the declaration of the function name. */
  save_decl();
  clear_decl();

  /* Create a new scope for the function body. */
  /* Resurrect the formal parameters */
  push_scope(TRUE);
}

void
post_function_definition_action (void)
{
#if 0
  int size_in_bytes = symtab[LAB]->size * sizeof(SYMLIST *);
  pop_scope();
  /* Labels have function scope. (JAT) */
  memset((void *) symtab[LAB]->table[scope], 0, size_in_bytes);
#else
  pop_scope();
#endif
}

/*****************************************************************************/
/*                  Function call actions.                                   */
/*****************************************************************************/

NODE *
function_call_nonterm (NODE *postfix_expression,
                       NODE *argument_expression_list)
{
  /* Is this a special operation or ordinary function call? */
  NODE *n = special_op_nonterm(postfix_expression, argument_expression_list);
  if (n == NULL)
  {
    /* Ordinary function call. */
    CTYPE *ctype = copy_ctype(postfix_expression->ident->ctype);
    reduce(ctype, FUN);
    n = nonterm(TYP, ctype, 4,
                postfix_expression,
                leftp(),
                argument_expression_list,
                rightp());
  }
  return n;
}

/*****************************************************************************/
/*                  Cast expression actions.                                 */
/*****************************************************************************/

void
pre_cast_expression_action (void)
{
  push_decl();
}

NODE *
post_cast_expression_action (NODE *type_name, NODE *cast_expression)
{
  CTYPE *c = copy_ctype(decl->btype);
  NODE *n;

  append(c, decl->dtype);
  n = nonterm(TYP, c, 4, leftp(), type_name, rightp(), cast_expression);
  pop_decl();
  return n;
}

NODE *
unary_operator_cast_expression_nonterm (NODE *unary_operator,
                                        NODE *cast_expression)
{
  CTYPE *ctype = copy_ctype(cast_expression->ident->ctype);
  NODE *n;

  if (unary_operator->narg != 0)
    parse_error("illegal unary operator cast expression");
  if (strcmp(unary_operator->ident->name, "&") == 0)
    expand(ctype, new_ptype(PTR, UND, NULL));
  else if (strcmp(unary_operator->ident->name, "*") == 0)
    reduce(ctype, PTR);
  n = nonterm(TYP, ctype, 2, unary_operator, cast_expression);
  return n;
}

/*****************************************************************************/
/*                  Left and right paren actions.                            */
/*****************************************************************************/

/* These actions are invoked when left or right parentheses are seen
   in declarations.  It is necessary to associate these actions with a
   parenthesis (rather than a production), because the pushing of scope
   and decl must be done as soon as the parenthesis is seen (shifted),
   rather than after the entire production is seen (reduced).  It is
   necessary to associate these actions whith all parentheses in
   declarations, because shift-reduce conflicts result if we try to
   associate different actions (or different non-terminals) with
   different parenthesis. (JAT) */

void
left_paren_action (void)
{
  push_scope(FALSE);
  push_decl();
}

void
right_paren_action (void)
{
  /* If the declaration has a base type, then save the declaration. */

  /* This case applies to:
       int x(int y);    prototyped function
                  ^
       int (*x)(int y); prototyped function (second parentheses)
                     ^
       int (*x)(int);   prototyped function (second parentheses)
                   ^
   */

  if (decl->btype->len != 0) {
    save_decl();
    pop_decl();
    pop_scope();
  }

  /* Otherwise, the declaration does not have a base type,
     append the type of the child declaration to the type
     of the parent declaration.  Also, if the child declaration
     has a name, make it the name of the parent declaration. */

  /* This case applies to:
       int (x);         redundant parentheses
             ^
       int x();         non-prototyped function without arguments
             ^
       int x(y);        non-prototyped function with arguments
              ^
       int (*x)(int y); function pointer (first parentheses)
              ^
       int (*x)(int);   function pointer (first parentheses)
              ^
       int (*x)();      function pointer (first parentheses)
              ^
       int (*x)();      non-prototyped function (second parentheses)
                ^
   */

  else {
    DECL *child = decl;
    pop_decl();
    pop_scope();
    append(decl->dtype, child->dtype);
    if (child->name != NULL && decl->name == NULL)
      decl->name = child->name;
  }
}

/*****************************************************************************/
/*                  Aggregate actions.                                       */
/*****************************************************************************/

void
unnamed_aggregate_declaration_action (void)
{
  DECL *parent;
  IDENT *i;

  /* Declaration of un-named aggregate. */

  decl->name = new_unnamed_sue_name();
  i = new_ident(SUE, decl->name, decl->btype, NULL, FALSE);
  i->ctype->ident = i;
  decl->btype->ident = i;
  add_ident_to_symtab1(symtab[SUE], i);
  clear_dtype();
  parent = decl;
  push_decl();
  decl->eclass = MBR;
  decl->symlist = &parent->btype->ident->members;
}

void
named_aggregate_declaration_action (NODE *aggregate_name)
{
  ENTRY *e;
  DECL *parent;
  IDENT *i;

  /* Declaration of named aggregate. */

  e = symtab_lookup(symtab[SUE], aggregate_name->ident->name);
  if (e == NULL) {
    /* Declaration of not previously referenced aggregate. */
    i = new_ident(SUE, decl->name, decl->btype, NULL, FALSE);
    i->ctype->ident = i;
    decl->btype->ident = i;
    add_ident_to_symtab1(symtab[SUE], i);
  }
  else if (e->ident->forward == FALSE)
    /* Re-declaration of aggregate. */
    parse_error("re-declaration of aggregate %s", aggregate_name->ident->name);
  else {
    /* Declaration of forward referenced aggregate. */
    i = e->ident;
#if 0
    decl->btype = i->ctype;
    assert_ctype_valid(decl->btype);
#else
    set_btype(i->ctype);
#endif
    i->forward = FALSE;
    add_ident_to_symlist(&decl->declared_but_unprinted, i);
  }
  clear_dtype();
  parent = decl;
  push_decl();
  decl->eclass = MBR;
  decl->symlist = &parent->btype->ident->members;
}

void
aggregate_reference_action (NODE *aggregate_name)
{
  ENTRY *e;
  IDENT *i;

  /* Reference to aggregate */
              
  e = symtab_lookup(symtab[SUE], aggregate_name->ident->name);
  if (e == NULL) {
    /* Forward reference to aggregate. */
    i = new_ident1(SUE, aggregate_name->ident->name, decl->btype, NULL, FALSE);
    i->ctype->ident = i;
    i->forward = TRUE;
    add_ident_to_symtab(symtab[SUE], i);
  }
  else
    /* Non-forward reference to aggregate. */
    i = e->ident;
#if 0
  decl->btype = i->ctype;
  assert_ctype_valid(decl->btype);
#else
  set_btype(i->ctype);
#endif
  clear_dtype();
}

/*****************************************************************************/
/*                  enum actions.                                            */
/*****************************************************************************/

void
unnamed_enum_declaration_action (void)
{
  IDENT *i;

  /* Declaration of un-named enumeration. */

#if 0
  decl->btype = ENUM_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(ENUM_CTYPE);
#endif
  decl->name = new_unnamed_sue_name();
  i = new_ident(SUE, decl->name, decl->btype, NULL, FALSE);
  i->ctype->ident = i;
  decl->btype->ident = i;
  push_decl();
}

void
named_enum_declaration_action (NODE *enum_name)
{
  ENTRY *e;
  IDENT *i;

  /* Declaration of named enumeration. */

#if 0
  decl->btype = ENUM_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(ENUM_CTYPE);
#endif
  e = symtab_lookup(symtab[SUE], enum_name->ident->name);
  if (e == NULL) {
    /* Declaration of not previously referenced enumeration. */
    i = new_ident(SUE, decl->name, decl->btype, NULL, FALSE);
    i->ctype->ident = i;
    decl->btype->ident = i;
    add_ident_to_symtab1(symtab[SUE], i);
  }
  else if (e->ident->forward == FALSE)
    /* Re-declaration of enumeration. */
    parse_error("re-declaration of enumeration %s", enum_name->ident->name);
  else {
    /* Declaration of forward referenced enumeration. */
    i = e->ident;
#if 0
    decl->btype = i->ctype;
    assert_ctype_valid(decl->btype);
#else
    set_btype(i->ctype);
#endif
    i->forward = FALSE;
    add_ident_to_symlist(&decl->declared_but_unprinted, i);
  }
  push_decl();
}

void
enum_reference_action (NODE *enum_name)
{
  ENTRY *e;
  IDENT *i;

  /* Reference to enumeration. */

#if 0
  decl->btype = ENUM_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(ENUM_CTYPE);
#endif
  e = symtab_lookup(symtab[SUE], enum_name->ident->name);
  if (e == NULL) {
    /* Forward reference to enumeration. */
    i = new_ident(SUE, enum_name->ident->name, decl->btype, NULL, FALSE);
    i->ctype->ident = i;
    i->forward = TRUE;
    add_ident_to_symtab(symtab[SUE], i);
  }
  else
    /* Non-forward reference to enumeration. */
    i = e->ident;
#if 0
  decl->btype = i->ctype;
  assert_ctype_valid(decl->btype);
#else
  set_btype(i->ctype);
#endif
  clear_dtype();
}

/*****************************************************************************/
/*                  Element action                                           */
/*****************************************************************************/

/* type_specifier is a container or cursor */

/* Set the decl->btype to the transformed element type of the given
   container or cursor.  Return a parse tree containing the element
   type (unnecessary if element<...> is used in a declaration, but
   necessary if it is used in an expression. */

NODE *
element_nonterm (NODE *type_specifier)
{
  CTYPE *ctype;
  IDENT *ident;

  ctype = type_specifier->ident->ctype;
  if (ctype == NULL || ctype->cctype == NULL)
    parse_error("element parameter must be container or cursor");
  assert(ctype->cctype->ident3 != NULL);

  ident = ctype->cctype->ident3->ele;
  assert(ident != NULL);

#if 0
  decl->btype = ident->ctype;
  assert_ctype_valid(decl->btype);
#else
  set_btype(ident->ctype);
#endif

  return(nonterm(UNT, NULL, 2,
                 terminal_string1("struct"), terminal_ident(ident)));
}

/*****************************************************************************/
/*                  Params parse tree management                             */
/*****************************************************************************/

/* Assuming params is the parse tree returned by an
argument_expression_list nonterminal, return the number of
parameters that it represents. */

int
num_params (NODE *params)
{
  if (params == NULL)
    return(0);
  else if (params->narg != 3)
    return(1);
  else if (params->arg[1]->ident->name == NULL
           || strcmp(params->arg[1]->ident->name, ",") != 0)
    return(1);
  return(1 + num_params(params->arg[0]));
}

/* Assuming params is the parse tree returned by an
   argument_expression_list nonterminal, and params represents a total of
   m parameters, return the ptree of the n > 0 th parameter represented
   by params. (JAT) */

NODE *
nth_param (int n, int m, NODE *params)
{
#ifndef NDEBUG
  if (n < 1 || n > m)
    assertion_failed("argument n to nth_param_ptree %s",
                     (n < 1) ? "n < 1" : "n > m");
#endif /* NDEBUG */

  if (params == NULL)
    return(NULL);
  else if (m == 1)
    return(params);
  else if (m == n)
    return(params->arg[2]);
  else
    return(nth_param(n, m - 1, params->arg[0]));
}

/*****************************************************************************/
/*                  Convert param[] to params parse tree                     */
/*****************************************************************************/

/* Given an array of n param, return a single nonterminal having the same
   form as the parse tree returned for the argument_expression_list:
   param[0] , param[1] , ... , param[n-1] */

NODE *
param_to_params (int n, NODE *param[])
{
  if (n == 1)
    return(param[0]);
  else
    return(nonterm(UNT, NULL, 3,
                   param_to_params(n-1, param),
                   comma(),
                   param[n-1]));
}

/*****************************************************************************/
/*                  Params to path and tlist.                                */
/*****************************************************************************/

/* Assuming params is the parse tree returned by an argument_expression_list,
   fill-in the name or path array that it represents and
   return the number of arguments that it represents. */

/* Formerly, this code was (largely) duplicated in params_to_tlist()
   and params_to_path().  I have factored the (largely) duplicated
   code into this procedure and use the name parameter to distinguish
   between the two cases.  Calling this procedure with name equal to
   TRUE indicates the case where this code would be appropriate for
   params_to_tlist() (JAT) */

/* If name is TRUE, assume params is a typex and name_or_path is char **name.
   Otherwise, assume name_or_path is a path and name_or_path is PATH *path. */

static int
params_to_name_or_path (NODE *params, void *name_or_path, BOOLEAN name)
{
  int m = num_params(params);
  int min_args = (name) ? 3 : 2;
  int max_args = (name) ? MAX_TYPEX_LEN : MAX_PATH_LEN;
  char *typex_or_path = (name) ? "typex" : "path";
  int i;

  /* Check number of parameters. */

  if (m < min_args)
    parse_error("number of arguments to P2_%s < %d", typex_or_path, min_args);
  if (m > max_args)
    parse_error("number of arguments to P2_%s > %d", typex_or_path, max_args);

  for (i = 0; i < m; i++) {
    NODE   *param_ptree = nth_param(i+1, m, params);
    IDENT  *param_ident = param_ptree->ident;
    CTYPE  *param_ctype = param_ident->ctype;
    char   *param_name  = param_ident->name;
    size_t len;

    /* Make sure parameter has type pointer to char. */

    if (!string_ctype(param_ctype))
      parse_error("argument %d must be of type pointer to char", i+1);

#ifndef NDEBUG
    if (param_ptree->narg != 0)
      assertion_failed("node of type pointer to char has narg != 0");
#endif /* NDEBUG */

    len = strlen(param_name);

#ifndef NDEBUG
    if (len < 2)
      assertion_failed("quoted name of layer has length < 2");
#endif /* NDEBUG */

    /* Make sure name has quotes. */

    if (param_name[0] != '"' || param_name[len-1] != '"')
      parse_error("argument %d to P2_typex must have quotes around it", i+1);

    /* Copy.  Skip leading quote.  Delete trailing quote. */

    if (name) {
      /* Pointer copy. */
      ((char **) name_or_path)[i] = copy_string1(param_name+1, len-1);
      ((char **) name_or_path)[i][len-2] = '\0';
      check_typex_or_layer_name(((char **) name_or_path)[i], len-2, i);
    }
    else {
      /* Character copy. */
      strcpy((*(PATH *) name_or_path)[i].str, param_name+1);
      ((*(PATH *) name_or_path)[i].str)[len-2] = '\0';
    }
  }
  return(m);
}

/* Assuming params is the parse tree returned by an argument_expression_list,
   return the tlist that it represents. */

inline static TLIST *
params_to_tlist (NODE *params)
{
  char *name[MAX_TYPEX_LEN];
  TLIST *tlist;
  int m;

  /* Fill-in name array. */
  /* Each entry in the name array will be a pointer to an array of
     characters representing the quoted name of a layer. */

  m = params_to_name_or_path(params, name, TRUE);

  /* Fill-in TLIST. */

  /* Explicit cast is necessary to match function prototype. */
  tlist = new_tlist((const char **) name, m-1);

  /* Return. */

  return(tlist);
}

/* Assuming params is the parse tree returned by an argument_expression_list,
   return the path that it represents. */

inline static PATH *
params_to_path (NODE *params)
{
  PATH *path = (PATH *) xmalloc(sizeof(PATH));
  
  /* Fill-in path array. */
  /* Each entry in the name array will be a pointer to an array of
     characters representing the quoted name of a layer. */

  params_to_name_or_path(params, path, FALSE);

  /* Return. */

  return(path);
}

/*****************************************************************************/
/*                  Predicate option.                                        */
/*****************************************************************************/

void
predicate_opt_declaration (char *predicate)
{
  /* Every cursor declaration specializes the cursor declaration of
     the specified container.  The specialization amounts to pairing
     the cursor structure with the cursor's predicate. (DSB) */

  /* Note that we have to strip off the quotes in predicate--that's
     why we're copying from predicate+1 and truncating the string. */

  if (predicate == NULL)
    decl->btype->cctype->predicate = "1";
  else {
    size_t len = strlen(predicate);
    decl->btype->cctype->predicate = xmalloc_atomic(len);
    strcpy(decl->btype->cctype->predicate, predicate+1);
    decl->btype->cctype->predicate[len-2] = '\0';
  }
}

/*****************************************************************************/
/*                  Orderby option.                                          */
/*****************************************************************************/

void
orderby_opt_action (int orderby_direction,
                    char *orderby_cursor, char *orderby_field)
{
  decl->btype->cctype->orderby_cursor = copy_string(orderby_cursor);
  decl->btype->cctype->orderby_field = copy_string(orderby_field);
  decl->btype->cctype->orderby_direction = orderby_direction;
}

/*****************************************************************************/
/*                  ddlhints                                                 */
/*****************************************************************************/

/* Make a call to adorn as specified by a P2_ddlhint declaration.
   Most of what this involves is re-packaging the arguments to the
   P2_ddlhint declaration into a form appropriate for the adorn call. */

void
ddlhint_declaration (char *cont_name, NODE *path_params,
                     char *layer_name_with_quotes, NODE *annotation_params)
{
  static TE *te = NULL;
  BOOLEAN schema = ctypematch(decl->btype, schema_read_only_ctype);

#ifndef NDEBUG
  /* Make sure the current declaration is a schema or container. */
  if (!schema && !ctypematch(decl->btype, container_read_only_ctype))
    assertion_failed("expected schema or container");
#endif /* NDEBUG */

  if (strcmp(cont_name, "P2_default") == 0)
  {
    if (!schema)
    {
      /* Non-schema member container: use te from decl */
      te = decl->btype->cctype->te;
    }
    else
      error("must provide container name in schema ddlhint_declaration");
  }
  else
  {
    if (schema)
    {
      /* Schema member container: find ident in schema symlist,
         use te from this ident */
#if 0
      IDENT *ident
        = symlist_symbol_has_expected_ctype(decl->btype->ident->members,
                                            cont_name,
                                            container_read_only_ctype,
                                            "container");
#else
      ENTRY *entry = symlist_lookup(decl->btype->ident->members, cont_name);
      if (entry == NULL)
        parse_error("couldn't find container name \"%s\" in schema",
                    cont_name);
#if 0
      if (ctypematch1(entry->ident->ctype, container_read_only_ctype, TRUE))
#else
      if (base_ptype(entry->ident->ctype)->pclass == CON)
#endif
        te = entry->ident->ctype->cctype->te;
      else
        parse_error("argument \"%s\" to ddlhint_declaration is not"
                    " a container", cont_name);
#endif
    }
    else
      parse_error("incorrect container name \"%s\" in schema"
                  " ddlhint_declaration", cont_name);
  }

#ifndef NDEBUG
  /* Make sure te is non-NULL. */
  if (te == NULL)
    assertion_failed("NULL te in ddlhint_declaration");
#endif /* NDEBUG */

  /* Obtain the rest of the arguments for the call to adorn. */

  {
    int  annotec;     /* Number of annotations. */
    NODE **annotev;   /* Annotations. */
    char *layer_name; /* Layer name w/o quotes. */
    PATH *path;       /* name or path array represeted by path_params ptree. */
    int  n;           /* Index over parameters (and annotations). */
    int  m;           /* Number of annotations. */

    path = params_to_path(path_params);
    layer_name = copy_string(layer_name_with_quotes+1);
    layer_name[strlen(layer_name)-1] = '\0';

    /* Call adorn with 0-th parameter = cont_name */

    m = num_params(annotation_params);
    annotec = m + 1;
    annotev = (NODE**) xmalloc(annotec * sizeof(struct node_struct *));
    annotev[0] = (NODE *) cont_name; /* A string, not a ptree node */
    for (n = 1; n < annotec; n++)
      annotev[n] = nth_param(n, m, annotation_params);
    adorn(te, path, layer_name, annotec, annotev);
  }
}

/*****************************************************************************/
/*                  Binary operation nonterminal                             */
/*****************************************************************************/

NODE *
binop_nonterm (NODE *n1, NODE *name, NODE *n2)
{
  CTYPE *ctype;

  if (!ctypematch(n1->ident->ctype, n2->ident->ctype))
    parse_error("binary operator data type mismatch");
  ctype = binary_convert(n1->ident->ctype, n2->ident->ctype);
  return(nonterm(TYP, ctype, 3, n1, name, n2));
}

/*****************************************************************************/
/*                  Identifier expression nonterminal                        */
/*****************************************************************************/

NODE *
identifier_expression_nonterm (NODE *n)
{
  char *name = n->ident->name;
  ENTRY *entry = symtab_lookup(symtab[OTH], name);
  NODE *new_node;

  if (entry == NULL)
  {
    CTYPE *ctype = function_int_read_only_ctype;
    IDENT *ident = new_ident1(OTH, name, ctype, NULL, TRUE);
    /* Default identifier to a type function returning int. */
    parse_warning(1, "defaulting %s to type fn returning int", name);
    add_ident_to_symtab1(symtab[OTH], ident);
    /* ident defaulted == TRUE only in the symtab. */
    /* Why, so sprint_decl() will print the symbol??? (JAT) */
    new_node = terminal1(OTH, name, ctype);
  }
  else
  {
    IDENT *ident = entry->ident;
    char  *pname;

    if (ident->pname == NULL)
      /* Normal case: use name. */
      pname = name;
    else
      /* Special case: use pname. */
      pname = ident->pname;

    new_node = terminal1(OTH, pname, ident->ctype);
  }
  new_node->line_number = n->line_number;
  return(new_node); 
}

/*****************************************************************************/
/*                  Declarator nonterminal                                   */
/*****************************************************************************/

/* If (1) the decl->btype or decl->dtype has indirect_only equal to
   TRUE, (2) decl is a direct reference, and (3) the parse tree of
   declarator is s, set the pname of decl to "(*s)", effectively
   replacing all occurrences of "s" by "(*s)".  Print a warning
   indicating that this replacement has been performed. */

static char *
indirect_pname (char *name)
{
  char pname[MAX_IDENT_LEN+100];
  size_t len = 0;
  
  /* pname = (*declarator) */
  pname[0] = '\0';
  print2(pname, &len, "(*", 2);
  print1(pname, &len, name);
  print2(pname, &len, ")", 1);
  warning(1, "added indirection: replacing %s by %s", name, pname);
  if (len > MAX_IDENT_LEN)
    parse_error("print name \"%s\" too long", pname);
  return(copy_string(pname));
}

NODE *
declarator_nonterm (NODE *declarator)
{
  CTYPE *ctype;

  if (decl->dtype->len == 0)
    ctype = decl->btype;
  else
  {
    ctype = copy_ctype(decl->btype);
    append(ctype, decl->dtype);
  }

  if (ctype->cctype != NULL
      && ctype->cctype->indirect_only && direct_ctype(ctype)
      && !ctypematch1(ctype, schema_read_only_ctype, TRUE))
  {
    char name[MAX_IDENT_LEN];
    sprint_ptree(name, declarator);
    decl->pname = indirect_pname(name);
    return(terminal(OTH, decl->pname, undefined_read_only_ctype));
  }
  else
    return(declarator);
}

/*****************************************************************************/
/*                  Unthread and delete from symlist and symtab.             */
/*****************************************************************************/

static void
unthread_entry_from_symlist (SYMLIST **symlist, ENTRY *e)
{
  if (e->prev != NULL)
    e->prev->next = e->next;
  else
    (*symlist)->first = e->next;

  if (e->next != NULL)
    e->next->prev = e->prev;
  else
    (*symlist)->last = e->prev;
}

static void
delete_entry_from_symlist (SYMLIST **symlist, char *name)
{
  ENTRY *e = symlist_lookup(*symlist, name);
  unthread_entry_from_symlist(symlist, e);
}

static void
delete_entry_from_symtab (SYMTAB *symtab, char *name)
{
  unsigned key = str_hash(name, symtab->size);
  delete_entry_from_symlist(&symtab->table[scope][key], name);
}

/*****************************************************************************/
/*                  Sort symbol list.                                        */
/*****************************************************************************/

/*
   Sort symlist according to the dependencies between symbols
   so that, after symlist is sorted, the declarations could be
   legally made in the order they appear in symlist.

   Consider the following example:

       / * This declaration depends on struct P2_foo_cont_prim_cont.
       / * Thus, this declaration must be printed after P2_foo_cont_prim_cont
       struct P2_foo_cont
          {
            struct P2_foo_cont_prim_cont prim2;
            struct P2_foo_cont_sec_cont sec2;
          };

        ...

        / * struct P2_foo_cont_prim_cont depends on this declaration.
        / * Thus, this declaration must be printed before P2_foo_cont
        struct P2_foo_cont_prim_cont
          {
            struct P2_foo_cont_prim_xf *next_element4;
            struct P2_foo_cont_prim_xf elements4[10];
          };

  In the example above, struct P2_foo_cont includes a field of type
  struct P2_foo_cont_prim_cont.  Thus, the declaration of P2_foo_cont
  depends on the declaration of P2_foo_cont_prim_cont.
  Thus, the declaration of P2_foo_cont_prim_cont must occur before the
  declaration of P2_foo_cont.  Thus, sort_symlist must sort the
  symlist such that P2_foo_cont_prim_cont appears on symlist before
  P2_foo_cont appears on symlist.

*/

/* If the given entry appears after an entry that depends on it,
   return the entry (TRUE).  Otherwise, return NULL (FALSE). */

inline static ENTRY *
entry_out_of_order (ENTRY *entry)
{
  IDENT *ident;
  CTYPE *ctype;
  ENTRY *d, *m;

  assert(entry != NULL);
  ident = entry->ident;
  assert(ident != NULL);
  ctype = ident->ctype;
  assert_ctype_valid(ctype);
  if (aggregate_ctype(ctype))
  {
    for (d = entry->next; d != NULL; d = d->next)
    {
      assert(d->ident != NULL);
      assert_ctype_valid(d->ident->ctype);
      if (aggregate_ctype(d->ident->ctype)
          && d->ident->ctype->ident->members != NULL)
        for (m = d->ident->ctype->ident->members->last; m != NULL; m = m->prev)
        {
          assert_ctype_valid(m->ident->ctype);
          if (aggregate_or_aggregate_array_ctype(m->ident->ctype))
          {
            assert(m->ident->ctype->ident->name != NULL);
            assert(ident->name != NULL);
            if (strcmp(m->ident->ctype->ident->name, ident->name) == 0)
              return(d);
          }
        }
    }
  }
  return(NULL);
}

/* If a cycle exists in the dependencies, then this procedure would go
   into an infinte recursive loop and never terminate.  Thus, I use the
   variable recursion_depth to keep track of the depth of the recursion
   and terminate if it gets to deep. (JAT) */

#define SORT_SYMLIST_MAX_RECURSION_DEPTH 10

static void
sort_symlist (SYMLIST **symlist)
{
  BOOLEAN recursion;
  int     recursion_depth = 0;
  ENTRY   *e; /* entry */
  ENTRY   *d; /* dependency */

  do {
    recursion = FALSE;
    recursion_depth++;
    if (recursion_depth > SORT_SYMLIST_MAX_RECURSION_DEPTH)
      error("sort_symlist max_recursion_depth exceeded");
    for (e = (*symlist)->last; e != NULL; e = e->prev) {
      d = entry_out_of_order(e);
      if (d != NULL)
      {
        recursion = TRUE;
        /* Move entry (e) behind dependency (d)
           (so that entry will be printed before dependency). */
        unthread_entry_from_symlist(symlist, e);
        e->next = d->next;
        d->next = e;
        if (e->next != NULL)
          e->next->prev = e;
        e->prev = d;
        if ((*symlist)->last == d)
          (*symlist)->last = e;
      }
    }
  } while (recursion);
}

/*****************************************************************************/
/*                  Declaration parse tree                                   */
/*****************************************************************************/

/* Return a parse tree containing:
   (1) the declarations in decl->declared_but_unprinted_labels
   (2) the declarations in decl->declared_but_unprinted
   (3) the parse tree decl->verbatim_ptree
   (4) the parse tree decl->op_vec_ptree
*/

NODE *
decl_ptree (void)
{
  NODE  *n = empty();
  ENTRY *e;
  char  s[SPRINT_BUF_SIZE];

  /* GNU addition: local labels */
  if (decl->declared_but_unprinted_labels != NULL)
  {
    for (e = (decl->declared_but_unprinted_labels)->last;
         e != NULL; e = e->prev)
    {
      sprintf(s, "__label__ %s;", e->ident->name);
      n = nonterm(UNT, NULL, 2, n, terminal_string(s));
    }
    decl->declared_but_unprinted_labels = NULL;
  }

  if (decl->declared_but_unprinted != NULL)
  {
    sort_symlist(&decl->declared_but_unprinted);
    for (e = (decl->declared_but_unprinted)->last; e != NULL; e = e->prev)
    {
      sprint_decl(s, e->ident);
      n = nonterm(UNT, NULL, 2, n, terminal(OTH, s, e->ident->ctype));
    }
    decl->declared_but_unprinted = NULL;
  }
  if (decl->verbatim_ptree != NULL)
  {
    n = nonterm(UNT, NULL, 2, n, decl->verbatim_ptree);
    decl->verbatim_ptree = NULL;
  }
  if (decl->op_vec_ptree != NULL)
  {
    n = nonterm(UNT, NULL, 2, n, decl->op_vec_ptree);
    decl->op_vec_ptree = NULL;
  }
  return n;
}

/*****************************************************************************/
/*                  Container declaration.                                   */
/*****************************************************************************/

void
pre_typex_container_declaration (NODE *type_specifier)
{
  /* A call to lookup_struct is unnecessary, since the existing
     declaration mechanisms have already interpreted the (typedef or sue)
     name base type ident as the base type of the declaration. */

  IDENT *orig_type = decl->btype->ident;

#ifndef NDEBUG
  assert(decl->btype->ident != NULL);
  assert(orig_type != NULL);
#endif /* NDEBUG */

#if 0
  decl->btype = CONTAINER_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(CONTAINER_CTYPE);
#endif
  decl->btype->cctype = xmalloc_object(CCTYPE);
  /* Assign NULL values to cctype->cont (and other cctype fields). */
  memset((void *) decl->btype->cctype, 0, sizeof(CCTYPE));
  /* Make sure cont is NULL. */
  assert(decl->btype->cctype->cont == NULL);
  /* Assign non-NULL values to cctype fields. */
  decl->btype->cctype->arg = xmalloc_object(CONT_ARG);
  decl->btype->cctype->orig_type = orig_type;

  /* Except for schema containers, it is not necessary to make this
     assignment of cont_type here--we we could make it later, say in
     post_ddlhint_container_declaration().  It is necessary for schema
     containers, because otherwise the type_specifier would be
     completely unknown to post_ddlhint_schema_declaration() (JAT) */

  decl->btype->cctype->cont_type = new_container_name(type_specifier);
}

/* Create a *new* type expression tree (TE) from the linear format (TLIST),
   given the name of a TLIST. */

TE *
typex_name_to_te (char *typex_name)
{
  TLIST *tlist;
  TE *te;

  check_typex_or_layer_name(typex_name, strlen(typex_name), 0);

  /* Look-up the type expression corresponding to typex_name. */

  tlist = is_typex(typex_name);
  if (tlist == NULL)
    parse_error("expected a type expression");

  te = tlist_to_te(tlist);
  assert_te_valid(te);

  return(te);
}

/* Set a container's cctype->te and other related fields. */

void
set_container_cctype_te (CCTYPE *cctype, TE *te)
{
  cctype->indirect_only = te_requires_indirect_only(te);
  cctype->proceduralize_ref = te_requires_proceduralize_ref(te);
  cctype->te = te;
}

/* Get rid of cont_type argument??? (JAT) */
/* It's gone. (JAT) */

IDENT3 *
container_declaration_ident3 (TE *te, IDENT *ele, char *cont_name)
{
  /* container_declaration_ident3 returns a triplet of structure idents:
     transformed_element, cursor, and container.  The ele parameter
     structure is copied.  The naming convention for these generated
     structures is:

        P2_<cont_name>_xf
        P2_<cont_name>_cont
        P2_<cont_name>_curs
  */

  /* Allocate idents and result. */
  IDENT3 *result = xmalloc_object(IDENT3);
  char xfname[MAX_IDENT_LEN];
  char cont_type[MAX_IDENT_LEN];
  char curs_type[MAX_IDENT_LEN];

  /* Create names. */
  sprintf(xfname,   "P2_%s_xf",   cont_name);
  sprintf(cont_type, "P2_%s_cont", cont_name);
  sprintf(curs_type, "P2_%s_curs", cont_name);

  /* Copy input element structure, and copy generic cursor and container. */
  /* Element. */
  result->ele = copy_ident(ele);
  result->ele->name = copy_string(xfname);
  result->ele->ctype->cctype = xmalloc_object(CCTYPE);
  memset((void *) result->ele->ctype->cctype, 0, sizeof(CCTYPE));
  add_ident_to_symtab1(symtab[SUE], result->ele);
  /* Container. */
  result->con = new_struct(cont_type, TRUE);
  result->con->ctype->cctype = xmalloc_object(CCTYPE);
  memset((void *) result->con->ctype->cctype, 0, sizeof(CCTYPE));
  /* Cursor. */
  result->cur = new_struct(curs_type, TRUE);
  result->cur->ctype->cctype = xmalloc_object(CCTYPE);
  memset((void *) result->cur->ctype->cctype, 0, sizeof(CCTYPE));
  init_cursor_def(result->cur, result->ele, result->con);

  /* Add initialized and op_vec fields to container. */
  init_container_def(result->con);

  /* Assign container id. */
  result->con->ctype->cctype->container_id = cont_id_counter;

  /* Transform created element types. */
  layer_counter = 1;

#if 0
  /* Old. */
  call_level(te, XFORM_OP, 3, result->ele, result->con, result->cur);
#else
  /* New. Or, can we store the cont_name information elsewhere??? (JAT) */
  call_level(te, XFORM_OP, 4, result->ele, result->con, result->cur, cont_name);
#endif

  /* Increment cont_id_counter. */
  cont_id_counter++;

  /* Make base pclass of container and cursor CON and CUR respectively. */
  (*result->con->ctype->stype)[result->con->ctype->len-1]->pclass = CON;
  (*result->cur->ctype->stype)[result->cur->ctype->len-1]->pclass = CUR;

  /* Return result. */
  return(result);
}
   
/* The cont_name is necessary to find correct annotation
   (we'll find the cont_id from cont_id_counter++) */

static void
set_ctype_ident3 (CTYPE *ctype, char *typex_name, char *cont_name)
{
  CCTYPE *cctype = ctype->cctype;
  TE *te = cctype->te;
  IDENT3 *ident3;

  check_for_missing_annotations(te, cont_name);
  drc(te, typex_name);

  /* Note that container_declaration_ident3() calls xform. */
  ident3 = container_declaration_ident3(te, cctype->orig_type, cont_name);
  ctype->ident = ident3->con;
  cctype->ident3 = ident3;
  cctype->container_id = ident3->con->ctype->cctype->container_id;
  /* ident->ctype->cctype->cont is unknown at this point. */
  cctype->op_list = new_op_list(ctype, cctype->orig_type, CON);
}

void
post_ddlhint_container_declaration (char *typex_name)
{
  /* Use decl->btype->cctype->cont_type (a type name) as cont_name */
  set_ctype_ident3(decl->btype, typex_name, decl->btype->cctype->cont_type);

  decl->verbatim_ptree = verbatim_nonterm(decl->btype, CON);
  if (te_requires_op_vec(decl->btype->cctype->te))
    decl->op_vec_ptree = op_vec_nonterm(decl->btype, CON);
}

/*****************************************************************************/
/*                  Schema containers.                                       */
/*****************************************************************************/

void
schema_container_declaration (NODE *type_specifier)
{
  DECL *parent = parent_decl();

  if (parent == NULL
      || !ctypematch1(parent->btype, schema_read_only_ctype, TRUE))
    parse_error("container declaration must specify a stored_as"
                " type expression or be part of a schema declaration");
  pre_typex_container_declaration(type_specifier);
  /* Schema name is set in pb/pb-gram.y */
  /* Make sure cctype->schema is NULL. */
  assert(decl->btype->cctype->schema == NULL);

#if 0
  /* We don't know the schema name yet (the schema name is specified
     at the end of the schema declaration), but since there can only be
     one schema, we can pick a name arbitrarily. */
  decl->btype->cctype->schema = "P2_schema";
#endif
}

/*****************************************************************************/
/*                  Generic containers.                                      */
/*****************************************************************************/

void
generic_container_declaration (NODE *type_specifier)
{
  IDENT *ident;
  CTYPE *ctype = copy_ctype1(struct_read_only_ctype, FALSE);
  IDENT *orig_type = decl->btype->ident;

#ifndef NDEBUG
  assert(decl->btype->ident != NULL);
  assert(orig_type != NULL);
#endif /* NDEBUG */

  /* Create generic container struct. */

  ident = new_ident1(GCON, new_unnamed_sue_name(), ctype, NULL, FALSE);
  ctype->ident = ident;
  init_container_def(ident);
  add_ident_to_symtab1(symtab[SUE], ident);

  /* Set decl->btype */

#if 0
  decl->btype = GENERIC_CONTAINER_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(GENERIC_CONTAINER_CTYPE);
#endif
  decl->btype->ident = ident;
  decl->btype->cctype = xmalloc_object(CCTYPE);
  memset((void *) decl->btype->cctype, 0, sizeof(CCTYPE));
  decl->btype->cctype->arg = xmalloc_object(CONT_ARG);
  decl->btype->cctype->indirect_only = TRUE;
  decl->btype->cctype->proceduralize_ref = TRUE;
  decl->btype->cctype->orig_type = orig_type;
  decl->btype->cctype->op_list = new_op_list(decl->btype, orig_type, CON);
}

/*****************************************************************************/
/*                  curs, cont, rec and vptr arg strucures.                  */
/*****************************************************************************/

void
new_curs_arg (CURS_ARG *arg, NODE *op, int j,
              NODE *ptree, CTYPE *ctype, int funbody)
{
  char     s[SPRINT_BUF_SIZE];
  IDENT3   *ident3 = ctype->cctype->ident3;
  size_t   len = 0;
  
  s[0] = '\0';
  if (ctype->cctype->cursor_id == GENERIC_CURS_ID) {
    /* Generic cursor. */
    print2(s, &len, "(*", 2);
    print_ptree1(s, &len, ptree);
    print2(s, &len, ")", 1);
  }
  else {
#ifndef NDEBUG
    /* Make sure that we're not going to be de-referencing any NULL pointers */
    if (ident3 == NULL
        || ident3->cur == NULL || ident3->cur->name == NULL
        || ident3->con == NULL || ident3->con->name == NULL
        || ident3->ele == NULL || ident3->ele->name == NULL)
      assertion_failed("%s cursor arg %d has a NULL ident3 pointer",
        op->ident->name, j+1);
#endif /* NDEBUG */
    
    print_ptree1(s, &len, ptree);

    strcpy(arg->type, ident3->cur->name);
    strcpy(arg->cont, ctype->cctype->cont);
    strcpy(arg->cont_type, ident3->con->name);
    if (ctype->cctype->schema == NULL)
      arg->schema[0] = '\0';
    else
      strcpy(arg->schema, ctype->cctype->schema);
    strcpy(arg->obj_type, ident3->ele->name);
    if (ctype->cctype->predicate == NULL)
      arg->predicate[0] = '\0';
    else
      strcpy(arg->predicate, ctype->cctype->predicate);
    arg->retrieval_direction = ctype->cctype->retrieval_direction;
  }
  
#ifndef NDEBUG
  if (len > ARG_STR_LEN-1)
    assertion_failed("cursor expression too long to fit into CURS_ARG.expr");
#endif /* NDEBUG */

  strcpy(arg->expr, s);
  arg->funbody           = funbody;
  arg->proceduralize_ref = ctype->cctype->proceduralize_ref;
  if (ctype->cctype->orderby_field == NULL)
    arg->orderby_field[0] = '\0';
  else
    strcpy(arg->orderby_field, ctype->cctype->orderby_field);
  arg->orderby_direction = ctype->cctype->orderby_direction;
  strcpy(arg->orig_type, ctype->cctype->orig_type->name);
  arg->cost              = ctype->cctype->cost;
  arg->layer             = ctype->cctype->layer;
  arg->cursor_id         = ctype->cctype->cursor_id;
  arg->container_id      = ctype->cctype->container_id;
  arg->op_list           = ctype->cctype->op_list;
  arg->bound             = FALSE;
}

static void
new_cont_arg (CONT_ARG *arg, NODE *op, int j,
              NODE *ptree, CTYPE *ctype, int funbody)
{
  char     s[SPRINT_BUF_SIZE];
  IDENT3   *ident3 = ctype->cctype->ident3;
  size_t   len = 0;
  
  s[0] = '\0';
  if (ident3 == NULL) {
    /* Generic container. */
    print2(s, &len, "(*", 2);
    print_ptree1(s, &len, ptree);
    print2(s, &len, ")", 1);
    arg->container_id = GENERIC_CONT_ID;
  }
  else {
#ifndef NDEBUG
    /* Make sure we're not going to be de-referencing any NULL pointers. */
    if (ident3 == NULL
        || ident3->con == NULL || ident3->con->name == NULL
        || ident3->ele == NULL || ident3->ele->name == NULL)
      assertion_failed("%s container arg %d has a NULL ident3 pointer",
        op->ident->name, j+1);
#endif /* NDEBUG */

    print_ptree1(s, &len, ptree);

    strcpy(arg->type, ident3->con->name);
    if (ctype->cctype->schema == NULL)
      arg->schema[0] = '\0';
    else
      strcpy(arg->schema, ctype->cctype->schema);
    strcpy(arg->obj_type, ident3->ele->name);
    arg->container_id = ident3->con->ctype->cctype->container_id;
  }

#ifndef NDEBUG
  if (len > ARG_STR_LEN-1)
    assertion_failed("container expression too long for CONT_ARG.expr");
#endif /* NDEBUG */

  strcpy(arg->expr, s);
  sprintf(arg->orig_type, "struct %s", ctype->cctype->orig_type->name);
  arg->funbody = funbody;
  arg->op_list = ctype->cctype->op_list;
}

static SCH_ARG *
new_sch_arg (CTYPE *ctype)
{
  SCH_ARG *arg = xmalloc_object(SCH_ARG);

  assert(ctype->cctype->schema != NULL);
  strcpy(arg->expr, ctype->cctype->schema);
  arg->op_list = ctype->cctype->op_list;
  return(arg);
}

static REC_ARG *
new_rec_arg (NODE *op, int j, NODE *ptree, CTYPE *ctype)
{
  REC_ARG *arg = xmalloc_object(REC_ARG);
  char    s[SPRINT_BUF_SIZE];
  size_t  len = 0;
  
  /* Fill-in REC_ARG structure. */
  s[0] = '\0';
  print_ptree1(s, &len, ptree);
#ifndef NDEBUG
  if (len > ARG_STR_LEN-1)
    assertion_failed("record expression too long to fit into REC_ARG.expr");
#endif /* NDEBUG */
  strcpy(arg->expr, s);

  return(arg);
}

static VPTR_ARG *
new_vptr_arg (NODE *op, int j, NODE *ptree, CTYPE *ctype, int funbody)
{  
  VPTR_ARG *arg = xmalloc_object(VPTR_ARG);
  char    s[SPRINT_BUF_SIZE];
  size_t len = 0;

  s[0] = '\0';
  print_ptree1(s, &len, ptree);
  strcpy(arg->expr, s);
  arg->type = VPTR_STR;
  return(arg);
}

/*****************************************************************************/
/*                  Set optimization parameters                              */
/*****************************************************************************/

void
set_optimization_parameters (CTYPE *ctype, TE *te, IDENT *orig_type)
{
  NODE *op = terminal_string1("xform");
  NODE *ptree = terminal_string1(""); /* Formerly "*** NO EXPRESSION ***" */
  CURS_ARG *arg = (CURS_ARG *) ctype->cctype->arg;

#ifndef NDEBUG
  assert(orig_type != NULL);
#endif /* NDEBUG */

  ctype->cctype->cost = MAX_QOPT_COST;
  ctype->cctype->layer = -1;

  /* Don't set ctype->cctype->cont,
     since ctype->cctype->cont is set in cursor_declaration. (JAT) */

  ctype->cctype->orig_type = orig_type;
  ctype->cctype->te = te;

  new_curs_arg(arg, op, 0, ptree, ctype, FUNCALL_EXPAND_FUNBODY);

  if (ctype->cctype->cursor_id != GENERIC_CURS_ID) {
    /* Not generic cursor. */
    /* Perform "query optimization" and initialize. */

    call_level(te, OPTIMIZE_OP, 1, arg);

    /* Now propagate changes to predicate, cost, and layer. */

    if (arg->layer == -1)
      error("cannot process query %s", ctype->cctype->predicate);
    else {
      ctype->cctype->predicate = copy_string(arg->predicate);
      ctype->cctype->cost = arg->cost;
      ctype->cctype->layer = arg->layer;
      ctype->cctype->retrieval_direction = arg->retrieval_direction;
    }
  }
}

/*****************************************************************************/
/*                  Cursor declaration.                                      */
/*****************************************************************************/

/* Create an additional cursor over the container specified by the
given ident3 with the given predicate.  Return a new ident3 (dest)
identical to the given ident3 (src), but with the new cursor as its
cur field.

In DSB's words, what this procedure does is define a cursor type, given
the IDENT3 of the given container.  That is, subtype the basic cursor
type and add a predicate to the cursor. */

/* Predicate has no quotes.  Predicate is string copied. */

IDENT3 *
copy_cursor_ident3 (IDENT3 *src, char *predicate)
{
  IDENT3 *dest = (IDENT3 *) xmalloc(sizeof(IDENT3));

  dest->ele = src->ele;
  dest->con = src->con;
  /* Copy ident since it will have new values for its
     predicate, cost, layer, and state fields. */
  dest->cur = copy_ident(src->cur);
  if (predicate == NULL)
    predicate = "1";
  strcpy(dest->cur->ctype->cctype->predicate, predicate);
  set_optimization_parameters(dest->cur->ctype,
    dest->con->ctype->cctype->te, dest->con->ctype->cctype->orig_type);
  return(dest);
}

/* Original cursor declaration. */
/* Predicate has quotes that must be stripped.  Predicate is string copied. */

void
pre_opt_cursor_declaration (NODE *unary_expression)
{
  IDENT  *ident = unary_expression->ident;
  char   s[SPRINT_BUF_SIZE];
  size_t len = 0;

  s[0] = '\0';

  print_ptree1(s, &len, unary_expression);
  ident_has_expected_ctype(ident, container_read_only_ctype, "container");

#if 0
  decl->btype = CURSOR_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(CURSOR_CTYPE);
#endif
  decl->btype->ident = copy_ident(ident->ctype->cctype->ident3->cur);
  decl->btype->cctype = xmalloc_object(CCTYPE);
  memset((void *) decl->btype->cctype, 0, sizeof(CCTYPE));
  decl->btype->cctype->arg = xmalloc_object(CURS_ARG);
#if 0
  decl->btype->cctype->indirect_only
    = (ident->ctype->cctype != NULL && ident->ctype->cctype->indirect_only);
#else
  decl->btype->cctype->indirect_only = FALSE;
#endif
  decl->btype->cctype->proceduralize_ref
    = (ident->ctype->cctype != NULL
       && ident->ctype->cctype->proceduralize_ref);
  decl->btype->cctype->ident3 = ident->ctype->cctype->ident3;
  decl->btype->cctype->te = ident->ctype->cctype->te;
  decl->btype->cctype->schema = ident->ctype->cctype->schema;
#ifndef NDEBUG
  /* Make sure cctype->cont is NULL. */
  assert(decl->btype->cctype->cont == NULL);
#endif /* NDEBUG */
  /* The ONLY place where cctype->cont is assigned a non-NULL value. */
  decl->btype->cctype->cont = copy_string(s);
  decl->btype->cctype->cont_type = ident->ctype->cctype->cont_type;
  decl->btype->cctype->orig_type = ident->ctype->cctype->orig_type;

  decl->btype->cctype->cursor_id = curs_id_counter++;
  decl->btype->cctype->container_id
    = ident->ctype->cctype->ident3->con->ctype->cctype->container_id;
#if 0
  decl->btype->cctype->op_list
    = new_op_list(decl->btype, decl->btype->cctype->orig_type, CUR);
#endif
}

void
post_opt_cursor_declaration (NODE *unary_expression)
{
  CTYPE  *ctype = unary_expression->ident->ctype;
  TE *te = ctype->cctype->te;

#if 1
  decl->btype->cctype->op_list
    = new_op_list(decl->btype, decl->btype->cctype->orig_type, CUR);
#endif
  set_optimization_parameters(decl->btype, te, ctype->cctype->orig_type);
  decl->verbatim_ptree = verbatim_nonterm(decl->btype, CUR);
  if (te_requires_op_vec(decl->btype->cctype->te))
    decl->op_vec_ptree = op_vec_nonterm(decl->btype, CUR);
}

/*****************************************************************************/
/*                  Generic cursors.                                         */
/*****************************************************************************/

inline static TE *
generic_te (CTYPE *ctype)
{
  char   te_name[MAX_IDENT_LEN];
  IDENT  *orig_type = ctype->cctype->orig_type;
  char   *orig_type_name = orig_type->name;
  char   c = orig_type_name[strlen(orig_type_name)-1];
  TLIST  *tlist;
  TE     *te;

#ifndef NDEBUG
  assert(orig_type != NULL);
#endif /* NDEBUG */

  sprintf(te_name, "P2_%s%s%s%s", GENERIC_TE_NAME,
    (orig_type_name[0] == '_') ? "" : "_",
    orig_type_name,
    (c >= '0' && c <= '9') ? "x" : "");

  tlist = is_typex(te_name);

  if (tlist == NULL) {
    /* This is a mini-type expression which is intended to be legal,
       but is not intended to be used for anything,
       except as a place holder. (JAT) */
    const char *tlist_name[6] =
      {
        te_name,
        "top2ds", 
        "generic",
        "dlist",
        "malloc",
        "transient"
      };
    tlist = new_tlist(tlist_name, sizeof(tlist_name)/sizeof(char *));
    add_typex_to_symtab(tlist);
  }

  te = tlist_to_te(tlist);
  assert_te_valid(te);

  set_optimization_parameters(ctype, te, orig_type);

  return(te);
}

void
generic_cursor_declaration (NODE *type_specifier)
{
  IDENT *ident;
  CTYPE *ctype = copy_ctype1(struct_read_only_ctype, FALSE);
  IDENT *orig_type = decl->btype->ident;

#ifndef NDEBUG
  assert(orig_type != NULL);
#endif /* NDEBUG */

  /* Create generic cursor struct. */

  ident = new_ident1(GCUR, new_unnamed_sue_name(), ctype, NULL, FALSE);
  /* Can't assign ctype->cctype->ident3->ele,
     since it's the *transformed* element. */
  ctype->ident = ident;
  init_cursor_def(ident, type_specifier->ident, NULL);
  add_ident_to_symtab1(symtab[SUE], ident);

  /* Set decl->btype. */

#if 0
  decl->btype = GENERIC_CURSOR_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(GENERIC_CURSOR_CTYPE);
#endif
  decl->btype->ident = ident;
  decl->btype->cctype = xmalloc_object(CCTYPE);
  memset((void *) decl->btype->cctype, 0, sizeof(CCTYPE));
  decl->btype->cctype->arg = xmalloc_object(CURS_ARG);
  decl->btype->cctype->indirect_only = TRUE;
  decl->btype->cctype->proceduralize_ref
    = (ident->ctype->cctype != NULL && ident->ctype->cctype->proceduralize_ref);
  decl->btype->cctype->orig_type = orig_type;

  decl->btype->cctype->cursor_id    = GENERIC_CURS_ID;
  decl->btype->cctype->container_id = GENERIC_CONT_ID;

  /* Call these procedures last, because they depend on the
     proper initialization of several fields of ctype->cctype. (JAT) */

  decl->btype->cctype->te = generic_te(decl->btype);
  decl->btype->cctype->op_list = new_op_list(decl->btype, orig_type, CUR);
}

/*****************************************************************************/
/*                  TE providing the given operation                         */
/*****************************************************************************/

static TE *
layer_providing_op (NODE *ptree, int i, TE *te)
{
  RCLASS realm = te->layerdef->layer_realm;
  while ((realm != BOTTOM) && !(op_tab[i].op[realm])) { 
    te = te->down[0];
    if (!te) {
      parse_error("special op %s undefined", ptree->ident->name);
    }        
    realm = te->layerdef->layer_realm;
  }
  return(te);
}

/*****************************************************************************/
/*                  Call special operation                                   */
/*****************************************************************************/

/* For the given special operation op, make sure that op is defined in
   the ops_vector.  If so, call the operation defined, and return the
   parse tree it returns. */

inline static NODE *
call_special_op (NODE *ptree, void *arg[MAX_OP_PARAM], int i, TE *te)
{
  RCLASS    realm = te->layerdef->layer_realm;
  NODE      *result;
  int       num_arg;

  if ((realm != BOTTOM) && (!op_tab[i].op[realm]))
    parse_error("special op %s undefined in %s realm", ptree->ident->name,
      rclass_enum_const_string(realm));

#ifndef NDEBUG
  assert_te_valid(te);
  if (MAX_OP_PARAM > 6)
    assertion_failed("MAX_OP_PARAM > 6, need to add some additional cases");
#endif /* NDEBUG */

  num_arg = op_tab[i].num_arg;
  switch (num_arg)
  {
  case 0:
    result = call_level(te, op_tab[i].op_num, num_arg);
    break;
  case 1:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0]);
    break;
  case 2:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0], arg[1]);
    break;
  case 3:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0], arg[1], arg[2]);
    break;
  case 4:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0], arg[1], arg[2], arg[3]);
    break;
  case 5:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0], arg[1], arg[2], arg[3], arg[4]);
    break;
  case 6:
    result = call_level(te, op_tab[i].op_num, num_arg,
                        arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    break;
  default:
#ifndef NDEBUG
    assertion_failed("num_arg = %d > MAX_OP_PARAM = %d", num_arg,
                     MAX_OP_PARAM);
#endif /* NDEBUG */
    break;
  }
  return(result);
}

/*****************************************************************************/
/*                  Operation table lookup                                   */
/*****************************************************************************/

/* Return the index of the op_tab entry with the given name. */
/* That is, return i such that op_tab[i].name == name (JAT) */

inline static int
op_tab_lookup (char *name)
{
  int i = 0;
  while (op_tab[i].name != NULL && strcmp(op_tab[i].name, name) != 0)
    i++;

#ifndef NDEBUG
  if (op_tab[i].name == NULL)
    assertion_failed("couldn't find op_tab entry for %s", name);
#endif /* NDEBUG */

  return(i);
}

/*****************************************************************************/
/*                  aclass tests.                                            */
/*****************************************************************************/

/* Return TRUE iff a param of the given aclass has a ctype. */

inline static BOOLEAN
aclass_has_a_ctype (ACLASS aclass)
{
  return(aclass != PAR && aclass != FIE && aclass != LST);
}

/* Return TRUE iff the given aclass is also a pclass.
   That is, aclass is in the intersection of ACLASS and PCLASS.
   That is, aclass is in the subset of COMMON that is in ACLASS and PCLASS. */

inline static BOOLEAN
aclass_is_a_pclass (ACLASS aclass)
{
#ifndef NDEBUG
  assert(MAX_COMMON < MIN_ACLASS);
  assert(MAX_COMMON < MIN_PCLASS);
#endif /* NDEBUG */
  return(aclass <= MAX_COMMON);
}

/*****************************************************************************/
/*                  delete comments inplace.                                 */
/*****************************************************************************/

#if 0

Transform:
"upd(c, /* ref(b) */\n((b).obj)->foo /* end of special op ref(b) */\n+ 1)"

Into:
"upd(c, ((b).obj)->foo + 1)"

#endif

#if PRINT_CALL_AS_COMMENT

inline static void
delete_comments_inplace (char *s)
{
  char *start = s;
  char *end;
  do {
    /* Delete the entire comment. */
    start = strstr(start, "/*");
    if (start != NULL) {
      end = strstr(start, "*/");
      if (end != NULL)
        delete_string(start, end-start+2);
    }
  } while (start != NULL);
  remove_char(s, '\n');
}

#endif /* PRINT_CALL_AS_COMMENT */

/*****************************************************************************/
/*                  Special operation nonterminal node with comments         */
/*****************************************************************************/

#if PRINT_ARGS_AS_COMMENT
inline static void
print_curs_arg_as_comment (char *s, size_t *len, CURS_ARG *arg, int j)
{
  print2(s, len, "/*\n", 3);
  printf1(s, len, "arg[%d]->expr = %s\n",            j, arg->expr);
  printf1(s, len, "arg[%d]->type = %s\n",            j, arg->type);
  printf1(s, len, "arg[%d]->cont = %s\n",            j, arg->cont);
  printf1(s, len, "arg[%d]->cont_type = %s\n",       j, arg->cont_type);
  printf1(s, len, "arg[%d]->orig_type = %s\n",       j, arg->orig_type);
  printf1(s, len, "arg[%d]->obj_type = %s\n",        j, arg->obj_type);
  printf1(s, len, "arg[%d]->predicate = %s\n",       j, arg->predicate);
  printf1(s, len, "arg[%d]->cost = %d\n",            j, arg->cost);
  printf1(s, len, "arg[%d]->layer = %d\n",           j, arg->layer);
  printf1(s, len, "arg[%d]->cursor_id = %d\n",       j, arg->cursor_id);
  printf1(s, len, "arg[%d]->container_id = %d\n",    j, arg->container_id);
  print2(s, len, "*/\n", 3);
}

inline static void
print_cont_arg_as_comment (char *s, size_t *len, CONT_ARG *arg, int j)
{
  print2(s, len, "/*\n", 3);
  printf1(s, len, "arg[%d]->expr = %s\n",            j, arg->expr);
  printf1(s, len, "arg[%d]->type = %s\n",            j, arg->type);
  printf1(s, len, "arg[%d]->orig_type = %s\n",       j, arg->orig_type);
  printf1(s, len, "arg[%d]->obj_type = %s\n",        j, arg->obj_type);
  printf1(s, len, "arg[%d]->container_id = %d\n",    j, arg->container_id);
  print2(s, len, "*/\n", 3);
}

inline static void
print_rec_arg_as_comment (char *s, size_t *len, REC_ARG *arg, int j)
{
  print2(s, len, "/*\n", 3);
  printf1(s, len, "arg[%d]->expr = %s\n",            j, arg->expr);
  print2(s, len, "*/\n", 3);
}

#endif /* PRINT_ARGS_AS_COMMENT */

/* Combine with the transformed parse tree
   (1) comments describing the call and/or
   (2) arguments to the special operation,
   and return the result. (JAT) */

NODE *
special_op_nonterm_comments (NODE *op, NODE *param[], int m, int i,
                             void *arg[], NODE *xformed_ptree)
{
#if PRINT_CALL_AS_COMMENT
  char   call_string[SPRINT_BUF_SIZE];
  size_t call_string_len = 0;
#endif

#if PRINT_ARGS_AS_COMMENT
  char   args_string[SPRINT_BUF_SIZE];
  size_t args_string_len = 0;
#endif
  
#if PRINT_CALL_AS_COMMENT
  /* Create call string. */

  call_string[0] = '\0';
  print_ptree1(call_string, &call_string_len, op);
  print2(call_string, &call_string_len, "(", 1);

  if (i == -1) {
    /* Special case: just print first actual argument. */
    print_ptree1(call_string, &call_string_len, param[0]);
  }
  else {
    /* Special case: print all printable actual arguments. */
    int j = 0; /* Index over arguments to op. */
    while (j < m) {
      ACLASS aclass;
      /* Print actual parameter. */
      aclass = op_tab[i].param[j];
      if (aclass_has_a_ctype(aclass))
        print_ptree1(call_string, &call_string_len, param[j]);
      /* Print a comma. */
      j++;
      if (j < m) {
        aclass = op_tab[i].param[j];
        if (aclass_has_a_ctype(aclass))
          print2(call_string, &call_string_len, ", ", 2);
      }
    }
  }
  print2(call_string, &call_string_len, ")", 1);
#endif /* PRINT_CALL_AS_COMMENT */

#if PRINT_ARGS_AS_COMMENT
  /* Create args string. */
    
  args_string[0] = '\0';
  if (i != -1) {
    int j; /* Index over arguments to op. */
    for (j = 0; j < m; j++) 
      switch(op_tab[i].param[j]) {
      case CUR:
        print_curs_arg_as_comment(args_string, &args_string_len,
                                  (CURS_ARG *) arg[j], j);
        break;

      case CON:
        print_cont_arg_as_comment(args_string, &args_string_len,
                                  (CONT_ARG *) arg[j], j);
        break;

      case SCH:
#if 0
      /* The proceduralization of a schema special operation takes no
         schema argument, since there is only one schema, and thus the
         schema is implicit. */
        break;
#endif

      case STR:
        print_rec_arg_as_comment(args_string, &args_string_len,
                                 (REC_ARG *) arg[j], j);
        break;

      default:
      }
  }
#endif /* PRINT_ARGS_AS_COMMENT */

  /* Return result. */

#if PRINT_CALL_AS_COMMENT
  delete_comments_inplace(call_string);
  return(nonterm(UND, NULL, (PRINT_ARGS_AS_COMMENT) ? 8 : 7,
                 terminal_string1("/*"),
                 terminal_string(call_string),
                 terminal_string1("*/\n"),
#if PRINT_ARGS_AS_COMMENT
                 terminal_string(args_string),
#endif
                 xformed_ptree,
                 terminal_string1("/* end of special operation"),
                 terminal_string(call_string),
                 terminal_string1("*/\n")));
#elif PRINT_ARGS_AS_COMMENT
  return(nonterm(UND, NULL, 2, terminal_string(args_string), xformed_ptree));
#else
  return(xformed_ptree);
#endif
}

/*****************************************************************************/
/*                  Special operation nonterminal node                       */
/*****************************************************************************/

BOOLEAN
actual_matches_formal_param (CTYPE *ctype, ACLASS aclass)
{
  int k = 0;
  return(!aclass_is_a_pclass(aclass)
         || pclassmatch2(ctype, &k, (PCLASS) aclass, FALSE)
         || (ctypematch1(ctype, generic_container_read_only_ctype, TRUE)
             && aclass == CON)
         || (ctypematch1(ctype, generic_cursor_read_only_ctype, TRUE)
             && aclass == CUR));
}

/* This routine is called to print the actual
   params of an inlined special operation. */

inline static void
print_param (char *s, size_t *len, NODE *param[], int i, CTYPE *ctype)
{
  int j;
  print2(s, len, "(", 1);
  for (j = 0; j < op_tab[i].num_arg; j++)
  {
    /* There is only one schema, so we needn't pass it as an argument. */
    if (op_tab[i].param[j] == SCH)
    {
      /* The schema must be the only argument to the special operation. */
      assert(op_tab[i].num_arg == 1);
    }
    /* Can't pass arguments of type field (at all).  Currently,
       proceduralized special operations that take field arguments
       include the field as part of the procedure name (e.g.,
       P2_upd_foo_id1000() to update field foo).  Is this an example
       of currying: the proceduralized special operation is a curried
       function? (JAT) */
    else
    {
      if (op_tab[i].param[j] != FIE)
      {
        /* Pass integers (IN), expressions (EXP), and generics by value,
           everything else by reference. */
        if (op_tab[i].param[j] != IN
            && op_tab[i].param[j] != EXP
            && !generic_pclass(base_ptype(param[j]->ident->ctype)->pclass))
        {
          if (op_tab[i].param[j] == VPR)
            print2(s, len, "(vptr *) ", 9);
          print2(s, len, "&", 1);
        }
#if 0
        if (param[j]->ident->ctype->cctype != NULL
            && param[j]->ident->ctype->cctype->indirect_only)
        {
          /* Special case for indirect_only. */
          if (param[j]->ident->name[0] != '*')
            assertion_failed("indirect only by name[0] != '*'");
          else
            print1(s, len, &param[j]->ident->name[1]);
        }
        else
#endif
        if (j == 0
            && op_tab[i].indirect_container && ctype->cctype->indirect_only)
        {
          /* Special case: must add an extra level of indirection to
             container argument.  Do this iff special operation has
             indirect_container equal to TRUE (e.g., open_cont), AND
             type expression has indirect_only equal to TRUE (e.g.,
             those that contain mmap_persistent).  Do this by getting
             rid of an asterisk (dereference operator).
             See paces/generic04.p2h */
          char s1[SPRINT_BUF_SIZE];
          size_t len1 = 0;
          /* Make sure argument is a container. */
          assert(op_tab[i].param[j] == CON);
          /* s1 = (*foo) */
          print_ptree1(s1, &len1, param[j]);
          if (len1 > MAX_IDENT_LEN)
            error("container name \"%s\" too long", s1);
          /* s1 = (foo) */
          if (replace_string_inplace1(s1, "*", "", 1) != 1)
            error("could not delete \"*\" from container \"%s\"", s1);
          print2(s, len, s1, len1-1);
        }
        else
          /* Normal case. */
          print_ptree1(s, len, param[j]);
      }
      if (j != op_tab[i].num_arg-1 && op_tab[i].param[j+1] != FIE)
        print2(s, len, ",", 1);
    }
  }
  print2(s, len, ")", 1);
  if (!op_tab[i].expr)
    print2(s, len, ";", 1);
}

inline static BOOLEAN
op_fully_parameterized_by_aclass (int i, ACLASS aclass)
{
  assert(aclass == SCH || aclass == CON || aclass == CUR);

  /* If operation has a (formal) parameter of type SCH, CON, or CUR,
     then the operation is only fully parameterized by an (actual)
     argument of type SCH, CON, or CUR, respectively. */
  if (op_has_aclass_param(i, SCH))
    return(aclass == SCH);
  else if (op_has_aclass_param(i, CON))
    return(aclass == CON);
  else if (op_has_aclass_param(i, CUR)) 
    return(aclass == CUR);

  /* Otherwise, the operation is fully parameterized by ANY argument. */
  else
    return(TRUE);

#if 0
  BOOLEAN r = FALSE;
  switch (aclass)
  {
  case CUR:
    r = op_has_aclass_param(i, CUR);
    break;
  case CON:
    r = !(op_has_aclass_param(i, CUR));
    break;
  case SCH:
    r = op_has_aclass_param(i, SCH)
    break;
  case ERR:
  default:
  }
  return(r);
#endif
}

/* Reuse arg x if possible.  Otherwise, allocate a new x.

   That is, return x if x != arg[0] ... arg[j-1].
   Otherwise, return a new object of given size.

   It is not possible to reuse x if, for example, we are calling
   swap(c0, c1) where c0 and c1 share the same cctype->arg = x,
   because c0 and c1 have, for example, been declared in the same
   declaration. */

inline static void *
reuse_arg (int j, void *arg[], void *x, size_t size)
{
  int k;
  for (k = 0; k < j; k++) {
    if (arg[k] == x)
      return(xmalloc(size));
  }
  return(x);
}

/* Handle the actual arguments to the special operation. */
/* Given op, param, m, and i.
   Return arg, op_has_generic_param, ctype, and field. */

/* Note similarity to init_args() (JAT) */

inline static void
special_op_nonterm_arg (NODE *op, NODE *param[], int m, int i,
                        void *arg[], NODE **op_has_generic_param,
                        CTYPE **ctype, char **field)
{
  int funbody = FUNCALL_EXPAND_FUNBODY;
  int j; /* Index over arguments to op. */

#ifndef NDEBUG
  if (m == 0)
    assertion_failed("Special operation %s has no arguments",
      op->ident->name);
#endif /* NDEBUG */
    
  /* Fill-in the argument structures. */
    
  for (j = 0; j < m; j++)
  {
    ACLASS aclass = op_tab[i].param[j];
    CTYPE *param_ctype = (aclass_has_a_ctype(aclass))
      ? param[j]->ident->ctype : NULL;

    if (!(*op_has_generic_param))
    {
      if (param_ctype != NULL
          && generic_pclass(base_ptype(param_ctype)->pclass))
        (*op_has_generic_param) = param[j];
      if (param_ctype != NULL)
        if ((*ctype) == NULL)
          (*ctype) = param_ctype;
    }

    switch(op_tab[i].param[j])
    {
    case CUR:
      arg[j] = reuse_arg(j, arg, param_ctype->cctype->arg, sizeof(CURS_ARG));
      new_curs_arg((CURS_ARG *) arg[j], op, j, param[j], param_ctype, funbody);
      break;

    case CON:
      arg[j] = reuse_arg(j, arg, param_ctype->cctype->arg, sizeof(CONT_ARG));
      new_cont_arg((CONT_ARG *) arg[j], op, j, param[j], param_ctype, funbody);
      break;

    case SCH:
#if 0
      /* The proceduralization of a schema special operation takes no
         schema argument, since there is only one schema, and thus the
         schema is implicit. */
      break;
#endif

    case STR:
      arg[j] = new_rec_arg(op, j, param[j], param_ctype);
      break;

    case PAR:
    case IN:
    case EXP:
      arg[j] = (void *) param[j];
      break;

    case FIE:
      {
        char s[SPRINT_BUF_SIZE];
        sprint_ptree(s, param[j]);
        arg[j] = (void *) copy_string(s);
        (*field) = (char *) arg[j];
      }
      break;

    case VPR: 
      arg[j] = new_vptr_arg(op, j, param[j], param_ctype, 0);
      break;

    case LST:
      arg[j] = (LST_ARG *) param[j];
      break;

    default:
#ifndef NDEBUG
      assertion_failed("illegal special op prototype pclass %s",
        pclass_enum_const_string(op_tab[i].param[j]));
#endif /* NDEBUG */
      break;
    }
  }
}

/* If op is a special operation, return the appropriate ptree,
   otherwise return NULL. */
/* i is operation number, or -1 to force operation lookup. */
/* Does not check for correctness of argument type and number (prototype) */

NODE *
special_op_nonterm1 (NODE *op, NODE *param[], int m, int i, TE *te)
{
  void  *arg[MAX_OP_PARAM]; /* curs, cont, rec, or vptr args */
  NODE  *xformed_ptree;
  NODE  *op_has_generic_param = NULL;
  NODE  *n;
  CTYPE *ctype = NULL;
  char  *field = NULL;
  int   t; /* op_list index of op */

  /* Lookup operation */

  if (i == -1)
    i = op_tab_lookup(op->ident->name);

  /* Handle arguments */

#ifndef NDEBUG
  {
    /* Initialize arg[] to known (illegal) values */
    int j;
    for (j = 0; j < MAX_OP_PARAM; j++)
      arg[j] = (void *) -1;
  }
#endif /* NDEBUG */

  special_op_nonterm_arg(op, param, m, i,
                         arg, &op_has_generic_param, &ctype, &field);
  if (te == NULL)
    te = ctype->cctype->te;

#if FUNCALL
  t = op_list_match(ctype->cctype->op_list, op_tab[i].name, field);
  if (proceduralize_op(i, ctype))
  {
    /* Proceduralize operation. */
    char   s[SPRINT_BUF_SIZE];
    size_t len = 0;

#ifndef NDEBUG
    if (t == -1)
    {
      strcpy(s, "operation ");
      esprint_ptree(s, op);
      if (field != NULL)
      {
        strcat(s, " field ");
        strcat(s, field);
      }
      /* Be careful: we create upd procedures only for those fields
         with supported data types (i.e., int or str).
         See pb/pb-type.c:new_op_list1() (JAT) */
      assertion_failed("proceduralize[%s] is true, but couldn't find \"%s\""
                       " in op_tab", op_tab[i].name, s);
    }
#endif /* NDEBUG */

    s[0] = '\0';
    print1(s, &len,
      "/* proceduralized by pb/pb-actions:special_op_nonterm1() */ ");
    if (op_has_generic_param != NULL) {
      /* Proceduralize operation as a runtime indirection through op_vec, ie
         ((op_has_generic_param)->op_vec[i])(param[0], ... , param[m-1]) */
      print2(s, &len, "((*", 3);
      print_ptree1(s, &len, op_has_generic_param);
      printf1(s, &len, ").op_vec[%d])", t);
    }
    else {
      /* Proceduralize operation as a call to a statically known function, ie
         P2_op#(param[0], ... , param[m-1]) */
      print1(s, &len, ctype->cctype->op_list->tuple[t].procedure);
    }
    print_param(s, &len, param, i, ctype);
    n = terminal_string(s);
  }
  else
#endif /* FUNCALL */
  {
    /* Inline operation. */
    assert_te_valid(te);
    n = call_special_op(op, arg, i, te);
  }
  
  /* Add comments. */

#if PRINT_CALL_AS_COMMENT || PRINT_ARGS_AS_COMMENT
  xformed_ptree = special_op_nonterm_comments(op, param, m, i, arg, n);
#else
  xformed_ptree = n;
#endif

  /* Add ctype. */

  if (op_tab[i].expr) {
    IDENT *ident = new_ident1(TYP, xformed_ptree->ident->name,
                              int_read_only_ctype, NULL, FALSE);
    xformed_ptree->ident = ident;
#ifndef NDEBUG
    assert_ctype_valid(xformed_ptree->ident->ctype);
#endif /* NDEBUG */
  }

  return(xformed_ptree);
}

/* If op is not a special operation, return NULL.
   Otherwise, return the appropriate ptree. */
/* Checks for correctness of argument type and number (prototype) */

NODE *
special_op_nonterm (NODE *op, NODE *params)
{
  if (op->ident->name == NULL)
    return(NULL);
  else
  {
    ENTRY *e = symtab_lookup(symtab[OTH], op->ident->name);

    /* Special case for compcurs special operations. */

    if (e == NULL || e->ident->sclass != SPE)
      return(compcurs_special_op_nonterm(op, params));

    /* Normal case. */

    else {
      int i = op_tab_lookup(op->ident->name); /* op_tab index of op */
      int j; /* Index over arguments to op. */
      int m = num_params(params);
      NODE *param[MAX_OP_PARAM];

      /* Make sure we won't be writing past the end of the param array. (JAT) */

      if (m > MAX_OP_PARAM)
        parse_error("%d arguments to special op %s exceeds maximum %d",
                    m, op->ident->name, MAX_OP_PARAM);

      /* Fill in param. */

      for (j = 0; j < m; j++)
        param[j] = nth_param(j+1, m, params);

      /* Make sure that the *number* of actual parameters matches prototype. */

      if (m != op_tab[i].num_arg)
        parse_error("%d arguments to special op %s which expects %d",
                    m, op->ident->name, op_tab[i].num_arg);

      /* Make sure that the *types* of actual parameters match prototype. */

      for (j = 0; j < m; j++)
      {
        ACLASS aclass = op_tab[i].param[j];
        if (aclass_has_a_ctype(aclass))
        {
          IDENT *param_ident = param[j]->ident;
          CTYPE *param_ctype = param_ident->ctype;
          if (!actual_matches_formal_param(param_ctype, aclass))
          {
            char   s[SPRINT_BUF_SIZE];
            size_t len = 0;
            s[0] = '\0';
            sprint_decl1(s, &len, param_ident, FALSE);
            parse_error("%s arg %d has %s where %s expected",
                        op->ident->name, j+1, s, aclass_string(aclass));
          }
        }
      }

      /* Return transformed parse tree. */

      return(special_op_nonterm1(op, param, m, i, NULL));
    }
  }
}

/*****************************************************************************/
/*                  Operation vector nonterm                                 */
/*****************************************************************************/

/* Copy the container and cursor specific ctype fields from src to dest. */

inline static void
copy_container_and_cursor_ctype_fields (CTYPE *dest, CTYPE *src)
{
#if 0
  /* Deep copy. */
  dest->cctype = xmalloc_object(CCTYPE);
  dest->cctype->ident3    = src->cctype->ident3;
  dest->cctype->te        = src->cctype->te;
  dest->cctype->cont      = src->cctype->cont;
  dest->cctype->cont_type = src->cctype->cont_type;
  dest->cctype->orig_type = src->cctype->orig_type;
#else
  /* Shallow copy. */
  dest->cctype = src->cctype;
#endif
  dest->ident = src->ident;
}

/* Create the parse tree nodes for the formal parameters. */

inline static void
init_formal_nodes (FORMAL_NODES *formal_nodes, CTYPE *ctype)
{
  int   j; /* Parameter number: 0, 1, ..., MAX_OP_PARAM */
  char  s[SPRINT_BUF_SIZE];
  CTYPE *cont_ctype = copy_ctype1(pointer_container_read_only_ctype, FALSE);
  CTYPE *curs_ctype = copy_ctype1(pointer_cursor_read_only_ctype, FALSE);
  CTYPE *rec_ctype  = copy_ctype1(pointer_struct_read_only_ctype, FALSE);
  CTYPE *vptr_ctype = copy_ctype1(pointer_vptr_read_only_ctype, FALSE);
  CTYPE *int_ctype  = copy_ctype1(int_read_only_ctype, FALSE);
  /* Is int okay here?  Will this cause a problem for char * (ie, char string),
     and any other types that we might add in the future (eg, float, double)?
     (JAT) */
  CTYPE *expr_ctype = copy_ctype1(int_read_only_ctype, FALSE);

  copy_container_and_cursor_ctype_fields(cont_ctype, ctype);
  copy_container_and_cursor_ctype_fields(curs_ctype, ctype);
  rec_ctype->ident = ctype->cctype->orig_type;
  copy_container_and_cursor_ctype_fields(rec_ctype, ctype);
  for (j = 0; j < MAX_OP_PARAM; j++)
  {
    sprintf(s, "(*P2_cont%d)", j);
    formal_nodes->cont_node[j] = terminal(CON, s, cont_ctype);
#if 0
    /* Debugging: works for everything except x/mmap_{persistent,shared}.xp */
    sprintf(s, "(*P2_cont%d)", j);
    formal_nodes->icont_node[j] = terminal(CON, s, cont_ctype);
#else
    /* Add an extra level of indirection.
       See pb/pb-actions.c:print_param() and paces/generic04.p2h */
    sprintf(s, "(**P2_cont%d)", j);
    formal_nodes->icont_node[j] = terminal(CON, s, cont_ctype);
#endif
    sprintf(s, "(*P2_curs%d)", j);
    formal_nodes->curs_node[j] = terminal(CUR, s, curs_ctype);
    sprintf(s, "(*P2_rec%d)", j);
    formal_nodes->rec_node[j] = terminal(STR, s, rec_ctype);
    sprintf(s, "(*vp%d)", j);
    formal_nodes->vptr_node[j] = terminal(VPR, s, vptr_ctype);
    sprintf(s, "P2_int%d", j);
    formal_nodes->int_node[j] = terminal(EXP, s, int_ctype);
    sprintf(s, "P2_expr%d", j);
    formal_nodes->expr_node[j] = terminal(EXP, s, expr_ctype);
  }
} 

/* Note similarity to special_op_nonterm_arg() (JAT) */

inline static void
init_args (void **arg, FORMAL_NODES *formal_nodes,
           int i, TE *layer, NODE *ptree, CTYPE *ctype, IDENT *ident)
{
#if 1
  int funbody = op_tab[i].op_num;
#else
  int funbody = MACRO_EXPAND_FUNBODY;
#endif

  int j; /* Index over arguments to op. */
  
  for (j = 0; j < op_tab[i].num_arg; j++)
  {
    switch (op_tab[i].param[j])
    {
     case CUR:
      arg[j] = reuse_arg(j, arg, ctype->cctype->arg, sizeof(CURS_ARG));
      new_curs_arg((CURS_ARG *) arg[j], ptree, j, formal_nodes->curs_node[j],
                   ctype, funbody);
      break;

     case CON:
      if (op_tab[i].indirect_container && ctype->cctype->indirect_only)
      {
        /* Add an extra level of indirection.
           See pb/pb-actions.c:print_param() and paces/generic04.p2h */
        arg[j] = reuse_arg(j, arg, ctype->cctype->arg, sizeof(CONT_ARG));
        new_cont_arg((CONT_ARG *) arg[j], ptree, j, formal_nodes->icont_node[j],
                   ctype, funbody);
      }
      else
      {
        arg[j] = reuse_arg(j, arg, ctype->cctype->arg, sizeof(CONT_ARG));
        new_cont_arg((CONT_ARG *) arg[j], ptree, j, formal_nodes->cont_node[j],
                   ctype, funbody);
      }
      break;

     case SCH:
      arg[j] = new_sch_arg(ctype);
      break;

     case STR:
      arg[j] = new_rec_arg(ptree, j, formal_nodes->rec_node[j], ctype);
      break;

     case FIE:
#if 1
      arg[j] = (void *) ident->name;
#else
      arg[j] = (void *) formal_nodes->expr_node[j];
#endif
      break;

     case IN:
      arg[j] = (void *) formal_nodes->int_node[j];
      break;

     case EXP:
#if 0
      arg[j] = (void *) terminal_ident(ident);
#else
      arg[j] = (void *) formal_nodes->expr_node[j];
#endif
      break;

     case VPR: 
      arg[j] = new_vptr_arg(ptree, j, formal_nodes->vptr_node[j],
                            ctype, funbody);
      break;

     default:
#ifndef NDEBUG
      assertion_failed("can't proceduralize ops w/ params of aclass = %s",
        aclass_string(op_tab[i].param[j]));
#endif /* NDEBUG */
      break;
    }
  }
}

NODE *
verbatim_nonterm (CTYPE *ctype, ACLASS aclass)
{
  FORMAL_NODES formal_nodes;
  TE      *te = ctype->cctype->te;
  char    s[SPRINT_BUF_SIZE];
  size_t  len = 0;
  int     i;

  s[0] = '\0';
  init_formal_nodes(&formal_nodes, ctype);
  assert_te_valid(te);

  for (i = 0; op_tab[i].name != NULL; i++)
  {
    if (op_tab[i].verbatim && op_fully_parameterized_by_aclass(i, aclass))
    {
      void *arg[MAX_OP_PARAM];
      NODE *ptree = terminal_string1(op_tab[i].name);
      TE *layer = layer_providing_op(ptree, i, te);
      NODE *special_op_nonterm;

      init_args(arg, &formal_nodes, i, layer, ptree, ctype, NULL);
      special_op_nonterm = call_special_op(ptree, arg, i, layer);
#ifndef NDEBUG
      /* Check for parse tree equal to "0"--a common parse tree,
         because "0" is the default parse tree for expressions--but
         not a valid verbatim parse tree. */
      if (special_op_nonterm != NULL
          && strcmp(special_op_nonterm->ident->name, "0") == 0)
        warning(4, "verbatim operation %s expanded to \"0\"", op_tab[i].name);
#endif /* NDEBUG */
      print_ptree1(s, &len, special_op_nonterm);
    }
  }

  if (s[0] == '\0')
    return(NULL);
  else
    return(terminal_string(s));
}

/* Return the typename of a special operation.  Currently returns
   "int" or "char *".  Normal is case "int".  Special case "char *"
   applies when the special operation is a ref function, and the field
   is a string type. */

inline static char *
special_op_typename (CTYPE *ctype, int t)
{
  OP_LIST *op_list = ctype->cctype->op_list;
  IDENT *m = op_list->tuple[t].ident;
  if (strncmp(op_list->tuple[t].procedure, "P2_ref_", 7) == 0
      && string_ctype(m->ctype))
    return("char *");
  else
    return("int");
}

/* Print the function declarator of a special operation. */

inline static void
print_special_op_function_declarator (char *s, size_t *len, CTYPE *ctype,
                                      int i, int t, FORMAL_NODES *formal_nodes)
{
  OP_LIST *op_list = ctype->cctype->op_list;
  int j;

  /* If the current scope is not top level,
     then print the static storage class specifier. */

  /* Note that it is necessary to provide the static storage class
     specifier for non top level function prototye declarations,
     because in gcc, non top level function *definitions* are implicitly
     static, whereas non top level function *prototype declarations* are
     not implicitly static (they are implicitly extern). */

  if (scope != 0)
    print2(s, len, "static ", 7);

  /* Print the type. */

  printf1(s, len, "%s ", special_op_typename(ctype, t));

  /* Print the name. */

  print1(s, len, op_list->tuple[t].procedure);

  /* Print the argument list. */

  print2(s, len, " (", 2);
  for (j = 0; j < op_tab[i].num_arg; j++)
  {
    switch (op_tab[i].param[j])
    {
    case CON:
      if (op_tab[i].indirect_container && ctype->cctype->indirect_only)
      {
        /* Add an extra level of indirection.
           See pb/pb-actions.c:print_param() and paces/generic04.p2h */
        printf1(s, len, "struct %s ", ctype->cctype->ident3->con->name);
        print_ptree1(s, len, formal_nodes->icont_node[j]);
      }
      else
      {
        printf1(s, len, "struct %s ", ctype->cctype->ident3->con->name);
        print_ptree1(s, len, formal_nodes->cont_node[j]);
      }
      break;
    case CUR:
      printf1(s, len, "struct %s ", ctype->cctype->ident3->cur->name);
      print_ptree1(s, len, formal_nodes->curs_node[j]);
      break;
    case SCH:
      /* The schema must be the only argument to the special operation. */
      assert(op_tab[i].num_arg == 1);
      /* The proceduralization of a schema special operation takes no
         schema argument, since there is only one schema, and thus the
         schema is implicit. */
      print1(s, len, "void");
      break;
    case STR:
      printf1(s, len, "struct %s ", ctype->cctype->orig_type->name);
      print_ptree1(s, len, formal_nodes->rec_node[j]);
      break;
    case VPR:
      print1(s, len, VPTR_STR);
      print_ptree1(s, len, formal_nodes->vptr_node[j]);
      break;
    case IN:
      print1(s, len, "int ");
      print_ptree1(s, len, formal_nodes->int_node[j]);
      break;
    case EXP:
      /* Why int?  See init_formal_nodes() (JAT) */
      /* BUG: Unfortunately, this can give a compile-time warning when
         the actual argument is an int or a char * (character string).
         We should somehow infer the actual type. (JAT) */
      if (op_list->tuple[t].ident == 0)
        /* NODE *expr argument to pos() */
        printf1(s, len, "void * ");
      else if (ctypematch1(op_list->tuple[t].ident->ctype,
                           string_read_only_ctype, TRUE))
        /* char *expr argument to upd() */
        printf1(s, len, "char * ");
      else
        /* int expr argument to upd() */
        printf1(s, len, "int ");
      print_ptree1(s, len, formal_nodes->expr_node[j]);
      break;
    case FIE:
      /* Can't pass arguments of type field.
         See pb/pb-actions.c:print_param() (JAT) */
    default:
      break;
    }
    if (j != op_tab[i].num_arg-1 && op_tab[i].param[j+1] != FIE)
      print2(s, len, ",", 1);
  }
  print2(s, len, ")", 1);
}

/* Print the function body. */

inline static void
print_special_op_function_body (char *s, size_t *len, CTYPE *ctype,
                                int i, int t, FORMAL_NODES *formal_nodes)
{
  OP_LIST *op_list = ctype->cctype->op_list;
  TE      *te = ctype->cctype->te;
  NODE    *ptree = terminal_string1(op_tab[i].name);
  TE      *layer = layer_providing_op(ptree, i, te);
  void    *arg[MAX_OP_PARAM];

  print1(s, len, "{\n");
  if (op_tab[i].expr)
    printf1(s, len, "return (%s) (", special_op_typename(ctype, t));
  init_args(arg, formal_nodes, i, layer, ptree, ctype, op_list->tuple[t].ident);
  print_ptree1(s, len, call_special_op(ptree, arg, i, layer));
  if (op_tab[i].expr)
    print1(s, len, ");");
  print1(s, len, "}\n");
}

/* Print the function definition (declarator + function body)
   of a special operation. */

static void
print_special_op_function_definition (char *s, size_t *len, CTYPE *ctype,
                                      int i, int t, FORMAL_NODES *formal_nodes)
{
  print_special_op_function_declarator(s, len, ctype, i, t, formal_nodes);

#ifndef NDEBUG
  assert_all_chars_printable(s);
#endif /* NDEBUG */

  /* Print a newline. */
  print2(s, len, "\n", 1);

  /* Print the function body. */
  print_special_op_function_body(s, len, ctype, i, t, formal_nodes);
}

NODE *
op_vec_nonterm (CTYPE *ctype, ACLASS aclass)
{
  FORMAL_NODES formal_nodes;
  int     i, t;
  char    s[SPRINT_BUF_SIZE];
  size_t  len = 0;
  TE      *te = ctype->cctype->te;
  int     id;
  OP_LIST *op_list = ctype->cctype->op_list;
  
  s[0] = '\0';
  init_formal_nodes(&formal_nodes, ctype);
  assert_te_valid(te);
  
  /* Print the special operation prototypes
     (declarator followed by semicolon). */
  /* It is necessary to do this, because the operation vector declaration
     refererences the special operation functions and vice versa.
     Thus, these prototypes serve as a "forward" declaration of the special
     operations. (JAT) */
  /* Previously, instead of using these function prototypes as a forward
     declaration of the special operations,
     I had used an extern declaration of the operation vector to serve as
     a "forward" declaration of the special operations.
     The problem with the old solution was that extern also implies top
     level, and thus the old solution only worked at the top level.
     Thus, with the old solution, local cursors and containers could not
     be proceduralized. (JAT) */
  
  for (i = 0; op_tab[i].name != NULL; i++)
  {
    if (proceduralize_op(i, ctype)
        && op_fully_parameterized_by_aclass(i, aclass))
    {
      for (t = 0; t < op_list->size; t++)
      {
        if (op_list->tuple[t].i == i)
        {
          /* Print the function declarator. */
          print_special_op_function_declarator(s, &len, ctype, i, t,
                                               &formal_nodes);
          /* Print a semicolon. */
          print2(s, &len, ";\n", 2);
        }
      }
    }
  }
  
  switch (aclass)
  {
  case CUR:
    id = ctype->cctype->cursor_id;
    /* Can't be 0 (not a legal cursor id)
       or less than 0 (generic cursor id) */
    assert(id > 0);
    break;
  case CON:
    id = ctype->cctype->container_id;
    /* Can't be 0 (not a legal container id)
       or less than 0 (generic container id) */
    assert(id > 0);
    break;
  case SCH:
    id = 0;
    break;
  default:
     
#ifndef NDEBUG
    assertion_failed("op_vec_nonterm called with illegal aclass %s",
      aclass_string(aclass));
#endif /* NDEBUG */
    break;
  }

    /* Print the operation vector declaration. */

    printf1(s, &len, "P2_op_vec_func P2_op_vec_id%d[%d] = {\n",
            id, op_list->size);
    for (t = 0; t < op_list->size; t++)
    {
      printf1(s, &len, "(P2_op_vec_func) %s", op_list->tuple[t].procedure);
      if (t != op_list->size-1)
        print2(s, &len, ",", 1);
      print2(s, &len, "\n", 1);
    }
    printf1(s, &len, "};\n");

  /* Print special operation definitions. */

  for (i = 0; op_tab[i].name != NULL; i++)
    if (proceduralize_op(i, ctype)
        && op_fully_parameterized_by_aclass(i, aclass))
      for (t = 0; t < op_list->size; t++)
        if (op_list->tuple[t].i == i)
          print_special_op_function_definition(s, &len, ctype, i, t, &formal_nodes);
  
  return(terminal_string(s));
}

/*****************************************************************************/
/*                  Member (ie dot and arrow) operator nonterminal node      */
/*****************************************************************************/

inline static NODE *
member_nonterm (NODE *postfix_expression, NODE *op, NODE *member_name)
{
  IDENT *i = postfix_expression->ident->ctype->ident;
  char  s1[SPRINT_BUF_SIZE];
  CTYPE *member_ctype;
  NODE *result;
  ENTRY *e;
  
  /* Set the type of the expression to the type of the member. */
  
  if (i == NULL) {
    sprint_ptree(s1, postfix_expression);
    parse_error("component selection on %s not aggregate", s1);
  }
  e = symlist_lookup(i->members, member_name->ident->name);
  if (e == NULL) {
    char s3[SPRINT_BUF_SIZE];
    sprint_ptree(s1, postfix_expression);
    sprint_ptree(s3, member_name);
    warning(4, "aggregate %s does not have member %s, assuming member is void",
            s1, s3);
    member_ctype = void_read_only_ctype;
  }
  else
    member_ctype = e->ident->ctype;
  result = nonterm(TYP, member_ctype, 3, postfix_expression, op, member_name);
  return result;
}

/* This function returns postfix_expression.obj if member_name == "obj",
   ref(postfix_expression, member_name) otherwise. */

/* ctype is the ctype of postfix_expression. */

inline static NODE *
cursor_member_nonterm (NODE *postfix_expression, CTYPE *ctype,
                       NODE *member_name)
{
  NODE *result = NULL;
  ENTRY *e;

  if (strcmp(member_name->ident->name, "obj") == 0)
  {
    /*** Case 1: postfix_expression.obj ***/

    /* Object Pointer Reference: member_name is "obj".
       "postfix_expression.member_name" -> "postfix_expression.obj" */

    CTYPE *c = copy_ctype(ctype->cctype->ident3->ele->ctype);
    expand(c, new_ptype(PTR, UND, NULL));
    result = nonterm(TYP, c, 3, postfix_expression, dot(), member_name);
    /* Skip check for e == NULL. */
    return(result);
  }
  if (result == NULL)
  {
    /*** Case 2: ref(postfix_expression, member_name) ***/

    /* Element Member Field Reference: member_name is a field of the original
       (untransformed) ELEMENT type. "postfix_expression.member_name"
       -> ref(postfix_expression, member_name) */

    IDENT *i = ctype->cctype->orig_type;
    NODE  *params = nonterm(TYP, ctype, 3,
                            postfix_expression,
                            comma(),
                            member_name);
    NODE *n;

    params->arg[2] = terminal_ident(member_name->ident);
    assert_node_valid(params);
    
    /* Make sure that member_name is a field of the original
       (untransformed) ELEMENT type. */
    e = symlist_lookup(i->members, member_name->ident->name);
    if (e != NULL)
    {
      n = terminal_string1("ref");
      result = special_op_nonterm(n, params);
      result->ident->ctype = e->ident->ctype;
    }
  }
  /* Generic containers have ident3 equal to NULL. */
  if (result == NULL && ctype->cctype->ident3 != NULL)
  {
    /*** Case 3: postfix_expression.member_name ***/

    /* Cursor Member Field Reference: member_name is a field of the transformed
       CURSOR struct.  For example, a field added by cursor_structure.
       "postfix_expression.member_name" -> "postfix_expression.member_name" */

    /* Note: Logically, cases 1 and 2 take precidence over this case.
       For instance, if there is a field "foo" that is a member of
       both the cursor and the element, "cursor.foo" should be
       expanded to "ref(cursor, foo)" (usually "((cursor).obj)->foo"),
       NOT "cursor.foo".  Thus, make sure the code for this case
       FOLLOWS the code for cases 1 and 2. */
    e = symlist_lookup(ctype->cctype->ident3->cur->members,
                       member_name->ident->name);
    if (e != NULL)
      result = member_nonterm(postfix_expression, dot(), member_name);
  }
  if (e == NULL) {
    /*** Error ***/

    char s1[SPRINT_BUF_SIZE], s3[SPRINT_BUF_SIZE];
    sprint_ptree(s1, postfix_expression);
    sprint_ptree(s3, member_name);
    parse_error("cursor %s does not have member %s", s1, s3);
  }

  return result;
}

NODE *
dot_member_nonterm (NODE *postfix_expression, NODE *member_name)
{
  CTYPE *ctype = postfix_expression->ident->ctype;
  NODE *result;

  if (ctypematch1(ctype, cursor_read_only_ctype, TRUE)
      || ctypematch1(ctype, generic_cursor_read_only_ctype, TRUE))
    result = cursor_member_nonterm(postfix_expression, ctype, member_name);
  else
    result = member_nonterm(postfix_expression, dot(), member_name);

  return result;
}

NODE *
arrow_member_nonterm (NODE *postfix_expression, NODE *member_name)
{
  CTYPE *ctype = copy_ctype(postfix_expression->ident->ctype);
  NODE *result;

  reduce(ctype, PTR);
  if (ctypematch1(ctype, cursor_read_only_ctype, TRUE)
      || ctypematch1(ctype, generic_cursor_read_only_ctype, TRUE)) {
    NODE *n;
    n = nonterm(TYP, ctype, 4, leftp(), star(), postfix_expression, rightp());
    result = cursor_member_nonterm(n, ctype, member_name);
  }
  else
    result = member_nonterm(postfix_expression, arrow(), member_name);
  return result;
}

/*****************************************************************************/
/*                  type expressions                                         */
/*****************************************************************************/

void
typex_declaration (NODE *params)
{
  TLIST *tlist;
  tlist = params_to_tlist(params);
  add_typex_to_symtab(tlist);
}

/*****************************************************************************/
/*                  string_literal_list stuff                                */
/*****************************************************************************/

NODE *
string_literal_list_action (NODE *n1, NODE *n2)
{
   int i = strlen(n1->ident->name);
   int j = strlen(n2->ident->name);
   char *c = xmalloc_atomic(i+j-1);
   NODE *n;

   strcpy(c, n1->ident->name);
   *(c+i-1) = '\0';
   strcat(c+i-1, n2->ident->name + 1);
   n = terminal1(TYP, c, string_read_only_ctype);
   return n;
}

/*****************************************************************************/
/*                  Schemas                                                  */
/*****************************************************************************/

/* Add some checking for more than once schema instance per
   application??? (JAT) */

void
pre_typex_schema_declaration (void)
{
#if 0
  decl->btype = SCHEMA_CTYPE;
  assert_ctype_valid(decl->btype);
#else
  set_btype(SCHEMA_CTYPE);
#endif
  unnamed_aggregate_declaration_action();
}

/* Problem:

     Want a single, shared te for the schema and all of its member
     containers why???

     Want a new, separate te for the schema and all of its member
     containers so that each member container can have it's own
     annotations.  For example, employee array can have size 1000,
     department array size 100, and job array size 10.

*/

void
post_typex_schema_declaration (char *typex_name)
{
  IDENT *ident = decl->btype->ident;
  MCURSOR *mcurs = new_mcursor(ident);
  OP_LIST *op_list = new_op_list(decl->btype, NULL, SCH);
  CTYPE *ctype = ident->ctype;
  TE *te = typex_name_to_te(typex_name); /* Create new te. */

  ctype->cctype = xmalloc_object(CCTYPE);
  memset((void *) ctype->cctype, 0, sizeof(CCTYPE));
  set_container_cctype_te(ctype->cctype, te);
  ctype->cctype->op_list = op_list;

  FOREACH_MEMBER(mcurs)
  {
    CTYPE *member_ctype = mcurs->pos->ident->ctype; /* Same for all members? */
#if 0
    if (ctypematch1(member_ctype, container_read_only_ctype, TRUE))
#else
    if (base_ptype(member_ctype)->pclass == CON)
#endif
    {
      assert(member_ctype->cctype != NULL);
      set_container_cctype_te(member_ctype->cctype, te);
      member_ctype->cctype->op_list = new_op_list(member_ctype, NULL, CON);
      /* Schema name is set in pb/pb-gram.y */
      /* Make sure cctype->schema is NULL. */
      assert(member_ctype->cctype->schema == NULL);
    }
  }
  xfree(mcurs);
}

void
post_ddlhint_schema_declaration (char *schema_name, char *typex_name)
{
  IDENT *ident = decl->btype->ident;
  MCURSOR *mcurs = new_mcursor(ident);
  CTYPE *ctype = ident->ctype; /* Why??? */
  CTYPE *member_ctype;
  TE *te = NULL;  /* Individual te shared by all schema member containers. */
  NODE *v = NULL; /* Combined verbatim of schema and all members. */
  NODE *n = NULL; /* Combined operation vector of schema and all members. */
  /* Each container in a schema container declaring list containing
     more than one container will have the same container identifier.
     All such containers will have the same operation vector, so we
     only want to print the operation vector of the first such container.
     We accomplish this by remembering the container id of the last
     operation vector we printed, and only printing a new operation
     vector for a container whose container_id != op_vec_container_id
     (JAT) */
  int op_vec_container_id = 0; /* container id of previously printed op vec. */

  /* For the schema, set the schema name. */
  decl->btype->cctype->schema = schema_name;

  /* For all member containers, set the schema name and call
     set_ctype_ident3(). */
  FOREACH_MEMBER(mcurs)
  {
    member_ctype = mcurs->pos->ident->ctype;
#if 0
    if (ctypematch1(member_ctype, container_read_only_ctype, TRUE))
#else
    if (base_ptype(member_ctype)->pclass == CON)
#endif
    {
      /* Set the schema name. */
      member_ctype->cctype->schema = schema_name;
      /* Use the schema member name (a container name) as cont_name. */
      set_ctype_ident3(member_ctype, typex_name, mcurs->pos->ident->name);
    }
  }

  /* For all member containers:
     (1) call verbatim_nonterm(..., CON) (which calls the k_verbatim()
         special operation), and
     (2) if the type expression requires an operation vector, call
         op_vec_nonterm(). */
  FOREACH_MEMBER(mcurs)
  {
    member_ctype = mcurs->pos->ident->ctype;
#if 0
    if (ctypematch1(member_ctype, container_read_only_ctype, TRUE))
#else
    if (base_ptype(member_ctype)->pclass == CON)
#endif
    {
      v = nonterm(UNT, NULL, 2, v, verbatim_nonterm(member_ctype, CON));
      /* For the first member container, set te and f. */
      if (te == NULL)
      {
        te = member_ctype->cctype->te;
      }
#ifndef NDEBUG
      /* For subsequent member containers, make sure that they share
         type expression te. */
      else
      {
        assert(te == member_ctype->cctype->te);
      }
#endif /* NDEBUG */
      /* operation vector */
      if (te_requires_op_vec(te))
        if (member_ctype->cctype->container_id != op_vec_container_id)
        {
          /* Remember container id. */
          op_vec_container_id = member_ctype->cctype->container_id;
          /* Print operation vector. */
          n = nonterm(UNT, NULL, 2, n, op_vec_nonterm(member_ctype, CON));
        }
      /* pname */
      if (te->requires_indirect_only && direct_ctype(member_ctype))
        parse_error("automatic indirection of schema member containers"
                    " is not yet implemented: manually convert"
                    " schema %s container %s to an indirect reference",
                    schema_name, mcurs->pos->ident->name);
    }
  }

  /* For the schema:
     (1) call verbatim_nonterm(..., SCH) (which calls the s_verbatim()
         special operation), and
     (2) if the type expression requires an operation vector, call
         op_vec_nonterm(). */
  v = nonterm(UNT, NULL, 2, v, verbatim_nonterm(decl->btype, SCH));
  assert(decl->verbatim_ptree == NULL); /* Don't over-write if non-NULL. */
  decl->verbatim_ptree = v;
  if (te_requires_op_vec(ctype->cctype->te))
    n = nonterm(UNT, NULL, 2, n, op_vec_nonterm(decl->btype, SCH));
  assert(decl->op_vec_ptree == NULL); /* Don't over-write if non-NULL. */
  decl->op_vec_ptree = n;

  /* Add initialized field to schema. */
  init_schema_def(decl->btype->ident);

  xfree(mcurs);
}

/* This routine declares an unnamed schema by copying the schema
   struct members to symtab[OTH] and deleting the schema struct.
   The net effect is to "promote" the schema members from the
   schema struct scope to the next higher scope. (JAT) */

void
unnamed_schema_declaration (void)
{
  IDENT *ident = decl->btype->ident;
  char *name = ident->name;
  MCURSOR *mcurs = new_mcursor(ident);

  /* Add all schema struct members to symtab[OTH]. */
  FOREACH_MEMBER(mcurs)
  {
    /* Might want to change eclass from MBR to UND. (JAT) */
    add_ident_to_symtab1(symtab[OTH], mcurs->pos->ident);
  }

  /* Delete schema struct. */
  delete_entry_from_symlist(&decl->declared_but_unprinted, name);
  delete_entry_from_symtab(symtab[SUE], name);

  xfree(mcurs);
}
