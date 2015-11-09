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




/* Copy the first part of user declarations.  */
#line 1 "./ddl-gram.y"


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
#line 48 "./ddl-gram.y"
{
  char     str[MAX_IDENT_LEN];
  LISTNODE *node;
}
/* Line 193 of yacc.c.  */
#line 197 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 210 "y.tab.c"

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
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   425

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNRULES -- Number of states.  */
#define YYNSTATES  162

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    37,     2,    38,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    48,    50,    52,    54,    56,    58,
      60,    62,    66,    71,    75,    80,    82,    84,    87,    89,
      92,    94,    98,   100,   105,   107,   109,   111,   113,   115,
     117,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     139,   141,   144,   146,   149,   151,   155,   158,   160,   161,
     164,   165,   167,   169,   171,   173,   175,   181,   185,   194,
     200,   206,   213,   226,   236,   245,   250,   255,   260,   273,
     292,   296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,
      -1,    28,    -1,    44,    -1,    43,    44,    -1,    45,    -1,
      46,    -1,    31,    -1,    32,    -1,    33,    -1,    55,    -1,
      42,    -1,    47,    31,    32,    -1,    47,    31,    48,    32,
      -1,     7,    31,    32,    -1,     7,    31,    49,    32,    -1,
       6,    -1,    62,    -1,    48,    62,    -1,    50,    -1,    49,
      50,    -1,    33,    -1,    53,    34,    51,    -1,    53,    -1,
      53,    35,    54,    52,    -1,    36,    -1,     1,    -1,     3,
      -1,    42,    -1,     1,    -1,    51,    -1,    54,    37,    51,
      -1,     5,    -1,     3,    -1,     4,    -1,    34,    -1,    37,
      -1,    35,    -1,    36,    -1,    38,    -1,    39,    -1,    40,
      -1,     1,    42,    -1,    55,    -1,    55,    56,    -1,    53,
      -1,    57,    38,    53,    -1,     8,     3,    -1,     3,    -1,
      -1,     9,    56,    -1,    -1,     3,    -1,    22,    -1,    23,
      -1,    24,    -1,    33,    -1,    57,    10,    58,    11,    56,
      -1,    57,    58,     5,    -1,    57,    58,    19,    11,     5,
       6,    10,    56,    -1,    57,    58,    25,    13,    56,    -1,
      57,    15,    58,    11,    56,    -1,    57,    28,    58,    11,
      56,    59,    -1,    57,    28,    58,    11,    56,    15,    11,
      56,     6,    10,    56,    59,    -1,    57,    15,    58,    11,
      56,     6,    10,    56,    59,    -1,    57,    58,    13,    11,
      56,    26,    11,    56,    -1,    57,    58,    13,    56,    -1,
      57,    58,    14,    56,    -1,    57,    58,    17,     5,    -1,
      57,    28,    58,    11,    56,    17,     5,     6,    56,     6,
      56,    59,    -1,    57,    28,    58,    11,    56,    15,    11,
      56,     6,    10,    56,    17,     5,     6,    56,     6,    56,
      59,    -1,    57,    58,    27,    -1,    57,    16,    60,    14,
      61,    58,    18,    61,    58,    20,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   100,   100,   100,   100,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     103,   103,   112,   113,   116,   117,   120,   121,   122,   123,
     124,   128,   129,   130,   131,   135,   138,   139,   142,   143,
     147,   148,   159,   160,   168,   169,   173,   174,   175,   178,
     180,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   202,   203,   206,   207,   210,   211,   212,   215,
     216,   223,   226,   227,   228,   231,   232,   240,   246,   254,
     262,   270,   280,   295,   310,   320,   327,   334,   341,   358,
     379,   387
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "OP", "LITERAL", "WITH",
  "TYPEX", "OF", "OPTION", "SIZE", "IS", "FILENAME", "FIELD", "ON", "KEY",
  "LINK", "PREDICATE", "TO", "FILE_TOKEN", "WHERE", "FROM", "ONE_TOKEN",
  "MANY_TOKEN", "AT_MOST_ONE_TOKEN", "AT", "COUNTER", "ANONYMOUS",
  "TIMESTAMP", "PRE_ACTION", "POST_ACTION", "'{'", "'}'", "';'", "'='",
  "'['", "']'", "','", "'.'", "'('", "')'", "$accept", "reserved",
  "program", "segment", "any_token", "formatted", "with", "stmt_list",
  "eqn_list", "eqn", "param", "endsq", "name", "param_list", "expr_token",
  "expr", "pathexpr", "container", "option", "link", "card", "stmt", 0
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
     285,   123,   125,    59,    61,    91,    93,    44,    46,    40,
      41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    45,    45,
      45,    46,    46,    46,    46,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    58,    59,
      59,    60,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     4,     1,     1,     2,     1,     2,
       1,     3,     1,     4,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     3,     2,     1,     0,     2,
       0,     1,     1,     1,     1,     1,     5,     3,     8,     5,
       5,     6,    12,     9,     8,     4,     4,     4,    12,    18,
       3,    11
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    52,    53,    51,    35,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    26,    27,    28,
      54,    56,    57,    55,    58,    59,    60,    30,     0,    22,
      24,    25,     0,    29,    61,     0,     1,    23,     0,    48,
      46,    33,    40,    47,     0,    38,     0,    31,    75,     0,
      64,    68,    36,    34,    39,     0,    32,    37,    67,     0,
      68,    68,     0,    68,     0,     0,    41,    42,    66,     0,
       0,    71,     0,     0,    65,    77,     0,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,     0,     0,    49,     0,    76,    80,    72,    73,
      74,    68,    70,     0,    63,     0,    79,    45,    44,     0,
      43,     0,     0,     0,     0,     0,    81,     0,     0,    50,
       0,     0,    69,     0,     0,     0,     0,    70,    68,     0,
       0,    84,    78,    83,     0,     0,     0,     0,     0,     0,
      91,    70,    70,     0,    82,    88,     0,     0,     0,     0,
      70,    89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    53,    38,    39,    40,    41,    42,    59,    54,    55,
      76,   120,    77,   105,    98,    99,    61,    75,   126,    82,
     111,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -88
