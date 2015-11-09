/* $Id: type.c,v 45.3 1997/09/20 03:42:24 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Common type system definitions. */

/* This file contains some of the definitions that were formerly made in
   type.c.  Specifically, this file contains only the type system
   definitions that are needed by xp (as well as pb).  By compiling with
   this file instead of the original type.c, xp is able define the
   routines it needs without defining alot of other routines that would
   result in many dependencies on definitions in other files.  Thus, xp
   is able to compile with this file by itself, without alot of the other
   pb source files. (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>       /* assert() */
#include <stdarg.h>       /* va_list */
#include <stddef.h>       /* offsetof() */
#include <stdio.h>        /* NULL */
#include <string.h>       /* strcmp() */

#include "error.h"        /* assertion_failed() */  
#include "io.h"           /* SPRINT_BUF_SIZE */
#include "op-tab.h"       /* op_tab */ 
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* MAX_OCLASS */
#include "xform.h"        /* TE, ANNOTE */
#include "xmalloc.h"      /* xmalloc(), xmalloc_atomic() */

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

int     scope; /* Current scope */
DECL    *decl; /* Current declaration */

/* Symbol table */

SYMTAB  *symtab[MAX_OCLASS+1];

/* I am assuming that the difference
   xxx_id_counter-INIT_XXX_ID_COUNTER is the number of xxx,
   or at least an upper bound on the number of xxx. (JAT) */

int curs_id_counter = INIT_CURS_ID_COUNTER;
int cont_id_counter = INIT_CONT_ID_COUNTER;
int loop_id_counter = INIT_LOOP_ID_COUNTER;
int other_id_counter = INIT_OTHER_ID_COUNTER;

BOOLEAN enable_continue_labels = FALSE;

/*****************************************************************************/
/*                  Read only ctype optimization.                            */
/*****************************************************************************/

CTYPE *container_read_only_ctype;
CTYPE *generic_container_read_only_ctype;
CTYPE *cursor_read_only_ctype;
CTYPE *composite_cursor_read_only_ctype;
CTYPE *generic_cursor_read_only_ctype;
CTYPE *int_read_only_ctype;
CTYPE *float_read_only_ctype;
CTYPE *char_read_only_ctype;
#if 0
CTYPE *varchar_read_only_ctype;
#endif
CTYPE *schema_read_only_ctype;
CTYPE *string_read_only_ctype;
CTYPE *struct_read_only_ctype;
CTYPE *union_read_only_ctype;
CTYPE *void_read_only_ctype;
CTYPE *function_int_read_only_ctype;
CTYPE *function_void_read_only_ctype;
CTYPE *pointer_struct_read_only_ctype;
CTYPE *pointer_void_read_only_ctype;
CTYPE *pointer_composite_cursor_read_only_ctype;
CTYPE *pointer_container_read_only_ctype;
CTYPE *pointer_cursor_read_only_ctype;
CTYPE *pointer_vptr_read_only_ctype;
CTYPE *op_vec_read_only_ctype;
CTYPE *undefined_read_only_ctype;

/*****************************************************************************/
/*                  sizeof variably sized structures.                        */
/*****************************************************************************/

size_t
sizeof_node (int narg)
{
  size_t size;
#ifndef NDEBUG
  size = sizeof(NODE);
#else /* NDEBUG */
  size = sizeof(NODE) - ((MAX_NODE_ARG-narg)*sizeof(NODE*));
#endif /* NDEBUG */
  return(size);
}

size_t
sizeof_ident (ECLASS eclass)
{
#if 1
  /* Allocate an entire IDENT struct:
       + Works.
       - Inefficient.
  */
  return(sizeof(IDENT));
#else
  /* Allocate only that fraction of an IDENT struct as we need:
     - Broken.
     + Efficient.
  */
  size_t size;

  switch (eclass)
  {
  case UNT:
    size = offsetof(IDENT, name) + sizeof(ECLASS);
    break;
  default:
    size = sizeof(IDENT);
    break;
  }
  return(size);
#endif
}

/*****************************************************************************/
/*                  Classes of pclass                                        */
/*****************************************************************************/

#ifndef NDEBUG

static BOOLEAN
base_pclass (PCLASS pclass)
{
  switch (pclass)
  {
    case UND:
    case CON:
    case GCON:
    case CUR:
    case GCUR:
    case KCUR:
    case SCH:
    case STR:
    case UNI:
    case VOI:
#if 0
    case CTQ:
    case VTQ:
#endif
    case CHA:
    case VCHA:
    case SHO:
    case ENU:
    case IN:
    case LON:
    case LLON:
    case FLO:
    case DOU:
    case LDOU:
    case VPR: 
      return(TRUE);
    default:
      return(FALSE);
  }
}

static BOOLEAN
derrived_pclass (PCLASS pclass)
{
  switch (pclass)
  {
    case UND:
    case FUN:
    case ARR:
    case PTR:
    case CTQ:
    case VTQ:
      return(TRUE);
    default:
      return(FALSE);
  }
}

#endif /* NDEBUG */

