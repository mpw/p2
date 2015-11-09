/* $Id: pb-actions.h,v 45.0 1997/09/19 05:45:51 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* pb parser action declarations. */

#ifndef INCLUDE_PB_ACTIONS_H
#define INCLUDE_PB_ACTIONS_H

#include "arg.h"       /* CURS_ARG */
#include "type.h"      /* NODE, IDENT, IDENT3, ACLASS */
#include "util.h"      /* BOOLEAN */
#include "xform.h"     /* TE */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

/* These defines turn on/off comments in P2 generated .c code. */
/* These comments are useful for debugging, but increase the size
   of the P2 generated .c code, and decrease the speed of P2. (JAT) */

#define PRINT_DECL_AS_COMMENT   0
#define PRINT_CALL_AS_COMMENT   0
#define PRINT_ARGS_AS_COMMENT   0

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

BOOLEAN actual_matches_formal_param(CTYPE *ctype, ACLASS aclass);
void    aggregate_reference_action(NODE *aggregate_name);
NODE    *arrow_member_nonterm(NODE *postfix_expression, NODE *member_name);
void    assert_curs_arg_valid(CURS_ARG *arg);
NODE    *binop_nonterm(NODE *n1, NODE *name, NODE *n2);
IDENT3  *container_declaration_ident3(TE *te, IDENT *ele, char *cont_name);
NODE    *decl_ptree(void);
NODE    *dot_member_nonterm(NODE *postfix_expression, NODE *member_name);
void    ddlhint_declaration(char *cont_name, NODE *path_params,
          char *layer_name_with_quotes, NODE *annotation_params);
NODE    *declarator_nonterm(NODE *declarator);
NODE    *element_nonterm(NODE *type_specifier);
void    enum_reference_action(NODE *enum_name);
NODE    *function_call_nonterm(NODE *postfix_expression,
                               NODE *argument_expression_list);
void    generic_container_declaration(NODE *type_specifier);
void    generic_cursor_declaration(NODE *type_specifier);
NODE    *identifier_expression_nonterm(NODE *n); 
void    left_paren_action(void);
void    named_aggregate_declaration_action(NODE *aggregate_name);
void    named_enum_declaration_action(NODE *enum_name);
void    new_curs_arg(CURS_ARG *arg, NODE *op, int j,
                     NODE *ptree, CTYPE *ctype, int funbody);
NODE    *nth_param(int n, int m, NODE *params);
int     num_params(NODE *params);
NODE    *op_vec_nonterm(CTYPE *ctype, ACLASS aclass);
void    orderby_opt_action(int orderby_direction,
                           char *orderby_cursor, char *orderby_field);
NODE    *param_to_params(int n, NODE *param[]);
NODE    *post_cast_expression_action(NODE *type_name, NODE *cast_expression);
void    post_ddlhint_container_declaration(char *typex_name);
void    post_ddlhint_schema_declaration(char *schema_name, char *typex_name);
void    post_function_definition_action(void);
void    post_opt_cursor_declaration(NODE *unary_expression);
void    post_typex_schema_declaration(char *typex_name);
void    pre_cast_expression_action(void);
void    pre_function_definition_action(void);
void    pre_opt_cursor_declaration(NODE *unary_expression);
void    pre_typex_container_declaration(NODE *type_specifier);
void    pre_typex_schema_declaration(void);
void    predicate_opt_declaration(char *s);
void    right_paren_action(void);
void    schema_container_declaration(NODE *type_specifier);
NODE    *special_op_nonterm(NODE *op, NODE *arg);
NODE    *special_op_nonterm1(NODE *op, NODE *param[], int m, int i, TE *te);
NODE    *special_op_nonterm_comments(NODE *op, NODE *param[], int m, int i,
                                     void *arg[], NODE *xformed_ptree);
void    set_container_cctype_te(CCTYPE *cctype, TE *te);
void    typex_declaration(NODE *params);
TE      *typex_name_to_te(char *typex_name);
NODE    *unary_operator_cast_expression_nonterm(NODE *unary_operator,
                                                NODE *cast_expression);
void    unnamed_aggregate_declaration_action(void);
void    unnamed_enum_declaration_action(void);
void    unnamed_schema_declaration(void);
NODE    *verbatim_nonterm(CTYPE *ctype, ACLASS aclass);
NODE    *string_literal_list_action ( NODE *n1, NODE *n2 );

#endif /* INCLUDE_PB_ACTIONS_H */
