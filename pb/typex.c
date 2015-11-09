/* $Id: typex.c,v 45.4 1997/09/29 03:50:29 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Type expression definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>     /* assert() */
#include <stdarg.h>     /* va_list, ap */
#include <stdio.h>      /* printf() */
#include <string.h>     /* strstr() */

#include "annotation.h" /* name_match() */
#include "call-down.h"  /* call_level() */
#include "error.h"      /* parse_error() */
#include "layer-tab.h"  /* layer_tab */
#include "typex.h"
#include "util.h"       /* BOOLEAN */
#include "xmalloc.h"    /* xmalloc() */
#include "xform.h"      /* ANNOTATION */

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

typedef enum {
  FORWARD,
  BACKTRACK
} DIRECTION;

/*****************************************************************************/
/*                  Variables                                                */
/*****************************************************************************/

/* Layer number counter, zero reserved for conceptual. */
int layer_counter;

/* list of defined type expressions */
static TLIST *type_expressions = NULL;

/*****************************************************************************/
/*                  Check typex name                                         */
/*****************************************************************************/

void
check_typex_or_layer_name (const char *name, int len, int i)
{
  /* i == 0 indicates name is a typex name,
     i >= 1 indicates name is a layer name. */

  char *s = (i == 0)? "typex" : "layer";

  /* Make sure that name is not too long. */

  if (len > MAX_IDENT_LEN-1)
    parse_error("%s name too long--maximum length is %d characters",
      s, MAX_IDENT_LEN-1);

  /* If typex name, make sure that name doesn't end in a digit. */

  if (i == 0 && name[len-1] >= '0' && name[len-1] <= '9') {
    parse_error("%s name cannot end in a numeral", s);
  }
}

/*****************************************************************************/
/*                  New TLIST                                                */
/*****************************************************************************/

static TLIST *
new_tlist1 (const char *name, int id, TLIST **head, TLIST **tail)
{
  /* Counter for next type identifier. */
  static int type_expression_counter = MIN_TYPEX_ID;

  TLIST *t = (TLIST*) xmalloc(sizeof(TLIST));
  
#ifndef NDEBUG
  check_typex_or_layer_name(name, strlen(name), id);
#endif /* NDEBUG */

  strcpy(t->name, name);
  t->te           = NULL;
  t->layerdef     = NULL;
  if (id == 0) {
    /* typex name */
    t->id         = type_expression_counter++;
    (*tail)       = t;
  }
  else {
    /* layer name */
    t->id         = id;
    (*head)->next = t;
  }
 (*head)          = t;
  return(t);
}

/* This routine creates a TLIST of nodes that are to represent the
   arguments of a typex declaration.  No fancy processing goes on
   inside, other than assigning node ids. (DSB) */
/* name is an array of layer name strings. */

TLIST *
new_tlist (const char **name, int n)
{
  TLIST *head;
  TLIST *tail;
  int       id = 0;
  int       i;
  
  for (i = 0; i < n; i++) {
#ifndef NDEBUG
    if (strcmp(name[i], "conceptual") == 0) {
#if 0
      /* Why is this here?  It never seems to be executed. (JAT) */
      /* Replacement of conceptual by other layers is done by ddl,
         it should not be done here. (JAT) */
      new_tlist1("top2ds",             id++, &head, &tail);
      new_tlist1("generic",            id++, &head, &tail);
      new_tlist1("init_generic",       id++, &head, &tail);
#if 1
      new_tlist1("generic_funcall",    id++, &head, &tail);
#else
      new_tlist1("named_funcall",      id++, &head, &tail);
#endif
      new_tlist1("inbetween",          id++, &head, &tail);
      new_tlist1("qualify",            id++, &head, &tail);
#else
      /* Fail if this is ever executed. (JAT) */
      assertion_failed("new_tlist: name[i] == conceptual");
#endif
    }
    else
#endif /* NDEBUG */
      new_tlist1(name[i], id++, &head, &tail);
  }
  head->next = NULL;
  return(tail);
}

/*****************************************************************************/
/*                  Local Utilities                                          */
/*****************************************************************************/

/* This procedure strips off the identifying and trailing digits of a
   layer name or typex name.  Input string is s and output string is c. */

static void
truncate (const char *s, char *c)
{
  const char *e;
  
  e = s + strlen(s) - 1;
  while (*e <= '9' && *e >= '0')
    e--;
  while (s<=e)
    *c++ = *s++;
  *c = '\0';
}

