/* $Id: xp-gram.y,v 45.1 1997/09/29 03:51:22 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* xp grammar (bison source file). */

/* layer.xp -> layer.c (XP2C aka expand) preprocessor grammar (DSB) */

%{

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <stdlib.h>       /* atoi() */
#include <string.h>       /* strcpy() */

#include "adhoc-arg.h"    /* ADHOC_ARG */
#include "error.h"        /* parse_error() */
#include "field.h"        /* add_new_cursor_field() */
#include "gen-layerdef.h" /* annotations */
#include "io.h"           /* SPRINT_BUF_SIZE */
#include "lex.h"          /* yytext */
#include "ref-util.h"     /* ref_util() */
#include "rlist.h"        /* RLIST */
#include "seen.h"         /* seen */
#include "string-util.h"  /* replace_string_inplace() */
#include "util.h"         /* BOOLEAN */
#include "xp-actions.h"   /* do_action() */
#include "xform.h"        /* ANNOTATION */
#include "xp-io.h"        /* out() */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

#define YYDEBUG 1         /* Pretty debugging code. */
#define YYERROR_VERBOSE 1 /* define as anything for verbose BISON errors. */

/*****************************************************************************/
/*                  Local variables.                                         */
/*****************************************************************************/

static BOOLEAN output_semicolon = FALSE; /* Should we output a semicolon? */

/* Left hand side of update statement. */

static BOOLEAN lhs_obj_field;            /* References obj field? */
static int     lhs_pnum;                 /* For assignment statement. */
static int     lhs_cnum;                 /* Numeric tag for cursor/container */
static char    *lhs_field;
static char    *lhs_rparam;
static BOOLEAN lhs_cursor_field;         /* References cursor field? */
static BOOLEAN lhs_unknown_fld;          /* Don't know name of lhs field. */

/*****************************************************************************/
/*                  Local forward references                                 */
/*****************************************************************************/

int  yylex(void);
void yyerror(char *s);

%}

/***********************************************************************
                Tokens  
************************************************************************/

%token ADD
%token ADHOC
%token ADV
%token ALLOC
%token VARALLOC
%token P2_ANNOTATION
%token ARGUMENT
%token ARROW
%token AS_CURSOR
%token BANG_LINE
%token CALL
%token CHECKPOINT_CONT
%token CLOSE_CONT
%token CNSTATE
%token COMMENT
%token CONTAINER
%token CONTAINER_FUNC
%token CONTAINER_ID
%token CONTAINER_TYPE
%token CONT_STATE
%token COST
%token CRSTATE
%token CURSOR
%token CURSOR_FUNC
%token CURSOR_ID
%token CURSOR_TYPE
%token CURS_STATE
%token C_PUT_OP_VEC
%token C_VERBATIM
%token D2U
%token DDLHINT
%token DEF_CONTAINER_FUNC
%token DEF_CURSOR_FUNC
%token DELETE
%token DELETE_CURS
%token DOLLAR_WORD
%token DS_TOKEN
%token ELEMENT
%token END_ADV
%token END_FOREACH
%token END_REV
%token END_ROFEACH
%token EXPR
%token FIELD
%token FOREACH
%token FUNBODY
%token GETREC
%token HASH_IDENTIFIER
%token IDENTIFIER
%token INDIRECT_ONLY
%token INIT_CONT
%token INIT_CURS
%token INSERT
%token VARINSERT
%token IREF
%token K_VERBATIM
%token K_PUT_OP_VEC
%token LAYER
%token LAYERNO
%token LIMIT
%token LITERAL
%token L_VERBATIM
%token MAPPED_VIA_PARAM
%token MCURS
%token MEM_TOKEN
%token MULTIPLE
%token NEW_CONTAINER_TYPE
%token NO
%token OBJ_TYPE
%token OPEN_CONT
%token OPEN_CONT_NUMBER
%token OPLIST
%token OPTIMIZE
%token OPTIONAL
%token ORDERBY_DIRECTION
%token ORDERBY_FIELD
%token ORIG_TYPE
%token OVERFLOW
%token VAROVERFLOW
%token PADOT
%token PANN
%token POSITION
%token PREDICATE
%token PROCEDURALIZE_REF
%token PSDOT
%token QUERY
%token RECORD
%token REF
%token REPLICATE
%token RESET_END
%token RESET_START
%token P2_RETRIEVAL_ALWAYS
%token P2_RETRIEVAL_DIRECTION
%token P2_RETRIEVAL_NEVER
%token P2_RETRIEVAL_SOMETIMES
%token REV
%token ROFEACH
%token S_PUT_OP_VEC
%token S_VERBATIM
%token STABLE
%token STRUCT
%token SWAP
%token SYNC_CONT
%token TOP_TOKEN
%token UNSTABLE
%token UPD
%token VALUE
%token VPTOK
%token WITH_TYPE
%token XEND
%token XFORM
%token XSTART

/* Transaction tokens. */

%token OPEN_SCHEMA INIT_SCHEMA CHECKPOINT_SCHEMA CLOSE_SCHEMA
%token ABORT_XACT BEGIN_XACT COMMIT_XACT

/* Link operation tokens. */

%token ADVC
%token ADVP
%token CONNECT
%token DISCONNECT
%token ENDC
%token ENDP
%token FOREACHC
%token FOREACHL
%token FOREACHP
%token LOPTIMIZE
%token RELATED 
%token RESETC
%token RESETP

/* Link keyword tokens. */

%token APPLY
%token BOUND
%token CCARD
%token COMPANION
%token CRESIDUAL
%token LINKANNOTE
%token LINKCOST
%token LINKLAYER
%token LINKNAME
%token LINKPREDICATE
%token LSTATE
%token PCARD
%token PRESIDUAL
%token SCHEMA
%token SPECIAL

/* Link realm tokens. */

%token LINK_TOKEN TOPLINK_TOKEN

%union {
   char      str[MAX_IDENT_LEN];
   RLIST     *ptr;
   NODE      *node;
   ADHOC_ARG *aptr;
   int       i;
}

%type <str>  ADHOC
%type <str>  ADV
%type <str>  ADVC
%type <str>  ADVP
%type <str>  ALLOC
%type <str>  VARALLOC
%type <str>  APPLY
%type <str>  ARROW 
%type <str>  AS_CURSOR
%type <str>  BANG_LINE
%type <str>  BOUND
%type <str>  CCARD
%type <str>  CHECKPOINT_CONT
%type <str>  CLOSE_CONT
%type <str>  COMMENT
%type <str>  COMPANION
%type <str>  CONNECT
%type <str>  CONTAINER
%type <str>  CONTAINER_ID
%type <str>  CONTAINER_TYPE
%type <str>  COST
%type <str>  CRESIDUAL
%type <str>  CURSOR
%type <str>  CURSOR_ID
%type <str>  CURSOR_TYPE
%type <str>  C_PUT_OP_VEC
%type <str>  C_VERBATIM
%type <str>  DEF_CONTAINER_FUNC
%type <str>  DEF_CURSOR_FUNC
%type <str>  DELETE 
%type <str>  DELETE_CURS
%type <str>  DISCONNECT 
%type <str>  DOLLAR_WORD
%type <str>  ELEMENT
%type <str>  ENDC
%type <str>  ENDP
%type <str>  END_ADV
%type <str>  END_REV
%type <str>  EXPR
%type <str>  FIELD
%type <str>  FOREACH
%type <str>  FOREACHC
%type <str>  FOREACHL
%type <str>  FOREACHP
%type <str>  FUNBODY
%type <str>  GETREC
%type <str>  HASH_IDENTIFIER
%type <str>  IDENTIFIER
%type <str>  INIT_CONT
%type <str>  INIT_CURS
%type <str>  INSERT
%type <str>  VARINSERT
%type <str>  IREF
%type <str>  K_PUT_OP_VEC
%type <str>  K_VERBATIM
%type <str>  LAYER
%type <str>  LINKANNOTE
%type <str>  LINKCOST
%type <str>  LINKLAYER
%type <str>  LINKNAME
%type <str>  LINKPREDICATE
%type <str>  LITERAL
%type <str>  LSTATE
%type <str>  L_VERBATIM
%type <str>  MULTIPLE
%type <str>  NEW_CONTAINER_TYPE
%type <str>  OBJ_TYPE
%type <str>  OPEN_CONT
%type <str>  OPEN_CONT_NUMBER
%type <str>  OPLIST
%type <str>  OPTIMIZE
%type <str>  OPTIONAL
%type <str>  ORDERBY_DIRECTION
%type <str>  ORDERBY_FIELD
%type <str>  ORIG_TYPE
%type <str>  OVERFLOW
%type <str>  VAROVERFLOW
%type <str>  PCARD
%type <str>  POSITION
%type <str>  PREDICATE
%type <str>  PRESIDUAL
%type <str>  PROCEDURALIZE_REF
%type <str>  QUERY
%type <str>  RECORD
%type <str>  REF
%type <str>  RELATED
%type <str>  REPLICATE
%type <str>  RESETC
%type <str>  RESETP
%type <str>  RESET_END
%type <str>  RESET_START
%type <str>  P2_RETRIEVAL_ALWAYS
%type <str>  P2_RETRIEVAL_DIRECTION
%type <str>  P2_RETRIEVAL_NEVER 
%type <str>  P2_RETRIEVAL_SOMETIMES
%type <str>  REV
%type <str>  ROFEACH
%type <str>  S_PUT_OP_VEC
%type <str>  S_VERBATIM
%type <str>  SCHEMA
%type <str>  SPECIAL
%type <str>  STRUCT
%type <str>  SWAP
%type <str>  SYNC_CONT
%type <str>  UPD
%type <str>  VPTOK
%type <str>  XFORM

