/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 8 "./xp-gram.y"


/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <stdlib.h>       /* atoi() */
#include <string.h>       /* strcpy() */

#include "adhoc-arg.h"    /* ADHOC_ARG */
#include "error.h"        /* parse_error() */
#include "field.h"        /* add_new_cursor_field() */
#include "gen-layerdef.h" /* annotations */
#include "io.h"           /* SPRINT_BUF_SIZE */
#include "lex.h"          /* yytext */
#include "ref-util.h"     /* ref_util() */
#include "rlist.h"        /* RLIST */
#include "seen.h"         /* seen */
#include "string-util.h"  /* replace_string_inplace() */
#include "util.h"         /* BOOLEAN */
#include "xp-actions.h"   /* do_action() */
#include "xform.h"        /* ANNOTATION */
#include "xp-io.h"        /* out() */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

#define YYDEBUG 1         /* Pretty debugging code. */
#define YYERROR_VERBOSE 1 /* define as anything for verbose BISON errors. */

/*****************************************************************************/
/*                  Local variables.                                         */
/*****************************************************************************/

static BOOLEAN output_semicolon = FALSE; /* Should we output a semicolon? */

/* Left hand side of update statement. */

static BOOLEAN lhs_obj_field;            /* References obj field? */
static int     lhs_pnum;                 /* For assignment statement. */
static int     lhs_cnum;                 /* Numeric tag for cursor/container */
static char    *lhs_field;
static char    *lhs_rparam;
static BOOLEAN lhs_cursor_field;         /* References cursor field? */
static BOOLEAN lhs_unknown_fld;          /* Don't know name of lhs field. */

/*****************************************************************************/
/*                  Local forward references                                 */
/*****************************************************************************/