/* This procedure returns a pointer to a layer's definition given its name.
   If n is not a layer, a null pointer is returned. */

static LAYER_DEF *
is_layer (const char *layer_name)
{
  int  i;
  char short_layer_name[MAX_IDENT_LEN];
  
  truncate(layer_name, short_layer_name);
  for (i=0; layer_tab[i] != 0; i++) {
    if (layer_tab[i]->layer_name[0] == '\0')
      assertion_failed("layer_tab[%d]->layer_name[0] = 0", i);
    if (strcmp(layer_tab[i]->layer_name, short_layer_name) == 0) 
      return(layer_tab[i]);
  }
  return(NULL);
}

/* This procedure returns a pointer to the root of the type expr with
   the given layer_name.  If the given layer_name is not the
   layer_name of a typex, returns NULL. */

TLIST *
is_typex (const char *layer_name)
{
  TLIST *tx;
#if 0
  char  short_layer_name[MAX_IDENT_LEN];
  truncate(layer_name, short_layer_name);
  for (tx = type_expressions; tx != NULL; tx = tx->te) {
    if (strcmp(tx->layer_name, short_layer_name) == 0)
      return(tx);
  }
#else
  for (tx = type_expressions; tx != NULL; tx = tx->te) {
    if (strcmp(tx->name, layer_name) == 0)
      return(tx);
  }
#endif
  return(NULL);
}

/*****************************************************************************/
/*                  Add typex to symtab.                                     */
/*****************************************************************************/

/*
   add_typex_to_symtab(t)--t is a type expression in the form of a
     TLIST.  add_typex_to_symtab(t) adds t to the list of type exprs
     already defined.  There is some minimal checking to see that the
     elements referenced are either primitive layers or previously
     defined type expressions.  The latter is useful to preclude
     circular definitions (i.e., data structures with feedback--a
     nonsensical concept).

  errors:
    typex name already defined--multiple type expressions with
      same name.
    invalid type expression--too many components--the flattened
      typex given has too many components.  Should not
      occur if ddl preprocessor is used--that's where
      the error should be caught.
    invalid type expression--too few components--the flattened
      typex has too few components.  Should not occur
      ... see last error for details.

  (DSB)
*/

static void
check_typex_nodes (const TLIST *t)
{
  TLIST *n;
  int   actual_len = 0;
  int   expected_len = 1;
  char  short_layer_name[MAX_IDENT_LEN];

  for (n = t->next; n != NULL; n = n->next) {
    actual_len++;
    n->layerdef = is_layer(n->name);
    if (n->layerdef == NULL) {
      n->te = is_typex(n->name);
      if (n->te == NULL) {
        truncate(n->name, short_layer_name);
        parse_error("typex name undefined: %s", short_layer_name);
      }
    }
    else {
      n->te = NULL;
      if (actual_len > expected_len) {
        truncate(t->name, short_layer_name);
        error("invalid type expression %s: too many components", short_layer_name);
      }
      expected_len += n->layerdef->num_of_params;
    }
  }
  if (actual_len != expected_len) {
    truncate(t->name, short_layer_name);
    parse_error("invalid type expression %s: too %s components", short_layer_name,
      (actual_len < expected_len)? "few" : "many");
  }
}

TLIST *
add_typex_to_symtab (TLIST *t)
{
  char short_layer_name[MAX_IDENT_LEN];
  
  /* Step 1: check to see that the first node has not been defined
     previously. */
  
  if (is_layer(t->name) != NULL
      || is_typex(t->name) != NULL) {
    truncate(t->name, short_layer_name);
    error("typex name already defined: %s", short_layer_name);
  }
  
  /* Step 2: check to see that all other nodes have been defined
     previously.  Also make sure that the type expression actually
     contains the expected number of nodes. */
  
  check_typex_nodes(t);

  /* Step 3:  Now go and add t to the list of recognized type
     expressions. */
  
  t->te = type_expressions;
  type_expressions = t;
  return(t);
}

/*****************************************************************************/
/*                  TE contains layer_name with substring                     */
/*****************************************************************************/

/* This routine is a HACK.  Presumably, it will eventually be
   subsumed by a DaTE-style layout editor.  (JAT) */

