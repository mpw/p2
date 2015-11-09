/* $Id: xp-actions.h,v 45.0 1997/09/19 05:47:02 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#ifndef INCLUDE_XP_ACTIONS_H
#define INCLUDE_XP_ACTIONS_H

#include "adhoc-arg.h" /* ADHOC_ARG */
#include "lex.h"       /* MAX_IDENT_LEN */
#include "op-tab.h"    /* SPECIAL_OP */
#include "type.h"      /* CTYPE */
#include "util.h"      /* BOOLEAN */

/************************************************************************/
/*              External declarations.                                  */
/************************************************************************/

extern BOOLEAN cont_state;
extern int     current_op;
extern BOOLEAN curs_state;
extern BOOLEAN cursor_field;
extern char    cdef_name[MAX_IDENT_LEN];
extern BOOLEAN delete_operation;
extern int     enable_hierarchy_comments;
extern char    field_val[MAX_IDENT_LEN];
extern BOOLEAN force_field_ref;
extern BOOLEAN has_container_arg;
extern BOOLEAN has_cursor_arg;
extern BOOLEAN in_ddlhint_proc;
extern BOOLEAN in_defaults;
extern BOOLEAN in_optimize_proc;
extern BOOLEAN in_special_proc;
extern BOOLEAN in_xform_proc;
extern char    index_val[MAX_IDENT_LEN];
extern char    kdef_name[MAX_IDENT_LEN];
extern BOOLEAN know_member_name;
extern CTYPE   *member_ctype;
extern char    member_name[MAX_IDENT_LEN];
extern char    member_type[MAX_IDENT_LEN];
extern BOOLEAN obj_field;
extern BOOLEAN print_local_vars;
extern BOOLEAN print_return;
extern char    rf_field[MAX_IDENT_LEN];
extern BOOLEAN unknown_fld;
extern BOOLEAN unknown_idx;

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    add_ddlhint_annotation(void);
PCLASS  base_type(char *s);
void    ckeyword_action(char *k, char *c, char *h, ...);
void    check_ddlhint_arguments(char *n);
void    clear_member(void);
void    cursor_func_action(char *func_name, char *curs_name,
                           char *opt_literal);
void    container_func_action(char *func_name, char *cont_name,
                              char *opt_literal);
void    def_cursor_func_action(char *dollar_word);
void    def_container_func_action(char *dollar_word);
void    do_action(char *op_name, ...);
void    do_adhoc_action(char *op_name, ADHOC_ARG *arglist);
void    do_dollar(char *dollar_word, char *buffer);
void    identifier_declaration_action(char *identifier_name);
void    ikeyword_action(char *s, char *t, char *x, char *k, char *c, char *h,
                        ...);
void    link_retrieval_layer_header(SPECIAL_OP op, char *op_name, char *params);
void    opcall1(SPECIAL_OP op, char *op_name, char *arg1);
void    opcall2(SPECIAL_OP op, char *op_name, char *arg1, char *arg2);
void    opcall3(SPECIAL_OP op, char *op_name, char *arg1, char *arg2, char *arg3);
void    opcall4(SPECIAL_OP op, char *op_name, char *arg1, char *arg2, char *arg3,
                char *arg4);
void    opcallN(char *op_name, ADHOC_ARG *arglist);
void    opheader(SPECIAL_OP op);
void    print_proc_header(void);
void    print_proc_trailer(void);
void    retrieval_layer_header(SPECIAL_OP op, char *op_name, char *params);
BOOLEAN retrieval_op(int opnum);
void    undefined_operation(char *op_name, int op);
char    *xp_container_id(void);
char    *xp_container_name(void);

#endif /* INCLUDE_XP_ACTIONS_H */
