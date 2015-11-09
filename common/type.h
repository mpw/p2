/* $Id: type.h,v 45.1 1997/09/23 05:41:54 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Common type system declarations. */

#ifndef INCLUDE_TYPE_H
#define INCLUDE_TYPE_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdlib.h> /* size_t */
#include "op-id.h"  /* P2_MAX_OP_ID */
#include "util.h"   /* BOOLEAN */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

/* Fundamental constants. */

#define MAX_CTYPE_LEN    12   /* Max length of data type signature. */
#define MAX_NODE_ARG     12   /* Max children of parse tree node. */

#define MAX_SCOPE_DEPTH  25   /* Max depth of declaration (ie scope) stack. */

/* Max length of a compile-time layer string argument. */

#define ARG_STR_LEN 2000
#define MAX_PRED_LEN ARG_STR_LEN /* Max length of predicate (in chars). */

/* Funbody, i.e. op number of operation being expanded. */

#define MACRO_EXPAND_FUNBODY -1
#define FUNCALL_EXPAND_FUNBODY -2

/* Cursor and container Identifiers. */
/* These can be any value < 0. (JAT) */

#define GENERIC_CONT_ID -1
#define UNKNOWN_CONT_ID -2

#define GENERIC_CURS_ID -1
#define UNKNOWN_CURS_ID -2

/* The following counters should be initializable to any value > 0.
   recovery.xp assumes cursor_id > 0. */
/* Here, I have initialized these counters to values which I expect never
   to intersect, so that I can easily identify something about the type
   of an identifier from its id number.  Despite the fact that I expect
   these values never to intersect, the rest of P2 should be written so
   as to have predictable behavior if these counters do happen to
   intersect. (JAT) */

#define INIT_CURS_ID_COUNTER 1000
#define INIT_CONT_ID_COUNTER 2000
#define INIT_LOOP_ID_COUNTER 3000
#define INIT_OTHER_ID_COUNTER 4000

/* Labels. */

#define LABEL_NAME      "label"
#define EXIT_LABEL_NAME "exit_label"

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Common */

/* I liked these enumeration constants so much that I wanted to use
   them in several different enumerations, but unfortunately, gcc does
   not allow this. (JAT) */

/* When assign an enumeration constant to a value (eg FUN = TDF+1),
   I am doing it for a reason, do not change these assignments. (JAT) */

enum common {
  ERR = 0,              /* error = 0, auto initialized values = error. */
  UND = ERR+1,          /* undefined = lowest legal value.  */
  OTH,                  /* other */
  TDF,                  /* typedef */
  FUN = TDF+1,          /* function */
  CON,                  /* container */
  GCON,                 /* generic container */
  CUR,                  /* cursor */
  GCUR,                 /* generic cursor */
  KCUR,                 /* composite cursor */
  SCH,                  /* schema */
  STR,                  /* structure */
  VPR,                  /* a pointer to void (void *), will cast everything (BJG) */
  MAX_COMMON = VPR
};

/* Link type declarations. (DSB) */

typedef enum {
  AT_MOST_ONE = UND+1,
  ONE,
  MANY
} CARD;

typedef enum {
  TO_CHILD = UND+1,
  TO_PARENT,
  NO_PROPAGATE
} PROPAGATE;

/* Storage classes. */

typedef enum {
  AUT = TDF+1,          /* auto */
  EXT,                  /* extern */
  STA,                  /* static */
  REG,                  /* register */
  SPE                   /* special operation */
} SCLASS;

/* Classes of expressions. */
/* The first several of these are overloading classes (aka name spaces). */
/* There should be a symbol table per overloading class. */

typedef enum
{
  VAR = MAX_COMMON+1,   /* variable */
  ENC,                  /* enumeration constant */
  SUE,                  /* structure, union, or enumeration tag */
  MBR,                  /* structure or union member */
  MAX_SCOPED = MBR,
  LAB,                  /* statment label */
  MAX_OCLASS = LAB,
  TYP,                  /* typed, but not an identifier */
  MAX_TYPED = TYP,
  UNT,                  /* untyped, not an identifier */
  MAX_ECLASS = UNT
} ECLASS;

/* Classes of primitive data types. */

/* When you add an enum constant to this list, make sure you modify
   the numerous other places in the P2 source code that do case analysis
   on these enum constants,p eg:

     type matching routines in pb/type.c
     assert_ctype_vaild in common/ctype.c
     type printing routines in pb/debug.c

  (JAT) */

