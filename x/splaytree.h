/* splaytree.h 1995/11/15 gjimenez */

struct splaytree_annote {
   struct splaytree_annote *next;
   int cont_id;
   char *cont_name;
   char                  ofield[20];       /* name of key field */

   /* Added by xform. */

   VOID_FUNC             bi;               /* bounds impact function */
   OP_TAB                *typeptr;         /* type_table entry for this type */
   char                  *ofield_type;     /* type of key field */
} ;


struct splaytree_cstate {
  int id;
  int layerno;
  struct splaytree_cstate *next;

  /* New fields. */

  BOUNDS  b;  /* bounds of predicate */
};
