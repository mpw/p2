%{

/* $Id: pb-gram.y,v 45.0 1997/09/19 05:45:52 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* pb grammar (bison source file). */

/*

Derived from a grammar by James A. Roskind (1990), version 1.0.  
Original comments are retained for documentation purposes (DSB).

PREDATOR additions by JAT.

*/

/*

This refined grammar resolves several typedef ambiguities  in  the
draft  proposed  ANSI  C  standard  syntax  down  to  1  shift/reduce
conflict, as reported by a YACC process.  Note  that  the  one  shift
reduce  conflict   is the traditional if-if-else conflict that is not
resolved by the grammar.  This ambiguity can  be  removed  using  the
method  described in the Dragon Book (2nd edition), but this does not
appear worth the effort.

There was quite a bit of effort made to reduce the conflicts to  this
level,  and  an  additional effort was made to make the grammar quite
similar to the C++ grammar being developed in  parallel.   Note  that
this grammar resolves the following ANSI C ambiguity as follows:

ANSI  C  section  3.5.6,  "If  the [typedef name] is redeclared at an
inner scope, the type specifiers shall not be omitted  in  the  inner
declaration".   Supplying type specifiers prevents consideration of T
as a typedef name in this grammar.  Failure to supply type specifiers
forced the use of the TYPEDEFname as a type specifier.

ANSI C section 3.5.4.3, "In a parameter declaration, a single typedef
name in parentheses is  taken  to  be  an  abstract  declarator  that
specifies  a  function  with  a  single  parameter,  not as redundant
parentheses around the identifier".  This is extended  to  cover  the
following cases:

typedef float T;
int noo(const (T[5]));
int moo(const (T(int)));
...

Where  again the '(' immediately to the left of 'T' is interpreted as
being the start of a parameter type list,  and  not  as  a  redundant
paren around a redeclaration of T.  Hence an equivalent code fragment
is:

typedef float T;
int noo(const int identifier1 (T identifier2 [5]));
int moo(const int identifier1 (T identifier2 (int identifier3)));
...

(James A. Roskind)

*/

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <string.h>       /* strcat() needed by yyparse() */

#include "compcurs.h"     /* pre_opt_compcurs_decl() */
#include "error.h"        /* parse_error() */
#include "io.h"           /* print_ptree(), print_liner_pragma */
#include "pb-actions.h"   /* identifier_expression_nonterm() */
#include "pb-io.h"        /* direction_string() */
#include "pb-type.h"      /* copy_ctype() */
#include "pb-xform.h"     /* FOREACH_MEMBER */
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* terminal() */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

#define YYDEBUG 1                    /* Pretty debugging code. */
#define YYDEBUG_LEXER_TEXT (yylval)  /* Our lexer loads this up each time. */
#define YYERROR_VERBOSE 1 /* define as anything for verbose BISON errors. */
#define YYPRINT(file, type, value) \
     yyprint(file, type, value)

/*****************************************************************************/
/*                  Local forward references                                 */
/*****************************************************************************/

int  yylex(void);
void yyerror(char *s);

#if YYDEBUG
static void yyprint();
#endif

%}
 
/*****************************************************************************/
/*                  Tokens                                                   */
/*****************************************************************************/

/* Keywords. */
%token AUTO            DOUBLE          INT             STRUCT
%token BREAK           ELSE            LONG            SWITCH
%token CASE            ENUM            REGISTER        TYPEDEF
%token CHAR            EXTERN          RETURN          UNION
%token CONST           FLOAT           SHORT           UNSIGNED
%token CONTINUE        FOR             SIGNED          VOID
%token DEFAULT         GOTO            SIZEOF          VOLATILE
%token DO              IF              STATIC          WHILE

/* Operation literals. */ 
%token COMMA DOT STAR COLON SEMICOLON
%token ASSIGN AND PLUS MINUS NEGATE NOT DIV MOD LT GT
%token XOR PIPE QUESTION
/* () { } [ ] */ 
/* It is useful to use symbolic names for parens and brackets,
   so that the emacs matching routines don't get confused. (JAT) */
%token LP RP LC RC LB RB

/* PREDATOR additions. */
%token VARCHAR
%token CURSOR          GENERIC_CURSOR
%token CONTAINER       GENERIC_CONTAINER
%token SCHEMA          STORED_AS       WHERE
%token FOREACH         FOREACHK        ROFEACH
%token ASCENDING       DESCENDING      ORDERBY
%token ELEMENT         COMPCURS        GIVEN           VALID
%token P2_DDLHINT      P2_PATH         P2_TYPEX
%token DOLLAR

/* GNU additions. */
%token ATTRIBUTE
%token INLINE
%token LABEL
%token TYPEOF
%token ASM

/* ANSI Grammar suggestions. */
%token IDENTIFIER              STRINGliteral
%token FLOATINGconstant        INTEGERconstant         CHARACTERconstant

/* New Lexical element, whereas ANSI suggested non-terminal. (JAR) */

%token TYPEDEFname /* Lexer will tell the difference between this and
    an  identifier!   An  identifier  that is CURRENTLY in scope as a
    typedef name is provided to the parser as a TYPEDEFname. */

/* Multi-Character operators. */
%token  ARROW            /*    ->                              */
%token  INCR DECR        /*    ++      --                      */
%token  LS RS            /*    <<      >>                      */
%token  LE GE EQ NE      /*    <=      >=      ==      !=      */
%token  ANDAND OROR      /*    &&      ||                      */
%token  ELLIPSIS         /*    ...                             */

/* Modifying assignment operators. */
%token MULTassign  DIVassign    MODassign   /*   *=      /=      %=      */
%token PLUSassign  MINUSassign              /*   +=      -=              */
%token LSassign    RSassign                 /*   <<=     >>=             */
%token ANDassign   ERassign     ORassign    /*   &=      ^=      |=      */

/*************************************************************************/

%union {
  NODE    *n;
  int      i;
}

/* Tokens. */
%type <n> TYPEDEFname 
%type <n> IDENTIFIER
%type <n> STRINGliteral FLOATINGconstant INTEGERconstant CHARACTERconstant
%type <n> BREAK CASE CONTINUE DEFAULT DO ELSE FOR GOTO
%type <n> IF RETURN SIZEOF SWITCH WHILE
%type <n> CONST VOLATILE TYPEDEF EXTERN
%type <n> STATIC AUTO REGISTER INT CHAR SHORT LONG
%type <n> FLOAT DOUBLE SIGNED UNSIGNED VOID STRUCT
%type <n> UNION ELLIPSIS ENUM 

/* Operation literals. */
%type <n> MULTassign  DIVassign MODassign PLUSassign  MINUSassign 
%type <n> LSassign    RSassign  ANDassign   ERassign     ORassign
%type <n> ARROW INCR DECR LS RS LE GE EQ NE ANDAND OROR 
%type <n> LP RP LC RC LB RB COMMA DOT STAR COLON SEMICOLON
%type <n> ASSIGN AND PLUS MINUS NEGATE NOT DIV MOD LT GT
%type <n> XOR PIPE QUESTION

