/* $Id: annotation.h,v 45.0 1997/09/19 05:45:42 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* Annotation declarations. */

#ifndef INCLUDE_ANNOTATION_H
#define INCLUDE_ANNOTATION_H

#include "xform.h"        /* ANNOTE, TE */

/************************************************************************/
/*              Typedefs.                                               */
/************************************************************************/

typedef enum {
  DEFAULT_MATCH = 1,
  DEFAULT_ANNOTE_MATCH,
  DEFAULT_KEY_MATCH,
  EXACT_MATCH
} MATCH;

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    add_annotation(TE *te, int size, int cont_id, char *cont_name);
MATCH   id_match(int key_id, int annote_id);
MATCH   name_match(const char *key_name, char *annote_name);
ANNOTE  *lookup_annotation(TE *te, int cont_id, char *cont_name);

#endif /* INCLUDE_ANNOTATION_H */
