/* $Id: adhoc-arg.h,v 45.0 1997/09/19 05:46:58 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* ADHOC_ARG declarations. */

#ifndef INCLUDE_ADHOC_ARG_H
#define INCLUDE_ADHOC_ARG_H

#include "lex.h" /* MAX_IDENT_LEN */

/************************************************************************/
/*              Global structs                                          */
/************************************************************************/

typedef struct adhoc_arg_struct {
    char name[MAX_IDENT_LEN];
    struct adhoc_arg_struct *next;
} ADHOC_ARG;

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

extern ADHOC_ARG *adhoc_arg; /* List of arguments for adhocs. */

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

ADHOC_ARG *append_arg(ADHOC_ARG *l, char *name);
void verify_args(ADHOC_ARG *l, char *name);

#endif INCLUDE_ADHOC_ARG_H
