/* $Id: ref-util.c,v 45.1 1997/09/19 07:51:49 jthomas Exp $ */
/* Copyright (C) 1995, The University of Texas at Austin. */

/* Reference utility definitions. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>      /* strcpy() */

#include "error.h"       /* assertion_failed() */
#include "field.h"       /* is_basic_container_field() */
#include "op-tab.h"      /* DS */
#include "rlist.h"       /* RLIST */
#include "string-util.h" /* last_char */
#include "util.h"        /* TRUE */
#include "xp-actions.h"  /* has_container_arg */
#include "xp-io.h"       /* out() */

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

/* ref parameters. */

int     pnum;           /* Parameter numbe. */
int     cnum;           /* Numeric tag. */
char    *realm_param;   /* Realm parameter. */

/************************************************************************/
/*              label, param, and path number.                          */
/************************************************************************/

/* For maintenance:
   get_label_num and get_param_num are ALMOST identical. (DSB) */

static int
get_label_num (char *s) 
{
  char c = last_char(s);
  
  if (c >= '0' && c <= '9')
    return ((int) c - '0');
  return(0);
} 

int
get_param_num (char *s)
{
#if 0
#if 0 
  char c = last_char(s);
 
  if (s[0] == 'c' && (s[1]=='u' || s[1]=='o')) {
    if (c >= '0' && c <= '9')
      return(((int) c - '0')/2);
    else
      return(0);
  }
#else
  if (c >= '0' && c <= '9')
    return ((int) c - '0');
  return(0);
#endif
#else
  /* Note: get_label_num and get_param_num are EXACTLY identical. (JAT) */
  return(get_label_num(s));
#endif
}

int
get_path_num (char *s)
{
  int i = get_param_num(s);
  return(path[i]);
}

/************************************************************************/
/*              get_realm_param                                         */
/************************************************************************/

static char *
get_realm_param (char *s)
{
  char *result = NULL;
  if (params_rlist != NULL) {
    int i = get_path_num(s);
    RLIST *p;

    for (p = params_rlist; i > 0; p = p->next, i--);

    switch (p->type) {
    case DS:
      result = "DS";
      break;
    case MEM:
      result = "MEM"; 
      break;
    case TOP:
      result = "TOP";
      break;
    case TOPLINK:
      result = "TOPLINK";
      break;
    case LINK:
      result = "LINK";
      break;
    case BOTTOM:
      result = "BOTTOM";
      break;
#ifndef NDEBUG
    default:
      assertion_failed("illegal realm param %d", p->type);
#endif
    }
  }
  return(result);
}

/************************************************************************/
/*              sref_util.                                              */
/************************************************************************/

/* Schema dot reference. */

void
sref_util (char *schema)
{
#if 0
   out("P2_rf = terminal_vstring(\"(%%s).%%s%%d\", %s->expr, %s,"
       "te->layerno);", schema, field_val);
#else
   out("P2_rf = terminal_vstring(\"(%%s).%s\", %s->expr);",
       field_val, schema);
#endif
}

/************************************************************************/
/*              kref_util and kref_util_array.                          */
/************************************************************************/

void
kref_util (char *container)
{  
  /* Step 1:  set values for ref parameters */

  pnum = get_path_num(container);
  cnum = get_param_num(container);
  realm_param = get_realm_param(container);

  /* Step 2: generate the right code */

  if (force_field_ref)
  {
    /* This feature is not used in any existing layer. (JAT) */
    assert(unknown_fld);
    out("P2_rf = terminal_vstring(\"(%%s).%%s\", %s->expr, %s);",
        container, field_val);
  }
  else
  {
    if (has_container_arg)
    {
      if (unknown_fld) 
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d\", %s->expr, %s,"
            "te->layerno);", container, field_val);
      else
        if (is_basic_container_field(field_val))
          out("P2_rf = terminal_vstring(\"(%%s).%s\", %s->expr);",
              field_val, container);
        else
          out("P2_rf = terminal_vstring(\"(%%s).%s%%d\", %s->expr,"
              "te->layerno);", field_val, container);
    }
    else
    {
      if (unknown_fld) 
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d\", cursor%d->cont, %s,"
            "te->layerno);", pnum, field_val);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d\", cursor%d->cont,"
            "te->layerno);", field_val, pnum);
    }
  }

  /* Step 3: remember this is not a cursor or object field that
     is being referenced */

  cursor_field = FALSE;
  obj_field    = FALSE;
}

