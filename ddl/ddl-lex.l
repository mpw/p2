%{

/* $Id: ddl-lex.l,v 45.0 1997/09/19 05:41:00 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* ddl lexicographic analyzer (flex source file). */

/* Derived from a source file by James A. Roskind (1990) */

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ddl.h"
#include "error.h"        /* parse_warning(), parse_error() */
#include "lex.h"          /* MAX_IDENT_LEN */

#include "ddl-gram.tab.h" /* BISON-YACC generated defs based on C++ grammar */

/************************************************************************/
/*              YYLMAX.                                                 */
/************************************************************************/

/* Necessary for AT&T lex. */
#undef YYLMAX
#define YYLMAX MAX_IDENT_LEN

%}

/************************************************************************/
/*              Definitions.                                            */
/************************************************************************/

/* The following definitions are common to all P2 lex files. (JAT) */

identifier [a-zA-Z_][0-9a-zA-Z_]*

integer_suffix_opt ([uU]?[lL]?)|([lL][uU])
decimal_constant [1-9][0-9]*{integer_suffix_opt}
octal_constant "0"[0-7]*{integer_suffix_opt}
hex_constant "0"[xX][0-9a-fA-F]+{integer_suffix_opt}
integer_constant ({decimal_constant}|{octal_constant}|{hex_constant})

exponent ([Ee][-+]?[0-9]+)
float0 ([0-9]+\.[0-9]*)
float1 ({integer_constant}{exponent})
float2 ({float0}{exponent})
floating_constant (({float0}|{float1}|{float2})[lLfF]?)

simple_escape [abfnrtv'"?\\]
octal_escape  [0-7]{1,3}
hex_escape "x"[0-9a-fA-F]+

escape_sequence [\\]({simple_escape}|{octal_escape}|{hex_escape})
c_char [^'\\\n]|{escape_sequence}
s_char [^"\\\n]|{escape_sequence}

h_tab [\011]
form_feed [\014]
v_tab [\013]
c_return [\015]

horizontal_white [ ]|{h_tab}
whitespace {horizontal_white}|{v_tab}|{form_feed}

char_constant (L?\'([^\n'\\]|(\\.)|(\\\n))*\')
string_constant (L?\"([^\n"\\]|(\\.)|(\\\n))*\")

/************************************************************************/
/*              Commands.                                               */
/************************************************************************/

%%

%{
/* Some versions of flex define yywrap() as a macro.
   We define yywrap() as a function.
   Thus we must undefine yywrap(). (JAT) */

#undef yywrap
%}

\n                   { line_number++;
                       RETURN_WHITESPACE_TOKEN(yytext);
                     }
"//".*               { RETURN_WHITESPACE_TOKEN(""); }
{whitespace}+        { RETURN_WHITESPACE_TOKEN(""); }
#.*\n                { line_number++;
                       RETURN_WHITESPACE_TOKEN(yytext);
                       ECHO;
                     }

{integer_constant}   { RETURN_STRING_TOKEN(LITERAL); }
{floating_constant}  { RETURN_STRING_TOKEN(LITERAL); }

{char_constant}      { RETURN_STRING_TOKEN(LITERAL);}
{string_constant}    { RETURN_STRING_TOKEN(LITERAL);}

"("                  { RETURN_STRING_TOKEN('('); }
")"                  { RETURN_STRING_TOKEN(')'); }
","                  { RETURN_STRING_TOKEN(','); }
"#"                  { RETURN_STRING_TOKEN(LITERAL); }
"##"                 { RETURN_STRING_TOKEN(LITERAL); }

