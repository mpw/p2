/* $Id: xp-actions.c,v 45.2 1997/09/29 03:51:11 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Routines that ARE called from xp-gram.y (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>        /* NULL */
#include <stdarg.h>       /* va_list */
#include <stdlib.h>       /* size_t */
#include <string.h>       /* strcpy() */

#include "adhoc-arg.h"    /* ADHOC_ARG */
#include "error.h"        /* error() */
#include "gen-layerdef.h" /* retrieval */
#include "io.h"           /* SPRINT_BUF_SIZE */
#include "lex.h"          /* MAX_IDENT_LEN */
#include "ref-util.h"     /* get_path_num() */
#include "rlist.h"        /* RLIST */
#include "seen.h"         /* operation_seen() */
#include "string-util.h"  /* copy_string() */
#include "type.h"         /* CTYPE */
#include "util.h"         /* BOOLEAN */
#include "xform.h"        /* OPTIONAL_ANNOTATION */
#include "xmalloc.h"      /* xfree() */
#include "xp-io.h"        /* out() */

/*****************************************************************************/
/*                  Local Variables.                                         */
/*****************************************************************************/

static BOOLEAN print_trailer = FALSE;    /* Should we print a "}"? */

/*****************************************************************************/
/*                  Global variables.                                        */
/*****************************************************************************/

/* These variables communicate layer options to print_proc_header() */

BOOLEAN curs_state       = FALSE;        /* Do cursors have state? */
BOOLEAN cont_state       = FALSE;        /* Do containers have state? */

/* These variables record properties of the
   current xp procedure (aka special operation). */

/* Note: previously, before schema arguments,
   has_cursor_arg == !has_container_arg
   The fact that this is no longer true may cause problems. (JAT) */

BOOLEAN has_container_arg;               /* In proc w/ container argument(s)? */
BOOLEAN has_cursor_arg;                  /* In proc w/ cursor argument(s)? */
BOOLEAN has_schema_arg;                  /* In proc w/ cursor argument(s)? */
BOOLEAN in_xform_proc    = FALSE;        /* In xform proc? */
BOOLEAN in_ddlhint_proc  = FALSE;        /* In ddlhint proc? */
BOOLEAN in_optimize_proc = FALSE;        /* In optimize proc? */
BOOLEAN in_special_proc  = FALSE;        /* In proc with no state variables */
                                         /* i.e ddlhint, lverbatim */
BOOLEAN print_local_vars = FALSE;        /* have we printed local vars yet? */
BOOLEAN print_return     = FALSE;        /* should we print return stmt?    */
BOOLEAN delete_operation = FALSE;        /* are we processing the delete op? */

/* Other */

BOOLEAN force_field_ref = FALSE;         /* Is field a sure field? */
BOOLEAN know_member_name = TRUE;         /* do we know member name or not?  */
BOOLEAN in_defaults = FALSE;             /* In a default declaration? */
int     current_op = 0;                  /* current operation */ 
BOOLEAN unknown_fld;                     /* name of referenced field known? */
BOOLEAN unknown_idx;                     /* name of index offset known?     */
BOOLEAN cursor_field;                    /* is field referenced a curs fld? */
BOOLEAN obj_field;                       /* is curs fld the obj field?      */
char    rf_field[MAX_IDENT_LEN];         /* name of member being updated    */
char    field_val[MAX_IDENT_LEN];        /* name of referenced field        */
char    index_val[MAX_IDENT_LEN];        /* index offset                    */

int   enable_hierarchy_comments;
CTYPE *member_ctype;
char  member_name[MAX_IDENT_LEN];
char  member_type[MAX_IDENT_LEN];
char  cdef_name[MAX_IDENT_LEN];
char  kdef_name[MAX_IDENT_LEN];

/*****************************************************************************/
/*                  Clear Member.                                            */
/*****************************************************************************/

static void
clear_ctype (CTYPE *m)
{
   STYPE *stype = m->stype;
   memset((void *) m, 0, sizeof(CTYPE));
   m->stype = stype;
   m->uclass = UND;
}

void
clear_member (void)
{
   member_type[0]   = '\0';
   member_name[0]   = '\0';
   know_member_name = FALSE;
   clear_ctype(member_ctype);
}

/*****************************************************************************/
/*                  Base type.                                               */
/*****************************************************************************/

#define TEST(str,val) if (strcmp(s,str)==0) return(val)

PCLASS
base_type (char *s)
{
   TEST("void",    VOI);
   TEST("char",    CHA);
   TEST("varchar", VCHA);
   TEST("short",   SHO);
   TEST("int",     IN);
   TEST("long",    LON);
   TEST("float",   FLO);
   TEST("double",  DOU);

   return(ERR);
}

/*****************************************************************************/
/*                  Operation header.                                        */
/*****************************************************************************/

static BOOLEAN
op_has_arg (OP_DESC *op_desc, ACLASS aclass)
{
  int i;
  for (i = 0; i < op_desc->num_arg; i++)
    if (op_desc->param[i] == aclass)
      return(TRUE);
  return(FALSE);
}

/* Print the banner for xp procs and initialize global variables. */