#if 0
inline static BOOLEAN
type_qualifier_pclass (PCLASS pclass)
{
  return(pclass == CTQ || pclass == VTQ);
}
#endif

/* Return TRUE if the given PCLASS can be used as an address,
   FALSE otherwise. */

static BOOLEAN
address_pclass (PCLASS pclass)
{
  switch (pclass) {
   case ARR:
   case PTR:
   case CHA:
   case VCHA:
   case SHO:
   case ENU:
   case IN:
   case LON:
   case LLON:
     return(TRUE);
   case UND:     
   case OTH:
   case TDF:
   case FUN:
   case VOI:
   case CON:
   case GCON:
   case CUR:
   case GCUR:
   case KCUR:
   case SCH:
   case STR:
   case UNI:
   case FLO:
   case DOU:
   case LDOU:
     return(FALSE);
   default:
#ifndef NDEBUG
     assertion_failed("illegal parameter value, pclass = %d", pclass);
#endif /* NDEBUG */
     return(FALSE);
  }
}

/* Return TRUE if the given PCLASS is arithmetic,
   FALSE otherwise. */

static BOOLEAN
arithmetic_pclass (PCLASS pclass)
{
  switch (pclass) {
   case ARR:
   case PTR:
   case CHA:
   case VCHA:
   case SHO:
   case ENU:
   case IN:
   case LON:
   case LLON:
   case FLO:
   case DOU:
   case LDOU:
     return(TRUE);
   case UND:     
   case OTH:
   case TDF:
   case FUN:
   case VOI:
   case CON:
   case GCON:
   case CUR:
   case GCUR:
   case KCUR:
   case SCH:
   case STR:
   case UNI:
     return(FALSE);
   default:
#ifndef NDEBUG
     assertion_failed("illegal parameter value, pclass = %d", pclass);
#endif /* NDEBUG */
     return(FALSE);
  }
}

static BOOLEAN
integral_pclass (PCLASS pclass)
{
  switch (pclass) {
   case CHA:
   case VCHA:
   case SHO:
   case ENU: 
   case IN: 
   case LON:
   case LLON:
    return(TRUE);
   case UND:
   case OTH:
   case TDF:
   case FUN:
   case VOI:
   case CON:
   case GCON:
   case CUR:
   case GCUR:
   case SCH:
   case STR: 
   case UNI:
   case ARR:
   case PTR:
   case FLO:
   case DOU:
   case LDOU:
    return(FALSE);
   default:
#ifndef NDEBUG
    assertion_failed("illegal parameter value, pclass = %d", pclass);
#endif /* NDEBUG */
    return(FALSE);
  }
}

BOOLEAN
generic_pclass (PCLASS pclass)
{
  return(pclass == GCON || pclass == GCUR);
}

BOOLEAN
structure_or_union_pclass (PCLASS pclass)
{
 return(/* Structure */
         pclass == STR
         /* Union */
      || pclass == UNI);
}

BOOLEAN
aggregate_pclass (PCLASS pclass)
{
  return(/* Structure or Union */
         structure_or_union_pclass(pclass)
         /* Container */
      || pclass == CON || pclass == GCON
         /* Cursor */
      || pclass == CUR || pclass == GCUR || pclass == KCUR
         /* Schema */
      || pclass == SCH
  );
}

/*****************************************************************************/
/*                  Assertions                                               */
/*****************************************************************************/

/* Make sure n is a valid node.  Specifically, recursively verify */
/* that n and all of the children n thinks it has are non-null. */

void
assert_node_valid (const NODE *n)
{
#ifndef NDEBUG
  if (n == NULL)
    assertion_failed("null node");
  if ((n->narg < 0) || (n->narg > MAX_NODE_ARG))
    assertion_failed("illegal node narg value = %d", n->narg);
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  {
    int i;
    /* This recursive part is very expensive. (JAT) */
    for (i = 0; i < n->narg; i++)
      assert_node_valid(n->arg[i]);
  }
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
}

BOOLEAN
qclass_valid (QCLASS qclass)
{
  return(qclass == UND || qclass == CTQ || qclass == VTQ);
}

void
assert_ptype_valid (const PTYPE *ptype)
{
#ifndef NDEBUG
  assert(ptype != NULL);
  assert(base_pclass(ptype->pclass) || derrived_pclass(ptype->pclass));
  assert(qclass_valid(ptype->qclass));
#endif /* NDEBUG */
}

#ifndef NDEBUG

static void
assert_stype_valid (const STYPE *stype, int len)
{
  PTYPE *ptype;
  PCLASS pclass;
  QCLASS qclass;
  int i;

  assert(stype != NULL);
  assert(len >= 0 && len < MAX_CTYPE_LEN);

  for (i = 0; i < len; i++)
  {
    ptype = (*stype)[i];
    assert(ptype != NULL);
    pclass = ptype->pclass;
    qclass = ptype->qclass;
    if (i == len-1)
      assert(base_pclass(pclass));
    else
      assert(derrived_pclass(pclass));
    assert(qclass_valid(qclass));
  }
}