/* This routine returns TRUE iff te contains a layer whose name
   includes the give substring. */

static BOOLEAN
te_contains_layer_name_with_substring (const TE *te, const char *s)
{
  if (te != NULL) {
    if (strstr(te->layer_name, s) != NULL)
      return(TRUE);
    else {
      int i;
      for (i = 0; i < te->layerdef->num_of_params; i++)
        if (te_contains_layer_name_with_substring(te->down[i], s))
          return(TRUE);
    }
  }
  return(FALSE);
}

/*****************************************************************************/
/*                  New TE.                                                  */
/*****************************************************************************/

static TE *
new_te (const char *te_name, LAYER_DEF *layerdef, TE *parent, BOOLEAN top)
{
  TE *te = xmalloc_object(TE);
  memset((void *) te, 0, sizeof(TE));

  strcpy(te->layer_name, te_name);
  te->layerno          = layer_counter++;
  te->layerdef         = layerdef;
  te->parent           = parent;
  te->top              = top;

#ifndef NDEBUG
  te->requires_proceduralize_ref = -1;
  te->requires_indirect_only = -1;
  te->requires_op_vec = -1;
  te->requires_kcur = -1;
#endif /* NDEBUG */

  return(te);
}

/*****************************************************************************/
/*                  TLIST to TE                                              */
/*****************************************************************************/

/*
   Create a *new* type expression tree (TE) from the linear format (TLIST).

   This routine is a recursive utility routine that creates a type
   expression tree from t, and does the work of creating te trees.

   Arguments:
     tlist is a type expression in the form of a TLIST.
     parent is the pointer to the parent TE node.
     top indicates whether the root node created by this routine is the
       root of a type-expression column.

   Fatal errors:                                               
    "invalid type expression"
       Indicates that name in TLIST cannot be identified with known
       typex or layer.  This error should never happen since
       add_typex_to_symtab() should have caught the error.

  (DSB)
*/

static TE *
tlist_to_te1 (const TLIST **tlist, TE *parent, BOOLEAN top)
{
  /* Allocate TE node and fill in its values. */
  
  TE *te = new_te((*tlist)->name, (*tlist)->layerdef, parent, top);

  /* Fill in its parameters. */
  
  top = FALSE;
  if (te->layerdef != NULL) {
    /* Action for layer. */
    int i;
    for (i = 0; i < te->layerdef->num_of_params; i++) {
      *tlist = (*tlist)->next;
      te->down[i] = tlist_to_te1(tlist, te, top);
      top = TRUE;
    }
  }
  else {
    /* Action for typex reference. */
    TLIST *r = is_typex(te->layer_name);
    if (r) {
      const TLIST *rr = r->next;
      te->down[0] = tlist_to_te1(&rr, te, FALSE);      
    }
    else 
      error("invalid type expression %s", te->layer_name);
  }
  return(te);
}

/* This function takes a type expression in the form of a TLIST and
   creates a type expression tree.  No node is created to maintain the
   name of the expression, as you might expect. (DSB) */

TE *
tlist_to_te (const TLIST *tlist)
{
  /* This function takes the linear format of tlist and creates a
     proper type expression tree whose root node is the root (first)
     layer of tlist. (DSB) */
  
  TE *te;

  /* Begin tree creation with first node. */
  
  tlist = tlist->next;

  /* Convert tlist to te. */

  te = tlist_to_te1(&tlist, NULL, TRUE);

  /* Fill in "requires_" fields. */
  /* Note: only works for the topmost layer in the type expression. (JAT) */

  te->requires_proceduralize_ref
    = (te_contains_layer_name_with_substring(te, "part")
       || te_contains_layer_name_with_substring(te, "recover"));
  te->requires_indirect_only
    = (te_contains_layer_name_with_substring(te, "mmap")
       || te_contains_layer_name_with_substring(te, "persist")
       || te_contains_layer_name_with_substring(te, "shared"));
  te->requires_op_vec
    = (te_contains_layer_name_with_substring(te, "generic")
       || te_contains_layer_name_with_substring(te, "funcall")
       || te_contains_layer_name_with_substring(te, "recover"));
  te->requires_kcur
    = (te_contains_layer_name_with_substring(te, "kcur"));

  /* Return. */

  return(te);
}

/*****************************************************************************/
/*                  Search.                                                  */
/*****************************************************************************/

