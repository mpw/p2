%{

/* $Id: rl-lex.l,v 45.0 1997/09/19 05:46:10 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "rl.h"
#include "rl-gram.tab.h"

extern int line_number;

#define RETURN_STRING(t) \
  yylval.string = (char *) malloc(strlen(yytext) + 1); \
  strcpy(yylval.string, yytext); \
  return t;

%}

int_lit         [0-9]+
float_lit       [0-9]*"."[0-9]+
symbol          ([+a-zA-Z0-9_-][\.+a-zA-Z0-9_-]*)
rel_op          "="|"<"|">"|"<="|">="|"<>"|"<=>"
string_lit      (\"([^\n"\\]|(\\.)|(\\\n))*\")

%% 

%{
/* Some versions of flex define yywrap() as a macro.
   We define yywrap() as a function.
   Thus we must undefine yywrap(). (JAT) */

#undef yywrap
%}

integer         { return INTEGER; }
float           { return FLOAT; }
char            { return CHAR; }

";".*\n         { line_number++; }
[ \t]           ; 
[\n]            { line_number++; }
"("             { return LP; }
")"             { return RP; }
p               { return PTOK; }
-->             { return SEPRTR; }
"{"             { return LCB; }
"}"             { return RCB; }
"-"             { return MINUS; }
"+"             { return PLUS; }
{rel_op}        { RETURN_STRING(PREDICATE); }
{int_lit}       { RETURN_STRING(FIXPTNO); }
{float_lit}     { RETURN_STRING(FLOATPTNO); }
{string_lit}    {
                  yylval.string = (char *) malloc (strlen(yytext)+1);
                  strcpy(yytext+strlen(yytext)-1, "\0");
                  strcpy(yylval.string, yytext + 1);
                  return STRING;
                }
include         { return INCLUDE; }
symbols         { return SYMBOLS; }
cbind           { return CBIND; }
equal           { return EQUAL; }
literalize      { return LITERALIZE; }
make            { return MAKE; }
remove          { return REMOVE; }
modify          { return MODIFY; }
halt            { return HALT; }
bind            { return BIND; }
call            { return CALL; }
write           { return WRITE; }
openfile        { return OPENFILE; }
closefile       { return CLOSEFILE; }
default         { return DEFAULT; }
litval          { return LITVAL; }
substr          { return SUBSTR; }
genatom         { return GENATOM; }
crlf            { return CRLF; }
rjust           { return RJUST; }
tabto           { return TABTO; }
acceptline      { return ACCEPTLINE; }
accept          { return ACCEPT; }
compute         { return COMPUTE; }
"<<"            { return ORLP; }
">>"            { return ORRP; }
"//"            { return DIV; }
"\\"            { return MOD; }
literal         { return LITERAL; }
vector_attribute { return VECTORATTR; }
external        { return EXTERNAL; }
{symbol}        { RETURN_STRING(CONSTANTSYMBOLICATOM); }
\^{symbol}      { 
                  yylval.string = (char *) malloc(strlen(yytext) + 1);
                  strcpy(yylval.string, yytext + 1);
                  return ATTRIBUTENAME; 
                }
"<"{symbol}">"  { 
                  yylval.string = (char *) malloc(strlen(yytext) + 1);
                  strcpy(yytext+strlen(yytext)-1, "\0");
                  strcpy(yylval.string, yytext + 1);
                  return VARIABLE;
                }
.               { return yytext[0]; }

%%