%type <str>  OPEN_SCHEMA INIT_SCHEMA CHECKPOINT_SCHEMA CLOSE_SCHEMA
%type <str>  ABORT_XACT BEGIN_XACT COMMIT_XACT

%type <i>    CNSTATE
%type <i>    CRSTATE
%type <i>    PADOT
%type <i>    PANN
%type <i>    LAYERNO
%type <i>    VALUE
%type <i>    XEND
%type <i>    XSTART

%type <str>  adhoc_id
%type <str>  btoken
%type <str>  eos
%type <str>  ikeyword
%type <str>  itoken
%type <str>  opt_literal
%type <str>  structure

%type <ptr>  realm_list_opt
%type <ptr>  realm realm_list

%type <node> constant_expression 
%type <aptr> adhoc_actual_args

/* Start symbol. */
%start program

/* This is an ambiguous grammar. */
/* There are four shift-reduce conflicts that I cannot eliminate.
   These occur in the definitions of production ref and kref. (DSB) */
/* So, why expect five rather than four??? (JAT) */
/* %expect 5 */

%%

program:
        layer_dcl xp_stmts { /* Suppress default action. */ }
        ;

/************************************************************************/
/*             Bang (!) lines.                                           */
/*****************************************************************************/

/* Bang (!) lines are often, but not always C preprocessor statments such as
   "!#include "..." */

bang_line_opt:
        /* Nothing */
        | bang_line_list
        ;

bang_line_list:
        bang_line
        | bang_line_list bang_line
        ;

bang_line:
        BANG_LINE
          { out("\n%s\n", $1+1); 
          }
        ;

/*****************************************************************************/
/*                  layer declarations and options.                          */
/*****************************************************************************/

layer_dcl:
        bang_line_opt layer_stmt layer_options
        ;

layer_stmt:
        LAYER realm IDENTIFIER '[' realm_list_opt ']'
          {
             layer_stmt_seen($2->type, $3, $5);
          }
        ; 

realm_list_opt:
        /* Nothing */
          {
             $$ = NULL;
          }
        | realm_list
        ;

realm_list:
        realm
        | realm_list ',' realm
          {
             $$ = tackon_rlist_node($1, $3);
          }
        ;

realm:
        DS_TOKEN
          {
             $$ = new_rlist_node(DS);
          }
        | MEM_TOKEN
          {
             $$ = new_rlist_node(MEM);
          }
        | TOP_TOKEN
          {
             $$ = new_rlist_node(TOP);
          }
        | LINK_TOKEN
          {
             $$ = new_rlist_node(LINK);
          }
        | TOPLINK_TOKEN
          {
             $$ = new_rlist_node(TOPLINK);
          }
        ;

/*****************************************************************************/
/*                  Layer options.                                           */
/*****************************************************************************/

/*
 P2_ANNOTATION:  does layer have any annotations?
 STABLE:      defines cursor stability parameter 
 D2U:         tells us if layer translates deletions to updates
 P2_RETRIEVAL:   can the layer be a retrieval layer?
 CURS_STATE:  do cursors have state?
 CONT_STATE:  do containers have state?
*/

layer_options:
        lopt_list  
          {  out("\n#include \"pb.h\"\n");
             out("\n#include \"%s-ref.h\"\n",layer_name);
             clear_member();
          }
        ;

lopt_list:
        lopt
        | lopt_list lopt
        ;

lopt:
        NO P2_ANNOTATION
          { annotations = NO_ANNOTATION; }
        | P2_ANNOTATION
          { annotations = ANNOTATION; }
        | MULTIPLE P2_ANNOTATION
          { annotations = MULTIPLE_ANNOTATION; }
        | OPTIONAL P2_ANNOTATION
          { annotations = OPTIONAL_ANNOTATION; }
        | OPTIONAL MULTIPLE P2_ANNOTATION
          { annotations = OPTIONAL_MULTIPLE_ANNOTATION; }
        | STABLE
          { stable = TRUE; }
        | UNSTABLE
          { stable = FALSE; }
        | D2U
          { d2u = TRUE; }
        | CURS_STATE
          { curs_state = TRUE; }
        | CONT_STATE
          { cont_state = TRUE; }
        | INDIRECT_ONLY
          { indirect_only = TRUE; }
        | P2_RETRIEVAL_NEVER
          { retrieval = RETRIEVAL_NEVER; }
        | P2_RETRIEVAL_SOMETIMES
          { retrieval = RETRIEVAL_SOMETIMES; }
        | P2_RETRIEVAL_ALWAYS
          { retrieval = RETRIEVAL_ALWAYS; }
        ;

/*****************************************************************************/
/*                  xp statements.                                           */
/*****************************************************************************/

/* Procedures with optional semicolons or bang (!) lines. */

xp_stmts:
        xp_stmt
        | xp_stmts xp_stmt
        ;

xp_stmt:
        procs body
          {  if (!seen[LAYER_STMT])
                parse_error("place layer statement before all procedures");
          } 
        | ';'
          {  out(";");
          }
        | bang_line
        ;

/*****************************************************************************/
/*                  xp procedures.                                           */
/*****************************************************************************/