#endif /* NDEBUG */

void
assert_ctype_valid (const CTYPE *ctype)
{
#ifndef NDEBUG
  if (ctype == NULL)
    assertion_failed("NULL ctype");
  else
  {
    UCLASS uclass = ctype->uclass;
    /* uclass */
    switch (uclass)
    {
      case UND:
      case SIG:
      case UNS:
        break;
      default:
        assertion_failed("invalid uclass, value = %d", uclass);
    }
    /* pclass */
    assert_stype_valid(ctype->stype, ctype->len);
  }
#endif /* NDEBUG */
}

BOOLEAN
read_only_ctype (const CTYPE *c)
{
  return(c == container_read_only_ctype
         || c == generic_container_read_only_ctype
         || c == cursor_read_only_ctype
         || c == composite_cursor_read_only_ctype
         || c == generic_cursor_read_only_ctype
         || c == int_read_only_ctype
         || c == float_read_only_ctype
         || c == char_read_only_ctype
#if 0
         || c == varchar_read_only_ctype
#endif
         || c == string_read_only_ctype
         || c == struct_read_only_ctype
         || c == union_read_only_ctype
         || c == void_read_only_ctype
         || c == function_int_read_only_ctype
         || c == function_void_read_only_ctype
         || c == pointer_struct_read_only_ctype
         || c == pointer_void_read_only_ctype
         || c == pointer_composite_cursor_read_only_ctype
         || c == pointer_container_read_only_ctype
         || c == pointer_cursor_read_only_ctype
         || c == pointer_vptr_read_only_ctype
         || c == op_vec_read_only_ctype
         || c == undefined_read_only_ctype
        );
}

/*****************************************************************************/
/*                  Initialize the type system                               */
/*****************************************************************************/

void
init_type_system (void)
{
  char_read_only_ctype = CHAR_CTYPE;
#if 0
  varchar_read_only_ctype = VARCHAR_CTYPE;
#endif
  composite_cursor_read_only_ctype = COMPOSITE_CURSOR_CTYPE;
  container_read_only_ctype = CONTAINER_CTYPE;
  cursor_read_only_ctype = CURSOR_CTYPE;
  float_read_only_ctype = FLOAT_CTYPE;
  function_int_read_only_ctype = FUNCTION_INT_CTYPE;
  function_void_read_only_ctype = FUNCTION_VOID_CTYPE;
  generic_container_read_only_ctype = GENERIC_CONTAINER_CTYPE;
  generic_cursor_read_only_ctype = GENERIC_CURSOR_CTYPE;
  int_read_only_ctype = INT_CTYPE;
  op_vec_read_only_ctype = OP_VEC_CTYPE;
  pointer_composite_cursor_read_only_ctype = POINTER_COMPOSITE_CURSOR_CTYPE;
  pointer_container_read_only_ctype = POINTER_CONTAINER_CTYPE;
  pointer_cursor_read_only_ctype = POINTER_CURSOR_CTYPE;
  pointer_struct_read_only_ctype = POINTER_STRUCT_CTYPE;
  pointer_void_read_only_ctype = POINTER_VOID_CTYPE;
  pointer_vptr_read_only_ctype = POINTER_VPTR_CTYPE;
  schema_read_only_ctype = SCHEMA_CTYPE;
  string_read_only_ctype = STRING_CTYPE;
  struct_read_only_ctype = STRUCT_CTYPE;
  undefined_read_only_ctype = UNDEFINED_CTYPE;
  union_read_only_ctype = UNION_CTYPE;
  void_read_only_ctype = VOID_CTYPE;

#ifndef NDEBUG
  assert_ctype_valid(char_read_only_ctype);
#if 0
  assert_ctype_valid(varchar_read_only_ctype);
#endif
  assert_ctype_valid(composite_cursor_read_only_ctype);
  assert_ctype_valid(container_read_only_ctype);
  assert_ctype_valid(cursor_read_only_ctype);
  assert_ctype_valid(float_read_only_ctype);
  assert_ctype_valid(function_int_read_only_ctype);
  assert_ctype_valid(function_void_read_only_ctype);
  assert_ctype_valid(generic_container_read_only_ctype);
  assert_ctype_valid(generic_cursor_read_only_ctype);
  assert_ctype_valid(int_read_only_ctype);
  assert_ctype_valid(op_vec_read_only_ctype);
  assert_ctype_valid(pointer_composite_cursor_read_only_ctype);
  assert_ctype_valid(pointer_container_read_only_ctype);
  assert_ctype_valid(pointer_cursor_read_only_ctype);
  assert_ctype_valid(pointer_struct_read_only_ctype);
  assert_ctype_valid(pointer_void_read_only_ctype);
  assert_ctype_valid(pointer_vptr_read_only_ctype);
  assert_ctype_valid(schema_read_only_ctype);
  assert_ctype_valid(string_read_only_ctype);
  assert_ctype_valid(struct_read_only_ctype);
  assert_ctype_valid(undefined_read_only_ctype);
  assert_ctype_valid(union_read_only_ctype);
  assert_ctype_valid(void_read_only_ctype);
#endif /* NDEBUG */
}

