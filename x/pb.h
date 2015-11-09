/* $Id: pb.h,v 45.0 1997/09/19 05:46:44 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#ifndef INCLUDE_PB_H
#define INCLUDE_PB_H

/* Standard header file for layer .c files. */
/* xp automatically #include's this file in the .c files it generates. */

/* Ideally, this file would only #include header files for definitions
   needed by automatically generated (i.e. hidden) code.  If a
   particular layer needs to #include additional header files, then
   that layer .xp file should !#include them explicitly.
   Unfortunately, there are some "standard" definitions that all
   layers assume (for example, strcpy() to construct identifiers at
   compile time).  (JAT) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>       /* NULL */
#include <stdlib.h>      /* atoi() */
#include <string.h>      /* strcpy() */
#include <memory.h>      /* memcpy() */

#include "arg.h"         /* CURS_ARG */
#include "call-down.h"   /* call_down() */
#include "data-type.h"
#include "error.h"
#include "io.h"          /* sprint_ptree() */
#include "layer-util.h"  /* FOREACH_ANNOTATION */
#include "pb-actions.h"  /* container_declarabtion_ident3() */
#include "pb-type.h"     /* symtab_lookup() */
#include "pb-xform.h"    /* FOREACH_MEMBER */
#include "qopt.h"
#include "string-util.h" /* assert_string_nonempty_and_valid() */
#include "type.h"        /* add_annotation() */
#include "typex.h"
#include "util.h"        /* BOOLEAN */
#include "xform.h"
#include "xmalloc.h"

#endif /* INCLUDE_PB_H */