/*
   search(t,p,d) returns a TE * to the type expression node in tree
     t whose path name is p.  d is an enum whose values are FORWARD or
     BACKTRACK.  Always use FORWARD when calling search; BACKTRACK is
     used only internally by the algorithm when searching multiple
     child paths

   fatal errors
     path too long--the end of a type expression tree has been
       reached and there still more path to follow.
     null path encountered--search was called with a null path.
     bad path--all the children of a node have been searched and
       there is no path from which to backtrack.

   (DSB)
*/

static TE *
search (TE *te, const PATH *path, DIRECTION direction) 
{
  int i;
  TE  *result;
  
  /* Step 1:  make sure that there is a node to examine in the
     type expression */
  
  if (te == NULL) {
    switch (direction) {
    case FORWARD:
      error("path too long %s", (*path));
    case BACKTRACK:
      return(NULL);
    }
  }
  
  /* Step 2:  make sure that there is a path to follow */
  
  if (strcmp((*path)[0].str, "") == 0)
    error("null path encountered");
  
  /* Step 3:  examine current node.  If there is a match of names
     do one of two things: either we're at the end of the
     path, which means we've found the node in question,
     or we need to continue searching.  In any case, bump 
     the path pointer and we are no longer in a backtracking
     mode as we've had a match. */
  
  if (strcmp(te->layer_name, (*path)[0].str) == 0) {
    direction = FORWARD;
    path = (PATH *) &(*path)[1]; /* an ugly way to increment */
    if (strcmp((*path)[0].str, "") == 0)
      return(te);
  }
  
  /* Step 3:  continue looking.  We need to proceed to the children
     or child of t.  If there is a single child, just go
     to it.  Otherwise, for each child, we'll have to search
     in a backtracking manner */
  
  if (!te->layerdef || te->layerdef->num_of_params == 1) 
    return(search(te->down[0], path, direction));
  else {
    for (i = 0; i < te->layerdef->num_of_params; i++) {
      result = search(te->down[i], path, BACKTRACK);
      if (result != NULL)
        return(result);
    }
    if (direction != BACKTRACK)
      error("search: bad path: trying to annote layer \"%s\""
            " which does not appear in type expression?",
            (*path)[0].str);
    return(NULL);
  }
} 

/*****************************************************************************/
/*                  add and remove type expressions.                         */
/*****************************************************************************/

static TE *
add_te (TE *src)
{
  TE *dest;

  if (src->layerdef->num_of_params != 1)
    error("layer %s must have 1 parameter to replicate", src->layer_name);

  /* First, allocate the te and copy all the data. */

  dest = xmalloc_object(TE);
  memcpy(dest, src, sizeof(TE));

  dest->layerno = layer_counter++;
  dest->top = FALSE;
  dest->version_number = src->version_number + 1;

  /* Alter parent and down. */

  dest->parent = src; 
  src->down[0]->parent = dest;

  dest->down[0] = src->down[0];
  src->down[0] = dest;

  return(dest);
}
    
static void
remove_te (TE *te)
{
  if (te->layerdef->num_of_params != 1)
    error("No annotation for layer \"%s\", attempted to remove it"
          " from type expression, but layer has %d parameters;"
          " can only remove layers with exactly 1 parameter",
          te->layer_name, te->layerdef->num_of_params);
  else
  {
    TE *child = te->down[0];
    TE *parent = te->parent;

    /* Should this be a warning() or a parse_warning()?
       parse_warning() prints the line number (which is good), but
       also the token queue (which is bad, because ddl transforms
       annotations into something resembling a function call. (JAT) */

    parse_warning(2,
      "No annotation for layer \"%s\", removing it from type expression;"
      " to keep it, either modify .p2 file to give layer an annotation,"
      " or modify layer definintion in .xp file to \"optional annotation\"",
      te->layer_name);

    /* Replace reference to the te by its parent with its child. */
    if (parent != NULL) { 
      int i;
      for(i=0; i<MAX_TE_ARG; i++) { 
        if (parent->down[i] == te) { 
          parent->down[i] = child;
          break;
        }
      }
    }

    /* Replace references to the te by its child with its parent. */
    if (child != NULL) { 
      child->parent = parent;
      child->top = te->top;
    }
  }
}

/*****************************************************************************/
/*                  Adorn.                                                   */
/*****************************************************************************/

