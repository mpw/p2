/* $Id: util.h,v 45.0 1997/09/19 05:40:56 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Declarations that are used everywhere and don't belong anywhere else. */

#ifndef INCLUDE_UTIL_H
#define INCLUDE_UTIL_H

/*****************************************************************************/
/*                  Macros.                                                  */
/*****************************************************************************/

/* The P2_ prefix is not necessary here, but I choose to use it in order
   to avoid possible conflicts (with, for example, C  pre-processsor
   symbols in system header files). (JAT) */
#define P2_MIN(x1,x2) (((x1) < (x2))? (x1) : (x2))
#define P2_MAX(x1,x2) (((x1) > (x2))? (x1) : (x2))

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Boolean. */
/* Define FALSE, TRUE, and BOOLEAN if not already defined (eg by AIX) */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef BOOLEAN
#define BOOLEAN int
#endif

/* Function pointers (for the declaration syntax challenged) */

typedef void     (*VOID_FUNC)();
typedef int      (*INT_FUNC)();
typedef unsigned (*UNSIGNED_FUNC)();
typedef short    (*SHORT_FUNC)();
typedef BOOLEAN  (*BOOL_FUNC)();

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    machine_setup( void );

#endif /* INCLUDE_UTIL_H */
