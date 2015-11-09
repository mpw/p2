/* $Id: named_funcall.h,v 45.0 1997/09/19 05:46:39 jthomas Exp $ */

struct named_funcall_cstate {
   int                         id;        /* identifier of cursor type */
   int                         layerno;
   struct named_funcall_cstate *next;     /* next record of this type  */

   int                         retrieval_layer;
};