int  yylex(void);
void yyerror(char *s);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 467 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 480 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  164
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  392
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1089

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   406

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     156,   157,   161,     2,   154,     2,   163,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   158,   155,
       2,   162,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   152,     2,   153,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   159,     2,   160,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    11,    14,    16,    20,
      27,    28,    30,    32,    36,    38,    40,    42,    44,    46,
      48,    50,    53,    56,    58,    61,    64,    68,    70,    72,
      74,    76,    78,    80,    82,    84,    86,    88,    91,    94,
      96,    98,   103,   108,   113,   118,   123,   128,   133,   137,
     142,   149,   154,   161,   166,   171,   176,   183,   190,   199,
     206,   213,   220,   225,   230,   235,   240,   245,   250,   255,
     260,   265,   270,   277,   288,   295,   300,   307,   316,   323,
     330,   339,   343,   348,   353,   358,   363,   368,   373,   378,
     387,   396,   405,   414,   423,   432,   443,   454,   465,   474,
     483,   492,   501,   503,   510,   517,   521,   525,   526,   529,
     531,   533,   536,   540,   542,   546,   548,   550,   552,   554,
     555,   560,   561,   566,   569,   571,   574,   577,   580,   583,
     585,   588,   589,   594,   597,   598,   603,   605,   608,   613,
     620,   626,   633,   636,   641,   646,   655,   662,   669,   673,
     682,   684,   686,   688,   690,   692,   695,   699,   705,   707,
     709,   711,   713,   715,   717,   719,   721,   723,   725,   727,
     729,   731,   733,   735,   737,   739,   741,   743,   745,   747,
     749,   751,   753,   755,   757,   759,   761,   763,   765,   768,
     771,   774,   776,   778,   780,   782,   784,   786,   788,   790,
     792,   794,   796,   798,   800,   802,   804,   806,   808,   810,
     812,   814,   816,   818,   820,   822,   824,   826,   828,   830,
     832,   833,   838,   840,   842,   844,   846,   848,   850,   851,
     855,   860,   867,   875,   882,   886,   889,   891,   894,   897,
     900,   902,   905,   907,   910,   913,   915,   918,   922,   927,
     934,   938,   945,   947,   949,   951,   955,   956,   960,   962,
     964,   966,   967,   969,   971,   975,   980,   985,   990,   997,
    1002,  1007,  1014,  1019,  1026,  1033,  1042,  1051,  1060,  1064,
    1066,  1068,  1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,
    1087,  1090,  1093,  1096,  1098,  1100,  1102,  1104,  1106,  1108,
    1110,  1112,  1114,  1116,  1118,  1123,  1128,  1133,  1138,  1143,
    1148,  1153,  1158,  1163,  1170,  1175,  1180,  1187,  1196,  1203,
    1211,  1216,  1225,  1232,  1233,  1241,  1248,  1249,  1257,  1262,
    1269,  1274,  1279,  1284,  1289,  1296,  1307,  1314,  1321,  1328,
    1333,  1338,  1343,  1348,  1353,  1358,  1363,  1372,  1381,  1390,
    1399,  1410,  1421,  1432,  1441,  1450,  1453,  1454,  1459,  1461,
    1465,  1467,  1469,  1471,  1472,  1477,  1479,  1482,  1484,  1486,
    1489,  1493,  1496,  1500,  1502,  1504,  1506,  1509,  1512,  1516,
    1521,  1523,  1526,  1529,  1533,  1535,  1538,  1541,  1545,  1550,
    1553,  1555,  1557
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     165,     0,    -1,   169,   177,    -1,    -1,   167,    -1,   168,
      -1,   167,   168,    -1,    12,    -1,   166,   170,   174,    -1,
      60,   173,    51,   152,   171,   153,    -1,    -1,   172,    -1,
     173,    -1,   172,   154,   173,    -1,    39,    -1,    67,    -1,
     106,    -1,   150,    -1,   151,    -1,   175,    -1,   176,    -1,
     175,   176,    -1,    70,     8,    -1,     8,    -1,    68,     8,
      -1,    76,     8,    -1,    76,    68,     8,    -1,   102,    -1,
     107,    -1,    32,    -1,    29,    -1,    22,    -1,    52,    -1,
      96,    -1,    97,    -1,    94,    -1,   178,    -1,   177,   178,
      -1,   179,   186,    -1,   155,    -1,   168,    -1,    53,   156,
      18,   157,    -1,    30,   156,    25,   157,    -1,    31,   156,
      25,   157,    -1,    59,   156,    18,   157,    -1,    58,   156,
      18,   157,    -1,   100,   156,   148,   157,    -1,   101,   156,
     148,   157,    -1,    64,   156,   157,    -1,    88,   156,    25,
     157,    -1,    33,   156,    51,   154,    51,   157,    -1,    72,
     156,    18,   157,    -1,    73,   156,    18,   154,    45,   157,
      -1,    14,   156,    18,   157,    -1,    15,   156,    18,   157,
      -1,    80,   156,    18,   157,    -1,    81,   156,    18,   154,
      45,   157,    -1,    55,   156,    25,   154,    89,   157,    -1,
      56,   156,    25,   154,    89,   154,    45,   157,    -1,    90,
     156,    25,   154,    46,   157,    -1,    57,   156,    25,   154,
      46,   157,    -1,    84,   156,    25,   154,    45,   157,    -1,
      41,   156,    25,   157,    -1,    43,   156,    25,   157,    -1,
       5,   156,    25,   157,    -1,    75,   156,    25,   157,    -1,
      54,   156,    25,   157,    -1,    98,   156,    25,   157,    -1,
      36,   156,    25,   157,    -1,    37,   156,    25,   157,    -1,
      93,   156,    25,   157,    -1,    92,   156,    25,   157,    -1,
     104,   156,    25,   154,    25,   157,    -1,   105,   156,    18,
     154,    45,   154,    45,   154,    45,   157,    -1,    49,   156,
      25,   154,    89,   157,    -1,     6,   156,    25,   157,    -1,
       7,   156,    25,   154,    45,   157,    -1,   108,   156,    25,
     154,    46,   154,    45,   157,    -1,    47,   156,    25,   154,
      45,   157,    -1,    99,   156,    25,   154,    45,   157,    -1,
     113,   156,    40,   154,    18,   154,    25,   157,    -1,     4,
     182,   183,    -1,   115,   156,   148,   157,    -1,   116,   156,
     148,   157,    -1,   118,   156,   148,   157,    -1,   119,   156,
     148,   157,    -1,   120,   156,   148,   157,    -1,   121,   156,
     148,   157,    -1,   117,   156,   148,   157,    -1,   133,   156,
      25,   154,    25,   154,   145,   157,    -1,   134,   156,    25,
     154,    25,   154,   145,   157,    -1,   122,   156,    25,   154,
      25,   154,   145,   157,    -1,   123,   156,    25,   154,    25,
     154,   145,   157,    -1,   126,   156,    25,   154,    25,   154,
     145,   157,    -1,   127,   156,    25,   154,    25,   154,   145,
     157,    -1,   130,   156,    25,   154,    25,   154,   145,   154,
      45,   157,    -1,   128,   156,    25,   154,    25,   154,   145,
     154,    45,   157,    -1,   129,   156,    25,   154,    25,   154,
     145,   154,    45,   157,    -1,   132,   156,    25,   154,    25,
     154,   145,   157,    -1,   124,   156,    25,   154,    25,   154,
     145,   157,    -1,   125,   156,    25,   154,    25,   154,   145,
     157,    -1,   131,   156,    25,   154,    25,   154,   145,   157,
      -1,   180,    -1,    26,    51,   156,    25,   181,   157,    -1,
      19,    51,   156,    18,   181,   157,    -1,    35,   158,    38,
      -1,    34,   158,    38,    -1,    -1,   154,    63,    -1,    51,
      -1,    50,    -1,   156,   157,    -1,   156,   184,   157,    -1,
     185,    -1,   184,   154,   185,    -1,    25,    -1,    18,    -1,
     148,    -1,   110,    -1,    -1,   114,   187,   201,   112,    -1,
      -1,   159,   188,   189,   160,    -1,   159,   160,    -1,   190,
      -1,   189,   190,    -1,   195,   155,    -1,   197,   155,    -1,
     194,   155,    -1,   191,    -1,   194,   191,    -1,    -1,   159,
     192,   189,   160,    -1,   159,   160,    -1,    -1,   114,   193,
     201,   112,    -1,   200,    -1,   194,   200,    -1,     3,   196,
     158,   227,    -1,     3,   196,   158,    66,    51,    51,    -1,
       3,   196,   158,    66,    51,    -1,    69,    51,   111,    51,
      65,    63,    -1,    91,    11,    -1,   138,    51,    65,    63,
      -1,    75,   156,    25,   157,    -1,   113,   156,    40,   154,
      18,   154,    25,   157,    -1,    13,    51,   156,    25,   181,
     157,    -1,    13,    51,   156,    18,   181,   157,    -1,     4,
     182,   218,    -1,   131,   156,    25,   154,    25,   154,   145,
     157,    -1,    51,    -1,    18,    -1,    40,    -1,    25,    -1,
     148,    -1,    70,     8,    -1,    62,    63,     9,    -1,    62,
      63,     8,    63,     9,    -1,    51,    -1,    17,    -1,    39,
      -1,    67,    -1,   106,    -1,   103,    -1,    40,    -1,   152,
      -1,   153,    -1,   156,    -1,   157,    -1,   154,    -1,   158,
      -1,   161,    -1,   162,    -1,    38,    -1,    18,    -1,    20,
      -1,    21,    -1,    25,    -1,    27,    -1,    28,    -1,    85,
      -1,    89,    -1,    46,    -1,    45,    -1,   110,    -1,    79,
      -1,    71,    -1,    83,    -1,    82,    51,    -1,    24,    51,
      -1,    16,    51,    -1,    61,    -1,    60,    -1,    23,    -1,
      48,    -1,    74,    -1,    86,    -1,    78,    -1,    77,    -1,
      95,    -1,   148,    -1,   144,    -1,   142,    -1,   141,    -1,
     139,    -1,   147,    -1,   135,    -1,   140,    -1,   143,    -1,
     146,    -1,   137,    -1,   136,    -1,   145,    -1,   149,    -1,
     198,    -1,   163,    -1,    10,    -1,    63,    -1,   199,    -1,
     204,    -1,    -1,   201,   203,   202,   204,    -1,   155,    -1,
     159,    -1,   160,    -1,   215,    -1,   222,    -1,   225,    -1,
      -1,    25,   163,   207,    -1,    25,   163,   163,   207,    -1,
      25,   163,   207,   152,   206,   153,    -1,    25,   163,   163,
     207,   152,   206,   153,    -1,   205,    10,   207,   152,   206,
     153,    -1,   205,    10,   207,    -1,   109,    51,    -1,    63,
      -1,    24,    51,    -1,    16,    51,    -1,    82,    51,    -1,
      51,    -1,   109,    51,    -1,    46,    -1,    24,    51,    -1,
      16,    51,    -1,    51,    -1,    82,    51,    -1,    18,   163,
     207,    -1,    18,   163,   163,   207,    -1,    18,   163,   207,
     152,   206,   153,    -1,   208,    10,   207,    -1,   208,    10,
     207,   152,   206,   153,    -1,   205,    -1,   210,    -1,   208,
      -1,   148,   163,   207,    -1,    -1,   198,   211,   212,    -1,
      63,    -1,   213,    -1,   214,    -1,    -1,    10,    -1,   163,
      -1,   163,   163,    51,    -1,    41,   156,    25,   157,    -1,
      43,   156,    25,   157,    -1,     6,   156,    25,   157,    -1,
       7,   156,    25,   154,    45,   157,    -1,    80,   156,    18,
     157,    -1,    81,   156,    18,   157,    -1,    84,   156,    25,
     154,    45,   157,    -1,    88,   156,    25,   157,    -1,    90,
     156,    25,   154,    46,   157,    -1,    57,   156,    25,   154,
      46,   157,    -1,   126,   156,    25,   154,    25,   154,   145,
     157,    -1,   127,   156,    25,   154,    25,   154,   145,   157,
      -1,   132,   156,    25,   154,    25,   154,   145,   157,    -1,
       4,   182,   218,    -1,    25,    -1,    18,    -1,    20,    -1,
      21,    -1,    27,    -1,    85,    -1,    79,    -1,    71,    -1,
      28,    -1,    89,    -1,    82,    51,    -1,    24,    51,    -1,
      16,    51,    -1,   109,    51,    -1,    45,    -1,    46,    -1,
      78,    -1,    77,    -1,    95,    -1,   110,    -1,   148,    -1,
     144,    -1,   142,    -1,   140,    -1,   143,    -1,    53,   156,
      18,   157,    -1,    30,   156,    25,   157,    -1,    31,   156,
      25,   157,    -1,    59,   156,    25,   157,    -1,    58,   156,
      18,   157,    -1,   100,   156,    25,   157,    -1,   101,   156,
     148,   157,    -1,    54,   156,    25,   157,    -1,    72,   156,
      18,   157,    -1,    73,   156,    18,   154,    45,   157,    -1,
      14,   156,    18,   157,    -1,    15,   156,    18,   157,    -1,
      55,   156,    25,   154,    89,   157,    -1,    56,   156,    25,
     154,    89,   154,    45,   157,    -1,    55,   156,    25,   154,
      51,   157,    -1,    55,   156,    25,   154,   109,    51,   157,
      -1,     5,   156,    25,   157,    -1,   108,   156,    25,   154,
      46,   154,    45,   157,    -1,    47,   156,    25,   154,    45,
     157,    -1,    -1,    47,   156,    25,   157,   216,   201,    42,
      -1,    99,   156,    25,   154,    45,   157,    -1,    -1,    99,
     156,    25,   157,   217,   201,    44,    -1,    98,   156,    25,
     157,    -1,    90,   156,    25,   154,    51,   157,    -1,    36,
     156,    25,   157,    -1,    37,   156,    25,   157,    -1,    93,
     156,    25,   157,    -1,    92,   156,    25,   157,    -1,   104,
     156,    25,   154,    25,   157,    -1,   105,   156,    18,   154,
      45,   154,    45,   154,    45,   157,    -1,    49,   156,    25,
     154,    89,   157,    -1,    13,    51,   156,    25,   181,   157,
      -1,    13,    51,   156,    18,   181,   157,    -1,   115,   156,
     148,   157,    -1,   116,   156,   148,   157,    -1,   118,   156,
     148,   157,    -1,   119,   156,   148,   157,    -1,   120,   156,
     148,   157,    -1,   121,   156,   148,   157,    -1,   117,   156,
     148,   157,    -1,   133,   156,    25,   154,    25,   154,   145,
     157,    -1,   134,   156,    25,   154,    25,   154,   145,   157,
      -1,   122,   156,    25,   154,    25,   154,   145,   157,    -1,
     123,   156,    25,   154,    25,   154,   145,   157,    -1,   129,
     156,    25,   154,    25,   154,   145,   154,    45,   157,    -1,
     128,   156,    25,   154,    25,   154,   145,   154,    45,   157,
      -1,   130,   156,    25,   154,    25,   154,   145,   154,    45,
     157,    -1,   124,   156,    25,   154,    25,   154,   145,   157,
      -1,   125,   156,    25,   154,    25,   154,   145,   157,    -1,
     156,   157,    -1,    -1,   156,   219,   220,   157,    -1,   221,
      -1,   220,   154,   221,    -1,    25,    -1,    18,    -1,   110,
      -1,    -1,   205,   162,   223,   224,    -1,   209,    -1,   224,
     209,    -1,   226,    -1,   210,    -1,   210,   224,    -1,   103,
     196,   228,    -1,    51,   228,    -1,    82,    51,   228,    -1,
     229,    -1,   231,    -1,   230,    -1,   161,   228,    -1,   231,
     232,    -1,   156,   229,   157,    -1,   156,   229,   157,   232,
      -1,    51,    -1,    82,    51,    -1,   109,    51,    -1,   156,
     231,   157,    -1,   233,    -1,   156,   157,    -1,   152,   153,
      -1,   152,   234,   153,    -1,   233,   152,   234,   153,    -1,
      82,    51,    -1,    51,    -1,    63,    -1,   109,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   383,   383,   393,   395,   399,   400,   404,   414,   418,
     426,   429,   433,   434,   441,   445,   449,   453,   457,   477,
     485,   486,   490,   492,   494,   496,   498,   500,   502,   504,
     506,   508,   510,   512,   514,   516,   527,   528,   532,   536,
     539,   547,   549,   551,   553,   555,   557,   559,   561,   563,
     567,   572,   574,   576,   578,   580,   582,   584,   586,   588,
     590,   592,   594,   598,   602,   606,   610,   612,   616,   618,
     620,   624,   628,   633,   635,   637,   639,   641,   643,   645,
     647,   651,   656,   658,   660,   663,   665,   667,   669,   674,
     679,   684,   689,   694,   699,   704,   709,   714,   719,   722,
     725,   728,   733,   744,   747,   750,   753,   760,   762,   788,
     789,   797,   798,   802,   803,   807,   808,   809,   810,   827,
     826,   835,   834,   840,   875,   876,   885,   886,   887,   890,
     891,   896,   895,   903,   907,   906,   915,   918,   935,   955,
     962,   965,   983,   992,  1004,  1017,  1028,  1034,  1040,  1045,
    1066,  1067,  1068,  1069,  1070,  1082,  1086,  1092,  1112,  1115,
    1120,  1123,  1126,  1129,  1132,  1135,  1138,  1141,  1144,  1147,
    1150,  1153,  1156,  1159,  1174,  1178,  1183,  1187,  1191,  1195,
    1199,  1203,  1206,  1209,  1212,  1215,  1219,  1224,  1229,  1236,
    1239,  1242,  1245,  1249,  1253,  1257,  1262,  1267,  1272,  1277,
    1286,  1308,  1312,  1316,  1320,  1324,  1328,  1332,  1337,  1341,
    1345,  1349,  1353,  1356,  1372,  1373,  1376,  1379,  1398,  1412,
    1416,  1415,  1426,  1429,  1432,  1438,  1442,  1446,  1450,  1478,
    1483,  1488,  1493,  1498,  1502,  1524,  1528,  1532,  1536,  1540,
    1552,  1574,  1578,  1582,  1586,  1590,  1594,  1623,  1628,  1634,
    1638,  1642,  1670,  1674,  1678,  1682,  1688,  1687,  1693,  1698,
    1699,  1702,  1704,  1708,  1712,  1725,  1727,  1729,  1731,  1733,
    1735,  1737,  1739,  1741,  1743,  1748,  1750,  1752,  1757,  1768,
    1772,  1776,  1781,  1785,  1789,  1793,  1797,  1801,  1805,  1808,
    1820,  1823,  1826,  1829,  1841,  1844,  1848,  1852,  1856,  1863,
    1886,  1890,  1894,  1898,  1911,  1913,  1915,  1917,  1919,  1921,
    1923,  1929,  1931,  1933,  1935,  1937,  1939,  1941,  1943,  1950,
    1957,  1959,  1961,  1964,  1963,  1977,  1980,  1979,  1992,  1994,
    1996,  1998,  2000,  2002,  2004,  2006,  2008,  2010,  2017,  2027,
    2029,  2031,  2034,  2036,  2038,  2040,  2045,  2047,  2049,  2051,
    2053,  2055,  2057,  2059,  2061,  2070,  2073,  2072,  2079,  2080,
    2084,  2086,  2088,  2116,  2115,  2178,  2179,  2195,  2200,  2201,
    2216,  2220,  2223,  2229,  2230,  2234,  2235,  2241,  2242,  2243,
    2247,  2251,  2264,  2268,  2272,  2273,  2279,  2282,  2285,  2291,
    2305,  2308,  2311
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "ADHOC", "ADV", "ALLOC",
  "VARALLOC", "P2_ANNOTATION", "ARGUMENT", "ARROW", "AS_CURSOR",
  "BANG_LINE", "CALL", "CHECKPOINT_CONT", "CLOSE_CONT", "CNSTATE",
  "COMMENT", "CONTAINER", "CONTAINER_FUNC", "CONTAINER_ID",
  "CONTAINER_TYPE", "CONT_STATE", "COST", "CRSTATE", "CURSOR",
  "CURSOR_FUNC", "CURSOR_ID", "CURSOR_TYPE", "CURS_STATE", "C_PUT_OP_VEC",
  "C_VERBATIM", "D2U", "DDLHINT", "DEF_CONTAINER_FUNC", "DEF_CURSOR_FUNC",
  "DELETE", "DELETE_CURS", "DOLLAR_WORD", "DS_TOKEN", "ELEMENT", "END_ADV",
  "END_FOREACH", "END_REV", "END_ROFEACH", "EXPR", "FIELD", "FOREACH",
  "FUNBODY", "GETREC", "HASH_IDENTIFIER", "IDENTIFIER", "INDIRECT_ONLY",
  "INIT_CONT", "INIT_CURS", "INSERT", "VARINSERT", "IREF", "K_VERBATIM",
  "K_PUT_OP_VEC", "LAYER", "LAYERNO", "LIMIT", "LITERAL", "L_VERBATIM",
  "MAPPED_VIA_PARAM", "MCURS", "MEM_TOKEN", "MULTIPLE",
  "NEW_CONTAINER_TYPE", "NO", "OBJ_TYPE", "OPEN_CONT", "OPEN_CONT_NUMBER",
  "OPLIST", "OPTIMIZE", "OPTIONAL", "ORDERBY_DIRECTION", "ORDERBY_FIELD",
  "ORIG_TYPE", "OVERFLOW", "VAROVERFLOW", "PADOT", "PANN", "POSITION",
  "PREDICATE", "PROCEDURALIZE_REF", "PSDOT", "QUERY", "RECORD", "REF",
  "REPLICATE", "RESET_END", "RESET_START", "P2_RETRIEVAL_ALWAYS",
  "P2_RETRIEVAL_DIRECTION", "P2_RETRIEVAL_NEVER", "P2_RETRIEVAL_SOMETIMES",
  "REV", "ROFEACH", "S_PUT_OP_VEC", "S_VERBATIM", "STABLE", "STRUCT",
  "SWAP", "SYNC_CONT", "TOP_TOKEN", "UNSTABLE", "UPD", "VALUE", "VPTOK",
  "WITH_TYPE", "XEND", "XFORM", "XSTART", "OPEN_SCHEMA", "INIT_SCHEMA",
  "CHECKPOINT_SCHEMA", "CLOSE_SCHEMA", "ABORT_XACT", "BEGIN_XACT",
  "COMMIT_XACT", "ADVC", "ADVP", "CONNECT", "DISCONNECT", "ENDC", "ENDP",
  "FOREACHC", "FOREACHL", "FOREACHP", "LOPTIMIZE", "RELATED", "RESETC",
  "RESETP", "APPLY", "BOUND", "CCARD", "COMPANION", "CRESIDUAL",
  "LINKANNOTE", "LINKCOST", "LINKLAYER", "LINKNAME", "LINKPREDICATE",
  "LSTATE", "PCARD", "PRESIDUAL", "SCHEMA", "SPECIAL", "LINK_TOKEN",
  "TOPLINK_TOKEN", "'['", "']'", "','", "';'", "'('", "')'", "':'", "'{'",
  "'}'", "'*'", "'='", "'.'", "$accept", "program", "bang_line_opt",
  "bang_line_list", "bang_line", "layer_dcl", "layer_stmt",
  "realm_list_opt", "realm_list", "realm", "layer_options", "lopt_list",
  "lopt", "xp_stmts", "xp_stmt", "procs", "user_funcs", "opt_literal",
  "adhoc_id", "adhoc_formal_args", "adhoc_formal_arg_list",
  "adhoc_formal_arg", "body", "@1", "@2", "itoken_stmts", "itoken_stmt",
  "itoken_body", "@3", "@4", "itoken_list", "iprocs", "structure",
  "ddlhints", "btoken", "ikeyword", "itoken", "ctoken_stmts", "@5", "eos",
  "stmt", "ref", "index", "field", "kref", "ctoken", "ctoknr", "@6",
  "opt_follow", "cxprocs", "ckeyword", "cprocs", "@7", "@8",
  "adhoc_actual_args", "@9", "adhoc_actual_arg_list", "adhoc_actual_arg",
  "update", "@10", "left_hand_side", "no_update", "n_upd", "declaration",
  "identifier_declarator", "unary_identifier_declarator",
  "postfix_identifier_declarator", "paren_identifier_declarator",
  "postfixing_abstract_declarator", "array_abstract_declarator",
  "constant_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,    91,    93,    44,    59,    40,    41,    58,   123,
     125,    42,    61,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   164,   165,   166,   166,   167,   167,   168,   169,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   173,   174,
     175,   175,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   177,   178,   178,
     178,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   180,   180,   180,   180,   181,   181,   182,
     182,   183,   183,   184,   184,   185,   185,   185,   185,   187,
     186,   188,   186,   186,   189,   189,   190,   190,   190,   190,
     190,   192,   191,   191,   193,   191,   194,   194,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     196,   196,   196,   196,   196,   197,   197,   197,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   200,   200,   200,   200,   200,   201,
     202,   201,   203,   203,   203,   204,   204,   204,   204,   205,
     205,   205,   205,   205,   205,   206,   206,   206,   206,   206,
     206,   207,   207,   207,   207,   207,   207,   208,   208,   208,
     208,   208,   209,   209,   210,   210,   211,   210,   210,   210,
     210,   212,   212,   212,   212,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   216,   215,   215,   217,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   218,   219,   218,   220,   220,
     221,   221,   221,   223,   222,   224,   224,   225,   226,   226,
     227,   227,   227,   228,   228,   229,   229,   230,   230,   230,
     231,   231,   231,   231,   232,   232,   233,   233,   233,   234,
     234,   234,   234
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     2,     1,     3,     6,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     4,     4,     4,     4,     4,     4,     4,     3,     4,
       6,     4,     6,     4,     4,     4,     6,     6,     8,     6,
       6,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     6,    10,     6,     4,     6,     8,     6,     6,
       8,     3,     4,     4,     4,     4,     4,     4,     4,     8,
       8,     8,     8,     8,     8,    10,    10,    10,     8,     8,
       8,     8,     1,     6,     6,     3,     3,     0,     2,     1,
       1,     2,     3,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     2,     1,     2,     2,     2,     2,     1,
       2,     0,     4,     2,     0,     4,     1,     2,     4,     6,
       5,     6,     2,     4,     4,     8,     6,     6,     3,     8,
       1,     1,     1,     1,     1,     2,     3,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     0,     3,
       4,     6,     7,     6,     3,     2,     1,     2,     2,     2,
       1,     2,     1,     2,     2,     1,     2,     3,     4,     6,
       3,     6,     1,     1,     1,     3,     0,     3,     1,     1,
       1,     0,     1,     1,     3,     4,     4,     4,     6,     4,
       4,     6,     4,     6,     6,     8,     8,     8,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     6,     4,     4,     6,     8,     6,     7,
       4,     8,     6,     0,     7,     6,     0,     7,     4,     6,
       4,     4,     4,     4,     6,    10,     6,     6,     6,     4,
       4,     4,     4,     4,     4,     4,     8,     8,     8,     8,
      10,    10,    10,     8,     8,     2,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     1,     2,     1,     1,     2,
       3,     2,     3,     1,     1,     1,     2,     2,     3,     4,
       1,     2,     2,     3,     1,     2,     2,     3,     4,     2,
       1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     7,     0,     0,     4,     5,     0,     1,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    40,     2,    36,
       0,   102,    14,    15,    16,    17,    18,     0,    23,    31,
      30,    29,    32,     0,     0,     0,    35,    33,    34,    27,
      28,     8,    19,    20,   110,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,   119,   121,    38,     0,    24,    22,    25,     0,
      21,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   228,   123,     0,
      10,    26,   116,   115,   118,   117,   111,     0,   113,    64,
      75,     0,    53,    54,   107,   107,    42,    43,     0,    68,
      69,    62,    63,     0,     0,    41,    66,     0,     0,     0,
      45,    44,    51,     0,    65,    55,     0,     0,    49,     0,
      71,    70,    67,     0,    46,    47,     0,     0,     0,     0,
      82,    83,    88,    84,    85,    86,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   280,
     281,   282,     0,   279,   283,   287,     0,     0,     0,     0,
     173,   160,   164,     0,     0,   293,   294,     0,     0,   158,
       0,     0,     0,     0,     0,     0,     0,   258,   161,   286,
       0,     0,   296,   295,   285,     0,     0,     0,     0,   284,
       0,   288,     0,     0,     0,   297,     0,     0,     0,     0,
     163,     0,     0,   162,     0,     0,   298,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   302,   301,   303,   300,
     299,   165,   166,   169,   167,   168,   170,   171,   172,   256,
       0,   219,     0,   254,   368,   259,   260,   225,   226,   227,
     367,     0,     0,   216,     0,     0,   174,   175,   176,   193,
       0,   177,   178,   179,   183,   182,   194,   192,   191,     0,
     217,     0,     0,   186,   195,     0,   198,   197,   185,     0,
     187,   180,   196,   181,     0,   199,   184,     0,   134,     0,
     206,   211,   210,     0,   204,   207,   203,   202,   208,   201,
     212,   209,   205,   200,   213,   131,   215,     0,   124,   129,
       0,     0,     0,   214,   218,   136,     0,    11,    12,     0,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     291,     0,   290,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   292,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   261,   120,   222,
     223,   224,   220,     0,   363,     0,     0,   252,   365,   253,
     369,   151,   153,   152,   150,   154,     0,     0,     0,   190,
     189,     0,     0,   155,     0,   188,   142,     0,   228,     0,
       0,   133,     0,   122,   125,   128,   130,   137,   126,   127,
       9,     0,   114,    76,   108,   104,   103,    50,    78,    74,
      57,     0,    60,    52,    56,    61,    59,    79,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   356,   278,     0,     0,     0,
       0,     0,     0,     0,     0,   242,   245,     0,     0,     0,
     247,     0,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   255,   262,   263,   257,   228,   234,     0,
     250,     0,   366,     0,   148,     0,     0,   156,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   355,     0,   320,   267,     0,   107,   107,
     314,   315,   244,   243,   246,   241,   248,     0,   230,     0,
     305,   306,   330,   331,   265,   266,     0,   323,     0,   304,
     311,     0,     0,     0,   308,   307,   312,     0,   269,   270,
       0,   272,     0,   333,   332,   328,     0,   326,   309,   310,
       0,     0,     0,   339,   340,   345,   341,   342,   343,   344,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   221,     0,   364,     0,     0,     0,     0,
       0,     0,   138,   107,   107,     0,     0,   144,     0,   135,
       0,   143,   132,    58,     0,    77,    80,    91,    92,    99,
     100,    93,    94,     0,     0,     0,   101,    98,    89,    90,
     361,   360,   362,     0,   358,     0,     0,     0,     0,     0,
     240,   236,     0,     0,     0,     0,     0,     0,   228,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     228,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   264,     0,     0,     0,
     380,     0,     0,     0,     0,   371,   373,   375,   374,   140,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,   357,   268,   338,   337,   238,   237,   239,
     235,   249,     0,   231,   322,     0,   336,   318,   316,     0,
       0,   274,   313,   271,   273,   329,   325,     0,   334,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   233,   251,   381,   382,     0,     0,   376,
       0,     0,   377,   384,   139,   372,   370,   147,   146,   141,
       0,     0,    73,    96,    97,    95,   359,   232,   324,   319,
       0,   327,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   383,   390,   391,
       0,     0,   386,     0,   385,     0,     0,     0,   317,     0,
     321,   348,   349,   353,   354,   275,   276,     0,     0,     0,
     277,   346,   347,   379,   389,   392,   387,     0,   145,   149,
       0,     0,     0,     0,   388,   335,   351,   350,   352
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    77,     6,     9,   496,   497,    87,
     101,   102,   103,    78,    79,    80,    81,   503,   106,   182,
     257,   258,   174,   247,   249,   487,   488,   489,   632,   628,
     490,   491,   616,   492,   419,   494,   495,   420,   747,   602,
     421,   422,   904,   690,   423,   608,   424,   597,   746,   425,
     426,   427,   908,   920,   676,   784,   893,   894,   428,   749,
     610,   429,   430,   862,   945,   946,   947,   948,  1012,  1013,
    1053
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -914
static const yytype_int16 yypact[] =
{
       8,  -914,    36,     1,     8,  -914,  1032,  -914,    50,  1159,
    -914,    52,   -75,   -71,   -61,   -25,   -24,    75,    86,   -18,
      21,    26,    25,    28,    40,    48,    51,    53,    58,    65,
      68,    70,    76,    82,    89,    91,   103,   104,   107,   111,
     112,   115,   120,   123,   126,   133,   137,   138,   139,   140,
     143,   144,   146,   147,   148,   150,   151,   154,   155,   156,
     157,   159,   160,   161,   162,   164,   165,   167,   168,   169,
     190,   194,   203,   204,   205,   206,  -914,  -914,  1032,  -914,
    -101,  -914,  -914,  -914,  -914,  -914,  -914,   141,  -914,  -914,
    -914,  -914,  -914,   219,   223,    38,  -914,  -914,  -914,  -914,
    -914,  -914,  1159,  -914,  -914,  -914,   207,   211,   225,   297,
     346,   347,   212,   213,   342,   345,   320,   334,   335,   349,
     350,   351,   353,   354,   355,   363,   357,   358,   362,   364,
     368,   370,   233,   373,   374,   371,   379,   380,   376,   377,
     384,   391,   394,   395,   396,   251,   256,   397,   387,   398,
     385,   278,   279,   283,   284,   289,   291,   292,   417,   419,
     420,   421,   422,   423,   424,   429,   430,   431,   433,   437,
     438,  -914,  -914,   306,  -914,   319,  -914,  -914,  -914,   466,
    -914,    45,  -914,   321,   323,   328,   326,   327,   459,   461,
     330,   331,   336,  -914,  -914,   332,   337,   338,   340,   344,
     348,   352,   356,   360,   365,   366,   383,   388,  -914,   393,
     400,   399,   401,   403,   405,   404,   406,   407,   408,   409,
     413,   415,   416,   432,   436,   439,   442,   418,   426,   440,
     449,   451,   455,   457,   462,   470,   471,   472,   474,   475,
     476,   478,   479,   480,   484,   485,   486,   564,  -914,   390,
      50,  -914,  -914,  -914,  -914,  -914,  -914,   -47,  -914,  -914,
    -914,   446,  -914,  -914,   493,   493,  -914,  -914,   441,  -914,
    -914,  -914,  -914,   454,   412,  -914,  -914,   428,   452,   460,
    -914,  -914,  -914,   463,  -914,  -914,   465,   467,  -914,   469,
    -914,  -914,  -914,   473,  -914,  -914,   482,   477,   509,   487,
    -914,  -914,  -914,  -914,  -914,  -914,  -914,   537,   538,   549,
     551,   562,   625,   626,   630,   633,   635,   636,   641,   646,
      52,   519,   520,   521,   627,   539,   543,   649,  -914,   540,
    -914,  -914,   650,   542,  -914,  -914,   546,   553,   554,   555,
    -914,  -914,  -914,   557,   558,  -914,  -914,   559,   563,  -914,
     567,   568,   572,   575,   576,   577,   578,  -914,  -914,  -914,
     579,   580,  -914,  -914,  -914,   581,   582,   691,   589,  -914,
     590,  -914,   593,   596,   597,  -914,   598,   599,   600,   601,
    -914,   602,   603,  -914,   604,   714,  -914,   611,   614,   615,
     616,   617,   619,   620,   621,   622,   623,   628,   629,   631,
     632,   637,   639,   640,   642,   643,  -914,  -914,  -914,  -914,
     618,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
      94,  -914,     9,   501,   723,  -914,  -914,  -914,  -914,  -914,
    -914,    46,    52,  -914,   731,   732,  -914,  -914,  -914,  -914,
     738,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,   728,
    -914,   741,   789,  -914,  -914,   653,  -914,  -914,  -914,   755,
    -914,  -914,  -914,  -914,   799,  -914,  -914,   658,  -914,   659,
    -914,  -914,  -914,   765,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,  -914,  -914,  -914,   657,  -914,     5,  -914,  -914,
     872,   664,   665,  -914,  -914,  -914,   668,   669,  -914,    80,
    -914,   667,   759,   670,   671,   673,   674,   677,   678,   682,
     680,   681,   683,   684,   685,   686,   687,   692,   693,   694,
     697,   698,   699,   700,   702,   703,   704,   705,   706,   707,
     708,   710,   715,   689,   800,   814,   843,   716,   852,   855,
    -914,    11,  -914,    88,   849,   853,   858,   861,   862,   866,
     869,   873,   883,   877,   878,   879,   880,   888,   882,   890,
     891,   895,   896,  -914,   894,   897,   899,   900,   901,   902,
     903,   904,   767,   905,   898,   906,  -914,   773,   786,   788,
     790,   792,   793,   794,   912,   919,   920,   922,   923,   927,
     928,   931,   934,   935,   937,   938,   179,     6,  -914,  -914,
    -914,  -914,  -914,   179,  -914,   179,   808,   955,  -914,  -914,
     723,  -914,  -914,  -914,  -914,  -914,   810,   689,   813,  -914,
    -914,   105,   859,  -914,   941,  -914,  -914,   932,   564,   946,
     908,  -914,   390,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,    50,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,   929,  -914,  -914,  -914,  -914,  -914,  -914,  -914,   936,
     939,   951,   832,   834,   835,   838,   840,   842,   844,   845,
     846,   847,   848,   850,   851,   831,  -914,   837,   841,   856,
      16,   865,   875,   948,   949,  -914,  -914,   950,   952,   179,
     854,   179,   871,   884,   885,   886,   892,   893,   907,    18,
     916,   914,   915,   924,   926,   930,   917,   925,   940,   944,
     942,   943,   947,   945,   954,   953,   957,   958,    19,   960,
     961,   965,   967,   969,   970,   971,   972,   977,   978,   981,
     982,   987,   988,   989,   990,   992,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  -914,  -914,   839,  -914,   564,   909,   723,
     959,   979,  -914,   263,  -914,    22,   985,  -914,   994,  1021,
    1022,   132,  1023,   991,   195,  -914,  1025,  1026,  1027,  1028,
    1029,  1033,  1035,  1036,  1037,  1038,  1042,  1043,  1044,  1045,
    1046,  1047,  1048,  -914,    -1,  -914,  -914,   995,   493,   493,
    -914,  -914,  -914,  -914,  -914,  -914,  -914,   361,   974,   361,
    -914,  -914,  -914,  -914,  -914,  -914,  1007,  -914,   964,  -914,
    -914,    71,   966,  1010,  -914,  -914,  -914,  1012,  -914,  -914,
    1031,  -914,     3,  -914,  -914,  -914,  1049,  -914,  -914,  -914,
     980,  1050,  1013,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    1052,  1058,  1067,  1068,  1078,  1081,  1084,  1150,  1154,  1158,
    1164,  1174,  1009,  -914,   361,   723,   361,  1053,   -40,  1149,
    1155,    46,  -914,   493,   493,  1192,  1143,  -914,  1191,  -914,
    1185,  -914,  -914,  -914,  1167,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,  -914,  1168,  1169,  1170,  -914,  -914,  -914,  -914,
    -914,  -914,  -914,    24,  -914,  1059,  1060,  1061,  1171,  1172,
    -914,  -914,  1173,  1175,  1066,   361,  1072,  1063,   564,  1064,
    1071,  1073,  1180,  1079,  1075,  1077,  1080,  1082,  1083,  1085,
     564,  1086,  1087,  1090,  1091,  1092,  1093,  1094,  1095,  1096,
    1097,  1098,  1100,  1103,  1104,  1105,  -914,  1107,  1109,  1190,
    -914,  1187,  1212,   -40,   -40,  -914,  -914,  -914,  -104,  1213,
     -40,   -40,  1108,  1110,  -914,  1205,  1115,  1116,  1114,  1117,
    1118,  1119,    -1,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,  1120,  -914,  -914,   -32,  -914,  -914,  -914,  1121,
    1227,  -914,  -914,  -914,  -914,  -914,  -914,   -30,  -914,  1232,
    1234,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1144,
    1145,  1146,  1147,  -914,  -914,  -914,  -914,  1131,   -97,  -914,
     166,  1148,  -914,  1151,  -914,  -914,  -914,  -914,  -914,  -914,
    1268,  1152,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    1153,  -914,  1157,  1156,  1160,  1161,  1162,  1163,  1165,  1166,
    1176,  1177,  1178,  1179,  1181,  1182,  -104,  -914,  -914,  -914,
    1243,  1244,  -914,  1184,  -914,   128,  1183,  1186,  -914,  1251,
    -914,  -914,  -914,  -914,  -914,  -914,  -914,  1253,  1254,  1255,
    -914,  -914,  -914,  -914,  -914,  -914,  -914,  1188,  -914,  -914,
    1189,  1193,  1194,  1195,  -914,  -914,  -914,  -914,  -914
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -914,  -914,  -914,  -914,    73,  -914,  -914,  -914,  -914,  -246,
    -914,  -914,  1199,  -914,  1224,  -914,  -914,  -265,  -308,  -914,
    -914,   498,  -914,  -914,  -914,   672,  -481,   816,  -914,  -914,
    -914,  -914,   447,  -914,  -248,  -914,   817,  -623,  -914,  -914,
     565,  -422,  -721,  -504,  -914,  -603,  -421,  -914,  -914,  -914,
    -914,  -914,  -914,  -914,   709,  -914,  -914,   359,  -914,  -914,
     560,  -914,  -914,  -914,  -913,   372,  -914,   381,   268,  -914,
     261
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     504,   493,   607,   609,   498,   761,   634,   752,   431,   432,
    1028,   940,   533,   172,  1031,   433,   744,   890,   434,   603,
       1,   435,   328,   436,   891,   437,   438,   683,   439,   440,
     441,  1009,   442,   443,   788,   684,     7,  1015,  1016,   692,
     863,   789,   941,   340,   341,   342,   178,   864,  1010,   917,
     444,   445,  1011,   446,   918,  1010,   349,   685,   173,  1011,
    1047,     8,   686,   252,   611,   447,   448,   449,   450,   942,
     253,   612,   358,     5,   451,   452,   453,    10,   906,   454,
     455,   107,   456,   457,   458,   108,   613,   459,   460,    82,
     461,   462,   743,   687,   463,   109,   464,   614,   252,   748,
     465,   750,   104,   105,   683,   253,   179,   499,   380,   892,
     500,   383,   684,   756,   757,   466,   943,    83,   467,   468,
     688,   944,   910,   599,   617,   599,   112,   600,   601,   600,
     601,   110,   111,   937,   685,   938,   469,   113,   114,   686,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   254,    84,   411,   412,   413,
     911,   414,   415,   416,   485,   633,   417,   418,   486,   745,
     687,   604,   806,   826,   689,   807,   827,   115,   962,  1048,
     912,   963,   116,   117,   972,   796,   118,   798,   607,   609,
     254,  1049,   175,   255,   615,   683,   119,   688,   431,   432,
      85,    86,   256,   684,   120,   433,   598,   121,   434,   122,
    1050,   435,   328,   436,   123,   437,   438,  1048,   439,   440,
     441,   124,   442,   443,   125,   685,   126,   176,   255,  1049,
     686,   177,   127,   340,   341,   342,   183,  1051,   128,   493,
     444,   445,   493,   446,   869,   129,   349,   130,  1050,   599,
     184,   691,   752,   600,   601,   447,   448,   449,   450,   131,
     132,   687,   358,   133,   451,   452,   453,   134,   135,   454,
     455,   136,   456,   457,   458,  1051,   137,   459,   460,   138,
     461,   462,   139,   634,   463,   975,   464,   599,   688,   140,
     465,   600,   601,   141,   142,   143,   144,   987,   380,   145,
     146,   383,   147,   148,   149,   466,   150,   151,   467,   468,
     152,   153,   154,   155,   858,   156,   157,   158,   159,  1052,
     160,   161,   185,   162,   163,   164,   469,   607,   609,   859,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   860,   165,   411,   412,   413,
     166,   414,   415,   416,   485,   872,   417,   418,   486,   167,
     168,   169,   170,   181,   186,   187,   861,   190,   188,   189,
     191,   192,   193,   194,   195,   196,   197,   898,   198,   199,
     200,   201,   202,   203,   493,   899,   206,   204,   207,   205,
     208,   209,   210,   431,   432,   765,   211,   212,   213,   221,
     433,   214,   215,   434,   222,   224,   435,   328,   436,   216,
     437,   438,   900,   439,   440,   441,   217,   442,   443,   218,
     219,   220,   223,   225,   901,   226,   227,   228,   340,   341,
     342,   229,   230,   607,   609,   444,   445,   231,   446,   232,
     233,   349,   234,   902,   235,   236,   237,   238,   239,   240,
     447,   448,   449,   450,   241,   242,   243,   358,   244,   451,
     452,   453,   245,   246,   454,   455,   248,   456,   457,   458,
     903,   250,   459,   460,   251,   461,   462,   264,   259,   463,
     260,   464,   261,   262,   263,   465,   265,   266,   267,   269,
     268,   501,   505,   380,   270,   271,   383,   272,   273,   506,
     466,   507,   274,   467,   468,   519,   510,   516,   511,   275,
     512,   605,   513,   276,   277,   514,   493,   508,   515,   278,
     279,   469,   517,   896,   897,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     280,   509,   411,   412,   413,   281,   414,   415,   416,   485,
     282,   417,   418,   486,   283,   518,   284,   286,   285,   287,
     289,   288,   520,   521,   290,   291,   292,   293,   320,   321,
     322,   323,   294,   295,   522,   300,   523,   324,   325,   326,
     327,   328,   329,   301,   330,   331,   296,   524,   332,   333,
     297,   334,   335,   298,   336,   337,   299,   302,   952,   953,
     338,   339,   340,   341,   342,   343,   303,   344,   304,   345,
     346,   347,   305,   348,   306,   349,   307,   350,   351,   352,
     353,   354,   355,   356,   308,   309,   310,   357,   311,   312,
     313,   358,   314,   315,   316,   359,   360,   361,   317,   318,
     319,   362,   363,   364,   365,   366,   367,   502,   368,   369,
     525,   526,   370,   371,   372,   527,   373,   374,   528,   375,
     529,   530,   376,   377,   378,   379,   531,   380,   381,   382,
     383,   532,   384,   385,   386,   534,   535,   536,   537,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   538,   403,   404,   405,   539,
     540,   542,   544,   541,   406,   543,   407,   408,   409,   545,
     546,   547,   410,   548,   549,   550,   411,   412,   413,   551,
     414,   415,   416,   552,   553,   417,   418,   320,   554,   322,
     323,   555,   556,   557,   558,   559,   560,   561,   562,   327,
     328,   329,   563,   330,   331,   564,   565,   332,   333,   566,
     334,   335,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   340,   341,   342,   343,   576,   344,   577,   345,   346,
     578,   579,   580,   581,   349,   582,   583,   584,   585,   586,
     354,   596,   618,   619,   587,   588,   357,   589,   590,   620,
     358,   621,   622,   591,   359,   592,   593,   623,   594,   595,
     362,   363,   364,   365,   366,   367,   625,   368,   369,   624,
     626,   370,   371,   606,   627,   629,   630,   631,   375,   638,
     639,   640,   644,   641,   643,   677,   380,   645,   646,   383,
     647,   648,   385,   386,   649,   650,   651,   652,   653,   678,
     654,   655,   656,   657,   658,   675,   659,   660,   661,   398,
     399,   662,   663,   664,   665,   403,   666,   667,   668,   669,
     670,   671,   672,   406,   673,   407,   408,   409,   679,   674,
     681,   410,   680,   682,   693,   411,   412,   413,   694,   414,
     415,   416,   433,   695,   417,   418,   696,   697,   435,   328,
     436,   698,   437,   438,   699,   439,   440,   441,   700,   442,
     443,   701,   702,   703,   704,   705,   706,   707,   708,   709,
     340,   341,   342,   710,   711,   720,   722,   444,   445,   712,
     446,   724,   713,   349,   714,   715,   716,   717,   718,   719,
     721,   723,   447,   448,   725,   450,   726,   731,   727,   358,
     728,   729,   730,   453,   732,   733,   454,   734,   735,   456,
     457,   458,   736,   737,   459,   460,   738,   461,   462,   739,
     740,   463,   741,   742,   751,   603,   759,   465,   753,   755,
     758,   762,   760,   763,   766,   380,   769,   770,   383,   771,
     772,   767,   466,   773,   768,   774,   468,   775,   783,   776,
     777,   778,   779,   780,   785,   781,   782,   642,   786,   792,
     793,   794,   852,   795,   857,   921,   797,   470,   471,   472,
     787,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   790,   799,   411,   412,   413,   635,   414,   415,
     416,   485,   791,   417,   418,   486,    11,    12,    13,    14,
     895,   800,   801,   802,     1,   866,    15,    16,   865,   803,
     804,    17,   907,   909,   871,   913,   914,   915,    18,   923,
     936,   854,    19,    20,   805,    21,    22,    23,    24,    25,
     808,   809,   810,    26,   814,    27,   916,   924,   811,    28,
     812,    29,   815,   925,   813,    30,    31,    32,    33,    34,
      35,    36,   926,   927,   919,   922,    37,   816,   817,   818,
     819,   820,   821,   928,    38,    39,   929,    40,   822,   930,
     823,   856,    41,    42,   824,   825,    43,   828,   829,   830,
      44,   831,    45,   832,    46,    47,   905,   833,   834,   835,
      48,    49,    50,    51,   836,   837,    52,    53,   838,   839,
      54,   840,   841,   842,   843,    55,   844,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    88,   845,   846,
     847,   848,   849,   850,   851,   931,   868,   870,   867,   932,
     874,    89,   873,   933,   875,   876,   877,    76,    90,   934,
     878,    91,   879,   880,   881,   882,   883,   884,   885,   935,
     949,   954,   886,   887,   888,   889,   950,   939,   955,   956,
     957,    92,   958,   959,   960,   961,   964,   965,   966,   971,
     974,   976,   967,   968,   969,   973,   970,    93,   977,    94,
     978,   979,   981,   980,   982,    95,   917,   983,  1005,   984,
     985,   989,   986,   988,   990,   991,   992,   993,   994,   995,
     996,   997,   998,    96,   999,    97,    98,  1000,  1001,  1002,
    1003,    99,  1004,  1006,  1014,  1017,   100,  1018,  1019,  1020,
    1021,  1022,  1030,  1027,  1023,  1024,  1025,  1032,  1029,  1033,
    1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1046,  1042,
    1043,  1044,  1045,  1056,  1074,  1075,  1080,  1057,  1081,  1082,
    1083,   180,   171,  1055,   764,  1054,   636,   637,   951,   855,
    1058,  1059,   853,  1060,  1073,  1007,  1077,  1061,  1062,  1063,
    1064,  1026,  1065,  1066,  1008,     0,   754,     0,     0,     0,
    1067,  1068,  1069,     0,     0,     0,  1070,  1076,  1071,  1072,
    1078,  1084,     0,  1079,     0,     0,  1085,     0,     0,     0,
    1086,  1087,  1088
};

