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
     IDENTIFIER = 258,
     OP = 259,
     LITERAL = 260,
     WITH = 261,
     TYPEX = 262,
     OF = 263,
     OPTION = 264,
     SIZE = 265,
     IS = 266,
     FILENAME = 267,
     FIELD = 268,
     ON = 269,
     KEY = 270,
     LINK = 271,
     PREDICATE = 272,
     TO = 273,
     FILE_TOKEN = 274,
     WHERE = 275,
     FROM = 276,
     ONE_TOKEN = 277,
     MANY_TOKEN = 278,
     AT_MOST_ONE_TOKEN = 279,
     AT = 280,
     COUNTER = 281,
     ANONYMOUS = 282,
     TIMESTAMP = 283,
     PRE_ACTION = 284,
     POST_ACTION = 285
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define OP 259
#define LITERAL 260
#define WITH 261
#define TYPEX 262
#define OF 263
#define OPTION 264
#define SIZE 265
#define IS 266
#define FILENAME 267
#define FIELD 268
#define ON 269
#define KEY 270
#define LINK 271
#define PREDICATE 272
#define TO 273
#define FILE_TOKEN 274
#define WHERE 275
#define FROM 276
#define ONE_TOKEN 277
#define MANY_TOKEN 278
#define AT_MOST_ONE_TOKEN 279
#define AT 280
#define COUNTER 281
#define ANONYMOUS 282
#define TIMESTAMP 283
#define PRE_ACTION 284
#define POST_ACTION 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "./ddl-gram.y"
{
  char     str[MAX_IDENT_LEN];
  LISTNODE *node;
}
/* Line 1529 of yacc.c.  */
#line 114 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

