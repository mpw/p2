/* $Id: pb-io.h,v 45.0 1997/09/19 05:45:55 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Input/Output declarations. */

#ifndef INCLUDE_PB_IO_H
#define INCLUDE_PB_IO_H

#include <stdlib.h>     /* size_t */

#include "op-tab.h"    /* RCLASS */
#include "type.h"      /* ACLASS, IDENT */
#include "util.h"      /* BOOLEAN */

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

char    *aclass_string(ACLASS aclass);
char    *direction_string(int direction);
char    *pclass_string(PCLASS c, IDENT *i);
char    *rclass_enum_const_string(RCLASS rclass);
char    *sclass_string(SCLASS sclass);
void    sprint_decl(char *s, IDENT *i);
void    sprint_decl1(char *s, size_t *len, IDENT *i, BOOLEAN print_semicolon);

#endif /* INCLUDE_PB_IO_H */