typedef enum
{
  MIN_PCLASS = MAX_COMMON+1,
  UNI  = MIN_PCLASS,    /* union */
  VOI,                  /* void */
#if 0
  CTQ,                  /* const type qualifier */
  VTQ,                  /* volatile type qualifier */
#endif
  ARR,                  /* array */
  PTR,                  /* pointer */
  CHA,                  /* char */
  VCHA = CHA+1,         /* variable length character string (P2 extension) */
  SHO  = VCHA+1,        /* short int */
  ENU  = SHO+1,         /* enumeration */
  IN   = ENU+1,         /* int */
  LON  = IN+1,          /* long int */
  LLON = LON+1,         /* long long int (GNU extension) */
  FLO  = LLON+1,        /* float */
  DOU  = FLO+1,         /* double */
  LDOU = DOU+1,         /* long double */
  MAX_PCLASS = LDOU
} PCLASS;

/* Classes of signs. */

typedef enum
{
  SIG = UND+1,          /* signed */
  UNS = SIG+1,          /* unsigned */
  MAX_UCLASS = UNS
} UCLASS;

/* Special operation argument classes. */
/* This enumeration should include a symbol for each of the types
assumable by the arguments to a special operation. */

typedef enum {
  MIN_ACLASS = MAX_COMMON+1,
  PAR = MIN_ACLASS,     /* Parse tree (aka pointer to NODE) */
  FIE,                  /* Field (aka pointer to char) */
  IDE,                  /* Identifier (aka IDENT) */
  EXP,                  /* Expression */
  LST                   /* Link state */
} ACLASS;

/* Type qualifier class */

typedef enum {
  CTQ = UND+1,          /* Constant type qualifier. */
  VTQ                   /* Volatile type qualifier. */
} QCLASS;

/* Operation list */

typedef struct {
  int                   i;
  char                  *op;
  char                  *procedure;
  struct ident_struct   *ident;         /* field ident */
} OP_LIST_TUPLE;

typedef struct {
  int                   size;
  OP_LIST_TUPLE         tuple[P2_MAX_OP_ID];
} OP_LIST;

/* Primitive type */

typedef struct {
  PCLASS                pclass;         /* Primitive class. */
  QCLASS                qclass;         /* Type qualifier class. */
  struct node_struct    *supp;          /* Array size or function prototype. */
} PTYPE;

/* Triplet of structure idents: cursor, container, transformed element. */
/* See container_declaration_ident3(). */

typedef struct {
  struct ident_struct   *cur;           /* cursor */
  struct ident_struct   *con;           /* container */
  struct ident_struct   *ele;           /* transformed element */
} IDENT3;

/* Signature type. */
/* Array of pointers to prinitive types. */
/* This should be a struct encapsulating len as well as array of ptype. (JAT) */

typedef PTYPE *STYPE[MAX_CTYPE_LEN];

/* Cursor and container type. */

typedef struct {
  void    *arg;                       /* curs arg */

  /* The following two fields just seem to cache information that can
     be computed from te: te_requires_indirect_only(), and
     te_requires_proceduralize_ref().  Should we get rid of them in
     order to reduce the size of cctype, and reduce wasted memory? (JAT) */
  BOOLEAN indirect_only;              /* change direct refs to indirect */
  BOOLEAN proceduralize_ref;          /* proceduralize ops w/ FIE param */

  IDENT3  *ident3;              
  struct  te_struct *te;
  char    *schema;                    /* schema instance (variable) name */
  char    *cont;                      /* container instance (variable) name */
  char    *cont_type;                 /* transformed cont struct (type) name */
  struct  ident_struct *orig_type;    /* original curs or cont struct */
  char    *orderby_field;             /* orderby key field name. */
  int     orderby_direction;          /* orderby direction. */
  char    *orderby_cursor;            /* orderby cursor name. */
  struct  cp_table_struct *cp_table;  /* cursor-predicate table. */
  char    *predicate;                 /* retrieval predicate */
  int     cost;                       /* retrieval cost */
  int     layer;                      /* retrieval layer id */
  int     retrieval_direction;        /* -1, 0, or 1 */
  int     cursor_id;                  /* state id of cursor */
  int     container_id;               /* state id of container */
  OP_LIST *op_list;
} CCTYPE;

