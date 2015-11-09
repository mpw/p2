%{
/* Generated automatically from pb-lex.l.in by Makefile. */
%}
%p10000
%o5000
%n5000
%k1000
%e5000
%a5000
%{

/* $Id: pb-lex.l.in,v 45.0 1997/09/19 05:45:55 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* pb lexicographic analyzer (flex source file). */

/*

Derived from a source file by James A. Roskind (1990)
Original comments are retained for documentation purposes (DSB).

PREDATOR additions by JAT.

*/

/*

Comment  removal  must  be done during the lexing, as context (such as
enclosure in string literals) must be  observed.   For  this  cut-down
lexer,  we  will  assume that comments have been removed (don't assume
this if you are writing a compiler or browser!).

For each IDENTIFIER like string that is found,  there  are  several
distinct interpretations that can be applied:

1)  The  preprocessor  may  interpret  the  string as a "keyword" in a
directive (eg: "pragma" or "include", "defined").

2) The parser may interpret the string as a keyword. (eg: "int").

3) Both parser and preprocessor may interpret the string as a  keyword
(eg: "if").

Since  this  file  is based on source that actually lexically analyses
text for both preprocessing and parsing, macro definitions  were  used
throughout.   The macro definitions supplied here have been customized
to a C++ parse only, and  all  preprocessor  keywords  are  passed  as
IDENTIFIER  or  TYPEDEFname.   Also, since there is no symbol table to
interrogate to decide whether a string  is  a  TYPEDEFname,  I  simply
assume  that  any  identifier beginning with an upper case letter is a
TYPEDEFname.  This hack  should  allow  you  to  check  out  how  code
segments  are  parsed  using my grammar.  Unfortunately, if you really
want to parse major league code, you have to write a symbol table, and
maintain appropriate scoping information

(James  A.  Roskind).

*/

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>       /* NULL */
#include <string.h>      /* strcpy() */

#include "error.h"       /* parse_warning() */
#include "lex.h"         /* MAX_IDENT_LEN */
#include "op-tab.h"
#include "pb-type.h"
#include "util.h"
#include "xform.h"

#include "type.h"        /* NODE */
#include "pb-gram.tab.h" /* BISON-YACC generated defs based on C++ grammar */

/************************************************************************/
/*              YYLMAX.                                                 */
/************************************************************************/

/* Necessary for AT&T lex. */
#undef YYLMAX
#define YYLMAX MAX_IDENT_LEN

/************************************************************************/
/*              "Return" macros.                                        */
/************************************************************************/

/* Keyword. */

#define RETURN_KEYWORD_TOKEN(x) \
  RETURN_NODE_TOKEN(x, NULL)

/* Identifier. */

#define RETURN_IDENTIFIER_TOKEN() \
 RETURN_NODE_TOKEN((isaTYPE((char *) yytext)?TYPEDEFname:IDENTIFIER), NULL)

/* ASCII operator. */

#define RETURN_ASCII_OPERATOR_TOKEN(x) \
  RETURN_NODE_TOKEN(x, NULL)

/* Named, multi-character operator */

#define RETURN_NAMED_OPERATOR_TOKEN(x) \
  RETURN_NODE_TOKEN(x, NULL)

/* Constants. */

#define RETURN_CONSTANT_TOKEN(x, ctype) \
  RETURN_NODE_TOKEN(x, ctype)

%}

/************************************************************************/
/*              Definitions.                                            */
/************************************************************************/

/* The following definitions are common to all P2 lex files. (JAT) */

identifier [a-zA-Z_][0-9a-zA-Z_]*

integer_suffix_opt ([uU]?[lL]?)|([lL][uU])|LL|ULL
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

\n                  { line_number++;
                      RETURN_WHITESPACE_TOKEN((char *) yytext);
                    }
"//".*              { RETURN_WHITESPACE_TOKEN(""); }
{whitespace}+       { RETURN_WHITESPACE_TOKEN(""); }
#.*\n               { line_number++;
                      RETURN_WHITESPACE_TOKEN((char *) yytext);
                      ECHO;
                    }