/* PREDATOR additions */
%type <n> VARCHAR
%type <n> ASCENDING CONTAINER CURSOR DESCENDING
%type <n> DOLLAR
%type <n> GENERIC_CONTAINER GENERIC_CURSOR ORDERBY SCHEMA
%type <n> FOREACH FOREACHK ROFEACH
%type <n> ELEMENT COMPCURS GIVEN VALID
%type <n> STORED_AS P2_DDLHINT P2_PATH P2_TYPEX WHERE

/* GNU additions */
%type <n> ATTRIBUTE
%type <n> INLINE
%type <n> LABEL
%type <n> TYPEOF
%type <n> ASM

/* Declarations. */
%type <n> default_declaring_list declaring_list declaration_specifier 
%type <n> type_specifier declaration_qualifier_list type_qualifier_list 
%type <n> declaration_qualifier type_qualifier basic_declaration_specifier 
%type <n> basic_type_specifier sue_declaration_specifier sue_type_specifier 
%type <n> typedef_declaration_specifier typedef_type_specifier storage_class
%type <n> basic_type_name elaborated_type_name aggregate_name aggregate_key 
%type <n> member_declaration_list member_declaration
%type <n> member_default_declaring_list 
%type <n> member_declaring_list member_declarator member_identifier_declarator 
%type <n> bit_field_size_opt bit_field_size enum_name enumerator_list 
%type <n> enumerator_value_opt parameter_type_list parameter_list 
%type <n> parameter_declaration identifier_list identifier_or_typedef_name 
%type <n> type_name initializer_opt initializer initializer_list

/* PREDATOR additions */
%type <n> declaration1
%type <n> ddlhint_list_opt ddlhint_list ddlhint
%type <n> cursor_container_pair_list_opt cursor_container_pair_list
%type <n> given_opt schema_type

/* Externs. */
%type <n> translation_unit external_definition declaration function_definition
%type <n> declarator typedef_declarator parameter_typedef_declarator
%type <n> clean_typedef_declarator clean_postfix_typedef_declarator
%type <n> paren_typedef_declarator paren_postfix_typedef_declarator
%type <n> simple_paren_typedef_declarator identifier_declarator
%type <n> unary_identifier_declarator postfix_identifier_declarator
%type <n> paren_identifier_declarator old_function_declarator
%type <n> postfix_old_function_declarator abstract_declarator
%type <n> postfixing_abstract_declarator array_abstract_declarator
%type <n> unary_abstract_declarator postfix_abstract_declarator

/* Expressions and statements. */
%type <n> constant string_literal_list primary_expression
%type <n> postfix_expression member_name argument_expression_list
%type <n> unary_expression unary_operator cast_expression
%type <n> multiplicative_expression additive_expression 
%type <n> shift_expression relational_expression equality_expression
%type <n> AND_expression exclusive_OR_expression 
%type <n> inclusive_OR_expression logical_AND_expression
%type <n> logical_OR_expression conditional_expression
%type <n> assignment_expression assignment_operator
%type <n> comma_expression constant_expression comma_expression_opt
%type <n> statement labeled_statement compound_statement
%type <n> declaration_list statement_list expression_statement
%type <n> selection_statement iteration_statement jump_statement
 
/* PREDATOR additions. */
%type <n> foreach_or_rofeach
%type <n> left_brace right_brace left_paren right_paren
%type <n> predicate_opt valid_opt orderby_opt
%type <i> direction

/* GNU additions */
%type <n> attribute_opt attribute_list attribute
%type <n> label_list
%type <n> comma_expression_or_typedef_name
%type <n> asm_statement asm_op_desc_opt
%type <n> asm_op_list_opt asm_op_list asm_op
%type <n> asm_name_opt

/* Start symbol. */
%start translation_unit

/* Eliminate shift-reduce warning for:
     (1) if if else shift-reduce conflict.
     (2) long long shift-reduce conflict.
     (3) long double shift-reduce conflict.
   Note: we have worked very hard to eliminate shift-reduce conflicts.
   Introduce new ones only as a last resort. (JAT) */
/* %expect 3 */

%%

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

constant:
        /* We are not including ENUMERATIONconstant here  because  we
           are  treating  it like a variable with a type of "enumeration
           constant".  */
        FLOATINGconstant
        | INTEGERconstant
        | CHARACTERconstant
        ;

string_literal_list:
        STRINGliteral
        | string_literal_list STRINGliteral
          {  $$ = string_literal_list_action( $1, $2 );
          }
        ;


/*****************************************************************************/
/*                  Expressions.                                             */
/*****************************************************************************/

primary_expression:
        IDENTIFIER
          {  $$ = identifier_expression_nonterm($1);
          }
        /* GNU addition: labels as values */
        | ANDAND IDENTIFIER
          {  $$ = nonterm(TYP, pointer_void_read_only_ctype, 2, $1, $2);
          }
        | constant
        | string_literal_list
        | LP comma_expression RP
          {  $$ = nonterm(TYP, $2->ident->ctype, 3, $1, $2, $3);
          }
        /* GNU addition: statement expressions */
        | LP compound_statement RP
          {  CTYPE *c;
             if ($2->ident->eclass == UNT)
               c = void_read_only_ctype;
             else
               c = $2->ident->ctype;
             $$ = nonterm(TYP, c, 3, $1, $2, $3);
          }
        | LP error RP 
          {  CTYPE *c = int_read_only_ctype;
             NODE *n = terminal1(TYP, "1", c);
             warning(4, "couldn't parse expression--setting it to 1");
             $$ = nonterm(TYP, c, 3, $1, n, $3);
          }
        ;

postfix_expression:
        primary_expression
        | postfix_expression LB comma_expression RB
          {  CTYPE *c = copy_ctype($1->ident->ctype);
             reduce(c, ARR);
             $$ = nonterm(TYP, c, 4, $1, $2, $3, $4);
          }
        | postfix_expression LP RP
          {  CTYPE *c = copy_ctype($1->ident->ctype);
             reduce(c, FUN);
             $$ = nonterm(TYP, c, 3, $1, $2, $3);
          }
        | postfix_expression LP argument_expression_list RP
          {  $$ = function_call_nonterm($1, $3);
          }
        | postfix_expression DOT member_name
          {  $$ = dot_member_nonterm($1, $3);
          }
        | postfix_expression ARROW member_name
          {  $$ = arrow_member_nonterm($1, $3);
          }
        | postfix_expression INCR
           {  CTYPE *c = $1->ident->ctype;
              $$ = nonterm(TYP, c, 2, $1, $2);
           }
        | postfix_expression DECR
           {  CTYPE *c = $1->ident->ctype;
              $$ = nonterm(TYP, c, 2, $1, $2);
           }
        ;

