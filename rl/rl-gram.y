%{

/* $Id: rl-gram.y,v 45.0 1997/09/19 05:46:09 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* rl grammar (bison source file). */

/********************** Include files *******************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "rl.h"

/********************** Some global contant definitions *************************/

#define YYDEBUG         1

/********************** Global variables ***************************************/

BOOLEAN error_status = FALSE ;  /* global variable to indicate prese- */
                                /* of parse errors ; TRUE if errors   */
                                /* occurred and FALSE otherwise       */
int line_number = 1 ;           /* Line number in the source code     */

CONT_PTR    current_container;  /* used in parsing LITERALIZE stmts   */
RULE_PTR    current_rule;       /* used in parsing RULES              */
ELEMENT_PTR current_element;    /* used in parsing RULES              */
CLAUSE_PTR  current_clause;     /* ""                                 */
ACTION_PTR  current_action;     /* ""                                 */
VALTYPE     current_valtype;    /* ""                                 */
TEXT        current_relop;      /*                                    */
TEXT        current_cons;       /*                                    */
STRLIST_PTR string_list;        /*                                    */
NAME        current_attribute;  /* name of current attribute          */
int         size;               /* size of current character array    */

/*******************************************************************************/
%}

/* %expect 15 */

%union {
   char *string ;
   FIELDTYPE ftype;
   NODE_PTR  node;
} 

%token LP PTOK CONSTANTSYMBOLICATOM SEPRTR RP LCB RCB ATTRIBUTENAME
%token PREDICATE VARIABLE FIXPTNO FLOATPTNO CBIND EQUAL LITERALIZE
%token MAKE REMOVE MODIFY HALT BIND CALL WRITE OPENFILE CLOSEFILE 
%token DEFAULT LITVAL SUBSTR GENATOM CRLF RJUST ORLP ORRP TABTO 
%token ACCEPTLINE ACCEPT COMPUTE OPERATOR LITERAL VECTORATTR INCLUDE
%token EXTERNAL VARIABLEOFFSET NIL STRING MINUS PLUS INTEGER FLOAT CHAR
%token SYMBOLS

%right '+' '-' '*' DIV MOD

%type <string> CONSTANTSYMBOLICATOM FIXPTNO FLOATPTNO VARIABLE
%type <string> PREDICATE ATTRIBUTENAME STRING MINUS PLUS CRLF
%type <string> litvaluex elementdesignator operator
%type <ftype>  datatype
%type <node>   rhsvalue function userdefinedfunction expression 
%type <node>   varorconstantx

%%


file    :  declarations 
           { }
        ;

declarations  :  declarations declaration
              |  /* empty */
              ;

declaration   :  LP LITERALIZE litvaluex RP
              |  LP INCLUDE CONSTANTSYMBOLICATOM RP
                 { new_predicate(&include_list, $3); }
              |  LP SYMBOLS litvallist RP
              |  LP LITERAL litassignx RP
              |  LP EXTERNAL funcnames RP
              |  LP VECTORATTR vectornames RP
              |  LP PTOK firstrule rules 
              |  LP MAKE CONSTANTSYMBOLICATOM attr_value RP
              ;

funcnames     :  funcnames CONSTANTSYMBOLICATOM 
              |  /* empty */
              ;

vectornames   :  vectornames CONSTANTSYMBOLICATOM 
              |  /* empty */
              ;


litassignx    :  litassignx CONSTANTSYMBOLICATOM EQUAL FIXPTNO 
              |  /* empty */
              ;

litvallist    : litvallist CONSTANTSYMBOLICATOM
                { new_predicate( &symbol_table, $2 ); }
              | CONSTANTSYMBOLICATOM
                { new_predicate( &symbol_table, $1 ); }
              ;

litvaluex     :  litvaluex CONSTANTSYMBOLICATOM datatype
                 { make_type( new_field(current_container, $2), $3, size); }
              |  litvaluex CONSTANTSYMBOLICATOM 
                 { new_field(current_container, $2); }
              |  CONSTANTSYMBOLICATOM
                 { current_container = new_container($1); }
              ;

datatype      :  INTEGER
                 { $$ = INT; size = 0; }
              |  FLOAT
                 { $$ = REAL; size = 0; }
              |  CHAR '[' FIXPTNO ']'
                 { $$ = STR; size =  atoi($3); }
              ;

firstrule     :  CONSTANTSYMBOLICATOM 
                 { current_rule = new_rule($1); }
                 lhs SEPRTR rhs RP
              ;