void
opheader (SPECIAL_OP op)
{
  OP_DESC *op_desc;
  FOREACH_OPERATION(op_desc) { 
    if (op_desc->op_num == op) {

      /* Record the fact that operation has been seen. */
      operation_seen(op);

      /* Print procedure header. */
      out(op_desc->proc, layer_name);

      /* Set global variables */
      has_container_arg = op_has_arg(op_desc, CON);
      assert(has_container_arg == op_desc->has_container_arg);
      has_cursor_arg    = op_has_arg(op_desc, CUR);
      has_schema_arg    = op_has_arg(op_desc, SCH);

      print_local_vars  = op_desc->print_local_vars;
      print_return      = op_desc->print_return;
      delete_operation  = op_desc->delete_operation;
      return;
    }
  }
  error("unrecognizable operation");
}

/*****************************************************************************/
/*                  undefined_operation.                                     */
/*****************************************************************************/

/* This procedure provides defaults for undefined operations rather
   than crash.  The user is warned as well. (BJG) */

void
undefined_operation (char *op_name, int op)
{
  int indx = getindxop(op);

  if (op_tab[indx].expr) { 
    /* Expressions. */
    warning(4, "layer %s must define %s--providing default of \"0\".",
            layer_name, op_name);
    out("terminal_string1(\"0\")");
  }
  else { 
    /* Procedures. */
    warning(4, "layer %s must define %s--providing null statement default.",
            layer_name, op_name);
    out("terminal_string1(\" \")");
  }
}

/*****************************************************************************/
/*                  not_concrete                                             */
/*****************************************************************************/

BOOLEAN
not_concrete (char *s)
{
  char c = last_char(s);
  return(c == '#');
}

/*****************************************************************************/
/*                  do_action1 and print_arglist.                            */
/*****************************************************************************/

/* Helper routines for do_action, do_adhoc_action, and opcallN (JAT) */

static void
do_action1 (char *op_name, int *indx, int *op)
{
  if (not_concrete(op_name)) {
    /* Delete trailing '#' from op_name. */
    int len = strlen(op_name);
    {
      char s[len];
      strncpy(s, op_name, len-1);
      s[len-1] = '\0';
      (*op) = getop(s);
    }
  }
  else
    (*op) = getop(op_name);

  (*indx) = getindxop(*op);
}

/* Move this to adhoc-arg.[ch]??? (JAT) */

static void
print_adhoc_arg (ADHOC_ARG *adhoc_arg, int num_arg)
{
  int i;
  for(i = 0; i < num_arg; i++) {
    out(" %s", adhoc_arg->name);
    if (i < num_arg-1) {
      out(",");
      adhoc_arg = adhoc_arg->next;
    }
  }
}

/*****************************************************************************/
/*                  do_action and do_adhoc_action                            */
/*****************************************************************************/

/* 
   These are actions that are performed for procedures that return an
   expression, sometimes as the right hand side of an update.  They 
   used to be in xp_gram.y in the cxprocs rule.  These actions are 
   also used for kref & iref in "have_all_layers_been_seen". 
*/

void
do_action (char *op_name, ...)
{
  char *arg[MAX_OP_PARAM];
  int indx;
  int op;
  OP_DESC *op_desc;
  char *cname;
  int num_arg;

  do_action1(op_name, &indx, &op);
  op_desc = &op_tab[indx];
  cname = op_desc->constname;
  num_arg = op_desc->num_arg;

  if (num_arg > 0) {
    va_list ap;
    int i;

    va_start(ap, op_name);
    for(i = 0; i < num_arg; i++)
      arg[i] = va_arg(ap, char *);
    va_end(ap);
  }

  switch(op) { 

  /* Single argument operations. */

  case END_ADV_OP: 
  case END_REV_OP:
  case ALLOC_OP:
  case OVERFLOW_OP:
  case QUERY_OP:
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, %s, 1, %s));", cname, arg[0]);
    else if (call_below(op, get_path_num(arg[0])))
      out("NONTERM(call_down(te, %d, %s, 1, %s));",
          get_path_num(arg[0]), cname, arg[0]);
    else
      undefined_operation(op_desc->name, op); 
    break;

  /* Double argument operations. */

  case VARALLOC_OP:
  case POS_OP:
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, %s, 2, %s, expr0));", cname, arg[0]);
    else if (call_below(op, get_path_num(arg[0])))
      out("NONTERM(call_down(te, %d, %s, 2, %s, expr0));",
          get_path_num(arg[0]), cname, arg[0]);
    else
      undefined_operation(op_desc->name, op); 
    break; 

  case REF_OP:
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, REF_OP, 2, %s, %s));",
          arg[0], arg[1]);
    else if (call_below(REF_OP, get_path_num(arg[0])))
      out("NONTERM(call_down(te, %d, REF_OP, 2, %s, %s));",
          get_path_num(arg[0]), arg[0], arg[1]);
    else {
      out("if (strcmp(field,\"obj\") == 0)"
          "{"
          "NONTERM(terminal_vstring(\"(%%s).obj\", %s->expr));", arg[0]);
      out("}"
          "else");
      /* Cast the cursor.obj to orig_type or obj_type.  Do this to avoid a
         "dereferencing pointer to incomplete type" error
         when referencing a field of a generic cursor. (JAT) */
      /* This casts only when the cursor is generic.
         (Produces cleaner object (.c) code). */
      out("{"
          "if (%s->cursor_id == GENERIC_CURS_ID) {", arg[0]);
      out("NONTERM(terminal_vstring(\"((struct %%s *)(%%s).obj)->%%s\","
          "%s->orig_type, %s->expr, field));", arg[0], arg[0]);
      out("}"
          "else"
          "{");
      out("NONTERM(terminal_vstring(\"((%%s).obj)->%%s\","
          "%s->expr, field));", arg[0]);
      out("}"
          "}");
    }
    break;

  case IREF_OP:
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, IREF_OP, 2, %s, %s));",
          arg[0], arg[1]);
    else if (call_below(IREF_OP,get_path_num(arg[0])))
      out("NONTERM(call_down(te, %d, IREF_OP, 2, %s, field));",
          get_path_num(arg[0]), arg[0]);
    else
      out("NONTERM(terminal_vstring(\"(%%s)->%%s\", cursor%d->expr, field));",
          get_param_num(op_name));
    break;

  case ENDC_OP: 
  case ENDP_OP:
  case RELATED_OP:
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, %s, 3, %s, %s, %s));",
          cname, arg[0], arg[1], arg[2]);
    else if (call_below(op,get_path_num(arg[0])))
      out("NONTERM(call_down(te, %d, %s, 3, %s, %s, %s));",
          get_path_num(arg[0]), cname, arg[0], arg[1], arg[2]);
    else
      undefined_operation(op_desc->name, op); 
    break;

  default:
    undefined_operation(op_desc->name, op); 
  }
}

