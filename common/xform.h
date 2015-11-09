/* $Id: xform.h,v 45.0 1997/09/19 05:40:57 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Type expression transformation declarations. */
/* Rename this file. (JAT) */

#ifndef INCLUDE_XFORM_H
#define INCLUDE_XFORM_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include "lex.h"    /* MAX_IDENT_LEN */
#include "op-tab.h" /* RCLASS */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define MAX_LAYER_PARAM 10
#define MAX_TE_ARG      20
#define MAX_ANODE_ARG   20
#define MAX_PATH_LEN    20

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

/* Previously, BJG defined used magic-numbers to represent these
   NEEDS_ANNOTATION and RETRIEVAL values.  For the time being, I have
   explicitly defined these symbolic constants to have the same
   numeric value that BJG used.  Eventually, I would like to define
   these to different values, and see if anything breaks. (JAT) */

typedef enum {
  NO_ANNOTATION = 0,
  ANNOTATION = 1,                   /* Single, required annotation */
  MULTIPLE_ANNOTATION = 2,
  OPTIONAL_ANNOTATION = 3,          /* Single, optional annotation */
  OPTIONAL_MULTIPLE_ANNOTATION = 4
} NEEDS_ANNOTATION;

typedef enum {
  RETRIEVAL_NEVER = 0,
  RETRIEVAL_SOMETIMES = 1,
  RETRIEVAL_ALWAYS = 2
} RETRIEVAL;

typedef struct {
  char      layer_name[MAX_IDENT_LEN]; /* Layer name. */
  RCLASS    layer_realm;               /* Layer's realm class. */
  int       num_of_params;             /* number of parameters for layer. */
  BOOLEAN   indirect_only;             /* does layer impl. persistence? */
  BOOLEAN   d2u;                       /* does layer map deletes to upds? */
  BOOLEAN   cursor_stability;          /* is cursor stable on deletion? */
  NEEDS_ANNOTATION needs_annotation;   /* does layer need annotation? */
  RETRIEVAL retrieval;                 /* can the layer be a retrieval layer */
  RCLASS    params[MAX_LAYER_PARAM];   /* Realm class for each parameter. */
  NODE_FUNC ops[MAX_NUM_OPS+1];        /* Ops vector indexed by enum. */
} LAYER_DEF;

/* Type expressions */
/* The struct ANNOTE is the abstract superclass of the various
   layer-specific annote structs.  That is, for each layer foo with an
   annotation foo the layer-specific header file foo.h must declare a
   struct named foo_annote whose first fields match the fields are the
   same as the fields we declare here in ANNOTE. (JAT) */

typedef struct annote_struct {
  struct annote_struct *next;
  int cont_id;
  char *cont_name;
} ANNOTE;

/* Used for linking cursor and container state info together. (DSB) */
/* If you change this struct, make sure that for all layers foo,
   you change the definition of foo_cstruct and foo_kstruct in foo.h (JAT) */

typedef struct kc_state {
  int             id;      /* Cursor or container id. */
  int             layerno; /* Layer number. */
  struct kc_state *next;   /* Next record of this type. */
} KC_STATE;

typedef struct ccbus {             /* used only by the ccbus layer       */
  struct te_struct *te;           /* pointer to type equation           */
  int              cont_id;       /* container id - used to identify te */
  struct ccbus     *next;         /* next node on list */
} CCBUS;

typedef struct te_struct {
  char             layer_name[MAX_IDENT_LEN];  /* used for debugging only   */
  int              layerno;                    /* layer number - generated  */
  ANNOTE           *annotation;                /* ptr to annotation struct  */
  ANNOTE           *first_annotation;          /* ptr to 1st annote struct  */
  KC_STATE         *cursor_state;              /* ptr to cursor state       */
  KC_STATE         *container_state;           /* ptr to container state    */
  LAYER_DEF        *layerdef;                  /* ptr to definition of layer*/
  struct te_struct *parent;                    /* pointer to parent node    */
  BOOLEAN          top;                        /* is this the top node of a 
                                                  type expression column?   */
  struct te_struct *down[MAX_TE_ARG];          /* type arguments            */

#if 0
  BOOLEAN          already_adorned;            /* has annotations been applied
                                                  to this layer             */
#endif

  int              version_number;             /* For debugging purposes. */
                                               /* Which invocation of the
                                                  layer this is. */
  CCBUS            *bus_list;                  /* List of TEs for ccbus. */
  
  BOOLEAN          requires_proceduralize_ref;
  BOOLEAN          requires_indirect_only;
  BOOLEAN          requires_op_vec;
  BOOLEAN          requires_kcur;
} TE;

typedef struct pnode_struct {
  char                 str[MAX_IDENT_LEN];     /* contents of parse-tree node */
  struct pnode_struct  *ptr[4];                /* lower-level parse trees     */
} PNODE;
typedef PNODE PATH[MAX_PATH_LEN];

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    assert_te_valid(const TE *te);

#endif /* INCLUDE_XFORM_H */
