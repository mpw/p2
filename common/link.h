/* $Id: link.h,v 45.0 1997/09/19 05:40:49 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* link declarations */

#ifndef INCLUDE_LINK_H
#define INCLUDE_LINK_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "type.h" /* ERR */

/*****************************************************************************/
/*                  Typedefs                                                 */
/*****************************************************************************/

typedef enum {
  NONE = ERR+1,
  PARENT,
  CHILD,
  BOTH
} LINKTYPE;

/*****************************************************************************/
/*                  Function prototypes                                      */
/*****************************************************************************/

void    linkpartition(const char *linkpredicate,
                      char *parentres, char *childres, char *rest);

#endif /* INCLUDE_LINK_H */