void
kref_util_array (char *container)
{
  /* Step 1:  set values for ref parameters */

  pnum = get_path_num(container);
  cnum = get_param_num(container);
  realm_param = get_realm_param(container);

  /* Step 2: generate the right code  - assume that there is no
     array field that is basic to a cursor */

  if (has_container_arg) {
    if (unknown_fld) {
      if (unknown_idx)
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d[%%s]\", %s->expr, %s,"
            "te->layerno, %s);", container, field_val, index_val);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d[%s]\", %s->expr, %s,"
            "te->layerno);", index_val, container, field_val);
    }
    else {
      if (unknown_idx)
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d[%%s]\", %s->expr,"
            "te->layerno, %s);", field_val, container, index_val);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d[%s]\", %s->expr,"
            "te->layerno);", field_val, index_val, container);
    }
  }
  else {
    if (unknown_fld) {
      if (unknown_idx) 
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d[%%s]\", cursor%d->cont, %s,"
            "te->layerno, %s);", pnum, field_val, index_val);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%%s%%d[%s]\", cursor%d->cont, %s,"
            "te->layerno);", index_val, pnum, field_val);
    }
    else {
      if (unknown_idx)
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d[%%s]\", cursor%d->cont,"
            "te->layerno, %s);", field_val, pnum, index_val);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d[%s]\", cursor%d->cont,"
            "te->layerno);", field_val, index_val, pnum);
    }
  }

  /* Step 3: remember this is not a cursor or object field that
     is being referenced */

  cursor_field = FALSE;
  obj_field    = FALSE;
}

/************************************************************************/
/*              iref_util and iref_util_array.                          */
/************************************************************************/

void
iref_util (void)
{
  /* Note: this translation is not always correct.  It assumes
     that expressions like:

            cursor.field1->field2->...->fieldn

     ALWAYS reference the same container as the cursor.  This
     makes sense for list and binary tree types of layers, but
     does not make sense for pointer based joins.  Because
     xp is not a full-fledged compiler with a symbol table,
     if field2 (for example) references another container, then
     one must break up the above expression into assignments
     that are xp legal:

            cursor2.obj = cursor.field1->field2;
            cursor3.obj = cursor2.field3;
            ...
            cursorN.obj = cursorN-1.fieldN-1;
  */

  if (unknown_fld) {
     out("{"
         "CURS_ARG c;"
         "char id[MAX_IDENT_LEN];");
     if (has_container_arg)
       out("memcpy(&c,container%d,sizeof(CONT_ARG));", cnum);
     else
       out("memcpy(&c,cursor%d,sizeof(CURS_ARG));", cnum);
     out("sprint_ptree(c.expr, P2_rf);"
         "strcpy(id,%s);", field_val);
     out("P2_rf = call_down(te, %d, IREF_OP, 2, &c, &id);", pnum);
     out("}");
  }
  else {
     out("{"
         "CURS_ARG c;"
         "char id[MAX_IDENT_LEN];");
     if (has_container_arg)
       out("memcpy(&c,container%d,sizeof(CONT_ARG));", cnum);
     else
       out("memcpy(&c,cursor%d,sizeof(CURS_ARG));", cnum);
     out("sprint_ptree(c.expr, P2_rf);"
         "sprintf(id,\"%s%%d\",te->layerno);", field_val);
     out("P2_rf = call_down(te, %d, IREF_OP, 2, &c, &id);", pnum);
     out("}");
  }
  strcpy(rf_field, field_val);

  /* Step 3: remember this is not a cursor or object field that
             is being referenced */

  cursor_field = FALSE;
  obj_field    = FALSE;
}

void
iref_util_array (void)
{
   /* Note: this translation is not always correct.  It assumes
      that expressions like:

             cursor.field1->field2->...->fieldn

      ALWAYS reference the same container as the cursor.  This
      makes sense for list and binary tree types of layers, but
      does not make sense for pointer based joins.  Because
      xp is not a full-fledged compiler with a symbol table,
      if field2 (for example) references another container, then
      one must break up the above expression into assignments
      that are xp legal:

             cursor2.obj = cursor.field1->field2;
             cursor3.obj = cursor2.field3;
             ...
             cursorN.obj = cursorN-1.fieldN-1;
   */

   /* Step 1: Initialize lhs variable (to the value of the field that
      is being referenced). */

   if (unknown_fld) {
      if (unknown_idx)
         out("sprintf(P2_lhs,\"%%s%%d[%%s]\", %s, te->layerno, %s);",
             field_val, index_val);
      else
         out("sprintf(P2_lhs,\"%%s%%d[%s]\", %s, te->layerno);",
             index_val, field_val);
   }
   else {
      if (unknown_idx)
         out("sprintf(P2_lhs,\"%s%%d[%%s]\", te->layerno, %s);",
             field_val, index_val);
      else
         out("sprintf(P2_lhs,\"%s%%d[%s]\", te->layerno);",
             field_val, index_val);
   }

   /* Step 2: The values for cnum, pnum, realm_param, were set in
      ref_util_array or ref_util.  All we have to do is to generate
      the iref now. */

   out("{"
       "CURS_ARG c;"
       "memcpy(&c,cursor%d,sizeof(CURS_ARG));", cnum);
   out("sprint_ptree(c.expr, P2_rf);"
       "P2_rf = call_down(te, %d, IREF_OP, 2, &c, P2_lhs);", pnum);
   out("}");
   strcpy(rf_field, "P2_lhs");

   /* Step 3: Remember this is not a cursor or object field that is
      being referenced. */

   cursor_field = FALSE;
   obj_field    = FALSE;
}

