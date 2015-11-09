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
     AUTO = 258,
     DOUBLE = 259,
     INT = 260,
     STRUCT = 261,
     BREAK = 262,
     ELSE = 263,
     LONG = 264,
     SWITCH = 265,
     CASE = 266,
     ENUM = 267,
     REGISTER = 268,
     TYPEDEF = 269,
     CHAR = 270,
     EXTERN = 271,
     RETURN = 272,
     UNION = 273,
     CONST = 274,
     FLOAT = 275,
     SHORT = 276,
     UNSIGNED = 277,
     CONTINUE = 278,
     FOR = 279,
     SIGNED = 280,
     VOID = 281,
     DEFAULT = 282,
     GOTO = 283,
     SIZEOF = 284,
     VOLATILE = 285,
     DO = 286,
     IF = 287,
     STATIC = 288,
     WHILE = 289,
     COMMA = 290,
     DOT = 291,
     STAR = 292,
     COLON = 293,
     SEMICOLON = 294,
     ASSIGN = 295,
     AND = 296,
     PLUS = 297,
     MINUS = 298,
     NEGATE = 299,
     NOT = 300,
     DIV = 301,
     MOD = 302,
     LT = 303,
     GT = 304,
     XOR = 305,
     PIPE = 306,
     QUESTION = 307,
     LP = 308,
     RP = 309,
     LC = 310,
     RC = 311,
     LB = 312,
     RB = 313,
     VARCHAR = 314,
     CURSOR = 315,
     GENERIC_CURSOR = 316,
     CONTAINER = 317,
     GENERIC_CONTAINER = 318,
     SCHEMA = 319,
     STORED_AS = 320,
     WHERE = 321,
     FOREACH = 322,
     FOREACHK = 323,
     ROFEACH = 324,
     ASCENDING = 325,
     DESCENDING = 326,
     ORDERBY = 327,
     ELEMENT = 328,
     COMPCURS = 329,
     GIVEN = 330,
     VALID = 331,
     P2_DDLHINT = 332,
     P2_PATH = 333,
     P2_TYPEX = 334,
     DOLLAR = 335,
     ATTRIBUTE = 336,
     INLINE = 337,
     LABEL = 338,
     TYPEOF = 339,
     ASM = 340,
     IDENTIFIER = 341,
     STRINGliteral = 342,
     FLOATINGconstant = 343,
     INTEGERconstant = 344,
     CHARACTERconstant = 345,
     TYPEDEFname = 346,
     ARROW = 347,
     INCR = 348,
     DECR = 349,
     LS = 350,
     RS = 351,
     LE = 352,
     GE = 353,
     EQ = 354,
     NE = 355,
     ANDAND = 356,
     OROR = 357,
     ELLIPSIS = 358,
     MULTassign = 359,
     DIVassign = 360,
     MODassign = 361,
     PLUSassign = 362,
     MINUSassign = 363,
     LSassign = 364,
     RSassign = 365,
     ANDassign = 366,
     ERassign = 367,
     ORassign = 368
   };
#endif
/* Tokens.  */
#define AUTO 258
#define DOUBLE 259
#define INT 260
#define STRUCT 261
#define BREAK 262
#define ELSE 263
#define LONG 264
#define SWITCH 265
#define CASE 266
#define ENUM 267
#define REGISTER 268
#define TYPEDEF 269
#define CHAR 270
#define EXTERN 271
#define RETURN 272
#define UNION 273
#define CONST 274
#define FLOAT 275
#define SHORT 276
#define UNSIGNED 277
#define CONTINUE 278
#define FOR 279
#define SIGNED 280
#define VOID 281
#define DEFAULT 282
#define GOTO 283
#define SIZEOF 284
#define VOLATILE 285
#define DO 286
#define IF 287
#define STATIC 288
#define WHILE 289
#define COMMA 290
#define DOT 291
#define STAR 292
#define COLON 293
#define SEMICOLON 294
#define ASSIGN 295
#define AND 296
#define PLUS 297
#define MINUS 298
#define NEGATE 299
#define NOT 300
#define DIV 301
#define MOD 302
#define LT 303
#define GT 304
#define XOR 305
#define PIPE 306
#define QUESTION 307
#define LP 308
#define RP 309
#define LC 310
#define RC 311
#define LB 312
#define RB 313
#define VARCHAR 314
#define CURSOR 315
#define GENERIC_CURSOR 316
#define CONTAINER 317
#define GENERIC_CONTAINER 318
#define SCHEMA 319
#define STORED_AS 320
#define WHERE 321
#define FOREACH 322
#define FOREACHK 323
#define ROFEACH 324
#define ASCENDING 325
#define DESCENDING 326
#define ORDERBY 327
#define ELEMENT 328
#define COMPCURS 329
#define GIVEN 330
#define VALID 331
#define P2_DDLHINT 332
#define P2_PATH 333
#define P2_TYPEX 334
#define DOLLAR 335
#define ATTRIBUTE 336
#define INLINE 337
#define LABEL 338
#define TYPEOF 339
#define ASM 340
#define IDENTIFIER 341
#define STRINGliteral 342
#define FLOATINGconstant 343
#define INTEGERconstant 344
#define CHARACTERconstant 345
#define TYPEDEFname 346
#define ARROW 347
#define INCR 348
#define DECR 349
#define LS 350
#define RS 351
#define LE 352
#define GE 353
#define EQ 354
#define NE 355
#define ANDAND 356
#define OROR 357
#define ELLIPSIS 358
#define MULTassign 359
#define DIVassign 360
#define MODassign 361
#define PLUSassign 362
#define MINUSassign 363
#define LSassign 364
#define RSassign 365
#define ANDassign 366
#define ERassign 367
#define ORassign 368




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 174 "./pb-gram.y"
{
  NODE    *n;
  int      i;
}
/* Line 1529 of yacc.c.  */
#line 280 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