/* Complete type. */

typedef struct ctype_struct {
  int                   len;          /* length of type signature */
  STYPE                 *stype;       /* type signature. */
  UCLASS                uclass;       /* signed or unsigned */
  struct ident_struct   *ident;       /* non-NULL iff STR or UNI */
  CCTYPE                *cctype;
} CTYPE;

/* Identifier. */

typedef struct ident_struct {
  char                  *name;        /* name */

  /* The following fields may be omitted if eclass == UNT. (JAT) */
  /* This is a hack to save memory. (JAT) */

  char                  *pname;       /* print name or NULL */
  ECLASS                eclass;       /* expression (overloading) class */
  CTYPE                 *ctype;       /* complete type */
  int                   scope;        /* scope in which symbol was declared */
  struct symlist_struct *members;     /* non-NULL iff SU */
  struct node_struct    *supp;        /* enumeration body or bit field size */
  struct node_struct    *attribute;   /* GNU __attribute__ */
  struct node_struct    *initializer; /* initializer */
  SCLASS                sclass;       /* storage class */
  BOOLEAN               defaulted;    /* true iff ctype defaulted to int() */
  BOOLEAN               forward;      /* true iff ident is forward reference */
} IDENT;

/* Symbol table entry */

typedef struct entry_struct {
  IDENT                 *ident;
  struct entry_struct   *next;
  struct entry_struct   *prev;
} ENTRY;

/* Symbol list. */

typedef struct symlist_struct {
  ENTRY                 *first;
  ENTRY                 *last;
} SYMLIST;

/* Symbol table. */

typedef struct {
  int                   size;
  int                   scope_depth;
  SYMLIST               ***table;
} SYMTAB;

/* Parse tree node */

typedef struct node_struct {
  IDENT                 *ident;
  int                   line_number;
  int                   narg;
  struct node_struct    *arg[MAX_NODE_ARG];
} NODE, *(*NODE_FUNC)();

/* Declaration */
/* If you add new fields to DECL, make sure to update one of
   pb/pb-type.c:clear_{dtype,btype,decl}. (JAT) */

typedef struct decl_struct {
  SCLASS  sclass;                  /* storage class */
  ECLASS  eclass;                  /* expression (overloading) class */  
  char    *name;                   /* name */
  char    *pname;                  /* print name */
  QCLASS  qclass;                  /* type qualifier class */
  CTYPE   *btype;                  /* basic type */
  CTYPE   *dtype;                  /* derrived type */
  SYMLIST **symlist;               /* Symbol list containing the decl. */
  SYMLIST *declared_but_unprinted; /* Declared but unprinted declarations. */
                                   /* Most symbols are added to this
                                      symbol list at the same time that they
                                      are added to a global symbol table,
                                      such as symlist[OTH] (JAT) */
  SYMLIST *declared_but_unprinted_labels; /* GNU addition: local labels */
  NODE    *verbatim_ptree;         /* Verbatim ptree. */
                                   /* The ptree (C code) generated by a
                                      cursor, container, or layer
                                      verbatum special operation. (JAT) */
  NODE    *supp;                   /* enumeration body or bit field size */
  NODE    *attribute;              /* GNU __attribute__ */
  NODE    *initializer;            /* initializer */
  char    *cont_name;              /* container name, referent of P2_default */
  char    *typex_name;             /* schema typex name */
  BOOLEAN saved;                   /* true iff ident saved to symbol table */
  NODE    *op_vec_ptree;           /* Operation vector ptree. */
                                   /* The ptree (C code) specifiying a
                                      cursor or container operation vector.
                                      (JAT) */
} DECL;

/* Virtual argument pointer. */
/* May be "void *" or "int *" on different machines (BJG). */

typedef int      *vptr;

/*****************************************************************************/
/*                  External declarations.                                   */
/*****************************************************************************/

extern SYMTAB  *symtab[MAX_OCLASS+1];

extern DECL *decl;
extern int scope;

extern int curs_id_counter; /* Zero is error, negative special value */
extern int cont_id_counter; /* Zero is error; negative special value */
extern int loop_id_counter;
extern int other_id_counter;

extern  BOOLEAN enable_continue_labels;

/*****************************************************************************/
/*                  Read only ctype optimization.                            */
/*****************************************************************************/

