/* $Id: gen-layerdef.c,v 45.1 1997/09/24 05:12:40 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* gen_layerdef() definitions. */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>   /* fprintf() */

#include "error.h"   /* error() */
#include "lex.h"     /* MAX_IDENT_LEN */
#include "op-tab.h"  /* op_tab */
#include "rlist.h"   /* rclass_str() */
#include "seen.h"    /* seen */
#include "util.h"    /* BOOLEAN */
#include "xform.h"   /* NEEDS_ANNOTATION */
#include "xp-io.h"   /* out() */

/*****************************************************************************/
/*                  Global variables.                                        */
/*****************************************************************************/

/* These variables communicate layer options to gen_layerdef() */

NEEDS_ANNOTATION annotations = NO_ANNOTATION; /* Does layer have annotations? */
BOOLEAN stable = FALSE; /* Are cursors stable on deletion? */
BOOLEAN d2u = FALSE; /* Does layer map delete() to upd()? */
BOOLEAN indirect_only = FALSE; /* Do we have a persistent layer?  */
RETRIEVAL retrieval = RETRIEVAL_NEVER; /* Can this be a retrieval layer? */

/*****************************************************************************/
/*                  gen_layerdef                                             */
/*****************************************************************************/

static void
print_forward_refs (FILE *fp)
{
  int r = layer_realm; 
  int q;
  
  fprintf(fp,"\n/* forward referencing */\n\n");
  FOREACH_OPERATION_INDEX(q) { 
    int op = op_tab[q].op_num;
    if (seen[op]) {
      if (op_exists_in_realm(op_tab[q].op_num, r))
        if (op_tab[q].is_void)
          fprintf(fp,"void %s_%s();\n", op_tab[q].name, layer_name);
        else
          fprintf(fp,"NODE *%s_%s();\n", op_tab[q].name, layer_name);
    } 
  }
  fprintf(fp,"\n\n");
}

static void
print_ops (FILE *fp)
{
  int r = layer_realm;

  SPECIAL_OP op;
  int q;

  for (op = 0; op < min_special_op; op++)
    fprintf(fp,"(NODE_FUNC) 0,");
  
  for (op = min_special_op; op <= max_special_op; op++) {
    q = getindxop(op);
    if (op_exists_in_realm(op, r) && seen[op]) {
      if (op_tab[q].is_void) 
        fprintf(fp,"(NODE_FUNC) %s_%s", op_tab[q].name, layer_name);
      else
        fprintf(fp,"%s_%s", op_tab[q].name, layer_name);
    }
    else
      fprintf(fp,"(NODE_FUNC) 0");
    if (op < max_special_op)
      fprintf(fp,", ");
  }
}

void
gen_layerdef (void)
{
  int i;
  FILE *rfp;
  char rfp_name[MAX_IDENT_LEN];

  sprintf(rfp_name,"%s-ref.h", layer_name);
  if (!(rfp = fopen(rfp_name,"w"))) {
    error("Cannot open file %s", rfp_name);
  }
  
  print_forward_refs(rfp);
  fprintf(rfp, "\nLAYER_DEF P2_%s_ = { \"%s\", %s, %d, ",
          layer_name, layer_name,
          rclass_str(layer_realm), count_params(params_rlist));
  fprintf(rfp, " %s, ", (indirect_only) ? "TRUE" : "FALSE");
  fprintf(rfp, " %s, ", (d2u) ? "TRUE" : "FALSE");
  fprintf(rfp, " %s, ", (stable) ? "TRUE" : "FALSE");
  fprintf(rfp, " %d, ", annotations);
  fprintf(rfp, " %d, ", retrieval);
  fprintf(rfp, "{");
  print_realm_list(rfp, params_rlist);
  fprintf(rfp, "}, {");
  print_ops(rfp);
  fprintf(rfp, "} };\n");

  /* For each of the digits '2' thuough '9' */
  for (i=2; i<=9; i++) {
    fprintf(rfp,"static CURS_ARG c_verbatim%d;",i);
    fprintf(rfp,"static CONT_ARG k_verbatim%d;",i); 
    fprintf(rfp,"static CURS_ARG *cursor%d = &c_verbatim%d;", i,i);
    fprintf(rfp,"static CONT_ARG *container%d = &k_verbatim%d;", i,i);
    fprintf(rfp,"static vptr vp%d;\n",i);
  }

  fclose(rfp);
}