/*
   adorn(te, path, layer_name, cont_name, annotev) assigns annotations
   annotev[0...annotec-1] to the node = search(te, path, FORWARD).
   Note that unpacking is done now.  Also, layer is the name of the
   layer on which to adorn the annotation; this is to make sure that
   the annotation for an "array" is an "array" annotation.

   fatal errors:
     bad path--a path was given that corresponds to know known node
       in the given type expression tree.
   warnings:
     multiple annotations for node--only one annotation per node is
       legal--the first annotations are ignored.
     annotation for node->layer_name on layer--an attempt was made to
       annotate layer with an annotation for layer node->layer_name.

   (DSB)
*/

inline static BOOLEAN
already_adorned (TE *node, const char *cont_name)
{
  ANNOTE *x;
  for (x = node->annotation; x != NULL; x = x->next)
    if (name_match(cont_name, x->cont_name))
      return(TRUE);
  return(FALSE);
}

void
adorn (TE *te, PATH *path, const char *layer_name, int annotec, NODE **annotev)
{
  TE   *node;
  char short_layer_name[MAX_IDENT_LEN];

  assert(annotec > 0);

  /* Step 1: Find node in the type expression tree that is referenced
     by the path. */

  node = search(te, path, FORWARD);
  if (!node) 
    error("adorn: bad path");

  /* Step 2: Just to make sure we have the right node, take the
     layer_name and remove the trailing digits (which distinguishes
     different instances of the layer). */
  
  truncate(node->layer_name, short_layer_name);
  if (strcmp(short_layer_name, layer_name) != 0)
    error("annotation for %s on layer %s", layer_name, node->layer_name);

  /* Step 3: Annotate the node. */

  if (already_adorned(node, (char *) annotev[0])) { 
    assert(node->layerdef->needs_annotation != NO_ANNOTATION);
    if ((node->layerdef->needs_annotation == ANNOTATION) || 
        (node->layerdef->needs_annotation == OPTIONAL_ANNOTATION)) { 
      /*
         Single annotation node. We will need to replicate it. Since
         we may already have some replicated layers, we need last_node
         pointing to the last location of the replicated layers. (BJG)
      */
      TE *new_node;
      TE *last_node;

      last_node = node;
      while(strcmp(last_node->down[0]->layer_name, node->layer_name) == 0)
        last_node = last_node->down[0];
      new_node = add_te(last_node);
#if 0
      new_node->already_adorned = TRUE;
#else
      assert(already_adorned(new_node, (char *) annotev[0]));
#endif
      call_level(new_node, DDLHINT_OP, 2, annotec, annotev);
    }
    else /* Multiple annotation nodes. */
      call_level(node, DDLHINT_OP, 2, annotec, annotev);
  }
  else { 
    call_level(node, DDLHINT_OP, 2, annotec, annotev);
#if 0
    node->already_adorned = TRUE;
#else
    assert(already_adorned(node, (char *) annotev[0]));
#endif
  }
}

/*****************************************************************************/
/*                  Print a single type expression.                          */
/*****************************************************************************/

/*
   This function prints a type expression tree.
   When calling this function, pass zero as the offset (o) parameter.

   Example call:
     print_te(y, 0);
   Yields:
     index1 big1 predindx1 dlist2 array3 transient
            x2 dlist1 dlist2 array transient
   Note that index1 has two parameters.  The subtree of the first
   parameter is listed on the line with "index1".  The second
   parameter is listed immediately below the first parameter
   "big1" (i.e., has the same offset, so that type expressions
   are easy to read.

   Assertions checked (formerly fatal errors):
     "bogus type tree s"
   Indicates that s is a name that cannot be identified with a layer
   or typex. Should not happen--error should be caught by earlier
   routines. (DSB) That's why I made it an assertion. (JAT)
*/

static void
print_te (TE *t, int offset)
{
#if 0
  /* This gets big fast. */
  int newoffset = offset + strlen(t->layer_name) + 1;
#else
  int newoffset = offset + 2;
#endif
  
  printf("%s ", t->layer_name);
  if (t->layerdef) {
    /* Action for layer. */
    if (t->layerdef->num_of_params == 0)
      printf("\n");
    else {
      int i;
      for (i=0; i<t->layerdef->num_of_params; i++) {
        print_te(t->down[i], newoffset);
        if (t->layerdef->num_of_params > 1)
          printf("%*s", newoffset, "");
      }
    }
  }
  else {
    /* Action for typex reference. */
    TLIST *r = is_typex(t->layer_name);
    if (r)
      print_te(t->down[0], newoffset);      
#ifndef NDEBUG
    else
      assertion_failed("bogus type tree %s", t->layer_name);
#endif /* NDEBUG */
  }
#if 0
  if (offset == 0)
    printf("\n");
#endif
}

