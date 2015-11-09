/* $Id: typex.h,v 45.0 1997/09/19 05:46:03 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Type expression declarations. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifndef INCLUDE_TYPEX_H
#define INCLUDE_TYPEX_H

#include "lex.h"       /* MAX_IDENT_LEN */
#include "util.h"      /* BOOLEAN */
#include "xform.h"     /* LAYER_DEF */

#define MIN_COMPONENT_ID  0
#define MAX_COMPONENT_ID  99
#define MIN_TYPEX_ID      100
#define MAX_TYPEX_ID      255

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

typedef struct tlist_struct {
   char  name[MAX_IDENT_LEN]; /* Name of component or type expression. */
   int   id;                  /* Internal identifier.
                                 Components:
                                   MIN_COMPONENT_ID ... MAX_COMPONENT_ID
                                 Type expressions:
                                   MIN_TYPEX_ID ... MAX_COMPONENT_ID
                                 This value is assigned. (DSB) */
   struct tlist_struct *next; /* Next component/typex in list. */

/* Note: one and only one of the following fields
   (te or layerdef) will be NULL. (DSB) */

   struct tlist_struct *te;   /* Root of type expression.
                                 NULL if this node is not a root. */
   LAYER_DEF *layerdef;       /* If layer, pointer to layer definition. */
} TLIST;

/*****************************************************************************/
/*                  External declarations and function prototypes.           */
/*****************************************************************************/

extern    int layer_counter;

TLIST     *add_typex_to_symtab(TLIST *t);
void      adorn(TE *te, PATH *path, const char *layer_name,
                int annotec, NODE **annotev);
BOOLEAN   are_cursors_stable_at_higher_layers(TE *t);
BOOLEAN   are_cursors_stable_at_lower_layers(TE *t, int a);
void      check_for_missing_annotations(TE *te, const char *cont_name);
void      check_typex_or_layer_name(const char *name, int len, int i);
TLIST     *is_typex(const char *name);
TLIST     *new_tlist(const char **name, int n);
void      print_typex(void);
TE        *reroute(TE *te, int cont_id);
TE        *retrieval_layer_is_below (TE *te, int retrieval_layer);
TE        *tlist_to_te(const TLIST *t);
const TE  *top_node(const TE *te);
TE        *unify_another_te(TE *unified_te, TE *te, int cont_id);
TE        *unify_te(TE *te1, int cont_id1, TE *te2, int cont_id2);

#endif /* INCLUDE_TYPEX_H */