/*****************************************************************************/
/*                  New label name.                                          */
/*****************************************************************************/

char *
new_label_name (int counter, int id)
{
  char label[MAX_IDENT_LEN+25];
  sprintf(label, "P2_%s_counter%d_id%d", LABEL_NAME, counter, id);
  return(copy_string(label));
}

char *
new_exit_label_name (int counter)
{
  char exit_label[MAX_IDENT_LEN+25];
  sprintf(exit_label, "P2_%s_counter%d", EXIT_LABEL_NAME, counter);
  return(copy_string(exit_label));
}

/*****************************************************************************/
/*                  Base ptype                                               */
/*****************************************************************************/

PTYPE *
base_ptype (const CTYPE *ctype)
{
  PTYPE *ptype;
  assert(ctype != NULL);
  ptype = (*(ctype)->stype)[(ctype)->len-1]; 
  assert_ptype_valid(ptype);
  return(ptype);
}

/*****************************************************************************/
/*                  Manipulate ctypes                                        */
/*****************************************************************************/

/* Shift c to the left, and add ptype to the *right* (ie zero-th
   position) of c. */

void
expand (CTYPE *c, const PTYPE *ptype)
{
  int i;

#ifndef NDEBUG
  if (read_only_ctype(c))
    assertion_failed("read only ctype passed to expand");
#endif /* NDEBUG */

  /* Shift c left */
  for (i = c->len; i > 0; i--)
    (*c->stype)[i] = (*c->stype)[i-1];
  c->len++;

  /* Set (*c->stype)[0] to ptype */
  /* Explicit cast is necessary, because assignment discards const. */
  (*c->stype)[0] = (PTYPE *) ptype;
}

void
append (CTYPE *dest, const CTYPE *src)
{
  int i, j;

  i = src->len;
  for (j = i; j > 0; j--)
    expand(dest, (*src->stype)[j-1]);
}

/* Append ptype to the *left* (ie len-th position) of c
   (the opposite of expand) */
/* Note: This routine is called from xp_gram.y */

void
left_expand (CTYPE *c, const PTYPE *ptype)
{
  int len = c->len;

  assert(len >= 0 && len < MAX_CTYPE_LEN);
  assert(!read_only_ctype(c));
  assert_ptype_valid(ptype);

  if (len == MAX_CTYPE_LEN)
    parse_error("type length overflow");
  /* Explicit cast is necessary, because assignment discards const. */
  (*c->stype)[len] = (PTYPE *) ptype;
  c->len++;
}

/* Add ptype to the *left* (ie len-th position) of decl->dtype. */

void
left_expand_decl_dtype (const PTYPE *ptype)
{
  left_expand(decl->dtype, ptype);
}

/*****************************************************************************/
/*                  xmalloc node and ident.                                  */
/*****************************************************************************/

/* xmalloc node.  Given narg, allocate exactly as much memory as
   necessary for a node with narg children. */

NODE *
xmalloc_node (int narg)
{
  const size_t size = sizeof_node(narg);
  NODE *n;

#ifndef NDEBUG
  if (narg < 0 || narg > MAX_NODE_ARG)
    assertion_failed("illegal parameter value, narg = %d", narg);
#endif /* NDEBUG */

#if XMALLOC_DEBUG
  {
    char comment_string[10];
    sprintf(comment_string, "NODE%d", size);
    n = (NODE *) xmalloc1(size, comment_string);
  }
#else
  n = (NODE *) xmalloc(size);
#endif

  n->line_number = original_line_number;
  n->narg = narg;
  return(n);
}

IDENT *
xmalloc_ident (ECLASS eclass)
{
  const size_t size = sizeof_ident(eclass);
  IDENT *i;

#ifndef NDEBUG
  if (eclass < UND || eclass > MAX_ECLASS)
    assertion_failed("illegal parameter value, eclass = %d", eclass);
#endif /* NDEBUG */

#if XMALLOC_DEBUG
  {
    char comment_string[10];
    sprintf(comment_string, "IDENT%d", size);
    i = (IDENT *) xmalloc1(size, comment_string);
  }
#else /* XMALLOC_DEBUG */
  i = (IDENT *) xmalloc(size);
#endif /* XMALLOC_DEBUG */

  return(i);
}

/*****************************************************************************/
/*                  Create various types of structures.                      */
/*****************************************************************************/

PTYPE *
new_ptype (PCLASS pclass, QCLASS qclass, const NODE *s)
{
  PTYPE *ptype;

  ptype = (PTYPE *) xmalloc(sizeof(PTYPE));
  assert(pclass >= UND && pclass <= MAX_PCLASS);
  ptype->pclass = pclass;
  ptype->qclass = qclass;
  /* Explicit cast is necessary, because assignment discards const. */
  ptype->supp = (NODE *) s;
  return(ptype);
}

/* Create a new ctype. */
/* Takes a uclass followed by a variable number of triples:
     ( pclass, qclass, NODE* ) */