/*
   Like do_action, only it's for adhoc operations.  Arguments are 
   passed in an arglist instead of having varags here.  This 
   procedure may one day be generalized to cover all the operations
   replacing do_action, and then replace opcallN, 
   which someday will replace opcall[1234]. (BJG)
*/

void
do_adhoc_action (char *name, ADHOC_ARG *arglist)
{
  char *cname;
  int indx;
  int op; 
  OP_DESC *op_desc;
  int num_arg;

  do_action1(name, &indx, &op);
  op_desc = &op_tab[indx];
  cname = op_desc->constname;
  num_arg = op_desc->num_arg;

#if 0

  /* Later, we may wish to alter the xp grammar to determine if we
     should expecting only an expression.  For now, we'll accept
     anything.  The trouble is that not all adhocs are expected to
     return some values.  So I handled it like ref, which can do both
     and assume that the adhocs themselves will do the right
     thing. (BJG) */

   if (!op_desc->expr)
     error("%s must be an expression here",name);

#endif

  if (num_arg == 0) { 
    if (not_concrete(name))
      out("NONTERM(call_level(te, %s, 0));", cname); 
    else if (call_below(op, 0))
      out("NONTERM(call_down(te, 0, %s, 0));", cname);
    else
      undefined_operation(op_desc->name, op); 
  }
  else { 
    verify_args(arglist, op_desc->name);
    
    if (not_concrete(name)) {
      out("NONTERM(call_level(te, %s, %d,", cname, num_arg);
      print_adhoc_arg(arglist, num_arg);
      out("));");
    }
    else if (call_below(op, 0)) {
      out("NONTERM(call_down(te, %d, %s, %d,", 
             get_path_num(arglist->name), cname, num_arg);
      print_adhoc_arg(arglist, num_arg);
      out("));");
    }
    else
      undefined_operation(op_desc->name, op); 
  }
}

/*****************************************************************************/
/*                  Opcall.                                                  */
/*****************************************************************************/

/* These are the procedures that are called when a concrete call of an
   xp proc is to be generated.  The procedures differ only in the
   number of arguments that they take. */

/* Thought #1:
   The opcall[1234] should simply repackage the 
   arguments and call opcallN. (BJG) */

/* Thought #2: 
   After that's done, perhaps these procedures
   should be merged with do_action & do_adhoc_action.   
   Yow! (BJG) */

void
opcall1 (SPECIAL_OP op, char *op_name, char *arg1)
{
  OP_DESC *op_desc;
  FOREACH_OPERATION(op_desc) { 
    if (op_desc->op_num == op) {
      if (not_concrete(op_name))
        out("NONTERM(call_level(te, %s, 1, %s));", 
            op_desc->constname, arg1);
      else
        if (call_below(op, get_path_num(arg1)))
          out("NONTERM(call_down(te, %d, %s, 1, %s));",
              get_path_num(arg1), op_desc->constname, arg1);
        else
          error("no concrete %s function", op_desc->proc);
      return;
    }
  }
}

void
opcall2 (SPECIAL_OP op, char *op_name, char *arg1, char *arg2)
{
  OP_DESC *op_desc;
  FOREACH_OPERATION(op_desc) { 
    if (op_desc->op_num == op) {
      if (not_concrete(op_name))
        out("NONTERM(call_level(te, %s, 2, %s, %s));", 
            op_desc->constname, arg1, arg2);
      else
        if (call_below(op, get_path_num(arg1)))
          out("NONTERM(call_down(te, %d, %s, 2, %s, %s));",
              get_path_num(arg1), op_desc->constname, arg1, arg2);
        else
          error("no concrete %s function", op_desc->proc);
      return;
    }
  }
}

void
opcall3 (SPECIAL_OP op, char *op_name, char *arg1, char *arg2, char *arg3)
{
  OP_DESC *op_desc;
  FOREACH_OPERATION(op_desc) { 
    if (op_desc->op_num == op) {
      if (not_concrete(op_name))
        out("NONTERM(call_level(te, %s, 3, %s, %s, %s));", 
            op_desc->constname, arg1, arg2, arg3);
      else
        if (call_below(op, get_path_num(arg1)))
          out("NONTERM(call_down(te, %d, %s, 3, %s, %s, %s));",
              get_path_num(arg1), op_desc->constname, arg1, arg2, arg3);
        else
          if (op == UPD_OP) 
            out("NONTERM(nonterm(NULL, 4, terminal_string(cursor%d->expr),"
                "terminal_string(\"=\"), expr, terminal_string(\";\")));",
                get_param_num(arg1));
          else
            error("no concrete %s function", op_desc->proc);
      return;
    }
  }
}