rules         :  rules production 
              |  /* empty */ 
              ;

production    :  LP PTOK CONSTANTSYMBOLICATOM 
                 { current_rule = new_rule($3); }
                 lhs SEPRTR rhs RP
              ;

attr_value    :  attr_value ATTRIBUTENAME constant
              |  /* empty */
              ;

lhs           :  postivece cex 
              ;

cex           :  cex postivece 
              |  cex negativece 
              |  /* empty */
              ;

postivece     :  form 
              |  LCB VARIABLE form RCB 
              |  LCB form VARIABLE RCB 
              |  error 
              ;

negativece    :  MINUS form 
                 { current_element->neg = TRUE;
                   { CONT_PTR c = find_container(current_element->name);
                     if (!c)
                        fprintf(stderr,"undeclared container %s line %d\n",
                                current_element->name, line_number);
                     else
                        make_shadow( c );
                   }
                 }
              ;

form          :  LP CONSTANTSYMBOLICATOM 
                 { current_element = new_element( current_rule, $2, FALSE ); }
                 lhstermp RP
              |  LP error RP 
                 { yyerrok; }
              ;

lhstermp      :  lhstermp lhsterm 
              |  lhsterm
              |  /* empty */
              ;

lhsterm       :  ATTRIBUTENAME 
                 { strcpy(current_attribute, $1); }
                 lhsvalue 
              |  lhsvalue 
                    {
                       yyerror("Attribute not specified") ;
                       YYERROR ;
                    }
              |  LP error RP 
                 { yyerrok; }
              ;

lhsvalue      :  LCB restrictionx RCB 
              |  restriction 
              ;

restrictionx  :  restrictionx restriction
              |  restriction
              ;

restriction   : restrict
                { current_clause = new_clause( current_element,
                                    current_attribute,
                                    current_relop, current_valtype,
                                    current_cons);
                   if (current_valtype == DIS) {
                      STRLIST_PTR s;
                      for (s = string_list; s ; s = s->next)
                         new_disj(current_clause,s->name);
                   }
                 }
               ;

restrict      :  disjunction
                 { current_valtype = DIS; 
                   strcpy(current_relop,"");
                 }
              |  PREDICATE varorconstant 
                 { strcpy(current_relop,$1);
                   if (strcmp(current_relop,"<=>")==0) {
                      fprintf(stderr,"<=> not supported\n");
                   }
                 }
              |  varorconstant 
                 { strcpy(current_relop,""); }
              ;

varorconstant :  VARIABLE 
                 { current_valtype = VAR; 
                   strcpy(current_cons, $1);
                 }
              |  constant 
                 { current_valtype = CONS; }
              ;

disjunction   :  ORLP disjvaluep ORRP 
              ;

disjvaluep    :  disjvaluep constant 
                 { STRLIST_PTR s = (STRLIST_PTR) malloc(sizeof(STRLIST));
                   strcpy(s->name, current_cons);
                   s->next = string_list;
                   string_list = s;
                 }
              |  constant 
                 { STRLIST_PTR s = (STRLIST_PTR) malloc(sizeof(STRLIST));
                   strcpy(s->name, current_cons);
                   s->next = 0;
                   string_list = s;
                 }
              ;

constant      :  FIXPTNO 
                 { strcpy(current_cons, $1); }
              |  FLOATPTNO 
                 { strcpy(current_cons, $1); }
              |  CONSTANTSYMBOLICATOM
                 { strcpy(current_cons, $1); }
              ;

rhs           :  rhs action
              |  /* empty */
              ;

action        :  LP MAKE CONSTANTSYMBOLICATOM 
                 { current_action = new_action(current_rule, MAK, $3); }
                 rhstermx RP 
