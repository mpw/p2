/* $Id: op-tab.c,v 45.3 1997/09/29 03:48:26 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Operation table definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "op-tab.h" /* OP_DESC, K_VERBATIM_OP */
#include "type.h"   /* CON, CUR */

/*****************************************************************************/
/*                  Globals.                                                 */
/*****************************************************************************/

/* Table describing special operations. */

/* Note that the order in which operations appear in the table (op-tab)
   is important, since operations are proceduralized (op-list) in the
   same order that they appear in this table. (JAT) */

/* STYLE NOTE: I use 1 and 0 rather than TRUE and FALSE in order to
   keep the rows shorter and improve readability. (JAT) */

/* When adding a new special operation foo, remember to add the
   constant "FOO_OP" to common/op-tab.h (BJG), and the appropriate
   code to xp/xp-lex.l.in and xp/xp-gram.y (if foo is NOT an adhoc
   operation) or x/adhoc.xp1 (if foo IS an adhoc operation). (JAT) */

OP_DESC op_tab[] = {

/*                 user
                   |  is_void
                   |  |  expr
                   |  |  |  proceduralize
                   |  |  |  |  verbatim
                   |  |  |  |  |  has_container_arg
                   |  |  |  |  |  |  print_local_vars
                   |  |  |  |  |  |  |  print_return
                   |  |  |  |  |  |  |  |  delete_operation
                   |  |  |  |  |  |  |  |  |  indirect container
                   |  |  |  |  |  |  |  |  |  | */

/* User (aka verbatim) operations. */
/* expr = 1 so that $GENSEMI does not add a semicolon. */

  { "k_verbatim",  0, 0, 1, 0, 1, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    K_VERBATIM_OP, "K_VERBATIM_OP",
    "NODE *k_verbatim_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "c_verbatim",  0, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CUR },
    C_VERBATIM_OP, "C_VERBATIM_OP",
    "NODE *c_verbatim_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "s_verbatim",  0, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    S_VERBATIM_OP, "S_VERBATIM_OP",
    "NODE *s_verbatim_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "l_verbatim",  0, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 0, { ERR },
    L_VERBATIM_OP, "L_VERBATIM_OP",
    "NODE *l_verbatim_%s(TE *te)",
    "0" },

/* TOP realm. */

  { "foreach",     1, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 1, 0, 1, 1 }, 2, { CUR, PAR },
    FOREACH_OP, "FOREACH_OP",
    "NODE *foreach_%s(TE *te, CURS_ARG *cursor0, NODE *expr0)",
    "2, cursor0, expr0" },
  { "rofeach",     1, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 1, 0, 1, 1 }, 2, { CUR, PAR },
    ROFEACH_OP, "ROFEACH_OP",
    "NODE *rofeach_%s(TE *te, CURS_ARG *cursor0, NODE *expr0)",
    "2, cursor0, expr0" },

/* DS and MEM realms. */

  { "checkpoint_cont", 1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    CHECKPOINT_CONT_OP, "CHECKPOINT_CONT_OP",
    "NODE *checkpoint_cont_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "close_cont",  1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    CLOSE_CONT_OP, "CLOSE_CONT_OP",
    "NODE *close_cont_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "ddlhint",     0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { IDE },
    DDLHINT_OP, "DDLHINT_OP",
    "void ddlhint_%s(TE *te, int argc, NODE **argv)",
    "2, argc, argv" },
  { "init_cont",   1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    INIT_CONT_OP, "INIT_CONT_OP",
    "NODE *init_cont_%s(TE *te, CONT_ARG *container0)",
    "1, container0"},
  { "open_cont",   1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    OPEN_CONT_OP, "OPEN_CONT_OP",
    "NODE *open_cont_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "open_cont_number", 1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
    { 1, 1, 1, 1, 1 }, 2, { CON, IN },
    OPEN_CONT_NUMBER_OP, "OPEN_CONT_NUMBER_OP",
    "NODE *open_cont_number_%s(TE *te, CONT_ARG *container0, NODE *expr0)",
    "2, container0, expr0" },
  { "sync_cont",   1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 4, { CON, EXP, EXP, EXP },
    SYNC_CONT_OP, "SYNC_CONT_OP",
    "NODE *sync_cont_%s(TE *te, CONT_ARG *container0,"
    " NODE *expr0, NODE *expr1, NODE *expr2)",
    "4, container0, expr0, expr1, expr2" },
  { "xform",       0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    { 1, 1, 1, 1, 1 }, 3, { IDE, IDE, IDE },
    XFORM_OP, "XFORM_OP",
    "void xform_%s(TE *te, IDENT *element0, IDENT *container0,"
    " IDENT *cursor0, char *P2_cont_name)",
    "3, element0, container0, cursor0" },
  
