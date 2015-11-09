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
     ADD = 258,
     ADHOC = 259,
     ADV = 260,
     ALLOC = 261,
     VARALLOC = 262,
     P2_ANNOTATION = 263,
     ARGUMENT = 264,
     ARROW = 265,
     AS_CURSOR = 266,
     BANG_LINE = 267,
     CALL = 268,
     CHECKPOINT_CONT = 269,
     CLOSE_CONT = 270,
     CNSTATE = 271,
     COMMENT = 272,
     CONTAINER = 273,
     CONTAINER_FUNC = 274,
     CONTAINER_ID = 275,
     CONTAINER_TYPE = 276,
     CONT_STATE = 277,
     COST = 278,
     CRSTATE = 279,
     CURSOR = 280,
     CURSOR_FUNC = 281,
     CURSOR_ID = 282,
     CURSOR_TYPE = 283,
     CURS_STATE = 284,
     C_PUT_OP_VEC = 285,
     C_VERBATIM = 286,
     D2U = 287,
     DDLHINT = 288,
     DEF_CONTAINER_FUNC = 289,
     DEF_CURSOR_FUNC = 290,
     DELETE = 291,
     DELETE_CURS = 292,
     DOLLAR_WORD = 293,
     DS_TOKEN = 294,
     ELEMENT = 295,
     END_ADV = 296,
     END_FOREACH = 297,
     END_REV = 298,
     END_ROFEACH = 299,
     EXPR = 300,
     FIELD = 301,
     FOREACH = 302,
     FUNBODY = 303,
     GETREC = 304,
     HASH_IDENTIFIER = 305,
     IDENTIFIER = 306,
     INDIRECT_ONLY = 307,
     INIT_CONT = 308,
     INIT_CURS = 309,
     INSERT = 310,
     VARINSERT = 311,
     IREF = 312,
     K_VERBATIM = 313,
     K_PUT_OP_VEC = 314,
     LAYER = 315,
     LAYERNO = 316,
     LIMIT = 317,
     LITERAL = 318,
     L_VERBATIM = 319,
     MAPPED_VIA_PARAM = 320,
     MCURS = 321,
     MEM_TOKEN = 322,
     MULTIPLE = 323,
     NEW_CONTAINER_TYPE = 324,
     NO = 325,
     OBJ_TYPE = 326,
     OPEN_CONT = 327,
     OPEN_CONT_NUMBER = 328,
     OPLIST = 329,
     OPTIMIZE = 330,
     OPTIONAL = 331,
     ORDERBY_DIRECTION = 332,
     ORDERBY_FIELD = 333,
     ORIG_TYPE = 334,
     OVERFLOW = 335,
     VAROVERFLOW = 336,
     PADOT = 337,
     PANN = 338,
     POSITION = 339,
     PREDICATE = 340,
     PROCEDURALIZE_REF = 341,
     PSDOT = 342,
     QUERY = 343,
     RECORD = 344,
     REF = 345,
     REPLICATE = 346,
     RESET_END = 347,
     RESET_START = 348,
     P2_RETRIEVAL_ALWAYS = 349,
     P2_RETRIEVAL_DIRECTION = 350,
     P2_RETRIEVAL_NEVER = 351,
     P2_RETRIEVAL_SOMETIMES = 352,
     REV = 353,
     ROFEACH = 354,
     S_PUT_OP_VEC = 355,
     S_VERBATIM = 356,
     STABLE = 357,
     STRUCT = 358,
     SWAP = 359,
     SYNC_CONT = 360,
     TOP_TOKEN = 361,
     UNSTABLE = 362,
     UPD = 363,
     VALUE = 364,
     VPTOK = 365,
     WITH_TYPE = 366,
     XEND = 367,
     XFORM = 368,
     XSTART = 369,
     OPEN_SCHEMA = 370,
     INIT_SCHEMA = 371,
     CHECKPOINT_SCHEMA = 372,
     CLOSE_SCHEMA = 373,
     ABORT_XACT = 374,
     BEGIN_XACT = 375,
     COMMIT_XACT = 376,
     ADVC = 377,
     ADVP = 378,
     CONNECT = 379,
     DISCONNECT = 380,
     ENDC = 381,
     ENDP = 382,
     FOREACHC = 383,
     FOREACHL = 384,
     FOREACHP = 385,
     LOPTIMIZE = 386,
     RELATED = 387,
     RESETC = 388,
     RESETP = 389,
     APPLY = 390,
     BOUND = 391,
     CCARD = 392,
     COMPANION = 393,
     CRESIDUAL = 394,
     LINKANNOTE = 395,
     LINKCOST = 396,
     LINKLAYER = 397,
     LINKNAME = 398,
     LINKPREDICATE = 399,
     LSTATE = 400,
     PCARD = 401,
     PRESIDUAL = 402,
     SCHEMA = 403,
     SPECIAL = 404,
     LINK_TOKEN = 405,
     TOPLINK_TOKEN = 406
   };
