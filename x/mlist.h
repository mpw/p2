/* $Id: mlist.h,v 45.0 1997/09/19 05:46:36 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#define  MAXX   100              /* maximum number of attributes to index */

/* Container-specific information per index. */

typedef struct {
  IDENT *abs;                    /* type identifiers      */
  IDENT *ele;
  IDENT *con;
  IDENT *cur;  
  int   con_id;                  /* container id */
  char  org_type[MAX_IDENT_LEN]; /* name of orig element   */
  char  ele_type[MAX_IDENT_LEN]; /* name of element type   */
  char  con_type[MAX_IDENT_LEN]; /* name of container type */
  char  cur_type[MAX_IDENT_LEN]; /* name of cursor type    */
  char  fld[MAX_IDENT_LEN];      /* name of indexed field  */
  char  fld_type[MAX_IDENT_LEN]; /* name of field type     */
  char  ret_cur[MAX_IDENT_LEN];  /* name of retr cur field */
  char  upd_cur[MAX_IDENT_LEN];  /* name of upd  cur field */
  char  con_name[MAX_IDENT_LEN]; /* name of container      */
} Kstruct;

/* Cursor-specific information per index. */

typedef struct {
   int   update_id;
   int   update_cost;
   int   update_layer;
   char  update_predicate[MAX_IDENT_LEN];

   int   retrieval_id;
   int   retrieval_cost;
   int   retrieval_layer;
   char  retrieval_predicate[MAX_IDENT_LEN];
   char  residual_predicate[MAX_IDENT_LEN];
} Cstruct;

struct mlist_annote {
  struct mlist_annote *next;
  int    cont_id;
  char   *cont_name;
  char   xfield[MAX_IDENT_LEN];  /* Name of indexed field */
};

struct mlist_cstate {
  int    id;                     /* identifier of cursor type */
  int    layerno;
  struct mlist_cstate *next;     /* next record of this type  */
  int    use_index;              /* -1 if index is not used for query
                                    processing */
  int    single;                 /* TRUE iff predicate is of the form
                                    fld == value or fld == variable.
                                    Used for query optimization */
  Cstruct x[MAXX];               /* cursor specific opt info  */
};

struct mlist_kstate {
  int    id;                     /* identifier of cont. type */
  int    layerno;
  struct mlist_kstate *next;     /* next record of this type */
  int    fieldno;                /* number of fields indexed */
  Kstruct x[MAXX];  
};