/*
              |  LP MAKE 
                    {
                       yyerror("Class name required");
                       YYERROR ;
                    }
                 rhstermx RP 
*/
              |  LP REMOVE 
                 { current_action = new_action(current_rule, REM, ""); }
                 elementdesignatorx RP
              |  LP MODIFY elementdesignator 
                 { char tmp[50];
                   strcpy(tmp,$3);
                   if (tmp[0] < '0' || tmp[0] > '9') {
                      fprintf(stderr,"var container in modify not supported\n");
                      exit(1);
                   }
                   current_action = new_action(current_rule, UPD, $3); 
                 }
                 rhstermx RP 
              |  LP HALT RP 
                 { current_action = new_action(current_rule, END, ""); }
              |  LP BIND VARIABLE rhstermx RP 
                 { fprintf(stderr,"bind not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP CBIND VARIABLE RP 
                 { fprintf(stderr,"cbind not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP CALL constant rhstermx RP 
                 { fprintf(stderr,"call not supported: line %d\n", line_number);
                   exit(1); }
              |  LP WRITE 
                 { current_action = new_action(current_rule, OUT, ""); }
                 rhstermx RP 
/*            |  LP WRITE STRING varorconstantx RP
              |  LP WRITE STRING RP
*/
              |  LP OPENFILE rhstermx RP 
                 { fprintf(stderr,"openfile not supported: line %d\n", line_number);
                   exit(1);}
              |  LP CLOSEFILE rhstermx RP 
                 { fprintf(stderr,"closefile not supported: line %d\n", line_number);
                   exit(1);}
              |  LP DEFAULT rhstermx RP 
                 { fprintf(stderr,"default not supported: line %d\n", line_number);
                   exit(1);}
              |  LP error RP 
                    { yyerrok ;}
              ;

elementdesignatorx :  elementdesignatorx elementdesignator 
                      { new_arg(current_action, $2, 0); }
                   |  elementdesignator
                      { new_arg(current_action, $1, 0); }
                   ;

elementdesignator  :  FIXPTNO  
                   |  VARIABLE 
                   ;

rhstermx      :  rhstermx ATTRIBUTENAME rhsvalue
                 { new_arg( current_action, $2, $3 ); }
/*            |  rhstermx FIXPTNO rhsvalue
*/
              |  rhstermx rhsvalue              /* used only in write stmts */
                 { new_arg( current_action, "", $2 ); }
              |  /* empty */
              ;

rhsvalue      :  varorconstant
                 { if (current_valtype == CONS)
                      $$ = new_node(current_cons, CONS_NODE, 0,0,0); 
                   else
                      $$ = new_node(current_cons, VAR_NODE, 0,0,0); 
                 }
              |  function
              ;

function      :  LP LITVAL varorconstant RP
                 { fprintf(stderr,"litval not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP SUBSTR elementdesignator varorconstant varorconstant RP 
                 { fprintf(stderr,"substr not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP GENATOM RP 
                 { fprintf(stderr,"genatom not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP CRLF RP 
                 { $$ = new_node( "", CRLF_NODE, 0, 0, 0); }
              |  LP RJUST varorconstant RP
                 { fprintf(stderr,"rjust not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP TABTO varorconstant RP 
                 { fprintf(stderr,"tabto not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP ACCEPT RP
                 { fprintf(stderr,"accept not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP ACCEPT varorconstant RP 
                 { fprintf(stderr,"accept not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP ACCEPTLINE varorconstantx RP
                 { fprintf(stderr,"acceptline not supported: line %d\n", line_number);
                   exit(1);
                 }
              |  LP COMPUTE expression RP 
                 { $$ = new_node( "", COMPUTE_NODE, $3, 0, 0); }
              |  userdefinedfunction 
              |  LP error RP 
                 {  yyerrok; }
              ;

userdefinedfunction  :  LP CONSTANTSYMBOLICATOM  varorconstantx RP 
                        { $$ = new_node($2,UFUNC_NODE, $3, 0,0); }
                     ;

expression    :  FIXPTNO 
                 { $$ = new_node($1,CONS_NODE,0,0,0); }
              |  FLOATPTNO 
                 { $$ = new_node($1,CONS_NODE,0,0,0); }
              |  VARIABLE 
                 { $$ = new_node($1,VAR_NODE,0,0,0); }
              |  expression operator expression 
                 { $$ = new_node($2,OPR_NODE,$1,$3,0); }
              |  LP expression RP
                 { $$ = $2; }
              ;

operator      : PLUS
                { strcpy($$,"+"); }
              | MINUS
                { strcpy($$,"-"); }
              | '*' 
                { strcpy($$,"*"); }
              | DIV 
                { strcpy($$,"/"); }
              | MOD 
                { strcpy($$,"//"); }
              ;

varorconstantx:  varorconstantx varorconstant
                 { if (current_valtype == CONS)
                      $$ = new_node(current_cons, CONS_NODE, $1, 0, 0);
                   else
                      $$ = new_node(current_cons, VAR_NODE, $1, 0, 0);
                 }
              |  /* empty */
                 { $$ = 0; }
              ;

%% 

/* The lex library is supposed to define yywrap(),
   but we cannot count on finding the library.
   Thus, for safety, we define yywrap as a function. (JAT) */

int
yywrap (void)
{ 
   return(1);
}