member_name:
        IDENTIFIER 
         { /* Node is untyped */
#if 0
             $1->ident->ctype = UNDEFINED_CTYPE;
#else
             $1->ident->ctype = undefined_read_only_ctype;
#endif
         }
        | TYPEDEFname
         { /* Node is untyped */
#if 0
             $1->ident->ctype = UNDEFINED_CTYPE;
#else
             $1->ident->ctype = undefined_read_only_ctype;
#endif
         }
        ;

argument_expression_list:
        assignment_expression
        | argument_expression_list COMMA assignment_expression
         {  $$ = nonterm(TYP, $3->ident->ctype, 3, $1, $2, $3);
         }
        ;

unary_expression:
        postfix_expression
        | INCR unary_expression
          {  CTYPE *ctype;
              ctype = $2->ident->ctype;
              $$ = nonterm(TYP, ctype, 2, $1, $2);
           }
        | DECR unary_expression
          {  CTYPE *ctype;
              ctype = $2->ident->ctype;
              $$ = nonterm(TYP, ctype, 2, $2, $2);
           }
        | unary_operator cast_expression
          {  $$ = unary_operator_cast_expression_nonterm($1, $2);
          }
        | SIZEOF unary_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 2, $1, $2);
          }
        | SIZEOF LP    
          {  push_decl();
          }
          type_name RP
          {  $$ = nonterm(TYP, int_read_only_ctype, 4, $1, $2, $4, $5);
             pop_decl();
          }
        ;

unary_operator:
        AND
        | STAR
        | PLUS
        | MINUS
        | NEGATE
        | NOT
        ; 

/* I think that this (that is, at the end of the cast_expression
   productions) is where we should check for certain types,
   if we plan to take special actions for them (JAT). */

cast_expression:
        unary_expression
        | LP 
           {  pre_cast_expression_action();
           }
          type_name RP cast_expression
           {  $$ = post_cast_expression_action($3, $5);
           }
        ;

multiplicative_expression:
        cast_expression
        | multiplicative_expression STAR cast_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        | multiplicative_expression DIV cast_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        | multiplicative_expression MOD cast_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

additive_expression:
        multiplicative_expression
        | additive_expression PLUS multiplicative_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        | additive_expression MINUS multiplicative_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

shift_expression:
        additive_expression
        | shift_expression LS additive_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        | shift_expression RS additive_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

relational_expression:
  /* Need to create a new function relop similar to binop??? (JAT) */
        shift_expression
        | relational_expression LT shift_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 3, $1, $2, $3); }
        | relational_expression GT shift_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 3, $1, $2, $3); }
        | relational_expression LE shift_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 3, $1, $2, $3); }
        | relational_expression GE shift_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 3, $1, $2, $3); } 
        ;

equality_expression:
        relational_expression
        | equality_expression EQ relational_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        | equality_expression NE relational_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

AND_expression:
        equality_expression
        | AND_expression AND equality_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

exclusive_OR_expression:
        AND_expression
        | exclusive_OR_expression XOR AND_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

inclusive_OR_expression:
        exclusive_OR_expression
        | inclusive_OR_expression PIPE exclusive_OR_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

logical_AND_expression:
        inclusive_OR_expression
        | logical_AND_expression ANDAND inclusive_OR_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

logical_OR_expression:
        logical_AND_expression
        | logical_OR_expression OROR logical_AND_expression
          {  $$ = binop_nonterm($1, $2, $3);
          }
        ;

conditional_expression:
        logical_OR_expression
        | logical_OR_expression QUESTION comma_expression COLON
          conditional_expression
          {  CTYPE *c;
             if (!ctypematch($3->ident->ctype, $5->ident->ctype)) {
               parse_warning(4, "conditional expr type mismatch--assuming"
                             " result void");
               c = void_read_only_ctype; /* Assume result void. */
             }
             else
               c = binary_convert($3->ident->ctype, $5->ident->ctype);
             $$ = nonterm(TYP, c, 5, $1, $2, $3, $4, $5);
          }
        ;

assignment_expression:
        conditional_expression
        | unary_expression assignment_operator assignment_expression
          {  $$ = nonterm(TYP, $1->ident->ctype, 3, $1, $2, $3);
          }
        ;

assignment_operator:
        ASSIGN 
        | MULTassign  
        | DIVassign 
        | MODassign 
        | PLUSassign 
        | MINUSassign 
        | LSassign 
        | RSassign 
        | ANDassign 
        | ERassign 
        | ORassign 
        ;

comma_expression:
        assignment_expression
        | comma_expression COMMA assignment_expression
          {  $$ = nonterm(TYP, $3->ident->ctype, 3, $1, $2, $3);
          }
        ;

constant_expression:
        conditional_expression
        ;

/* The following was used for clarity. (JAT) */

comma_expression_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | comma_expression
        ;

/*****************************************************************************/
/*                  Declarations.                                            */
/*****************************************************************************/

    /* The following is different from the ANSI C specified  grammar.
    The  changes  were  made  to  disambiguate  typedef's presence in
    declaration_specifiers (vs.  in the declarator for redefinition);
    to allow struct/union/enum tag declarations without  declarators,
    and  to  better  reflect the parsing of declarations (declarators
    must be combined with declaration_specifiers ASAP  so  that  they
    are visible in scope).

    Example  of  typedef  use  as either a declaration_specifier or a
    declarator:

      typedef int T;
      struct S { T T;}; /* redefinition of T as member name * /

    Example of legal and illegal statements detected by this grammar:

      int; /* syntax error: vacuous declaration * /
      struct S;  /* no error: tag is defined or elaborated * /

    Example of result of proper declaration binding:

        int a=sizeof(a); /* note that "a" is declared with a type  in
            the name space BEFORE parsing the initializer * /

        int b, c[sizeof(b)]; /* Note that the first declarator "b" is
             declared  with  a  type  BEFORE the second declarator is
             parsed * /

    */

declaration:
        declaration1
          {  
            /* HACK: the check for decl->typex_name != NULL is to
               insure that the following code is only executed only
               for schema declarations or schema typedefs, and
               not for declarations of INSTANCES of schema typedefs.

               It just happens to be true that decl->typex_name will be
               non-NULL only in these cases, and I could have chosen some
               other test, such as decl->declared_but_unprinted != NULL,
               but decl->typex_name != NULL seemed most logical, since
               (1) decl->typex_name != NULL seems more fundamental than
               decl->declared_but_unprinted != NULL, and
               (2) the following code depends on decl->typex_name != NULL,
               anyway. (JAT) */

            if (decl->btype->len != 0
                && base_ptype(decl->btype)->pclass == SCH
                && decl->typex_name != NULL)
            {
              if (decl->sclass == TDF)
                parse_error("schema declaration can not be a typedef:"
                            " schema declaration must specify a single,"
                            " plain identifier");
              if (decl->dtype->len != 0)
                parse_error("schema declaration can not be a derrived type:"
                            " schema declaration must specify a single,"
                            " plain identifier");
              /* decl->name is the schema name, e.g. foo_schema. */
              /* decl->btype->ident->name is the schema type struct name,
                   e.g.  P2_unnamed_sue123 */
              post_ddlhint_schema_declaration(decl->name, decl->typex_name);
            }
            save_decl();
#if PRINT_DECL_AS_COMMENT
            $$ = nonterm(UNT, NULL, 4,
                         terminal_string1("/*"),
                         $1,
                         terminal_string1("*/\n"),
                         decl_ptree());
#else
            $$ = decl_ptree();
#endif
            clear_decl();
         }