/************************************************************************/
/*              ref_util and ref_util_array.                            */
/************************************************************************/

void
ref_util (char *cursor)
{
  cnum = get_param_num(cursor);
  pnum = get_path_num(cursor);
  realm_param = get_realm_param(cursor);
  
  if (force_field_ref)
  {
    if (unknown_fld)
      out("P2_rf = terminal_vstring(\"(%%s).%%s\", %s->expr, %s);",
          cursor, field_val);
    else
      out("P2_rf = terminal_vstring(\"(%%s).%s%%d\", %s->expr, te->layerno);",
          field_val, cursor);
    cursor_field = TRUE;
    obj_field    = FALSE;
  }
  else
    if (!unknown_fld && is_cursor_field(field_val))
    {
      cursor_field = TRUE;
      if (strcmp(field_val, "obj") == 0)
        obj_field = TRUE;
      else 
        obj_field = FALSE;
      if (is_basic_cursor_field(field_val))
        out("P2_rf = terminal_vstring(\"(%%s).%s\", %s->expr);",
            field_val, cursor);
      else
        out("P2_rf = terminal_vstring(\"(%%s).%s%%d\", %s->expr, te->layerno);",
            field_val, cursor);
    }
    else
    {
      /* must be a reference to an element field */

      cursor_field = FALSE;
      obj_field    = FALSE;
      if (call_below(REF_OP, pnum))
      {
        if (unknown_fld)
        {
          out("{"
              "char id[MAX_IDENT_LEN];"
              "strcpy(id,%s);", field_val); 
          out("P2_rf = call_down(te, %d, REF_OP, 2, %s, id);", pnum, cursor);
          out("}");
        }
        else
        {
          out("{"
              "char id[MAX_IDENT_LEN];"
              "sprintf(id,\"%s%%d\",te->layerno);", field_val);
          out("P2_rf = call_down(te, %d, REF_OP, 2, %s, id);", pnum, cursor);
          out("}");
        }
      }
      else
      {
#if 0
        if (!unknown_fld)
          out("P2_rf = terminal_vstring(\"(%%s).obj->%%s\", %s->expr, field_val);",
              cursor);
        else
#else
        if (!unknown_fld)
          out("P2_rf = terminal_vstring(\"(%%s).obj->%s%%d\", %s->expr, te->layerno);",
              field_val, cursor);
        else
#endif
          out("P2_rf = terminal_vstring(\"(%%s).obj->%%s\", %s->expr, %s);",
              cursor, field_val);
      }
    }
  strcpy(rf_field, field_val);
}

/* Used to process references for arrays. (DSB) */

void
ref_util_array (char *cursor)
{ 
  /* Step 1: Initialize lhs variable (to the value of the field that
     is being referenced). */

  if (unknown_fld) {
    if (unknown_idx)
      out("sprintf(P2_lhs,\"%%s%%d[%%s]\", %s, te->layerno, %s);",
          field_val, index_val);
    else
      out("sprintf(P2_lhs,\"%%s%%d[%s]\", %s, te->layerno);",
          field_val, index_val);
  }
  else {
    if (unknown_idx)
      out("sprintf(P2_lhs,\"%s%%d[%%s]\", te->layerno, %s);",
          field_val, index_val);
    else 
      out("sprintf(P2_lhs,\"%s%%d[%s]\", te->layerno);",
          field_val, index_val);
  }

  /* Step 2: Initialize variables for update. */

  cnum = get_param_num(cursor);
  pnum = get_path_num(cursor);
  realm_param = get_realm_param(cursor);

  /* Step 3: Assume that basic fields of cursors are not arrays
     and generate the appropriate terminals. */

  if (is_cursor_field(field_val)) {
    cursor_field = TRUE;
    obj_field    = FALSE;
    out("P2_rf = terminal_vstring(\"(%%s).%%s\", %s->expr, P2_lhs);");
  }
  else {

    /* must be a reference to an element field */

    cursor_field = FALSE;
    obj_field    = FALSE;
    if (call_below(REF_OP, pnum)) {
      out("P2_rf = call_down(te, %d, REF_OP, 2, %s, P2_lhs);",
          pnum, cursor);
    }
    else {
      out("P2_rf = terminal_vstring(\"(%%s).obj->%%s\", %s->expr, P2_lhs);",
          cursor);
    }
    strcpy(rf_field, "P2_lhs");
  }
}