extern CTYPE *container_read_only_ctype;
extern CTYPE *generic_container_read_only_ctype;
extern CTYPE *cursor_read_only_ctype;
extern CTYPE *composite_cursor_read_only_ctype;
extern CTYPE *generic_cursor_read_only_ctype;
extern CTYPE *int_read_only_ctype;
extern CTYPE *float_read_only_ctype;
extern CTYPE *char_read_only_ctype;
#if 0
extern CTYPE *varchar_read_only_ctype;
#endif
extern CTYPE *schema_read_only_ctype;
extern CTYPE *string_read_only_ctype;
extern CTYPE *struct_read_only_ctype;
extern CTYPE *union_read_only_ctype;
extern CTYPE *void_read_only_ctype;
extern CTYPE *function_int_read_only_ctype;
extern CTYPE *function_void_read_only_ctype;
extern CTYPE *pointer_struct_read_only_ctype;
extern CTYPE *pointer_void_read_only_ctype;
extern CTYPE *pointer_composite_cursor_read_only_ctype;
extern CTYPE *pointer_container_read_only_ctype;
extern CTYPE *pointer_cursor_read_only_ctype;
extern CTYPE *pointer_vptr_read_only_ctype;
extern CTYPE *op_vec_read_only_ctype;
extern CTYPE *undefined_read_only_ctype;

/*****************************************************************************/
/*                  Standard ctypes.                                         */
/*****************************************************************************/

#define CHAR_CTYPE                     new_ctype(1, UND, CHA,  UND, NULL)
#if 0
#define VARCHAR_CTYPE                  new_ctype(1, UND, VCHA, UND, NULL)
#endif
#define COMPOSITE_CURSOR_CTYPE         new_ctype(1, UND, KCUR, UND, NULL)
#define CONTAINER_CTYPE                new_ctype(1, UND, CON,  UND, NULL)
#define CURSOR_CTYPE                   new_ctype(1, UND, CUR,  UND, NULL)
#define EMPTY_CTYPE                    new_ctype(0, UND)
#define ENUM_CTYPE                     new_ctype(1, UND, ENU,  UND, NULL)
#define FLOAT_CTYPE                    new_ctype(1, UND, FLO,  UND, NULL)
#define FUNCTION_INT_CTYPE             new_ctype(2, UND, FUN,  UND, NULL, \
                                                         IN,   UND, NULL)
#define FUNCTION_VOID_CTYPE            new_ctype(2, UND, FUN,  UND, NULL, \
                                                         VOI,  UND, NULL)
#define GENERIC_CONTAINER_CTYPE        new_ctype(2, UND, PTR,  UND, NULL, \
                                                         GCON, UND, NULL)
#define GENERIC_CURSOR_CTYPE           new_ctype(2, UND, PTR,  UND, NULL, \
                                                         GCUR, UND, NULL)
#define INT_CTYPE                      new_ctype(1, UND, IN,   UND, NULL)
#define POINTER_COMPOSITE_CURSOR_CTYPE new_ctype(2, UND, PTR,  UND, NULL, \
                                                         KCUR, UND, NULL)
#define POINTER_CONTAINER_CTYPE        new_ctype(2, UND, PTR,  UND, NULL, \
                                                         CON,  UND, NULL)
#define POINTER_CURSOR_CTYPE           new_ctype(2, UND, PTR,  UND, NULL, \
                                                         CUR,  UND, NULL)
#define POINTER_STRUCT_CTYPE           new_ctype(2, UND, PTR,  UND, NULL, \
                                                         STR,  UND, NULL)
#define POINTER_VOID_CTYPE             new_ctype(2, UND, PTR,  UND, NULL, \
                                                         VOI,  UND, NULL)
#define POINTER_VPTR_CTYPE             new_ctype(2, UND, PTR,  UND, NULL, \
                                                         VPR,  UND, NULL)
#define OP_VEC_CTYPE                   new_ctype(4, UND, PTR,  UND, NULL, \
                                                         PTR,  UND, NULL, \
                                                         FUN,  UND, NULL, \
                                                         IN,   UND, NULL)
#define SCHEMA_CTYPE                   new_ctype(1, UND, SCH,  UND, NULL)
#define STRING_CTYPE                   new_ctype(2, UND, ARR,  UND, NULL, \
                                                         CHA,  UND, NULL)