asm|__asm|__asm__   { RETURN_KEYWORD_TOKEN(ASM); }
__attribute|__attribute__ { RETURN_KEYWORD_TOKEN(ATTRIBUTE); }
auto                { RETURN_KEYWORD_TOKEN(AUTO); }
break               { RETURN_KEYWORD_TOKEN(BREAK); }
case                { RETURN_KEYWORD_TOKEN(CASE); }
char                { RETURN_KEYWORD_TOKEN(CHAR); }
varchar             { RETURN_KEYWORD_TOKEN(VARCHAR); }
const|__const|__const__ { RETURN_KEYWORD_TOKEN(CONST); }
continue            { RETURN_KEYWORD_TOKEN(CONTINUE); }
default             { RETURN_KEYWORD_TOKEN(DEFAULT); }
do                  { RETURN_KEYWORD_TOKEN(DO); }
double              { RETURN_KEYWORD_TOKEN(DOUBLE); }
else                { RETURN_KEYWORD_TOKEN(ELSE); }
enum                { RETURN_KEYWORD_TOKEN(ENUM); }
extern              { RETURN_KEYWORD_TOKEN(EXTERN); }
float               { RETURN_KEYWORD_TOKEN(FLOAT); }
for                 { RETURN_KEYWORD_TOKEN(FOR); }
goto                { RETURN_KEYWORD_TOKEN(GOTO); }
if                  { RETURN_KEYWORD_TOKEN(IF); }
int                 { RETURN_KEYWORD_TOKEN(INT); }
inline|__inline|__inline__ { RETURN_KEYWORD_TOKEN(INLINE); }
__label__           { RETURN_KEYWORD_TOKEN(LABEL); }
long                { RETURN_KEYWORD_TOKEN(LONG); }
register            { RETURN_KEYWORD_TOKEN(REGISTER); }
return              { RETURN_KEYWORD_TOKEN(RETURN); }
short               { RETURN_KEYWORD_TOKEN(SHORT); }
signed|__signed|__signed__ { RETURN_KEYWORD_TOKEN(SIGNED); }
sizeof              { RETURN_KEYWORD_TOKEN(SIZEOF); }
static              { RETURN_KEYWORD_TOKEN(STATIC); }
struct              { RETURN_KEYWORD_TOKEN(STRUCT); }
switch              { RETURN_KEYWORD_TOKEN(SWITCH); }
typedef             { RETURN_KEYWORD_TOKEN(TYPEDEF); }
typeof|__typeof__   { RETURN_KEYWORD_TOKEN(TYPEOF); }
union               { RETURN_KEYWORD_TOKEN(UNION); }
unsigned            { RETURN_KEYWORD_TOKEN(UNSIGNED); }
void                { RETURN_KEYWORD_TOKEN(VOID); }
volatile|__volatile|__volatile__ { RETURN_KEYWORD_TOKEN(VOLATILE); }
while               { RETURN_KEYWORD_TOKEN(WHILE); }

ascending           { RETURN_KEYWORD_TOKEN(ASCENDING); }
compcurs            { RETURN_KEYWORD_TOKEN(COMPCURS); }
container           { RETURN_KEYWORD_TOKEN(CONTAINER); }
cursor              { RETURN_KEYWORD_TOKEN(CURSOR); }
descending          { RETURN_KEYWORD_TOKEN(DESCENDING); }
element             { RETURN_KEYWORD_TOKEN(ELEMENT); }
foreach             { RETURN_KEYWORD_TOKEN(FOREACH); }
foreachk            { RETURN_KEYWORD_TOKEN(FOREACHK); }
generic_container   { RETURN_KEYWORD_TOKEN(GENERIC_CONTAINER); }
generic_cursor      { RETURN_KEYWORD_TOKEN(GENERIC_CURSOR); }
given               { RETURN_KEYWORD_TOKEN(GIVEN); }
orderby             { RETURN_KEYWORD_TOKEN(ORDERBY); }
rofeach             { RETURN_KEYWORD_TOKEN(ROFEACH); }
schema              { RETURN_KEYWORD_TOKEN(SCHEMA); }
stored_as           { RETURN_KEYWORD_TOKEN(STORED_AS); }
P2_ddlhint          { RETURN_KEYWORD_TOKEN(P2_DDLHINT); }
P2_path             { RETURN_KEYWORD_TOKEN(P2_PATH); }
P2_typex            { RETURN_KEYWORD_TOKEN(P2_TYPEX); }
valid               { RETURN_KEYWORD_TOKEN(VALID); }
where               { RETURN_KEYWORD_TOKEN(WHERE); }

{identifier}        { RETURN_IDENTIFIER_TOKEN(); }

{integer_constant}  { RETURN_CONSTANT_TOKEN(INTEGERconstant,
                                            int_read_only_ctype); }
{floating_constant} { RETURN_CONSTANT_TOKEN(FLOATINGconstant,
                                            float_read_only_ctype); }

