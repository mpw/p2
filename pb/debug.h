/* $Id: debug.h,v 45.2 1997/09/19 22:14:29 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#include "type.h"  /* CTYPE */

#ifndef NDEBUG

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    print_ctype(CTYPE *c)
void    print_symbols(void);

#endif /* NDEBUG */
#endif /* INCLUDE_DEBUG_H */