CTYPE *
new_ctype (int len, UCLASS uclass, ...)
{
  CTYPE   *c;
  PCLASS  pclass;
  QCLASS  qclass;
  NODE    *supp;
  int     i;
  va_list ap;

  assert(uclass >= UND && uclass <= MAX_UCLASS);
  assert(len >= 0 && len <= MAX_CTYPE_LEN);
  c = (CTYPE *) xmalloc_object(CTYPE);

  memset((void *) c, 0, sizeof(CTYPE));

  c->len = len;
  c->stype = (STYPE *) xmalloc(sizeof(STYPE));
  c->uclass = uclass;

  va_start(ap, uclass);
  for (i = 0; i < len; i++) {
    pclass = va_arg(ap, PCLASS);
    assert(pclass >= UND && pclass <= MAX_PCLASS);
    qclass = va_arg(ap, QCLASS);
    assert(qclass_valid(qclass));
    supp = va_arg(ap, NODE*);
    (*c->stype)[i] = new_ptype(pclass, qclass, supp);
  }

#ifndef NDEBUG
  assert_ctype_valid(c);
#endif /* NDEBUG */

  va_end(ap);
  return(c);
}

/* Create a new ident containing the given data. */
/* Does not add the new ident to the symbol table. */

/* Do not copy name.  This is an optimization.
   Only call this routine if you are sure that name
     (1) is not alocated on the stack and
     (2) will not be modified. (JAT) */

IDENT *
new_ident1 (ECLASS eclass, const char *name, const CTYPE *ctype,
            const SYMLIST *members, BOOLEAN defaulted)
{
  IDENT *i;

  i = xmalloc_ident(eclass);

  /* Explicit cast is necessary, because assignment discards const. */
  i->name = (char *) name;
  i->pname = NULL;
  i->eclass = eclass;
  /* Explicit cast is necessary, because assignment discards const. */
  i->ctype = (CTYPE *) ctype;

  if (eclass != UNT) {
    i->scope = scope;
    /* Explicit cast is necessary, because assignment discards const. */
    i->members = (SYMLIST *) members;
    i->supp = NULL;
    i->attribute = NULL;
    i->initializer = NULL;
    i->sclass = UND;
    i->defaulted = defaulted;
    i->forward = FALSE;
  }

#ifndef NDEBUG
  else /* eclass == UNT */
    if (ctype != NULL || members != NULL || defaulted )
      assertion_failed("eclass == UNT, but other information is non-NULL");
#endif /* NDEBUG */

  return(i);
}

/* Copy name. */

IDENT *
new_ident (ECLASS eclass, const char *name, const CTYPE *ctype,
           const SYMLIST *members, BOOLEAN defaulted)
{
  /* This copy shouldn't be necessary.  Ideally, the caller should
     be smart enough to copy name if it is allocated on the stack, but in
     practice we cannot depend on the caller doing this (JAT).
     Thus, *must* function correctly when name is allocated on the stack. */

  return(new_ident1(eclass, copy_string(name), ctype, members, defaulted));
}

/*****************************************************************************/
/*                  Deep copies                                              */
/*****************************************************************************/

inline static PTYPE *
copy_ptype (const PTYPE *src)
{
  PTYPE *dest;

  if (src == NULL)
    return(NULL);
  dest = (PTYPE *) xmalloc(sizeof(PTYPE));
  dest->pclass = src->pclass;
  dest->qclass = src->qclass;
  dest->supp = src->supp;
  return(dest);
}

inline static STYPE *
copy_stype (int len, const STYPE *src)
{
  STYPE *dest;
  int i;

  if (src == NULL)
    return(NULL);
  dest = (STYPE *) xmalloc(sizeof(STYPE));
  for (i = 0; i < len; i++)
    (*dest)[i] = copy_ptype((*src)[i]);
  return(dest);
}

CTYPE *
copy_ctype1 (const CTYPE *src, BOOLEAN deep)
{
  CTYPE *dest;

  if (src == NULL)
    return(NULL);
  dest = (CTYPE *) xmalloc_object(CTYPE);
  memcpy((char *) dest, (char *) src, sizeof(CTYPE));
  if (deep)
    dest->stype = copy_stype(src->len, src->stype);
  return(dest);
}

CTYPE *
copy_ctype (const CTYPE *src)
{
  return(copy_ctype1(src, TRUE));
}

/*****************************************************************************/
/*                  Terminal                                                 */
/*****************************************************************************/

/* If the terminal/nonterm you are allocating will ever have a type,
   then pass eclass == UNT (untyped).  Otherwise, pass eclass == TYP
   (typed).  A typed terminal/nonterm is much larger than untyped,
   but if you ever try to read or write the type of an untyped
   terminal/nonterm you will get a segmentation violation.  Thus, it is
   important to correctly specify this argument.  As a rule-of-thumb,
   an expression has a type, whereas a declaration does not. (JAT) */

/* Do not copy name. */

NODE *
terminal1 (ECLASS eclass, const char *name, const CTYPE *ctype)
{
  NODE *n = xmalloc_node(0);
  n->ident = new_ident1(eclass, name, ctype, NULL, FALSE);
  return n;
}