void
opcall4 (SPECIAL_OP op, char *op_name, char *arg1,
         char *arg2, char *arg3, char *arg4)
{
  OP_DESC *op_desc;
  FOREACH_OPERATION(op_desc) {
    if (op_desc->op_num == op) {
      if (not_concrete(op_name))
        out("NONTERM(call_level(te, %s, 4, %s, %s, %s, %s));",
            op_desc->constname, arg1, arg2, arg3, arg4);
      else
        if (call_below(op, get_path_num(arg1)))
          out("NONTERM(call_down(te, %d, %s, 4, %s, %s, %s, %s));",
              get_path_num(arg1), op_desc->constname,
              arg1, arg2, arg3, arg4);
        else
          error("no concrete %s function", op_desc->proc);
      return;
    }
  }
}

/* The truly generic 0-or-NONTERM-arguments operation call function. (BJG) */

void
opcallN (char *op_name, ADHOC_ARG *arglist) 
{
  int indx;
  int op;
  OP_DESC *op_desc;
  int num_arg;

  do_action1(op_name, &indx, &op);
  op_desc = &op_tab[indx];
  num_arg = op_desc->num_arg;
  
  if (num_arg == 0) {
    if (not_concrete(op_name))
      out("NONTERM(call_level(te, %s, 0));", op_desc->constname); 
    else if (call_below(op, 0))
      out("NONTERM(call_down(te, %s, 0));", op_desc->constname);
    else
      error("no concrete %s function", op_desc->name);
  }
  else {
    verify_args(arglist,op_desc->name);
    if (not_concrete(op_name)) {
      out("NONTERM(call_level(te, %s, %d,",
          op_desc->constname, num_arg);
      print_adhoc_arg(arglist, num_arg);
      out("));");      
    }
    else {
      if (call_below(op, 0)) {
        out("NONTERM(call_down(te, %d, %s, %d,", 
            get_path_num(arglist->name), op_desc->constname, num_arg);
        print_adhoc_arg(arglist, num_arg);
        out("));");
      }
      else {
        if (op == UPD_OP)
          out("NONTERM(nonterm(NULL, 4, terminal_string(cursor%d->expr),"
              "terminal_string(\"=\"), expr, terminal_string(\";\")));",
              get_param_num(arglist->name));
        else
          error("no concrete %s function", op_desc->proc);
      }
    }
  }
}

/*****************************************************************************/
/*                  ddlhint                                                  */
/*****************************************************************************/

/* Generate code to add an annotation */

void
add_ddlhint_annotation (void)
{
#ifndef NDEBUG
  /* Make sure argv[0] is a valid string. */
  out("assert_string_nonempty_and_valid((char *) argv[0]);");
#endif
  /* Add annotation with unknown container id, but known name. */
  out("add_annotation(te, sizeof(struct %s_annote), UNKNOWN_CONT_ID,"
      "(char *) argv[0]);", layer_name);
}

/* Check ddlhint arguments.  Generate code to make sure n == (argc - 1)
   (the 0-th argument to ddlhint is the container name), where n is
   the numeric literal (expressed as a string) passed to ddlhint; for
   example, "2" in "limit 2 arguments". */

void
check_ddlhint_arguments (char *n)
{
  if ((annotations == OPTIONAL_ANNOTATION)
      || (annotations == OPTIONAL_MULTIPLE_ANNOTATION)) { 
    /* optional annotations */ 
    out("if (((argc - 1) != %s) && ((argc - 1) != 0))", n);
    out("error(\"%s given %%d arguments, expects 0 or %s\", (argc - 1));",
        layer_name, n);
  }
  else {
    out("if ((argc - 1) != %s)", n);
    out("error(\"%s given %%d arguments, expects %s\", (argc - 1));",
        layer_name, n);
  }
}

/*****************************************************************************/
/*                  Add restore code.                                        */
/*****************************************************************************/

/*
  This code deals with cursor stability in deletions.

  if top layer && advance layer - generate usual code
  if top layer && !advance layer && cursors are stable at lower layers
          - generate usual code
**if top layer && ! advance layer && cursors are unstable at lower layers
          - generate usual code; cursor.obj = cursor.restore;
  if !top layer && advance layer && cursors are stable at higher layers
          - generate usual code  
**if !top layer && advance layer && cursors are not stable at higher layers
          - generate usual code; cursor.restore = cursor.obj
  if !top layer && !advance layer
          - generate usual code

  One NONTERM case.  In the case of delete flag, a deletion is translated
  into an update.  Thus, the second rule never fires.  The test
  that we need to make is:

   if layer_maps_delete_to_update && retrieval_layer_is_below &&
      cursors are not stable at higher layers && no higher layers map
      deletes_to_updates then
         - generate cursor.restore = obj;

   note: the last condition "no higher layers map deletes_to_updates"
         is vacuously true.  The only time that the above test is made
         is in deletion.  If there were a higher layer that mapped deletions
         to updates, it would have caught the deletion and not propagated
         it.  Thus the condition to generate if a layer maps D2U is:

    if (retrieval_layer_is_below && cursors are unstable at higher layers)
         - generate cursor.restore = obj;
*/

