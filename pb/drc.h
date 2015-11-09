/* $Id: drc.h,v 45.0 1997/09/19 05:45:48 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

#ifndef INCLUDE_DRC_H
#define INCLUDE_DRC_H

#include "xform.h" /* TE */

/************************************************************************/
/*              Variables.                                              */
/************************************************************************/

extern char attr_file_name[MAX_IDENT_LEN]; /* Attribute file name. */

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void drc(TE *t, char *te_name);
void init_drc(void);

#endif /* INCLUDE_DRC_H */
