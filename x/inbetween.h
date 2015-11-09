/* $Id: inbetween.h,v 45.0 1997/09/19 05:46:28 jthomas Exp $ */

struct inbetween_cstate {
   int                         id;        /* identifier of cursor type */
   int                         layerno;
   struct inbetween_cstate     *next;     /* next record of this type  */

   int                         retrieval_layer;
};