static const yytype_int16 yycheck[] =
{
     265,   249,   424,   424,   250,   628,   487,   610,     3,     4,
      42,    51,   320,   114,    44,    10,    10,    18,    13,    10,
      12,    16,    17,    18,    25,    20,    21,    16,    23,    24,
      25,   944,    27,    28,    18,    24,     0,   950,   951,   543,
      18,    25,    82,    38,    39,    40,     8,    25,   152,    46,
      45,    46,   156,    48,    51,   152,    51,    46,   159,   156,
     157,    60,    51,    18,    18,    60,    61,    62,    63,   109,
      25,    25,    67,     0,    69,    70,    71,     4,   799,    74,
      75,   156,    77,    78,    79,   156,    40,    82,    83,    39,
      85,    86,   596,    82,    89,   156,    91,    51,    18,   603,
      95,   605,    50,    51,    16,    25,    68,   154,   103,   110,
     157,   106,    24,     8,     9,   110,   156,    67,   113,   114,
     109,   161,    51,   155,   432,   155,    51,   159,   160,   159,
     160,   156,   156,   854,    46,   856,   131,    51,   156,    51,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   110,   106,   152,   153,   154,
      89,   156,   157,   158,   159,   160,   161,   162,   163,   163,
      82,   162,   154,   154,   163,   157,   157,   156,   154,    51,
     109,   157,   156,   158,   905,   689,   158,   691,   610,   610,
     110,    63,    51,   148,   148,    16,   156,   109,     3,     4,
     150,   151,   157,    24,   156,    10,   112,   156,    13,   156,
      82,    16,    17,    18,   156,    20,    21,    51,    23,    24,
      25,   156,    27,    28,   156,    46,   156,     8,   148,    63,
      51,     8,   156,    38,    39,    40,    25,   109,   156,   487,
      45,    46,   490,    48,   112,   156,    51,   156,    82,   155,
      25,   163,   855,   159,   160,    60,    61,    62,    63,   156,
     156,    82,    67,   156,    69,    70,    71,   156,   156,    74,
      75,   156,    77,    78,    79,   109,   156,    82,    83,   156,
      85,    86,   156,   764,    89,   908,    91,   155,   109,   156,
      95,   159,   160,   156,   156,   156,   156,   920,   103,   156,
     156,   106,   156,   156,   156,   110,   156,   156,   113,   114,
     156,   156,   156,   156,    51,   156,   156,   156,   156,   153,
     156,   156,    25,   156,   156,   156,   131,   749,   749,    66,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,    82,   156,   152,   153,   154,
     156,   156,   157,   158,   159,   160,   161,   162,   163,   156,
     156,   156,   156,   156,    18,    18,   103,    25,   156,   156,
      25,    51,    38,    38,    25,    25,    25,    16,    25,    25,
      25,    18,    25,    25,   632,    24,    18,    25,    18,    25,
     157,    18,    18,     3,     4,   641,    25,    18,    18,   148,
      10,    25,    25,    13,   148,    18,    16,    17,    18,    25,
      20,    21,    51,    23,    24,    25,    25,    27,    28,    25,
      25,    25,    25,    25,    63,    40,   148,   148,    38,    39,
      40,   148,   148,   855,   855,    45,    46,   148,    48,   148,
     148,    51,    25,    82,    25,    25,    25,    25,    25,    25,
      60,    61,    62,    63,    25,    25,    25,    67,    25,    69,
      70,    71,    25,    25,    74,    75,   160,    77,    78,    79,
     109,   152,    82,    83,     8,    85,    86,    18,   157,    89,
     157,    91,   154,   157,   157,    95,    25,   157,   157,   157,
     154,    45,    51,   103,   157,   157,   106,   157,   154,    45,
     110,    89,   154,   113,   114,    18,    46,    25,    45,   157,
      45,    10,    45,   157,   154,    46,   764,    89,    45,   154,
     154,   131,    45,   788,   789,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     157,    89,   152,   153,   154,   157,   156,   157,   158,   159,
     157,   161,   162,   163,   154,    46,   157,   154,   157,   154,
     154,   157,    25,    25,   157,   157,   157,   154,     4,     5,
       6,     7,   157,   157,    25,   157,    25,    13,    14,    15,
      16,    17,    18,   157,    20,    21,   154,    25,    24,    25,
     154,    27,    28,   154,    30,    31,   154,   157,   863,   864,
      36,    37,    38,    39,    40,    41,   157,    43,   157,    45,
      46,    47,   157,    49,   157,    51,   154,    53,    54,    55,
      56,    57,    58,    59,   154,   154,   154,    63,   154,   154,
     154,    67,   154,   154,   154,    71,    72,    73,   154,   154,
     154,    77,    78,    79,    80,    81,    82,   154,    84,    85,
      25,    25,    88,    89,    90,    25,    92,    93,    25,    95,
      25,    25,    98,    99,   100,   101,    25,   103,   104,   105,
     106,    25,   108,   109,   110,   156,   156,   156,    51,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   156,   132,   133,   134,   156,
      51,    51,   156,   163,   140,   163,   142,   143,   144,   156,
     156,   156,   148,   156,   156,   156,   152,   153,   154,   156,
     156,   157,   158,   156,   156,   161,   162,     4,   156,     6,
       7,   156,   156,   156,   156,   156,   156,   156,   156,    16,
      17,    18,    51,    20,    21,   156,   156,    24,    25,   156,
      27,    28,   156,   156,   156,   156,   156,   156,   156,   156,
     156,    38,    39,    40,    41,    51,    43,   156,    45,    46,
     156,   156,   156,   156,    51,   156,   156,   156,   156,   156,
      57,   163,    51,    51,   156,   156,    63,   156,   156,    51,
      67,    63,    51,   156,    71,   156,   156,     8,   156,   156,
      77,    78,    79,    80,    81,    82,    51,    84,    85,   156,
      11,    88,    89,    90,   156,   156,    51,   160,    95,   155,
     155,   153,    63,   154,   157,    25,   103,   157,   157,   106,
     157,   157,   109,   110,   157,   157,   154,   157,   157,    25,
     157,   157,   157,   157,   157,   156,   154,   154,   154,   126,
     127,   154,   154,   154,   154,   132,   154,   154,   154,   154,
     154,   154,   154,   140,   154,   142,   143,   144,    25,   154,
      18,   148,   156,    18,    25,   152,   153,   154,    25,   156,
     157,   158,    10,    25,   161,   162,    25,    25,    16,    17,
      18,    25,    20,    21,    25,    23,    24,    25,    25,    27,
      28,    18,    25,    25,    25,    25,    18,    25,    18,    18,
      38,    39,    40,    18,    18,   148,    18,    45,    46,    25,
      48,   148,    25,    51,    25,    25,    25,    25,    25,    25,
      25,    25,    60,    61,   148,    63,   148,    25,   148,    67,
     148,   148,   148,    71,    25,    25,    74,    25,    25,    77,
      78,    79,    25,    25,    82,    83,    25,    85,    86,    25,
      25,    89,    25,    25,   156,    10,    25,    95,   158,   156,
     111,    25,    40,    65,    45,   103,    25,   145,   106,   145,
     145,    45,   110,   145,    45,   145,   114,   145,   157,   145,
     145,   145,   145,   145,   157,   145,   145,   499,   157,    51,
      51,    51,   163,    51,    25,    25,   152,   135,   136,   137,
     154,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   157,   152,   152,   153,   154,   155,   156,   157,
     158,   159,   157,   161,   162,   163,     4,     5,     6,     7,
      45,   157,   157,   157,    12,    51,    14,    15,    63,   157,
     157,    19,    45,    89,    63,    89,    46,    45,    26,    46,
      51,   152,    30,    31,   157,    33,    34,    35,    36,    37,
     154,   157,   157,    41,   157,    43,    45,    25,   154,    47,
     154,    49,   157,    25,   154,    53,    54,    55,    56,    57,
      58,    59,    25,    25,    45,    45,    64,   157,   154,   157,
     157,   154,   157,    25,    72,    73,    25,    75,   154,    25,
     157,   152,    80,    81,   157,   157,    84,   157,   157,   154,
      88,   154,    90,   154,    92,    93,   152,   157,   157,   157,
      98,    99,   100,   101,   157,   157,   104,   105,   157,   157,
     108,   154,   154,   154,   154,   113,   154,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     8,   154,   154,
     154,   154,   154,   154,   154,    25,   154,   154,   157,    25,
     154,    22,   157,    25,   157,   157,   157,   155,    29,    25,
     157,    32,   157,   157,   157,   157,   154,   154,   154,    25,
      51,     9,   157,   157,   157,   157,    51,   154,    65,    18,
      25,    52,    45,    45,    45,    45,   157,   157,   157,   153,
     157,   157,    51,    51,    51,   153,    51,    68,   157,    70,
     157,    51,   157,   154,   157,    76,    46,   157,    51,   157,
     157,   154,   157,   157,   154,   154,   154,   154,   154,   154,
     154,   154,   154,    94,   154,    96,    97,   154,   154,   154,
     153,   102,   153,    51,    51,   157,   107,   157,    63,   154,
     154,   157,    45,   153,   157,   157,   157,    45,   157,    45,
     145,   145,   145,   145,   145,   145,   145,   145,   157,   145,
     145,   145,   145,    25,    51,    51,    45,   145,    45,    45,
      45,   102,    78,   152,   632,   157,   490,   490,   861,   749,
     157,   154,   747,   157,  1046,   943,  1055,   157,   157,   157,
     157,   962,   157,   157,   943,    -1,   617,    -1,    -1,    -1,
     154,   154,   154,    -1,    -1,    -1,   157,   153,   157,   157,
     157,   153,    -1,   157,    -1,    -1,   157,    -1,    -1,    -1,
     157,   157,   157
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,   165,   166,   167,   168,   169,     0,    60,   170,
     168,     4,     5,     6,     7,    14,    15,    19,    26,    30,
      31,    33,    34,    35,    36,    37,    41,    43,    47,    49,
      53,    54,    55,    56,    57,    58,    59,    64,    72,    73,
      75,    80,    81,    84,    88,    90,    92,    93,    98,    99,
     100,   101,   104,   105,   108,   113,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   155,   168,   177,   178,
     179,   180,    39,    67,   106,   150,   151,   173,     8,    22,
      29,    32,    52,    68,    70,    76,    94,    96,    97,   102,
     107,   174,   175,   176,    50,    51,   182,   156,   156,   156,
     156,   156,    51,    51,   156,   156,   156,   158,   158,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   178,   114,   159,   186,    51,     8,     8,     8,    68,
     176,   156,   183,    25,    25,    25,    18,    18,   156,   156,
      25,    25,    51,    38,    38,    25,    25,    25,    25,    25,
      25,    18,    25,    25,    25,    25,    18,    18,   157,    18,
      18,    25,    18,    18,    25,    25,    25,    25,    25,    25,
      25,   148,   148,    25,    18,    25,    40,   148,   148,   148,
     148,   148,   148,   148,    25,    25,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    25,   187,   160,   188,
     152,     8,    18,    25,   110,   148,   157,   184,   185,   157,
     157,   154,   157,   157,    18,    25,   157,   157,   154,   157,
     157,   157,   157,   154,   154,   157,   157,   154,   154,   154,
     157,   157,   157,   154,   157,   157,   154,   154,   157,   154,
     157,   157,   157,   154,   157,   157,   154,   154,   154,   154,
     157,   157,   157,   157,   157,   157,   157,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
       4,     5,     6,     7,    13,    14,    15,    16,    17,    18,
      20,    21,    24,    25,    27,    28,    30,    31,    36,    37,
      38,    39,    40,    41,    43,    45,    46,    47,    49,    51,
      53,    54,    55,    56,    57,    58,    59,    63,    67,    71,
      72,    73,    77,    78,    79,    80,    81,    82,    84,    85,
      88,    89,    90,    92,    93,    95,    98,    99,   100,   101,
     103,   104,   105,   106,   108,   109,   110,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   132,   133,   134,   140,   142,   143,   144,
     148,   152,   153,   154,   156,   157,   158,   161,   162,   198,
     201,   204,   205,   208,   210,   213,   214,   215,   222,   225,
     226,     3,     4,    10,    13,    16,    18,    20,    21,    23,
      24,    25,    27,    28,    45,    46,    48,    60,    61,    62,
      63,    69,    70,    71,    74,    75,    77,    78,    79,    82,
      83,    85,    86,    89,    91,    95,   110,   113,   114,   131,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   159,   163,   189,   190,   191,
     194,   195,   197,   198,   199,   200,   171,   172,   173,   154,
     157,    45,   154,   181,   181,    51,    45,    89,    89,    89,
      46,    45,    45,    45,    46,    45,    25,    45,    46,    18,
      25,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    25,   182,   156,   156,   156,    51,   156,   156,
      51,   163,    51,   163,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,    51,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,    51,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   163,   211,   112,   155,
     159,   160,   203,    10,   162,    10,    90,   205,   209,   210,
     224,    18,    25,    40,    51,   148,   196,   182,    51,    51,
      51,    63,    51,     8,   156,    51,    11,   156,   193,   156,
      51,   160,   192,   160,   190,   155,   191,   200,   155,   155,
     153,   154,   185,   157,    63,   157,   157,   157,   157,   157,
     157,   154,   157,   157,   157,   157,   157,   157,   157,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   156,   218,    25,    25,    25,
     156,    18,    18,    16,    24,    46,    51,    82,   109,   163,
     207,   163,   207,    25,    25,    25,    25,    25,    25,    25,
      25,    18,    25,    25,    25,    25,    18,    25,    18,    18,
      18,    18,    25,    25,    25,    25,    25,    25,    25,    25,
     148,    25,    18,    25,   148,   148,   148,   148,   148,   148,
     148,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    25,   207,    10,   163,   212,   202,   207,   223,
     207,   156,   209,   158,   218,   156,     8,     9,   111,    25,
      40,   201,    25,    65,   189,   173,    45,    45,    45,    25,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   157,   219,   157,   157,   154,    18,    25,
     157,   157,    51,    51,    51,    51,   207,   152,   207,   152,
     157,   157,   157,   157,   157,   157,   154,   157,   154,   157,
     157,   154,   154,   154,   157,   157,   157,   154,   157,   157,
     154,   157,   154,   157,   157,   157,   154,   157,   157,   157,
     154,   154,   154,   157,   157,   157,   157,   157,   157,   157,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   163,   204,   152,   224,   152,    25,    51,    66,
      82,   103,   227,    18,    25,    63,    51,   157,   154,   112,
     154,    63,   160,   157,   154,   157,   157,   157,   157,   157,
     157,   157,   157,   154,   154,   154,   157,   157,   157,   157,
      18,    25,   110,   220,   221,    45,   181,   181,    16,    24,
      51,    63,    82,   109,   206,   152,   206,    45,   216,    89,
      51,    89,   109,    89,    46,    45,    45,    46,    51,    45,
     217,    25,    45,    46,    25,    25,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    51,   206,   206,   154,
      51,    82,   109,   156,   161,   228,   229,   230,   231,    51,
      51,   196,   181,   181,     9,    65,    18,    25,    45,    45,
      45,    45,   154,   157,   157,   157,   157,    51,    51,    51,
      51,   153,   206,   153,   157,   201,   157,   157,   157,    51,
     154,   157,   157,   157,   157,   157,   157,   201,   157,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   153,   153,    51,    51,   229,   231,   228,
     152,   156,   232,   233,    51,   228,   228,   157,   157,    63,
     154,   154,   157,   157,   157,   157,   221,   153,    42,   157,
      45,    44,    45,    45,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   157,   157,    51,    63,
      82,   109,   153,   234,   157,   152,    25,   145,   157,   154,
     157,   157,   157,   157,   157,   157,   157,   154,   154,   154,
     157,   157,   157,   232,    51,    51,   153,   234,   157,   157,
      45,    45,    45,    45,   153,   157,   157,   157,   157
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 383 "./xp-gram.y"
    { /* Suppress default action. */ }
    break;

  case 7:
#line 405 "./xp-gram.y"
    { out("\n%s\n", (yyvsp[(1) - (1)].str)+1); 
          }
    break;

  case 9:
#line 419 "./xp-gram.y"
    {
             layer_stmt_seen((yyvsp[(2) - (6)].ptr)->type, (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].ptr));
          }
    break;

  case 10:
#line 426 "./xp-gram.y"
    {
             (yyval.ptr) = NULL;
          }
    break;

  case 13:
#line 435 "./xp-gram.y"
    {
             (yyval.ptr) = tackon_rlist_node((yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
          }
    break;

  case 14:
#line 442 "./xp-gram.y"
    {
             (yyval.ptr) = new_rlist_node(DS);
          }
    break;

  case 15:
#line 446 "./xp-gram.y"
    {
             (yyval.ptr) = new_rlist_node(MEM);
          }
    break;

  case 16:
#line 450 "./xp-gram.y"
    {
             (yyval.ptr) = new_rlist_node(TOP);
          }
    break;

  case 17:
#line 454 "./xp-gram.y"
    {
             (yyval.ptr) = new_rlist_node(LINK);
          }
    break;

  case 18:
#line 458 "./xp-gram.y"
    {
             (yyval.ptr) = new_rlist_node(TOPLINK);
          }
    break;

  case 19:
#line 478 "./xp-gram.y"
    {  out("\n#include \"pb.h\"\n");
             out("\n#include \"%s-ref.h\"\n",layer_name);
             clear_member();
          }
    break;

  case 22:
#line 491 "./xp-gram.y"
    { annotations = NO_ANNOTATION; }
    break;

  case 23:
#line 493 "./xp-gram.y"
    { annotations = ANNOTATION; }
    break;

  case 24:
#line 495 "./xp-gram.y"
    { annotations = MULTIPLE_ANNOTATION; }
    break;

  case 25:
#line 497 "./xp-gram.y"
    { annotations = OPTIONAL_ANNOTATION; }
    break;

  case 26:
#line 499 "./xp-gram.y"
    { annotations = OPTIONAL_MULTIPLE_ANNOTATION; }
    break;

  case 27:
#line 501 "./xp-gram.y"
    { stable = TRUE; }
    break;

  case 28:
#line 503 "./xp-gram.y"
    { stable = FALSE; }
    break;

  case 29:
#line 505 "./xp-gram.y"
    { d2u = TRUE; }
    break;

  case 30:
#line 507 "./xp-gram.y"
    { curs_state = TRUE; }
    break;

  case 31:
#line 509 "./xp-gram.y"
    { cont_state = TRUE; }
    break;

  case 32:
#line 511 "./xp-gram.y"
    { indirect_only = TRUE; }
    break;

  case 33:
#line 513 "./xp-gram.y"
    { retrieval = RETRIEVAL_NEVER; }
    break;

  case 34:
#line 515 "./xp-gram.y"
    { retrieval = RETRIEVAL_SOMETIMES; }
    break;

  case 35:
#line 517 "./xp-gram.y"
    { retrieval = RETRIEVAL_ALWAYS; }
    break;

  case 38:
#line 533 "./xp-gram.y"
    {  if (!seen[LAYER_STMT])
                parse_error("place layer statement before all procedures");
          }
    break;

  case 39:
#line 537 "./xp-gram.y"
    {  out(";");
          }
    break;

  case 41:
#line 548 "./xp-gram.y"
    { opheader(INIT_CONT_OP); }
    break;

  case 42:
#line 550 "./xp-gram.y"
    { opheader(C_PUT_OP_VEC_OP); }
    break;

  case 43:
#line 552 "./xp-gram.y"
    { opheader(C_VERBATIM_OP); }
    break;

  case 44:
#line 554 "./xp-gram.y"
    { opheader(K_PUT_OP_VEC_OP); }
    break;

  case 45:
#line 556 "./xp-gram.y"
    { opheader(K_VERBATIM_OP); }
    break;

  case 46:
#line 558 "./xp-gram.y"
    { opheader(S_PUT_OP_VEC_OP); }
    break;

  case 47:
#line 560 "./xp-gram.y"
    { opheader(S_VERBATIM_OP); }
    break;

  case 48:
#line 562 "./xp-gram.y"
    { opheader(L_VERBATIM_OP); }
    break;

  case 49:
#line 564 "./xp-gram.y"
    { opheader(QUERY_OP);
            retrieval_layer_header(QUERY_OP, "QUERY_OP", "cursor0");
          }
    break;

  case 50:
#line 568 "./xp-gram.y"
    { opheader(DDLHINT_OP);
            in_ddlhint_proc = TRUE;
            in_special_proc = TRUE;
          }
    break;

  case 51:
#line 573 "./xp-gram.y"
    { opheader(OPEN_CONT_OP); }
    break;

  case 52:
#line 575 "./xp-gram.y"
    { opheader(OPEN_CONT_NUMBER_OP); }
    break;

  case 53:
#line 577 "./xp-gram.y"
    { opheader(CHECKPOINT_CONT_OP); }
    break;

  case 54:
#line 579 "./xp-gram.y"
    { opheader(CLOSE_CONT_OP); }
    break;

  case 55:
#line 581 "./xp-gram.y"
    { opheader(OVERFLOW_OP); }
    break;

  case 56:
#line 583 "./xp-gram.y"
    { opheader(VAROVERFLOW_OP); }
    break;

  case 57:
#line 585 "./xp-gram.y"
    { opheader(INSERT_OP); }
    break;

  case 58:
#line 587 "./xp-gram.y"
    { opheader(VARINSERT_OP); }
    break;

  case 59:
#line 589 "./xp-gram.y"
    { opheader(REF_OP); }
    break;

  case 60:
#line 591 "./xp-gram.y"
    { opheader(IREF_OP); }
    break;

  case 61:
#line 593 "./xp-gram.y"
    { opheader(POS_OP); }
    break;

  case 62:
#line 595 "./xp-gram.y"
    { opheader(END_ADV_OP);
            retrieval_layer_header(END_ADV_OP, "END_ADV_OP", "cursor0");
          }
    break;

  case 63:
#line 599 "./xp-gram.y"
    { opheader(END_REV_OP); 
            retrieval_layer_header(END_REV_OP, "END_REV_OP", "cursor0");
          }
    break;

  case 64:
#line 603 "./xp-gram.y"
    { opheader(ADV_OP);  
            retrieval_layer_header(ADV_OP, "ADV_OP", "cursor0");
          }
    break;

  case 65:
#line 607 "./xp-gram.y"
    { opheader(OPTIMIZE_OP);
            in_optimize_proc = TRUE;
          }
    break;

  case 66:
#line 611 "./xp-gram.y"
    { opheader(INIT_CURS_OP); }
    break;

  case 67:
#line 613 "./xp-gram.y"
    { opheader(REV_OP);  
            retrieval_layer_header(REV_OP, "REV_OP", "cursor0");
          }
    break;

  case 68:
#line 617 "./xp-gram.y"
    { opheader(DELETE_OP); }
    break;

  case 69:
#line 619 "./xp-gram.y"
    { opheader(DELETE_CURS_OP); }
    break;

  case 70:
#line 621 "./xp-gram.y"
    { opheader(RESET_START_OP);
            retrieval_layer_header(RESET_START_OP, "RESET_START_OP", "cursor0");
          }
    break;

  case 71:
#line 625 "./xp-gram.y"
    { opheader(RESET_END_OP);
            retrieval_layer_header(RESET_END_OP, "RESET_END_OP", "cursor0");
          }
    break;

  case 72:
#line 629 "./xp-gram.y"
    { opheader(SWAP_OP);
            if ((get_param_num((yyvsp[(3) - (6)].str)) != 0) || (get_param_num((yyvsp[(5) - (6)].str)) != 1)) 
              parse_error("cursor parameters of swap are indexed wrong");
          }
    break;

  case 73:
#line 634 "./xp-gram.y"
    { opheader(SYNC_CONT_OP); }
    break;

  case 74:
#line 636 "./xp-gram.y"
    { opheader(GETREC_OP); }
    break;

  case 75:
#line 638 "./xp-gram.y"
    { opheader(ALLOC_OP); }
    break;

  case 76:
#line 640 "./xp-gram.y"
    { opheader(VARALLOC_OP); }
    break;

  case 77:
#line 642 "./xp-gram.y"
    { opheader(UPD_OP); }
    break;

  case 78:
#line 644 "./xp-gram.y"
    { opheader(FOREACH_OP); }
    break;

  case 79:
#line 646 "./xp-gram.y"
    { opheader(ROFEACH_OP); }
    break;

  case 80:
#line 648 "./xp-gram.y"
    { opheader(XFORM_OP);
            in_xform_proc = TRUE;
          }
    break;

  case 81:
#line 652 "./xp-gram.y"
    { opheader(getop((yyvsp[(2) - (3)].str))); }
    break;

  case 82:
#line 657 "./xp-gram.y"
    { opheader(OPEN_SCHEMA_OP); }
    break;

  case 83:
#line 659 "./xp-gram.y"
    { opheader(INIT_SCHEMA_OP); }
    break;

  case 84:
#line 661 "./xp-gram.y"
    { opheader(CLOSE_SCHEMA_OP); }
    break;

  case 85:
#line 664 "./xp-gram.y"
    { opheader(ABORT_XACT_OP); }
    break;

  case 86:
#line 666 "./xp-gram.y"
    { opheader(BEGIN_XACT_OP); }
    break;

  case 87:
#line 668 "./xp-gram.y"
    { opheader(COMMIT_XACT_OP); }
    break;

  case 88:
#line 670 "./xp-gram.y"
    { opheader(CHECKPOINT_SCHEMA_OP); }
    break;

  case 89:
#line 675 "./xp-gram.y"
    { opheader(RESETC_OP);  
            link_retrieval_layer_header(RESETC_OP, "RESETC_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 90:
#line 680 "./xp-gram.y"
    { opheader(RESETP_OP);  
            link_retrieval_layer_header(RESETP_OP, "RESETP_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 91:
#line 685 "./xp-gram.y"
    { opheader(ADVC_OP);  
            link_retrieval_layer_header(ADVC_OP, "ADVC_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 92:
#line 690 "./xp-gram.y"
    { opheader(ADVP_OP);  
            link_retrieval_layer_header(ADVP_OP, "ADVP_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 93:
#line 695 "./xp-gram.y"
    { opheader(ENDC_OP);  
            link_retrieval_layer_header(ENDC_OP, "ENDC_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 94:
#line 700 "./xp-gram.y"
    { opheader(ENDP_OP);  
            link_retrieval_layer_header(ENDP_OP, "ENDP_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 95:
#line 705 "./xp-gram.y"
    { opheader(FOREACHP_OP);  
            link_retrieval_layer_header(FOREACHP_OP, "FOREACHP_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 96:
#line 710 "./xp-gram.y"
    { opheader(FOREACHC_OP);  
            link_retrieval_layer_header(FOREACHC_OP, "FOREACHC_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 97:
#line 715 "./xp-gram.y"
    { opheader(FOREACHL_OP);  
            link_retrieval_layer_header(FOREACHL_OP, "FOREACHL_OP", 
                       "cursor0, cursor1, lstate0");
          }
    break;

  case 98:
#line 720 "./xp-gram.y"
    { opheader(RELATED_OP); 
          }
    break;

  case 99:
#line 723 "./xp-gram.y"
    { opheader(CONNECT_OP); 
          }
    break;

  case 100:
#line 726 "./xp-gram.y"
    { opheader(DISCONNECT_OP); 
          }
    break;

  case 101:
#line 729 "./xp-gram.y"
    { opheader(LOPTIMIZE_OP);  
            in_optimize_proc = TRUE;
          }
    break;

  case 103:
#line 745 "./xp-gram.y"
    {  cursor_func_action((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
          }
    break;

  case 104:
#line 748 "./xp-gram.y"
    {  container_func_action((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
          }
    break;

  case 105:
#line 751 "./xp-gram.y"
    {  def_cursor_func_action((yyvsp[(3) - (3)].str));
          }
    break;

  case 106:
#line 754 "./xp-gram.y"
    {  def_container_func_action((yyvsp[(3) - (3)].str));
          }
    break;

  case 107:
#line 760 "./xp-gram.y"
    {  strcpy((yyval.str), "");
          }
    break;

  case 108:
#line 763 "./xp-gram.y"
    {
#if 1
             /* These statements replace quote and double backslash with
                the empty string. */
             /* I was going to get rid of these replacements, but they
                seem to only be used in cursor_func and container_func,
                and don't seem to be doing any harm. (JAT) */
             replace_char((yyvsp[(2) - (2)].str), '"', ' ');
             replace_char((yyvsp[(2) - (2)].str), '\\', ' ');
#else
             /* Replace backslash quote (\") with quote (") */
             replace_string_inplace((yyvsp[(2) - (2)].str), "\\\"", "\"");

             /* Replace double backslash (\\) with backslash (\) */
             replace_string_inplace((yyvsp[(2) - (2)].str), "\\\\", "\\");
#endif
             strcpy((yyval.str), (yyvsp[(2) - (2)].str));
          }
    break;

  case 115:
#line 807 "./xp-gram.y"
    { /* Suppress default action. */ }
    break;

  case 116:
#line 808 "./xp-gram.y"
    { /* Suppress default action. */ }
    break;

  case 117:
#line 809 "./xp-gram.y"
    { /* Suppress default action. */ }
    break;

  case 118:
#line 810 "./xp-gram.y"
    { /* Suppress default action. */ }
    break;

  case 119:
#line 827 "./xp-gram.y"
    {  print_proc_header();
            x_header(FALSE);
         }
    break;

  case 120:
#line 831 "./xp-gram.y"
    {  print_proc_trailer();
            x_trailer(FALSE);
         }
    break;

  case 121:
#line 835 "./xp-gram.y"
    {  print_proc_header();
         }
    break;

  case 122:
#line 838 "./xp-gram.y"
    {  print_proc_trailer();
         }
    break;

  case 123:
#line 841 "./xp-gram.y"
    { print_proc_header();
           print_proc_trailer();
         }
    break;

  case 128:
#line 888 "./xp-gram.y"
    { out("; ");
          }
    break;

  case 131:
#line 896 "./xp-gram.y"
    {  out("{");
             brace_nesting_depth++;
          }
    break;

  case 132:
#line 900 "./xp-gram.y"
    {  brace_nesting_depth--;
             out("}");
          }
    break;

  case 133:
#line 904 "./xp-gram.y"
    { out("{ }");
          }
    break;

  case 134:
#line 907 "./xp-gram.y"
    {  x_header(TRUE);
          }
    break;

  case 135:
#line 910 "./xp-gram.y"
    { x_trailer(TRUE);
          }
    break;

  case 136:
#line 916 "./xp-gram.y"
    {  out((yyvsp[(1) - (1)].str));
          }
    break;

  case 137:
#line 919 "./xp-gram.y"
    {  out(" ");
             out((yyvsp[(2) - (2)].str));
          }
    break;

  case 138:
#line 936 "./xp-gram.y"
    {
            char t[SPRINT_BUF_SIZE];
            sprint_ctype_as_new_ctype_call(t, member_ctype);
            if (know_member_name) {
              out("new_member(te, %s, \"%s\", %s, %s);",
                  (yyvsp[(2) - (4)].str), member_name, t, member_type);
              if (strncmp((yyvsp[(2) - (4)].str),"cursor", 6) == 0)
                add_new_cursor_field (member_name);
            }
            else {
              if (strcmp((yyvsp[(2) - (4)].str),"global") == 0)
                out("new_global(te, %s, %s, %s);",
                    member_name, t, member_type);
              else
                out("new_member(te, %s, %s, %s, %s);",
                    (yyvsp[(2) - (4)].str), member_name, t, member_type);
            }
            clear_member();
          }
    break;

  case 139:
#line 956 "./xp-gram.y"
    {
             out("new_member(te, %s, \"%s\", ctype_of(%s), (%s)->ident);",
                 (yyvsp[(2) - (6)].str), (yyvsp[(6) - (6)].str), (yyvsp[(5) - (6)].str), (yyvsp[(5) - (6)].str));
             if (strncmp((yyvsp[(2) - (6)].str),"cursor", 6) == 0)
               add_new_cursor_field ((yyvsp[(6) - (6)].str));
           }
    break;

  case 140:
#line 963 "./xp-gram.y"
    {  out("copy_member(%s,%s);", (yyvsp[(2) - (5)].str), (yyvsp[(5) - (5)].str));
           }
    break;

  case 141:
#line 968 "./xp-gram.y"
    {
             int p = get_param_num((yyvsp[(1) - (6)].str));
             path[p] = atoi((yyvsp[(6) - (6)].str));
             out("{"
                 "IDENT3 *i;"
#if 0
                 "cont_id_counter++;"
#endif
                 "i = container_declaration_ident3(te->down[%s], %s, %s);",
                 (yyvsp[(6) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(2) - (6)].str));
             out("cursor%d = i->cur;", p);
             out("container%d = i->con;", p);
             out("element%d = i->ele;", p);
             out("}");
           }
    break;

  case 142:
#line 984 "./xp-gram.y"
    {
             int p = get_param_num((yyvsp[(1) - (2)].str));
             int q = get_param_num((yyvsp[(2) - (2)].str));
             path[q] = path[p];
             out("cursor%d = cursor%d;", q, p);
             out("container%d = container%d;", q, p);
             out("element%d = element%d;", q, p);
           }
    break;

  case 143:
#line 993 "./xp-gram.y"
    {
             int p = get_param_num((yyvsp[(1) - (4)].str));
             out("{"
                 "IDENT3 *i;"
                 "i = find_ident3(%s);", (yyvsp[(2) - (4)].str));
             out("cursor%d    = i->cur;", p);
             out("container%d = i->con;", p);
             out("element%d   = i->ele;", p);
             out("}");
             path[p] = atoi((yyvsp[(4) - (4)].str));
           }
    break;

  case 144:
#line 1005 "./xp-gram.y"
    {  if (call_below(OPTIMIZE_OP, get_path_num((yyvsp[(3) - (4)].str)))) { 
               out("call_down(te, %d, OPTIMIZE_OP, 1, %s);",
                   get_path_num((yyvsp[(3) - (4)].str)), (yyvsp[(3) - (4)].str));
               if (in_optimize_proc && (retrieval == RETRIEVAL_NEVER)) { 
                 out("if (%s->layer == te->layerno)", (yyvsp[(3) - (4)].str));
                 out("error(\"retrieval_never layer%s cannot be retrieval layer\");",
                     layer_name);
               }    
            }
            else
               parse_error("no optimize() function on lower layer");
         }
    break;

  case 145:
#line 1018 "./xp-gram.y"
    {  if (call_below(XFORM_OP, get_param_num((yyvsp[(1) - (8)].str)))) {
              out("call_down(te, %d, XFORM_OP, 4, %s, %s, %s, P2_cont_name);",
                  get_path_num((yyvsp[(3) - (8)].str)), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str));
              if ((get_param_num((yyvsp[(3) - (8)].str)) != get_param_num((yyvsp[(5) - (8)].str))) ||
                  (get_param_num((yyvsp[(5) - (8)].str)) != get_param_num((yyvsp[(7) - (8)].str))))
                 parse_error("xform parameter number arguments don't match");
            }
            else
              parse_error("no concrete operations for terminal layer");
         }
    break;

  case 146:
#line 1029 "./xp-gram.y"
    { if (strcmp((yyvsp[(5) - (6)].str),"") == 0)
              out("%s(te, %s);", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str));
           else
              out("%s(te, %s, %s);", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
         }
    break;

  case 147:
#line 1035 "./xp-gram.y"
    { if (strcmp((yyvsp[(5) - (6)].str),"") == 0)
              out("%s(te, %s);", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str));
           else
              out("%s(te, %s, %s);", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
         }
    break;

  case 148:
#line 1041 "./xp-gram.y"
    { opcallN((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].aptr)); }
    break;

  case 149:
#line 1046 "./xp-gram.y"
    {  if (call_below(LOPTIMIZE_OP, get_path_num((yyvsp[(7) - (8)].str)))) {
               out("call_down(te, %d, LOPTIMIZE_OP, 3, %s, %s, %s);",
                   get_path_num((yyvsp[(7) - (8)].str)), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str));
            }
            else
               parse_error("no loptimize() function on lower layer");
        }
    break;

  case 155:
#line 1083 "./xp-gram.y"
    {
            out("error(\"%s has no annotations\");", layer_name);
          }
    break;

  case 156:
#line 1087 "./xp-gram.y"
    {
            /* LITERAL may be 0 */
            add_ddlhint_annotation();
            check_ddlhint_arguments((yyvsp[(2) - (3)].str));
          }
    break;

  case 157:
#line 1093 "./xp-gram.y"
    {
            /* This is not fully implemented. (JAT) */
            add_ddlhint_annotation();
            check_ddlhint_arguments((yyvsp[(4) - (5)].str));
            out("number_of_annotations++;");
            out("if (number_of_annotations > %s)", (yyvsp[(2) - (5)].str));
            out("error(\"%%s has too many annotations\");", layer_name);
          }
    break;

  case 158:
#line 1113 "./xp-gram.y"
    {  strcpy((yyval.str), (yyvsp[(1) - (1)].str));
          }
    break;

  case 159:
#line 1116 "./xp-gram.y"
    {  strcpy((yyval.str), "/* ");
             strcat((yyval.str), (((yyvsp[(1) - (1)].str))+2));
             strcat((yyval.str), " */\n");
          }
    break;

  case 160:
#line 1121 "./xp-gram.y"
    {  strcpy((yyval.str),"ds");
          }
    break;

  case 161:
#line 1124 "./xp-gram.y"
    {  strcpy((yyval.str),"mem");
          }
    break;

  case 162:
#line 1127 "./xp-gram.y"
    {  strcpy((yyval.str),"top");
          }
    break;

  case 163:
#line 1130 "./xp-gram.y"
    {  strcpy((yyval.str), (yyvsp[(1) - (1)].str));
          }
    break;

  case 164:
#line 1133 "./xp-gram.y"
    {  strcpy((yyval.str), (yyvsp[(1) - (1)].str));
          }
    break;

  case 165:
#line 1136 "./xp-gram.y"
    {  strcpy((yyval.str),"[");
          }
    break;

  case 166:
#line 1139 "./xp-gram.y"
    {  strcpy((yyval.str),"]");
          }
    break;

  case 167:
#line 1142 "./xp-gram.y"
    {  strcpy((yyval.str),"(");
          }
    break;

  case 168:
#line 1145 "./xp-gram.y"
    {  strcpy((yyval.str),")");
          }
    break;

  case 169:
#line 1148 "./xp-gram.y"
    {  strcpy((yyval.str),",");
          }
    break;

  case 170:
#line 1151 "./xp-gram.y"
    {  strcpy((yyval.str),":");
          }
    break;

  case 171:
#line 1154 "./xp-gram.y"
    {  strcpy((yyval.str),"*");
          }
    break;

  case 172:
#line 1157 "./xp-gram.y"
    {  strcpy((yyval.str),"=");
          }
    break;

  case 173:
#line 1160 "./xp-gram.y"
    {  do_dollar((yyvsp[(1) - (1)].str), (yyval.str)); 
         }
    break;

  case 174:
#line 1175 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), "container%d->expr", "cursor%d->cont",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 175:
#line 1179 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "container%d->ctype->cctype->container_id",
                             "container%d->container_id",
                             "cursor%d->container_id", NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 176:
#line 1184 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "container%d->name", "container%d->type",
                             "cursor%d->cont_type", NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 177:
#line 1188 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), "cursor%d->expr",
                             NULL, NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 178:
#line 1192 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), NULL, (char *) -1, "cursor%d->cursor_id",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 179:
#line 1196 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "cursor%d->name", "cursor%d->type", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 180:
#line 1200 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, "cursor%d->predicate", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 181:
#line 1204 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, "record->expr", NULL, NULL);
          }
    break;

  case 182:
#line 1207 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), NULL, NULL, NULL);
          }
    break;

  case 183:
#line 1210 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), NULL, NULL, NULL);
          }
    break;

  case 184:
#line 1213 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), NULL, NULL, NULL);
          }
    break;

  case 185:
#line 1216 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "orig_type", "container%d->orig_type",
                             "cursor%d->orig_type", NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 186:
#line 1220 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "element%d->name",
                             "container%d->obj_type",  "cursor%d->obj_type",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 187:
#line 1225 "./xp-gram.y"
    {
            sprintf((yyval.str), "((struct %s_annote *) lookup_annotation(te, %s, %s))",
                    layer_name, xp_container_id(), xp_container_name());
          }
    break;

  case 188:
#line 1230 "./xp-gram.y"
    {
            assert((yyvsp[(2) - (2)].str) != NULL);
            sprintf((yyval.str),
                    "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                    layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
          }
    break;

  case 189:
#line 1237 "./xp-gram.y"
    {  ikeyword_action((yyval.str), NULL, "cs->%s", NULL, NULL, NULL, (yyvsp[(2) - (2)].str));
          }
    break;

  case 190:
#line 1240 "./xp-gram.y"
    {  ikeyword_action((yyval.str), NULL, "ks->%s", NULL, NULL, NULL, (yyvsp[(2) - (2)].str));
          }
    break;

  case 191:
#line 1243 "./xp-gram.y"
    {  ikeyword_action((yyval.str), NULL, "te->layerno", NULL, NULL, NULL);
          }
    break;

  case 192:
#line 1246 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), NULL, (char *) -1, "cursor%d->layer",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 193:
#line 1250 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, "cursor%d->cost", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 194:
#line 1254 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, "container%d->funbody",
                             "cursor%d->funbody", NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 195:
#line 1258 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, "container%d->op_list",
                             "cursor%d->op_list", "schema%d->op_list",
                             get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 196:
#line 1263 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, (char *) -1,
                             "cursor%d->proceduralize_ref", NULL,
                             get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 197:
#line 1268 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, (char *) -1,
                             "cursor%d->orderby_field", NULL,
                             get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 198:
#line 1273 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, (char *) -1,
                             "cursor%d->orderby_direction",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 199:
#line 1278 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1, (char *) -1,
                             "cursor%d->retrieval_direction",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 200:
#line 1287 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (char *) -1,
#if 0
             /* schema is an error if not a schema container or cursor. */
             "(container%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"container->schema"
               " is un-initialized, cannot expand schema\")"
               ": container%d->schema",
             "(cursor%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"cursor->schema"
               " is un-initialized, cannot expand schema\")"
               ": cursor%d->schema",
#else
              /* schema is the empty string (schema[0] == '\0') if not
                 a schema container or cursor. */
              "container%d->schema", "cursor%d->schema",
#endif
             NULL, get_param_num((yyvsp[(1) - (1)].str)), get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 201:
#line 1309 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->linkpredicate", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 202:
#line 1313 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->linklayer", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 203:
#line 1317 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->linkcost", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 204:
#line 1321 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->cresidual", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 205:
#line 1325 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->presidual", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 206:
#line 1329 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->apply", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 207:
#line 1333 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "((struct %s_annote *)"
                             "(lstate%d->linkannote))",
                             NULL, NULL, layer_name, NULL, get_param_num((yyvsp[(1) - (1)].str))); 
          }
    break;

  case 208:
#line 1338 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->linkname", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 209:
#line 1342 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->pcard", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 210:
#line 1346 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->ccard", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 211:
#line 1350 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "cursor%d->bound", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 212:
#line 1354 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), (yyvsp[(1) - (1)].str), NULL, NULL, NULL, NULL);
          }
    break;

  case 213:
#line 1357 "./xp-gram.y"
    {  ikeyword_action((yyval.str), (yyvsp[(1) - (1)].str), "lstate%d->special_foreachl", NULL, NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 215:
#line 1374 "./xp-gram.y"
    {  strcpy((yyval.str), ".");
         }
    break;

  case 216:
#line 1377 "./xp-gram.y"
    {  strcpy((yyval.str), (yyvsp[(1) - (1)].str));
         }
    break;

  case 217:
#line 1380 "./xp-gram.y"
    {
#if 0
            /* This statement replaces double quote with the empty
               string.  This is bad--with this statement in here,
               there is no way to emit, for example character escape
               codes, such as backslash n (newline). (JAT) */
            /* Previous to revision 1.14, this statement instead
               replaced backslash quote (\") with quote (").
               This is good, so I have re-instated this behavior.
               (JAT) */
            remove_char((yyvsp[(1) - (1)].str), '\\');
#else
            /* Replace backslash quote (\") with quote (") */
            replace_string_inplace((yyvsp[(1) - (1)].str), "\\\"", "\"");
#endif
            fputs((yyvsp[(1) - (1)].str), stdout);
            (yyval.str)[0] = '\0';
         }
    break;

  case 219:
#line 1413 "./xp-gram.y"
    {  jettison();
          }
    break;

  case 220:
#line 1416 "./xp-gram.y"
    {  if (output_semicolon || strcmp((yyvsp[(2) - (2)].str), ";") != 0)
               strcat(ctoken_line, (yyvsp[(2) - (2)].str));
             jettison();
          }
    break;

  case 221:
#line 1421 "./xp-gram.y"
    {  jettison();
          }
    break;

  case 222:
#line 1427 "./xp-gram.y"
    {  strcpy((yyval.str), ";");
          }
    break;

  case 223:
#line 1430 "./xp-gram.y"
    {  strcpy((yyval.str), "{");
          }
    break;

  case 224:
#line 1433 "./xp-gram.y"
    {  strcpy((yyval.str), "}");
          }
    break;

  case 225:
#line 1439 "./xp-gram.y"
    { /* I assume that any generated code has lots of semicolons (DSB) */
         output_semicolon = FALSE;
       }
    break;

  case 226:
#line 1443 "./xp-gram.y"
    { /* I assume that any generated code has lots of semicolons (DSB) */
         output_semicolon = FALSE;
       }
    break;

  case 227:
#line 1447 "./xp-gram.y"
    { output_semicolon = TRUE;
       }
    break;

  case 228:
#line 1450 "./xp-gram.y"
    {
         /* I was having the problem in an XSTART/XEND block
            containing only a semicoln (ie %{ ; %}) that the
            semicolon was not output.  This fix seems to solve that
            problem without introducing too many un-intended
            semicolons elsewhere. (JAT) */
         output_semicolon = TRUE;
       }
    break;

  case 229:
#line 1479 "./xp-gram.y"
    { 
          force_field_ref = FALSE;
          ref_util((yyvsp[(1) - (3)].str));
       }
    break;

  case 230:
#line 1484 "./xp-gram.y"
    { 
          force_field_ref = TRUE;
          ref_util((yyvsp[(1) - (4)].str));
       }
    break;

  case 231:
#line 1489 "./xp-gram.y"
    {
         force_field_ref = FALSE;
         ref_util_array((yyvsp[(1) - (6)].str));
       }
    break;

  case 232:
#line 1494 "./xp-gram.y"
    {
         force_field_ref = TRUE;
         ref_util_array((yyvsp[(1) - (7)].str));
       }
    break;

  case 233:
#line 1499 "./xp-gram.y"
    {
          iref_util_array();
       }
    break;

  case 234:
#line 1503 "./xp-gram.y"
    {
         iref_util();
       }
    break;

  case 235:
#line 1525 "./xp-gram.y"
    { unknown_idx = TRUE;
          strcpy(index_val, (yyvsp[(2) - (2)].str));
        }
    break;

  case 236:
#line 1529 "./xp-gram.y"
    { unknown_idx = FALSE;
          strcpy(index_val, (yyvsp[(1) - (1)].str));
        }
    break;

  case 237:
#line 1533 "./xp-gram.y"
    { unknown_idx = TRUE;
          sprintf(index_val, "cs->%s", (yyvsp[(2) - (2)].str)); 
        }
    break;

  case 238:
#line 1537 "./xp-gram.y"
    { unknown_idx = TRUE;
          sprintf(index_val, "ks->%s", (yyvsp[(2) - (2)].str));
        }
    break;

  case 239:
#line 1541 "./xp-gram.y"
    { unknown_idx = TRUE;
#if 0
          sprintf(index_val,"((struct %s_annote *)(te->annotation))->%s",
                  layer_name, (yyvsp[(2) - (2)].str));
#else
          assert((yyvsp[(2) - (2)].str) != NULL);
          sprintf(index_val,
                  "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                  layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
#endif
        }
    break;

  case 240:
#line 1553 "./xp-gram.y"
    { unknown_idx = FALSE;
          strcpy(index_val, (yyvsp[(1) - (1)].str));
        }
    break;

  case 241:
#line 1575 "./xp-gram.y"
    { unknown_fld = TRUE;
          strcpy(field_val, (yyvsp[(2) - (2)].str));
        }
    break;

  case 242:
#line 1579 "./xp-gram.y"
    { unknown_fld = TRUE;
          strcpy(field_val, (yyvsp[(1) - (1)].str));
        }
    break;

  case 243:
#line 1583 "./xp-gram.y"
    { unknown_fld = TRUE;
          sprintf(field_val, "cs->%s", (yyvsp[(2) - (2)].str));
        }
    break;

  case 244:
#line 1587 "./xp-gram.y"
    { unknown_fld = TRUE;
          sprintf(field_val, "ks->%s", (yyvsp[(2) - (2)].str));
        }
    break;

  case 245:
#line 1591 "./xp-gram.y"
    { unknown_fld = FALSE;
          strcpy(field_val, (yyvsp[(1) - (1)].str));
        }
    break;

  case 246:
#line 1595 "./xp-gram.y"
    { unknown_fld = TRUE;
#if 0
          sprintf(field_val,"((struct %s_annote *)(te->annotation))->%s",
                  layer_name, (yyvsp[(2) - (2)].str));
#else
          assert((yyvsp[(2) - (2)].str) != NULL);
          sprintf(field_val,
                  "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                  layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
#endif
        }
    break;

  case 247:
#line 1624 "./xp-gram.y"
    {
         force_field_ref = FALSE;
         kref_util((yyvsp[(1) - (3)].str));
       }
    break;

  case 248:
#line 1629 "./xp-gram.y"
    {
         /* This feature is not used in any existing layer. (JAT) */
         force_field_ref = TRUE;
         kref_util((yyvsp[(1) - (4)].str));
       }
    break;

  case 249:
#line 1635 "./xp-gram.y"
    {
         kref_util_array((yyvsp[(1) - (6)].str));
       }
    break;

  case 250:
#line 1639 "./xp-gram.y"
    {
          iref_util();
       }
    break;

  case 251:
#line 1643 "./xp-gram.y"
    { 
          iref_util_array();
       }
    break;

  case 252:
#line 1671 "./xp-gram.y"
    {  jettison();
             out("NONTERM(P2_rf);");
          }
    break;

  case 254:
#line 1679 "./xp-gram.y"
    {  jettison();
             out("NONTERM(P2_rf);");
          }
    break;

  case 255:
#line 1683 "./xp-gram.y"
    {  sref_util((yyvsp[(1) - (3)].str));
             jettison();
             out("NONTERM(P2_rf);");
          }
    break;

  case 256:
#line 1688 "./xp-gram.y"
    { 
             strcat(ctoken_line, " ");
             strcat(ctoken_line, (yyvsp[(1) - (1)].str));
          }
    break;

  case 258:
#line 1694 "./xp-gram.y"
    { 
             strcat(ctoken_line, " ");
             strcat(ctoken_line, (yyvsp[(1) - (1)].str));
          }
    break;

  case 262:
#line 1705 "./xp-gram.y"
    { 
             strcat(ctoken_line, "->");
          }
    break;

  case 263:
#line 1709 "./xp-gram.y"
    { 
             strcat(ctoken_line, ".");
          }
    break;

  case 264:
#line 1713 "./xp-gram.y"
    {  jettison();
             out("NONTERM(terminal_vstring(\".%s%%d\", te->layerno));", (yyvsp[(3) - (3)].str));
          }
    break;

  case 265:
#line 1726 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 266:
#line 1728 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 267:
#line 1730 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 268:
#line 1732 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 269:
#line 1734 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 270:
#line 1736 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 271:
#line 1738 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 272:
#line 1740 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 273:
#line 1742 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 274:
#line 1744 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 275:
#line 1749 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 276:
#line 1751 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 277:
#line 1753 "./xp-gram.y"
    {  jettison(); do_action((yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 278:
#line 1758 "./xp-gram.y"
    {  jettison(); do_adhoc_action((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].aptr));  }
    break;

  case 279:
#line 1769 "./xp-gram.y"
    {  ckeyword_action("(cursor%d->expr)", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 280:
#line 1773 "./xp-gram.y"
    {  ckeyword_action("(container%d->expr)", "(cursor%d->cont)",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 281:
#line 1777 "./xp-gram.y"
    {  ckeyword_action("\"%%%%d\", container%d->container_id",
                             "\"%%%%d\", cursor%d->container_id",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 282:
#line 1782 "./xp-gram.y"
    {  ckeyword_action("(container%d->type)", "(cursor%d->cont_type)",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 283:
#line 1786 "./xp-gram.y"
    {  ckeyword_action("\"%%%%d\", cursor%d->cursor_id", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 284:
#line 1790 "./xp-gram.y"
    {  ckeyword_action("cursor%d->predicate", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 285:
#line 1794 "./xp-gram.y"
    {  ckeyword_action("container%d->orig_type", "cursor%d->orig_type",
                             NULL, get_param_num((yyvsp[(1) - (1)].str))); 
          }
    break;

  case 286:
#line 1798 "./xp-gram.y"
    {  ckeyword_action("container%d->obj_type", "cursor%d->obj_type",
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 287:
#line 1802 "./xp-gram.y"
    {  ckeyword_action("cursor%d->type", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 288:
#line 1806 "./xp-gram.y"
    {  ckeyword_action("record->expr", NULL, NULL);
          }
    break;

  case 289:
#line 1809 "./xp-gram.y"
    {
#if 0
            ckeyword_action("((struct %s_annote *)(te->annotation))->%s", NULL,
                            NULL, layer_name, (yyvsp[(2) - (2)].str));
#else
            assert((yyvsp[(2) - (2)].str) != NULL);
            ckeyword_action(
              "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s", NULL,
              NULL, layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
#endif
          }
    break;

  case 290:
#line 1821 "./xp-gram.y"
    {  ckeyword_action("cs->%s", NULL, NULL, (yyvsp[(2) - (2)].str));
          }
    break;

  case 291:
#line 1824 "./xp-gram.y"
    {  ckeyword_action("ks->%s", NULL, NULL, (yyvsp[(2) - (2)].str));
          }
    break;

  case 292:
#line 1827 "./xp-gram.y"
    {  ckeyword_action("\"%%%%s\", %s", NULL, NULL, (yyvsp[(2) - (2)].str));
          }
    break;

  case 293:
#line 1830 "./xp-gram.y"
    {  /* expr is a parse tree (NODE *).  Thus, it would be
                awarkward and inefficient to use ckeyword_action here,
                since (1) we would have to flatten expr in order to
                pass it to ckeyword_action, and (2) ckeyword_action
                would immediately convert expr back into a parse
                tree. (JAT) */
             char s[MAX_IDENT_LEN+10];
             jettison();
             sprintf(s, "NONTERM(expr%d);", get_param_num((yyvsp[(1) - (1)].str)));
             out(s);
          }
    break;

  case 294:
#line 1842 "./xp-gram.y"
    {  ckeyword_action("\"%%%%s\", %s", NULL, NULL, "field");
          }
    break;

  case 295:
#line 1845 "./xp-gram.y"
    {  ckeyword_action("cursor%d->orderby_field", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 296:
#line 1849 "./xp-gram.y"
    {  ckeyword_action("cursor%d->orderby_direction", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 297:
#line 1853 "./xp-gram.y"
    {  ckeyword_action("cursor%d->retrieval_direction", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 298:
#line 1857 "./xp-gram.y"
    {  ckeyword_action("vp%d", NULL, NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 299:
#line 1864 "./xp-gram.y"
    {  ckeyword_action(
#if 0
             /* schema is an error if not a schema container or cursor. */
             "(container%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"container->schema"
               " is un-initialized, cannot expand schema\")"
               ": container%d->schema",
             "(cursor%d->schema[0] == '\\0')?"
               " (char *) parse_error(\"cursor->schema"
               " is un-initialized, cannot expand schema\")"
               ": cursor%d->schema",
#else
             /* schema is the empty string (schema[0] == '\0') if not
                 a schema container or cursor. */
             "container%d->schema", "cursor%d->schema",
#endif
             "schema%d->expr",
             get_param_num((yyvsp[(1) - (1)].str)), get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 300:
#line 1887 "./xp-gram.y"
    {  ckeyword_action("lstate%d->linkpredicate", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 301:
#line 1891 "./xp-gram.y"
    {  ckeyword_action("lstate%d->linklayer", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 302:
#line 1895 "./xp-gram.y"
    {  ckeyword_action("((struct %s_annote *)(lstate%d->linkannote))",
                             layer_name, NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 303:
#line 1899 "./xp-gram.y"
    {  ckeyword_action("lstate%d->linkname", NULL,
                             NULL, get_param_num((yyvsp[(1) - (1)].str)));
          }
    break;

  case 304:
#line 1912 "./xp-gram.y"
    { opcall1(INIT_CONT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 305:
#line 1914 "./xp-gram.y"
    { opcall1(C_PUT_OP_VEC_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 306:
#line 1916 "./xp-gram.y"
    { opcall1(C_VERBATIM_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 307:
#line 1918 "./xp-gram.y"
    { opcall1(K_PUT_OP_VEC_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 308:
#line 1920 "./xp-gram.y"
    { opcall1(K_VERBATIM_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 309:
#line 1922 "./xp-gram.y"
    { opcall1(S_PUT_OP_VEC_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 310:
#line 1924 "./xp-gram.y"
    { opcall1(S_VERBATIM_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 311:
#line 1930 "./xp-gram.y"
    { opcall1(INIT_CURS_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 312:
#line 1932 "./xp-gram.y"
    { opcall1(OPEN_CONT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 313:
#line 1934 "./xp-gram.y"
    { opcall2(OPEN_CONT_NUMBER_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 314:
#line 1936 "./xp-gram.y"
    { opcall1(CHECKPOINT_CONT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 315:
#line 1938 "./xp-gram.y"
    { opcall1(CLOSE_CONT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 316:
#line 1940 "./xp-gram.y"
    { opcall2(INSERT_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 317:
#line 1942 "./xp-gram.y"
    { opcall3(VARINSERT_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 318:
#line 1944 "./xp-gram.y"
    { out("{"
               "REC_ARG P2_rec;"
               "strcpy(P2_rec.expr,\"%s\");", (yyvsp[(5) - (6)].str));
           opcall2(INSERT_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), "&P2_rec");
           out("}");
         }
    break;

  case 319:
#line 1951 "./xp-gram.y"
    { out("{"
               "REC_ARG P2_rec;"
               "strcpy(P2_rec.expr,%s);", (yyvsp[(6) - (7)].str));
           opcall2(INSERT_OP, (yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].str), "&P2_rec");
           out("}");
         }
    break;

  case 320:
#line 1958 "./xp-gram.y"
    { opcall1(ADV_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 321:
#line 1960 "./xp-gram.y"
    { opcall3(UPD_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 322:
#line 1962 "./xp-gram.y"
    { opcall2(FOREACH_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 323:
#line 1964 "./xp-gram.y"
    { out("P2_before_foreach = P2_result;"
               "P2_result = 0;"
               "{"
               "NODE *P2_before_foreach = 0;"
               "NODE *P2_after_foreach;");
         }
    break;

  case 324:
#line 1971 "./xp-gram.y"
    { out("P2_after_foreach = P2_result;"
               "P2_result = 0;");
           opcall2(FOREACH_OP, (yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].str), "P2_after_foreach");
           out("}"
               "P2_result = nonterm(UNT,NULL,2,P2_before_foreach,P2_result);");
         }
    break;

  case 325:
#line 1978 "./xp-gram.y"
    { opcall2(ROFEACH_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 326:
#line 1980 "./xp-gram.y"
    { out("P2_before_foreach = P2_result;"
               "P2_result = 0; {"
               "NODE *P2_before_foreach = 0;"
               "NODE *P2_after_foreach;");
         }
    break;

  case 327:
#line 1986 "./xp-gram.y"
    { out("P2_after_foreach = P2_result;"
               "P2_result = 0;");
           opcall2(ROFEACH_OP, (yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].str), "P2_after_foreach");
           out("}"
               "P2_result = nonterm(UNT,NULL,2,P2_before_foreach,P2_result);");
         }
    break;

  case 328:
#line 1993 "./xp-gram.y"
    { opcall1(REV_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 329:
#line 1995 "./xp-gram.y"
    { opcall2(REF_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 330:
#line 1997 "./xp-gram.y"
    { opcall1(DELETE_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 331:
#line 1999 "./xp-gram.y"
    { opcall1(DELETE_CURS_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 332:
#line 2001 "./xp-gram.y"
    { opcall1(RESET_START_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 333:
#line 2003 "./xp-gram.y"
    { opcall1(RESET_END_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 334:
#line 2005 "./xp-gram.y"
    { opcall2(SWAP_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 335:
#line 2007 "./xp-gram.y"
    { opcall4(SYNC_CONT_OP, (yyvsp[(1) - (10)].str), (yyvsp[(3) - (10)].str), (yyvsp[(5) - (10)].str), (yyvsp[(7) - (10)].str), (yyvsp[(9) - (10)].str)); }
    break;

  case 336:
#line 2009 "./xp-gram.y"
    { opcall2(GETREC_OP, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].str)); }
    break;

  case 337:
#line 2011 "./xp-gram.y"
    {  jettison();
            if (strcmp((yyvsp[(5) - (6)].str),"") == 0)
              out("NONTERM(%s(te, %s));", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str));
            else
              out("NONTERM(%s(te, %s, %s));", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
         }
    break;

  case 338:
#line 2018 "./xp-gram.y"
    {  jettison();
            if (strcmp((yyvsp[(5) - (6)].str),"") == 0)
              out("NONTERM(%s(te, %s));", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str));
            else
              out("NONTERM(%s(te, %s, %s));", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].str), (yyvsp[(5) - (6)].str));
         }
    break;

  case 339:
#line 2028 "./xp-gram.y"
    { opcall1(OPEN_SCHEMA_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 340:
#line 2030 "./xp-gram.y"
    { opcall1(INIT_SCHEMA_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 341:
#line 2032 "./xp-gram.y"
    { opcall1(CLOSE_SCHEMA_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 342:
#line 2035 "./xp-gram.y"
    { opcall1(ABORT_XACT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 343:
#line 2037 "./xp-gram.y"
    { opcall1(BEGIN_XACT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 344:
#line 2039 "./xp-gram.y"
    { opcall1(COMMIT_XACT_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 345:
#line 2041 "./xp-gram.y"
    { opcall1(CHECKPOINT_SCHEMA_OP, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].str)); }
    break;

  case 346:
#line 2046 "./xp-gram.y"
    { opcall3(RESETC_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 347:
#line 2048 "./xp-gram.y"
    { opcall3(RESETP_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 348:
#line 2050 "./xp-gram.y"
    { opcall3(ADVC_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 349:
#line 2052 "./xp-gram.y"
    { opcall3(ADVP_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 350:
#line 2054 "./xp-gram.y"
    { opcall4(FOREACHL_OP, (yyvsp[(1) - (10)].str), (yyvsp[(3) - (10)].str), (yyvsp[(5) - (10)].str), (yyvsp[(7) - (10)].str), (yyvsp[(9) - (10)].str)); }
    break;

  case 351:
#line 2056 "./xp-gram.y"
    { opcall4(FOREACHC_OP, (yyvsp[(1) - (10)].str), (yyvsp[(3) - (10)].str), (yyvsp[(5) - (10)].str), (yyvsp[(7) - (10)].str), (yyvsp[(9) - (10)].str)); }
    break;

  case 352:
#line 2058 "./xp-gram.y"
    { opcall4(FOREACHP_OP, (yyvsp[(1) - (10)].str), (yyvsp[(3) - (10)].str), (yyvsp[(5) - (10)].str), (yyvsp[(7) - (10)].str), (yyvsp[(9) - (10)].str)); }
    break;

  case 353:
#line 2060 "./xp-gram.y"
    { opcall3(CONNECT_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 354:
#line 2062 "./xp-gram.y"
    { opcall3(DISCONNECT_OP, (yyvsp[(1) - (8)].str), (yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].str), (yyvsp[(7) - (8)].str)); }
    break;

  case 355:
#line 2071 "./xp-gram.y"
    { (yyval.aptr) = NULL; }
    break;

  case 356:
#line 2073 "./xp-gram.y"
    { adhoc_arg = NULL;  }
    break;

  case 357:
#line 2075 "./xp-gram.y"
    { (yyval.aptr) = adhoc_arg; }
    break;

  case 360:
#line 2085 "./xp-gram.y"
    { adhoc_arg = append_arg(adhoc_arg, (yyvsp[(1) - (1)].str)); }
    break;

  case 361:
#line 2087 "./xp-gram.y"
    { adhoc_arg = append_arg(adhoc_arg, (yyvsp[(1) - (1)].str)); }
    break;

  case 362:
#line 2089 "./xp-gram.y"
    { adhoc_arg = append_arg(adhoc_arg, (yyvsp[(1) - (1)].str)); }
    break;

  case 363:
#line 2116 "./xp-gram.y"
    { out("P2_lhs_rf = P2_rf;");
           out("P2_previous = P2_result;");
           out("P2_result = NULL;");
           lhs_pnum         = pnum;
           lhs_cnum         = cnum;
           lhs_rparam       = realm_param;
           lhs_field        = rf_field;
           lhs_cursor_field = cursor_field || force_field_ref;
           lhs_unknown_fld  = unknown_fld;
           lhs_obj_field    = obj_field;
         }
    break;

  case 364:
#line 2128 "./xp-gram.y"
    { jettison();
           if (lhs_cursor_field && !lhs_obj_field) {
              /* generate the code directly without calling the lower layer */
              out("{"
                  "NODE *rhs = P2_result;"
                  "P2_result = P2_previous;"
                  "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                  "rhs,terminal_string1(\";\")));"
                  "}");
           }
           if (lhs_cursor_field && lhs_obj_field) {
               /* generate a call to position */ 
              if (call_below(POS_OP, lhs_pnum)) {
                 out("{"
                     "CURS_ARG c;"
                     "NODE *rhs;"
                     "memcpy(&c,cursor%d,sizeof(CURS_ARG));", lhs_cnum);
                 /* P2_result has parse tree of rhs of assignment statement
                    P2_previous has parse tree of everything prior to statement
                    P2_lhs_rf has parse tree of right-hand side of assignment */
                 out("rhs = P2_result;"
                     "P2_result = P2_previous;");
                 /* now set the new cursor's position to the lhs */
                 out("sprint_ptree(c.expr,P2_lhs_rf);");
                 /* P2_lhs_rf has ".obj" attached to it. remove it */
                 out("c.expr[strlen(c.expr)-4] = '\\0';"
                     "NONTERM(call_down(te, %d, POS_OP, 2, &c, rhs));",
                     lhs_pnum);
                 out("}");
              }
              else {
                /* generate the code directly w/out calling the lower layer */
                out("{"
                    "NODE *rhs = P2_result; P2_result = P2_previous;"
                    "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                    "rhs,terminal_string1(\";\")));"
                    "}");
              }
           }
           if (!lhs_cursor_field) {
             out("{"
                 "NODE *rhs = P2_result; P2_result = P2_previous;"
                 "NONTERM(nonterm(UNT,NULL,4,P2_lhs_rf,terminal_string1(\"=\"),"
                 "rhs,terminal_string1(\";\")));"
                 "}");
           }
         }
    break;

  case 367:
#line 2196 "./xp-gram.y"
    {  jettison();
           }
    break;

  case 370:
#line 2217 "./xp-gram.y"
    {  strcpy(member_type, (yyvsp[(2) - (3)].str));
             left_expand(member_ctype, new_ptype(STR, UND, NULL));
          }
    break;

  case 371:
#line 2221 "./xp-gram.y"
    {  identifier_declaration_action((yyvsp[(1) - (2)].str));
          }
    break;

  case 372:
#line 2224 "./xp-gram.y"
    {  parse_warning(3, "Don't know how to process this statement");
          }
    break;

  case 376:
#line 2236 "./xp-gram.y"
    { left_expand(member_ctype, new_ptype(PTR, UND, NULL));
          }
    break;

  case 380:
#line 2248 "./xp-gram.y"
    { strcpy(member_name, (yyvsp[(1) - (1)].str));
            know_member_name = TRUE;
          }
    break;

  case 381:
#line 2252 "./xp-gram.y"
    {
#if 0
            sprintf(member_name, "((struct %s_annote *)(te->annotation))->%s",
                    layer_name, (yyvsp[(2) - (2)].str));
#else
            assert((yyvsp[(2) - (2)].str) != NULL);
            sprintf(member_name,
                    "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s",
                    layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
#endif
            know_member_name = FALSE;
          }
    break;

  case 382:
#line 2265 "./xp-gram.y"
    { strcpy(member_name, (yyvsp[(2) - (2)].str)); 
            know_member_name = FALSE;
          }
    break;

  case 385:
#line 2274 "./xp-gram.y"
    { left_expand(member_ctype, new_ptype(FUN, UND, NULL));
          }
    break;

  case 386:
#line 2280 "./xp-gram.y"
    { left_expand(member_ctype, new_ptype(ARR, UND, NULL));
          }
    break;

  case 387:
#line 2283 "./xp-gram.y"
    { left_expand(member_ctype, new_ptype(ARR, UND, (yyvsp[(2) - (3)].node)));
          }
    break;

  case 388:
#line 2286 "./xp-gram.y"
    { left_expand(member_ctype, new_ptype(ARR, UND, (yyvsp[(3) - (4)].node)));
          }
    break;

  case 389:
#line 2292 "./xp-gram.y"
    {
            char s[MAX_IDENT_LEN*4+10];
#if 0
             sprintf(s, "terminal_string(((struct %s_annote *)"
                     "(te->annotation))->%s)", layer_name, (yyvsp[(2) - (2)].str));
#else
             assert((yyvsp[(2) - (2)].str) != NULL);
             sprintf(s, "terminal_string("
               "((struct %s_annote *) lookup_annotation(te, %s, %s))->%s)",
               layer_name, xp_container_id(), xp_container_name(), (yyvsp[(2) - (2)].str));
#endif
             (yyval.node) = terminal_string(s);
          }
    break;

  case 390:
#line 2306 "./xp-gram.y"
    {  (yyval.node) = terminal_string((yyvsp[(1) - (1)].str));
          }
    break;

  case 391:
#line 2309 "./xp-gram.y"
    {  (yyval.node) = terminal_string((yyvsp[(1) - (1)].str));
          }
    break;

  case 392:
#line 2312 "./xp-gram.y"
    {  char s[MAX_IDENT_LEN];
             sprintf(s, "terminal_string(%s)", (yyvsp[(2) - (2)].str));
             (yyval.node) = terminal_string(s);
          }
    break;


/* Line 1267 of yacc.c.  */
#line 5032 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 2317 "./xp-gram.y"


/*****************************************************************************/
/*                  End of Grammar.                                          */
/*****************************************************************************/

void
yyerror (char *string)
{
  parse_error("%s at \"%s\"", string, yytext);
}

int
yywrap (void)
{
  static int guard = 0;
  int i, alldone;
  
  if (!guard) { 
    FILE *fp1 = fopen(cdef_name, "r");
    FILE *fp2 = fopen(kdef_name, "r");
    if (!fp1 && !fp2) 
      return(1); /* Quit.  No defaults. (BJG) */
    guard = 1;
  }

  if (yyin) 
    fclose(yyin);
  
  alldone = 1;
  for(i = 0; op_tab[i].op_num; i++) { 
    int op = op_tab[i].op_num;
    if (op_exists_in_realm(op,layer_realm) && !seen[op]) { 
      if (retrieval_op(op) && !retrieval) { 
        continue;
        /* Don't generate retrieval ops for non-retrieval layers. (BJG) */
      }

      if (op_tab[i].param[0] == CUR)
        yyin = fopen(cdef_name,"r");
      else if (op_tab[i].param[0] == CON)
        yyin = fopen(kdef_name,"r");
      else
        continue; /* Got one of them weird functions. (BJG) */

      if (!yyin)
        continue; /* We don't have a spec. Try the next entry. (BJG) */

      seen[op] = TRUE;
      current_op = i;
      return(0); 
    }
  }
  return(alldone);
}