static void
add_restore_code (void)
{
/*
  This is the intent of this code:  
   if (te->top && (te->layerno != cursor0->layer) &&
       !are_cursors_stable_at_lower_layers(te, cursor0->layer))
   %{ cursor.obj = cursor.restore;
   %}
   if (!te->top && (te->layerno == cursor0->layer) &&
       !are_cursors_stable_at_higher_layers(te))
   %{ cursor.restore = cursor.obj;
   %}
*/

  if (!delete_operation)
    return; /* Add nothing. */

  out("if (te->top && (te->layerno != cursor0->layer) && "
      "!are_cursors_stable_at_lower_layers(te, cursor0->layer))"
      "{"
      "NONTERM(terminal_vstring(\"%%s.obj = %%s.restore;\","
      "cursor0->expr, cursor0->expr));"
      "}"
      "if (!te->top && (te->layerno == cursor0->layer) && "
      "!are_cursors_stable_at_higher_layers(te))"
      "{"
      "NONTERM(terminal_vstring(\"%%s.restore = %%s.obj;\","
      "cursor0->expr, cursor0->expr));"
      "}");

  if (d2u)
    out("if (retrieval_layer_is_below(te,cursor0->layer) && "
        "!are_cursors_stable_at_higher_layers(te))"
        "{"
        "NONTERM(terminal_vstring(\"%%s.restore = %%s.obj;\","
        "cursor0->expr, cursor0->expr));"
        "}");
}

/*****************************************************************************/
/*                  retrieval_op                                             */
/*****************************************************************************/

BOOLEAN
retrieval_op (int opnum)
{
  /* Return TRUE if operation needed for retrieval layers */ 
  switch (opnum) {
  case ADV_OP: 
  case REV_OP:
  case END_ADV_OP: 
  case END_REV_OP:
  case RESET_START_OP:
  case RESET_END_OP:
  case QUERY_OP:
    return(TRUE);
  default:
    return(FALSE);
  }
}

/*****************************************************************************/
/*                  Print procedure header and trailer.                      */
/*****************************************************************************/

/* These are the actions that are triggered at the beginning and the
   end of an xp proc. */

/* Note that print_proc_header and print_proc_trailer are not exactly
   symmetrical.  The retrieval_layer_trailer is paired with select
   procedures that have retrieval_layer_header;
   retrieval_layer_trailer is smart enough to know if
   retrieval_layer_header has been called. */

void
retrieval_layer_header (SPECIAL_OP op, char *op_name, char *params)
{

  /* Add header for retrieval/advance layer only if the corresponding
     operation exists in the concrete layer immediately below this
     layer--don't generate anything if it is a layer from the TOP realm. */

   if (layer_realm == TOP
       || !params_rlist
       || !op_exists_in_realm(op, params_rlist->type))
      return;

   if (retrieval_op(op) && !retrieval)
     error("retrieval operation %s defined for non-retrieval layer %s",
           op_name, layer_name);
   
   /* Add the following lines of code if retrieval-sometimes. */
   
   out("{");
   if (retrieval == 1) {
     out("if (cursor0->layer != te->layerno)");
     out("return(call_down(te, 0, %s, 1, %s));", op_name, params);
     out("else");
   }
   print_trailer = TRUE;
}

void
link_retrieval_layer_header (SPECIAL_OP op, char *op_name, char *params)
{
  /* Add header for retrieval/advance layer only if the corresponding
     operation exists in the concrete layer immediately below this layer
     layer--don't generate anything if it is a layer from the TOPLINK realm. */

   if (layer_realm == TOPLINK
       || !params_rlist
       || !op_exists_in_realm(op, params_rlist->type))
      return;

    if (retrieval_op(op) && !retrieval)
      error("retrieval operation %s defined for non-retrieval layer %s",
            op_name, layer_name);

   out("{"
       "if (lstate0->linklayer != te->layerno)"
       "return(call_down(te, 0, %s, 1, %s));", op_name, params);
   out("else");
   print_trailer = TRUE;
}

