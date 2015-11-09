/* $Id: seen.c,v 45.0 1997/09/19 05:47:00 jthomas Exp $ */
/* Copyright (C) 1995, The University of Texas at Austin. */

/* seen definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>       /* strcat() */

#include "error.h"        /* error() */
#include "gen-layerdef.h" /* annotations */
#include "lex.h"          /* MAX_IDENT_LEN */
#include "op-tab.h"       /* op_tab, RCLASS */
#include "rlist.h"        /* RLIST */
#include "type.h"         /* terminal_string1() */
#include "util.h"         /* BOOLEAN */
#include "xp-actions.h"   /* retrieval_op(), do_action() */
#include "xp-io.h"        /* out() */

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

BOOLEAN seen[MAX_NUM_OPS+1];       /* Have we seen [op] statement yet? */

/************************************************************************/
/*              Layer Statement Seen.                                   */
/************************************************************************/

/* Migrated from xp_gram.y (JAT) */

void
layer_stmt_seen (RCLASS realm, char *name, RLIST *rlist)
{
  if (seen[LAYER_STMT])
    warning(3, "multiple layer statements--all but first ignored");
  else {
    seen[LAYER_STMT] = TRUE;
    strcpy(layer_name, name);
    layer_realm = realm;
    params_rlist = rlist;
  }
}

/************************************************************************/
/*              operation_seen                                          */
/************************************************************************/

void
operation_seen (SPECIAL_OP op)
{
  int q = getindxop(op); 
  if (! op_exists_in_realm(op, layer_realm)) 
    assertion_failed("op %s is not in realm %d", 
                     op_tab[q].name, layer_realm);
  q = getindxop(op);

  if (seen[op])
    parse_error("multiple %s procs", op_tab[q].name);
  else
    seen[op] = TRUE;
}

/************************************************************************/
/*              have_all_operations_been_seen                           */
/************************************************************************/

static void
gen_ddl (void)
{
  int q = getindxop(DDLHINT_OP);
  out(op_tab[q].proc, layer_name);
  out("{ error(\"%s has no annotations\"); }",layer_name);
  seen[DDLHINT_OP] = TRUE;
}

void
have_all_operations_been_seen (void)
{
  char missing_list[MAX_IDENT_LEN * MAX_NUM_OPS];
  char unneeded_list[MAX_IDENT_LEN * MAX_NUM_OPS];
  SPECIAL_OP op;
  int q;
  
  missing_list[0] = '\0';
  unneeded_list[0] = '\0';

  FOREACH_OPERATION_INDEX(q) {
    op = op_tab[q].op_num;
    if (op_exists_in_realm(op, layer_realm) && !seen[op]) {
      if (op == DDLHINT_OP) { 
        if (!annotations) { 
          /* The "no annotation" remark is enough to call gen_ddl */
          gen_ddl();
        }
        else { 
          /* There's no other notion of default for this procedure */
          strcat(missing_list, op_tab[q].name);
          strcat(missing_list, " ");
        }
        continue;
      }

      if (retrieval_op(op) && !retrieval) { 
        /* Okay.  We don't expect them here (BJG). */
        continue;
      }

      if (!call_below(op, 0)) { 
        /* Then what happens is that this is the last layer that the 
           operation can exist in (since it can't be called below). 
           We generate a warning & some notion of a default. 
           The default depends on if the operation can be an expression
           or not. (BJG) */ 

        out(op_tab[q].proc, layer_name);
        if (op == REF_OP || op == IREF_OP) { 
          out("{ NODE *P2_r, *P2_result = NULL;");
          do_action((op == REF_OP) ? "ref" : "iref", "cursor0", "field");
          out("if (!P2_result)"
              "P2_result = terminal_string1(\" \");"
              "return(P2_result); }");
        }
        else { 
          out("{ return(");
          undefined_operation(op_tab[q].name, op);
          out("); }");
        }
        seen[op] = TRUE;
        continue;
      }

      if (retrieval_op(op)) { 
        switch (retrieval) { 
        case 0:
          /* NEVER */
          /* ok. don't need retrieval ops */
          break;
        case 1:
        case 2:
          /* SOMETIMES */
          /* ALWAYS */
          warning(3, "retrieval operation %s not defined for layer %s",
                  op_tab[q].name, layer_name);
          break;
        default:
          error("Error in retrieval value");
        }
        continue;
      }
    }
    if (!(op_exists_in_realm(op, layer_realm)) && seen[op]) {
      strcat(unneeded_list, op_tab[q].name);
      strcat(unneeded_list, "  ");
    }
  }

  if (missing_list[0] != '\0')
    error("missing operations: %s", missing_list);
  if (unneeded_list[0] != '\0')
    error("unneeded operations: %s", unneeded_list);
}
