/* $Id: field.c,v 45.0 1997/09/19 05:46:58 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Cursor and Container field definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>      /* strcpy() */

#include "error.h"       /* error() */
#include "util.h"        /* BOOLEAN */

/************************************************************************/
/*              Local variables.                                        */
/************************************************************************/

/* We should re-write all of this stuff to use the normal symbol table
   handling functionality, eg add_ident_to_symlist() and symlist_lookup()
   (JAT) */

/* We could define MAX_FIELD_NAME_LEN to be something smaller than
   MAX_IDENT_LEN (note that all of the basic field names are much
   shorter than MAX_FIELD_NAME_LEN), but (1) the memory savings would
   be minimal, and (2) memory savings would come at the cost of
   confusion for the user due to the special case: the maximum length
   of an identifier is MAX_FIELD_NAME_LEN, unless the identifier is an
   xp generated field name. (JAT) */

#define MAX_FIELD_NAME_LEN MAX_IDENT_LEN
typedef char FIELD_NAME[MAX_FIELD_NAME_LEN];

/* If you change these, don't forget to also change:
   (1) MAX_xxx_FIELDS and NUM_BASIC_xxx_FIELDS (in this file)
   (2) init_cursor_def() and init_container_def (in pb/pb-type.c)
   (3) P2_basic_cursor (in P2.h)
*/

#define MAX_CURSOR_FIELDS 10
#define NUM_BASIC_CURSOR_FIELDS 5
static num_cursor_fields = NUM_BASIC_CURSOR_FIELDS;
static FIELD_NAME cursor_fields[MAX_CURSOR_FIELDS] = {
  "obj",         /* pointer to element */
  "con",         /* generic (pointer to container) */
  "op_vec",      /* generic (pointer to operation vector) */
  "restore",     /* deletion */
  "inbetween"    /* deletion (does cursor point a deleted object?) */
};

#define MAX_CONTAINER_FIELDS 2
#define NUM_BASIC_CONTAINER_FIELDS 2
static FIELD_NAME container_fields[MAX_CONTAINER_FIELDS] = {
  "initialized", /* has continer been initialized? */
  "op_vec"       /* generic (pointer to operation vector) */
};

/************************************************************************/
/*              Add new cursor field.                                   */
/************************************************************************/

/* Add s to the list of basic cursor fields. */

void
add_new_cursor_field (char *s)
{
  /* Check for errors. */

  if (num_cursor_fields >= MAX_CURSOR_FIELDS)
    error("exceeded maximum number of cursor fields = %d", MAX_CURSOR_FIELDS);
  else if (strlen(s) > MAX_FIELD_NAME_LEN)
    error("field name %s too long, max len = %d chars", s, MAX_FIELD_NAME_LEN);
  else {
    int i;
    for (i = 0; i < num_cursor_fields; i++)
      if (strcmp(cursor_fields[i], s) == 0)
        error("field %s already exists", s);

    /* Add field. */

    strcpy(cursor_fields[num_cursor_fields], s);
    num_cursor_fields++;
  }
}

/************************************************************************/
/*              Is field predicates.                                    */
/************************************************************************/

/* Return true if s is the name of a global cursor field (i.e., a
   field that belongs to a cursor that is shared by all layers) or if s
   is a name of a field that was added by the xform procedure. */

BOOLEAN
is_cursor_field (char *s)
{
  FIELD_NAME *p = cursor_fields;

  while (strcmp(*p,"") != 0) {
    if (strcmp(*p,s) == 0)
      return(TRUE);
    p++;
  }
  return(FALSE);
}

/* Returns true if a global field of a cursor is referenced. */

BOOLEAN
is_basic_cursor_field (char *s)
{
  int k;
  FIELD_NAME *p = cursor_fields;
    
  for (k = 1; k <= NUM_BASIC_CURSOR_FIELDS ; k++) {
    if (strcmp(*p++,s) == 0)
      return(TRUE);
  }
  return(FALSE);
}

/* Returns true if a global field of a container is referenced. */
 
BOOLEAN
is_basic_container_field (char *s)
{
  int k; 
  FIELD_NAME *p = container_fields;
    
  for (k = 1; k <= NUM_BASIC_CONTAINER_FIELDS ; k++) {
    if (strcmp(*p++,s) == 0)
      return(TRUE);
  }
  return(FALSE);
}

