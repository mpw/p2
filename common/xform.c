/* $Id: xform.c,v 45.3 1997/09/20 03:42:26 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Type expression transformation definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h> /* strcmp() */

#include "error.h"  /* assertion_failed() */
#include "op-tab.h" /* MIN_RCLASS, MAX_RCLASS */
#include "xform.h"  /* TE */

/*****************************************************************************/
/*                  Assertions.                                              */
/*****************************************************************************/

/* Make sure layerdef is a valid layer def. */

#ifndef NDEBUG
static void
assert_layerdef_valid (const LAYER_DEF *layerdef)
{
  if (layerdef == NULL)
    assertion_failed("NULL layerdef");
  if (layerdef->layer_name == NULL)
    assertion_failed("NULL layer_name");
  if (((int)layerdef->layer_realm < MIN_RCLASS) || 
      layerdef->layer_realm > MAX_RCLASS) 
    assertion_failed("illegal layer_realm = %d", layerdef->layer_realm);
}
#endif /* NDEBUG */

/* Make sure te is a valid type expression. */
/* This function *must* check to make sure te->layerdef is non-NULL. */

void
assert_te_valid (const TE *te)
{
#ifndef NDEBUG
  if (te == NULL)
    assertion_failed("NULL type expression ");
  assert_layerdef_valid(te->layerdef);
#if 0
  if (te->layerno == 0) {
    char *layer_name = te->layerdef->layer_name;
    if (strcmp(layer_name, "conceptual") != 0)
      assertion_failed("Top layer %s must be conceptual", layer_name);
  }
#endif
#endif /* NDEBUG */
}