/*****************************************************************************/
/*                 Print all type expressions.                               */
/*****************************************************************************/

void
print_typex (void)
{
  TLIST *tx;
  TE    *tx_tree;
  char  short_layer_name[MAX_IDENT_LEN];
  
  for (tx = type_expressions; tx != NULL; tx = tx->te) {
    tx_tree = tlist_to_te(tx);
    truncate(tx->name, short_layer_name);
    printf("%s : ", short_layer_name);
    print_te(tx_tree, 0);
  }
}

/*****************************************************************************/
/*                  Check for missing annotations                            */
/*****************************************************************************/

/* This routine traverses type expression tree te and makes sure that
   all layers that need annotations in fact have them.  This routine
   should be called after the te tree has been adorned. (DSB) */
/* Modifications by (BJG)??? */

void
check_for_missing_annotations (TE *te, const char *cont_name)
{
  int j = te->layerdef->needs_annotation;

  if (((j == ANNOTATION) || (j == MULTIPLE_ANNOTATION))
      && (te->annotation == NULL))
  {
    /* Required annotations. */
    /* Remove the layer. */
    remove_te(te);
    check_for_missing_annotations(te->down[0], cont_name);
  }
  else
  { 
    int i;
    if (((j == OPTIONAL_ANNOTATION) || (j == OPTIONAL_MULTIPLE_ANNOTATION))
        && (te->annotation == NULL)) { 
      /* Optional annotations. */
      /* Call DDLHINT with no annotations before proceeding. */
      call_level(te, DDLHINT_OP, 2, 1, (ANNOTE **) &cont_name);
    }
    for (i = 0; i < te->layerdef->num_of_params; i++)
      check_for_missing_annotations(te->down[i], cont_name);
  }
}

/*****************************************************************************/
/*                  Cursor stability.                                        */
/*****************************************************************************/

/* are_cursors_stable_at_higher_layers(t) looks at the stability of
   all layers above layer t in the type expression chimney.  If any
   are unstable, the result is FALSE, otherwise TRUE. (DSB) */

BOOLEAN
are_cursors_stable_at_higher_layers (TE *te)
{
  BOOLEAN result = TRUE;

  while (!te->top) {
    te = te->parent;
    result = result && te->layerdef->cursor_stability;
  }
  return(result);
}

/* are_cursors_stable_at_lower_layers(t,n) looks at root of a type
   expression t and traverses straight down the type expression
   chimney till it reaches the advance layer (whose layer number is n)
   or the D2U layer is reached. (The D2U layer is a logical deletion
   layer; this is the layer at which the deletion occurred).  Any
   unstable layers above the identified layer returns FALSE, otherwise
   TRUE. (DSB) */

BOOLEAN
are_cursors_stable_at_lower_layers (TE *te, int adv_layer_no)
{
  BOOLEAN result = TRUE;

  while (te->layerno != adv_layer_no && !te->layerdef->d2u) {
    result = result && te->layerdef->cursor_stability;
    te = te->down[0];
  }
  return(result);
}

/* are_cursors_stable_thru_retrieval_layer(t,n) looks at root of a
   type expression t and traverses straight down the type expression
   chimney till it reaches the advance layer (whose layer number is n)
   or a D2U layer is reached.  (The D2U layer is a logical deletion
   layer; this is the layer at which the deletion occurred).  Any
   unstable layers at or above the identified layer returns FALSE,
   otherwise TRUE. (DSB) */

BOOLEAN
are_cursors_stable_thru_retrieval_layer (TE *te, int adv_layer_no)
{
  BOOLEAN result = TRUE;

  do {
    te = te->down[0];
    result = result && te->layerdef->cursor_stability;
  } while (te->layerno != adv_layer_no && !te->layerdef->d2u);
  return(result);
}

/*****************************************************************************/
/*                  Retrieval layer is below                                 */
/*****************************************************************************/

