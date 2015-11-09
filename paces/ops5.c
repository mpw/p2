/* $Id: ops5.c,v 45.0 1997/09/19 05:43:54 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

/****************** common leaps/ops5 routines *******************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* all this stuff could be optimized by replacing malloc calls
   with something more efficient */


/****************** push and pop wait-list ***********************/
/*----------------- standard includes ---------------------------*/

void push_wl(void *ob, int time_stamp, int cont)
{
  WLS t_wl ;
  t_wl.cursor_position = ob ;
  t_wl.time_stamp      = time_stamp ;
  t_wl.cont            = cont ;
  insert(wlc,t_wl) ;
}


void pop_wl(void)
{
  /* Step 1: toss top of wait list - return if at end */

  reset_start(wlc);
  if (end_adv(wlc))
    return;
  delete(wlc);
  adv(wlc);

  /* Step 2: continue popping items that are no longer valid
             or the wait list is empty */

  while( !end_adv(wlc) ) {
      if (test_valid(wlc.cont, wlc.cursor_position))
         return;
      delete(wlc);
      adv(wlc);
  }
}


/****************** push and pop wait-stack ***********************/
/*----------------- standard includes ----------------------------*/

void push_ws(void *curs, void *curs_pos, int time_stamp, int cont, 
             VOID_FUNC rule)
{
  WSS t_ws ;

  t_ws.curs            = curs ;
  t_ws.cursor_position = curs_pos;
  t_ws.time_stamp      = time_stamp ;
  t_ws.cont            = cont ;
  t_ws.current_rule    = rule ;
  t_ws.force_fresh     = FALSE;
  insert(wsc, t_ws) ;
}


void pop_ws(void)
{
  /* Step 1: toss top of wait stack - return if at end */

  reset_start(wsc);
  if (end_adv(wsc))
    return;
  delete(wsc);
  adv(wsc);

  /* Step 2: continue popping items that are no longer valid
             or the wait stack is empty */

  while( !end_adv(wsc) ) {
      if (test_valid(wsc.cont, wsc.cursor_position))
         return;
      delete(wsc);
      adv(wsc);
  }
}


/**************** get_next_rule ********************************/
/*--------------- standard include ----------------------------*/

VOID_FUNC get_next_rule()
{
   int list_time  = NEG_TIME;
   int stack_time = NEG_TIME;
   VOID_FUNC rule_to_fire;

   /* Step 1: get the most recent time stamp from the wait stack
              and state stack */

   foreach(wlc) {
      list_time = wlc.time_stamp;
      goto l1;
   }

l1:
   foreach(wsc) {
      stack_time = wsc.time_stamp;
      goto l2;
   };

l2:
   /* Step 2: we're at fix-point if both timestamps are NEG_TIME */

   if ((stack_time == NEG_TIME) && (list_time == NEG_TIME))
      return (VOID_FUNC) FIX_POINT;

   /* Step 3: if dominant object on wait stack, push it onto the
              state stack (as it is likely to be on the state stack
              for a while), and pop it off of the wait-list.  Otherwise
              dominant object on state stack and just continue with
              the execution of the identified rule */

   from_stack = (stack_time >= list_time);
   if (from_wait_list) {
      rule_to_fire = first_rule[ wlc.cont ];
      push_ws( (void*) 0, wlc.cursor_position, wlc.time_stamp, wlc.cont, rule_to_fire );
      pop_wl();
      fresh = TRUE;
      dom_timestamp = wsc.time_stamp;
   }
   else {
      rule_to_fire    = wsc.current_rule;
      fresh           = wsc.force_fresh;
      wsc.force_fresh = FALSE;
   }

   /* Step 3: set the dominant timestamp */

   dom_timestamp = wsc.time_stamp;
   return ( rule_to_fire );
}


/****************  execute_production_system  ******************/


void execute_production_system()
{
VOID_FUNC next_rule;

  for(;;) {
    next_rule = get_next_rule();
    if (next_rule == (VOID_FUNC) FIX_POINT)
      return;
    (*next_rule)();
   }
}


/***************  main ***************************************/


void main(void)
{
   /* Step 1: initialize all containers and cursors */

   init_all();

   /* Step 2: initialize data and start up production system */

   init_data() ; 
   execute_production_system();
}