void
print_proc_header (void)
{
  if ((brace_nesting_depth == 0) && print_local_vars) {
    out("{"
        "NODE *P2_r, *P2_rf, *P2_previous, *P2_lhs_rf,"
        " *P2_result = NULL, *P2_before_foreach;"
        "char P2_lhs[MAX_IDENT_LEN];");
    if (enable_hierarchy_comments)
      out("if (enable_hierarchy_comments)"
          "{"
          "NONTERM(terminal_string(\"/*%s*/\\n\"));"
          "} {", layer_name);
  }
  else
    out("{");

  if (in_xform_proc) {
    char i;
    for (i = '2'; i <= '9'; i++)
      out("IDENT *cursor%c, *element%c, *container%c;", i, i, i);
  }

  /* Initialize cursor state in all xp procedures except:
     xform (since it doesn't deal with cursors)
     ddlhint (since it doesn't deal with cursors at all)
     optimize (since it allocates cursor state variables)
     and any xp procs that have only container arguments. */
  if (!in_xform_proc
      && !in_special_proc
      && !in_optimize_proc
      && curs_state
      && !has_container_arg) {
    out("struct %s_cstate *cs = (struct %s_cstate *)", 
        layer_name, layer_name);
    out("lookup_kc_state(te, cursor0->cursor_id, cursor0->expr, 1);");
  }

  /* Initialize container state in all xp procedures except
     xform (since it allocates container state variables)
     ddlhint (since it doesn't deal with containers). */
  if (!in_xform_proc && !in_special_proc && cont_state) {
    out("struct %s_kstate *ks = (struct %s_kstate *)",
        layer_name, layer_name);
    out("lookup_kc_state(te, %s0->container_id, %s0->expr, 0);",
        (has_container_arg) ? "container" : "cursor",
        (has_container_arg) ? "container" : "cursor");
  }

  /* Allocate cursor state only in optimize procedure. */
  if (in_optimize_proc && curs_state) {
    out("struct %s_cstate *cs = (struct %s_cstate *)", 
        layer_name, layer_name);
    out("new_kc_state(te, sizeof(struct %s_cstate),"
        "cursor0->cursor_id, 1);", layer_name);
  }

  /* Allocate container state only in xform procedure. */
  if (in_xform_proc && cont_state) {
    out("struct %s_kstate *ks = (struct %s_kstate *)", 
        layer_name, layer_name);
    out("new_kc_state(te, sizeof(struct %s_kstate),"
        "container0->ctype->cctype->container_id, 0);", layer_name);
  }

#ifndef NDEBUG
  /* Only in xform procedure. */ 
 if (in_xform_proc) {
    out("assert_string_nonempty_and_valid(P2_cont_name);");
    out("{");
  }
#endif

  brace_nesting_depth++;
}

static void
retrieval_layer_trailer (void)
{
   if ((brace_nesting_depth == 0) && print_trailer) {
      out("}");
      print_trailer = FALSE;
   }
}

void
print_proc_trailer (void)
{
#ifndef NDEBUG
  /* Only in xform procedure. */
  if (in_xform_proc) {
    out("}");
  }
#endif

  if ((brace_nesting_depth == 1) && print_local_vars) { 
    if (enable_hierarchy_comments)
      out("}"
          "if (enable_hierarchy_comments)"
          "{"
          "NONTERM(terminal_string(\"/*%s*/\\n\"));"
          "}", layer_name);
    print_local_vars = FALSE;
  }
  if ((brace_nesting_depth == 1) && print_return) {
    add_restore_code();
    out("if (P2_result==0) P2_result = terminal_string1(\" \");");
    out("return(P2_result);");
  }
  brace_nesting_depth--;
  out("}");
  retrieval_layer_trailer();
  if (brace_nesting_depth == 0) {
    in_xform_proc      = FALSE;
    in_ddlhint_proc    = FALSE;
    in_optimize_proc   = FALSE;
    in_special_proc    = FALSE;
  }
}

/*****************************************************************************/
/*                  Dollar actions.                                          */
/*****************************************************************************/

/* Initialize the variables for these defaulted procedures. */

static void
set_vars (int q)
{ 
  print_local_vars = op_tab[q].print_local_vars;
  print_return = op_tab[q].print_return;

  has_container_arg = op_has_arg(&op_tab[q], CON);
  assert(has_container_arg == op_tab[q].has_container_arg);
  has_cursor_arg = op_has_arg(&op_tab[q], CUR);
  has_schema_arg = op_has_arg(&op_tab[q], SCH);

  delete_operation = op_tab[q].delete_operation;
  in_xform_proc = (op_tab[q].op_num == XFORM_OP);
  in_ddlhint_proc = (op_tab[q].op_num == DDLHINT_OP);
  in_special_proc = ((op_tab[q].op_num == DDLHINT_OP)
                     || (op_tab[q].op_num == L_VERBATIM_OP));
  in_optimize_proc = (op_tab[q].op_num == OPTIMIZE_OP);
}

/*
   Used to convert arguments to by reference.

   A string of the form:
     n, arg1, arg2, ..., argN

   Will be translated into:
     "(&(%s), &(%s), ..., &(%s))", arg1->expr, arg2->expr, ..., argN->expr
*/

static char *
oparglist_to_generic_arguments (const char *oparglist)
{
  int narg = char_occurrences(oparglist, ',');

#ifndef NDEBUG
  /* Make sure oparglist format is valid. */
  int narg1;
  /* Oparglist begins with a single decimal integer. */
  assert(sscanf(oparglist, "%d", &narg1) == 1);
  /* That decimal integer is equal to the number of occurrences of ','
     (i.e. the number of arguments) in oparglist. */
  assert(narg1 == narg);
#endif

  if (narg == 0)
    return(copy_string("()"));
  else {
    char s[SPRINT_BUF_SIZE];
    size_t len = 0;
    s[0] = '\0';
    print2(s, &len, "\"(", 2);
    {
      int i = 0;
      while (i < narg) {
        print1(s, &len, "&(%s)");
        i++;
        if (i < narg)
          print2(s, &len, ", ", 2);
      }
    }
    print2(s, &len, ")\", ", 4);
    {
      char *t = copy_string(oparglist);
      char *token;
      strtok(t, ", ");
      token = strtok(NULL, ", ");
      while (token != NULL)
      {
        print1(s, &len, token);
        /* If argI != "exprJ", then convert argI into argI->expr. */
        /* argI != "exprJ" if argI has length != 5 or prefix != "expr" */
        if (strlen(token) != 5 || strncmp(token, "expr", 4) != 0)
          print2(s, &len, "->expr", 6);
        token = strtok(NULL, ", ");
        if (token != NULL)
        print2(s, &len, ", ", 2);
      }
      xfree(t);
    }
    return(copy_string1(s, len));
  }
}

