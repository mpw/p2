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




/* Copy the first part of user declarations.  */
#line 1 "./pb-gram.y"


/* $Id: pb-gram.y,v 45.0 1997/09/19 05:45:52 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/* pb grammar (bison source file). */

/*

Derived from a grammar by James A. Roskind (1990), version 1.0.  
Original comments are retained for documentation purposes (DSB).

PREDATOR additions by JAT.

*/

/*

This refined grammar resolves several typedef ambiguities  in  the
draft  proposed  ANSI  C  standard  syntax  down  to  1  shift/reduce
conflict, as reported by a YACC process.  Note  that  the  one  shift
reduce  conflict   is the traditional if-if-else conflict that is not
resolved by the grammar.  This ambiguity can  be  removed  using  the
method  described in the Dragon Book (2nd edition), but this does not
appear worth the effort.

There was quite a bit of effort made to reduce the conflicts to  this
level,  and  an  additional effort was made to make the grammar quite
similar to the C++ grammar being developed in  parallel.   Note  that
this grammar resolves the following ANSI C ambiguity as follows:

ANSI  C  section  3.5.6,  "If  the [typedef name] is redeclared at an
inner scope, the type specifiers shall not be omitted  in  the  inner
declaration".   Supplying type specifiers prevents consideration of T
as a typedef name in this grammar.  Failure to supply type specifiers
forced the use of the TYPEDEFname as a type specifier.

ANSI C section 3.5.4.3, "In a parameter declaration, a single typedef
name in parentheses is  taken  to  be  an  abstract  declarator  that
specifies  a  function  with  a  single  parameter,  not as redundant
parentheses around the identifier".  This is extended  to  cover  the
following cases:

typedef float T;
int noo(const (T[5]));
int moo(const (T(int)));
...

Where  again the '(' immediately to the left of 'T' is interpreted as
being the start of a parameter type list,  and  not  as  a  redundant
paren around a redeclaration of T.  Hence an equivalent code fragment
is:

typedef float T;
int noo(const int identifier1 (T identifier2 [5]));
int moo(const int identifier1 (T identifier2 (int identifier3)));
...

(James A. Roskind)

*/

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <string.h>       /* strcat() needed by yyparse() */

#include "compcurs.h"     /* pre_opt_compcurs_decl() */
#include "error.h"        /* parse_error() */
#include "io.h"           /* print_ptree(), print_liner_pragma */
#include "pb-actions.h"   /* identifier_expression_nonterm() */
#include "pb-io.h"        /* direction_string() */
#include "pb-type.h"      /* copy_ctype() */
#include "pb-xform.h"     /* FOREACH_MEMBER */
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* terminal() */

/*****************************************************************************/
/*                  Defines.                                                 */
/*****************************************************************************/

#define YYDEBUG 1                    /* Pretty debugging code. */
#define YYDEBUG_LEXER_TEXT (yylval)  /* Our lexer loads this up each time. */
#define YYERROR_VERBOSE 1 /* define as anything for verbose BISON errors. */
#define YYPRINT(file, type, value) \
     yyprint(file, type, value)

/*****************************************************************************/
/*                  Local forward references                                 */
/*****************************************************************************/

int  yylex(void);
void yyerror(char *s);

