/* $Id: call-down.h,v 45.0 1997/09/19 05:45:43 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Call down declarations. */

#ifndef INCLUDE_CALL_DOWN_H
#define INCLUDE_CALL_DOWN_H

#include "op-tab.h" /* L_VERBATIM_OP */
#include "type.h"   /* NODE_FUNC */
#include "xform.h"  /* TE */

/************************************************************************/
/*              Macros.                                                 */
/************************************************************************/

#define CASCADE_OP(layer)  (!(layer == L_VERBATIM_OP))

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

NODE      *call_down(TE *te, int chimney, int opnum, int num_arg, ...);
NODE      *call_level(TE *te, int opnum, int num_arg, ...);
NODE_FUNC cascade_op(TE **cascade_te, int opnum);

#endif /* INCLUDE_CALL_DOWN_H */
