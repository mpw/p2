/* $Id: nloops.h,v 45.0 1997/09/19 05:46:39 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

struct nloops_annote {
  struct nloops_annote  *next;
  int cont_id;
  char   *cont_name;

  char lnkname[MAX_IDENT_LEN];          /* name of link */
  CARD parent_card;                     /* # of parents per child */
  CARD child_card;                      /* # of children per parent */
  char child_container[MAX_IDENT_LEN];  /* name of child container */
  char parent_container[MAX_IDENT_LEN]; /* name of child container */
  char linkpred[MAX_PRED_LEN];          /* link predicate */
};