declaration1:
          /* The production declaration1 -> sue_declaration_specifier
             leads to legal, but useless declarations.  For example,
             the following declares a sue with a type specifier, but
             no instances:
               declaration1
               -> sue_declaration_specifier SEMICOLON
               ...
               -> auto struct s { int i; };
             As soon as we add an instance, this production is no
             longer used:
               declaration1
               -> declaring_list SEMICOLON
               ...
               -> auto struct s { int i; } t; */
          sue_declaration_specifier attribute_opt SEMICOLON
        | sue_type_specifier attribute_opt SEMICOLON
        | declaring_list SEMICOLON
        | default_declaring_list SEMICOLON

/* GNU addition: local labels */

        | LABEL label_list SEMICOLON
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }

/* PREDATOR additions */

        /* Type expressions. */
        | P2_TYPEX LP argument_expression_list RP SEMICOLON
          {  typex_declaration($3);  
             $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $4, $5);
#if 0
          }
        /* Un-named schema. */
        | schema_type SEMICOLON
          {  
             unnamed_schema_declaration();
             $$ = nonterm(UNT, NULL, 2, $1, $2);
#endif
          }
       ;

/* GNU addition: local labels */

label_list:
        IDENTIFIER
          {  add_label_to_symtab1($1->ident->name);
             $$ = $1;
          }
        | label_list COMMA IDENTIFIER
          {  add_label_to_symtab1($3->ident->name);
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

/* PREDATOR additions. */
/* A ddlhint_list_opt is a list of zero or more ddlhints. */

ddlhint_list_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | ddlhint_list
        ;

ddlhint_list:
        ddlhint
        | ddlhint_list ddlhint
          {  $$ = nonterm(UNT, NULL, 2, $1, $2); }
        ;

ddlhint:
          P2_DDLHINT LP IDENTIFIER COMMA P2_PATH
          LP argument_expression_list RP COMMA
          string_literal_list COMMA argument_expression_list RP SEMICOLON
          {  ddlhint_declaration($3->ident->name, $7, $10->ident->name, $12);
             $$ = nonterm(UNT, NULL, 12,
                          $1, $2, $3, $4, $5, $6, $7, $8, $10, $11, $12, $13); 
          }     
        ;

/* Note that if a typedef were redeclared, then a declaration
specifier must be supplied. */

default_declaring_list:         /* Can't redeclare typedef names */
        declaration_qualifier_list identifier_declarator
          asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | type_qualifier_list identifier_declarator
          asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | default_declaring_list COMMA
          {  save_decl();
             clear_dtype();
          }
        identifier_declarator asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, $4, $5, $6);
          }
        ;

declaring_list:
        declaration_specifier declarator
        asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | type_specifier declarator
        asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | declaring_list COMMA
          {  
            if (decl->btype->len != 0 && base_ptype(decl->btype)->pclass == SCH)
              parse_error("schema declaration must specify only one instance");
            save_decl();
            clear_dtype();
          }
          declarator asm_name_opt attribute_opt initializer_opt
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, $4, $5, $6);
          }
        ;

declaration_specifier:
        basic_declaration_specifier          /* Arithmetic or void */
        | sue_declaration_specifier          /* Struct/union/enum */
        | typedef_declaration_specifier      /* Typedef */
        ;

type_specifier:
        basic_type_specifier                 /* Arithmetic or void */
        | sue_type_specifier                 /* Struct/Union/Enum */
        | typedef_type_specifier             /* Typedef */
        ;

declaration_qualifier_list:     /* const/volatile, AND storage class */
        storage_class
        | type_qualifier_list storage_class
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_qualifier_list declaration_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

type_qualifier_list:
        type_qualifier
        | type_qualifier_list type_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

declaration_qualifier:
        storage_class
        | type_qualifier          /* const or volatile */
        ;

type_qualifier:
        CONST      { decl->qclass = CTQ; }
        | VOLATILE { decl->qclass = VTQ; }
        ;

basic_declaration_specifier:    /* Storage Class + Arithmetic or void */
        declaration_qualifier_list basic_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | basic_type_specifier  storage_class
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | basic_declaration_specifier declaration_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | basic_declaration_specifier basic_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

basic_type_specifier:
        basic_type_name         /* Arithmetic or void */
        | type_qualifier_list  basic_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | basic_type_specifier type_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | basic_type_specifier basic_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

sue_declaration_specifier:      /* Storage Class + struct/union/enum */
        declaration_qualifier_list  elaborated_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | sue_type_specifier        storage_class
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | sue_declaration_specifier declaration_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

sue_type_specifier:
        elaborated_type_name    /* struct/union/enum */
        | type_qualifier_list elaborated_type_name
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | sue_type_specifier  type_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;


typedef_declaration_specifier:  /* Storage Class + typedef types */
        typedef_type_specifier          storage_class
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_qualifier_list    TYPEDEFname
          {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], $2->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", $2->ident->name);
             i = e->ident;
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                 decl->eclass = OTH;
             $2->ident->eclass = OTH; 
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | typedef_declaration_specifier declaration_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

typedef_type_specifier:         /* typedef types */
        TYPEDEFname
          {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], $1->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", $1->ident->name);
             i = e->ident;
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                decl->eclass = OTH;
             /* Do not propigate type info. */
             $1->ident->eclass = UNT; 
          }
        | type_qualifier_list    TYPEDEFname
          {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], $2->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", $2->ident->name);
             i = e->ident;
             assert(decl->qclass != UND);
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                 decl->eclass = OTH;
             $2->ident->eclass = OTH;
             /* Do not propigate type info. */
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | typedef_type_specifier type_qualifier
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

storage_class:
        TYPEDEF
          { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = TDF;
            decl->eclass = TDF;
          }
        | EXTERN
          { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = EXT;
            decl->eclass = OTH;
          }
        | STATIC
          { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = STA;
            decl->eclass = OTH;
          }
        | AUTO
          { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = AUT;
            decl->eclass = OTH;
          }
        | REGISTER
          { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = REG;
            decl->eclass = OTH;
          }
        | INLINE
          {
          }
        ;