/* DS realm. */

  { "adv",         1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    ADV_OP, "ADV_OP",
    "NODE *adv_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "delete",      1, 0, 0, 1, 0, 0, 1, 1, 1, 0,
    { 1, 1, 0, 1, 1 }, 1,  { CUR },
    DELETE_OP, "DELETE_OP",
    "NODE *delete_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  /* delete_curs() is used in refrence counting.
     See x/refcount.xp1, included by x/free.xp and x/refcount.xp */
  { "delete_curs", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    DELETE_CURS_OP, "DELETE_CURS_OP",
    "NODE *delete_curs_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "end_adv",     1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    END_ADV_OP, "END_ADV_OP",
    "NODE *end_adv_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "end_rev",     1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    END_REV_OP, "END_REV_OP",
    "NODE *end_rev_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "getrec",      1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, STR },
    GETREC_OP, "GETREC_OP",
    "NODE *getrec_%s(TE *te, CURS_ARG *cursor0, REC_ARG *record)",
    "2, cursor0, record" },
  { "init_curs",   1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    INIT_CURS_OP, "INIT_CURS_OP",
    "NODE *init_curs_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "insert",      1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, STR },
    INSERT_OP, "INSERT_OP",
    "NODE *insert_%s(TE *te, CURS_ARG *cursor0, REC_ARG *record)",
    "2, cursor0, record" },
  { "varinsert",   1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 3, { CUR, STR, IN },
    VARINSERT_OP, "VARINSERT_OP",
    "NODE *varinsert_%s(TE *te, CURS_ARG *cursor0, REC_ARG *record, NODE *expr0)",
    "3, cursor0, record, expr0" },
  { "overflow",    1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { CON },
    OVERFLOW_OP, "OVERFLOW_OP",
    "NODE *overflow_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "varoverflow", 1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 2, { CON, IN },
    VAROVERFLOW_OP, "VAROVERFLOW_OP",
    "NODE *varoverflow_%s(TE *te, CONT_ARG *container0, NODE *expr0)",
    "2, container0, expr0" },
  { "optimize",    0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    OPTIMIZE_OP, "OPTIMIZE_OP",
    "void optimize_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "pos",         1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, EXP },
    POS_OP, "POS_OP",
    "NODE *pos_%s(TE *te, CURS_ARG *cursor0, NODE *expr0)",
    "2, cursor0, expr0" },
  { "query",       1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    QUERY_OP, "QUERY_OP",
    "NODE *query_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "reset_end",   1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    RESET_END_OP, "RESET_END_OP",
    "NODE *reset_end_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "reset_start", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    RESET_START_OP, "RESET_START_OP",
    "NODE *reset_start_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "rev",         1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    REV_OP, "REV_OP",
    "NODE *rev_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "swap",        1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, CUR },
    SWAP_OP, "SWAP_OP",
    "NODE *swap_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1)",
    "2, cursor0, cursor1" },

  /* Put operation vector. */

  { "c_put_op_vec", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    C_PUT_OP_VEC_OP, "C_PUT_OP_VEC_OP",
    "NODE *c_put_op_vec_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "k_put_op_vec", 1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CON },
    K_PUT_OP_VEC_OP, "K_PUT_OP_VEC_OP",
    "NODE *k_put_op_vec_%s(TE *te, CONT_ARG *container0)",
    "1, container0"},
  { "s_put_op_vec", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { SCH },
    S_PUT_OP_VEC_OP, "S_PUT_OP_VEC_OP",
    "NODE *s_put_op_vec_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },

  /* Transactions. */

  { "open_schema", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    OPEN_SCHEMA_OP, "OPEN_SCHEMA_OP",
    "NODE *open_schema_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "init_schema", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    INIT_SCHEMA_OP, "INIT_SCHEMA_OP",
    "NODE *init_schema_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "checkpoint_schema", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    CHECKPOINT_SCHEMA_OP, "CHECKPOINT_SCHEMA_OP",
    "NODE *checkpoint_schema_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "close_schema", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    CLOSE_SCHEMA_OP, "CLOSE_SCHEMA_OP",
    "NODE *close_schema_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },

  { "abort_xact",  1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    ABORT_XACT_OP, "ABORT_XACT_OP",
    "NODE *abort_xact_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "begin_xact",  1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    BEGIN_XACT_OP, "BEGIN_XACT_OP",
    "NODE *begin_xact_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },
  { "commit_xact", 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 1, 1, 1 }, 1, { SCH },
    COMMIT_XACT_OP, "COMMIT_XACT_OP",
    "NODE *commit_xact_%s(TE *te, SCH_ARG *schema0)",
    "1, schema0" },

/* MEM realm. */

  { "alloc",       1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 1, 0, 0 }, 1, { CUR },
    ALLOC_OP, "ALLOC_OP",
    "NODE *alloc_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "varalloc",    1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 1, 0, 0 }, 2, { CUR, IN },
    VARALLOC_OP, "VARALLOC_OP",
    "NODE *varalloc_%s(TE *te, CURS_ARG *cursor0, NODE *expr0)",
    "2, cursor0, expr0" },

/* LINK realm. */

  { "resetc",      0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     RESETC_OP, "RESETC_OP",
     "NODE *resetc_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "resetp",      0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     RESETP_OP, "RESETP_OP",
     "NODE *resetp_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "advc",        0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     ADVC_OP, "ADVC_OP",
     "NODE *advc_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "advp",        0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     ADVP_OP, "ADVP_OP",
     "NODE *advp_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "endc",        0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     ENDC_OP, "ENDC_OP",
     "NODE *endc_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "endp",        0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     ENDP_OP, "ENDP_OP",
     "NODE *endp_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "foreachp",    0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 4, { CUR, CUR, LST, PAR },
     FOREACHP_OP, "FOREACHP_OP",
     "NODE *foreachp_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0, NODE* expr0)",
     "4, cursor0, cursor1, lstate0, expr0" },
  { "foreachc",    0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 4, { CUR, CUR, LST, PAR },
     FOREACHC_OP, "FOREACHC_OP",
     "NODE *foreachc_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0, NODE* expr0)",
     "4, cursor0, cursor1, lstate0, expr0" },
  { "foreachl",    0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 4, { CUR, CUR, LST, PAR },
     FOREACHL_OP, "FOREACHL_OP",
     "NODE *foreachl_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0, NODE* expr0)",
     "4, cursor0, cursor1, lstate0, expr0" },
  { "loptimize",   0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     LOPTIMIZE_OP, "LOPTIMIZE_OP",
     "NODE *loptimize_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "related",     0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     RELATED_OP, "RELATED_OP",
     "NODE *related_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "connect",     0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     CONNECT_OP, "CONNECT_OP",
     "NODE *connect_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },
  { "disconnect",  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    { 0, 0, 0, 1, 1 }, 3, { CUR, CUR, LST },
     DISCONNECT_OP, "DISCONNECT_OP",
     "NODE *disconnect_%s(TE *te, CURS_ARG *cursor0, CURS_ARG *cursor1, LST_ARG *lstate0)",
     "3, cursor0, cursor1, lstate0" },

/* ADHOC operations */

/* What distinguishes adhoc operations from current (aka built-in)
   operations is that they have they keyword adhoc before their
   definition name and that certain parameters are always identical.
   Namely: user = 1, is_void = 0, verbatim = 0, print_local_vars =1,
   print_return = 1. (BJG)

   NOTE: this may change soon.  A lot of effort has gone into making
   adhocs appear just like any other operation. (BJG)

   Currently, it just so happens that expr = 0, proceduralize = 1, and
   delete_operation = 0.  The next thing that will be attempted is to
   show that adhocs can return boolean expressions, just like
   overflow, end_adv, etc. (BJG) */

  { "cardinality", 1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CON },
    CARDINALITY_OP, "CARDINALITY_OP",
    "NODE *cardinality_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "cont_id",     1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CON },
    CONT_ID_OP, "CONT_ID_OP",
    "NODE *cont_id_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "curs_id",     1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    CURS_ID_OP, "CURS_ID_OP",
    "NODE *curs_id_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "deleted",     1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    DELETED_OP, "DELETED_OP",
    "NODE *deleted_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "refcount",    1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    REFCOUNT_OP, "REFCOUNT_OP",
    "NODE *refcount_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "serial_number", 1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CON },
    SERIAL_NUMBER_OP, "SERIAL_NUMBER_OP",
    "NODE *serial_number_%s(TE *te, CONT_ARG *container0)",
    "1, container0" },
  { "tid",         1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    TID_OP, "TID_OP",
    "NODE *tid_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },
  { "timestamp",   1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 1, { CUR },
    TIMESTAMP_OP, "TIMESTAMP_OP",
    "NODE *timestamp_%s(TE *te, CURS_ARG *cursor0)",
    "1, cursor0" },

  /* Field parameter. */

  /* These operations with a field parameter should appear at the end
     of the table (op-tab).

     This is because operations with a field parameter will appear a
     variable number of times in op_list--once for every field in the
     element type.  Thus, for these operations, and all the operations
     that appear after them in the table, op_list_match() will return
     different operation identifiers for different element types.

     This confuses layers such as x/log.xp, x/log_tid_hack.xp, and
     x/log_transient.xp that, outside of a container or cursor special
     operation (i.e. when the element type is unknown), get an
     operation vector (P2_get_op_vec) and dispatch to a function in
     the operation vector. (JAT) */

  { "iref",        1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, FIE },
    IREF_OP, "IREF_OP",
    "NODE *iref_%s(TE *te, CURS_ARG *cursor0, char *field)",
    "2, cursor0, field" },
  { "ref",         1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 2, { CUR, FIE },
    REF_OP, "REF_OP",
    "NODE *ref_%s(TE *te, CURS_ARG *cursor0, char *field)",
    "2, cursor0, field" },
  { "upd",         1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    { 1, 1, 0, 1, 1 }, 3, { CUR, FIE, EXP },
    UPD_OP, "UPD_OP",
    "NODE *upd_%s(TE *te, CURS_ARG *cursor0, char *field, NODE *expr0)",
    "3, cursor0, field, expr0" },
  
/* Terminator, must appear at the end of the table. */
/* Termination condition is (op_tab[i].name == NULL) */
  { "",            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    { 0, 0, 0, 1, 1 }, 0, { ERR },
    0, "0", "", "" },

};