/* 
   Interpret a word beginning with a dollar sign.
   The two cases $GENERICARGS and $HEADER print directly to the file. 
   All other cases print to the buffer. This was done to because it 
   was difficult to alter the grammar to print it out from the buffer
   in these two places.
   As time goes on, this procedure may be extended to include NONTERM
   dollarwords. Neither xp_gram.y nor xp_lex.l has to be changed.
   (BJG)
*/

void
do_dollar (char *dollar_word, char *buffer)
{
  if (!in_defaults)
    error("Not in a default definition procedure");
  
  if (buffer)
    buffer[0] = '\0';

  if (strcmp(dollar_word, "$NAME") == 0) { 
    if (buffer)
      sprintf(buffer, op_tab[current_op].name); 
  }
  else if (strcmp(dollar_word, "$OP") == 0) { 
    if (buffer)
      sprintf(buffer, "%d", op_tab[current_op].op_num);
  }
  else if (strcmp(dollar_word, "$EXPR") == 0) {
    if (buffer)
      sprintf(buffer, "%d", op_tab[current_op].expr);
  }
  else if (strcmp(dollar_word, "$CALL_LEVEL") == 0) { 
    if (buffer)
      sprintf(buffer, "NONTERM(call_level(te, %d, %s));",
              op_tab[current_op].op_num, op_tab[current_op].oparglist);
  }
  else if (strcmp(dollar_word, "$CALLDOWN") == 0) { 
    if (buffer)
      sprintf(buffer, "NONTERM(call_down(te, 0, %d, %s));",
              op_tab[current_op].op_num, op_tab[current_op].oparglist);
  }
  else if ((strlen(dollar_word) > 9)
           && (strncmp(dollar_word, "$CALLDOWN", 9) == 0)) { 

    /* Then call down substituting the argument number in the 
       call_down expression. */

    char narglist[MAX_IDENT_LEN];
    int narg;
    char body[20];
    sscanf(dollar_word, "$CALLDOWN%d", &narg);
    
    if (op_tab[current_op].num_arg == 0) { 
      if (buffer)
        sprintf(buffer, "NONTERM(call_down(te, %d, %d, %s));",
                get_path_num(dollar_word), op_tab[current_op].op_num,
                op_tab[current_op].oparglist);
    }
    else {
      if (op_tab[current_op].param[0] == CUR) { 
        if (buffer) {
          /* replace "cursor0" with "cursor%d", narg (BJG) */ 
          sprintf(body, "cursor%d", narg);
          replace_string(op_tab[current_op].oparglist, "cursor0", body, narglist);
          sprintf(buffer, "NONTERM(call_down(te, %d, %d, %s));",
                  get_path_num(dollar_word), op_tab[current_op].op_num, narglist);
        }
      }
      else if (op_tab[current_op].param[0] == CON) {
        if (buffer) {
          /* replace "container0" with "container%d", narg (BJG) */
          sprintf(body, "container%d", narg);
          replace_string(op_tab[current_op].oparglist, "container0",
                         body, narglist);
          sprintf(buffer, "NONTERM(call_down(te, %d, %d, %s));",
                  get_path_num(dollar_word), op_tab[current_op].op_num, narglist);
        }
      }
    }
  }
  else if (strcmp(dollar_word, "$STRNAME") == 0) { 
    if (buffer)
      sprintf(buffer, "\"%s\"", op_tab[current_op].name);
  }
  else if (strcmp(dollar_word, "$GENSEMI") == 0) { 
    if (!op_tab[current_op].expr && buffer) {
      /* i.e. a procedure */
      sprintf(buffer, "NONTERM(terminal_string1(\";\"));");
    }
  }
  else if (strcmp(dollar_word, "$HEADER") == 0) {
    int curr_op;
    out(op_tab[current_op].proc, layer_name); 
    set_vars(current_op); 
    curr_op = op_tab[current_op].op_num;
    if (retrieval_op(curr_op))
      retrieval_layer_header(curr_op, op_tab[current_op].constname, "cursor0");
  }
  else if (strcmp(dollar_word, "$GENERICARGS") == 0) {
    char *s = oparglist_to_generic_arguments(op_tab[current_op].oparglist);
    /* The string s may contain both a printf format string and arguments. */
    out("NONTERM(terminal_vstring(%s));", s);
    xfree(s);
  }
  else { 
    error("Unknown $ argument");
  }
}

/*****************************************************************************/
/*                  Cursor and container function actions.                   */
/*****************************************************************************/

static void
func_action (char *func_name, char *curs_or_cont_name, char *opt_literal)
{
  if (get_param_num(curs_or_cont_name) != 0)
    error("%s parameter of %s should not be indexed",
          (has_container_arg) ? "container" : "cursor",
          func_name);
  out("static NODE * %s(TE *te, %s_ARG *%s0 ",
      func_name,
      (has_container_arg) ? "CONT" : "CURS",
      (has_container_arg) ? "container" : "cursor");
  if (strcmp(opt_literal, "") != 0) 
    out(", %s ", opt_literal);
  out(")");

  print_local_vars  = TRUE;
  print_return      = TRUE;
  delete_operation  = FALSE;
}

void
cursor_func_action (char *func_name, char *curs_name, char *opt_literal)
{
  has_cursor_arg = TRUE;
  if (strstr(opt_literal, "container") != NULL)
    has_container_arg = TRUE;
  else
    has_container_arg = FALSE;
  func_action(func_name, curs_name, opt_literal);
}

