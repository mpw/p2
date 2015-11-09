/* $Id: pb-xform.h,v 45.0 1997/09/19 05:46:01 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* Type expression transformation declarations. */

#ifndef INCLUDE_PB_XFORM_H
#define INCLUDE_PB_XFORM_H

#include "type.h"      /* IDENT, CTYPE */
#include "util.h"      /* BOOLEAN */
#include "xform.h"     /* TE */

/************************************************************************/
/*              Macros.                                                 */
/************************************************************************/

#define FOREACH_MEMBER(P2_mcurs) \
  for (mcursor_res(P2_mcurs); mcursor_eof(P2_mcurs); mcursor_adv(P2_mcurs))

/************************************************************************/
/*              Typedefs.                                               */
/************************************************************************/

typedef struct {
   IDENT  *ident;   /* Pointer to structure */
   SYMLIST *home;   /* Pointer to first entry of memberlist */
   ENTRY  *pos;     /* Pointer to current member of memberlist */
} MCURSOR;

/************************************************************************/
/*              function prototypes                                     */
/************************************************************************/

void     copy_member(IDENT *ident, MCURSOR *mcurs);
CTYPE    *ctype_of(MCURSOR *mcurs);
void     init_mcursor (MCURSOR *mcurs, IDENT *i);
BOOLEAN  is_member_of(IDENT *s, char *f);
KC_STATE *lookup_kc_state(TE *te, int id, char *expr, BOOLEAN c);
IDENT    *lookup_struct(char *name);
void     mcursor_adv(MCURSOR *mcurs);
BOOLEAN  mcursor_eof(MCURSOR *mcurs);
void     mcursor_res(MCURSOR *mcurs);
SYMLIST  *members_of(MCURSOR *mcurs);
char     *name_of(MCURSOR *mcurs);
KC_STATE *new_kc_state(TE *te, int size, int id, BOOLEAN c);
IDENT    *new_struct(char *name, BOOLEAN add_to_symtab);
MCURSOR  *new_mcursor(IDENT *i);
IDENT    *new_member(TE *texp, IDENT *str, char *name,
                     CTYPE *ctype, IDENT *ident);
void     position_member(MCURSOR *mcurs, char *field);
void     print_fields(IDENT *i);
char     *type_of(MCURSOR *mcurs);

#endif /* INCLUDE_PB_XFORM_H */