#endif
/* Tokens.  */
#define ADD 258
#define ADHOC 259
#define ADV 260
#define ALLOC 261
#define VARALLOC 262
#define P2_ANNOTATION 263
#define ARGUMENT 264
#define ARROW 265
#define AS_CURSOR 266
#define BANG_LINE 267
#define CALL 268
#define CHECKPOINT_CONT 269
#define CLOSE_CONT 270
#define CNSTATE 271
#define COMMENT 272
#define CONTAINER 273
#define CONTAINER_FUNC 274
#define CONTAINER_ID 275
#define CONTAINER_TYPE 276
#define CONT_STATE 277
#define COST 278
#define CRSTATE 279
#define CURSOR 280
#define CURSOR_FUNC 281
#define CURSOR_ID 282
#define CURSOR_TYPE 283
#define CURS_STATE 284
#define C_PUT_OP_VEC 285
#define C_VERBATIM 286
#define D2U 287
#define DDLHINT 288
#define DEF_CONTAINER_FUNC 289
#define DEF_CURSOR_FUNC 290
#define DELETE 291
#define DELETE_CURS 292
#define DOLLAR_WORD 293
#define DS_TOKEN 294
#define ELEMENT 295
#define END_ADV 296
#define END_FOREACH 297
#define END_REV 298
#define END_ROFEACH 299
#define EXPR 300
#define FIELD 301
#define FOREACH 302
#define FUNBODY 303
#define GETREC 304
#define HASH_IDENTIFIER 305
#define IDENTIFIER 306
#define INDIRECT_ONLY 307
#define INIT_CONT 308
#define INIT_CURS 309
#define INSERT 310
#define VARINSERT 311
#define IREF 312
#define K_VERBATIM 313
#define K_PUT_OP_VEC 314
#define LAYER 315
#define LAYERNO 316
#define LIMIT 317
#define LITERAL 318
#define L_VERBATIM 319
#define MAPPED_VIA_PARAM 320
#define MCURS 321
#define MEM_TOKEN 322
#define MULTIPLE 323
#define NEW_CONTAINER_TYPE 324
#define NO 325
#define OBJ_TYPE 326
#define OPEN_CONT 327
#define OPEN_CONT_NUMBER 328
#define OPLIST 329
#define OPTIMIZE 330
#define OPTIONAL 331
#define ORDERBY_DIRECTION 332
#define ORDERBY_FIELD 333
#define ORIG_TYPE 334
#define OVERFLOW 335
#define VAROVERFLOW 336
#define PADOT 337
#define PANN 338
#define POSITION 339
#define PREDICATE 340
#define PROCEDURALIZE_REF 341
#define PSDOT 342
#define QUERY 343
#define RECORD 344
#define REF 345
#define REPLICATE 346
#define RESET_END 347
#define RESET_START 348
#define P2_RETRIEVAL_ALWAYS 349
#define P2_RETRIEVAL_DIRECTION 350
#define P2_RETRIEVAL_NEVER 351
#define P2_RETRIEVAL_SOMETIMES 352
#define REV 353
#define ROFEACH 354
#define S_PUT_OP_VEC 355
#define S_VERBATIM 356
#define STABLE 357
#define STRUCT 358
#define SWAP 359
#define SYNC_CONT 360
#define TOP_TOKEN 361
#define UNSTABLE 362
#define UPD 363
#define VALUE 364
#define VPTOK 365
#define WITH_TYPE 366
#define XEND 367
#define XFORM 368
#define XSTART 369
#define OPEN_SCHEMA 370
#define INIT_SCHEMA 371
#define CHECKPOINT_SCHEMA 372
#define CLOSE_SCHEMA 373
#define ABORT_XACT 374
#define BEGIN_XACT 375
#define COMMIT_XACT 376
#define ADVC 377
#define ADVP 378
#define CONNECT 379
#define DISCONNECT 380
#define ENDC 381
#define ENDP 382
#define FOREACHC 383
#define FOREACHL 384
#define FOREACHP 385
#define LOPTIMIZE 386
#define RELATED 387
#define RESETC 388
#define RESETP 389
#define APPLY 390
#define BOUND 391
#define CCARD 392
#define COMPANION 393
#define CRESIDUAL 394
#define LINKANNOTE 395
#define LINKCOST 396
#define LINKLAYER 397
#define LINKNAME 398
#define LINKPREDICATE 399
#define LSTATE 400
#define PCARD 401
#define PRESIDUAL 402
#define SCHEMA 403
#define SPECIAL 404
#define LINK_TOKEN 405
#define TOPLINK_TOKEN 406




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 229 "./xp-gram.y"
{
   char      str[MAX_IDENT_LEN];
   RLIST     *ptr;
   NODE      *node;
   ADHOC_ARG *aptr;
   int       i;
}
/* Line 1529 of yacc.c.  */
#line 359 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