NODE *
terminal_string1 (const char *string)
{
  NODE *n = terminal1(UNT, string, NULL);
  return n;
}
    
/* Copy name. */

NODE *
terminal (ECLASS eclass, const char *name, const CTYPE *ctype)
{
  NODE *n = terminal1(eclass, copy_string(name), ctype);
  return n;
}

NODE *
terminal_string (const char *string)
{
  NODE *n = terminal_string1(copy_string(string));
  return n;
}
    
NODE *
terminal_vstring (const char *format, ...)
{
  va_list args;
  char    line[SPRINT_BUF_SIZE];
  
  va_start(args, format);
  vsprintf(line, format, args);
  va_end(args);
#ifndef NDEBUG
#ifndef P2_NEDEBUG
  /* Expensive assertion. */
  if (strlen(line) > SPRINT_BUF_SIZE)
    assertion_failed("line too long");
#endif /* P2_NEDEBUG */
#endif /* NDEBUG */
  return(terminal_string(line));
}

/* Terminal ident. */

NODE *
terminal_ident (const IDENT *ident)
{
  NODE *n = xmalloc_node(0);
  /* Explicit cast is necessary, because assignment discards const. */
  n->ident = (IDENT *) ident;
  return n;
}

/*****************************************************************************/
/*                  Named symbol terminals                                   */
/*****************************************************************************/

NODE *arrow (void)            { return(terminal_string1("->")); }
NODE *colon (void)            { return(terminal_string1(":"));  }
NODE *comma (void)            { return(terminal_string1(","));  }
NODE *dot (void)              { return(terminal_string1("."));  }
NODE *empty (void)            { return(terminal_string1(""));   }
NODE *equals (void)           { return(terminal_string1("="));  }
NODE *inc (void)              { return(terminal_string1("++")); }
NODE *dec (void)              { return(terminal_string1("--")); }
NODE *leftbrace (void)        { return(terminal_string1("{"));  }
NODE *rightbrace (void)       { return(terminal_string1("}"));  }
NODE *leftbracket (void)      { return(terminal_string1("["));  }
NODE *rightbracket (void)     { return(terminal_string1("]"));  }
NODE *leftp (void)            { return(terminal_string1("("));  }
NODE *rightp (void)           { return(terminal_string1(")"));  }
NODE *nl (void)               { return(terminal_string1("\n")); }
NODE *semicolon (void)        { return(terminal_string1(";"));  }
NODE *star (void)             { return(terminal_string1("*"));  }

/*****************************************************************************/
/*                  Non-terminal                                             */
/*****************************************************************************/

/* See comments for terminal. (JAT) */

NODE *
nonterm (ECLASS eclass, const CTYPE *ctype, int narg, ...)
{
  /* We need the eclass argument.  We can't just assume that if
     ctype == NULL then eclass == UNT, because sometimes we
     call nonterm with ctype == NULL, and then later add a ctype.
     (JAT) */

  va_list ap;
  NODE    *parent, *child;
  int     n;
  int     i;

  /* Count number of non-NULL arguments. */
  parent = NULL;
  n = 0;
  va_start(ap, narg);
  for (i = 0; i < narg; i++) {
    child = va_arg(ap, NODE*);
    if (child != NULL) {
      parent = child;
      n++;
    }
  }
  va_end(ap);

  if (n > 1) {

#ifndef NDEBUG
    if (n < 1 || n > MAX_NODE_ARG)
      assertion_failed("illegal number of node children %d", n);
    if (eclass == UNT && ctype != NULL)
      assertion_failed("eclass == UNT, but ctype is non-NULL");
#endif /* NDEBUG */

    parent = xmalloc_node(n);
    parent->ident = new_ident1(eclass, "", ctype, NULL, FALSE);
    parent->narg = n;

    i = 0;
    va_start(ap, narg);
    while (i < n) {
      /* Allow NULL arguments. This makes things simpler for the caller. */
      /* If an argument is NULL, do not add it as a child of the parent node */
      child = va_arg(ap, NODE*);
      if (child != NULL) {
#ifndef NDEBUG
        assert_node_valid(child);
#endif /* NDEBUG */
        parent->arg[i++] = child;
      }
    }
    va_end(ap);
  }

  return(parent);
}

/*****************************************************************************/
/*                  Layer name tests                                         */
/*****************************************************************************/

/* This routine returns TRUE iff a type expression te contains a
   partition layer, and thus, in order to work properly with generics,
   the reference special operation must be proceduralized. */

BOOLEAN
te_requires_proceduralize_ref (const TE *te)
{
#ifndef NDEBUG
  /* Make sure te->requires_proceduralize_ref is initialized. */
  if (te->requires_proceduralize_ref == -1)
    assertion_failed("te->requires_proceduralize_ref un-initialized");
#endif /* NDEBUG */

  return(te->requires_proceduralize_ref);
}

/* This routine returns TRUE iff a type expression te contains a
   persistence layer, and thus, all cursor references must be
   indirect. */