static const yytype_int16 yypact[] =
{
     113,   397,   -88,   -88,   -88,   -88,   -26,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,    73,   -88,
     -88,   -88,   -23,   -88,   -88,   242,   -88,   -88,   270,   -88,
     -88,   -88,   -88,   -88,   298,   -88,   -20,   -88,   -88,   326,
     -88,    19,   -88,   -88,   -88,   354,   -88,   -88,   -88,    15,
      37,    37,    21,    37,   354,   378,   -88,   -14,   -88,     4,
      27,   -88,    25,    40,   -88,   -88,   193,   202,    51,    47,
      17,   -88,   354,   202,   202,    41,   202,   202,   153,   -88,
     -88,   -88,    54,   202,   -88,    18,   -88,    60,   -88,   -88,
     -88,    37,    16,    42,   -88,    61,   -88,   -88,   -88,   354,
     -88,    65,    53,   202,    70,    97,   -88,    92,   105,   -88,
     202,    41,   -88,   202,   115,   202,   202,   133,    37,   137,
     202,   -88,   -88,   -88,   135,   150,   155,   202,   202,   202,
     -88,    11,   133,   177,   -88,   -88,   178,   202,   194,   202,
     133,   -88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,    12,   -88,   145,   -88,   -88,   -88,   -88,   -88,   147,
     -75,   -88,   -22,   -88,     3,   -87,   -88,   -69,    58,   -88,
      68,   143
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -63
static const yytype_int16 yytable[] =
{
     100,    79,    80,    43,    83,    45,   106,   107,    48,   112,
     113,   114,    37,    44,    65,    93,   116,   104,    78,   117,
     123,    92,    68,    56,    81,   123,    60,    69,   153,    70,
     103,   124,    56,   125,    71,    72,   132,    60,    94,    95,
      68,    43,   122,   137,   129,    69,   139,    73,   141,   142,
      37,    96,    84,   146,   118,   119,   101,    74,   102,   115,
     150,   151,   152,   108,   109,   110,   121,   128,   127,   144,
     158,   131,   160,    46,     1,   130,     2,     3,     4,     5,
       6,   133,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   134,   135,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,     1,   136,     2,     3,     4,     5,
       6,   140,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   123,   145,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,     1,   147,     2,     3,     4,   -62,
     148,   149,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   156,    47,   157,   -62,   -62,    30,    31,    32,
      33,    34,    35,    36,     1,   143,     2,     3,     4,   138,
     159,    64,    67,     1,    97,     2,     3,     4,     0,   154,
     155,     0,     0,     0,     0,     0,     0,     0,   161,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
      33,    34,    35,    36,     0,     0,    30,    31,    32,    33,
      34,    35,    36,    49,     0,    50,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    49,     0,    50,    51,    52,     0,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    49,
       0,    50,    57,    58,     0,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    49,     0,    50,
      63,    52,     0,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    49,     0,    50,    66,    58,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    85,     0,     0,     0,     0,     0,     0,
       0,    86,    87,     0,     0,    88,     0,    89,     0,     0,
       0,     0,     0,    90,     0,    91,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26
};

static const yytype_int16 yycheck[] =
{
      87,    70,    71,     0,    73,    31,    93,    94,    31,    96,
      97,    98,     0,     1,    34,    11,   103,    92,     3,     1,
       9,    35,     3,    45,     3,     9,    48,     8,    17,    10,
      13,    15,    54,    17,    15,    16,   123,    59,    11,    14,
       3,    38,   111,   130,   119,     8,   133,    28,   135,   136,
      38,    11,    74,   140,    36,    37,     5,    38,    11,     5,
     147,   148,   149,    22,    23,    24,     6,     6,    26,   138,
     157,    18,   159,     0,     1,    10,     3,     4,     5,     6,
       7,    11,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     5,    11,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     1,    10,     3,     4,     5,     6,
       7,     6,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     9,     6,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     1,    20,     3,     4,     5,     6,
      10,     6,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     5,    38,     6,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     1,   137,     3,     4,     5,   131,
       6,    54,    59,     1,    11,     3,     4,     5,    -1,   151,
     152,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   160,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,     1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     1,    -1,     3,    32,    33,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     1,
      -1,     3,    32,    33,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     1,    -1,     3,
      32,    33,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     1,    -1,     3,    32,    33,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    17,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    42,    43,    44,
      45,    46,    47,    55,    42,    31,     0,    44,    31,     1,
       3,    32,    33,    42,    49,    50,    53,    32,    33,    48,
      53,    57,    62,    32,    50,    34,    32,    62,     3,     8,
      10,    15,    16,    28,    38,    58,    51,    53,     3,    58,
      58,     3,    60,    58,    53,     5,    13,    14,    17,    19,
      25,    27,    35,    11,    11,    14,    11,    11,    55,    56,
      56,     5,    11,    13,    51,    54,    56,    56,    22,    23,
      24,    61,    56,    56,    56,     5,    56,     1,    36,    37,
      52,     6,    58,     9,    15,    17,    59,    26,     6,    51,
      10,    18,    56,    11,     5,    11,    10,    56,    61,    56,
       6,    56,    56,    59,    58,     6,    56,    20,    10,     6,
      56,    56,    56,    17,    59,    59,     5,     6,    56,     6,
      56,    59
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
        case 26:
#line 120 "./ddl-gram.y"
    { printf("{ "); }
    break;

  case 27:
#line 121 "./ddl-gram.y"
    { printf("} "); }
    break;

  case 28:
#line 122 "./ddl-gram.y"
    { printf(";\n"); }
    break;

  case 29:
#line 123 "./ddl-gram.y"
    { printf("%s ", (yyvsp[(1) - (1)].str)); }
    break;

  case 30:
#line 124 "./ddl-gram.y"
    { printf("%s ", (yyvsp[(1) - (1)].str)); }
    break;

  case 35:
#line 135 "./ddl-gram.y"
    { printf("\n"); }
    break;

  case 41:
#line 149 "./ddl-gram.y"
    {  printf("P2_typex(");
                 print_string_expr((yyvsp[(1) - (3)].node)); 
                 printf(", "); 
                 print_string_expr((yyvsp[(3) - (3)].node));
                 printf(", \"\");\n");
                 new_equation((yyvsp[(1) - (3)].node)->text, (yyvsp[(3) - (3)].node));
              }
    break;

  case 43:
#line 161 "./ddl-gram.y"
    { if (strcmp((yyvsp[(1) - (4)].node)->text, "conceptual") == 0)
                 (yyval.node) = decompose_conceptual((yyvsp[(3) - (4)].node));
             else
               (yyval.node) = new_list_head((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
           }
    break;

  case 44:
#line 168 "./ddl-gram.y"
    { /* nothing */ }
    break;

  case 45:
#line 169 "./ddl-gram.y"
    { warning(3, "Need a ]");  yyerrok; }
    break;

  case 46:
#line 173 "./ddl-gram.y"
    { (yyval.node) = new_node((yyvsp[(1) - (1)].str)); }
    break;

  case 47:
#line 174 "./ddl-gram.y"
    { (yyval.node) = new_node((yyvsp[(1) - (1)].str)); }
    break;

  case 48:
#line 175 "./ddl-gram.y"
    { warning(3, "Inappropriate name"); }
    break;

  case 49:
#line 179 "./ddl-gram.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 50:
#line 181 "./ddl-gram.y"
    { (yyval.node) = new_list_tail((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 54:
#line 188 "./ddl-gram.y"
    { strcpy((yyval.str), "="); }
    break;

  case 55:
#line 189 "./ddl-gram.y"
    { strcpy((yyval.str), ","); }
    break;

  case 56:
#line 190 "./ddl-gram.y"
    { strcpy((yyval.str), "["); }
    break;

  case 57:
#line 191 "./ddl-gram.y"
    { strcpy((yyval.str), "]"); }
    break;

  case 58:
#line 192 "./ddl-gram.y"
    { strcpy((yyval.str), "."); }
    break;

  case 59:
#line 193 "./ddl-gram.y"
    { strcpy((yyval.str), "("); }
    break;

  case 60:
#line 194 "./ddl-gram.y"
    { strcpy((yyval.str), ")"); }
    break;

  case 61:
#line 196 "./ddl-gram.y"
    { warning(3, "Reserved word used as expression");
               yyerrok;
             }
    break;

  case 62:
#line 202 "./ddl-gram.y"
    { (yyval.node) = new_node((yyvsp[(1) - (1)].str)); }
    break;

  case 63:
#line 203 "./ddl-gram.y"
    { (yyval.node) = new_list((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].node)); }
    break;

  case 64:
#line 206 "./ddl-gram.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 65:
#line 207 "./ddl-gram.y"
    { (yyval.node) = new_list_tail((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 66:
#line 210 "./ddl-gram.y"
    { strcpy((yyval.str), (yyvsp[(2) - (2)].str)); }
    break;

  case 68:
#line 212 "./ddl-gram.y"
    { strcpy((yyval.str), "P2_default"); }
    break;

  case 69:
#line 215 "./ddl-gram.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 70:
#line 216 "./ddl-gram.y"
    { (yyval.node) = new_node(""); }
    break;

  case 76:
#line 233 "./ddl-gram.y"
    { /* array */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (5)].str));
              print_path((yyvsp[(1) - (5)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (5)].node));
              printf(");\n");
            }
    break;

  case 77:
#line 241 "./ddl-gram.y"
    { /* cursor_structure, container_structure */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (3)].str));
              print_path((yyvsp[(1) - (3)].node));
              printf(", \"%s\", %s);\n", target_layer, (yyvsp[(3) - (3)].str));
            }
    break;

  case 78:
#line 247 "./ddl-gram.y"
    { /* mmap_persistent, mmap_shared */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (8)].str));
              print_path((yyvsp[(1) - (8)].node));
              printf(", \"%s\", %s,", target_layer, (yyvsp[(5) - (8)].str));
              print_expr((yyvsp[(8) - (8)].node));
              printf(");\n");
            }
    break;

  case 79:
#line 255 "./ddl-gram.y"
    { /* partitioning layers like part, parttwo */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (5)].str));
              print_path((yyvsp[(1) - (5)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (5)].node));
              printf(");\n");
            }
    break;

  case 80:
#line 263 "./ddl-gram.y"
    { /* key-ordering layers like bintree, odlist */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (5)].str));
              print_path((yyvsp[(1) - (5)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (5)].node));
              printf(");\n");
            }
    break;

  case 81:
#line 271 "./ddl-gram.y"
    { /* llist (and other leaps list layers?) */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (6)].str));
              print_path((yyvsp[(1) - (6)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (6)].node));
              printf(", ");
              print_expr((yyvsp[(6) - (6)].node));
              printf(");\n");
            }
    break;

  case 82:
#line 282 "./ddl-gram.y"
    { /* leaps list layers */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (12)].str));
              print_path((yyvsp[(1) - (12)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (12)].node));
              printf(", ");
              print_expr((yyvsp[(8) - (12)].node));
              printf(", ");
              print_expr((yyvsp[(11) - (12)].node));
              printf(", ");
              print_expr((yyvsp[(12) - (12)].node));
              printf(");\n");
            }
    break;

  case 83:
#line 296 "./ddl-gram.y"
    { /* hash, hash_array, qsort */
              /* hash, hash_array option hash_function. */
              /* qsort option "prinary" (key is unique)
                 or "secondary" (key is not necessarily unique). */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (9)].str));
              print_path((yyvsp[(1) - (9)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (9)].node));
              printf(", ");
              print_expr((yyvsp[(8) - (9)].node));
              printf(", ");
              print_expr((yyvsp[(9) - (9)].node));
              printf(");\n");
            }
    break;

  case 84:
#line 311 "./ddl-gram.y"
    { /* vtimestamp */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (8)].str));
              print_path((yyvsp[(1) - (8)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(5) - (8)].node));
              printf(", ");
              print_expr((yyvsp[(8) - (8)].node));
              printf(");\n");
            }
    break;

  case 85:
#line 321 "./ddl-gram.y"
    { printf("P2_ddlhint(%s, ", (yyvsp[(2) - (4)].str));
              print_path((yyvsp[(1) - (4)].node));
              printf(", \"hashcmp\", ");
              print_expr((yyvsp[(4) - (4)].node));
              printf(");\n");
            }
    break;

  case 86:
#line 328 "./ddl-gram.y"
    { printf("P2_ddlhint(%s, ", (yyvsp[(2) - (4)].str));
              print_path((yyvsp[(1) - (4)].node));
              printf(", \"%s\", ", target_layer);
              print_expr((yyvsp[(4) - (4)].node));
              printf(");\n");
            }
    break;

  case 87:
#line 335 "./ddl-gram.y"
    { /* predindx */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (4)].str));
              print_path((yyvsp[(1) - (4)].node));
              printf(", \"predindx\", %s", (yyvsp[(4) - (4)].str));
              printf(");\n");
            }
    break;

  case 88:
#line 343 "./ddl-gram.y"
    { /* lpredindx, tpredindx */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (12)].str));
              print_path((yyvsp[(1) - (12)].node));
              printf(", \"%s\"", target_layer);
              printf(", ");
              print_expr((yyvsp[(5) - (12)].node));
              printf(", %s", (yyvsp[(7) - (12)].str));
              printf(", ");
              print_expr((yyvsp[(9) - (12)].node));
              printf(", ");
              print_expr((yyvsp[(11) - (12)].node));
              printf(", ");
              print_expr((yyvsp[(12) - (12)].node));
              printf(");\n");
            }
    break;

  case 89:
#line 361 "./ddl-gram.y"
    { /* hpredindx */
              printf("P2_ddlhint(%s, ", (yyvsp[(3) - (18)].str));
              print_path((yyvsp[(1) - (18)].node));
              printf(", \"%s\"", target_layer);
              printf(", ");
              print_expr((yyvsp[(5) - (18)].node));
              printf(", ");
              print_expr((yyvsp[(8) - (18)].node));
              printf(", ");
              print_expr((yyvsp[(11) - (18)].node));
              printf(", %s, ", (yyvsp[(13) - (18)].str));
              print_expr((yyvsp[(15) - (18)].node));
              printf(", ");
              print_expr((yyvsp[(17) - (18)].node));
              printf(", ");
              print_expr((yyvsp[(18) - (18)].node));
              printf(");\n");
            }
    break;

  case 90:
#line 380 "./ddl-gram.y"
    { /* nloops */
              printf("P2_ddlhint(%s, ", (yyvsp[(2) - (3)].str));
              print_path((yyvsp[(1) - (3)].node));
              printf(", \"%s\", ", target_layer);
              printf("\"\"");
              printf(");\n");
            }
    break;

  case 91:
#line 390 "./ddl-gram.y"
    { /* nloops, ringlist */
              printf("P2_ddlhint(P2_default,");
              print_path((yyvsp[(1) - (11)].node));
              printf(", \"%s\", ", target_layer);
              printf("\"%s\", %s,", (yyvsp[(5) - (11)].str), (yyvsp[(6) - (11)].str));
              printf("\"%s\", %s,", (yyvsp[(8) - (11)].str), (yyvsp[(9) - (11)].str));
              print_expr((yyvsp[(11) - (11)].node));
              printf(");\n");
            }
    break;


/* Line 1267 of yacc.c.  */
#line 1981 "y.tab.c"
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


#line 404 "./ddl-gram.y"


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