procs:
        INIT_CONT '(' CONTAINER ')'
          { opheader(INIT_CONT_OP); }
        | C_PUT_OP_VEC '(' CURSOR ')'
          { opheader(C_PUT_OP_VEC_OP); }
        | C_VERBATIM '(' CURSOR ')'
          { opheader(C_VERBATIM_OP); }
        | K_PUT_OP_VEC '(' CONTAINER ')'
          { opheader(K_PUT_OP_VEC_OP); }
        | K_VERBATIM '(' CONTAINER ')'
          { opheader(K_VERBATIM_OP); }
        | S_PUT_OP_VEC '(' SCHEMA ')'
          { opheader(S_PUT_OP_VEC_OP); }
        | S_VERBATIM '(' SCHEMA ')'
          { opheader(S_VERBATIM_OP); }
        | L_VERBATIM '(' ')'
          { opheader(L_VERBATIM_OP); }
        | QUERY '(' CURSOR ')'
          { opheader(QUERY_OP);
            retrieval_layer_header(QUERY_OP, "QUERY_OP", "cursor0");
          }
        | DDLHINT '(' IDENTIFIER ',' IDENTIFIER ')'
          { opheader(DDLHINT_OP);
            in_ddlhint_proc = TRUE;
            in_special_proc = TRUE;
          }
        | OPEN_CONT '(' CONTAINER ')'
          { opheader(OPEN_CONT_OP); }
        | OPEN_CONT_NUMBER '(' CONTAINER ',' EXPR ')'
          { opheader(OPEN_CONT_NUMBER_OP); }
        | CHECKPOINT_CONT '(' CONTAINER ')'
          { opheader(CHECKPOINT_CONT_OP); }
        | CLOSE_CONT '(' CONTAINER ')'
          { opheader(CLOSE_CONT_OP); }
        | OVERFLOW '(' CONTAINER ')'
          { opheader(OVERFLOW_OP); }
        | VAROVERFLOW '(' CONTAINER ',' EXPR ')'
          { opheader(VAROVERFLOW_OP); }
        | INSERT '(' CURSOR ',' RECORD ')' 
          { opheader(INSERT_OP); }
        | VARINSERT '(' CURSOR ',' RECORD ',' EXPR ')' 
          { opheader(VARINSERT_OP); }
        | REF '(' CURSOR ',' FIELD ')' 
          { opheader(REF_OP); }
        | IREF '(' CURSOR ',' FIELD ')'
          { opheader(IREF_OP); }
        | POSITION '(' CURSOR ',' EXPR ')'
          { opheader(POS_OP); }
        | END_ADV '(' CURSOR ')' 
          { opheader(END_ADV_OP);
            retrieval_layer_header(END_ADV_OP, "END_ADV_OP", "cursor0");
          }
        | END_REV '(' CURSOR ')'
          { opheader(END_REV_OP); 
            retrieval_layer_header(END_REV_OP, "END_REV_OP", "cursor0");
          }
        | ADV '(' CURSOR ')'
          { opheader(ADV_OP);  
            retrieval_layer_header(ADV_OP, "ADV_OP", "cursor0");
          } 
        | OPTIMIZE '(' CURSOR ')'
          { opheader(OPTIMIZE_OP);
            in_optimize_proc = TRUE;
          }
        | INIT_CURS '(' CURSOR ')'
          { opheader(INIT_CURS_OP); }
        | REV '(' CURSOR ')'
          { opheader(REV_OP);  
            retrieval_layer_header(REV_OP, "REV_OP", "cursor0");
          } 
        | DELETE '(' CURSOR ')'
          { opheader(DELETE_OP); }
        | DELETE_CURS '(' CURSOR ')'
          { opheader(DELETE_CURS_OP); }
        | RESET_START '(' CURSOR ')'
          { opheader(RESET_START_OP);
            retrieval_layer_header(RESET_START_OP, "RESET_START_OP", "cursor0");
          } 
        | RESET_END '(' CURSOR ')'
          { opheader(RESET_END_OP);
            retrieval_layer_header(RESET_END_OP, "RESET_END_OP", "cursor0");
          }  
        | SWAP '(' CURSOR ',' CURSOR ')'
          { opheader(SWAP_OP);
            if ((get_param_num($3) != 0) || (get_param_num($5) != 1)) 
              parse_error("cursor parameters of swap are indexed wrong");
          }
        | SYNC_CONT '(' CONTAINER ',' EXPR ',' EXPR ',' EXPR ')'
          { opheader(SYNC_CONT_OP); }
        | GETREC '(' CURSOR ',' RECORD ')'
          { opheader(GETREC_OP); }   
        | ALLOC '(' CURSOR ')'
          { opheader(ALLOC_OP); } 
        | VARALLOC '(' CURSOR ',' EXPR ')'
          { opheader(VARALLOC_OP); } 
        | UPD '(' CURSOR ',' FIELD ',' EXPR ')'
          { opheader(UPD_OP); }
        | FOREACH '(' CURSOR ',' EXPR ')'
          { opheader(FOREACH_OP); }
        | ROFEACH '(' CURSOR ',' EXPR ')'
          { opheader(ROFEACH_OP); }
        | XFORM '(' ELEMENT ',' CONTAINER ',' CURSOR  ')'
          { opheader(XFORM_OP);
            in_xform_proc = TRUE;
          }
        | ADHOC adhoc_id adhoc_formal_args 
          { opheader(getop($2)); }
  
        /* Transaction operations. */

        | OPEN_SCHEMA '(' SCHEMA ')'
          { opheader(OPEN_SCHEMA_OP); }
        | INIT_SCHEMA '(' SCHEMA ')'
          { opheader(INIT_SCHEMA_OP); }
        | CLOSE_SCHEMA '(' SCHEMA ')'
          { opheader(CLOSE_SCHEMA_OP); }

        | ABORT_XACT '(' SCHEMA ')'
          { opheader(ABORT_XACT_OP); }
        | BEGIN_XACT '(' SCHEMA ')'
          { opheader(BEGIN_XACT_OP); }
        | COMMIT_XACT '(' SCHEMA ')'
          { opheader(COMMIT_XACT_OP); }
        | CHECKPOINT_SCHEMA '(' SCHEMA ')'
          { opheader(CHECKPOINT_SCHEMA_OP); }

        /* Link operations. */
  
        | RESETC '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(RESETC_OP);  
            link_retrieval_layer_header(RESETC_OP, "RESETC_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | RESETP '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(RESETP_OP);  
            link_retrieval_layer_header(RESETP_OP, "RESETP_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | ADVC  '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(ADVC_OP);  
            link_retrieval_layer_header(ADVC_OP, "ADVC_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | ADVP  '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(ADVP_OP);  
            link_retrieval_layer_header(ADVP_OP, "ADVP_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | ENDC  '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(ENDC_OP);  
            link_retrieval_layer_header(ENDC_OP, "ENDC_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | ENDP  '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(ENDP_OP);  
            link_retrieval_layer_header(ENDP_OP, "ENDP_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | FOREACHP  '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR ')'
          { opheader(FOREACHP_OP);  
            link_retrieval_layer_header(FOREACHP_OP, "FOREACHP_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | FOREACHC  '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR ')'
          { opheader(FOREACHC_OP);  
            link_retrieval_layer_header(FOREACHC_OP, "FOREACHC_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | FOREACHL  '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR  ')'
          { opheader(FOREACHL_OP);  
            link_retrieval_layer_header(FOREACHL_OP, "FOREACHL_OP", 
                       "cursor0, cursor1, lstate0");
          }
        | RELATED    '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(RELATED_OP); 
          }
        | CONNECT    '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(CONNECT_OP); 
          }
        | DISCONNECT '(' CURSOR ',' CURSOR ',' LSTATE ')'
          { opheader(DISCONNECT_OP); 
          }
        | LOPTIMIZE  '(' CURSOR ',' CURSOR ','  LSTATE ')'
          { opheader(LOPTIMIZE_OP);  
            in_optimize_proc = TRUE;
          }

        | user_funcs
        ;

/*****************************************************************************/
/*                  User functions.                                          */
/*****************************************************************************/

/* These are not official xp procs, but are auxiliary procedures
   defined by users that are static to the layer. */

user_funcs:
        CURSOR_FUNC IDENTIFIER '(' CURSOR opt_literal ')'
          {  cursor_func_action($2, $4, $5);
          }
        | CONTAINER_FUNC IDENTIFIER '(' CONTAINER opt_literal ')'
          {  container_func_action($2, $4, $5);
          }
        | DEF_CURSOR_FUNC ':' DOLLAR_WORD
          {  def_cursor_func_action($3);
          }
        | DEF_CONTAINER_FUNC ':' DOLLAR_WORD
          {  def_container_func_action($3);
          }
        ;

opt_literal:
        /* Nothing */
          {  strcpy($$, "");
          }
        | ',' LITERAL
          {
#if 1
             /* These statements replace quote and double backslash with
                the empty string. */
             /* I was going to get rid of these replacements, but they
                seem to only be used in cursor_func and container_func,
                and don't seem to be doing any harm. (JAT) */
             replace_char($2, '"', ' ');
             replace_char($2, '\\', ' ');
#else
             /* Replace backslash quote (\") with quote (") */
             replace_string_inplace($2, "\\\"", "\"");

             /* Replace double backslash (\\) with backslash (\) */
             replace_string_inplace($2, "\\\\", "\\");
#endif
             strcpy($$, $2);
          }
        ;

/*****************************************************************************/
/*                  adhoc identifier.                                        */
/*****************************************************************************/

adhoc_id:
        IDENTIFIER
        | HASH_IDENTIFIER
        ; 

/*****************************************************************************/
/*                  argument lists for adhoc operations.                     */
/*****************************************************************************/

adhoc_formal_args:
        '(' ')'
        | '(' adhoc_formal_arg_list ')' 
        ;

adhoc_formal_arg_list:
        adhoc_formal_arg
        | adhoc_formal_arg_list ',' adhoc_formal_arg
        ;

adhoc_formal_arg:
        CURSOR      { /* Suppress default action. */ }
        | CONTAINER { /* Suppress default action. */ }
        | SCHEMA    { /* Suppress default action. */ }
        | VPTOK     { /* Suppress default action. */ }
        ;

/*****************************************************************************/
/*                  xp procedure bodies.                                     */
/*****************************************************************************/

/* 
  xp distinguishes two sequences of tokens
  (1) those within %{ %} (called itokens) and
  (2) those that are not (called ctokens).

  The following rules are used to differentiate these token streams.
*/

body:
        XSTART 
         {  print_proc_header();
            x_header(FALSE);
         }
         ctoken_stmts XEND
         {  print_proc_trailer();
            x_trailer(FALSE);
         }
        | '{' 
         {  print_proc_header();
         }
         itoken_stmts '}'
         {  print_proc_trailer();
         }
        | '{' '}'
         { print_proc_header();
           print_proc_trailer();
         }
        ;

/*****************************************************************************/
/*                  itoken statements.                                       */
/*****************************************************************************/

/*
    An itoken statement is a list of tokens terminated by ';'
    or an itoken body.  An itoken body are itoken statements 
    enclosed within braces { }.

    Note: this grammar does not recognize constructs like:

       switch(something) {
       case 0:  optimize(cursor);  // error
                break;

    A parsing error occurs because "case 0:" is in front of 
    optimize.  The way to fix this would be to put in a 
    dummy statement like:

       case 0:  ;  // dummy statement
                optimize(cursor);  // ok
                break;

    The problem is that the add (iproc) statement likes 
    parentheses and braces and this introduces ambiguities
    in the grammar if iproc is trated as an itoken...
*/

itoken_stmts:
        itoken_stmt
        | itoken_stmts itoken_stmt
        ;

/* I'd like to make optional the semicolon following itoken_list.
   It would be nice to be able to omit this semicolon, for example,
   after a %v.endif that emits "#endif".  Unfortunately, making the
   semicolon optional causes lots of shift-reduce conflicts. (JAT) */

itoken_stmt:
        iprocs ';'
        | ddlhints ';'
        | itoken_list ';'
          { out("; ");
          }
        | itoken_body 
        | itoken_list itoken_body
        ;

itoken_body:
        '{'
          {  out("{");
             brace_nesting_depth++;
          }
        itoken_stmts '}'
          {  brace_nesting_depth--;
             out("}");
          }
        | '{' '}'
          { out("{ }");
          }
        | XSTART
          {  x_header(TRUE);
          }
          ctoken_stmts XEND
          { x_trailer(TRUE);
          }
        ;

itoken_list:
        itoken
          {  out($1);
          }
        | itoken_list itoken
          {  out(" ");
             out($2);
          }
        ;

/*****************************************************************************/
/*                  iprocs.                                                  */
/*****************************************************************************/

/*
  the only xp procs that can appear outside
  %{  %}.  They should only be called within xform()
  procs, although this is not checked (at present).
*/

iprocs:
        ADD structure ':' declaration 
          {
            char t[SPRINT_BUF_SIZE];
            sprint_ctype_as_new_ctype_call(t, member_ctype);
            if (know_member_name) {
              out("new_member(te, %s, \"%s\", %s, %s);",
                  $2, member_name, t, member_type);
              if (strncmp($2,"cursor", 6) == 0)
                add_new_cursor_field (member_name);
            }
            else {
              if (strcmp($2,"global") == 0)
                out("new_global(te, %s, %s, %s);",
                    member_name, t, member_type);
              else
                out("new_member(te, %s, %s, %s, %s);",
                    $2, member_name, t, member_type);
            }
            clear_member();
          }
        | ADD structure ':' MCURS IDENTIFIER IDENTIFIER
           {
             out("new_member(te, %s, \"%s\", ctype_of(%s), (%s)->ident);",
                 $2, $6, $5, $5);
             if (strncmp($2,"cursor", 6) == 0)
               add_new_cursor_field ($6);
           }
        | ADD structure ':' MCURS IDENTIFIER
           {  out("copy_member(%s,%s);", $2, $5);
           }
        |  NEW_CONTAINER_TYPE IDENTIFIER
           WITH_TYPE IDENTIFIER
           MAPPED_VIA_PARAM LITERAL
           {
             int p = get_param_num($1);
             path[p] = atoi($6);
             out("{"
                 "IDENT3 *i;"
#if 0
                 "cont_id_counter++;"
#endif
                 "i = container_declaration_ident3(te->down[%s], %s, %s);",
                 $6, $4, $2);
             out("cursor%d = i->cur;", p);
             out("container%d = i->con;", p);
             out("element%d = i->ele;", p);
             out("}");
           }
        | REPLICATE AS_CURSOR 
           {
             int p = get_param_num($1);
             int q = get_param_num($2);
             path[q] = path[p];
             out("cursor%d = cursor%d;", q, p);
             out("container%d = container%d;", q, p);
             out("element%d = element%d;", q, p);
           }
       | COMPANION IDENTIFIER MAPPED_VIA_PARAM LITERAL
           {
             int p = get_param_num($1);
             out("{"
                 "IDENT3 *i;"
                 "i = find_ident3(%s);", $2);
             out("cursor%d    = i->cur;", p);
             out("container%d = i->con;", p);
             out("element%d   = i->ele;", p);
             out("}");
             path[p] = atoi($4);
           }
       | OPTIMIZE '(' CURSOR ')' 
         {  if (call_below(OPTIMIZE_OP, get_path_num($3))) { 
               out("call_down(te, %d, OPTIMIZE_OP, 1, %s);",
                   get_path_num($3), $3);
               if (in_optimize_proc && (retrieval == RETRIEVAL_NEVER)) { 
                 out("if (%s->layer == te->layerno)", $3);
                 out("error(\"retrieval_never layer%s cannot be retrieval layer\");",
                     layer_name);
               }    
            }
            else
               parse_error("no optimize() function on lower layer");
         }
       | XFORM '(' ELEMENT ',' CONTAINER ',' CURSOR ')' 
         {  if (call_below(XFORM_OP, get_param_num($1))) {
              out("call_down(te, %d, XFORM_OP, 4, %s, %s, %s, P2_cont_name);",
                  get_path_num($3), $3, $5, $7);
              if ((get_param_num($3) != get_param_num($5)) ||
                  (get_param_num($5) != get_param_num($7)))
                 parse_error("xform parameter number arguments don't match");
            }
            else
              parse_error("no concrete operations for terminal layer");
         }
       | CALL IDENTIFIER '(' CURSOR opt_literal ')'
         { if (strcmp($5,"") == 0)
              out("%s(te, %s);", $2, $4);
           else
              out("%s(te, %s, %s);", $2, $4, $5);
         }
       | CALL IDENTIFIER '(' CONTAINER opt_literal ')'
         { if (strcmp($5,"") == 0)
              out("%s(te, %s);", $2, $4);
           else
              out("%s(te, %s, %s);", $2, $4, $5);
         }
       | ADHOC adhoc_id adhoc_actual_args
         { opcallN($2, $3); }

       /* Link additions. */

       | LOPTIMIZE  '(' CURSOR ',' CURSOR ','  LSTATE ')'
         {  if (call_below(LOPTIMIZE_OP, get_path_num($7))) {
               out("call_down(te, %d, LOPTIMIZE_OP, 3, %s, %s, %s);",
                   get_path_num($7), $3, $5, $7);
            }
            else
               parse_error("no loptimize() function on lower layer");
        }
       ;

/*****************************************************************************/
/*                  Structure.                                               */
/*****************************************************************************/

/*
   4 tokens pass for structures: IDENTIFIER, CONTAINER
   ELEMENT, and CURSOR.  Complex expressions that 
   refer to IDENT pointers won't work.
*/

structure:
        IDENTIFIER
        | CONTAINER
        | ELEMENT
        | CURSOR
        | SCHEMA
        ; 

/*****************************************************************************/
/*                  ddlhints.                                                */
/*****************************************************************************/

/* These statements should only appear inside ddl_hint() xp procs; but
   we currently make no test to ensure that they do (or don't)
   actually appear.  */

ddlhints:
        NO P2_ANNOTATION
          {
            out("error(\"%s has no annotations\");", layer_name);
          }
        | LIMIT LITERAL ARGUMENT
          {
            /* LITERAL may be 0 */
            add_ddlhint_annotation();
            check_ddlhint_arguments($2);
          }
        | LIMIT LITERAL P2_ANNOTATION LITERAL ARGUMENT 
          {
            /* This is not fully implemented. (JAT) */
            add_ddlhint_annotation();
            check_ddlhint_arguments($4);
            out("number_of_annotations++;");
            out("if (number_of_annotations > %s)", $2);
            out("error(\"%%s has too many annotations\");", layer_name);
          }
        ;

/*****************************************************************************/
/*                  btokens.                                                 */
/*****************************************************************************/

/* The following is a list of basic tokens and actions that are common
   to both itokens and ctokens--this is a simple factoring of grammar
   rules to minimize redundancy and make the xp grammer easier to read. */

btoken:
        IDENTIFIER 
          {  strcpy($$, $1);
          }
        | COMMENT
          {  strcpy($$, "/* ");
             strcat($$, (($1)+2));
             strcat($$, " */\n");
          }
        | DS_TOKEN
          {  strcpy($$,"ds");
          }
        | MEM_TOKEN
          {  strcpy($$,"mem");
          }
        | TOP_TOKEN
          {  strcpy($$,"top");
          }
        | STRUCT
          {  strcpy($$, $1);
          }
        | ELEMENT
          {  strcpy($$, $1);
          }
        | '['
          {  strcpy($$,"[");
          }
        | ']'
          {  strcpy($$,"]");
          }
        | '('
          {  strcpy($$,"(");
          }
        | ')'
          {  strcpy($$,")");
          }
        | ','
          {  strcpy($$,",");
          }
        | ':'
          {  strcpy($$,":");
          }
        | '*'
          {  strcpy($$,"*");
          }
        | '='
          {  strcpy($$,"=");
          }
       | DOLLAR_WORD
         {  do_dollar($1, $$); 
         }
       ;

/*****************************************************************************/
/*                  ikeyword.                                                */
/*****************************************************************************/

/*
   Here are the translations of xp keywords when they
   appear outside %{ %} 
*/

ikeyword: 
        CONTAINER 
          {  ikeyword_action($$, $1, $1, "container%d->expr", "cursor%d->cont",
                             NULL, get_param_num($1));
          }
        | CONTAINER_ID
          {  ikeyword_action($$, $1, "container%d->ctype->cctype->container_id",
                             "container%d->container_id",
                             "cursor%d->container_id", NULL, get_param_num($1));
          }
        | CONTAINER_TYPE 
          {  ikeyword_action($$, $1, "container%d->name", "container%d->type",
                             "cursor%d->cont_type", NULL, get_param_num($1));
          }
        | CURSOR 
          {  ikeyword_action($$, $1, $1, "cursor%d->expr",
                             NULL, NULL, get_param_num($1));
          }
        | CURSOR_ID
          {  ikeyword_action($$, $1, NULL, (char *) -1, "cursor%d->cursor_id",
                             NULL, get_param_num($1));
          }
        | CURSOR_TYPE 
          {  ikeyword_action($$, $1, "cursor%d->name", "cursor%d->type", NULL,
                             NULL, get_param_num($1));
          }
        | PREDICATE
          {  ikeyword_action($$, $1, (char *) -1, "cursor%d->predicate", NULL,
                             NULL, get_param_num($1));
          }
        | RECORD 
          {  ikeyword_action($$, $1, (char *) -1, "record->expr", NULL, NULL);
          }
        | FIELD
          {  ikeyword_action($$, $1, $1, NULL, NULL, NULL);
          }
        | EXPR
          {  ikeyword_action($$, $1, $1, NULL, NULL, NULL);
          }
        | VPTOK
          {  ikeyword_action($$, $1, $1, NULL, NULL, NULL);
          }
        | ORIG_TYPE 
          {  ikeyword_action($$, $1, "orig_type", "container%d->orig_type",
                             "cursor%d->orig_type", NULL, get_param_num($1));
          }
        | OBJ_TYPE 
          {  ikeyword_action($$, $1, "element%d->name",
                             "container%d->obj_type",  "cursor%d->obj_type",
                             NULL, get_param_num($1));
          }
        | PANN 
          {
            sprintf($$, "((struct %s_annote *) lookup_annotation(te, %s, %s))",
                    layer_name, xp_container_id(), xp_container_name());
          }
        | PADOT IDENTIFIER
          {
            assert($2 != NULL);
            sprintf($$,
                    "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                    layer_name, xp_container_id(), xp_container_name(), $2);
          }
        | CRSTATE IDENTIFIER
          {  ikeyword_action($$, NULL, "cs->%s", NULL, NULL, NULL, $2);
          }
        | CNSTATE IDENTIFIER
          {  ikeyword_action($$, NULL, "ks->%s", NULL, NULL, NULL, $2);
          }
        | LAYERNO
          {  ikeyword_action($$, NULL, "te->layerno", NULL, NULL, NULL);
          }
        | LAYER
          {  ikeyword_action($$, $1, NULL, (char *) -1, "cursor%d->layer",
                             NULL, get_param_num($1));
          }
        | COST
          {  ikeyword_action($$, $1, (char *) -1, "cursor%d->cost", NULL,
                             NULL, get_param_num($1));
          }
        | FUNBODY
          {  ikeyword_action($$, $1, (char *) -1, "container%d->funbody",
                             "cursor%d->funbody", NULL, get_param_num($1));
          }
        | OPLIST
          {  ikeyword_action($$, $1, (char *) -1, "container%d->op_list",
                             "cursor%d->op_list", "schema%d->op_list",
                             get_param_num($1));
          }
        | PROCEDURALIZE_REF
          {  ikeyword_action($$, $1, (char *) -1, (char *) -1,
                             "cursor%d->proceduralize_ref", NULL,
                             get_param_num($1));
          }
        | ORDERBY_FIELD
          {  ikeyword_action($$, $1, (char *) -1, (char *) -1,
                             "cursor%d->orderby_field", NULL,
                             get_param_num($1));
          }
        | ORDERBY_DIRECTION 
          {  ikeyword_action($$, $1, (char *) -1, (char *) -1,
                             "cursor%d->orderby_direction",
                             NULL, get_param_num($1));
          }
        | P2_RETRIEVAL_DIRECTION
          {  ikeyword_action($$, $1, (char *) -1, (char *) -1,
                             "cursor%d->retrieval_direction",
                             NULL, get_param_num($1));
          }

        /* Transaction keywords. */
        /* See analogous code for ckeyword_action() */

        | SCHEMA
          {  ikeyword_action($$, $1, (char *) -1,
#if 0
             /* schema is an error if not a schema container or cursor. */
             "(container%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"container->schema"
               " is un-initialized, cannot expand schema\")"
               ": container%d->schema",
             "(cursor%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"cursor->schema"
               " is un-initialized, cannot expand schema\")"
               ": cursor%d->schema",
#else
              /* schema is the empty string (schema[0] == '\0') if not
                 a schema container or cursor. */
              "container%d->schema", "cursor%d->schema",
#endif
             NULL, get_param_num($1), get_param_num($1));
          }

        /* Link keywords. */

        | LINKPREDICATE
          {  ikeyword_action($$, $1, "lstate%d->linkpredicate", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | LINKLAYER
          {  ikeyword_action($$, $1, "lstate%d->linklayer", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | LINKCOST 
          {  ikeyword_action($$, $1, "lstate%d->linkcost", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | CRESIDUAL
          {  ikeyword_action($$, $1, "lstate%d->cresidual", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | PRESIDUAL
          {  ikeyword_action($$, $1, "lstate%d->presidual", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | APPLY
          {  ikeyword_action($$, $1, "lstate%d->apply", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | LINKANNOTE
          {  ikeyword_action($$, $1, "((struct %s_annote *)"
                             "(lstate%d->linkannote))",
                             NULL, NULL, layer_name, NULL, get_param_num($1)); 
          }
        | LINKNAME 
          {  ikeyword_action($$, $1, "lstate%d->linkname", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | PCARD
          {  ikeyword_action($$, $1, "lstate%d->pcard", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | CCARD
          {  ikeyword_action($$, $1, "lstate%d->ccard", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | BOUND 
          {  ikeyword_action($$, $1, "cursor%d->bound", NULL, NULL,
                             NULL, get_param_num($1));
          }
        | LSTATE
          {  ikeyword_action($$, $1, $1, NULL, NULL, NULL, NULL);
          }
        | SPECIAL
          {  ikeyword_action($$, $1, "lstate%d->special_foreachl", NULL, NULL,
                             NULL, get_param_num($1));
          }
        ;

/*****************************************************************************/
/*                  itokens.                                                 */
/*****************************************************************************/

/*
   The following is the list of tokens and their translations when
   these tokens occur inside an xp proc but outside %{ %} braces.
*/

itoken:
       btoken
       | '.'
         {  strcpy($$, ".");
         }
       | ARROW
         {  strcpy($$, $1);
         }
       | LITERAL
         {
#if 0
            /* This statement replaces double quote with the empty
               string.  This is bad--with this statement in here,
               there is no way to emit, for example character escape
               codes, such as backslash n (newline). (JAT) */
            /* Previous to revision 1.14, this statement instead
               replaced backslash quote (\") with quote (").
               This is good, so I have re-instated this behavior.
               (JAT) */
            remove_char($1, '\\');
#else
            /* Replace backslash quote (\") with quote (") */
            replace_string_inplace($1, "\\\"", "\"");
#endif
            fputs($1, stdout);
            $$[0] = '\0';
         }
       | ikeyword
       ; 

/*****************************************************************************/
/*                  ctoken statements.                                       */
/*****************************************************************************/

/*
  A ctoken statement is a sequence of ctokens and conversions of
  special tokens (i.e., cursor, container_type, etc.).  A ctoken
  statement is terminated by any of three characters ';', '{', or '}'.
*/
  
ctoken_stmts:
        stmt 
          {  jettison();
          }
        | ctoken_stmts eos
          {  if (output_semicolon || strcmp($2, ";") != 0)
               strcat(ctoken_line, $2);
             jettison();
          }
          stmt
          {  jettison();
          }
        ;

eos:
        ';'
          {  strcpy($$, ";");
          }
        | '{' 
          {  strcpy($$, "{");
          }
        | '}'
          {  strcpy($$, "}");
          }
        ;

stmt:
            cprocs
       { /* I assume that any generated code has lots of semicolons (DSB) */
         output_semicolon = FALSE;
       }
     | update
       { /* I assume that any generated code has lots of semicolons (DSB) */
         output_semicolon = FALSE;
       }
     | no_update
       { output_semicolon = TRUE;
       }
     | /* Nothing */
       {
         /* I was having the problem in an XSTART/XEND block
            containing only a semicoln (ie %{ ; %}) that the
            semicolon was not output.  This fix seems to solve that
            problem without introducing too many un-intended
            semicolons elsewhere. (JAT) */
         output_semicolon = TRUE;
       }
     ;

/*****************************************************************************/
/*                  ref productions.                                         */
/*****************************************************************************/

/*
   ref productions generate calls to ref() and iref().
   ref calls are recognized by "cursor . <field>" and
   iref calls are recognized by "<ref call> -> <field>".
   Note that we need to know (and sometimes guess) 
   whether <field> is actually a field of an element
   or a field of a cursor...

   Note: syntax like (cursor.field)->arrow is NOT
   presently recognized...  Only flattend (cursor.field->arrow)
   syntax is...
*/

ref:
       CURSOR '.' field
       { 
          force_field_ref = FALSE;
          ref_util($1);
       }
     | CURSOR '.' '.' field
       { 
          force_field_ref = TRUE;
          ref_util($1);
       }
     | CURSOR '.' field '[' index ']'
       {
         force_field_ref = FALSE;
         ref_util_array($1);
       }
     | CURSOR '.' '.' field '[' index ']'
       {
         force_field_ref = TRUE;
         ref_util_array($1);
       }
    |  ref ARROW field '[' index ']'
       {
          iref_util_array();
       }
    |  ref ARROW field
       {
         iref_util();
       }
    ;

/*****************************************************************************/
/*                  index productions.                                       */
/*****************************************************************************/

/*
  Index productions are used to recognized array indices
  in element and container fields.  Two values are set:
  index_val (to indicate the value of the index) and 
  unknown_idx which is TRUE if we know the actual index
  value at xp compile time; FALSE otherwise. (DSB)
*/

/* Change "unknown_idx" to "constant_index" and negate it? (JAT) */
/* Combine this rule with constant_expression? (JAT) */

index:
      VALUE IDENTIFIER
        { unknown_idx = TRUE;
          strcpy(index_val, $2);
        }
      | LITERAL
        { unknown_idx = FALSE;
          strcpy(index_val, $1);
        }
      | CRSTATE IDENTIFIER
        { unknown_idx = TRUE;
          sprintf(index_val, "cs->%s", $2); 
        }
      | CNSTATE IDENTIFIER
        { unknown_idx = TRUE;
          sprintf(index_val, "ks->%s", $2);
        }
      | PADOT IDENTIFIER
        { unknown_idx = TRUE;
#if 0
          sprintf(index_val,"((struct %s_annote *)(te->annotation))->%s",
                  layer_name, $2);
#else
          assert($2 != NULL);
          sprintf(index_val,
                  "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                  layer_name, xp_container_id(), xp_container_name(), $2);
#endif
        }
      | IDENTIFIER
        { unknown_idx = FALSE;
          strcpy(index_val, $1);
        }
      ;

/*****************************************************************************/
/*                  field productions.                                       */
/*****************************************************************************/

/*
  Field productions are used to recognize fields of 
  cursors and elements.  Two variables are set:
  field_val (to indicate the name of the field) and
  unknown_idx which is TRUE if we know the actual name
  of the field at xp compile time; FALSE otherwise./
*/

/* Change "unknown_fld" to "constant_field" and negate it? (JAT) */
/* Combine this rule with constant_expression? (JAT) */

field:
        VALUE IDENTIFIER
        { unknown_fld = TRUE;
          strcpy(field_val, $2);
        }
      | FIELD
        { unknown_fld = TRUE;
          strcpy(field_val, $1);
        }
      | CRSTATE IDENTIFIER
        { unknown_fld = TRUE;
          sprintf(field_val, "cs->%s", $2);
        }
      | CNSTATE IDENTIFIER
        { unknown_fld = TRUE;
          sprintf(field_val, "ks->%s", $2);
        }
      | IDENTIFIER
        { unknown_fld = FALSE;
          strcpy(field_val, $1);
        }
      | PADOT IDENTIFIER
        { unknown_fld = TRUE;
#if 0
          sprintf(field_val,"((struct %s_annote *)(te->annotation))->%s",
                  layer_name, $2);
#else
          assert($2 != NULL);
          sprintf(field_val,
                  "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                  layer_name, xp_container_id(), xp_container_name(), $2);
#endif
        }
      ;

/*****************************************************************************/
/*                  kref productions.                                        */
/*****************************************************************************/

/*
   kref productions are to process container field
   references.  Note limitations below and in comments
   in particular productions

   Note: syntax like (container.field)->arrow is NOT
   presently recognized...  Only flattend (container.field->arrow)
   syntax is...
*/

kref:
       CONTAINER '.' field
       {
         force_field_ref = FALSE;
         kref_util($1);
       } 
     | CONTAINER '.' '.' field
       {
         /* This feature is not used in any existing layer. (JAT) */
         force_field_ref = TRUE;
         kref_util($1);
       }
     | CONTAINER '.' field '[' index ']'
       {
         kref_util_array($1);
       }
     | kref ARROW field
       {
          iref_util();
       }
     | kref ARROW field '[' index ']'
       { 
          iref_util_array();
       }
     ;

/*****************************************************************************/
/*                  ctokens.                                                 */
/*****************************************************************************/

/*
  The following is the list of tokens and their
  translations when these tokens occur inside
  %{ %} braces.

  ctoknr - is the set of ctokens minus refs.

  Note: dots and arrows are tricky things; ref and
  kref are productions that define how dots and arrows
  are to be interpreted in the context of cursors and
  containers...  we still need to be able to have dots 
  and arrows that are not bound to cursors and containers
  inside %{ %} so the way we have rigged this is that
  dots and arrows can only follow btokens (which actually
  makes sense)...
*/

ctoken:
        ref
          {  jettison();
             out("NONTERM(P2_rf);");
          }
        | ctoknr
        ; 

ctoknr:
        kref
          {  jettison();
             out("NONTERM(P2_rf);");
          }
        | SCHEMA '.' field
          {  sref_util($1);
             jettison();
             out("NONTERM(P2_rf);");
          }
        | btoken 
          { 
             strcat(ctoken_line, " ");
             strcat(ctoken_line, $1);
          }
          opt_follow
        | LITERAL
          { 
             strcat(ctoken_line, " ");
             strcat(ctoken_line, $1);
          }
        | cxprocs
        | ckeyword
        ;

opt_follow:
        /* Nothing*/
        | ARROW
          { 
             strcat(ctoken_line, "->");
          }
        | '.'
          { 
             strcat(ctoken_line, ".");
          }
        | '.' '.' IDENTIFIER
          {  jettison();
             out("NONTERM(terminal_vstring(\".%s%%d\", te->layerno));", $3);
          }
        ;

/*****************************************************************************/
/*                  cxprocs.                                                 */
/*****************************************************************************/

/* These are xp procs that can be embedded within a ctoken statement. */

cxprocs:
        END_ADV '(' CURSOR ')'  
          {  jettison(); do_action($1, $3); } 
        | END_REV '(' CURSOR ')'  
          {  jettison(); do_action($1, $3); }
        | ALLOC '(' CURSOR ')'
          {  jettison(); do_action($1, $3); } 
        | VARALLOC '(' CURSOR ',' EXPR ')'
          {  jettison(); do_action($1, $3, $5); } 
        | OVERFLOW '(' CONTAINER ')'
          {  jettison(); do_action($1, $3); } 
        | VAROVERFLOW '(' CONTAINER ')'
          {  jettison(); do_action($1, $3); } 
        | POSITION '(' CURSOR ',' EXPR ')'
          {  jettison(); do_action($1, $3, $5); } 
        | QUERY '(' CURSOR ')'
          {  jettison(); do_action($1, $3); }
        | REF '(' CURSOR ',' FIELD ')'
          {  jettison(); do_action($1, $3, $5); }
        | IREF '(' CURSOR ',' FIELD ')'
          {  jettison(); do_action($1, $3, $5); }

        /* Link operations. */

        | ENDC '(' CURSOR ',' CURSOR ',' LSTATE ')'
          {  jettison(); do_action($1, $3, $5, $7); } 
        | ENDP '(' CURSOR ',' CURSOR ',' LSTATE ')'
          {  jettison(); do_action($1, $3, $5, $7); } 
        | RELATED '(' CURSOR ',' CURSOR ',' LSTATE ')'
          {  jettison(); do_action($1, $3, $5, $7); } 

        /* Adhoc operations that return values. (BJG) */

        | ADHOC adhoc_id adhoc_actual_args
          {  jettison(); do_adhoc_action($2, $3);  } 
        ;

/*****************************************************************************/
/*                  ckeyword.                                                */
/*****************************************************************************/
  
/* Here are the translations of xp keywords when they appear within %{ %}. */

ckeyword:
        CURSOR 
          {  ckeyword_action("(cursor%d->expr)", NULL,
                             NULL, get_param_num($1));
          }
        | CONTAINER 
          {  ckeyword_action("(container%d->expr)", "(cursor%d->cont)",
                             NULL, get_param_num($1));
          }
        | CONTAINER_ID
          {  ckeyword_action("\"%%%%d\", container%d->container_id",
                             "\"%%%%d\", cursor%d->container_id",
                             NULL, get_param_num($1));
          }
        | CONTAINER_TYPE 
          {  ckeyword_action("(container%d->type)", "(cursor%d->cont_type)",
                             NULL, get_param_num($1));
          }
        | CURSOR_ID
          {  ckeyword_action("\"%%%%d\", cursor%d->cursor_id", NULL,
                             NULL, get_param_num($1));
          }
        | PREDICATE
          {  ckeyword_action("cursor%d->predicate", NULL,
                             NULL, get_param_num($1));
          }
        | ORIG_TYPE
          {  ckeyword_action("container%d->orig_type", "cursor%d->orig_type",
                             NULL, get_param_num($1)); 
          }
        | OBJ_TYPE  
          {  ckeyword_action("container%d->obj_type", "cursor%d->obj_type",
                             NULL, get_param_num($1));
          }
        | CURSOR_TYPE 
          {  ckeyword_action("cursor%d->type", NULL,
                             NULL, get_param_num($1));
          }
        | RECORD
          {  ckeyword_action("record->expr", NULL, NULL);
          }
        | PADOT IDENTIFIER 
          {
#if 0
            ckeyword_action("((struct %s_annote *)(te->annotation))->%s", NULL,
                            NULL, layer_name, $2);
#else
            assert($2 != NULL);
            ckeyword_action(
              "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s", NULL,
              NULL, layer_name, xp_container_id(), xp_container_name(), $2);
#endif
          }
        | CRSTATE IDENTIFIER
          {  ckeyword_action("cs->%s", NULL, NULL, $2);
          }
        | CNSTATE IDENTIFIER
          {  ckeyword_action("ks->%s", NULL, NULL, $2);
          }
        | VALUE IDENTIFIER
          {  ckeyword_action("\"%%%%s\", %s", NULL, NULL, $2);
          }
        | EXPR
          {  /* expr is a parse tree (NODE *).  Thus, it would be
                awarkward and inefficient to use ckeyword_action here,
                since (1) we would have to flatten expr in order to
                pass it to ckeyword_action, and (2) ckeyword_action
                would immediately convert expr back into a parse
                tree. (JAT) */
             char s[MAX_IDENT_LEN+10];
             jettison();
             sprintf(s, "NONTERM(expr%d);", get_param_num($1));
             out(s);
          }
        | FIELD
          {  ckeyword_action("\"%%%%s\", %s", NULL, NULL, "field");
          }
        | ORDERBY_FIELD
          {  ckeyword_action("cursor%d->orderby_field", NULL,
                             NULL, get_param_num($1));
          }
        | ORDERBY_DIRECTION 
          {  ckeyword_action("cursor%d->orderby_direction", NULL,
                             NULL, get_param_num($1));
          }
        | P2_RETRIEVAL_DIRECTION
          {  ckeyword_action("cursor%d->retrieval_direction", NULL,
                             NULL, get_param_num($1));
          }
        | VPTOK
          {  ckeyword_action("vp%d", NULL, NULL, get_param_num($1));
          }

        /* Transaction keywords. */
        /* See analogous code for ikeyword_action() */

        | SCHEMA
          {  ckeyword_action(
#if 0
             /* schema is an error if not a schema container or cursor. */
             "(container%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"container->schema"
               " is un-initialized, cannot expand schema\")"
               ": container%d->schema",
             "(cursor%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"cursor->schema"
               " is un-initialized, cannot expand schema\")"
               ": cursor%d->schema",
#else
             /* schema is the empty string (schema[0] == '\0') if not
                 a schema container or cursor. */
             "container%d->schema", "cursor%d->schema",
#endif
             "schema%d->expr",
             get_param_num($1), get_param_num($1));
          }

        /* Link keywords. */

        | LINKPREDICATE
          {  ckeyword_action("lstate%d->linkpredicate", NULL,
                             NULL, get_param_num($1));
          }
        | LINKLAYER
          {  ckeyword_action("lstate%d->linklayer", NULL,
                             NULL, get_param_num($1));
          }
        | LINKANNOTE
          {  ckeyword_action("((struct %s_annote *)(lstate%d->linkannote))",
                             layer_name, NULL, get_param_num($1));
          }
        | LINKNAME
          {  ckeyword_action("lstate%d->linkname", NULL,
                             NULL, get_param_num($1));
          }
        ;

/*****************************************************************************/
/*                  cprocs.                                                  */
/*****************************************************************************/

/* xp procs that can be called within %{ %} */

cprocs:
        INIT_CONT '(' CONTAINER ')' 
         { opcall1(INIT_CONT_OP, $1, $3); }
        | C_PUT_OP_VEC '(' CURSOR ')'
         { opcall1(C_PUT_OP_VEC_OP, $1, $3); }
        | C_VERBATIM '(' CURSOR ')'
         { opcall1(C_VERBATIM_OP, $1, $3); }
        | K_PUT_OP_VEC '(' CURSOR ')'
         { opcall1(K_PUT_OP_VEC_OP, $1, $3); }
        | K_VERBATIM '(' CONTAINER ')' 
         { opcall1(K_VERBATIM_OP, $1, $3); }
        | S_PUT_OP_VEC '(' CURSOR ')'
         { opcall1(S_PUT_OP_VEC_OP, $1, $3); }
        | S_VERBATIM '(' SCHEMA ')'
         { opcall1(S_VERBATIM_OP, $1, $3); }
/*
        | L_VERBATIM '(' ')'
         { opcall0(S_VERBATIM_OP, $1); }
*/
        | INIT_CURS '(' CURSOR ')'
         { opcall1(INIT_CURS_OP, $1, $3); }
        | OPEN_CONT '(' CONTAINER ')'
         { opcall1(OPEN_CONT_OP, $1, $3); }
        | OPEN_CONT_NUMBER '(' CONTAINER ',' EXPR ')'
         { opcall2(OPEN_CONT_NUMBER_OP, $1, $3, $5); }
        | CHECKPOINT_CONT '(' CONTAINER ')'
         { opcall1(CHECKPOINT_CONT_OP, $1, $3); }
        | CLOSE_CONT '(' CONTAINER ')'
         { opcall1(CLOSE_CONT_OP, $1, $3); }
        | INSERT '(' CURSOR ',' RECORD ')' 
         { opcall2(INSERT_OP, $1, $3, $5); }
        | VARINSERT '(' CURSOR ',' RECORD ',' EXPR ')' 
         { opcall3(VARINSERT_OP, $1, $3, $5, $7); }
        | INSERT '(' CURSOR ',' IDENTIFIER ')' 
         { out("{"
               "REC_ARG P2_rec;"
               "strcpy(P2_rec.expr,\"%s\");", $5);
           opcall2(INSERT_OP, $1, $3, "&P2_rec");
           out("}");
         }
        | INSERT '(' CURSOR ',' VALUE IDENTIFIER ')'
         { out("{"
               "REC_ARG P2_rec;"
               "strcpy(P2_rec.expr,%s);", $6);
           opcall2(INSERT_OP, $1, $3, "&P2_rec");
           out("}");
         }
        | ADV '(' CURSOR ')' 
         { opcall1(ADV_OP, $1, $3); }
        | UPD '(' CURSOR ',' FIELD ',' EXPR ')' 
         { opcall3(UPD_OP, $1, $3, $5, $7); }
        | FOREACH '(' CURSOR ',' EXPR ')'
         { opcall2(FOREACH_OP, $1, $3, $5); }
        | FOREACH '(' CURSOR ')' 
         { out("P2_before_foreach = P2_result;"
               "P2_result = 0;"
               "{"
               "NODE *P2_before_foreach = 0;"
               "NODE *P2_after_foreach;");
         }
         ctoken_stmts END_FOREACH
         { out("P2_after_foreach = P2_result;"
               "P2_result = 0;");
           opcall2(FOREACH_OP, $1, $3, "P2_after_foreach");
           out("}"
               "P2_result = nonterm(UNT,NULL,2,P2_before_foreach,P2_result);");
         }
        | ROFEACH '(' CURSOR ',' EXPR ')'
         { opcall2(ROFEACH_OP, $1, $3, $5); }
        | ROFEACH '(' CURSOR ')' 
         { out("P2_before_foreach = P2_result;"
               "P2_result = 0; {"
               "NODE *P2_before_foreach = 0;"
               "NODE *P2_after_foreach;");
         }
         ctoken_stmts END_ROFEACH
         { out("P2_after_foreach = P2_result;"
               "P2_result = 0;");
           opcall2(ROFEACH_OP, $1, $3, "P2_after_foreach");
           out("}"
               "P2_result = nonterm(UNT,NULL,2,P2_before_foreach,P2_result);");
         }
        | REV '(' CURSOR ')' 
         { opcall1(REV_OP, $1, $3); }
        | REF '(' CURSOR ',' IDENTIFIER ')'
         { opcall2(REF_OP, $1, $3, $5); }
        | DELETE '(' CURSOR ')'  
         { opcall1(DELETE_OP, $1, $3); }
        | DELETE_CURS '(' CURSOR ')'  
         { opcall1(DELETE_CURS_OP, $1, $3); }
        | RESET_START '(' CURSOR ')' 
         { opcall1(RESET_START_OP, $1, $3); }
        | RESET_END '(' CURSOR ')'  
         { opcall1(RESET_END_OP, $1, $3); }
        | SWAP '(' CURSOR ',' CURSOR ')' 
         { opcall2(SWAP_OP, $1, $3, $5); }
        | SYNC_CONT '(' CONTAINER ',' EXPR ',' EXPR ',' EXPR ')'
         { opcall4(SYNC_CONT_OP, $1, $3, $5, $7, $9); }
        | GETREC '(' CURSOR ',' RECORD ')' 
         { opcall2(GETREC_OP, $1, $3, $5); }
        | CALL IDENTIFIER '(' CURSOR opt_literal ')'
         {  jettison();
            if (strcmp($5,"") == 0)
              out("NONTERM(%s(te, %s));", $2, $4);
            else
              out("NONTERM(%s(te, %s, %s));", $2, $4, $5);
         }
        | CALL IDENTIFIER '(' CONTAINER opt_literal ')'
         {  jettison();
            if (strcmp($5,"") == 0)
              out("NONTERM(%s(te, %s));", $2, $4);
            else
              out("NONTERM(%s(te, %s, %s));", $2, $4, $5);
         }

        /* Transaction operations. */

        | OPEN_SCHEMA '(' SCHEMA ')'
         { opcall1(OPEN_SCHEMA_OP, $1, $3); }
        | INIT_SCHEMA '(' SCHEMA ')'
         { opcall1(INIT_SCHEMA_OP, $1, $3); }
        | CLOSE_SCHEMA '(' SCHEMA ')'
         { opcall1(CLOSE_SCHEMA_OP, $1, $3); }

        | ABORT_XACT '(' SCHEMA ')'
         { opcall1(ABORT_XACT_OP, $1, $3); }
        | BEGIN_XACT '(' SCHEMA ')'
         { opcall1(BEGIN_XACT_OP, $1, $3); }
        | COMMIT_XACT '(' SCHEMA ')'
         { opcall1(COMMIT_XACT_OP, $1, $3); }
        | CHECKPOINT_SCHEMA '(' SCHEMA ')'
         { opcall1(CHECKPOINT_SCHEMA_OP, $1, $3); }

        /* Link operations. */

        | RESETC     '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(RESETC_OP, $1, $3, $5, $7); }
        | RESETP     '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(RESETP_OP, $1, $3, $5, $7); }
        | ADVC       '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(ADVC_OP, $1, $3, $5, $7); }
        | ADVP       '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(ADVP_OP, $1, $3, $5, $7); }
        | FOREACHL   '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR ')'
         { opcall4(FOREACHL_OP, $1, $3, $5, $7, $9); }
        | FOREACHC   '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR  ')'
         { opcall4(FOREACHC_OP, $1, $3, $5, $7, $9); }
        | FOREACHP   '(' CURSOR ',' CURSOR ',' LSTATE ',' EXPR ')'
         { opcall4(FOREACHP_OP, $1, $3, $5, $7, $9); }
        | CONNECT    '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(CONNECT_OP, $1, $3, $5, $7); }
        | DISCONNECT '(' CURSOR ',' CURSOR ',' LSTATE ')'
         { opcall3(DISCONNECT_OP, $1, $3, $5, $7); }
        ;

/*****************************************************************************/
/*                  Parsing adhoc calling functions.                         */
/*****************************************************************************/

adhoc_actual_args:
         '(' ')'
           { $$ = NULL; }
         | '(' 
           { adhoc_arg = NULL;  } 
           adhoc_actual_arg_list ')'
           { $$ = adhoc_arg; } 
         ;

adhoc_actual_arg_list:
         adhoc_actual_arg
         | adhoc_actual_arg_list ',' adhoc_actual_arg
         ;

adhoc_actual_arg:
         CURSOR
             { adhoc_arg = append_arg(adhoc_arg, $1); }
         | CONTAINER
             { adhoc_arg = append_arg(adhoc_arg, $1); }
         | VPTOK
             { adhoc_arg = append_arg(adhoc_arg, $1); }
         ;

/*****************************************************************************/
/*                  Update statement.                                        */
/*****************************************************************************/

/*
  update statements are a big kludge in xp.  Any ctoken
  statement starting with a ref '=' expr is assumed to be
  an xp update proc.  Note that embedded assignment statements
  or increments (++) or decrements (--) are not recognized
  as updates.  Consequently, these statements are not 
  translated properly.

  Another kludge is also present.  Initially we were assuming
  that any ref = expr; was an update.  In fact, this is not
  true.  cursor.obj = expr must be translated into a position
  call; cursor.field = expr (where field is a field of the cursor
  and not of the element) can be generated directly.

  And can anyone explain why the update rule is: 
  "ref = left_hand_side" instead of "ref = right_hand_side"? (BJG)
*/

update:
        ref '=' 
         { out("P2_lhs_rf = P2_rf;");
           out("P2_previous = P2_result;");
           out("P2_result = NULL;");
           lhs_pnum         = pnum;
           lhs_cnum         = cnum;
           lhs_rparam       = realm_param;
           lhs_field        = rf_field;
           lhs_cursor_field = cursor_field || force_field_ref;
           lhs_unknown_fld  = unknown_fld;
           lhs_obj_field    = obj_field;
         }
         left_hand_side 
         { jettison();
           if (lhs_cursor_field && !lhs_obj_field) {
              /* generate the code directly without calling the lower layer */
              out("{"
                  "NODE *rhs = P2_result;"
                  "P2_result = P2_previous;"
                  "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                  "rhs,terminal_string1(\";\")));"
                  "}");
           }
           if (lhs_cursor_field && lhs_obj_field) {
               /* generate a call to position */ 
              if (call_below(POS_OP, lhs_pnum)) {
                 out("{"
                     "CURS_ARG c;"
                     "NODE *rhs;"
                     "memcpy(&c,cursor%d,sizeof(CURS_ARG));", lhs_cnum);
                 /* P2_result has parse tree of rhs of assignment statement
                    P2_previous has parse tree of everything prior to statement
                    P2_lhs_rf has parse tree of right-hand side of assignment */
                 out("rhs = P2_result;"
                     "P2_result = P2_previous;");
                 /* now set the new cursor's position to the lhs */
                 out("sprint_ptree(c.expr,P2_lhs_rf);");
                 /* P2_lhs_rf has ".obj" attached to it. remove it */
                 out("c.expr[strlen(c.expr)-4] = '\\0';"
                     "NONTERM(call_down(te, %d, POS_OP, 2, &c, rhs));",
                     lhs_pnum);
                 out("}");
              }
              else {
                /* generate the code directly w/out calling the lower layer */
                out("{"
                    "NODE *rhs = P2_result; P2_result = P2_previous;"
                    "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                    "rhs,terminal_string1(\";\")));"
                    "}");
              }
           }
           if (!lhs_cursor_field) {
             out("{"
                 "NODE *rhs = P2_result; P2_result = P2_previous;"
                 "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                 "rhs,terminal_string1(\";\")));"
                 "}");
           }
         }
       ;

left_hand_side:
        ctoken
        | left_hand_side ctoken
        ;

/*****************************************************************************/
/*                  no_update.                                               */
/*****************************************************************************/

/*
   A no-update ctoken statement is yet another wonderful hack
   in xp.  it is a sequence of ctokens that does NOT begin
   with "ref".  n_upd makes sure that the sequence of tokens
   is jettisoned, no matter how long (or short) the sequence is.
   (DSB)
*/

no_update:
         n_upd 
           {  jettison();
           }

n_upd:
         ctoknr 
         | ctoknr left_hand_side
         ;

/*****************************************************************************/
/*                  Declaration.                                             */
/*****************************************************************************/

/*
   Used only within xform bodies.  member_type is a string variable 
   that contains the expression that returns the IDENT handle to 
   the referenced structure.  NULL is supplied if no structure is 
   referenced.
*/
    
declaration:
        STRUCT structure identifier_declarator 
          {  strcpy(member_type, $2);
             left_expand(member_ctype, new_ptype(STR, UND, NULL));
          }
        | IDENTIFIER identifier_declarator
          {  identifier_declaration_action($1);
          }
        | PADOT IDENTIFIER identifier_declarator
          {  parse_warning(3, "Don't know how to process this statement");
          }
        ;

identifier_declarator:
        unary_identifier_declarator
        | paren_identifier_declarator
        ;

unary_identifier_declarator:
        postfix_identifier_declarator
        | '*' identifier_declarator
          { left_expand(member_ctype, new_ptype(PTR, UND, NULL));
          }
        ;

postfix_identifier_declarator:
        paren_identifier_declarator postfixing_abstract_declarator
        | '(' unary_identifier_declarator ')'
        | '(' unary_identifier_declarator ')' postfixing_abstract_declarator
        ;
 
paren_identifier_declarator:
        IDENTIFIER
          { strcpy(member_name, $1);
            know_member_name = TRUE;
          }
        | PADOT IDENTIFIER
          {
#if 0
            sprintf(member_name, "((struct %s_annote *)(te->annotation))->%s",
                    layer_name, $2);
#else
            assert($2 != NULL);
            sprintf(member_name,
                    "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                    layer_name, xp_container_id(), xp_container_name(), $2);
#endif
            know_member_name = FALSE;
          }
        | VALUE IDENTIFIER
          { strcpy(member_name, $2); 
            know_member_name = FALSE;
          }
        | '(' paren_identifier_declarator ')'
        ;
 
postfixing_abstract_declarator:
        array_abstract_declarator
        | '(' ')' 
          { left_expand(member_ctype, new_ptype(FUN, UND, NULL));
          }
        ;   
 
array_abstract_declarator:
        '[' ']'
          { left_expand(member_ctype, new_ptype(ARR, UND, NULL));
          }
        | '[' constant_expression ']'
          { left_expand(member_ctype, new_ptype(ARR, UND, $2));
          }
        | array_abstract_declarator '[' constant_expression ']'
          { left_expand(member_ctype, new_ptype(ARR, UND, $3));
          }
        ;   

constant_expression:
        PADOT IDENTIFIER 
          {
            char s[MAX_IDENT_LEN*4+10];
#if 0
             sprintf(s, "terminal_string(((struct %s_annote *)"
                     "(te->annotation))->%s)", layer_name, $2);
#else
             assert($2 != NULL);
             sprintf(s, "terminal_string("
               "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s)",
               layer_name, xp_container_id(), xp_container_name(), $2);
#endif
             $$ = terminal_string(s);
          }
        | IDENTIFIER
          {  $$ = terminal_string($1);
          }
        | LITERAL
          {  $$ = terminal_string($1);
          }
        | VALUE IDENTIFIER
          {  char s[MAX_IDENT_LEN];
             sprintf(s, "terminal_string(%s)", $2);
             $$ = terminal_string(s);
          }
        ;
%%

/*****************************************************************************/
/*                  End of Grammar.                                          */
/*****************************************************************************/

void
yyerror (char *string)
{
  parse_error("%s at \"%s\"", string, yytext);
}

int
yywrap (void)
{
  static int guard = 0;
  int i, alldone;
  
  if (!guard) { 
    FILE *fp1 = fopen(cdef_name, "r");
    FILE *fp2 = fopen(kdef_name, "r");
    if (!fp1 && !fp2) 
      return(1); /* Quit.  No defaults. (BJG) */
    guard = 1;
  }

  if (yyin) 
    fclose(yyin);
  
  alldone = 1;
  for(i = 0; op_tab[i].op_num; i++) { 
    int op = op_tab[i].op_num;
    if (op_exists_in_realm(op,layer_realm) && !seen[op]) { 
      if (retrieval_op(op) && !retrieval) { 
        continue;
        /* Don't generate retrieval ops for non-retrieval layers. (BJG) */
      }

      if (op_tab[i].param[0] == CUR)
        yyin = fopen(cdef_name,"r");
      else if (op_tab[i].param[0] == CON)
        yyin = fopen(kdef_name,"r");
      else
        continue; /* Got one of them weird functions. (BJG) */

      if (!yyin)
        continue; /* We don't have a spec. Try the next entry. (BJG) */

      seen[op] = TRUE;
      current_op = i;
      return(0); 
    }
  }
  return(alldone);
}
