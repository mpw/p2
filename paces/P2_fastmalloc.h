/* $Id: P2_fastmalloc.h,v 45.0 1997/09/19 05:42:33 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_FASTMALLOC_H
#define INCLUDE_P2_FASTMALLOC_H

void P2_init_fastmalloc(void);
void *P2_fastmalloc(int size);
void P2_freeall(void);
void *P2_get_avail(void **list, int size);
void P2_put_avail(void **list, void *ptr);

#define P2_GETSPACE(avail, type) \
        (type*) P2_get_avail((void**)&avail, sizeof(type));

#define P2_PUTSPACE(avail, ptr) \
        P2_put_avail((void**)&avail, (void*)ptr)

#endif /* INCLUDE_P2_FASTMALLOC_H */