basic_type_name:
        INT           { arithmetic_btype(UND, IN);  }
        | CHAR        { arithmetic_btype(UND, CHA); }
        | VARCHAR     { arithmetic_btype(UND, VCHA); }
        | SHORT       { arithmetic_btype(UND, SHO); }
        | FLOAT       { arithmetic_btype(UND, FLO); }
        | DOUBLE      { arithmetic_btype(UND, DOU); }
        | SIGNED      { arithmetic_btype(SIG, IN); }
        | UNSIGNED    { arithmetic_btype(UNS, IN); }
        | VOID        { arithmetic_btype(UND, VOI); }

/* GNU addition: long long */
/* long long shift-reduce conflict. (JAT) */

        | LONG        { arithmetic_btype(UND, LON); }
        | LONG LONG   { arithmetic_btype(UND, LLON); }

/* long double shift-reduce conflict. (JAT) */

        | LONG DOUBLE { arithmetic_btype(UND, LDOU); }

/* GNU addition: typeof */

/* I have specified that parenthesis are required around the
   the unary_expression in order to avoid shift-reduce conflicts.
   Despite the fact that the documentation for typeof says that the
   syntax looks like `sizeof', i.e., that parenthesis are not
   required, this should be okay since the behavior of gcc requires
   parenthesis. (JAT) */

        | TYPEOF LP unary_expression RP
          {
#if 0
             decl->btype = $3->ident->ctype;
#else
             set_btype($3->ident->ctype);
#endif
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | TYPEOF LP type_name RP
          {  /* decl->btype should already be properly set. */
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }

/* PREDATOR additions. */

/* Element. */

        | ELEMENT LT unary_expression GT
          {  $$ = element_nonterm($3);
          }

/* Cursors. */

        /* regular (non-generic, non-composite) cursor. */
        | CURSOR LT unary_expression GT
          {  pre_opt_cursor_declaration($3); 
          }
          predicate_opt orderby_opt
          {  NODE *n;
             post_opt_cursor_declaration($3);
             n = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
             $$ = nonterm(UNT, NULL, 3, n, $6, $7);
          }
        /* generic cursor. */
        | GENERIC_CURSOR LT type_specifier GT
          {  generic_cursor_declaration($3);
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4); 
          }
        /* composite cursor. */
        | COMPCURS LT cursor_container_pair_list_opt GT
          {  pre_opt_compcurs_declaration();
          }
          given_opt predicate_opt valid_opt orderby_opt
          {  post_opt_compcurs_declaration($3, $6, $8);
             $$ = nonterm(UNT, NULL, 7, $1, $2, $3, $4, $6, $7, $8, $9);
          }

/* Containers. */

        /* schema-member container. */
        | CONTAINER LT type_specifier GT
          {  schema_container_declaration($3);
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        /* regular (non-schema-member, non-generic) container. */
        | CONTAINER LT type_specifier GT
          STORED_AS IDENTIFIER
          {  TE *te = typex_name_to_te($6->ident->name);
             pre_typex_container_declaration($3);
             set_container_cctype_te(decl->btype->cctype, te);
          }
          ddlhint_list_opt
          {  post_ddlhint_container_declaration($6->ident->name);
             $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, $5, $6);
          }
        /* generic container. */
        | GENERIC_CONTAINER LT type_specifier GT
          {  generic_container_declaration($3);
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4); 
          }

/* Schema. */

        | schema_type
        ;

schema_type:
        SCHEMA LC
          {  pre_typex_schema_declaration();
          }        
          member_declaration_list RC
          {  pop_decl();
          }
          STORED_AS IDENTIFIER
          {  post_typex_schema_declaration($8->ident->name);
          }
          ddlhint_list_opt
          {  
             assert(decl->typex_name == NULL);
#if 0
             post_ddlhint_schema_declaration($8->ident->name);
#else
             decl->typex_name = copy_string($8->ident->name);
#endif
             $$ = nonterm(UNT, NULL, 6, $1, $2, $4, $5, $7, $8);
          }
        ;

given_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | GIVEN LT
          {  push_decl();
          }
          identifier_list GT
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $4, $5);
             pop_decl();
          }
        ;

cursor_container_pair_list_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | cursor_container_pair_list
        ;

cursor_container_pair_list:
        IDENTIFIER unary_expression
          {  $$ = nonterm(UNT, NULL, 2,  $1, $2);
          }
        | IDENTIFIER unary_expression COMMA cursor_container_pair_list 
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4); 
          }
        ;

predicate_opt:
        /* Nothing */
          {  predicate_opt_declaration(NULL);
             $$ = empty();
          }
        | WHERE string_literal_list
          {  predicate_opt_declaration($2->ident->name);
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

valid_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | VALID string_literal_list
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

orderby_opt:
        /* Nothing */
           {  orderby_opt_action(0, NULL, NULL);
              $$ = empty();
           }
        | ORDERBY direction IDENTIFIER
          {  orderby_opt_action($2, NULL, $3->ident->name);
             $$ = nonterm(UNT, NULL, 3, $1,
                          terminal_string1(direction_string($2)),
                          $3);
          }
        | ORDERBY direction DOLLAR IDENTIFIER DOT IDENTIFIER
          {  orderby_opt_action($2, $4->ident->name, $6->ident->name);
             $$ = nonterm(UNT, NULL, 6, $1,
                          terminal_string1(direction_string($2)),
                          $3, $4, $5, $6); 
          }
        ;

direction:
        /* Nothing */
          {  /* I have intentionally made this 1 (rather than 0). */
             /* Making this 1 makes ascending the default.  That is:
                "orderby field" is equivalent to "orderby ascending field"
                I don't think that it makes sense to make 0 the default,
                But a reasonable alternative to this is to not accept
                the empty string as a legal direction, in which case:
                "orderby field" is an illegal orderby_opt. (JAT) */
             $$ = 1;
          } 
        | ASCENDING
          {  $$ = 1;
          }
        | DESCENDING
          {  $$ = -1;
          }
        ;

elaborated_type_name:
        aggregate_name
        | enum_name
        ;

aggregate_name:
        aggregate_key LC  
          {  /* Declaration of un-named aggregate. */
             unnamed_aggregate_declaration_action();
          }
          member_declaration_list RC
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $4, $5);
             pop_decl();
          }
        | aggregate_key identifier_or_typedef_name LC  
          {  /* Declaration of named aggregate. */
             named_aggregate_declaration_action($2);
          }
          member_declaration_list RC
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $5, $6);
             pop_decl();
          }
        | aggregate_key identifier_or_typedef_name
          {  /* Reference to aggregate */
             aggregate_reference_action($2);
             /* Do not propigate type info. */
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

aggregate_key:
        STRUCT
          {
#if 0
            decl->btype = STRUCT_CTYPE;
#else
            set_btype(STRUCT_CTYPE);
#endif
          }
        | UNION
          {
#if 0
            decl->btype = UNION_CTYPE;
#else
            set_btype(UNION_CTYPE);
#endif
           }
        ;

/* Here's where the action is in defining the members of an aggregate. (DSB) */

member_declaration_list:
        member_declaration
        |  member_declaration_list member_declaration
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

member_declaration:
        member_declaring_list SEMICOLON
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
            save_decl();
            clear_btype();
        }
        | member_default_declaring_list SEMICOLON
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
            save_decl();
            clear_btype();
          }
        ;