BOOLEAN
te_requires_indirect_only (const TE *te)
{
#ifndef NDEBUG
  /* Make sure te->requires_indirect_only is initialized. */
  if (te->requires_indirect_only == -1)
    assertion_failed("te->requires_indirect_only un-initialized");
#endif /* NDEBUG */

  return(te->requires_indirect_only);
}

/* This routine returns TRUE iff a type expression te requires an
   operation vector. */

BOOLEAN
te_requires_op_vec (const TE *te)
{
#ifndef NDEBUG
  /* Make sure te->requires_op_vec is initialized. */
  if (te->requires_op_vec == -1)
    assertion_failed("te->requires_op_vec un-initialized");
#endif /* NDEBUG */

  return(te->requires_op_vec);
}

/* This routine returns TRUE iff a type expression te requires that
   the _kcur field be added to composite cursor member cursors. */

BOOLEAN
te_requires_kcur (const TE *te)
{
#ifndef NDEBUG
  /* Make sure te->requires_kcur is initialized. */
  if (te->requires_kcur == -1)
    assertion_failed("te->requires_kcur un-initialized");
#endif /* NDEBUG */

  return(te->requires_kcur);
}

/*****************************************************************************/
/*                  Operation list                                           */
/*****************************************************************************/

/* Return TRUE iff the given operation should be proceduralized. */

BOOLEAN
proceduralize_op (int i, const CTYPE *ctype)
{
  return(
    /* Op is proceduralizable. */
    op_tab[i].proceduralize

#if 1
    /* Type expression is NULL, requires an operation vector
       or requires proceduralization of container modification operations,
       and op is a container modification operation. */

    && (ctype == NULL
        || ctype->cctype == NULL
        || ctype->cctype->te == NULL
        || te_requires_op_vec(ctype->cctype->te))
#endif

    /* Either op is not a ref, or proceduralize_ref is TRUE. */
    /* That is, only proceduralize a ref if proceduralize_ref is TRUE. (JAT) */
    && (!strstr(op_tab[i].name, "ref")
        || (ctype != NULL
            && ctype->cctype != NULL
            && ctype->cctype->proceduralize_ref))
 );
}

/* Return the index in op_tab given the operation number. 
   They're not the same. (BJG) */

int
getindxop (int num)
{ 
  int q;
  for(q=0; op_tab[q].op_num; q++) { 
    if (op_tab[q].op_num == num)
      return(q);
  }
  return(-1);
}

/* Return operation number for a given name. */

int
getop (const char *name)
{
  OP_DESC *q;
  for(q=op_tab; q->op_num; q++) { 
    if (!strcmp(q->name,name))
      return(q->op_num);
  }
#ifndef NDEBUG
  assertion_failed("procedure name %s not found", name);
#endif /* NDEBUG */
  return(-1);
}

/*****************************************************************************/
/*                  Type matching                                            */
/*****************************************************************************/

/* Return TRUE iff c1 and c2 are compatible. */

BOOLEAN
pclassmatch2 (const CTYPE *c1, const int *i1, PCLASS p2, BOOLEAN exact)
{
  PCLASS p1;

#ifndef NDEBUG
  assert_ctype_valid(c1);
  assert((*i1) <= c1->len);
#endif /* NDEBUG */

  /* An empty ctype doesn't match any pclass. (JAT) */
  if (c1->len == 0)
    return(FALSE);

#if 0
  while (type_qualifier_pclass((*c1->stype)[*i1]->pclass))
  {
    (*i1)++;
    assert((*i1) <= c1->len);
  }
#endif

  p1 = (*c1->stype)[*i1]->pclass;
  return((p1 == p2)
#if 0
         || (container_pclass(p1) && container_pclass(p2))
         || (cursor_pclass(p1) && cursor_pclass(p2))
#endif
         || (address_pclass(p1) && address_pclass(p2))
         || (arithmetic_pclass(p1) && arithmetic_pclass(p2))
         /* Structure and Union match iff exact is FALSE. */
         || (!exact
             && structure_or_union_pclass(p1)
             && structure_or_union_pclass(p2))
         );
}

BOOLEAN
pclassmatch1 (const CTYPE *c1, const int *i1, PCLASS p2)
{
  return(pclassmatch2(c1, i1, p2, TRUE));
}

inline static BOOLEAN
pclassmatch (const CTYPE *c1, const int *i1, const CTYPE *c2, const int *i2)
{
  PCLASS p2;

#ifndef NDEBUG
  assert_ctype_valid(c1);
  assert_ctype_valid(c2);
  assert((*i1) <= c1->len);
  assert((*i2) <= c2->len);
#endif /* NDEBUG */

  /* An empty ctype matches only another ctype. (JAT) */
  if (c1->len == 0 || c2->len == 0)
    return(c1->len == c2->len);

#if 0
  while (type_qualifier_pclass((*c2->stype)[*i2]->pclass)) {
    (*i2)++;
    assert((*i2) <= c2->len);
  }
#endif
  p2 = (*c2->stype)[*i2]->pclass;
  return(pclassmatch1(c1, i1, p2));
}

