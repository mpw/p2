/* $Id: field.h,v 45.0 1997/09/19 05:46:58 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Cursor and Container field declarations. */

#ifndef INCLUDE_FIELD_H
#define INCLUDE_FIELD_H

#include "util.h"   /* BOOLEAN */

/************************************************************************/
/*              Function Prototypes.                                    */
/************************************************************************/

void    add_new_cursor_field(char *s);
BOOLEAN is_basic_cursor_field(char *s);
BOOLEAN is_basic_container_field(char *s);
BOOLEAN is_cursor_field(char *s);

#endif /* INCLUDE_FIELD_H */
