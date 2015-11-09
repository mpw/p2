/* $Id: gen-layerdef.h,v 45.0 1997/09/19 05:46:59 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* gen_layerdef() declarations. */

#ifndef INCLUDE_GEN_LAYERDEF_H
#define INCLUDE_GEN_LAYERDEF_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "util.h" /* BOOLEAN */

/*****************************************************************************/
/*                  Global variables.                                        */
/*****************************************************************************/

extern int     annotations;
extern BOOLEAN stable;
extern BOOLEAN d2u;
extern BOOLEAN indirect_only;
extern int     retrieval;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    gen_layerdef(void);

#endif /* INCLUDE_GEN_LAYERDEF_H */
