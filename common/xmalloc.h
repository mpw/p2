/* $Id: xmalloc.h,v 45.0 1997/09/19 05:40:58 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Error-checked malloc() and free() definitions. */

#ifndef INCLUDE_XMALLOC_H
#define INCLUDE_XMALLOC_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdlib.h> /* size_t */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

/* Keep xmalloc statistics. */
#define XMALLOC_STATS 0

/* Print xmalloc comment_string to stderr. */
#define XMALLOC_DEBUG 0

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

#if XMALLOC_DEBUG
#define xmalloc(x) xmalloc1(x, #x)
#define xmalloc_object(x) (x *) xmalloc1(sizeof(x), #x)
#else
#define xmalloc(x) xmalloc1(x)
#define xmalloc_object(x) (x *) xmalloc1(sizeof(x))
#endif

#define xmalloc_atomic(x) xmalloc_atomic1(x)

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

#if XMALLOC_DEBUG
char    *xmalloc1(size_t size, char *comment_string);
#else
char    *xmalloc1(size_t size);
#endif

char    *xmalloc_atomic1(size_t size);
void    xfree(void *ptr);

#if XMALLOC_STATS
void    xmalloc_stats_report(void);
#endif

#endif /* INCLUDE_XMALLOC_H */
