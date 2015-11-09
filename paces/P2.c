/* $Id: P2.c,v 45.2 1997/09/22 01:51:04 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Analogous to pb/data-type.c */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if 1
#include <limits.h> /* WORD_BIT */
#include <stdarg.h> /* va_list, va_start(), va_end() */
#include <stdio.h>  /* fprintf() */
#endif

short
P2_str_hashcmp (const char *str)
{
  int a = 0;
  short *s = (short *) str;

   while (!(*(char *)(s) == '\0' || *((char *)(s) + 1) == '\0'))
      a +=  *s++;
   a += *(char *) s;
   return(0x377 & a);
}

unsigned
P2_int_hash (int i, int size)
{
  return(abs(i*59) % size);
}

unsigned
P2_str_hash (const char *str, int size)
{
  unsigned hash = 0;
#if 0
  /* Assuming characters have 7 significant bits, set max_shift equal
     to the number of bits that we can shift characters to the left
     (i.e. multiply by 2^max_shift) so that the shifted value will fit
     into an unsigned word. (JAT) */
  int max_shift = WORD_BIT - 7;
  int shift = 0;

  if (max_shift < 0)
    max_shift = 0;

  while (*str)
  {
    hash = hash ^ (((unsigned int) *str) << shift);
    str++;
    if (shift == max_shift)
      shift = 0;
    else
      shift++;
  }
#elif 1
  /* Found this hash function on the web.  Works okay on both random
     words and numeric strings (JAT) */
  while (*str)
  {
    hash = hash << 1 ^ (*str);
    str++;
  }
#else
  /* Found at http://www.teb.upm.es/~jantonio/sfl/sfl155.htm#TOC169
     Calculates a 32-bit hash value for the string. The string must
     end in a null. To use the result as a hash key, take the modulo
     over the hash table size. The algorithm was designed by Peter
     Weinberger. This version was adapted from Dr Dobb's Journal April
     1996 page 26, http://www.ddj.com/ftp/1996/1996.04/hash.zip
     Works okay on both random words and numeric strings. (JAT) */
  /* Right shift one eighth */
  unsigned high_bits = ( ~((unsigned)(~0) >> 4 ));
  while (*str)
  {
    /* Left shift one eighth. */
    hash = (hash << 4) + *str;
    str++;
    if ((high_bits = hash & high_bits) != 0)
      /* Right shift three quarters */
      hash ^= high_bits >> 24;
    hash &= ~high_bits;
  }
#endif
  return(hash % size);
}

int
intcmp (int i1, int i2)
{
  return(i1 - i2);
}

/* Warnings. */

void
P2_runtime_warning (const char *format, ...)
{
  va_list args;
  fprintf(stderr, "P2 runtime warning: ");
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fprintf(stderr, "\n");
}

void
P2_runtime_pwarning (const char *format, ...)
{
  va_list args;
  fprintf(stderr, "P2 runtime pwarning: ");
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  perror(" ");
}

/* Fatal Errors. */

int
P2_runtime_error (const char *format, ...)
{
  va_list args;
  fprintf(stderr, "P2 runtime error: ");
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fprintf(stderr, "\n");
  exit(1);
}

int
P2_runtime_perror (const char *format, ...)
{
  va_list args;
  fprintf(stderr, "P2 runtime perror: ");
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  perror(" ");
  exit(1);
}