member_default_declaring_list:  /* Doesn't redeclare typedef. */
        type_qualifier_list member_identifier_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | member_default_declaring_list COMMA
          {  save_decl();
             clear_dtype();
          }
          member_identifier_declarator
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $4);
          }
        ;

member_declaring_list:
        type_specifier member_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | member_declaring_list COMMA
          {  save_decl();
             clear_dtype();
          }          
          member_declarator
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $4);
          }
        ;

member_declarator:
        declarator attribute_opt bit_field_size_opt
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | bit_field_size
        ;

member_identifier_declarator:
        identifier_declarator attribute_opt bit_field_size_opt
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | bit_field_size
        ;

bit_field_size_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | bit_field_size
        ;

bit_field_size:
        COLON constant_expression
          {  $$ = nonterm(TYP, int_read_only_ctype, 2, $1, $2);
            decl->supp = copy_ptree($2);
          }
        ;

enum_name:
        ENUM LC 
          {  /* Declaration of un-named enumeration. */
             unnamed_enum_declaration_action();
          }
          enumerator_list RC
          {  pop_decl();
             decl->btype->ident->supp = copy_ptree($4);
             add_ident_to_symtab1(symtab[SUE], decl->btype->ident);
             clear_dtype();
             $$ = nonterm(UNT, NULL, 4, $1, $2, $4, $5);
          }
        | ENUM identifier_or_typedef_name LC  
          {  /* Declaration of named enumeration. */
             named_enum_declaration_action($2);
          }
          enumerator_list RC
          {  pop_decl();
             decl->btype->ident->supp = copy_ptree($5);
             clear_dtype();
             $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $5, $6);
          }
        | ENUM identifier_or_typedef_name
          {  /* Reference to enumeration. */
             enum_reference_action($2);
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

enumerator_list:
        identifier_or_typedef_name enumerator_value_opt
          {  IDENT *i;
             $$ = nonterm(UNT, NULL, 2, $1, $2);
             i = new_ident1(ENC, $1->ident->name, int_read_only_ctype,
                            NULL, FALSE);
             add_ident_to_symtab1(symtab[OTH], i);
          }
        | enumerator_list COMMA identifier_or_typedef_name enumerator_value_opt
          {  IDENT *i;
             $$ = nonterm(UNT, NULL, 4, $1, comma(), $3, $4);
             i = new_ident1(ENC, $3->ident->name, int_read_only_ctype,
                            NULL, FALSE);
             add_ident_to_symtab1(symtab[OTH], i);
          }
        ;

enumerator_value_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | ASSIGN constant_expression
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

parameter_type_list:
        parameter_list
        | parameter_list COMMA
          {  save_decl();
             clear_btype(); /* Formerly: clear_dtype(); */
          }
        ELLIPSIS
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $4);
          }
        ;

parameter_list:
        parameter_declaration
        | parameter_list COMMA
          {  save_decl();
             /* This clear_btype is bad, eg, because it converts
                void foo (char(*)(), ...) to
                void foo (...) (JAT) */
             /* I think this has been fixed (JAT) */
             clear_btype(); /* Formerly: clear_dtype(); */
         }
          parameter_declaration
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $4);
          }
        ;

parameter_declaration:
        declaration_specifier
        | declaration_specifier abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_specifier identifier_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_specifier parameter_typedef_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_qualifier_list
        | declaration_qualifier_list abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | declaration_qualifier_list identifier_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_specifier
        | type_specifier abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_specifier identifier_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_specifier parameter_typedef_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_qualifier_list
        | type_qualifier_list abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_qualifier_list identifier_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

/* ANSI C section 3.7.1 states "An identifier declared as a typedef
   name shall not be redeclared as a parameter".  Hence the following
   is based only on IDENTIFIERs */

identifier_list:
        IDENTIFIER
          {  decl->name = copy_string($1->ident->name);
             $1->ident->eclass = OTH; 
          }
        | identifier_list COMMA
          {  save_decl();
             clear_dtype();
          }
        IDENTIFIER
          {  decl->name = copy_string($4->ident->name);
             $1->ident->eclass = OTH;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $4);
          }
        ;

identifier_or_typedef_name:
        IDENTIFIER
          {  decl->name = copy_string($1->ident->name);
          }
        | TYPEDEFname
          {  decl->name = copy_string($1->ident->name);
          }
        ;

type_name:
        type_specifier
        | type_specifier abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | type_qualifier_list
        | type_qualifier_list abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

initializer_opt:
        /* Nothing */
         {  $$ = empty();
         }
        | ASSIGN initializer
         {  $$ = nonterm(UNT, NULL, 2, $1, $2);
            decl->initializer = copy_ptree($2);
         }
        ;

initializer:
        LC initializer_list RC
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3); }
        | LC initializer_list COMMA RC
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4); }
        | assignment_expression
        ;

initializer_list:
        initializer
        | initializer_list COMMA initializer
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3); }
        ;


/*****************************************************************************/
/*                  Statements.                                              */
/*****************************************************************************/

statement:
        labeled_statement
        | compound_statement
        | expression_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        | asm_statement
        ;

asm_statement:
        ASM LP string_literal_list asm_op_desc_opt RP
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $4, $5);
          }
        | ASM VOLATILE LP string_literal_list asm_op_desc_opt RP
          {  $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, $5, $6);
          }
        ;

asm_op_desc_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | COLON asm_op_list_opt
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | COLON asm_op_list_opt COLON asm_op_list_opt
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | COLON asm_op_list_opt COLON asm_op_list_opt COLON asm_op_list_opt
          {  $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, $5, $6);
          }
        ;

asm_op_list_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | asm_op_list
        ;

asm_op_list:
        asm_op
        | asm_op_list COMMA asm_op
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

asm_op:
        string_literal_list
        | string_literal_list LP comma_expression RP
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | LP comma_expression RP
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

/* ANSI C requires a statement after the COLON in the rules for
   labeled_statement.  But, here, the statement is *optional*.
   If the statment is included, it is parsed as a
   compound_statement consisting of a labeled_statement
   followed by another statement. (JAT) */

labeled_statement:
        identifier_or_typedef_name COLON /* statement */
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
             add_label_to_symtab($1->ident->name);
          }
        | CASE constant_expression COLON /* statement */
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3); }
        | DEFAULT COLON /* statement */
          {  $$ = nonterm(UNT, NULL, 2, $1, $2); }
        ;

/* I had mid-rule actions here, but they resulted in reduce/reduce
   conflicts, so I had to take them out, and replace them with the
   non-terminals push_scope and pop_scope (JAT) */

