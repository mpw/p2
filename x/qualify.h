/* $Id: qualify.h,v 45.0 1997/09/19 05:46:47 jthomas Exp $ */

struct qualify_cstate {
   int                         id;        /* identifier of cursor type */
   int                         layerno;
   struct qualify_cstate       *next;     /* next record of this type  */

   int                         retrieval_layer;
};
