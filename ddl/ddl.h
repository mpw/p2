/* $Id: ddl.h,v 45.0 1997/09/19 05:41:01 jthomas Exp $ */

/* ddl declarations. */

#ifndef INCLUDE_DDL_H
#define INCLUDE_DDL_H

#include "lex.h" /* MAX_IDENT_LEN */

/* Text list node. */

/************************************************************************/
/*              Typedefs.                                               */
/************************************************************************/

typedef struct listnode_struct {
   struct listnode_struct *next;
   char                   text[MAX_IDENT_LEN];
} LISTNODE;

/************************************************************************/
/*              Extern declarations.                                    */
/************************************************************************/

extern char     target_layer[];                /* from ddl.c */

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

LISTNODE *decompose_conceptual(LISTNODE *param_list);
void     new_equation(char *name, LISTNODE *e);
LISTNODE *new_list(char *s, LISTNODE *l);
LISTNODE *new_list_head(LISTNODE *h, LISTNODE *l);
LISTNODE *new_list_tail(LISTNODE *l, LISTNODE *n);
LISTNODE *new_node(char *s);
void     print_expr(LISTNODE *p);
void     print_path(LISTNODE *p);
void     print_string_expr(LISTNODE *p);

#endif INCLUDE_DDL_H