"{"                  { RETURN_STRING_TOKEN('{'); }
"}"                  { RETURN_STRING_TOKEN('}'); }
"["                  { RETURN_STRING_TOKEN('['); }
"]"                  { RETURN_STRING_TOKEN(']'); }
"."                  { RETURN_STRING_TOKEN('.'); }
"&"                  { RETURN_STRING_TOKEN(OP); }
"*"                  { RETURN_STRING_TOKEN(OP); }
"+"                  { RETURN_STRING_TOKEN(OP); }
"-"                  { RETURN_STRING_TOKEN(OP); }
"~"                  { RETURN_STRING_TOKEN(OP); }
"!"                  { RETURN_STRING_TOKEN(OP); }
"/"                  { RETURN_STRING_TOKEN(OP); }
"%"                  { RETURN_STRING_TOKEN(OP); }
"<"                  { RETURN_STRING_TOKEN(OP); }
">"                  { RETURN_STRING_TOKEN(OP); }
"^"                  { RETURN_STRING_TOKEN(OP); }
"|"                  { RETURN_STRING_TOKEN(OP); }
"?"                  { RETURN_STRING_TOKEN(OP); }
":"                  { RETURN_STRING_TOKEN(OP); }
";"                  { RETURN_STRING_TOKEN(';'); }
"="                  { RETURN_STRING_TOKEN('='); }

"$"                  { RETURN_STRING_TOKEN(OP); }

"->"                 { RETURN_STRING_TOKEN(OP); }
"++"                 { RETURN_STRING_TOKEN(OP); }
"--"                 { RETURN_STRING_TOKEN(OP); }
"<<"                 { RETURN_STRING_TOKEN(OP); }
">>"                 { RETURN_STRING_TOKEN(OP); }
"<="                 { RETURN_STRING_TOKEN(OP); }
">="                 { RETURN_STRING_TOKEN(OP); }
"=="                 { RETURN_STRING_TOKEN(OP); }
"!="                 { RETURN_STRING_TOKEN(OP); }
"&&"                 { RETURN_STRING_TOKEN(OP); }
"||"                 { RETURN_STRING_TOKEN(OP); }
"*="                 { RETURN_STRING_TOKEN(OP); }
"/="                 { RETURN_STRING_TOKEN(OP); }
"%="                 { RETURN_STRING_TOKEN(OP); }
"+="                 { RETURN_STRING_TOKEN(OP); }
"-="                 { RETURN_STRING_TOKEN(OP); }
"<<="                { RETURN_STRING_TOKEN(OP); }
">>="                { RETURN_STRING_TOKEN(OP); }
"&="                 { RETURN_STRING_TOKEN(OP); }
"^="                 { RETURN_STRING_TOKEN(OP); }
"|="                 { RETURN_STRING_TOKEN(OP); }
"..."                { RETURN_STRING_TOKEN(OP); }

with                 { RETURN_STRING_TOKEN(WITH); }
typex                { RETURN_STRING_TOKEN(TYPEX); }
of                   { RETURN_STRING_TOKEN(OF); }

anonymous            { RETURN_STRING_TOKEN(ANONYMOUS); }
at                   { RETURN_STRING_TOKEN(AT); }
at_most_one          { RETURN_STRING_TOKEN(AT_MOST_ONE_TOKEN); }
counter              { RETURN_STRING_TOKEN(COUNTER); }
filename             { RETURN_STRING_TOKEN(FILENAME); }
field                { RETURN_NUMERIC_TOKEN(FIELD); }
file                 { RETURN_NUMERIC_TOKEN(FILE_TOKEN); }
from                 { RETURN_STRING_TOKEN(FROM); }
is                   { RETURN_STRING_TOKEN(IS); }
key                  { RETURN_STRING_TOKEN(KEY); }
link                 { RETURN_STRING_TOKEN(LINK); }
many                 { RETURN_STRING_TOKEN(MANY_TOKEN); }
on                   { RETURN_STRING_TOKEN(ON); }
one                  { RETURN_STRING_TOKEN(ONE_TOKEN); }
option               { RETURN_STRING_TOKEN(OPTION); }
predicate            { RETURN_STRING_TOKEN(PREDICATE); }
size                 { RETURN_STRING_TOKEN(SIZE); }
timestamp            { RETURN_STRING_TOKEN(TIMESTAMP); }
to                   { RETURN_STRING_TOKEN(TO); }
where                { RETURN_STRING_TOKEN(WHERE); }

{identifier}         { RETURN_STRING_TOKEN(IDENTIFIER); }

.                    { parse_warning(4, "unknown character ignored"); }

%%
