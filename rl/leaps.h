/* $Id: leaps.h,v 45.0 1997/09/19 05:46:05 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Standard leaps/ops5 include file (DSB) */
/* This file is included by RL *generated* files. (JAT) */

#ifndef INCLUDE_LEAPS_H
#define INCLUDE_LEAPS_H

/************************************************************************/
/*              Includes.                                               */
/************************************************************************/

#include <stdio.h>
#include <string.h>

/************************************************************************/
/*              Standard constants and macros.                          */
/************************************************************************/

#define L_PAREN '('
#define R_PAREN ')'
#define SPACE ' '

#define WATCH "watch"
#define RUN "run"
#define MAKE "make"
#define EXIT "exit"

#define NILSTR "nil"
#define NILVAL 0

#define LINE_LEN 255
#define TOKEN_LEN 40

#define test_valid(container_num, obj_ptr)   \
         (*valid_vect[container_num])(obj_ptr)

#define push_wl(curs_pos, timestamp, cont) \
     push(0, curs_pos, timestamp, cont, first_rule[cont])

#if SHADOW_OPTIMIZATION
#define push_wl_end(curs_pos, timestamp, cont) \
     push_end(0, curs_pos, timestamp, cont, first_rule[cont])
#endif


/************************************************************************/
/*              Typedefs.                                               */
/************************************************************************/

/* Boolean. */
/* Define FALSE, TRUE, and BOOLEAN if not already defined (eg by AIX) */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef BOOLEAN
#define BOOLEAN int
#endif

typedef BOOLEAN  (BOOL_FUNC)(), (*BOOL_FUNC_PTR)();
typedef void     (VOID_FUNC)(), (*VOID_FUNC_PTR)();
typedef char   FIELDNAME[TOKEN_LEN];

typedef struct   
{
  void          *curs;              /* pointer to stacked cursor */
  void          *cursor_position;   /* pointer to dominant object */
  int           time_stamp ;        /* time stamp of dominant object */
  int           cont ;              /* container id of dominant object */
  VOID_FUNC_PTR current_rule;       /* current rule to fire */
#if NEGATION_OPTIMIZATION
  int           last_timestamp;     /* ts of last join firing */
#endif
} STACK;

/************************************************************************/
/*              Forward refernces.                                      */
/************************************************************************/

void input_format_error(void);
void push(void *curs, void *curs_pos, int timestamp, int cont, VOID_FUNC rule);

#if SHADOW_OPTIMIZATION
void push_end(void *curs, void *curs_pos, int timestamp, int cont,
              VOID_FUNC rule);
#endif

void pop(void);
VOID_FUNC_PTR first_rule[];

/************************************************************************/
/*              Global variables.                                       */
/************************************************************************/

char inp_line[LINE_LEN];   /* input line */
char token[TOKEN_LEN];     /* token */

BOOLEAN   fresh ;                 /* should we allocate new cursor?  */
int       global_counter = 1;     /* global timestamp counter */
int       dom_timestamp;          /* dominant timestamp */
BOOLEAN   watch = FALSE;          /* do we print rule-firings ala leaps? */

#if NEGATION_OPTIMIZATION
int       last_timestamp;         /* time at which join was last fired */
#endif

/************************************************************************/
/*              Stack container declaration.                            */
/************************************************************************/

#if MALLOC_OPTIMIZATION
#define TRANSIENT transient_fast
#else
#define TRANSIENT transient
#endif

typex {
   stack_x  = top2ds_qualify[dlist_deque[avail[malloc[TRANSIENT]]]];
   symbol_x = top2ds_qualify[bintree[malloc[TRANSIENT]]];
}

container <STACK> stored_as stack_x with { } stack;
cursor <stack> top, active;

#endif /* INCLUDE_LEAPS_H */