{char_constant}     { RETURN_CONSTANT_TOKEN(CHARACTERconstant,
                                            char_read_only_ctype); }
{string_constant}   { RETURN_CONSTANT_TOKEN(STRINGliteral,
                                            string_read_only_ctype); }

"("                 { RETURN_ASCII_OPERATOR_TOKEN(LP); }
")"                 { RETURN_ASCII_OPERATOR_TOKEN(RP); }
","                 { RETURN_ASCII_OPERATOR_TOKEN(COMMA); }
"{"                 { RETURN_ASCII_OPERATOR_TOKEN(LC); }
"}"                 { RETURN_ASCII_OPERATOR_TOKEN(RC); }
"["                 { RETURN_ASCII_OPERATOR_TOKEN(LB); }
"]"                 { RETURN_ASCII_OPERATOR_TOKEN(RB); }
"."                 { RETURN_ASCII_OPERATOR_TOKEN(DOT); }
"*"                 { RETURN_ASCII_OPERATOR_TOKEN(STAR); }
":"                 { RETURN_ASCII_OPERATOR_TOKEN(COLON); }
";"                 { RETURN_ASCII_OPERATOR_TOKEN(SEMICOLON); }
"="                 { RETURN_ASCII_OPERATOR_TOKEN(ASSIGN); }
"&"                 { RETURN_ASCII_OPERATOR_TOKEN(AND); }
"+"                 { RETURN_ASCII_OPERATOR_TOKEN(PLUS); }
"-"                 { RETURN_ASCII_OPERATOR_TOKEN(MINUS); }
"~"                 { RETURN_ASCII_OPERATOR_TOKEN(NEGATE); }
"!"                 { RETURN_ASCII_OPERATOR_TOKEN(NOT); }
"/"                 { RETURN_ASCII_OPERATOR_TOKEN(DIV); }
"%"                 { RETURN_ASCII_OPERATOR_TOKEN(MOD); }
"<"                 { RETURN_ASCII_OPERATOR_TOKEN(LT); }
">"                 { RETURN_ASCII_OPERATOR_TOKEN(GT); }
"^"                 { RETURN_ASCII_OPERATOR_TOKEN(XOR); }
"|"                 { RETURN_ASCII_OPERATOR_TOKEN(PIPE); }
"?"                 { RETURN_ASCII_OPERATOR_TOKEN(QUESTION); }

"$"                 { RETURN_ASCII_OPERATOR_TOKEN(DOLLAR); }

"->"                { RETURN_NAMED_OPERATOR_TOKEN(ARROW); }
"++"                { RETURN_NAMED_OPERATOR_TOKEN(INCR); }
"--"                { RETURN_NAMED_OPERATOR_TOKEN(DECR); }
"<<"		    { RETURN_NAMED_OPERATOR_TOKEN(LS); }
">>"                { RETURN_NAMED_OPERATOR_TOKEN(RS); }
"<="                { RETURN_NAMED_OPERATOR_TOKEN(LE); }
">="                { RETURN_NAMED_OPERATOR_TOKEN(GE); }
"=="                { RETURN_NAMED_OPERATOR_TOKEN(EQ); }
"!="                { RETURN_NAMED_OPERATOR_TOKEN(NE); }
"&&"                { RETURN_NAMED_OPERATOR_TOKEN(ANDAND); }
"||"                { RETURN_NAMED_OPERATOR_TOKEN(OROR); }
"..."               { RETURN_NAMED_OPERATOR_TOKEN(ELLIPSIS); }  
"*="                { RETURN_NAMED_OPERATOR_TOKEN(MULTassign); }
"/="                { RETURN_NAMED_OPERATOR_TOKEN(DIVassign); }
"%="                { RETURN_NAMED_OPERATOR_TOKEN(MODassign); }
"+="                { RETURN_NAMED_OPERATOR_TOKEN(PLUSassign); }
"-="                { RETURN_NAMED_OPERATOR_TOKEN(MINUSassign); }
"<<="               { RETURN_NAMED_OPERATOR_TOKEN(LSassign); }
">>="               { RETURN_NAMED_OPERATOR_TOKEN(RSassign); }
"&="                { RETURN_NAMED_OPERATOR_TOKEN(ANDassign); }
"^="                { RETURN_NAMED_OPERATOR_TOKEN(ERassign); }
"|="                { RETURN_NAMED_OPERATOR_TOKEN(ORassign); }

.                   { parse_warning(4, "unknown character ignored"); }

%%

