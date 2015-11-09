/* $Id: annotation.c,v 45.1 1997/09/19 07:50:15 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* Annotation definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL, sprintf() */
#include <string.h>       /* strcmp() */

#include "annotation.h"   /* MATCH */
#include "error.h"        /* assertion_failed() */
#include "string-util.h"  /* assert_string_nonempty_and_valid() */
#include "type.h"         /* UNKNOWN_CONT_ID, GENERIC_CONT_ID */
#include "xform.h"        /* ANNOTE, TE */
#include "xmalloc.h"      /* xmalloc() */

/************************************************************************/
/*              Add anotation.                                          */
/************************************************************************/

/* Queue an annotation onto the annotation list. */

void
add_annotation (TE *te, int size, int cont_id, char *cont_name)
{
  ANNOTE *x;

#ifndef NDEBUG
  for (x = te->annotation; x != 0; x = x->next) {
    if ((cont_id > 0) && (cont_id == x->cont_id))
      assertion_failed("Already have annotation with cont_id %d", cont_id);
    if ((strcmp(cont_name, "P2_default") != 0)
        && (strcmp(cont_name, x->cont_name) == 0))
      assertion_failed("Already have annotation with cont_name %s", cont_name);
  }
#endif /* NDEBUG */

#if XMALLOC_DEBUG
  {
    /* For xmalloc() debugging.  Print the name and size of the ANNOTE. */
    char comment_string[20];
    sprintf(comment_string, "ANNOTE%d", size);
    x = (ANNOTE *) xmalloc1(size, comment_string);
  }
#else
  x = (ANNOTE *) xmalloc(size);
#endif /* XMALLOC_DEBUG */

  x->next = te->annotation;
  x->cont_id = cont_id;
  x->cont_name = cont_name;
  te->first_annotation = x;
  te->annotation = x;
}

/************************************************************************/
/*              Lookup anotation.                                       */
/************************************************************************/

inline static void
assert_cont_id_valid (int id)
{
  /* 0 is not a legal container id.  This restriction is intended to
     help catch (and hopefully, correct) un-intialized container ids. */
  assert(id != 0);
  /* If container id is not > 0, it must be the unknown or generic */
  assert(id > 0 || id == UNKNOWN_CONT_ID || id == GENERIC_CONT_ID);
}

inline static char *
cont_id_string (int id)
{
  static char s[10];
  if (id == UNKNOWN_CONT_ID)
    return("unknown");
  else if (id == GENERIC_CONT_ID)
    return("generic");
  else {
    sprintf(s, "%d", id);
    return(s);
  }
}

MATCH
id_match (int key_id, int annote_id)
{
  BOOLEAN key_default, annote_default;
  key_default = (key_id < 0);
  annote_default = (annote_id < 0);

  if (key_default && !annote_default)
    return(DEFAULT_KEY_MATCH);
  else if (!key_default && annote_default)
    return(DEFAULT_ANNOTE_MATCH);
  else if (key_default && annote_default)
    return(DEFAULT_MATCH);
  else if(key_id == annote_id)
    return(EXACT_MATCH);
  else
    return(FALSE);
}

MATCH
name_match (const char *key_name, char *annote_name)
{
  BOOLEAN key_default, annote_default;
  key_default = (strcmp(key_name, "P2_default") == 0);
  annote_default = (strcmp(annote_name, "P2_default") == 0);

  if (key_default && annote_default)
    return(DEFAULT_MATCH);
  else if (key_default && !annote_default)
    return(DEFAULT_KEY_MATCH);
  else if (!key_default && annote_default)
    return(DEFAULT_ANNOTE_MATCH);
  else if(strcmp(key_name, annote_name) == 0)
    return(EXACT_MATCH);
  return(FALSE);
}

/* Can be called with either default (unknown) or non-default (known)
   container id and name keys.  Default matches anything.  Non-default
   (know) keys will be used to fill-in default annotations, and check
   annotation consistency. */

/* As a result of "limit LITERAL argument" statements in the
   ddl_hint() xp proc, annotations are added with default (unknown)
   container id and non-default (known) name--passed to ddlhint as
   argv[0].  Later calls to add_annotation() will fill-in this default
   container id. */

ANNOTE *
lookup_annotation (TE *te, int cont_id, char *cont_name)
{
  ANNOTE *x;
  MATCH id, name;

  assert(te != NULL);
  assert_cont_id_valid(cont_id);
  assert_string_nonempty_and_valid(cont_name);

  x = te->annotation;
  if (x == NULL)
    error("lookup_annotation: layer %s: NULL te->annotation,"
          " couldn't find annotation for container id %s and name %s",
          te->layer_name, cont_id_string(cont_id), cont_name);

  while (1) {
    assert_cont_id_valid(x->cont_id);
    assert_string_nonempty_and_valid(x->cont_name);
    id = id_match(cont_id, x->cont_id);
    name = name_match(cont_name, x->cont_name);
    if (id && name) {
      /* Both container id and container name match.
         If one is an exact match and the other a default match, then
         use the non-default key to fill-in the default annotation. */
      if (id == EXACT_MATCH && name == DEFAULT_ANNOTE_MATCH)
        x->cont_name = cont_name;
      if (id == DEFAULT_ANNOTE_MATCH && name == EXACT_MATCH)
        x->cont_id = cont_id;
      return(x);
    }

    /* Only one of container id and container name match.
       If one is an exact match, and the other is not a match (not even
       a default match), then indicate annotation consistency error. */
    else if (id == EXACT_MATCH && !name)
      error("lookup_annotation: layer %s: container name %s and %s mismatch",
            te->layer_name, cont_name, x->cont_name);
    else if (!id && name == EXACT_MATCH)
      error("lookup_annotation: layer %s: container id %d and %d mismatch",
            te->layer_name, cont_id, x->cont_id);

    /* Next annotation. */
    else {
      x = x->next;
      if (x == NULL)
        error("lookup_annotation: layer %s: NULL annotation->next,"
              " couldn't find annotation for container id %s and name %s",
              te->layer_name, cont_id_string(cont_id), cont_name);
    }
  }
}

