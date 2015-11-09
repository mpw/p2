/* $Id: P2_fastmalloc.c,v 45.0 1997/09/19 05:42:32 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include "P2_fastmalloc.h"

#define BLOCKSIZE  2048 /* size of allocated blocks */

typedef struct blk {
  struct blk  *next;              /* chain of allocated blocks */
  char        block[BLOCKSIZE];   /* actual space */
} BLOCK;

static BLOCK  head;                /* first block already allocated */
static char   *nextfree;            /* next free character */
static int    freeleft;            /* number of free bytes left */
static int    blocks_allocated;    /* number of blocks allocated */

void
P2_init_fastmalloc (void)
{
  head.next = 0;
  nextfree = &head.block[0];  
  freeleft = BLOCKSIZE;    
  blocks_allocated = 0;
}

void *
P2_fastmalloc (int size) 
{
  BLOCK *b;
  char      *r;

  /* round size up to nearest word */

  if (size & 03) {
    size = size + 4;
    size = size & (~03);
  }

  if (freeleft < size) {
    b = (BLOCK *) malloc(sizeof(struct blk));
    if (b==0) {
      fprintf(stderr, "OUT OF MEMORY\n");
      abort();
    }
    b->next   = head.next;
    head.next = b;
    nextfree  = &b->block[0];
    freeleft  = BLOCKSIZE;
    blocks_allocated++;
  }
  freeleft -= size;
  r = nextfree;
  nextfree += size;
  return (void *) r;
}

void
P2_freeall (void)
{
  BLOCK *b;
  BLOCK *n;

  for (b = head.next ; b ; b = n) {
    n = b->next;
    free(b);
  }
  P2_init_fastmalloc();
}

void *
P2_get_avail(void **list, int size)
{
  void *r;
  
  if (*list) {
    r = *list;
    *list = *(void **)r;
    return r;
  }
  return P2_fastmalloc(size);
}

void
P2_put_avail(void **list, void *ptr)
{
  *(void**)ptr = *list;
  *list = ptr;
}

#if 0
/* For debugging only. (DSB) */

typedef struct {
  int a[500];
} BIG;

BIG **avail = 0;

main ()
{
  int i;
  BIG *b;

  P2_init_fastmalloc();
  for (i = 1; i < 50 ; i++)
  {
    b = (BIG *) P2_GETSPACE(avail, BIG);
    P2_PUTSPACE(avail,b);
  }
  printf("blocks allocated %d\n", blocks_allocated);
  P2_freeall();
}

#endif   