#define STRUCT_CTYPE                   new_ctype(1, UND, STR,  UND, NULL)
#define UNDEFINED_CTYPE                new_ctype(1, UND, UND,  UND, NULL)
#define UNION_CTYPE                    new_ctype(1, UND, UNI,  UND, NULL)
#define VOID_CTYPE                     new_ctype(1, UND, VOI,  UND, NULL)

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

BOOLEAN aggregate_ctype(const CTYPE *c);
BOOLEAN aggregate_or_aggregate_array_ctype(const CTYPE *c);
BOOLEAN aggregate_pclass(PCLASS pclass);
void    append(CTYPE *dest, const CTYPE *src);
void    assert_ctype_valid(const CTYPE *ctype);
void    assert_node_valid(const NODE *n);
void    assert_ptype_valid(const PTYPE *ptype);
PTYPE   *base_ptype(const CTYPE *ctype);
CTYPE   *binary_convert(const CTYPE *c1, const CTYPE *c2);
CTYPE   *copy_ctype(const CTYPE *src);
CTYPE   *copy_ctype1(const CTYPE *src, BOOLEAN deep);
BOOLEAN ctypematch(const CTYPE *c1, const CTYPE *c2);
BOOLEAN ctypematch1(const CTYPE *c1, const CTYPE *c2, BOOLEAN exact);
BOOLEAN direct_ctype(const CTYPE *c);
void    expand(CTYPE *c, const PTYPE *ptype);
BOOLEAN generic_pclass(PCLASS pclass);
int     getop(const char *name);
int     getindxop(int num);
void    init_type_system(void);
void    left_expand (CTYPE *c, const PTYPE *ptype);
void    left_expand_decl_dtype(const PTYPE *ptype);
CTYPE   *new_ctype(int len, UCLASS uclass, ...);
IDENT   *new_ident(ECLASS eclass, const char *name, const CTYPE *ctype,
                   const SYMLIST *members, BOOLEAN defaulted);
IDENT   *new_ident1(ECLASS eclass, const char *name, const CTYPE *ctype,
                    const SYMLIST *members, BOOLEAN defaulted);
char    *new_label_name(int counter, int id);
char    *new_exit_label_name(int counter);
PTYPE   *new_ptype(PCLASS pclass, QCLASS qclass, const NODE *supp);
NODE    *nonterm(ECLASS eclass, const CTYPE *ctype, int narg, ...);
BOOLEAN pclassmatch1(const CTYPE *c1, const int *i1, PCLASS p2);
BOOLEAN pclassmatch2(const CTYPE *c1, const int *i1, PCLASS p2, BOOLEAN exact);
BOOLEAN proceduralize_op(int i, const CTYPE *ctype);
BOOLEAN qclass_valid(QCLASS qclass);
BOOLEAN read_only_ctype(const CTYPE *c);
void    rplstr(char *format, char *target, char *copy, char *res);
size_t  sizeof_node(int narg);
size_t  sizeof_ident(ECLASS eclass);
BOOLEAN string_ctype(const CTYPE *c);
BOOLEAN structure_or_union_pclass(PCLASS pclass);
BOOLEAN te_requires_indirect_only(const struct te_struct *te);
BOOLEAN te_requires_op_vec(const struct te_struct *te);
BOOLEAN te_requires_kcur(const struct te_struct *te);
BOOLEAN te_requires_proceduralize_ref(const struct te_struct *te);
NODE    *terminal(ECLASS eclass, const char *name, const CTYPE *ctype);
NODE    *terminal1(ECLASS eclass, const char *name, const CTYPE *ctype);
NODE    *terminal_ident(const IDENT *ident);
NODE    *terminal_string(const char *string);
NODE    *terminal_string1(const char *string);
NODE    *terminal_vstring(const char *formal, ...);
IDENT   *xmalloc_ident(ECLASS eclass);
NODE    *xmalloc_node(int narg);

NODE    *arrow(void);
NODE    *colon(void);
NODE    *comma(void);
NODE    *dot(void);
NODE    *empty(void);
NODE    *equals(void);
NODE    *inc(void);
NODE    *dec(void);
NODE    *leftbrace(void);
NODE    *rightbrace(void);
NODE    *leftbracket(void);
NODE    *rightbracket(void);
NODE    *leftp(void);
NODE    *rightp(void);
NODE    *nl(void);
NODE    *semicolon(void);
NODE    *star(void);

#endif /* INCLUDE_TYPE_H */
