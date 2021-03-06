%{

/* $Id: ddl-gram.y,v 45.0 1997/09/19 05:40:59 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* ddl grammar (bison source file). */

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h> /* strcat() */

#include "ddl.h"
#include "error.h"  /* warning() */

/************************************************************************/
/*              Defines.                                                */
/************************************************************************/

#define YYDEBUG 1   /* pretty debugging code */
#define YYERROR_VERBOSE 1 /* define as anything for verbose BISON errors. */

/************************************************************************/
/*              Local forward references.                               */
/************************************************************************/

int    yylex(void);
void   yyerror(char *s);

%}

/************************************************************************/
/*              Tokens.                                                 */
/************************************************************************/

%token IDENTIFIER
%token OP
%token LITERAL
%token WITH
%token TYPEX
%token OF

%union {
  char     str[MAX_IDENT_LEN];
  LISTNODE *node;
}

%type <str>  IDENTIFIER OP LITERAL WITH
%type <str>  container
%type <str>  expr_token
%type <str>  reserved
%type <node> expr
%type <node> param
%type <node> param_list
%type <node> name
%type <node> endsq
%type <node> option
%type <node> pathexpr

/* Begin layer specific declarations. (DSB) */

%token OPTION
%token SIZE
%token IS
%token FILENAME         /* Where is this used??? (JAT) */
%token FIELD
%token ON
%token KEY
%token LINK
%token PREDICATE
%token TO
%token FILE_TOKEN       /* "FILE" */
%token WHERE
%token FROM
%token ONE_TOKEN
%token MANY_TOKEN
%token AT_MOST_ONE_TOKEN
%token AT
%token COUNTER
%token ANONYMOUS
%token TIMESTAMP
%token PRE_ACTION
%token POST_ACTION

%type <str> OPTION SIZE IS FILENAME FIELD 
%type <str> ON KEY LINK PREDICATE TO FILE_TOKEN  
%type <str> WHERE FROM ONE_TOKEN MANY_TOKEN AT_MOST_ONE_TOKEN 
%type <str> AT COUNTER ANONYMOUS TIMESTAMP
%type <str> card link 

%start program

%%

reserved:  OPTION | SIZE | IS | FILENAME | FIELD
           | ON | KEY | LINK | PREDICATE | TO | FILE_TOKEN
           | WHERE | FROM | ONE_TOKEN | MANY_TOKEN | AT_MOST_ONE_TOKEN
           | AT | COUNTER | ANONYMOUS | TIMESTAMP ;

/* End layer specific declarations. (DSB) */

/* Naming convention: internal rule names are prefaced by "".
   Rule names prefaced by "_" are generated by users or layer writers. (DSB) */
/* Why are any underscores necessary? */
/* Why not use "ddl_" and "usr_" instead of "" and "_"??? (JAT) */
 
program: segment
        | program segment
        ;

segment:  any_token
        | formatted 
        ;

any_token: '{'              { printf("{ "); }
              | '}'           { printf("} "); }
              | ';'           { printf(";\n"); }
              | expr_token  { printf("%s ", $1); }
              | reserved    { printf("%s ", $1); }
              ;    
 

formatted: with '{'             '}' 
            | with '{' stmt_list '}' 
            | TYPEX  '{'             '}'
            | TYPEX  '{' eqn_list  '}'
            ;


with:  WITH    { printf("\n"); }
        ;

stmt_list:  stmt
            | stmt_list stmt
            ;

eqn_list: eqn
            | eqn_list eqn
            ;


eqn:        ';'
            | name '=' param
              {  printf("P2_typex(");
                 print_string_expr($1); 
                 printf(", "); 
                 print_string_expr($3);
                 printf(", \"\");\n");
                 new_equation($1->text, $3);
              }
            ;

param:
              name 
           | name '[' param_list endsq
             { if (strcmp($1->text, "conceptual") == 0)
                 $$ = decompose_conceptual($3);
             else
               $$ = new_list_head($1, $3);
           }
           ;

endsq:  ']'  { /* nothing */ } 
           | error { warning(3, "Need a ]");  yyerrok; }
           ; 


name: IDENTIFIER          { $$ = new_node($1); }
           | reserved     { $$ = new_node($1); }
           | error   { warning(3, "Inappropriate name"); }
           ;
 
param_list: param
               { $$ = $1; }
             | param_list ','  param
               { $$ = new_list_tail($1, $3); }
             ;
           
expr_token:
           LITERAL
           | IDENTIFIER
           | OP
           | '='             { strcpy($$, "="); }
           | ','             { strcpy($$, ","); }
           | '['             { strcpy($$, "["); }
           | ']'             { strcpy($$, "]"); }
           | '.'             { strcpy($$, "."); }
           | '('             { strcpy($$, "("); }
           | ')'             { strcpy($$, ")"); }
           | error reserved 
             { warning(3, "Reserved word used as expression");
               yyerrok;
             } 
           ;   

