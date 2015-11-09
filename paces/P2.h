/* $Id: P2.h,v 45.2 1997/09/22 01:51:08 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_H
#define INCLUDE_P2_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

/* P2 will automatically #include this file in every file.  Thus, we
   want to #include as few additional files as possible in this file.
   We don't want to include P2_paces.h, which defines BOOLEAN, so
   we'll use int instead. (JAT) */

#include <stddef.h>    /* offsetof() in x/part.xp */
#include <stdio.h>     /* sprintf() in x/mmap.xp1 */

/*****************************************************************************/
/*                  Data-type (i.e., int or str) specific.                   */
/*****************************************************************************/

/* Unfortunately, all of these symbols are user visible. (JAT) */

#define int_EQ(a,b) a == b
#define int_LE(a,b) a <= b
#define int_LT(a,b) a < b
#define int_GT(a,b) a > b
#define int_GE(a,b) a >= b
#define int_NE(a,b) a != b
#define int_TRUE(a,b)  1
#define int_FALSE(a,b) 0
#define int_CPY(a,b) a = b

#define str_EQ(a,b) strcmp(a,b) == 0
#define str_LE(a,b) strcmp(a,b) <= 0
#define str_LT(a,b) strcmp(a,b) < 0
#define str_GT(a,b) strcmp(a,b) > 0
#define str_GE(a,b) strcmp(a,b) >= 0
#define str_NE(a,b) strcmp(a,b) != 0
#define str_TRUE(a,b)  1
#define str_FALSE(a,b) 0
#define str_CPY(a,b) strcpy(a,b)

#if 1
typedef char str[];
#else
typedef char *str;
#endif

int intcmp(int i1, int i2);
int strcmp(const char *s1, const char *s2);
short P2_str_hashcmp(char *str);
unsigned P2_int_hash(int i, int size);
unsigned P2_str_hash(const char *str, int size);

/*****************************************************************************/
/*                  Definitions.                                             */
/*****************************************************************************/

typedef int (*P2_op_vec_func)();

/* May be "void *" or "int *" on different machines (BJG). */

typedef int *vptr;

/* Cursor with all the basic fields. */

typedef struct {
  void *obj;
  void *con;
  int (**op_vec) ();
  void *restore;
  int inbetween;
} P2_BASIC_CURSOR;

/* offsetof and size_t should be defined in <stddef.h> (JAT) */
#ifndef offsetof
#define offsetof(type,member) ((size_t)&((type *)0)->member)
#endif

/*****************************************************************************/
/*                  Prototypes.                                              */
/*****************************************************************************/

/* Return int in case these routines appear in an expression. (JAT) */

/* Warning. */
int P2_runtime_warning(const char *format, ...);
int P2_runtime_pwarning(const char *format, ...);

/* Fatal Errors. */
int P2_runtime_error(const char *format, ...);
int P2_runtime_perror(const char *format, ...);

#endif /* INCLUDE_P2_H */
