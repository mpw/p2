/* $Id: xmalloc.c,v 45.1 1997/09/19 07:44:54 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Error-checked malloc() and free() definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>   /* fprintf() */
#include <stdlib.h>  /* size_t */
#include <string.h>  /* memset() */

#include "error.h"   /* assertion_failed() */
#include "lex.h"     /* MAX_IDENT_LEN */
#include "xmalloc.h" /* XMALLOC_STATS */

/*****************************************************************************/
/*                  Definitions.                                             */
/*****************************************************************************/

/* These definitions are malloc package specific. */

/* Define MALLOC and FREE */

#if USE_DB_MALLOC_PACKAGE || USE_UNIX_MALLOC_PACKAGE

#if USE_DB_MALLOC_PACKAGE

/* DB malloc */
/* Special case. */

#define USE_MALLOC_PACKAGE "DB"
#include "../dbmalloc/malloc.h"

#else

/* UNIX malloc */
/* Special case. */

#define USE_MALLOC_PACKAGE "UNIX"
#include <malloc.h>

#endif /* USE_DB_MALLOC_PACKAGE */

#define MALLOC        malloc
#define MALLOC_ATOMIC malloc
#define FREE          free

#else

/* GC malloc */
/* Default. */

#ifndef NDEBUG
#ifndef GC_DEBUG
#define GC_DEBUG
#endif
#endif /* NDEBUG */

#define USE_MALLOC_PACKAGE "GC"
#include "../gc/gc.h"

#define MALLOC        GC_MALLOC
#define MALLOC_ATOMIC GC_MALLOC_ATOMIC
#define FREE          GC_FREE

#endif /* USE_DB_MALLOC_PACKAGE || USE_UNIX_MALLOC_PACKAGE */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

#if XMALLOC_STATS

static int xmalloc_objects = 0;
static int xmalloc_atomic_objects = 0;
static int xfree_objects = 0;

static size_t xmalloc_bytes = 0;
static size_t xmalloc_atomic_bytes = 0;

#endif

/*****************************************************************************/
/*                  xmalloc() and xfree().                                   */
/*****************************************************************************/

/* Error-checked malloc() and free(). */

char *
#if XMALLOC_DEBUG
xmalloc1 (size_t size, const char *comment_string)
#else
xmalloc1 (size_t size)
#endif
{
  char *x = MALLOC(size);

#if XMALLOC_DEBUG
  {
    char s[MAX_IDENT_LEN+10];
    sprintf(s, "%s %d\n", comment_string, size);
    fputs(s, stderr);
  }
#endif
#ifndef NDEBUG
  if (x == 0)
    assertion_failed("out of memory");
  /* Fill the newly allocated memory with garbage. */
  memset((void *) x, 0xF0, size);
#endif
#if XMALLOC_STATS
  xmalloc_objects++;
  xmalloc_bytes += size;
#endif

  return(x);
}

/* Allocate an object that is guaranteed not to contain any pointers. */
/* Allocating an object as atomic is a performance hint for the
   garbage collector, because the garbage collector does not have to
   scan these objects for pointers. (JAT) */

char *
xmalloc_atomic1 (size_t size)
{
  char *x = MALLOC_ATOMIC(size);

#ifndef NDEBUG
  if (x == 0)
    assertion_failed("out of memory");
#endif
#if XMALLOC_STATS
  xmalloc_atomic_objects++;
  xmalloc_atomic_bytes += size;
#endif

  return(x);
}

void
xfree (void *ptr)
{
#ifndef NDEBUG
  if (ptr == NULL)
    assertion_failed("NULL pointer passed to xfree");
#endif
#if XMALLOC_STATS
  xfree_objects++;
#endif
  FREE(ptr);
}

/*****************************************************************************/
/*                  xmalloc statistics report.                               */
/*****************************************************************************/

#if XMALLOC_STATS
void
xmalloc_stats_report (void)
{
  int x = xmalloc_objects + xmalloc_atomic_objects;

  fprintf(stderr, "\n");
  fprintf(stderr, "%s malloc\n", USE_MALLOC_PACKAGE);
  fprintf(stderr, "xmalloc objects: %d + %d = %d - %d = %d\n",
          xmalloc_objects, xmalloc_atomic_objects, x,
          xfree_objects, x - xfree_objects);
  fprintf(stderr, "xmalloc bytes: %ld + %ld = %ld\n",
          (long) xmalloc_bytes, (long) xmalloc_atomic_bytes,
          (long) xmalloc_bytes + xmalloc_atomic_bytes);
}
#endif
