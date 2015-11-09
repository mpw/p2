/* $Id: part.h,v 45.0 1997/09/19 05:46:43 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

typedef enum {
  PRIM = UND+1,
  SEC,
  BOTH
} PRIM_SEC_OR_BOTH;

typedef char PRED[100];

struct part_annote {
  struct part_annote  *next;
  int cont_id;
  char   *cont_name;

  char                part_at_field[MAX_IDENT_LEN];  
  char                first_prim_field[MAX_IDENT_LEN];
};

struct part_cstate {
  int                id;
  int                layerno;
  struct part_cstate *next;

  PRED               prim_p;
  PRED               sec_p;
  PRED               res_p;
  int                id3;
  int                id5;
  int                retrieval_cost3;
  int                retrieval_cost5;
  int                retrieval_layer3;
  int                retrieval_layer5;
  PRIM_SEC_OR_BOTH   predicate_on_prim_sec_or_both;
};

struct part_kstate {
  int                id;
  int                layerno;
  struct part_kstate *next;

  IDENT              *p;       /* Primary. */
  IDENT              *s;       /* Secondary. */
  IDENT              *a;
};