/* Formerly, this procedure returned TRUE if the retrieval layer is
   below current node identified by type expression te; retrieval layer
   number is retrieval_layer. (DSB)

   Now, I modified this to return the te of the retrieval layer or NULL
   (rather than TRUE or FALSE. (JAT) */

TE *
retrieval_layer_is_below (TE *te, int retrieval_layer)
{
  do {
    te = te->down[0];
    if (te->layerdef->num_of_params == 0)
      return(NULL);
    if (te->layerno == retrieval_layer)
      return(te);
  } while (1);
}

#if 0
/*****************************************************************************/
/*                  Add conceptual layer                                     */
/*****************************************************************************/

/* Formerly, this procedure took a TLIST t0 and appended the conceptual
   layer onto its head producing another TLIST t1. (DSB)
   Now, this procedure does nothing. (JAT) */

TLIST *
add_conceptual_layer (TLIST *t0)
{
#if 0
  extern LAYER_DEF P2_conceptual_;

  TLIST *t1 = (TLIST*) xmalloc(sizeof(TLIST));
  TLIST *new_head = (TLIST*) xmalloc(sizeof(TLIST));

   *new_head = *t;
   new_head->next = t1; 
   strcpy(t1->name, "conceptual");
   t1->id       = 0;  /* Zero is reserved for the conceptual layer. */
   t1->te       = NULL;
   t1->layerdef = &P2_conceptual_;
   t1->next     = t->next;
   return(new_head);
#else
   return(t0);
#endif
}
#endif

/*****************************************************************************/
/*                  Top of type expression tree.                             */
/*****************************************************************************/

const TE *
top_node (const TE *te)
{
  assert(te != NULL);
  while(!te->top) {
    assert(te->parent != NULL);
    te = te->parent;
  }
  assert(te->parent == NULL);
  return(te);
}

/*****************************************************************************/
/*                  ccbus stuff                                              */
/*****************************************************************************/

/* Move this stuff into a separate file. (JAT) */

#define ANOTHER_LAYER(name, bottom) \
   bottom->down[0] = make_te_node(name, bottom); \
   bottom = bottom->down[0];

static TE *
make_te_node (const char *name, TE *parent)
{
  TE *te = new_te(name, is_layer(name), parent, (parent) ? TRUE : FALSE);
  return te;
}

static CCBUS *
bus_list (TE *te, int cont_id, CCBUS *next)
{
  CCBUS *x = (CCBUS *) xmalloc(sizeof(CCBUS));

  x->te      = te;
  x->cont_id = cont_id;
  x->next    = next;
  return x;
}

/*
   This routine takes in two te's of type TOP (or its specialization
   TOPLNK) and creates the following:
   top2lnk[nloops[linkterm[ccbus[te1, te2]]]].
   (DSB)
*/

TE *
unify_te (TE *te1, int cont_id1, TE *te2, int cont_id2)
{
  TE *top;
  TE *bottom;

  bottom = top = make_te_node("top2link", NULL);
  ANOTHER_LAYER("nloops", bottom);
  ANOTHER_LAYER("linkterm", bottom);
  ANOTHER_LAYER("ccbus", bottom);
  bottom->down[0] = NULL;

  /* now if both cont_ids are different, add both, otherwise, add one */

  if (cont_id1 != cont_id2) 
    bottom->bus_list = bus_list(te1, cont_id1, bus_list(te2, cont_id2, NULL));
  else
    bottom->bus_list = bus_list(te1, cont_id1, NULL);

  return top;
}   

#define FOREACH_TE(o, te) \
  for (o = te->bus_list; o ; o = o->next)

TE *
unify_another_te (TE *unified_te, TE *te, int cont_id)
{
  TE *bottom;
  CCBUS *o;

  /* find ccbus layer - identified with down[0] == NULL */

  for (bottom = unified_te; 
       bottom->down[0] != NULL;
       bottom = bottom->down[0]);

  /* add te only if it hasn't been added before */

  FOREACH_TE(o, te) {
    if (o->cont_id == cont_id)
      return unified_te;
  }
  bottom->bus_list = bus_list(te, cont_id, bottom->bus_list);

  return unified_te;
}

TE *
reroute (TE *te, int cont_id)
{
  CCBUS *o;

  FOREACH_TE(o, te) {
    if (o->cont_id == cont_id)
      return o->te ;
  }
  error("unknown path taken in ccbus layer");
  return NULL;
}