expr:
           expr_token             { $$ = new_node($1); }
           | expr_token expr      { $$ = new_list($1, $2); }
           ; 

pathexpr: name                 { $$ = $1; }
           | pathexpr '.' name { $$ = new_list_tail($1, $3); }
           ;

container: OF IDENTIFIER         { strcpy($$, $2); }
           | IDENTIFIER
           | /* empty */          { strcpy($$, "P2_default"); } 
           ; 

option:    OPTION expr          { $$ = $2; }
           | /* empty */          { $$ = new_node(""); }
           ;

  /* begin layer specific statement additions to language */

             
             
link: IDENTIFIER
           ;
 
card: ONE_TOKEN
           | MANY_TOKEN
           | AT_MOST_ONE_TOKEN
           ;

stmt:      ';'
           | pathexpr SIZE container IS expr 
            { /* array */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(");\n");
            }
           |  pathexpr container LITERAL
            { /* cursor_structure, container_structure */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", %s);\n", target_layer, $3);
            }
           |  pathexpr container FILE_TOKEN IS LITERAL WITH SIZE expr
            { /* mmap_persistent, mmap_shared */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", %s,", target_layer, $5);
              print_expr($8);
              printf(");\n");
            }
           |  pathexpr container AT FIELD expr
            { /* partitioning layers like part, parttwo */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(");\n");
            }
          | pathexpr KEY container IS expr 
            { /* key-ordering layers like bintree, odlist */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(");\n");
            }
          | pathexpr TIMESTAMP container IS expr option
            { /* llist (and other leaps list layers?) */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(", ");
              print_expr($6);
              printf(");\n");
            }
          | pathexpr TIMESTAMP container IS expr KEY IS expr 
             WITH SIZE expr option
            { /* leaps list layers */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(", ");
              print_expr($8);
              printf(", ");
              print_expr($11);
              printf(", ");
              print_expr($12);
              printf(");\n");
            }
          | pathexpr KEY container IS expr WITH SIZE expr option
            { /* hash, hash_array, qsort */
              /* hash, hash_array option hash_function. */
              /* qsort option "prinary" (key is unique)
                 or "secondary" (key is not necessarily unique). */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(", ");
              print_expr($8);
              printf(", ");
              print_expr($9);
              printf(");\n");
            }
          | pathexpr container FIELD IS expr COUNTER IS expr
            { /* vtimestamp */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($5);
              printf(", ");
              print_expr($8);
              printf(");\n");
            }
          | pathexpr container FIELD expr 
            { printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"hashcmp\", ");
              print_expr($4);
              printf(");\n");
            }
          | pathexpr container ON expr
            { printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              print_expr($4);
              printf(");\n");
            }
          | pathexpr container PREDICATE LITERAL
            { /* predindx */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"predindx\", %s", $4);
              printf(");\n");
            }
          | pathexpr TIMESTAMP container IS expr PREDICATE LITERAL 
             WITH expr WITH expr option
            { /* lpredindx, tpredindx */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\"", target_layer);
              printf(", ");
              print_expr($5);
              printf(", %s", $7);
              printf(", ");
              print_expr($9);
              printf(", ");
              print_expr($11);
              printf(", ");
              print_expr($12);
              printf(");\n");
            }
          | pathexpr TIMESTAMP container IS expr KEY IS expr 
             WITH SIZE expr PREDICATE LITERAL 
             WITH expr WITH expr option
            { /* hpredindx */
              printf("P2_ddlhint(%s, ", $3);
              print_path($1);
              printf(", \"%s\"", target_layer);
              printf(", ");
              print_expr($5);
              printf(", ");
              print_expr($8);
              printf(", ");
              print_expr($11);
              printf(", %s, ", $13);
              print_expr($15);
              printf(", ");
              print_expr($17);
              printf(", ");
              print_expr($18);
              printf(");\n");
            }
          | pathexpr container ANONYMOUS
            { /* nloops */
              printf("P2_ddlhint(%s, ", $2);
              print_path($1);
              printf(", \"%s\", ", target_layer);
              printf("\"\"");
              printf(");\n");
            }
          | pathexpr LINK link ON
            card container TO card container
            WHERE expr
            { /* nloops, ringlist */
              printf("P2_ddlhint(P2_default,");
              print_path($1);
              printf(", \"%s\", ", target_layer);
              printf("\"%s\", %s,", $5, $6);
              printf("\"%s\", %s,", $8, $9);
              print_expr($11);
              printf(");\n");
            }
          ;


   /* end layer specific statement additions to language */

%%

/************************************************************************/
/*              End of Grammar.                                        */
/************************************************************************/

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
