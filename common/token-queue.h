/* $Id: token-queue.h,v 45.0 1997/09/19 05:40:53 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Token queue definitions. */

#ifndef INCLUDE_TOKEN_QUEUE_H
#define INCLUDE_TOKEN_QUEUE_H

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    add_token_queue(const char *s, int len);
void    print_token_queue(void);

#endif /* INCLUDE_TOKEN_QUEUE_H */
