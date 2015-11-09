/* $Id: generic_funcall.h,v 45.0 1997/09/19 05:46:22 jthomas Exp $ */
/* Copyright (C) 1996 The University of Texas at Austin. */

struct generic_funcall_cstate {
   int id;
   int layerno;
   struct generic_funcall_cstate *next;

   int                           retrieval_layer;
};
