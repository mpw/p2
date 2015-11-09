/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LP = 258,
     PTOK = 259,
     CONSTANTSYMBOLICATOM = 260,
     SEPRTR = 261,
     RP = 262,
     LCB = 263,
     RCB = 264,
     ATTRIBUTENAME = 265,
     PREDICATE = 266,
     VARIABLE = 267,
     FIXPTNO = 268,
     FLOATPTNO = 269,
     CBIND = 270,
     EQUAL = 271,
     LITERALIZE = 272,
     MAKE = 273,
     REMOVE = 274,
     MODIFY = 275,
     HALT = 276,
     BIND = 277,
     CALL = 278,
     WRITE = 279,
     OPENFILE = 280,
     CLOSEFILE = 281,
     DEFAULT = 282,
     LITVAL = 283,
     SUBSTR = 284,
     GENATOM = 285,
     CRLF = 286,
     RJUST = 287,
     ORLP = 288,
     ORRP = 289,
     TABTO = 290,
     ACCEPTLINE = 291,
     ACCEPT = 292,
     COMPUTE = 293,
     OPERATOR = 294,
     LITERAL = 295,
     VECTORATTR = 296,
     INCLUDE = 297,
     EXTERNAL = 298,
     VARIABLEOFFSET = 299,
     NIL = 300,
     STRING = 301,
     MINUS = 302,
     PLUS = 303,
     INTEGER = 304,
     FLOAT = 305,
     CHAR = 306,
     SYMBOLS = 307,
     MOD = 308,
     DIV = 309
   };
#endif
/* Tokens.  */
#define LP 258
#define PTOK 259
#define CONSTANTSYMBOLICATOM 260
#define SEPRTR 261
#define RP 262
#define LCB 263
#define RCB 264
#define ATTRIBUTENAME 265
#define PREDICATE 266
#define VARIABLE 267
#define FIXPTNO 268
#define FLOATPTNO 269
#define CBIND 270
#define EQUAL 271
#define LITERALIZE 272
#define MAKE 273
#define REMOVE 274
#define MODIFY 275
#define HALT 276
#define BIND 277
#define CALL 278
#define WRITE 279
#define OPENFILE 280
#define CLOSEFILE 281
#define DEFAULT 282
#define LITVAL 283
#define SUBSTR 284
#define GENATOM 285
#define CRLF 286
#define RJUST 287
#define ORLP 288
#define ORRP 289
#define TABTO 290
#define ACCEPTLINE 291
#define ACCEPT 292
#define COMPUTE 293
#define OPERATOR 294
#define LITERAL 295
#define VECTORATTR 296
#define INCLUDE 297
#define EXTERNAL 298
#define VARIABLEOFFSET 299
#define NIL 300
#define STRING 301
#define MINUS 302
#define PLUS 303
#define INTEGER 304
#define FLOAT 305
#define CHAR 306
#define SYMBOLS 307
#define MOD 308
#define DIV 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 44 "rl-gram.y"
{
   char *string ;
   FIELDTYPE ftype;
   NODE_PTR  node;
}
/* Line 1529 of yacc.c.  */
#line 163 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

