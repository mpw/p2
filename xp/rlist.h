/* $Id: rlist.h,v 45.0 1997/09/19 05:47:00 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* RLIST declarations. */

#ifndef INCLUDE_RLIST_H
#define INCLUDE_RLIST_H

#include <stdio.h>  /* FILE */

#include "lex.h"    /* MAX_IDENT_LEN */
#include "op-tab.h" /* RCLASS */
#include "util.h"   /* BOOLEAN */

/************************************************************************/
/*              Global structs                                          */
/************************************************************************/

typedef struct rlist_struct {
   int type;
   struct rlist_struct *next;         
} RLIST;

/************************************************************************/
/*              External declarations.                                  */
/************************************************************************/

extern char    layer_name[MAX_IDENT_LEN];
extern RCLASS  layer_realm;
extern int     max_special_op;
extern int     min_special_op;
extern RLIST   *params_rlist;
extern int     path[];

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

BOOLEAN call_below(SPECIAL_OP op, int param);
int     count_params(RLIST *i);
RLIST   *new_rlist_node(int i);
int     op_exists_in_realm(int operation, RCLASS realm);
void    print_realm_list(FILE *fp, RLIST *i);
char    *rclass_str(RCLASS rclass);
RLIST   *tackon_rlist_node(RLIST *l, RLIST *n);

#endif /* INCLUDE_RLIST_H */