#if YYDEBUG
static void yyprint();
#endif



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
#line 174 "./pb-gram.y"
{
  NODE    *n;
  int      i;
}
/* Line 193 of yacc.c.  */
#line 433 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 446 "y.tab.c"

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
#define YYFINAL  143
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3835

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  422
/* YYNRULES -- Number of states.  */
#define YYNSTATES  733

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   368

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    14,    16,    19,
      21,    23,    27,    31,    35,    37,    42,    46,    51,    55,
      59,    62,    65,    67,    69,    71,    75,    77,    80,    83,
      86,    89,    90,    96,    98,   100,   102,   104,   106,   108,
     110,   111,   117,   119,   123,   127,   131,   133,   137,   141,
     143,   147,   151,   153,   157,   161,   165,   169,   171,   175,
     179,   181,   185,   187,   191,   193,   197,   199,   203,   205,
     209,   211,   217,   219,   223,   225,   227,   229,   231,   233,
     235,   237,   239,   241,   243,   245,   247,   251,   253,   254,
     256,   258,   262,   266,   269,   272,   276,   282,   285,   287,
     291,   292,   294,   296,   299,   314,   320,   326,   327,   335,
     341,   347,   348,   356,   358,   360,   362,   364,   366,   368,
     370,   373,   376,   378,   381,   383,   385,   387,   389,   392,
     395,   398,   401,   403,   406,   409,   412,   415,   418,   421,
     423,   426,   429,   432,   435,   438,   440,   443,   446,   448,
     450,   452,   454,   456,   458,   460,   462,   464,   466,   468,
     470,   472,   474,   476,   478,   481,   484,   489,   494,   499,
     500,   508,   513,   514,   524,   529,   530,   539,   544,   546,
     547,   548,   549,   560,   561,   562,   568,   569,   571,   574,
     579,   580,   583,   584,   587,   588,   592,   599,   600,   602,
     604,   606,   608,   609,   615,   616,   623,   626,   628,   630,
     632,   635,   638,   641,   644,   645,   650,   653,   654,   659,
     663,   665,   669,   671,   672,   674,   677,   678,   684,   685,
     692,   695,   698,   703,   704,   707,   709,   710,   715,   717,
     718,   723,   725,   728,   731,   734,   736,   739,   742,   744,
     747,   750,   753,   755,   758,   761,   763,   764,   769,   771,
     773,   775,   778,   780,   783,   784,   787,   791,   796,   798,
     800,   804,   806,   808,   810,   812,   814,   816,   818,   824,
     831,   832,   835,   840,   847,   848,   850,   852,   856,   858,
     863,   867,   870,   874,   877,   880,   886,   892,   899,   900,
     901,   903,   906,   908,   911,   914,   920,   928,   934,   940,
     948,   958,   964,   966,   968,   970,   974,   977,   980,   984,
     986,   988,   990,   993,   995,   997,  1000,  1003,  1004,  1008,
    1009,  1014,  1015,  1020,  1021,  1026,  1027,  1032,  1033,  1037,
    1038,  1043,  1044,  1049,  1050,  1055,  1056,  1061,  1062,  1067,
    1068,  1074,  1075,  1081,  1082,  1088,  1089,  1095,  1097,  1099,
    1101,  1103,  1105,  1108,  1110,  1112,  1115,  1119,  1123,  1128,
    1130,  1135,  1141,  1144,  1148,  1152,  1157,  1162,  1164,  1168,
    1170,  1172,  1173,  1178,  1179,  1186,  1188,  1192,  1194,  1196,
    1201,  1203,  1206,  1210,  1213,  1217,  1222,  1224,  1228,  1230,
    1233,  1237,  1242,  1246,  1251,  1253,  1255,  1257,  1259,  1262,
    1266,  1269,  1273,  1278,  1280,  1283,  1286,  1290,  1294,  1298,
    1302,  1307,  1309
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     231,     0,    -1,    88,    -1,    89,    -1,    90,    -1,    87,
      -1,   116,    87,    -1,    86,    -1,   101,    86,    -1,   115,
      -1,   116,    -1,    53,   139,    54,    -1,    53,   220,    54,
      -1,    53,     1,    54,    -1,   117,    -1,   118,    57,   139,
      58,    -1,   118,    53,    54,    -1,   118,    53,   120,    54,
      -1,   118,    36,   119,    -1,   118,    92,   119,    -1,   118,
      93,    -1,   118,    94,    -1,    86,    -1,    91,    -1,   137,
      -1,   120,    35,   137,    -1,   118,    -1,    93,   121,    -1,
      94,   121,    -1,   123,   124,    -1,    29,   121,    -1,    -1,
      29,    53,   122,   209,    54,    -1,    41,    -1,    37,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,   121,    -1,
      -1,    53,   125,   209,    54,   124,    -1,   124,    -1,   126,
      37,   124,    -1,   126,    46,   124,    -1,   126,    47,   124,
      -1,   126,    -1,   127,    42,   126,    -1,   127,    43,   126,
      -1,   127,    -1,   128,    95,   127,    -1,   128,    96,   127,
      -1,   128,    -1,   129,    48,   128,    -1,   129,    49,   128,
      -1,   129,    97,   128,    -1,   129,    98,   128,    -1,   129,
      -1,   130,    99,   129,    -1,   130,   100,   129,    -1,   130,
      -1,   131,    41,   130,    -1,   131,    -1,   132,    50,   131,
      -1,   132,    -1,   133,    51,   132,    -1,   133,    -1,   134,
     101,   133,    -1,   134,    -1,   135,   102,   134,    -1,   135,
      -1,   135,    52,   139,    38,   136,    -1,   136,    -1,   121,
     138,   137,    -1,    40,    -1,   104,    -1,   105,    -1,   106,
      -1,   107,    -1,   108,    -1,   109,    -1,   110,    -1,   111,
      -1,   112,    -1,   113,    -1,   137,    -1,   139,    35,   137,
      -1,   136,    -1,    -1,   139,    -1,   143,    -1,   160,   259,
      39,    -1,   161,   259,    39,    -1,   150,    39,    -1,   148,
      39,    -1,    83,   144,    39,    -1,    79,    53,   120,    54,
      39,    -1,   169,    39,    -1,    86,    -1,   144,    35,    86,
      -1,    -1,   146,    -1,   147,    -1,   146,   147,    -1,    77,
      53,    86,    35,    78,    53,   120,    54,    35,   116,    35,
     120,    54,    39,    -1,   154,   257,   258,   259,   210,    -1,
     155,   257,   258,   259,   210,    -1,    -1,   148,    35,   149,
     257,   258,   259,   210,    -1,   152,   249,   258,   259,   210,
      -1,   153,   249,   258,   259,   210,    -1,    -1,   150,    35,
     151,   249,   258,   259,   210,    -1,   158,    -1,   160,    -1,
     162,    -1,   159,    -1,   161,    -1,   163,    -1,   164,    -1,
     155,   164,    -1,   154,   156,    -1,   157,    -1,   155,   157,
      -1,   164,    -1,   157,    -1,    19,    -1,    30,    -1,   154,
     165,    -1,   159,   164,    -1,   158,   156,    -1,   158,   165,
      -1,   165,    -1,   155,   165,    -1,   159,   157,    -1,   159,
     165,    -1,   154,   181,    -1,   161,   164,    -1,   160,   156,
      -1,   181,    -1,   155,   181,    -1,   161,   157,    -1,   163,
     164,    -1,   154,    91,    -1,   162,   156,    -1,    91,    -1,
     155,    91,    -1,   163,   157,    -1,    14,    -1,    16,    -1,
      33,    -1,     3,    -1,    13,    -1,    82,    -1,     5,    -1,
      15,    -1,    59,    -1,    21,    -1,    20,    -1,     4,    -1,
      25,    -1,    22,    -1,    26,    -1,     9,    -1,     9,     9,
      -1,     9,     4,    -1,    84,    53,   121,    54,    -1,    84,
      53,   209,    54,    -1,    73,    48,   121,    49,    -1,    -1,
      60,    48,   121,    49,   166,   177,   179,    -1,    61,    48,
     153,    49,    -1,    -1,    74,    48,   175,    49,   167,   173,
     177,   178,   179,    -1,    62,    48,   153,    49,    -1,    -1,
      62,    48,   153,    49,    65,    86,   168,   145,    -1,    63,
      48,   153,    49,    -1,   169,    -1,    -1,    -1,    -1,    64,
      55,   170,   186,    56,   171,    65,    86,   172,   145,    -1,
      -1,    -1,    75,    48,   174,   206,    49,    -1,    -1,   176,
      -1,    86,   121,    -1,    86,   121,    35,   176,    -1,    -1,
      66,   116,    -1,    -1,    76,   116,    -1,    -1,    72,   180,
      86,    -1,    72,   180,    80,    86,    36,    86,    -1,    -1,
      70,    -1,    71,    -1,   182,    -1,   196,    -1,    -1,   185,
      55,   183,   186,    56,    -1,    -1,   185,   208,    55,   184,
     186,    56,    -1,   185,   208,    -1,     6,    -1,    18,    -1,
     187,    -1,   186,   187,    -1,   190,    39,    -1,   188,    39,
      -1,   155,   193,    -1,    -1,   188,    35,   189,   193,    -1,
     153,   192,    -1,    -1,   190,    35,   191,   192,    -1,   249,
     259,   194,    -1,   195,    -1,   257,   259,   194,    -1,   195,
      -1,    -1,   195,    -1,    38,   140,    -1,    -1,    12,    55,
     197,   199,    56,    -1,    -1,    12,   208,    55,   198,   199,
      56,    -1,    12,   208,    -1,   208,   200,    -1,   199,    35,
     208,   200,    -1,    -1,    40,   140,    -1,   203,    -1,    -1,
     203,    35,   202,   103,    -1,   205,    -1,    -1,   203,    35,
     204,   205,    -1,   152,    -1,   152,   267,    -1,   152,   257,
      -1,   152,   251,    -1,   154,    -1,   154,   267,    -1,   154,
     257,    -1,   153,    -1,   153,   267,    -1,   153,   257,    -1,
     153,   251,    -1,   155,    -1,   155,   267,    -1,   155,   257,
      -1,    86,    -1,    -1,   206,    35,   207,    86,    -1,    86,
      -1,    91,    -1,   153,    -1,   153,   267,    -1,   155,    -1,
     155,   267,    -1,    -1,    40,   211,    -1,    55,   212,    56,
      -1,    55,   212,    35,    56,    -1,   137,    -1,   211,    -1,
     212,    35,   211,    -1,   219,    -1,   220,    -1,   225,    -1,
     226,    -1,   227,    -1,   229,    -1,   214,    -1,    85,    53,
     116,   215,    54,    -1,    85,    30,    53,   116,   215,    54,
      -1,    -1,    38,   216,    -1,    38,   216,    38,   216,    -1,
      38,   216,    38,   216,    38,   216,    -1,    -1,   217,    -1,
     218,    -1,   217,    35,   218,    -1,   116,    -1,   116,    53,
     139,    54,    -1,    53,   139,    54,    -1,   208,    38,    -1,
      11,   140,    38,    -1,    27,    38,    -1,    55,    56,    -1,
      55,   221,   223,   222,    56,    -1,    55,   221,   224,   222,
      56,    -1,    55,   221,   223,   224,   222,    56,    -1,    -1,
      -1,   142,    -1,   223,   142,    -1,   213,    -1,   224,   213,
      -1,   141,    39,    -1,    32,    53,   139,    54,   213,    -1,
      32,    53,   139,    54,   213,     8,   213,    -1,    10,    53,
     139,    54,   213,    -1,    34,    53,   139,    54,   213,    -1,
      31,   213,    34,    53,   139,    54,    39,    -1,    24,    53,
     141,    39,   141,    39,   141,    54,   213,    -1,   228,    53,
     137,    54,   213,    -1,    67,    -1,    68,    -1,    69,    -1,
      28,   230,    39,    -1,    23,    39,    -1,     7,    39,    -1,
      17,   141,    39,    -1,   139,    -1,    91,    -1,   232,    -1,
     231,   232,    -1,   233,    -1,   142,    -1,     1,    39,    -1,
       1,    56,    -1,    -1,   257,   234,   220,    -1,    -1,   152,
     257,   235,   220,    -1,    -1,   153,   257,   236,   220,    -1,
      -1,   154,   257,   237,   220,    -1,    -1,   155,   257,   238,
     220,    -1,    -1,   265,   239,   220,    -1,    -1,   152,   265,
     240,   220,    -1,    -1,   153,   265,   241,   220,    -1,    -1,
     154,   265,   242,   220,    -1,    -1,   155,   265,   243,   220,
      -1,    -1,   265,   244,   223,   220,    -1,    -1,   152,   265,
     245,   223,   220,    -1,    -1,   153,   265,   246,   223,   220,
      -1,    -1,   154,   265,   247,   223,   220,    -1,    -1,   155,
     265,   248,   223,   220,    -1,   257,    -1,   250,    -1,   254,
      -1,   251,    -1,    91,    -1,    91,   268,    -1,   252,    -1,
     253,    -1,    37,   251,    -1,    37,   155,   251,    -1,   272,
     252,   273,    -1,   272,   252,   273,   268,    -1,   255,    -1,
      37,   272,   256,   273,    -1,    37,   155,   272,   256,   273,
      -1,    37,   254,    -1,    37,   155,   254,    -1,   272,   254,
     273,    -1,   272,   256,   268,   273,    -1,   272,   254,   273,
     268,    -1,    91,    -1,   272,   256,   273,    -1,   262,    -1,
     264,    -1,    -1,    85,    53,   116,    54,    -1,    -1,    81,
      53,    53,   260,    54,    54,    -1,   261,    -1,   260,    35,
     261,    -1,    19,    -1,    86,    -1,    86,    53,   120,    54,
      -1,   263,    -1,    37,   257,    -1,    37,   155,   257,    -1,
     264,   268,    -1,   272,   262,   273,    -1,   272,   262,   273,
     268,    -1,    86,    -1,   272,   264,   273,    -1,   266,    -1,
      37,   265,    -1,    37,   155,   265,    -1,   264,   272,   206,
     273,    -1,   272,   265,   273,    -1,   272,   265,   273,   268,
      -1,   270,    -1,   271,    -1,   268,    -1,   269,    -1,   272,
     273,    -1,   272,   201,   273,    -1,    57,    58,    -1,    57,
     140,    58,    -1,   269,    57,   140,    58,    -1,    37,    -1,
      37,   155,    -1,    37,   267,    -1,    37,   155,   267,    -1,
     272,   270,   273,    -1,   272,   271,   273,    -1,   272,   268,
     273,    -1,   272,   270,   273,   268,    -1,    53,    -1,    54,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   297,   297,   298,   299,   303,   304,   315,   319,   322,
     323,   324,   328,   336,   345,   346,   351,   356,   359,   362,
     365,   369,   376,   384,   395,   396,   402,   403,   408,   413,
     416,   420,   419,   429,   430,   431,   432,   433,   434,   442,
     444,   443,   452,   453,   456,   459,   465,   466,   469,   475,
     476,   479,   486,   487,   489,   491,   493,   498,   499,   502,
     508,   509,   515,   516,   522,   523,   529,   530,   536,   537,
     543,   544,   559,   560,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   580,   581,   587,   594,   596,
     634,   695,   696,   697,   698,   702,   709,   715,   726,   730,
     741,   743,   747,   748,   753,   766,   770,   775,   774,   784,
     788,   793,   792,   805,   806,   807,   811,   812,   813,   817,
     818,   821,   827,   828,   834,   835,   839,   840,   844,   847,
     850,   853,   859,   860,   863,   866,   872,   875,   878,   884,
     885,   888,   895,   898,   912,   918,   932,   948,   954,   960,
     966,   972,   978,   984,   990,   991,   992,   993,   994,   995,
     996,   997,   998,  1003,  1004,  1008,  1019,  1028,  1037,  1045,
    1044,  1054,  1060,  1059,  1070,  1077,  1075,  1086,  1093,  1098,
    1101,  1104,  1097,  1120,  1123,  1122,  1133,  1135,  1139,  1142,
    1149,  1152,  1160,  1162,  1169,  1172,  1178,  1188,  1197,  1200,
    1206,  1207,  1212,  1211,  1220,  1219,  1227,  1236,  1244,  1257,
    1258,  1264,  1269,  1277,  1281,  1280,  1290,  1294,  1293,  1303,
    1306,  1310,  1313,  1318,  1320,  1324,  1332,  1331,  1343,  1342,
    1352,  1360,  1367,  1378,  1380,  1386,  1388,  1387,  1397,  1399,
    1398,  1412,  1413,  1416,  1419,  1422,  1423,  1426,  1429,  1430,
    1433,  1436,  1439,  1440,  1443,  1453,  1458,  1457,  1469,  1472,
    1478,  1479,  1482,  1483,  1490,  1492,  1499,  1501,  1503,  1507,
    1508,  1518,  1519,  1520,  1521,  1522,  1523,  1524,  1528,  1531,
    1538,  1540,  1543,  1546,  1553,  1555,  1559,  1560,  1566,  1567,
    1570,  1582,  1586,  1588,  1597,  1599,  1601,  1605,  1613,  1621,
    1627,  1628,  1634,  1635,  1642,  1649,  1653,  1658,  1665,  1669,
    1673,  1678,  1685,  1686,  1687,  1691,  1700,  1703,  1706,  1712,
    1713,  1721,  1722,  1728,  1735,  1741,  1745,  1756,  1755,  1763,
    1762,  1770,  1769,  1777,  1776,  1784,  1783,  1794,  1793,  1801,
    1800,  1808,  1807,  1815,  1814,  1822,  1821,  1832,  1831,  1839,
    1838,  1846,  1845,  1853,  1852,  1860,  1859,  1869,  1872,  1878,
    1879,  1883,  1887,  1892,  1899,  1900,  1904,  1913,  1916,  1926,
    1927,  1932,  1940,  1944,  1953,  1956,  1961,  1968,  1984,  1990,
    1991,  1996,  1998,  2005,  2007,  2014,  2015,  2021,  2022,  2023,
    2029,  2030,  2034,  2043,  2046,  2049,  2056,  2065,  2071,  2072,
    2076,  2085,  2089,  2092,  2099,  2100,  2101,  2105,  2106,  2110,
    2117,  2121,  2125,  2132,  2135,  2141,  2145,  2154,  2158,  2162,
    2166,  2174,  2180
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTO", "DOUBLE", "INT", "STRUCT",
  "BREAK", "ELSE", "LONG", "SWITCH", "CASE", "ENUM", "REGISTER", "TYPEDEF",
  "CHAR", "EXTERN", "RETURN", "UNION", "CONST", "FLOAT", "SHORT",
  "UNSIGNED", "CONTINUE", "FOR", "SIGNED", "VOID", "DEFAULT", "GOTO",
  "SIZEOF", "VOLATILE", "DO", "IF", "STATIC", "WHILE", "COMMA", "DOT",
  "STAR", "COLON", "SEMICOLON", "ASSIGN", "AND", "PLUS", "MINUS", "NEGATE",
  "NOT", "DIV", "MOD", "LT", "GT", "XOR", "PIPE", "QUESTION", "LP", "RP",
  "LC", "RC", "LB", "RB", "VARCHAR", "CURSOR", "GENERIC_CURSOR",
  "CONTAINER", "GENERIC_CONTAINER", "SCHEMA", "STORED_AS", "WHERE",
  "FOREACH", "FOREACHK", "ROFEACH", "ASCENDING", "DESCENDING", "ORDERBY",
  "ELEMENT", "COMPCURS", "GIVEN", "VALID", "P2_DDLHINT", "P2_PATH",
  "P2_TYPEX", "DOLLAR", "ATTRIBUTE", "INLINE", "LABEL", "TYPEOF", "ASM",
  "IDENTIFIER", "STRINGliteral", "FLOATINGconstant", "INTEGERconstant",
  "CHARACTERconstant", "TYPEDEFname", "ARROW", "INCR", "DECR", "LS", "RS",
  "LE", "GE", "EQ", "NE", "ANDAND", "OROR", "ELLIPSIS", "MULTassign",
  "DIVassign", "MODassign", "PLUSassign", "MINUSassign", "LSassign",
  "RSassign", "ANDassign", "ERassign", "ORassign", "$accept", "constant",
  "string_literal_list", "primary_expression", "postfix_expression",
  "member_name", "argument_expression_list", "unary_expression", "@1",
  "unary_operator", "cast_expression", "@2", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "AND_expression", "exclusive_OR_expression",
  "inclusive_OR_expression", "logical_AND_expression",
  "logical_OR_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "comma_expression",
  "constant_expression", "comma_expression_opt", "declaration",
  "declaration1", "label_list", "ddlhint_list_opt", "ddlhint_list",
  "ddlhint", "default_declaring_list", "@3", "declaring_list", "@4",
  "declaration_specifier", "type_specifier", "declaration_qualifier_list",
  "type_qualifier_list", "declaration_qualifier", "type_qualifier",
  "basic_declaration_specifier", "basic_type_specifier",
  "sue_declaration_specifier", "sue_type_specifier",
  "typedef_declaration_specifier", "typedef_type_specifier",
  "storage_class", "basic_type_name", "@5", "@6", "@7", "schema_type",
  "@8", "@9", "@10", "given_opt", "@11", "cursor_container_pair_list_opt",
  "cursor_container_pair_list", "predicate_opt", "valid_opt",
  "orderby_opt", "direction", "elaborated_type_name", "aggregate_name",
  "@12", "@13", "aggregate_key", "member_declaration_list",
  "member_declaration", "member_default_declaring_list", "@14",
  "member_declaring_list", "@15", "member_declarator",
  "member_identifier_declarator", "bit_field_size_opt", "bit_field_size",
  "enum_name", "@16", "@17", "enumerator_list", "enumerator_value_opt",
  "parameter_type_list", "@18", "parameter_list", "@19",
  "parameter_declaration", "identifier_list", "@20",
  "identifier_or_typedef_name", "type_name", "initializer_opt",
  "initializer", "initializer_list", "statement", "asm_statement",
  "asm_op_desc_opt", "asm_op_list_opt", "asm_op_list", "asm_op",
  "labeled_statement", "compound_statement", "left_brace", "right_brace",
  "declaration_list", "statement_list", "expression_statement",
  "selection_statement", "iteration_statement", "foreach_or_rofeach",
  "jump_statement", "comma_expression_or_typedef_name", "translation_unit",
  "external_definition", "function_definition", "@21", "@22", "@23", "@24",
  "@25", "@26", "@27", "@28", "@29", "@30", "@31", "@32", "@33", "@34",
  "@35", "declarator", "typedef_declarator",
  "parameter_typedef_declarator", "clean_typedef_declarator",
  "clean_postfix_typedef_declarator", "paren_typedef_declarator",
  "paren_postfix_typedef_declarator", "simple_paren_typedef_declarator",
  "identifier_declarator", "asm_name_opt", "attribute_opt",
  "attribute_list", "attribute", "unary_identifier_declarator",
  "postfix_identifier_declarator", "paren_identifier_declarator",
  "old_function_declarator", "postfix_old_function_declarator",
  "abstract_declarator", "postfixing_abstract_declarator",
  "array_abstract_declarator", "unary_abstract_declarator",
  "postfix_abstract_declarator", "left_paren", "right_paren", 0
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
     365,   366,   367,   368
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   114,   115,   115,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   122,   121,   123,   123,   123,   123,   123,   123,   124,
     125,   124,   126,   126,   126,   126,   127,   127,   127,   128,
     128,   128,   129,   129,   129,   129,   129,   130,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   139,   139,   140,   141,   141,
     142,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     145,   145,   146,   146,   147,   148,   148,   149,   148,   150,
     150,   151,   150,   152,   152,   152,   153,   153,   153,   154,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     158,   158,   159,   159,   159,   159,   160,   160,   160,   161,
     161,   161,   162,   162,   162,   163,   163,   163,   164,   164,
     164,   164,   164,   164,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     165,   165,   167,   165,   165,   168,   165,   165,   165,   170,
     171,   172,   169,   173,   174,   173,   175,   175,   176,   176,
     177,   177,   178,   178,   179,   179,   179,   180,   180,   180,
     181,   181,   183,   182,   184,   182,   182,   185,   185,   186,
     186,   187,   187,   188,   189,   188,   190,   191,   190,   192,
     192,   193,   193,   194,   194,   195,   197,   196,   198,   196,
     196,   199,   199,   200,   200,   201,   202,   201,   203,   204,
     203,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   206,   207,   206,   208,   208,
     209,   209,   209,   209,   210,   210,   211,   211,   211,   212,
     212,   213,   213,   213,   213,   213,   213,   213,   214,   214,
     215,   215,   215,   215,   216,   216,   217,   217,   218,   218,
     218,   219,   219,   219,   220,   220,   220,   220,   221,   222,
     223,   223,   224,   224,   225,   226,   226,   226,   227,   227,
     227,   227,   228,   228,   228,   229,   229,   229,   229,   230,
     230,   231,   231,   232,   232,   232,   232,   234,   233,   235,
     233,   236,   233,   237,   233,   238,   233,   239,   233,   240,
     233,   241,   233,   242,   233,   243,   233,   244,   233,   245,
     233,   246,   233,   247,   233,   248,   233,   249,   249,   250,
     250,   251,   251,   251,   252,   252,   252,   253,   253,   254,
     254,   254,   254,   254,   255,   255,   255,   256,   256,   257,
     257,   258,   258,   259,   259,   260,   260,   261,   261,   261,
     262,   262,   262,   263,   263,   263,   264,   264,   265,   265,
     265,   266,   266,   266,   267,   267,   267,   268,   268,   268,
     269,   269,   269,   270,   270,   270,   270,   271,   271,   271,
     271,   272,   273
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     3,     3,     3,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     1,     1,     3,     1,     2,     2,     2,
       2,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       0,     5,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     1,
       1,     3,     3,     2,     2,     3,     5,     2,     1,     3,
       0,     1,     1,     2,    14,     5,     5,     0,     7,     5,
       5,     0,     7,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     2,     1,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     4,     4,     0,
       7,     4,     0,     9,     4,     0,     8,     4,     1,     0,
       0,     0,    10,     0,     0,     5,     0,     1,     2,     4,
       0,     2,     0,     2,     0,     3,     6,     0,     1,     1,
       1,     1,     0,     5,     0,     6,     2,     1,     1,     1,
       2,     2,     2,     2,     0,     4,     2,     0,     4,     3,
       1,     3,     1,     0,     1,     2,     0,     5,     0,     6,
       2,     2,     4,     0,     2,     1,     0,     4,     1,     0,
       4,     1,     2,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     1,     2,     2,     1,     0,     4,     1,     1,
       1,     2,     1,     2,     0,     2,     3,     4,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     5,     6,
       0,     2,     4,     6,     0,     1,     1,     3,     1,     4,
       3,     2,     3,     2,     2,     5,     5,     6,     0,     0,
       1,     2,     1,     2,     2,     5,     7,     5,     5,     7,
       9,     5,     1,     1,     1,     3,     2,     2,     3,     1,
       1,     1,     2,     1,     1,     2,     2,     0,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       5,     0,     5,     0,     5,     0,     5,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     3,     3,     4,     1,
       4,     5,     2,     3,     3,     4,     4,     1,     3,     1,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     4,
       1,     2,     3,     2,     3,     4,     1,     3,     1,     2,
       3,     4,     3,     4,     1,     1,     1,     1,     2,     3,
       2,     3,     4,     1,     2,     2,     3,     3,     3,     3,
       4,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   151,   159,   154,   207,   163,     0,   152,   148,
     155,   149,   208,   126,   158,   157,   161,   160,   162,   127,
     150,     0,   421,   156,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   396,   145,   324,    90,     0,
       0,     0,     0,     0,     0,   122,   113,   116,   114,   117,
     115,   118,   119,   132,   178,   139,   200,     0,   201,     0,
     321,   323,   327,   379,   390,   380,   347,   398,     0,   325,
     326,   165,   164,   226,   258,   259,   230,     0,   391,   399,
       0,     0,     0,     0,   179,     0,   186,     0,    98,     0,
       0,   107,    94,   111,    93,     0,   361,   381,   358,   360,
     363,   364,   359,   369,   357,   349,     0,   381,   357,   351,
     143,   121,   125,   124,   128,   178,   136,   381,   353,   146,
     123,   120,   133,   140,   381,   355,   130,   131,   134,   129,
     135,     0,   138,     0,   141,   137,     0,   144,   147,   142,
      97,   202,   206,     1,   322,     0,     0,   393,   407,     0,
       0,     0,     0,     0,     0,     0,   228,   392,   400,     0,
      34,    33,    35,    36,    37,    38,     0,     7,     5,     2,
       3,     4,     0,     0,     0,     9,    10,    14,    26,     0,
       0,     0,     0,   116,   117,   118,     0,     0,     0,     0,
       0,     0,   187,     0,     0,    39,    42,    46,    49,    52,
      57,    60,    62,    64,    66,    68,    70,    72,    24,     0,
      95,     0,   260,   262,     0,     0,     0,     0,   365,   372,
       0,   362,     0,     0,   383,     0,     0,     0,   377,     0,
       0,     0,     0,   383,     0,     0,     0,     0,   383,     0,
       0,     0,   383,     0,     0,     0,    91,    92,     0,   204,
     298,   328,   410,    39,    87,     0,     0,   422,   255,   241,
     248,   245,   252,   114,   117,     0,   235,   238,     0,   408,
     338,   300,     0,     0,     0,     0,     0,   394,   397,   402,
       0,   233,     0,     0,    30,     0,    85,     0,     0,    27,
      28,     8,     6,     0,     0,     0,     0,    20,    21,   169,
      29,   171,   174,   177,     0,     0,     0,   209,     0,     0,
     168,   188,   172,     0,     0,     0,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   166,   413,
     261,   406,   404,   405,     0,   263,   167,     0,   381,   380,
       0,     0,   381,   357,     0,   366,   373,     0,     0,     0,
     264,   330,   340,     0,   367,   374,     0,     0,   264,   332,
     342,     0,   334,   264,   344,     0,   336,   264,   346,     0,
       0,     0,     0,   294,    88,   411,     0,   413,   244,   243,
     242,     0,   251,   250,   249,   413,   247,   246,     0,   254,
     253,   409,   239,   256,   401,   381,   381,   301,   348,   395,
     403,     0,   227,     0,   231,     0,     0,    13,     0,    11,
      12,    22,    23,    18,    16,     0,     0,    19,   190,     0,
       0,   216,   220,   383,   213,   222,   383,   180,   210,   214,
     212,   217,   211,     0,   183,     0,    25,    96,    73,    43,
      44,    45,    47,    48,    50,    51,    53,    54,    55,    56,
      58,    59,    61,    63,    65,    67,     0,    69,   414,   415,
       0,     0,     0,     0,   383,     0,     0,     0,   383,     0,
       0,   370,     0,     0,   109,   350,   368,   376,   375,   378,
     110,   352,   105,   354,   106,   356,   387,   388,     0,   385,
     203,     0,     0,     0,     0,    88,     0,     0,     0,     0,
      88,     0,     0,   312,   313,   314,     0,     7,   145,    89,
       0,     0,   302,   277,   271,   272,    88,    88,   273,   274,
     275,     0,   276,   412,   414,   414,     0,     0,     0,   233,
     234,   229,     0,    86,    17,    15,     0,   194,   175,   225,
     223,   223,     0,     0,     0,   189,     0,   190,     0,     0,
     416,   419,   417,   418,   264,     0,   264,   371,   382,     0,
     268,   265,     0,     0,     0,   205,   317,     0,     0,     0,
     316,    88,   293,   320,   319,     0,     0,     0,     0,     0,
       0,   304,   291,     0,    88,   303,     0,     0,   237,   240,
     257,   232,    32,   191,   197,   170,   100,   219,   224,   221,
       0,   215,   218,   184,   192,    41,    71,   420,   108,   112,
     269,     0,     0,   386,   384,     0,   292,   318,     0,   315,
       0,     0,     0,     0,   280,   295,     0,   296,     0,   198,
     199,     0,     0,   176,   101,   102,   181,     0,     0,   194,
       0,   266,   389,    88,    88,     0,    88,    88,   280,   284,
       0,   297,    88,     0,   195,     0,   103,   100,     0,   193,
     173,   267,   270,   307,     0,     0,   305,   308,     0,     0,
     288,   281,   285,   286,   278,   311,     0,     0,   182,   185,
      88,     0,    88,   279,     0,     0,   284,     0,     0,     0,
       0,   309,   306,   290,     0,   282,   287,   196,     0,    88,
     289,   284,     0,   310,   283,     0,     0,     0,     0,     0,
       0,     0,   104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   175,   176,   177,   178,   433,   194,   195,   426,   180,
     196,   313,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   286,   327,   529,   255,   530,   271,    38,
      89,   653,   654,   655,    39,   215,    40,   216,   272,   273,
     274,   275,   111,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   438,   454,   616,   115,   188,   562,   677,   567,
     657,   191,   192,   557,   659,   615,   651,    55,    56,   248,
     392,    57,   306,   307,   308,   563,   309,   564,   441,   444,
     617,   442,    58,   155,   282,   280,   424,   265,   546,   266,
     547,   267,   268,   548,   531,   214,   494,   581,   631,   532,
     533,   670,   691,   692,   693,   534,   535,   394,   603,   276,
     537,   538,   539,   540,   541,   542,   595,    59,    60,    61,
     145,   225,   234,   237,   241,   150,   226,   235,   239,   243,
     151,   227,   236,   240,   244,    97,    98,    99,   100,   101,
     230,   103,   231,    78,   238,   133,   508,   509,    63,    64,
     359,   154,    67,   479,   351,   148,   352,   353,   222,   269
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -551
static const yytype_int16 yypact[] =
{
    1790,   118,  -551,  -551,  -551,  -551,   318,   248,  -551,  -551,
    -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,
    -551,    85,  -551,  -551,    -9,     0,    10,    37,   108,   124,
     131,   132,  -551,   142,   139,  -551,  -551,  -551,  -551,   382,
     393,   109,   109,  2284,  2368,  -551,  3538,  3538,   880,   880,
     733,   733,  -551,  -551,   199,  -551,  -551,   282,  -551,  1706,
    -551,  -551,  -551,  -551,  -551,   396,   205,  -551,    59,  -551,
    -551,  -551,  -551,  -551,  -551,  -551,   211,    85,  -551,  -551,
    3696,  3397,  3397,  3397,  -551,  3696,   187,  3714,  -551,   451,
    1437,  -551,  -551,  -551,  -551,   545,   396,   197,  -551,  -551,
    -551,  -551,  -551,  -551,   243,   277,   157,   197,   336,   345,
    -551,  -551,  -551,  -551,  -551,  -551,  -551,    17,   370,  -551,
    -551,  -551,  -551,  -551,    71,   372,  -551,  -551,  -551,  -551,
    -551,   329,  -551,   398,  -551,  -551,   415,  -551,  -551,  -551,
    -551,  -551,   410,  -551,  -551,   484,   962,  -551,   402,  2703,
     484,  2787,   464,   503,   464,   263,  -551,  -551,  -551,  3734,
    -551,  -551,  -551,  -551,  -551,  -551,   894,  -551,  -551,  -551,
    -551,  -551,  3696,  3696,   459,  -551,   465,  -551,   404,   514,
    3714,   529,  3471,  3565,   135,   135,   547,   553,  3397,   556,
    3696,   567,  -551,  1069,    -5,   919,  -551,   482,   188,   228,
     193,   481,   578,   558,   583,   536,    -2,  -551,  -551,   584,
    -551,   599,   430,  3101,   610,   167,   378,   545,  -551,  -551,
     157,  -551,  2870,   616,   592,   484,   484,  2787,  -551,   464,
     464,   396,   157,   592,   484,   484,  2787,   484,   592,   484,
    2787,   484,   592,   484,  2787,   622,  -551,  -551,  3397,  -551,
     623,  -551,  -551,  -551,  -551,   624,  3714,  -551,  -551,    87,
      87,  2042,  2126,   733,   733,   464,   645,  -551,    22,  -551,
    -551,  -551,   378,   378,  2452,  2536,  2620,   396,  -551,   396,
     236,   643,   263,  1160,  -551,   627,  -551,    39,   642,  -551,
    -551,  -551,  -551,   302,  3603,  3714,   302,  -551,  -551,  -551,
    -551,  -551,   636,  -551,   130,  3018,  3175,  -551,   560,   582,
    -551,   669,  -551,  3397,  3714,   666,  -551,  -551,  -551,  -551,
    -551,  -551,  -551,  -551,  -551,  -551,  -551,  3714,  3714,  3714,
    3714,  3714,  3714,  3714,  3714,  3714,  3714,  3714,  3714,  3714,
    3714,  3714,  3714,  3714,  3714,  3714,  3714,  -551,  -551,   289,
    -551,  -551,  -551,  -551,  2210,  -551,  -551,   641,   197,   396,
     167,   635,   197,  -551,   463,  -551,  -551,   157,   503,   619,
     667,  -551,  -551,  2620,   396,   396,   464,   503,   667,  -551,
    -551,  2620,  -551,   667,  -551,  2620,  -551,   667,  -551,  2620,
      23,  3249,  3397,  -551,  1346,  -551,   651,    95,  -551,  -551,
    -551,  1874,  -551,  -551,  -551,   609,  -551,  -551,  1958,  -551,
    -551,  -551,   607,  -551,  -551,   197,   197,  -551,  -551,  -551,
    -551,   263,  -551,  3714,  -551,   249,  3397,  -551,  3714,  -551,
    -551,  -551,  -551,  -551,  -551,   317,   106,  -551,   648,   629,
    3714,  -551,  -551,   592,  -551,  -551,   592,  -551,  -551,  -551,
    -551,  -551,  -551,   187,   644,   662,  -551,  -551,  -551,  -551,
    -551,  -551,   482,   482,   188,   188,   228,   228,   228,   228,
     193,   193,   481,   578,   558,   583,   312,   536,   289,  -551,
     464,   464,   464,   641,   592,   503,   635,   463,   592,   463,
     503,  -551,   -22,  3621,  -551,  -551,  -551,  -551,  -551,  -551,
    -551,  -551,  -551,  -551,  -551,  -551,  -551,   665,   360,  -551,
    -551,  3323,   681,   670,  3714,  3714,   692,   677,   694,  3641,
    1607,   682,   685,  -551,  -551,  -551,   183,   702,   703,   707,
     705,   710,  -551,  -551,  -551,  -551,  1253,  1522,  -551,  -551,
    -551,   697,  -551,  -551,    95,   609,   650,  2944,   671,   643,
    -551,  -551,   701,  -551,  -551,  -551,   619,   679,  -551,  -551,
     718,   718,   693,   230,   130,  -551,   712,   648,  3714,  3714,
    -551,  -551,   396,  -551,   667,   463,   667,  -551,  -551,  3621,
    -551,  -551,  3714,    23,   711,  -551,  -551,  3714,   726,   728,
    -551,  3714,  -551,  -551,   707,   729,   735,  3714,  3714,   734,
     619,  -551,  -551,   737,  1522,  -551,   738,  3714,  -551,  -551,
    -551,  -551,  -551,   465,   559,  -551,   713,  -551,  -551,  -551,
     715,  -551,  -551,  -551,   720,  -551,  -551,  -551,  -551,  -551,
    -551,   275,   376,  -551,  -551,   408,  -551,  -551,   750,  -551,
     745,   449,   458,   619,   -21,  -551,   747,  -551,   751,  -551,
    -551,     8,   753,  -551,   713,  -551,  -551,   723,   619,   679,
    1539,  -551,  -551,  1607,  3714,  3714,  1607,  1607,   -21,   -28,
     756,  -551,  1607,   725,  -551,   727,  -551,   713,   548,   465,
    -551,  -551,  -551,  -551,   752,   479,   804,  -551,   762,  3714,
      24,   780,   782,  -551,  -551,  -551,   783,   789,  -551,  -551,
    3714,   792,  1607,  -551,   496,  3714,   -28,   -28,   746,   755,
     781,  -551,  -551,  -551,   501,   796,  -551,  -551,   784,  1607,
    -551,   -28,  3714,  -551,  -551,   505,   803,   619,     3,  3714,
     508,   800,  -551
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -551,  -551,    18,  -551,  -551,   544,  -288,   442,  -551,  -551,
    -170,  -551,   327,   310,   288,   328,   504,   500,   506,   502,
     498,  -551,   -48,   -87,  -551,  -152,  -235,  -488,     5,  -551,
    -551,   170,  -551,   194,  -551,  -551,  -551,  -551,     1,   116,
       4,    47,   -39,   428,  -551,   486,  -121,   489,  -551,   566,
     779,   546,  -551,  -551,  -551,   121,  -551,  -551,  -551,  -551,
    -551,  -551,   397,   285,  -551,   195,  -551,   438,  -551,  -551,
    -551,  -551,  -245,  -286,  -551,  -551,  -551,  -551,   291,   290,
     295,  -243,  -551,  -551,  -551,   576,   311,  -551,  -551,  -551,
    -551,   314,   202,  -551,    29,  -287,  -365,  -550,  -551,  -283,
    -551,   196,  -381,  -551,   155,  -551,   691,  -551,  -485,  -149,
     330,  -551,  -551,  -551,  -551,  -551,  -551,  -551,   808,  -551,
    -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,  -551,
    -551,  -551,  -551,  -551,  -551,   -34,  -551,   164,   -71,  -551,
     -26,  -551,  -201,    40,   -73,   209,  -551,   280,   -31,  -551,
      12,    92,  -551,   -10,   232,  -551,  -281,  -231,     2,   532
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -384
static const yytype_int16 yytable[] =
{
     208,    41,    68,   391,    43,    37,   435,   126,   107,   132,
     300,   137,    65,   500,   287,   102,   102,   669,   502,   368,
     448,   396,   504,    68,   224,   689,   455,   589,   263,   630,
     314,   377,   578,    65,   233,   229,    76,   152,   729,    80,
      62,   287,   506,   106,   106,    68,    68,    44,    81,   315,
     345,   242,   606,    65,    65,    65,    65,   413,    82,   168,
      41,    68,   445,    43,    37,   292,   292,   149,    77,   219,
      68,    65,  -333,   481,   428,   152,   257,   705,   373,    68,
     153,   104,   108,   117,   124,    83,   142,   381,   673,    65,
     292,   385,    66,   429,   674,   389,    21,   220,   254,    62,
     346,   263,   223,   638,    13,   448,    44,    65,   232,   507,
     682,   292,    22,    79,    13,    19,    42,   157,   153,   646,
     481,    54,    21,   482,   397,    19,  -335,   481,   182,   182,
     182,   287,   397,   105,   109,   118,   125,   213,    22,   552,
      22,   428,   217,   436,   146,    35,    95,   511,    22,   229,
     259,    66,   146,   261,    13,   149,   223,    69,   459,   460,
     461,   229,    22,    84,   555,    19,   490,   361,   440,   158,
     482,    35,    85,    35,    70,    42,   684,   482,    96,    86,
      54,    35,   362,    22,   281,    87,    96,    79,   550,   152,
     102,   366,    90,   476,    95,    35,   262,   181,   186,   187,
      96,   152,   350,   355,   357,   559,   212,   208,   254,   628,
      22,   629,   710,   599,   354,   354,    35,   360,   364,   367,
      22,    96,   232,   259,   132,   448,   261,   456,    88,    65,
     331,   332,   153,   263,   232,   305,   600,   596,   140,   107,
     458,   335,   336,    35,   153,   536,   102,   102,   228,   400,
     404,   407,   410,    35,   605,   358,   363,   157,   136,   218,
    -337,   401,   401,   408,   408,   260,   156,   357,   440,   262,
     443,   421,    54,   190,   364,   364,   360,   360,   102,   588,
     263,   417,   223,    22,   421,   484,   368,   263,   377,   488,
     337,   338,   422,   229,   632,   305,   229,   147,  -329,   399,
     403,   406,   409,    73,   304,   551,   364,   360,    13,   158,
     660,   281,   363,   363,   415,   416,    35,   618,   618,    19,
     445,   605,    71,   333,   334,   715,   349,    72,   221,   152,
     229,   661,  -339,   152,    74,   219,   152,   141,   260,    75,
     724,   553,    22,   242,   363,   446,   146,   428,    54,    74,
     569,   354,   314,   305,    75,   259,   354,    54,   261,   360,
     213,    54,   360,   487,   304,    54,   489,   594,    74,   232,
     152,   554,   485,    75,   490,   254,   485,   152,   417,   153,
     683,   365,   245,   686,   687,   147,   417,   492,   431,   695,
     417,  -331,   254,   432,   417,   583,   478,    54,   625,   401,
    -341,   262,   259,   401,   483,   261,   580,   408,   486,   259,
     408,   314,   261,   485,   584,   361,   229,    91,   229,   712,
     485,    92,   304,   398,   402,  -343,   263,  -345,    93,   212,
     662,    22,    94,   370,   725,   635,   723,   246,   305,   305,
     293,   730,   378,   428,   544,   641,   642,   383,   262,    22,
     549,   387,   545,   146,   247,   262,   152,   294,   152,   256,
     366,   295,   663,   376,    35,   249,   254,   349,   570,    96,
     260,   112,   120,   213,   112,   128,   112,   134,   112,   138,
     354,   116,   123,    22,   428,   360,   209,   146,   575,   489,
     210,   489,   580,   428,    54,   208,   296,   297,   298,   485,
     361,   485,    54,   666,   229,   120,    54,   304,   304,   419,
      54,   420,   667,   685,   428,    54,    22,   260,   257,   328,
     648,   626,   179,   157,   260,   218,   157,   189,   329,   330,
     443,   428,   211,   701,   570,   570,   428,   704,   102,   250,
     314,   417,   212,   314,   152,   291,   401,   408,   259,    35,
     713,   261,   292,   714,   228,   720,    22,   257,   305,   726,
     146,   218,   731,   299,    13,   360,   364,   183,   183,   183,
     184,   184,   184,   580,   613,    19,   183,   489,   301,   184,
     339,   340,    95,   413,   157,   157,   480,   485,   253,   114,
     122,   147,   127,   130,   262,   449,   302,   699,    22,   450,
     376,   284,   303,   446,   363,   310,   496,   497,   342,   376,
     120,   128,   134,   138,   289,   290,   312,   451,   644,   341,
     123,   452,   253,   466,   467,   468,   469,   304,    13,   649,
     650,    35,   311,   480,   343,   208,    96,   344,   264,    19,
     480,   120,   208,   464,   465,   120,   405,   185,   185,   185,
     365,   123,   560,   348,    13,   561,   185,    54,   462,   463,
      13,   668,    22,   260,   356,    19,   146,   470,   471,   369,
     347,    19,   361,   131,   183,   390,   679,   184,   357,   393,
     412,   427,   395,   423,   277,   278,   279,   690,    22,   112,
     120,   112,   134,   574,    22,    35,   430,   576,   253,   116,
     123,   439,   112,   120,   453,   457,   168,   493,   365,   543,
    -236,   264,   116,   123,   556,   558,   568,   147,   582,   566,
     586,    35,   376,   587,   690,   690,    96,    35,   122,   130,
     591,   590,   592,   120,   183,   597,     2,   184,   598,   690,
    -258,  -259,   428,   123,   601,   728,     8,     9,   602,    11,
     607,   614,    13,   608,   185,   612,   440,   610,   620,   122,
     623,   374,   375,    19,   636,   634,    20,   637,   639,   640,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   643,   253,   664,
     652,   700,   183,   645,   647,   184,   658,   411,   665,   183,
     414,   656,   184,   671,   627,   672,   675,   114,   122,   258,
     694,   696,   702,   697,   185,    32,   703,   707,   706,   708,
     114,   122,   113,   121,   709,   113,   129,   113,   135,   113,
     139,   711,   717,   718,   721,   719,   251,   722,   727,   732,
     437,   270,   473,   264,   477,   472,   475,   698,   676,   474,
     565,   122,   624,   621,   680,   622,   619,   288,   425,   678,
     611,   609,   716,   633,   688,   253,   604,   144,     0,     0,
       0,     0,   185,     0,     0,     0,     0,   183,   183,   185,
     184,   184,   253,     2,   288,     0,     0,     0,     0,     0,
     264,     0,     0,     8,     9,   285,    11,   264,     0,    13,
     491,     0,     0,     0,     0,     0,   120,     0,   498,   499,
      19,   120,   183,    20,   120,   184,   371,   372,     0,  -383,
       0,     0,     0,   159,     0,   379,   380,     0,   382,     0,
     384,   160,   386,     0,   388,   161,   162,   163,   164,   165,
       0,     0,     0,     0,     0,     0,     0,   193,     0,   250,
       0,     0,     0,     0,     0,     0,   253,   185,   185,   316,
       0,   131,    32,     0,     0,     0,     0,   418,     0,     0,
       0,     0,   120,   120,   288,     0,     0,     0,     0,     0,
     167,   168,   169,   170,   171,     0,     0,   172,   173,     0,
       0,   159,   185,     0,     0,   174,     0,   183,     0,   160,
     184,     0,     0,   161,   162,   163,   164,   165,     0,     0,
     253,   253,   571,   572,   573,   193,     0,   278,     0,     0,
     252,     0,   577,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,     0,     0,     0,   264,     0,     0,     0,
     113,   121,   113,   135,     0,     0,     0,     0,   167,   168,
     169,   170,   171,   113,   121,   172,   173,     0,     0,     0,
       0,     0,     0,   174,   495,     0,     0,     0,     0,     0,
     285,     0,   501,   -40,   -40,   -40,   503,   185,   -40,     0,
     505,   -40,     0,     0,   -40,     0,     0,   -40,   -40,   -40,
     -40,   -40,     0,     0,   -40,   -40,     0,     0,   159,   -40,
       0,     0,     0,     0,     0,     0,   160,     0,     0,     0,
     161,   162,   163,   164,   165,     0,     0,     0,     0,     0,
       0,     0,   193,     0,   250,     0,     0,     0,   -40,   -40,
     -40,   -40,   -40,   -40,     0,     0,     0,     0,     0,     0,
       0,     0,   -40,   -40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -40,     0,   167,   168,   169,   170,   171,
     -40,   285,   172,   173,   -31,   -31,   -31,     0,     0,   -31,
     174,     0,   -31,     0,     0,   -31,     0,     0,   -31,   -31,
     -31,   -31,   -31,     0,     0,   -31,   -31,     0,     0,   159,
     -31,     0,     0,     0,     0,     0,     0,   160,     0,     0,
       0,   161,   162,   163,   164,   165,     0,     0,     0,     0,
       0,     0,     0,   193,     0,   250,     0,     0,     0,   -31,
     -31,   -31,   -31,   -31,   -31,     0,     0,     0,     0,     0,
       0,     0,     0,   -31,   -31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -31,     0,   167,   168,   169,   170,
     171,   -31,     0,   172,   173,     0,     2,     3,     4,     5,
     512,   174,     6,   513,   514,     7,     8,     9,    10,    11,
     515,    12,    13,    14,    15,    16,   516,   517,    17,    18,
     518,   519,   159,    19,   520,   521,    20,   522,     0,     0,
     160,     0,     0,     0,   161,   162,   163,   164,   165,     0,
       0,     0,     0,     0,     0,     0,   193,     0,   250,  -299,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
     523,   524,   525,     0,     0,     0,    29,    30,     0,     0,
       0,     0,    31,     0,     0,    32,    33,    34,   526,   527,
     168,   169,   170,   171,   528,     0,   172,   173,     0,     2,
       3,     4,     5,   512,   174,     6,   513,   514,     7,     8,
       9,    10,    11,   515,    12,    13,    14,    15,    16,   516,
     517,    17,    18,   518,   519,   159,    19,   520,   521,    20,
     522,     0,     0,   160,     0,     0,     0,   161,   162,   163,
     164,   165,     0,     0,     0,     0,     0,     0,     0,   193,
       0,   250,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,   523,   524,   525,     0,     0,     0,    29,
      30,     0,     0,     0,     0,    31,     0,     0,    32,    33,
      34,   526,   527,   168,   169,   170,   171,   528,     0,   172,
     173,     3,     4,     5,     0,     0,     6,   174,     0,     7,
       0,     0,    10,     0,     0,    12,    13,    14,    15,    16,
       0,     0,    17,    18,     0,     0,   159,    19,     0,     0,
       0,     0,     0,     0,   160,     0,     0,     0,   161,   162,
     163,   164,   165,     0,     0,     0,     0,     0,     0,     0,
     166,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,   167,   168,   169,   170,   171,    36,   512,
     172,   173,   513,   514,     0,     0,     0,     0,   174,   515,
       0,     0,     0,     0,     0,   516,   517,     0,     0,   518,
     519,   159,     0,   520,   521,     0,   522,     0,     0,   160,
       0,     0,     0,   161,   162,   163,   164,   165,   159,     0,
       0,     0,     0,     0,     0,   193,   160,   250,  -299,     0,
     161,   162,   163,   164,   165,     0,     0,     0,     0,   523,
     524,   525,   193,     0,   579,   681,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   526,   527,   168,
     169,   170,   171,    75,   512,   172,   173,   513,   514,     0,
       0,     0,     0,   174,   515,   167,   168,   169,   170,   171,
     516,   517,   172,   173,   518,   519,   159,     0,   520,   521,
     174,   522,     0,     0,   160,     0,     0,     0,   161,   162,
     163,   164,   165,     0,     0,     0,     0,     0,     0,     0,
     193,     0,   250,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   523,   524,   525,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   526,   527,   168,   169,   170,   171,    75,     0,
     172,   173,     0,     0,     0,     0,   143,     1,   174,     2,
       3,     4,     5,     0,     0,     6,     0,     0,     7,     8,
       9,    10,    11,     0,    12,    13,    14,    15,    16,     0,
       0,    17,    18,     0,     0,     0,    19,     0,     0,    20,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,    31,     0,     0,    32,    33,
      34,     1,    35,     2,     3,     4,     5,    36,     0,     6,
       0,     0,     7,     8,     9,    10,    11,     0,    12,    13,
      14,    15,    16,     0,     0,    17,    18,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     0,     0,    31,
       0,     0,    32,    33,    34,     0,    35,     2,     3,     4,
       5,    36,     0,     6,     0,     0,     7,     8,     9,    10,
      11,     0,    12,    13,    14,    15,    16,     0,     0,    17,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,   397,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,   257,     0,
       0,   146,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    32,     0,    34,     0,
      35,     2,     3,     4,     5,    36,     0,     6,     0,     0,
       7,     8,     9,    10,    11,     0,    12,    13,    14,    15,
      16,     0,     0,    17,    18,     0,     0,     0,    19,     0,
       0,    20,     0,     0,     0,   405,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,   257,     0,     0,   146,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      32,     0,    34,     0,    35,     2,     3,     4,     5,    36,
       0,     6,     0,     0,     7,     8,     9,    10,    11,     0,
      12,    13,    14,    15,    16,     0,     0,    17,    18,     0,
       0,     0,    19,     0,     0,    20,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,   146,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    32,     0,    34,     0,    35,     2,
       3,     4,     5,   110,     0,     6,     0,     0,     7,     8,
       9,    10,    11,     0,    12,    13,    14,    15,    16,     0,
       0,    17,    18,     0,     0,     0,    19,     0,     0,    20,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,   146,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    32,     0,
      34,     0,    35,     2,     3,     4,     5,   119,     0,     6,
       0,     0,     7,     8,     9,    10,    11,     0,    12,    13,
      14,    15,    16,     0,     0,    17,    18,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,   349,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,   257,     0,     0,   146,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     2,     3,     4,
       5,     0,    32,     6,    34,     0,     7,     8,     9,    10,
      11,    36,    12,    13,    14,    15,    16,     0,     0,    17,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    32,     0,    34,     0,
      35,     2,     3,     4,     5,   110,     0,     6,     0,     0,
       7,     8,     9,    10,    11,     0,    12,    13,    14,    15,
      16,     0,     0,    17,    18,     0,     0,     0,    19,     0,
       0,    20,     0,     0,     0,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      32,     0,    34,     0,    35,     2,     3,     4,     5,   119,
       0,     6,     0,     0,     7,     8,     9,    10,    11,     0,
      12,    13,    14,    15,    16,     0,     0,    17,    18,     0,
       0,     0,    19,     0,     0,    20,     0,     0,     0,   357,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    32,     0,    34,     0,    35,     2,
       3,     4,     5,   110,     0,     6,     0,     0,     7,     8,
       9,    10,    11,     0,    12,    13,    14,    15,    16,     0,
       0,    17,    18,     0,     0,     0,    19,     0,     0,    20,
       0,     0,     0,   357,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    32,     0,
      34,     0,    35,     2,     3,     4,     5,   119,     0,     6,
       0,     0,     7,     8,     9,    10,    11,     0,    12,    13,
      14,    15,    16,     0,     0,    17,    18,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   250,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     0,     0,    31,
       0,     0,    32,    33,    34,     0,     2,     3,     4,     5,
       0,    36,     6,     0,     0,     7,     8,     9,    10,    11,
       0,    12,    13,    14,    15,    16,     0,     0,    17,    18,
       0,     0,     0,    19,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    32,     0,    34,     0,   258,
       2,     3,     4,     5,    36,     0,     6,     0,     0,     7,
       8,     9,    10,    11,     0,    12,    13,    14,    15,    16,
       0,     0,    17,    18,     0,     0,     0,    19,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,    31,     0,     0,    32,
      33,    34,     0,     2,     3,     4,     5,     0,    36,     6,
       0,     0,     7,     8,     9,    10,    11,     0,    12,    13,
      14,    15,    16,     0,     0,    17,    18,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   257,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     2,     3,     4,
       5,     0,    32,     6,    34,     0,     7,     8,     9,    10,
      11,    36,    12,    13,    14,    15,    16,     0,     0,    17,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,     0,
       0,     0,     3,     4,     5,     0,    32,     6,    34,     0,
       7,     0,     0,    10,     0,    36,    12,    13,    14,    15,
      16,     0,     0,    17,    18,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,   357,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,    35,     3,     4,     5,     0,   119,
       6,     0,     0,     7,     0,     0,    10,     0,     0,    12,
      13,    14,    15,    16,     0,     0,    17,    18,     0,     0,
       0,    19,     0,     0,     0,     0,     0,     0,   349,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,   146,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    30,     0,     0,     0,     3,
       4,     5,     0,     0,     6,    34,     0,     7,     0,     0,
      10,     0,   119,    12,    13,    14,    15,    16,     0,     0,
      17,    18,     0,     0,     0,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   447,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     3,     4,     5,     0,     0,     6,    34,
       0,     7,     0,     0,    10,     0,    36,    12,    13,    14,
      15,    16,     0,     0,    17,    18,     0,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   510,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     3,     4,     5,
       0,     0,     6,    34,     0,     7,     0,     0,    10,     0,
      36,    12,    13,    14,    15,    16,     0,     0,    17,    18,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   585,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     3,     4,     5,     0,     0,     6,    34,     0,     7,
       0,     0,    10,     0,    36,    12,    13,    14,    15,    16,
       0,     0,    17,    18,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     3,     4,     5,     0,     0,
       6,    34,     0,     7,     0,     0,    10,     0,    36,    12,
      13,    14,    15,    16,     0,     0,    17,    18,     0,     0,
       0,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     2,     3,     4,    29,    30,     0,     6,     0,     0,
       0,     8,     9,    10,    11,    34,     0,    13,    14,    15,
      16,     0,   119,    17,    18,     0,     0,     0,    19,     3,
       4,    20,     0,     0,     6,     0,     0,     0,     0,     0,
      10,     0,     0,     0,    13,    14,    15,    16,     0,     0,
      17,    18,     0,     0,     0,    19,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      32,     0,    34,     0,    23,    24,    25,    26,    27,    28,
       0,     0,   159,     0,     0,     0,     0,     0,    29,    30,
     160,     0,     0,     0,   161,   162,   163,   164,   165,    34,
     159,     0,     0,     0,     0,     0,   193,   434,   160,     0,
       0,     0,   161,   162,   163,   164,   165,     0,     0,     0,
     159,     0,     0,     0,   193,     0,   579,     0,   160,     0,
       0,     0,   161,   162,   163,   164,   165,     0,     0,   167,
     168,   169,   170,   171,   193,     0,   172,   173,     0,     0,
       0,     0,     0,     0,   174,     0,     0,   167,   168,   169,
     170,   171,     0,     0,   172,   173,     0,     0,     0,     0,
       0,     0,   174,     0,     0,   159,     0,   167,   168,   169,
     170,   171,   593,   160,   172,   173,     0,   161,   162,   163,
     164,   165,   174,   159,     0,     0,     0,     0,     0,   166,
       0,   160,     0,     0,     0,   161,   162,   163,   164,   165,
       0,     0,     0,   159,     0,     0,     0,   193,     0,     0,
       0,   160,     0,     0,     0,   161,   162,   163,   164,   165,
       0,     0,   167,   168,   169,   170,   171,   283,     0,   172,
     173,     0,     0,     0,     0,     0,     0,   174,     0,     0,
     167,   168,   169,   170,   171,     0,     0,   172,   173,     0,
       0,     0,     0,     0,     0,   174,     0,     0,     0,     0,
     167,   168,   169,   170,   171,     0,     0,   172,   173,     0,
       0,     0,     0,     0,     0,   174
};

static const yytype_int16 yycheck[] =
{
      87,     0,     0,   248,     0,     0,   294,    46,    42,    48,
     180,    50,     0,   378,   166,    41,    42,    38,   383,   220,
     306,   256,   387,    21,    97,    53,   313,   515,   149,   579,
      35,   232,    54,    21,   107,   106,     7,    68,    35,    48,
       0,   193,    19,    41,    42,    43,    44,     0,    48,    54,
      52,   124,   537,    41,    42,    43,    44,    35,    48,    87,
      59,    59,   305,    59,    59,    87,    87,    65,    21,    95,
      68,    59,    55,   354,    35,   106,    54,    53,   227,    77,
      68,    41,    42,    43,    44,    48,    57,   236,    80,    77,
      87,   240,     0,    54,    86,   244,    37,    95,   146,    59,
     102,   222,    85,   591,    19,   391,    59,    95,   106,    86,
     660,    87,    53,    21,    19,    30,     0,    77,   106,   604,
     401,     0,    37,   354,    37,    30,    55,   408,    81,    82,
      83,   283,    37,    41,    42,    43,    44,    90,    53,   426,
      53,    35,    95,   295,    57,    86,    37,   392,    53,   220,
     149,    59,    57,   149,    19,   153,    85,    39,   328,   329,
     330,   232,    53,    55,    58,    30,   367,    37,    38,    77,
     401,    86,    48,    86,    56,    59,   664,   408,    91,    48,
      59,    86,   216,    53,   155,    53,    91,    95,   423,   220,
     216,   217,    53,   345,    37,    86,   149,    81,    82,    83,
      91,   232,   212,   213,    37,   440,    90,   294,   256,   574,
      53,   576,   700,    30,   212,   213,    86,   215,   216,   217,
      53,    91,   220,   222,   263,   511,   222,   314,    86,   217,
      42,    43,   220,   354,   232,   188,    53,   520,    39,   273,
     327,    48,    49,    86,   232,   394,   272,   273,    91,   259,
     260,   261,   262,    86,   537,   215,   216,   217,    49,    95,
      55,   259,   260,   261,   262,   149,    55,    37,    38,   222,
     304,    35,   151,    86,   272,   273,   274,   275,   304,   514,
     401,   276,    85,    53,    35,   358,   487,   408,   489,   362,
      97,    98,    56,   364,   582,   248,   367,    65,    55,   259,
     260,   261,   262,    55,   188,    56,   304,   305,    19,   217,
      35,   282,   272,   273,   274,   275,    86,   560,   561,    30,
     563,   604,     4,    95,    96,   706,    37,     9,    96,   360,
     401,    56,    55,   364,    86,   361,   367,    55,   222,    91,
     721,   428,    53,   416,   304,   305,    57,    35,   227,    86,
      38,   349,    35,   306,    91,   354,   354,   236,   354,   357,
     313,   240,   360,   361,   248,   244,   364,   519,    86,   367,
     401,    54,   360,    91,   575,   423,   364,   408,   373,   367,
     663,   217,    53,   666,   667,   153,   381,   369,    86,   672,
     385,    55,   440,    91,   389,    35,   349,   276,   568,   397,
      55,   354,   401,   401,   357,   401,   493,   405,   361,   408,
     408,    35,   408,   401,    54,    37,   487,    35,   489,   702,
     408,    39,   306,   259,   260,    55,   547,    55,    35,   313,
      54,    53,    39,   224,   722,   587,   719,    39,   391,   392,
      36,   729,   233,    35,   397,   597,   598,   238,   401,    53,
     421,   242,   405,    57,    39,   408,   487,    53,   489,    57,
     486,    57,    54,   231,    86,    55,   514,    37,   478,    91,
     354,    43,    44,   426,    46,    47,    48,    49,    50,    51,
     478,    43,    44,    53,    35,   483,    35,    57,   486,   487,
      39,   489,   579,    35,   373,   582,    92,    93,    94,   487,
      37,   489,   381,    54,   575,    77,   385,   391,   392,   277,
     389,   279,    54,   665,    35,   394,    53,   401,    54,    37,
     607,   569,    80,   483,   408,   361,   486,    85,    46,    47,
     564,    35,    90,    54,   544,   545,    35,   689,   564,    55,
      35,   536,   426,    35,   575,    86,   544,   545,   547,    86,
      54,   547,    87,   705,    91,    54,    53,    54,   511,    54,
      57,   397,    54,    49,    19,   563,   564,    81,    82,    83,
      81,    82,    83,   660,   556,    30,    90,   575,    49,    90,
      99,   100,    37,    35,   544,   545,   354,   575,   146,    43,
      44,   359,    46,    47,   547,    35,    49,    49,    53,    39,
     368,   159,    49,   563,   564,    49,   374,   375,    50,   377,
     182,   183,   184,   185,   172,   173,    49,    35,   600,    41,
     182,    39,   180,   335,   336,   337,   338,   511,    19,    70,
      71,    86,   190,   401,    51,   722,    91,   101,   149,    30,
     408,   213,   729,   333,   334,   217,    37,    81,    82,    83,
     486,   213,   443,    54,    19,   446,    90,   536,   331,   332,
      19,   643,    53,   547,    54,    30,    57,   339,   340,    53,
      86,    30,    37,    81,   188,    53,   658,   188,    37,    56,
      35,    54,    58,    40,   152,   153,   154,   669,    53,   261,
     262,   263,   264,   484,    53,    86,    54,   488,   256,   261,
     262,    65,   274,   275,    35,    39,    87,    40,   544,    58,
     103,   222,   274,   275,    66,    86,    54,   485,    53,    75,
      39,    86,   490,    53,   706,   707,    91,    86,   182,   183,
      53,    39,    38,   305,   248,    53,     3,   248,    53,   721,
      38,    38,    35,   305,    39,   727,    13,    14,    38,    16,
      53,    72,    19,   103,   188,    54,    38,    86,    65,   213,
      48,   229,   230,    30,    38,    54,    33,    39,    39,    34,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,    53,   346,    39,
      77,    39,   306,    56,    56,   306,    76,   265,    53,   313,
     268,    86,   313,    56,   572,    54,    53,   261,   262,    86,
      54,    86,     8,    86,   248,    82,    54,    35,    38,    36,
     274,   275,    43,    44,    35,    46,    47,    48,    49,    50,
      51,    39,    86,    78,    38,    54,   145,    53,    35,    39,
     296,   150,   342,   354,   346,   341,   344,   677,   654,   343,
     453,   305,   567,   563,   659,   564,   561,   166,   282,   657,
     549,   547,   707,   583,   668,   423,   536,    59,    -1,    -1,
      -1,    -1,   306,    -1,    -1,    -1,    -1,   391,   392,   313,
     391,   392,   440,     3,   193,    -1,    -1,    -1,    -1,    -1,
     401,    -1,    -1,    13,    14,     1,    16,   408,    -1,    19,
     368,    -1,    -1,    -1,    -1,    -1,   478,    -1,   376,   377,
      30,   483,   426,    33,   486,   426,   225,   226,    -1,    39,
      -1,    -1,    -1,    29,    -1,   234,   235,    -1,   237,    -1,
     239,    37,   241,    -1,   243,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,   514,   391,   392,    40,
      -1,    81,    82,    -1,    -1,    -1,    -1,   276,    -1,    -1,
      -1,    -1,   544,   545,   283,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    -1,    -1,    93,    94,    -1,
      -1,    29,   426,    -1,    -1,   101,    -1,   511,    -1,    37,
     511,    -1,    -1,    41,    42,    43,    44,    45,    -1,    -1,
     568,   569,   480,   481,   482,    53,    -1,   485,    -1,    -1,
      58,    -1,   490,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,   547,    -1,    -1,    -1,
     261,   262,   263,   264,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,   274,   275,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   373,    -1,    -1,    -1,    -1,    -1,
       1,    -1,   381,     4,     5,     6,   385,   511,     9,    -1,
     389,    12,    -1,    -1,    15,    -1,    -1,    18,    19,    20,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    55,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    86,    87,    88,    89,    90,
      91,     1,    93,    94,     4,     5,     6,    -1,    -1,     9,
     101,    -1,    12,    -1,    -1,    15,    -1,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    55,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    -1,     3,     4,     5,     6,
       7,   101,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    55,    56,
      -1,    -1,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    68,    69,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    -1,     3,
       4,     5,     6,     7,   101,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    67,    68,    69,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,     4,     5,     6,    -1,    -1,     9,   101,    -1,    12,
      -1,    -1,    15,    -1,    -1,    18,    19,    20,    21,    22,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    86,    87,    88,    89,    90,    91,     7,
      93,    94,    10,    11,    -1,    -1,    -1,    -1,   101,    17,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,
      28,    29,    -1,    31,    32,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    37,    55,    56,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    67,
      68,    69,    53,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,     7,    93,    94,    10,    11,    -1,
      -1,    -1,    -1,   101,    17,    86,    87,    88,    89,    90,
      23,    24,    93,    94,    27,    28,    29,    -1,    31,    32,
     101,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    -1,    -1,    -1,    -1,     0,     1,   101,     3,
       4,     5,     6,    -1,    -1,     9,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,    83,
      84,     1,    86,     3,     4,     5,     6,    91,    -1,     9,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,
      30,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    82,    83,    84,    -1,    86,     3,     4,     5,
       6,    91,    -1,     9,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    -1,    -1,    25,
      26,    -1,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,
      -1,    57,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,
      86,     3,     4,     5,     6,    91,    -1,     9,    -1,    -1,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    30,    -1,
      -1,    33,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    -1,    -1,    57,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    -1,    86,     3,     4,     5,     6,    91,
      -1,     9,    -1,    -1,    12,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    -1,
      -1,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    84,    -1,    86,     3,
       4,     5,     6,    91,    -1,     9,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    57,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    -1,    86,     3,     4,     5,     6,    91,    -1,     9,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,
      30,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    -1,    57,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    -1,    -1,     3,     4,     5,
       6,    -1,    82,     9,    84,    -1,    12,    13,    14,    15,
      16,    91,    18,    19,    20,    21,    22,    -1,    -1,    25,
      26,    -1,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,
      86,     3,     4,     5,     6,    91,    -1,     9,    -1,    -1,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    30,    -1,
      -1,    33,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    -1,    86,     3,     4,     5,     6,    91,
      -1,     9,    -1,    -1,    12,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    -1,
      -1,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    84,    -1,    86,     3,
       4,     5,     6,    91,    -1,     9,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    -1,    86,     3,     4,     5,     6,    91,    -1,     9,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    82,    83,    84,    -1,     3,     4,     5,     6,
      -1,    91,     9,    -1,    -1,    12,    13,    14,    15,    16,
      -1,    18,    19,    20,    21,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,    86,
       3,     4,     5,     6,    91,    -1,     9,    -1,    -1,    12,
      13,    14,    15,    16,    -1,    18,    19,    20,    21,    22,
      -1,    -1,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,
      83,    84,    -1,     3,     4,     5,     6,    -1,    91,     9,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    -1,    -1,     3,     4,     5,
       6,    -1,    82,     9,    84,    -1,    12,    13,    14,    15,
      16,    91,    18,    19,    20,    21,    22,    -1,    -1,    25,
      26,    -1,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    -1,     4,     5,     6,    -1,    82,     9,    84,    -1,
      12,    -1,    -1,    15,    -1,    91,    18,    19,    20,    21,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    86,     4,     5,     6,    -1,    91,
       9,    -1,    -1,    12,    -1,    -1,    15,    -1,    -1,    18,
      19,    20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,     4,
       5,     6,    -1,    -1,     9,    84,    -1,    12,    -1,    -1,
      15,    -1,    91,    18,    19,    20,    21,    22,    -1,    -1,
      25,    26,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    -1,     4,     5,     6,    -1,    -1,     9,    84,
      -1,    12,    -1,    -1,    15,    -1,    91,    18,    19,    20,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    -1,     4,     5,     6,
      -1,    -1,     9,    84,    -1,    12,    -1,    -1,    15,    -1,
      91,    18,    19,    20,    21,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,     4,     5,     6,    -1,    -1,     9,    84,    -1,    12,
      -1,    -1,    15,    -1,    91,    18,    19,    20,    21,    22,
      -1,    -1,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,
       9,    84,    -1,    12,    -1,    -1,    15,    -1,    91,    18,
      19,    20,    21,    22,    -1,    -1,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    73,    74,    -1,     9,    -1,    -1,
      -1,    13,    14,    15,    16,    84,    -1,    19,    20,    21,
      22,    -1,    91,    25,    26,    -1,    -1,    -1,    30,     4,
       5,    33,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    -1,
      25,    26,    -1,    -1,    -1,    30,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    73,    74,
      37,    -1,    -1,    -1,    41,    42,    43,    44,    45,    84,
      29,    -1,    -1,    -1,    -1,    -1,    53,    54,    37,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    53,    -1,    55,    -1,    37,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    -1,    86,
      87,    88,    89,    90,    53,    -1,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    86,    87,    88,
      89,    90,    -1,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    29,    -1,    86,    87,    88,
      89,    90,    91,    37,    93,    94,    -1,    41,    42,    43,
      44,    45,   101,    29,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      -1,    -1,    86,    87,    88,    89,    90,    53,    -1,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      86,    87,    88,    89,    90,    -1,    -1,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    -1,    -1,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,   101
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,     4,     5,     6,     9,    12,    13,    14,
      15,    16,    18,    19,    20,    21,    22,    25,    26,    30,
      33,    37,    53,    59,    60,    61,    62,    63,    64,    73,
      74,    79,    82,    83,    84,    86,    91,   142,   143,   148,
     150,   152,   153,   154,   155,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   169,   181,   182,   185,   196,   231,
     232,   233,   257,   262,   263,   264,   265,   266,   272,    39,
      56,     4,     9,    55,    86,    91,   208,   155,   257,   265,
      48,    48,    48,    48,    55,    48,    48,    53,    86,   144,
      53,    35,    39,    35,    39,    37,    91,   249,   250,   251,
     252,   253,   254,   255,   257,   265,   272,   249,   257,   265,
      91,   156,   157,   164,   165,   169,   181,   257,   265,    91,
     157,   164,   165,   181,   257,   265,   156,   165,   157,   164,
     165,    81,   156,   259,   157,   164,   259,   156,   157,   164,
      39,    55,   208,     0,   232,   234,    57,   268,   269,   272,
     239,   244,   262,   264,   265,   197,    55,   257,   265,    29,
      37,    41,    42,    43,    44,    45,    53,    86,    87,    88,
      89,    90,    93,    94,   101,   115,   116,   117,   118,   121,
     123,   153,   155,   159,   161,   163,   153,   153,   170,   121,
      86,   175,   176,    53,   120,   121,   124,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,    35,
      39,   121,   153,   155,   209,   149,   151,   155,   251,   254,
     272,   268,   272,    85,   258,   235,   240,   245,    91,   252,
     254,   256,   272,   258,   236,   241,   246,   237,   258,   242,
     247,   238,   258,   243,   248,    53,    39,    39,   183,    55,
      55,   220,    58,   121,   136,   140,    57,    54,    86,   152,
     153,   154,   155,   160,   161,   201,   203,   205,   206,   273,
     220,   142,   152,   153,   154,   155,   223,   273,   273,   273,
     199,   208,   198,    53,   121,     1,   137,   139,   220,   121,
     121,    86,    87,    36,    53,    57,    92,    93,    94,    49,
     124,    49,    49,    49,   153,   155,   186,   187,   188,   190,
      49,   121,    49,   125,    35,    54,    40,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   138,    37,    46,
      47,    42,    43,    95,    96,    48,    49,    97,    98,    99,
     100,    41,    50,    51,   101,    52,   102,    86,    54,    37,
     267,   268,   270,   271,   272,   267,    54,    37,   257,   264,
     272,    37,   249,   257,   272,   251,   254,   272,   256,    53,
     259,   220,   220,   223,   273,   273,   268,   256,   259,   220,
     220,   223,   220,   259,   220,   223,   220,   259,   220,   223,
      53,   186,   184,    56,   221,    58,   140,    37,   251,   257,
     267,   272,   251,   257,   267,    37,   257,   267,   272,   257,
     267,   273,    35,    35,   273,   257,   257,   142,   220,   268,
     268,    35,    56,    40,   200,   199,   122,    54,    35,    54,
      54,    86,    91,   119,    54,   120,   139,   119,   166,    65,
      38,   192,   195,   249,   193,   195,   257,    56,   187,    35,
      39,    35,    39,    35,   167,   209,   137,    39,   137,   124,
     124,   124,   126,   126,   127,   127,   128,   128,   128,   128,
     129,   129,   130,   131,   132,   133,   139,   134,   155,   267,
     268,   270,   271,   155,   258,   264,   155,   272,   258,   272,
     256,   273,   116,    40,   210,   220,   268,   268,   273,   273,
     210,   220,   210,   220,   210,   220,    19,    86,   260,   261,
      56,   186,     7,    10,    11,    17,    23,    24,    27,    28,
      31,    32,    34,    67,    68,    69,    85,    86,    91,   139,
     141,   208,   213,   214,   219,   220,   223,   224,   225,   226,
     227,   228,   229,    58,   155,   155,   202,   204,   207,   208,
     140,    56,   209,   137,    54,    58,    66,   177,    86,   140,
     259,   259,   171,   189,   191,   176,    75,   173,    54,    38,
     267,   273,   273,   273,   259,   272,   259,   273,    54,    55,
     137,   211,    53,    35,    54,    56,    39,    53,   140,   141,
      39,    53,    38,    91,   139,   230,   213,    53,    53,    30,
      53,    39,    38,   222,   224,   213,   222,    53,   103,   205,
      86,   200,    54,   116,    72,   179,   168,   194,   195,   194,
      65,   193,   192,    48,   177,   124,   136,   268,   210,   210,
     211,   212,   120,   261,    54,   139,    38,    39,   141,    39,
      34,   139,   139,    53,   116,    56,   222,    56,   137,    70,
      71,   180,    77,   145,   146,   147,    86,   174,    76,   178,
      35,    56,    54,    54,    39,    53,    54,    54,   116,    38,
     215,    56,    54,    80,    86,    53,   147,   172,   206,   116,
     179,    56,   211,   213,   141,   139,   213,   213,   215,    53,
     116,   216,   217,   218,    54,   213,    86,    86,   145,    49,
      39,    54,     8,    54,   139,    53,    38,    35,    36,    35,
     141,    39,   213,    54,   139,   216,   218,    86,    78,    54,
      54,    38,    53,   213,   216,   120,    54,    35,   116,    35,
     120,    54,    39
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
        case 6:
#line 305 "./pb-gram.y"
    {  (yyval.n) = string_literal_list_action( (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n) );
          }
    break;

  case 7:
#line 316 "./pb-gram.y"
    {  (yyval.n) = identifier_expression_nonterm((yyvsp[(1) - (1)].n));
          }
    break;

  case 8:
#line 320 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, pointer_void_read_only_ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 11:
#line 325 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, (yyvsp[(2) - (3)].n)->ident->ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 12:
#line 329 "./pb-gram.y"
    {  CTYPE *c;
             if ((yyvsp[(2) - (3)].n)->ident->eclass == UNT)
               c = void_read_only_ctype;
             else
               c = (yyvsp[(2) - (3)].n)->ident->ctype;
             (yyval.n) = nonterm(TYP, c, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 13:
#line 337 "./pb-gram.y"
    {  CTYPE *c = int_read_only_ctype;
             NODE *n = terminal1(TYP, "1", c);
             warning(4, "couldn't parse expression--setting it to 1");
             (yyval.n) = nonterm(TYP, c, 3, (yyvsp[(1) - (3)].n), n, (yyvsp[(3) - (3)].n));
          }
    break;

  case 15:
#line 347 "./pb-gram.y"
    {  CTYPE *c = copy_ctype((yyvsp[(1) - (4)].n)->ident->ctype);
             reduce(c, ARR);
             (yyval.n) = nonterm(TYP, c, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 16:
#line 352 "./pb-gram.y"
    {  CTYPE *c = copy_ctype((yyvsp[(1) - (3)].n)->ident->ctype);
             reduce(c, FUN);
             (yyval.n) = nonterm(TYP, c, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 17:
#line 357 "./pb-gram.y"
    {  (yyval.n) = function_call_nonterm((yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
          }
    break;

  case 18:
#line 360 "./pb-gram.y"
    {  (yyval.n) = dot_member_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 19:
#line 363 "./pb-gram.y"
    {  (yyval.n) = arrow_member_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 20:
#line 366 "./pb-gram.y"
    {  CTYPE *c = (yyvsp[(1) - (2)].n)->ident->ctype;
              (yyval.n) = nonterm(TYP, c, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
           }
    break;

  case 21:
#line 370 "./pb-gram.y"
    {  CTYPE *c = (yyvsp[(1) - (2)].n)->ident->ctype;
              (yyval.n) = nonterm(TYP, c, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
           }
    break;

  case 22:
#line 377 "./pb-gram.y"
    { /* Node is untyped */
#if 0
             (yyvsp[(1) - (1)].n)->ident->ctype = UNDEFINED_CTYPE;
#else
             (yyvsp[(1) - (1)].n)->ident->ctype = undefined_read_only_ctype;
#endif
         }
    break;

  case 23:
#line 385 "./pb-gram.y"
    { /* Node is untyped */
#if 0
             (yyvsp[(1) - (1)].n)->ident->ctype = UNDEFINED_CTYPE;
#else
             (yyvsp[(1) - (1)].n)->ident->ctype = undefined_read_only_ctype;
#endif
         }
    break;

  case 25:
#line 397 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, (yyvsp[(3) - (3)].n)->ident->ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
         }
    break;

  case 27:
#line 404 "./pb-gram.y"
    {  CTYPE *ctype;
              ctype = (yyvsp[(2) - (2)].n)->ident->ctype;
              (yyval.n) = nonterm(TYP, ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
           }
    break;

  case 28:
#line 409 "./pb-gram.y"
    {  CTYPE *ctype;
              ctype = (yyvsp[(2) - (2)].n)->ident->ctype;
              (yyval.n) = nonterm(TYP, ctype, 2, (yyvsp[(2) - (2)].n), (yyvsp[(2) - (2)].n));
           }
    break;

  case 29:
#line 414 "./pb-gram.y"
    {  (yyval.n) = unary_operator_cast_expression_nonterm((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 30:
#line 417 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 31:
#line 420 "./pb-gram.y"
    {  push_decl();
          }
    break;

  case 32:
#line 423 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
             pop_decl();
          }
    break;

  case 40:
#line 444 "./pb-gram.y"
    {  pre_cast_expression_action();
           }
    break;

  case 41:
#line 447 "./pb-gram.y"
    {  (yyval.n) = post_cast_expression_action((yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n));
           }
    break;

  case 43:
#line 454 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 44:
#line 457 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 45:
#line 460 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 47:
#line 467 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 48:
#line 470 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 50:
#line 477 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 51:
#line 480 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 53:
#line 488 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 54:
#line 490 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 55:
#line 492 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 56:
#line 494 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 58:
#line 500 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 59:
#line 503 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 61:
#line 510 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 63:
#line 517 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 65:
#line 524 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 67:
#line 531 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 69:
#line 538 "./pb-gram.y"
    {  (yyval.n) = binop_nonterm((yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 71:
#line 546 "./pb-gram.y"
    {  CTYPE *c;
             if (!ctypematch((yyvsp[(3) - (5)].n)->ident->ctype, (yyvsp[(5) - (5)].n)->ident->ctype)) {
               parse_warning(4, "conditional expr type mismatch--assuming"
                             " result void");
               c = void_read_only_ctype; /* Assume result void. */
             }
             else
               c = binary_convert((yyvsp[(3) - (5)].n)->ident->ctype, (yyvsp[(5) - (5)].n)->ident->ctype);
             (yyval.n) = nonterm(TYP, c, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 73:
#line 561 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, (yyvsp[(1) - (3)].n)->ident->ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 86:
#line 582 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, (yyvsp[(3) - (3)].n)->ident->ctype, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 88:
#line 594 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 90:
#line 635 "./pb-gram.y"
    {  
            /* HACK: the check for decl->typex_name != NULL is to
               insure that the following code is only executed only
               for schema declarations or schema typedefs, and
               not for declarations of INSTANCES of schema typedefs.

               It just happens to be true that decl->typex_name will be
               non-NULL only in these cases, and I could have chosen some
               other test, such as decl->declared_but_unprinted != NULL,
               but decl->typex_name != NULL seemed most logical, since
               (1) decl->typex_name != NULL seems more fundamental than
               decl->declared_but_unprinted != NULL, and
               (2) the following code depends on decl->typex_name != NULL,
               anyway. (JAT) */

            if (decl->btype->len != 0
                && base_ptype(decl->btype)->pclass == SCH
                && decl->typex_name != NULL)
            {
              if (decl->sclass == TDF)
                parse_error("schema declaration can not be a typedef:"
                            " schema declaration must specify a single,"
                            " plain identifier");
              if (decl->dtype->len != 0)
                parse_error("schema declaration can not be a derrived type:"
                            " schema declaration must specify a single,"
                            " plain identifier");
              /* decl->name is the schema name, e.g. foo_schema. */
              /* decl->btype->ident->name is the schema type struct name,
                   e.g.  P2_unnamed_sue123 */
              post_ddlhint_schema_declaration(decl->name, decl->typex_name);
            }
            save_decl();
#if PRINT_DECL_AS_COMMENT
            (yyval.n) = nonterm(UNT, NULL, 4,
                         terminal_string1("/*"),
                         (yyvsp[(1) - (1)].n),
                         terminal_string1("*/\n"),
                         decl_ptree());
#else
            (yyval.n) = decl_ptree();
#endif
            clear_decl();
         }
    break;

  case 95:
#line 703 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 96:
#line 710 "./pb-gram.y"
    {  typex_declaration((yyvsp[(3) - (5)].n));  
             (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
#if 0
          }
    break;

  case 97:
#line 716 "./pb-gram.y"
    {  
             unnamed_schema_declaration();
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
#endif
          }
    break;

  case 98:
#line 727 "./pb-gram.y"
    {  add_label_to_symtab1((yyvsp[(1) - (1)].n)->ident->name);
             (yyval.n) = (yyvsp[(1) - (1)].n);
          }
    break;

  case 99:
#line 731 "./pb-gram.y"
    {  add_label_to_symtab1((yyvsp[(3) - (3)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 100:
#line 741 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 103:
#line 749 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 104:
#line 756 "./pb-gram.y"
    {  ddlhint_declaration((yyvsp[(3) - (14)].n)->ident->name, (yyvsp[(7) - (14)].n), (yyvsp[(10) - (14)].n)->ident->name, (yyvsp[(12) - (14)].n));
             (yyval.n) = nonterm(UNT, NULL, 12,
                          (yyvsp[(1) - (14)].n), (yyvsp[(2) - (14)].n), (yyvsp[(3) - (14)].n), (yyvsp[(4) - (14)].n), (yyvsp[(5) - (14)].n), (yyvsp[(6) - (14)].n), (yyvsp[(7) - (14)].n), (yyvsp[(8) - (14)].n), (yyvsp[(10) - (14)].n), (yyvsp[(11) - (14)].n), (yyvsp[(12) - (14)].n), (yyvsp[(13) - (14)].n)); 
          }
    break;

  case 105:
#line 768 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n));
          }
    break;

  case 106:
#line 772 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n));
          }
    break;

  case 107:
#line 775 "./pb-gram.y"
    {  save_decl();
             clear_dtype();
          }
    break;

  case 108:
#line 779 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (7)].n), (yyvsp[(2) - (7)].n), (yyvsp[(4) - (7)].n), (yyvsp[(5) - (7)].n), (yyvsp[(6) - (7)].n));
          }
    break;

  case 109:
#line 786 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n));
          }
    break;

  case 110:
#line 790 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n));
          }
    break;

  case 111:
#line 793 "./pb-gram.y"
    {  
            if (decl->btype->len != 0 && base_ptype(decl->btype)->pclass == SCH)
              parse_error("schema declaration must specify only one instance");
            save_decl();
            clear_dtype();
          }
    break;

  case 112:
#line 800 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (7)].n), (yyvsp[(2) - (7)].n), (yyvsp[(4) - (7)].n), (yyvsp[(5) - (7)].n), (yyvsp[(6) - (7)].n));
          }
    break;

  case 120:
#line 819 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 121:
#line 822 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 123:
#line 829 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 126:
#line 839 "./pb-gram.y"
    { decl->qclass = CTQ; }
    break;

  case 127:
#line 840 "./pb-gram.y"
    { decl->qclass = VTQ; }
    break;

  case 128:
#line 845 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 129:
#line 848 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 130:
#line 851 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 131:
#line 854 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 133:
#line 861 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 134:
#line 864 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 135:
#line 867 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 136:
#line 873 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 137:
#line 876 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 138:
#line 879 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 140:
#line 886 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 141:
#line 889 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 142:
#line 896 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 143:
#line 899 "./pb-gram.y"
    {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], (yyvsp[(2) - (2)].n)->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", (yyvsp[(2) - (2)].n)->ident->name);
             i = e->ident;
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                 decl->eclass = OTH;
             (yyvsp[(2) - (2)].n)->ident->eclass = OTH; 
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 144:
#line 913 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 145:
#line 919 "./pb-gram.y"
    {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], (yyvsp[(1) - (1)].n)->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", (yyvsp[(1) - (1)].n)->ident->name);
             i = e->ident;
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                decl->eclass = OTH;
             /* Do not propigate type info. */
             (yyvsp[(1) - (1)].n)->ident->eclass = UNT; 
          }
    break;

  case 146:
#line 933 "./pb-gram.y"
    {  ENTRY *e;
             IDENT *i;
             e = symtab_lookup(symtab[OTH], (yyvsp[(2) - (2)].n)->ident->name);
             if (e == NULL)
               parse_error("%s is not a typedef name", (yyvsp[(2) - (2)].n)->ident->name);
             i = e->ident;
             assert(decl->qclass != UND);
             set_btype(copy_ctype(i->ctype));
             /* PREDATOR addition */
             if (i->eclass == CON)
                 decl->eclass = OTH;
             (yyvsp[(2) - (2)].n)->ident->eclass = OTH;
             /* Do not propigate type info. */
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 147:
#line 949 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 148:
#line 955 "./pb-gram.y"
    { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = TDF;
            decl->eclass = TDF;
          }
    break;

  case 149:
#line 961 "./pb-gram.y"
    { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = EXT;
            decl->eclass = OTH;
          }
    break;

  case 150:
#line 967 "./pb-gram.y"
    { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = STA;
            decl->eclass = OTH;
          }
    break;

  case 151:
#line 973 "./pb-gram.y"
    { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = AUT;
            decl->eclass = OTH;
          }
    break;

  case 152:
#line 979 "./pb-gram.y"
    { if (decl->sclass != UND)
              parse_error("multiple storage classes");
            decl->sclass = REG;
            decl->eclass = OTH;
          }
    break;

  case 153:
#line 985 "./pb-gram.y"
    {
          }
    break;

  case 154:
#line 990 "./pb-gram.y"
    { arithmetic_btype(UND, IN);  }
    break;

  case 155:
#line 991 "./pb-gram.y"
    { arithmetic_btype(UND, CHA); }
    break;

  case 156:
#line 992 "./pb-gram.y"
    { arithmetic_btype(UND, VCHA); }
    break;

  case 157:
#line 993 "./pb-gram.y"
    { arithmetic_btype(UND, SHO); }
    break;

  case 158:
#line 994 "./pb-gram.y"
    { arithmetic_btype(UND, FLO); }
    break;

  case 159:
#line 995 "./pb-gram.y"
    { arithmetic_btype(UND, DOU); }
    break;

  case 160:
#line 996 "./pb-gram.y"
    { arithmetic_btype(SIG, IN); }
    break;

  case 161:
#line 997 "./pb-gram.y"
    { arithmetic_btype(UNS, IN); }
    break;

  case 162:
#line 998 "./pb-gram.y"
    { arithmetic_btype(UND, VOI); }
    break;

  case 163:
#line 1003 "./pb-gram.y"
    { arithmetic_btype(UND, LON); }
    break;

  case 164:
#line 1004 "./pb-gram.y"
    { arithmetic_btype(UND, LLON); }
    break;

  case 165:
#line 1008 "./pb-gram.y"
    { arithmetic_btype(UND, LDOU); }
    break;

  case 166:
#line 1020 "./pb-gram.y"
    {
#if 0
             decl->btype = (yyvsp[(3) - (4)].n)->ident->ctype;
#else
             set_btype((yyvsp[(3) - (4)].n)->ident->ctype);
#endif
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 167:
#line 1029 "./pb-gram.y"
    {  /* decl->btype should already be properly set. */
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 168:
#line 1038 "./pb-gram.y"
    {  (yyval.n) = element_nonterm((yyvsp[(3) - (4)].n));
          }
    break;

  case 169:
#line 1045 "./pb-gram.y"
    {  pre_opt_cursor_declaration((yyvsp[(3) - (4)].n)); 
          }
    break;

  case 170:
#line 1048 "./pb-gram.y"
    {  NODE *n;
             post_opt_cursor_declaration((yyvsp[(3) - (7)].n));
             n = nonterm(UNT, NULL, 4, (yyvsp[(1) - (7)].n), (yyvsp[(2) - (7)].n), (yyvsp[(3) - (7)].n), (yyvsp[(4) - (7)].n));
             (yyval.n) = nonterm(UNT, NULL, 3, n, (yyvsp[(6) - (7)].n), (yyvsp[(7) - (7)].n));
          }
    break;

  case 171:
#line 1055 "./pb-gram.y"
    {  generic_cursor_declaration((yyvsp[(3) - (4)].n));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)); 
          }
    break;

  case 172:
#line 1060 "./pb-gram.y"
    {  pre_opt_compcurs_declaration();
          }
    break;

  case 173:
#line 1063 "./pb-gram.y"
    {  post_opt_compcurs_declaration((yyvsp[(3) - (9)].n), (yyvsp[(6) - (9)].n), (yyvsp[(8) - (9)].n));
             (yyval.n) = nonterm(UNT, NULL, 7, (yyvsp[(1) - (9)].n), (yyvsp[(2) - (9)].n), (yyvsp[(3) - (9)].n), (yyvsp[(4) - (9)].n), (yyvsp[(6) - (9)].n), (yyvsp[(7) - (9)].n), (yyvsp[(8) - (9)].n), (yyvsp[(9) - (9)].n));
          }
    break;

  case 174:
#line 1071 "./pb-gram.y"
    {  schema_container_declaration((yyvsp[(3) - (4)].n));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 175:
#line 1077 "./pb-gram.y"
    {  TE *te = typex_name_to_te((yyvsp[(6) - (6)].n)->ident->name);
             pre_typex_container_declaration((yyvsp[(3) - (6)].n));
             set_container_cctype_te(decl->btype->cctype, te);
          }
    break;

  case 176:
#line 1082 "./pb-gram.y"
    {  post_ddlhint_container_declaration((yyvsp[(6) - (8)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (8)].n), (yyvsp[(2) - (8)].n), (yyvsp[(3) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(5) - (8)].n), (yyvsp[(6) - (8)].n));
          }
    break;

  case 177:
#line 1087 "./pb-gram.y"
    {  generic_container_declaration((yyvsp[(3) - (4)].n));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)); 
          }
    break;

  case 179:
#line 1098 "./pb-gram.y"
    {  pre_typex_schema_declaration();
          }
    break;

  case 180:
#line 1101 "./pb-gram.y"
    {  pop_decl();
          }
    break;

  case 181:
#line 1104 "./pb-gram.y"
    {  post_typex_schema_declaration((yyvsp[(8) - (8)].n)->ident->name);
          }
    break;

  case 182:
#line 1107 "./pb-gram.y"
    {  
             assert(decl->typex_name == NULL);
#if 0
             post_ddlhint_schema_declaration((yyvsp[(8) - (10)].n)->ident->name);
#else
             decl->typex_name = copy_string((yyvsp[(8) - (10)].n)->ident->name);
#endif
             (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (10)].n), (yyvsp[(2) - (10)].n), (yyvsp[(4) - (10)].n), (yyvsp[(5) - (10)].n), (yyvsp[(7) - (10)].n), (yyvsp[(8) - (10)].n));
          }
    break;

  case 183:
#line 1120 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 184:
#line 1123 "./pb-gram.y"
    {  push_decl();
          }
    break;

  case 185:
#line 1126 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
             pop_decl();
          }
    break;

  case 186:
#line 1133 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 188:
#line 1140 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2,  (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 189:
#line 1143 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)); 
          }
    break;

  case 190:
#line 1149 "./pb-gram.y"
    {  predicate_opt_declaration(NULL);
             (yyval.n) = empty();
          }
    break;

  case 191:
#line 1153 "./pb-gram.y"
    {  predicate_opt_declaration((yyvsp[(2) - (2)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 192:
#line 1160 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 193:
#line 1163 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 194:
#line 1169 "./pb-gram.y"
    {  orderby_opt_action(0, NULL, NULL);
              (yyval.n) = empty();
           }
    break;

  case 195:
#line 1173 "./pb-gram.y"
    {  orderby_opt_action((yyvsp[(2) - (3)].i), NULL, (yyvsp[(3) - (3)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n),
                          terminal_string1(direction_string((yyvsp[(2) - (3)].i))),
                          (yyvsp[(3) - (3)].n));
          }
    break;

  case 196:
#line 1179 "./pb-gram.y"
    {  orderby_opt_action((yyvsp[(2) - (6)].i), (yyvsp[(4) - (6)].n)->ident->name, (yyvsp[(6) - (6)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (6)].n),
                          terminal_string1(direction_string((yyvsp[(2) - (6)].i))),
                          (yyvsp[(3) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n)); 
          }
    break;

  case 197:
#line 1188 "./pb-gram.y"
    {  /* I have intentionally made this 1 (rather than 0). */
             /* Making this 1 makes ascending the default.  That is:
                "orderby field" is equivalent to "orderby ascending field"
                I don't think that it makes sense to make 0 the default,
                But a reasonable alternative to this is to not accept
                the empty string as a legal direction, in which case:
                "orderby field" is an illegal orderby_opt. (JAT) */
             (yyval.i) = 1;
          }
    break;

  case 198:
#line 1198 "./pb-gram.y"
    {  (yyval.i) = 1;
          }
    break;

  case 199:
#line 1201 "./pb-gram.y"
    {  (yyval.i) = -1;
          }
    break;

  case 202:
#line 1212 "./pb-gram.y"
    {  /* Declaration of un-named aggregate. */
             unnamed_aggregate_declaration_action();
          }
    break;

  case 203:
#line 1216 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
             pop_decl();
          }
    break;

  case 204:
#line 1220 "./pb-gram.y"
    {  /* Declaration of named aggregate. */
             named_aggregate_declaration_action((yyvsp[(2) - (3)].n));
          }
    break;

  case 205:
#line 1224 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (6)].n), (yyvsp[(2) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n));
             pop_decl();
          }
    break;

  case 206:
#line 1228 "./pb-gram.y"
    {  /* Reference to aggregate */
             aggregate_reference_action((yyvsp[(2) - (2)].n));
             /* Do not propigate type info. */
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 207:
#line 1237 "./pb-gram.y"
    {
#if 0
            decl->btype = STRUCT_CTYPE;
#else
            set_btype(STRUCT_CTYPE);
#endif
          }
    break;

  case 208:
#line 1245 "./pb-gram.y"
    {
#if 0
            decl->btype = UNION_CTYPE;
#else
            set_btype(UNION_CTYPE);
#endif
           }
    break;

  case 210:
#line 1259 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 211:
#line 1265 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
            save_decl();
            clear_btype();
        }
    break;

  case 212:
#line 1270 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
            save_decl();
            clear_btype();
          }
    break;

  case 213:
#line 1278 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 214:
#line 1281 "./pb-gram.y"
    {  save_decl();
             clear_dtype();
          }
    break;

  case 215:
#line 1285 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 216:
#line 1291 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 217:
#line 1294 "./pb-gram.y"
    {  save_decl();
             clear_dtype();
          }
    break;

  case 218:
#line 1298 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 219:
#line 1304 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 221:
#line 1311 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 223:
#line 1318 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 225:
#line 1325 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, int_read_only_ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
            decl->supp = copy_ptree((yyvsp[(2) - (2)].n));
          }
    break;

  case 226:
#line 1332 "./pb-gram.y"
    {  /* Declaration of un-named enumeration. */
             unnamed_enum_declaration_action();
          }
    break;

  case 227:
#line 1336 "./pb-gram.y"
    {  pop_decl();
             decl->btype->ident->supp = copy_ptree((yyvsp[(4) - (5)].n));
             add_ident_to_symtab1(symtab[SUE], decl->btype->ident);
             clear_dtype();
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 228:
#line 1343 "./pb-gram.y"
    {  /* Declaration of named enumeration. */
             named_enum_declaration_action((yyvsp[(2) - (3)].n));
          }
    break;

  case 229:
#line 1347 "./pb-gram.y"
    {  pop_decl();
             decl->btype->ident->supp = copy_ptree((yyvsp[(5) - (6)].n));
             clear_dtype();
             (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (6)].n), (yyvsp[(2) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n));
          }
    break;

  case 230:
#line 1353 "./pb-gram.y"
    {  /* Reference to enumeration. */
             enum_reference_action((yyvsp[(2) - (2)].n));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 231:
#line 1361 "./pb-gram.y"
    {  IDENT *i;
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
             i = new_ident1(ENC, (yyvsp[(1) - (2)].n)->ident->name, int_read_only_ctype,
                            NULL, FALSE);
             add_ident_to_symtab1(symtab[OTH], i);
          }
    break;

  case 232:
#line 1368 "./pb-gram.y"
    {  IDENT *i;
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), comma(), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
             i = new_ident1(ENC, (yyvsp[(3) - (4)].n)->ident->name, int_read_only_ctype,
                            NULL, FALSE);
             add_ident_to_symtab1(symtab[OTH], i);
          }
    break;

  case 233:
#line 1378 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 234:
#line 1381 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 236:
#line 1388 "./pb-gram.y"
    {  save_decl();
             clear_btype(); /* Formerly: clear_dtype(); */
          }
    break;

  case 237:
#line 1392 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 239:
#line 1399 "./pb-gram.y"
    {  save_decl();
             /* This clear_btype is bad, eg, because it converts
                void foo (char(*)(), ...) to
                void foo (...) (JAT) */
             /* I think this has been fixed (JAT) */
             clear_btype(); /* Formerly: clear_dtype(); */
         }
    break;

  case 240:
#line 1407 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 242:
#line 1414 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 243:
#line 1417 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 244:
#line 1420 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 246:
#line 1424 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 247:
#line 1427 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 249:
#line 1431 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 250:
#line 1434 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 251:
#line 1437 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 253:
#line 1441 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 254:
#line 1444 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 255:
#line 1454 "./pb-gram.y"
    {  decl->name = copy_string((yyvsp[(1) - (1)].n)->ident->name);
             (yyvsp[(1) - (1)].n)->ident->eclass = OTH; 
          }
    break;

  case 256:
#line 1458 "./pb-gram.y"
    {  save_decl();
             clear_dtype();
          }
    break;

  case 257:
#line 1462 "./pb-gram.y"
    {  decl->name = copy_string((yyvsp[(4) - (4)].n)->ident->name);
             (yyvsp[(1) - (4)].n)->ident->eclass = OTH;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 258:
#line 1470 "./pb-gram.y"
    {  decl->name = copy_string((yyvsp[(1) - (1)].n)->ident->name);
          }
    break;

  case 259:
#line 1473 "./pb-gram.y"
    {  decl->name = copy_string((yyvsp[(1) - (1)].n)->ident->name);
          }
    break;

  case 261:
#line 1480 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 263:
#line 1484 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 264:
#line 1490 "./pb-gram.y"
    {  (yyval.n) = empty();
         }
    break;

  case 265:
#line 1493 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
            decl->initializer = copy_ptree((yyvsp[(2) - (2)].n));
         }
    break;

  case 266:
#line 1500 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 267:
#line 1502 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 270:
#line 1509 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 278:
#line 1529 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 279:
#line 1532 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (6)].n), (yyvsp[(2) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n));
          }
    break;

  case 280:
#line 1538 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 281:
#line 1541 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 282:
#line 1544 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 283:
#line 1547 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (6)].n), (yyvsp[(2) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n));
          }
    break;

  case 284:
#line 1553 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 287:
#line 1561 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 289:
#line 1568 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 290:
#line 1571 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 291:
#line 1583 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
             add_label_to_symtab((yyvsp[(1) - (2)].n)->ident->name);
          }
    break;

  case 292:
#line 1587 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 293:
#line 1589 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 294:
#line 1598 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 295:
#line 1600 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)); }
    break;

  case 296:
#line 1602 "./pb-gram.y"
    {  (yyval.n) = nonterm((yyvsp[(3) - (5)].n)->ident->eclass, (yyvsp[(3) - (5)].n)->ident->ctype,
                          3, (yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 297:
#line 1606 "./pb-gram.y"
    {  (yyval.n) = nonterm((yyvsp[(4) - (6)].n)->ident->eclass, (yyvsp[(4) - (6)].n)->ident->ctype,
                          4, (yyvsp[(1) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(6) - (6)].n));
          }
    break;

  case 298:
#line 1613 "./pb-gram.y"
    {  clear_decl(); /* decl->declared_but_unprinted = NULL. */
             push_scope(FALSE);
             (yyval.n) = empty();
         }
    break;

  case 299:
#line 1621 "./pb-gram.y"
    {  pop_scope();
             (yyval.n) = empty();
          }
    break;

  case 301:
#line 1629 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 303:
#line 1636 "./pb-gram.y"
    {
             (yyval.n) = nonterm((yyvsp[(2) - (2)].n)->ident->eclass, (yyvsp[(2) - (2)].n)->ident->ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 304:
#line 1643 "./pb-gram.y"
    {  (yyval.n) = nonterm(TYP, (yyvsp[(1) - (2)].n)->ident->ctype, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 305:
#line 1650 "./pb-gram.y"
    {  (yyvsp[(3) - (5)].n)->ident->ctype = int_read_only_ctype; /* boolean */
             (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), nl(), (yyvsp[(5) - (5)].n));
          }
    break;

  case 306:
#line 1654 "./pb-gram.y"
    {  (yyvsp[(3) - (7)].n)->ident->ctype = int_read_only_ctype; /* boolean */
             (yyval.n) = nonterm(UNT, NULL, 9, (yyvsp[(1) - (7)].n), (yyvsp[(2) - (7)].n), (yyvsp[(3) - (7)].n), (yyvsp[(4) - (7)].n), nl(), (yyvsp[(5) - (7)].n),
                         (yyvsp[(6) - (7)].n), nl(), (yyvsp[(7) - (7)].n));
          }
    break;

  case 307:
#line 1659 "./pb-gram.y"
    {  (yyvsp[(3) - (5)].n)->ident->ctype = int_read_only_ctype; /* int */
             (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 308:
#line 1666 "./pb-gram.y"
    {  (yyvsp[(3) - (5)].n)->ident->ctype = int_read_only_ctype; /* boolean */
             (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), nl(), (yyvsp[(5) - (5)].n));
          }
    break;

  case 309:
#line 1670 "./pb-gram.y"
    {  (yyvsp[(5) - (7)].n)->ident->ctype = int_read_only_ctype; /* boolean */
             (yyval.n) = nonterm(UNT, NULL, 7, (yyvsp[(1) - (7)].n), (yyvsp[(2) - (7)].n), (yyvsp[(3) - (7)].n), (yyvsp[(4) - (7)].n), (yyvsp[(5) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(7) - (7)].n));
          }
    break;

  case 310:
#line 1675 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 10, (yyvsp[(1) - (9)].n), (yyvsp[(2) - (9)].n), (yyvsp[(3) - (9)].n), (yyvsp[(4) - (9)].n), (yyvsp[(5) - (9)].n), (yyvsp[(6) - (9)].n), (yyvsp[(7) - (9)].n),
                          (yyvsp[(8) - (9)].n), nl(), (yyvsp[(9) - (9)].n));
          }
    break;

  case 311:
#line 1679 "./pb-gram.y"
    {  NODE *n = nonterm(UNT, NULL, 3, (yyvsp[(3) - (5)].n), comma(), (yyvsp[(5) - (5)].n));
             (yyval.n) = special_op_nonterm((yyvsp[(1) - (5)].n), n);
          }
    break;

  case 315:
#line 1692 "./pb-gram.y"
    {
             /* The target of the goto (constant_expression) can be
                identifier_or_typedef_name, which serves as an (implicit)
                declaration of the identifier_or_typedef_name as a label. */
             if ((yyvsp[(2) - (3)].n)->narg == 0)
               add_label_to_symtab((yyvsp[(2) - (3)].n)->ident->name);
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 316:
#line 1701 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 317:
#line 1704 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 318:
#line 1707 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 322:
#line 1723 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 323:
#line 1729 "./pb-gram.y"
    {  print_liner_pragma = TRUE;
             print_ptree((yyvsp[(1) - (1)].n));
             /* This would be a good place to delete_ptree($1)
                if we didn't have (automatic) garbage collection. (JAT) */
             print_liner_pragma = FALSE;
          }
    break;

  case 324:
#line 1736 "./pb-gram.y"
    {
             print_ptree((yyvsp[(1) - (1)].n));
             /* This would be a good place to delete_ptree($1)
                if we didn't have (automatic) garbage collection. (JAT) */
          }
    break;

  case 325:
#line 1742 "./pb-gram.y"
    {  warning(4, "incorrect definition or declaration--skipping to ';'");
             yyerrok;
          }
    break;

  case 326:
#line 1746 "./pb-gram.y"
    {  warning(4, "incorrect definition or declaration--skipping to '}'");
             yyerrok;
          }
    break;

  case 327:
#line 1756 "./pb-gram.y"
    { pre_function_definition_action(); 
          }
    break;

  case 328:
#line 1759 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), nl(), (yyvsp[(3) - (3)].n));
            post_function_definition_action();
          }
    break;

  case 329:
#line 1763 "./pb-gram.y"
    { pre_function_definition_action(); 
          }
    break;

  case 330:
#line 1766 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 331:
#line 1770 "./pb-gram.y"
    { pre_function_definition_action(); 
          }
    break;

  case 332:
#line 1773 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 333:
#line 1777 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 334:
#line 1780 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 335:
#line 1784 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 336:
#line 1787 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 337:
#line 1794 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 338:
#line 1797 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), nl(), (yyvsp[(3) - (3)].n));
            post_function_definition_action();
          }
    break;

  case 339:
#line 1801 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 340:
#line 1804 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 341:
#line 1808 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 342:
#line 1811 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 343:
#line 1815 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 344:
#line 1818 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 345:
#line 1822 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 346:
#line 1825 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), nl(), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 347:
#line 1832 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 348:
#line 1835 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), nl(), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
            post_function_definition_action();
          }
    break;

  case 349:
#line 1839 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 350:
#line 1842 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), nl(), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
            post_function_definition_action();
          }
    break;

  case 351:
#line 1846 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 352:
#line 1849 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), nl(), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
            post_function_definition_action();
          }
    break;

  case 353:
#line 1853 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 354:
#line 1856 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), nl(), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
            post_function_definition_action();
          }
    break;

  case 355:
#line 1860 "./pb-gram.y"
    { pre_function_definition_action();
          }
    break;

  case 356:
#line 1863 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), nl(), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
            post_function_definition_action();
          }
    break;

  case 357:
#line 1870 "./pb-gram.y"
    {  (yyval.n) = declarator_nonterm((yyvsp[(1) - (1)].n));
          }
    break;

  case 358:
#line 1873 "./pb-gram.y"
    {  (yyval.n) = declarator_nonterm((yyvsp[(1) - (1)].n));
          }
    break;

  case 361:
#line 1884 "./pb-gram.y"
    {  (yyvsp[(1) - (1)].n)->ident->eclass  =  OTH; 
             decl->name = copy_string((yyvsp[(1) - (1)].n)->ident->name);
          }
    break;

  case 362:
#line 1888 "./pb-gram.y"
    {  (yyvsp[(1) - (2)].n)->ident->eclass = OTH;
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
             decl->name = copy_string((yyvsp[(1) - (2)].n)->ident->name);
          }
    break;

  case 365:
#line 1901 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 366:
#line 1905 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 367:
#line 1914 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 368:
#line 1918 "./pb-gram.y"
    {(yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 370:
#line 1929 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 371:
#line 1935 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 5, (yyvsp[(1) - (5)].n), (yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
          }
    break;

  case 372:
#line 1941 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 373:
#line 1945 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 374:
#line 1954 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 375:
#line 1959 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 376:
#line 1963 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 377:
#line 1969 "./pb-gram.y"
    {   ENTRY *e;
              IDENT *i;
              e = symtab_lookup(symtab[OTH], (yyvsp[(1) - (1)].n)->ident->name);
              if (e == NULL)
                parse_error("%s is not a typedef name", (yyvsp[(1) - (1)].n)->ident->name);
              i = e->ident;
              if (i->eclass != OTH && i->eclass != TDF)
                parse_error("%s is not a typedef name", i->name);
              i->ctype = copy_ctype(decl->btype);
              decl->btype->ident = i->ctype->ident;
              /* PREDATOR addition */
              if (i->eclass == CON)
                decl->eclass = CON; /* Formerly: decl->eclass = CON */
              (yyvsp[(1) - (1)].n)->ident->eclass = OTH; 
          }
    break;

  case 378:
#line 1985 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 381:
#line 1996 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 382:
#line 1999 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 383:
#line 2005 "./pb-gram.y"
    {  (yyval.n) = empty();
          }
    break;

  case 384:
#line 2008 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 6, (yyvsp[(1) - (6)].n), (yyvsp[(2) - (6)].n), (yyvsp[(3) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n));
             decl->attribute = copy_ptree((yyval.n));
          }
    break;

  case 386:
#line 2016 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));  
          }
    break;

  case 389:
#line 2024 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 391:
#line 2031 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 392:
#line 2035 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 393:
#line 2044 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 394:
#line 2047 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 395:
#line 2051 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 396:
#line 2057 "./pb-gram.y"
    {  decl->name = copy_string((yyvsp[(1) - (1)].n)->ident->name);
             (yyvsp[(1) - (1)].n)->ident->eclass =  OTH;
#if 0
             (yyvsp[(1) - (1)].n)->ident->ctype = UNDEFINED_CTYPE;
#else
             (yyvsp[(1) - (1)].n)->ident->ctype = undefined_read_only_ctype;
#endif
          }
    break;

  case 397:
#line 2066 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 399:
#line 2073 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 400:
#line 2077 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 401:
#line 2086 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(3) - (4)].n)));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 402:
#line 2090 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 403:
#line 2094 "./pb-gram.y"
    {  (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 408:
#line 2107 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); 
          }
    break;

  case 409:
#line 2111 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(2) - (3)].n)));
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 410:
#line 2118 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(ARR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
          }
    break;

  case 411:
#line 2122 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(ARR, UND, copy_ptree((yyvsp[(2) - (3)].n))));
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 412:
#line 2126 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(ARR, UND, copy_ptree((yyvsp[(3) - (4)].n))));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 413:
#line 2133 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
          }
    break;

  case 414:
#line 2136 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)) ;
          }
    break;

  case 415:
#line 2142 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(PTR, UND, NULL));
             (yyval.n) = nonterm(UNT, NULL, 2, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)) ;
          }
    break;

  case 416:
#line 2146 "./pb-gram.y"
    {  assert(decl->qclass != UND);
             left_expand_decl_dtype(new_ptype(PTR, decl->qclass, NULL));
             decl->qclass = UND;
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)) ;
          }
    break;

  case 417:
#line 2155 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(2) - (3)].n)));
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 418:
#line 2159 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(2) - (3)].n)));
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 419:
#line 2163 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(2) - (3)].n)));
             (yyval.n) = nonterm(UNT, NULL, 3, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
          }
    break;

  case 420:
#line 2168 "./pb-gram.y"
    {  left_expand_decl_dtype(new_ptype(FUN, UND, (yyvsp[(2) - (4)].n)));
             (yyval.n) = nonterm(UNT, NULL, 4, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
          }
    break;

  case 421:
#line 2175 "./pb-gram.y"
    {  left_paren_action();
          }
    break;

  case 422:
#line 2181 "./pb-gram.y"
    {  right_paren_action();
          }
    break;


/* Line 1267 of yacc.c.  */
#line 5194 "y.tab.c"
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


#line 2185 "./pb-gram.y"


/*****************************************************************************/
/*                  End of Grammar.                                          */
/*****************************************************************************/

#if YYDEBUG
static void
yyprint (FILE *file, int type, YYSTYPE value)
{
  fprintf(file,"\nNode: ( %s )", value.n->ident->name);
}
#endif

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