compound_statement:
        LC RC
          {  $$ = nonterm(UNT, NULL, 2, $1, $2); }
        | LC left_brace declaration_list right_brace RC
          {  $$ = nonterm(UNT, NULL, 3, $1, $3, $5); }
        | LC left_brace statement_list right_brace RC
          {  $$ = nonterm($3->ident->eclass, $3->ident->ctype,
                          3, $1, $3, $5);
          }
        | LC left_brace declaration_list statement_list right_brace RC
          {  $$ = nonterm($4->ident->eclass, $4->ident->ctype,
                          4, $1, $3, $4, $6);
          }
        ;

left_brace:
        /* Nothing */
          {  clear_decl(); /* decl->declared_but_unprinted = NULL. */
             push_scope(FALSE);
             $$ = empty();
         }
        ;

right_brace:
        /* Nothing */
          {  pop_scope();
             $$ = empty();
          }
        ;

declaration_list:
        declaration
        | declaration_list declaration
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

statement_list:
        statement
        | statement_list statement
          {
             $$ = nonterm($2->ident->eclass, $2->ident->ctype, 2, $1, $2);
          }
        ;

expression_statement:
        comma_expression_opt SEMICOLON
          {  $$ = nonterm(TYP, $1->ident->ctype, 2, $1, $2);
          }
        ;

selection_statement:
        /* if-if-else shift-reduce conflict. (JAT) */
          IF LP comma_expression RP statement
          {  $3->ident->ctype = int_read_only_ctype; /* boolean */
             $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, nl(), $5);
          }
        | IF LP comma_expression RP statement ELSE statement
          {  $3->ident->ctype = int_read_only_ctype; /* boolean */
             $$ = nonterm(UNT, NULL, 9, $1, $2, $3, $4, nl(), $5,
                         $6, nl(), $7);
          }
        | SWITCH LP comma_expression RP statement
          {  $3->ident->ctype = int_read_only_ctype; /* int */
             $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $4, $5);
          }
        ;

iteration_statement:
        WHILE LP comma_expression RP statement
          {  $3->ident->ctype = int_read_only_ctype; /* boolean */
             $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, nl(), $5);
          }
        | DO statement WHILE LP comma_expression RP SEMICOLON
          {  $5->ident->ctype = int_read_only_ctype; /* boolean */
             $$ = nonterm(UNT, NULL, 7, $1, $2, $3, $4, $5, $6, $7);
          }
        | FOR LP comma_expression_opt SEMICOLON comma_expression_opt 
            SEMICOLON comma_expression_opt RP statement
          {  $$ = nonterm(UNT, NULL, 10, $1, $2, $3, $4, $5, $6, $7,
                          $8, nl(), $9);
          }
        | foreach_or_rofeach LP assignment_expression RP statement
          {  NODE *n = nonterm(UNT, NULL, 3, $3, comma(), $5);
             $$ = special_op_nonterm($1, n);
          }
        ;

foreach_or_rofeach:  
          FOREACH
        | FOREACHK
        | ROFEACH
        ;

jump_statement:
        GOTO comma_expression_or_typedef_name SEMICOLON
          {
             /* The target of the goto (constant_expression) can be
                identifier_or_typedef_name, which serves as an (implicit)
                declaration of the identifier_or_typedef_name as a label. */
             if ($2->narg == 0)
               add_label_to_symtab($2->ident->name);
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | CONTINUE SEMICOLON
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | BREAK SEMICOLON
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | RETURN comma_expression_opt SEMICOLON
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

comma_expression_or_typedef_name:
        comma_expression
        | TYPEDEFname
        ;

/*****************************************************************************/
/*                  External definitions.                                    */
/*****************************************************************************/

translation_unit:
        external_definition
        | translation_unit external_definition
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        ;

external_definition:
        function_definition
          {  print_liner_pragma = TRUE;
             print_ptree($1);
             /* This would be a good place to delete_ptree($1)
                if we didn't have (automatic) garbage collection. (JAT) */
             print_liner_pragma = FALSE;
          }
        | declaration
          {
             print_ptree($1);
             /* This would be a good place to delete_ptree($1)
                if we didn't have (automatic) garbage collection. (JAT) */
          }
        | error SEMICOLON
          {  warning(4, "incorrect definition or declaration--skipping to ';'");
             yyerrok;
          }
        | error RC
          {  warning(4, "incorrect definition or declaration--skipping to '}'");
             yyerrok;
          }
        ;

function_definition:

/* Prototyped */

                                     identifier_declarator
          { pre_function_definition_action(); 
          }
        compound_statement
          {  $$ = nonterm(UNT, NULL, 3, $1, nl(), $3);
            post_function_definition_action();
          }
        | declaration_specifier      identifier_declarator
          { pre_function_definition_action(); 
          }
        compound_statement 
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | type_specifier             identifier_declarator
          { pre_function_definition_action(); 
          }
        compound_statement 
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | declaration_qualifier_list identifier_declarator
          { pre_function_definition_action();
          }
        compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | type_qualifier_list        identifier_declarator
          { pre_function_definition_action();
          }
        compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }

/* Not prototyped, w/o declaration_list */

        |                           old_function_declarator
          { pre_function_definition_action();
          }
         compound_statement
          {  $$ = nonterm(UNT, NULL, 3, $1, nl(), $3);
            post_function_definition_action();
          }
        | declaration_specifier      old_function_declarator 
          { pre_function_definition_action();
          }
        compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | type_specifier             old_function_declarator 
          { pre_function_definition_action();
          }
        compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | declaration_qualifier_list old_function_declarator
          { pre_function_definition_action();
          }
         compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }
        | type_qualifier_list        old_function_declarator
          { pre_function_definition_action();
          }
         compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, nl(), $4);
            post_function_definition_action();
          }

/* Not prototyped, w/ declaration list */

        |                           old_function_declarator
          { pre_function_definition_action();
          }
         declaration_list compound_statement
          {  $$ = nonterm(UNT, NULL, 4, $1, nl(), $3, $4);
            post_function_definition_action();
          }
        | declaration_specifier      old_function_declarator 
          { pre_function_definition_action();
          }
        declaration_list compound_statement
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, nl(), $4, $5);
            post_function_definition_action();
          }
        | type_specifier             old_function_declarator 
          { pre_function_definition_action();
          }
        declaration_list compound_statement
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, nl(), $4, $5);
            post_function_definition_action();
          }
        | declaration_qualifier_list old_function_declarator
          { pre_function_definition_action();
          }
         declaration_list compound_statement
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, nl(), $4, $5);
            post_function_definition_action();
          }
        | type_qualifier_list        old_function_declarator 
          { pre_function_definition_action();
          }
        declaration_list compound_statement
          {  $$ = nonterm(UNT, NULL, 5, $1, $2, nl(), $4, $5);
            post_function_definition_action();
          }
        ;

