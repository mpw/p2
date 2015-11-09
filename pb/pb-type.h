/* $Id: pb-type.h,v 45.0 1997/09/19 05:46:00 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Type system declarations. */

#ifndef INCLUDE_PB_TYPE_H
#define INCLUDE_PB_TYPE_H

#include "util.h"      /* BOOLEAN */
#include "type.h"      /* CTYPE, NODE, IDENT3, DECL */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define UNNAMED_SUE_NAME "unnamed_sue"
#define GENERIC_TE_NAME  "generic_te"

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    add_ident_to_symlist(SYMLIST **symlist, IDENT *ident);
void    add_ident_to_symlist1(SYMLIST **symlist, IDENT *ident);
void    add_ident_to_symtab(SYMTAB *symtab, IDENT *ident);
void    add_ident_to_symtab1(SYMTAB *symtab, IDENT *ident);
void    add_label_to_symtab(char *name);
void    add_label_to_symtab1(char *name);
void    arithmetic_btype(UCLASS uclass, PCLASS pclass);
void    clear_btype(void);
void    clear_decl(void);
void    clear_dtype(void);
IDENT3  *copy_cursor_ident3(IDENT3 *src, char *predicate);
IDENT   *copy_ident(IDENT *src);
NODE    *copy_ptree(NODE *src);
void    copy_symlist(SYMLIST **dest, SYMLIST *src);
void    init_container_def(IDENT *con);
void    init_cursor_def(IDENT *cur, IDENT *ele, IDENT *con);
void    init_pb_type_system(void);
void    init_schema_def(IDENT *sch);
void    ident_has_expected_ctype(IDENT *ident,
                                 CTYPE *expected_ctype,
                                 char *expected_ctype_name);
BOOLEAN isaTYPE(char *name);
char    *new_container_name(NODE *type_specifier);
OP_LIST *new_op_list(CTYPE *ctype, IDENT *orig_type, ACLASS aclass);
OP_LIST *new_op_list1(CTYPE *ctype, IDENT *orig_type, ACLASS aclass, int id);
char    *new_unnamed_sue_name(void);
DECL    *parent_decl(void);
BOOLEAN op_has_aclass_param(int i, ACLASS aclass);
int     op_list_match(const OP_LIST *op_list, const char *op,
                      const char *field);
void    pop_decl(void);
void    pop_scope(void);
void    ptree_has_expected_ctype(NODE *ptree,
                                 CTYPE *expected_ctype,
                                 char *expected_ctype_name);
void    push_decl(void);
void    push_scope(BOOLEAN resurrect);
void    reduce(CTYPE *c, PCLASS pclass);
void    save_decl(void);
void    set_btype(CTYPE *ctype);
ENTRY   *symlist_lookup(const SYMLIST *symlist, const char *name);
ENTRY   *symtab_lookup(const SYMTAB *symtab, const char *name);
IDENT   *symlist_symbol_has_expected_ctype(SYMLIST *symlist, char *symbol_name,
                                           CTYPE *expected_ctype,
                                           char *expected_ctype_name);
#if 0
IDENT   *symtab_symbol_has_expected_ctype(SYMTAB *symtab, char *symbol_name,
                                          CTYPE *expected_ctype,
                                          char *expected_ctype_name);
#endif
void    unrestore_symtab(void);

#endif /* INCLUDE_PB_TYPE_H */
