/* $Id: seen.h,v 45.0 1997/09/19 05:47:01 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* seen declarations. */

#ifndef INCLUDE_SEEN_H
#define INCLUDE_SEEN_H

#include <stdio.h>  /* FILE */

#include "op-tab.h" /* RCLASS */
#include "rlist.h"  /* RLIST */
#include "util.h"   /* BOOLEAN */

/************************************************************************/
/*              External declarations.                                  */
/************************************************************************/

extern BOOLEAN seen[MAX_NUM_OPS+1];

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    have_all_operations_been_seen(void);
void    layer_stmt_seen(RCLASS realm, char *name, RLIST *rlist);
void    operation_seen(SPECIAL_OP op);

#endif /* INCLUDE_SEEN_H */