/* Return TRUE iff c1 and c2 are compatible. */

BOOLEAN
ctypematch1 (const CTYPE *c1, const CTYPE *c2, BOOLEAN exact) 
{
  int i1 = 0;
  int i2 = 0;
  
#ifndef NDEBUG
  assert_ctype_valid(c1);
  assert_ctype_valid(c2);
#endif /* NDEBUG */

  if (c1 == NULL)
    return(c2 == NULL);
  if (c2 == NULL)
    return(FALSE);
  
  while (i1 < c1->len && i2 < c2->len) {
    if (!pclassmatch(c1, &i1, c2, &i2))
      return(FALSE);
    i1++;
    i2++;
  }
  return(!(exact && (i1 != c1->len || i2 != c2->len)));
}

BOOLEAN
ctypematch (const CTYPE *c1, const CTYPE *c2) 
{
  int i1 = 0;
  int i2 = 0;

#ifndef NDEBUG
  assert_ctype_valid(c1);
  assert_ctype_valid(c2);
#endif /* NDEBUG */

#if 1
  /* Special case, pointer to void matches any pointer. */
  if ((pclassmatch1(c1, &i1, PTR)
       && ctypematch1(c2, pointer_void_read_only_ctype, TRUE))
      || (pclassmatch1(c2, &i2, PTR)
          && ctypematch1(c1, pointer_void_read_only_ctype, TRUE)))
    return(TRUE);
#endif

  return(ctypematch1(c1, c2, FALSE));
}

/* Binary conversion */

CTYPE *
binary_convert (const CTYPE *c1, const CTYPE *c2)
{
  const PCLASS p1 = base_ptype(c1)->pclass;
  const PCLASS p2 = base_ptype(c2)->pclass;
  CTYPE *c;

#ifndef NDEBUG
  assert_ctype_valid(c1);
  assert_ctype_valid(c2);
#endif /* NDEBUG */

  if (c1->len > c2->len)
    /* Explicit cast is necessary, because assignment discards const. */
    c = (CTYPE *) c1;
  else if (c1->len < c2->len)
    /* Explicit cast is necessary, because assignment discards const. */
    c = (CTYPE *) c2;
  else if (p1 >= p2 && (!integral_pclass(p1) || (c1->uclass >= c2->uclass)))
    /* Explicit cast is necessary, because assignment discards const. */
    c = (CTYPE *) c1;
  else if (p2 >= p1 && (!integral_pclass(p2) || (c2->uclass >= c1->uclass)))
    /* Explicit cast is necessary, because assignment discards const. */
    c = (CTYPE *) c2;

  else {
    c = copy_ctype(c1);
    (*c->stype)[(c->len)-1]->pclass = P2_MAX(p1, p2);
    if (integral_pclass(base_ptype(c)->pclass))
      c->uclass = P2_MAX(c1->uclass, c2->uclass);

#ifndef NDEBUG
    assert_ctype_valid(c);
#endif /* NDEBUG */
  }

  return(c);
}

BOOLEAN
string_ctype (const CTYPE *c)
{
#ifndef NDEBUG
  assert_ctype_valid(c);
#endif /* NDEBUG */

  return(ctypematch1(c, string_read_only_ctype, TRUE));
}

BOOLEAN
aggregate_ctype (const CTYPE *c)
{
#ifndef NDEBUG
  assert_ctype_valid(c);
#endif /* NDEBUG */

/* Add generic_container_read_only_ctype and generic_cursor_read_only_ctype???
   (JAT) */

  return(ctypematch1(c, container_read_only_ctype, TRUE)
         || ctypematch1(c, cursor_read_only_ctype, TRUE)
         || ctypematch1(c, composite_cursor_read_only_ctype, TRUE)
         || ctypematch1(c, schema_read_only_ctype, TRUE)
         || ctypematch1(c, struct_read_only_ctype, TRUE)
         || ctypematch1(c, union_read_only_ctype, TRUE));
}

BOOLEAN
aggregate_or_aggregate_array_ctype (const CTYPE *c)
{
  int i = 0;
  int len = c->len;
  while (i < len) {
    PCLASS pclass = (*c->stype)[i]->pclass;
#if 0
    if (!type_qualifier_pclass(pclass) && pclass != ARR)
#else
    if (pclass != ARR)
#endif
      return(aggregate_pclass(pclass));
    i++;
  }
  return(FALSE);
}

/* If ctype is a direct reference, return TRUE.  Otherwise, return FALSE. */

BOOLEAN
direct_ctype (const CTYPE *c)
{
#if 0
  int i = 0;
  int len = c->len;
#endif

#ifndef NDEBUG
  assert_ctype_valid(c);
#endif /* NDEBUG */

#if 0
  while (i < len-1)  {
    if (!type_qualifier_pclass((*c->stype)[i]->pclass))
      return(FALSE);
    i++;
  }
  return(TRUE);
#else
  assert(c->len != 0);
  return(c->len == 1);
#endif
}
