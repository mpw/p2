/* $Id: mmap.h,v 45.0 1997/09/19 05:40:50 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* mmap() includes. */
/* Both x/mmap.xp1 and paces/P2_mmap.c #include this file. (JAT) */

#ifndef INCLUDE_MMAP_H
#define INCLUDE_MMAP_H

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

/* Avoid powers of 2, e.g. 32 (JAT) */
/* Use paces/hash0[45].p2 to see if this number is high enough. */
#define MAX_MMAP_FILE 47 /* Maximum mmap files. */

#endif /* INCLUDE_MMAP_H */