void
container_func_action (char *func_name, char *cont_name, char *opt_literal)
{
  has_container_arg = TRUE;
  if (strstr(opt_literal, "cursor") != NULL)
    has_cursor_arg = TRUE;
  else
    has_cursor_arg = FALSE;
  func_action(func_name, cont_name, opt_literal);
}

/*****************************************************************************/
/*                  Default cursor and container function actions.           */
/*****************************************************************************/

static void
def_func_action (char *dollar_word)
{
  in_defaults       = TRUE;
  print_local_vars  = TRUE;
  print_return      = TRUE;
  delete_operation  = FALSE;

  if (strcmp(dollar_word, "$HEADER"))
    error("$HEADER not beginning of definition");

  do_dollar(dollar_word, NULL);
}

void
def_cursor_func_action (char *dollar_word)
{
  has_container_arg = FALSE;
  has_cursor_arg = TRUE;
  def_func_action(dollar_word);
}

void
def_container_func_action (char *dollar_word)
{
  has_container_arg = TRUE;
  has_cursor_arg = FALSE;
  def_func_action(dollar_word);
}

/*****************************************************************************/
/*                  Identifier declaration action.                           */
/*****************************************************************************/

void
identifier_declaration_action (char *identifier_name)
{
  /* See if identifier_name is a base type.  If not, it must be a typedef. */

  PCLASS p = base_type(identifier_name);

  /* Special case hack to handle unsigned (JAT) */
  if (p == ERR) {
    if (strcmp(identifier_name, "unsigned") == 0)
      p = IN;
    member_ctype->uclass = UNS;
  }
  if (p != ERR) {
    strcpy(member_type, "NULL");
    left_expand(member_ctype, new_ptype(p, UND, NULL));
  }
  else {
    parse_error("non-base type used: %s", identifier_name);
    sprintf(member_type, "symtab_lookup(symtab[OTH], \"%s\")", identifier_name);
    left_expand(member_ctype, new_ptype(TDF, UND, NULL));
  }
}

/*****************************************************************************/
/*                  ikeyword and ckeyword actions.                           */
/*****************************************************************************/

/*
   Arguments:
     s = Output string:    results are sprintf()ed into this string.
     t = Input token:      used for error reporting only.
     x = xform string:     string to print if k == NULL && c == NULL
                             or if this is an xform operation.
     k = container string: string to print if c == NULL or the
                             operation has a container argument.
     c = cursor string:    string to print if k == NULL or the
                             operation does not have a container argument.
     h = schema string:    string to print if the
                             operation has a schema argument. */

void
ikeyword_action (char *s, char *t, char *x, char *k, char *c, char *h, ...)
{
  va_list args;

  va_start(args, h);

  if ((k == NULL && c == NULL) || (x != NULL && in_xform_proc))
  {
    /* print x */
    if (x == (char *) -1)
      parse_error("cannot translate %s in xform operation", t);
    else
      vsprintf(s, x, args);
  }
#if 1
  else if (h != NULL && has_schema_arg)
  {
    /* print h */
    vsprintf(s, h, args);
  }
#endif
  else if ((c == NULL) || (k != NULL && has_container_arg))
  {
    /* print k */
    if (k == (char *) -1)
      parse_error("cannot translate %s in container operation", t);
    else
      vsprintf(s, k, args);
  }
  else
    /* print c */
    vsprintf(s, c, args);

  va_end(args);
}

void
ckeyword_action (char *k, char *c, char *h, ...)
{
  char format[MAX_IDENT_LEN];
  char s[MAX_IDENT_LEN*3];
  va_list args;
  
  strcpy(format, "NONTERM(terminal_vstring(");
#if 0
  /* This was the code before I added the schema argument h. */
  strcat(format, (c == NULL || has_container_arg) ? k : c);
#else
  if (h != NULL && has_schema_arg)
    strcat(format, h);
  else if (c == NULL || has_container_arg)
    strcat(format, k);
  else
    strcat(format, c);
#endif
  strcat(format, "));");
  assert(strlen(format) < MAX_IDENT_LEN);

  va_start(args, h);
  vsprintf(s, format, args);
  va_end(args);

  jettison();
  out(s);
}

/*****************************************************************************/
/*                  Container id and name.                                   */
/*****************************************************************************/

char *
xp_container_id (void)
{
  if (in_xform_proc)
    return("container0->ctype->cctype->container_id");
  else if (in_ddlhint_proc)
    /* Container id is unknown (unassigned) in ddlhint, because
       container_declaration_ident3() is called after ddlhint. */
    return("UNKNOWN_CONT_ID");
  else if (has_cursor_arg)
    return("cursor0->container_id");
  else if (has_container_arg)
    return("container0->container_id");
  else {
    /* Unknown container id. */
#if 0
    warning(2, "xp_container_id: cannot determine container id,"
               " providing default of %d", UNKNOWN_CONT_ID);
#endif
    return("UNKNOWN_CONT_ID");
  }
}

char *
xp_container_name (void)
{
  if (in_xform_proc)
    return("P2_cont_name");
  else if (in_ddlhint_proc)
    return("(char *) argv[0]");
  else {
    /* Unknown container name. */
#if 0
    warning(2, "xp_container_name: cannot determine container name,"
               " providing default of \"P2_default\"");
#endif
    return("\"P2_default\"");
  }
}