declarator:
        identifier_declarator
          {  $$ = declarator_nonterm($1);
          }
        | typedef_declarator
          {  $$ = declarator_nonterm($1);
          }
        ;

typedef_declarator:
        paren_typedef_declarator          /* would be ambiguous as parameter */
        | parameter_typedef_declarator    /* not ambiguous as parameter */
        ;

parameter_typedef_declarator:
        TYPEDEFname
          {  $1->ident->eclass  =  OTH; 
             decl->name = copy_string($1->ident->name);
          }
        | TYPEDEFname postfixing_abstract_declarator
          {  $1->ident->eclass = OTH;
             $$ = nonterm(UNT, NULL, 2, $1, $2);
             decl->name = copy_string($1->ident->name);
          }
        | clean_typedef_declarator
        ;

    /*  The following have at least one '*'. There is no (redundant)
    '(' between the '*' and the TYPEDEFname. */

clean_typedef_declarator:
        clean_postfix_typedef_declarator
        | STAR parameter_typedef_declarator
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | STAR type_qualifier_list parameter_typedef_declarator
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

clean_postfix_typedef_declarator:
        left_paren clean_typedef_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren clean_typedef_declarator right_paren
          postfixing_abstract_declarator
          {$$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

    /* The following have a redundant '(' placed immediately  to  the
    left of the TYPEDEFname */

paren_typedef_declarator:
        paren_postfix_typedef_declarator
        | STAR left_paren simple_paren_typedef_declarator right_paren
          /* redundant paren */
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | STAR type_qualifier_list
              left_paren simple_paren_typedef_declarator right_paren
          /* redundant paren */
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 5, $1, $2, $3, $4, $5);
          }
        | STAR paren_typedef_declarator
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | STAR type_qualifier_list paren_typedef_declarator
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

paren_postfix_typedef_declarator:       /* Redundant paren to left of tname */
        left_paren paren_typedef_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren simple_paren_typedef_declarator
          postfixing_abstract_declarator right_paren
          /* redundant paren */
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | left_paren paren_typedef_declarator right_paren
           postfixing_abstract_declarator
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

simple_paren_typedef_declarator:
        TYPEDEFname
          {   ENTRY *e;
              IDENT *i;
              e = symtab_lookup(symtab[OTH], $1->ident->name);
              if (e == NULL)
                parse_error("%s is not a typedef name", $1->ident->name);
              i = e->ident;
              if (i->eclass != OTH && i->eclass != TDF)
                parse_error("%s is not a typedef name", i->name);
              i->ctype = copy_ctype(decl->btype);
              decl->btype->ident = i->ctype->ident;
              /* PREDATOR addition */
              if (i->eclass == CON)
                decl->eclass = CON; /* Formerly: decl->eclass = CON */
              $1->ident->eclass = OTH; 
          }
        | left_paren simple_paren_typedef_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

identifier_declarator:
        unary_identifier_declarator
        | paren_identifier_declarator
        ;

asm_name_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | ASM LP string_literal_list RP
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

attribute_opt:
        /* Nothing */
          {  $$ = empty();
          }
        | ATTRIBUTE LP LP attribute_list RP RP
          {  $$ = nonterm(UNT, NULL, 6, $1, $2, $3, $4, $5, $6);
             decl->attribute = copy_ptree($$);
          }
        ;

attribute_list:
        attribute
        | attribute_list COMMA attribute
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);  
          }
        ;

attribute:
        CONST
        | IDENTIFIER
        | IDENTIFIER LP argument_expression_list RP
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

unary_identifier_declarator:
        postfix_identifier_declarator
        | STAR identifier_declarator
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | STAR type_qualifier_list identifier_declarator
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

postfix_identifier_declarator:
        paren_identifier_declarator postfixing_abstract_declarator
          {  $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | left_paren unary_identifier_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren unary_identifier_declarator right_paren
        postfixing_abstract_declarator
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

paren_identifier_declarator:
        IDENTIFIER 
          {  decl->name = copy_string($1->ident->name);
             $1->ident->eclass =  OTH;
#if 0
             $1->ident->ctype = UNDEFINED_CTYPE;
#else
             $1->ident->ctype = undefined_read_only_ctype;
#endif
          }
        | left_paren paren_identifier_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

old_function_declarator:
        postfix_old_function_declarator
        | STAR old_function_declarator
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | STAR type_qualifier_list old_function_declarator
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

postfix_old_function_declarator:
        paren_identifier_declarator left_paren identifier_list right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $3));
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        | left_paren old_function_declarator right_paren
          {  $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren old_function_declarator right_paren
          postfixing_abstract_declarator
          {  $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

abstract_declarator:
        unary_abstract_declarator
        | postfix_abstract_declarator
        | postfixing_abstract_declarator
        ;

postfixing_abstract_declarator:
        array_abstract_declarator
        | left_paren right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2); 
          }
        | left_paren parameter_type_list right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $2));
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        ;

array_abstract_declarator:
        LB RB
          {  left_expand_decl_dtype(new_ptype(ARR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2);
          }
        | LB constant_expression RB
          {  left_expand_decl_dtype(new_ptype(ARR, UND, copy_ptree($2)));
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | array_abstract_declarator LB constant_expression RB
          {  left_expand_decl_dtype(new_ptype(ARR, UND, copy_ptree($3)));
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

unary_abstract_declarator:
        STAR
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
          }
        | STAR type_qualifier_list
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 2, $1, $2) ;
          }
        | STAR abstract_declarator
          {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             $$ = nonterm(UNT, NULL, 2, $1, $2) ;
          }
        | STAR type_qualifier_list abstract_declarator
          {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3) ;
          }
        ;

postfix_abstract_declarator:
        left_paren unary_abstract_declarator right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $2));
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren postfix_abstract_declarator right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $2));
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren postfixing_abstract_declarator right_paren
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $2));
             $$ = nonterm(UNT, NULL, 3, $1, $2, $3);
          }
        | left_paren unary_abstract_declarator right_paren
          postfixing_abstract_declarator
          {  left_expand_decl_dtype(new_ptype(FUN, UND, $2));
             $$ = nonterm(UNT, NULL, 4, $1, $2, $3, $4);
          }
        ;

left_paren:
        LP
          {  left_paren_action();
          }
        ;

right_paren:
        RP
          {  right_paren_action();
          }
        ;

%%

/*****************************************************************************/
/*                  End of Grammar.                                          */
/*****************************************************************************/

#if YYDEBUG
static void
yyprint (FILE *file, int type, YYSTYPE value)
{
  fprintf(file,"\nNode: ( %s )", value.n->ident->name);
}
#endif

/* The lex library is supposed to define yywrap(),
   but we cannot count on finding the library.
   Thus, for safety, we define yywrap as a function. (JAT) */

int
yywrap (void)
{ 
   return(1);
}

void
yyerror (char *s)
{
   parse_error(s);
}
