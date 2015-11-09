/* $Id: leaps.c,v 45.0 1997/09/19 05:46:05 jthomas Exp $ */
/* Copyright (C) 1995, The University of Texas at Austin. */

/****************** common leaps/ops5 routines *******************/

/* all this stuff could be optimized by replacing malloc calls
   with something more efficient (DSB) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/****************** push and pop *********************************/

int P2_insert_tail = 0;  /* we need to keep this until we have
                            flavors of insertions */

#if SHADOW_OPTIMIZATION
void push_end(void *curs, void *curs_pos, int time_stamp, int cont,
             VOID_FUNC rule)
{
  STACK s;

  s.curs            = curs ;
  s.cursor_position = curs_pos;
  s.time_stamp      = time_stamp ;
  s.cont            = cont ;
  s.current_rule    = rule ;
#if NEGATION_OPTIMIZATION
  s.last_timestamp  = global_counter;
#endif
  P2_insert_tail    = 1;
  insert(active,s) ;
}
#endif

void push(void *curs, void *curs_pos, int time_stamp, int cont, 
             VOID_FUNC rule)
{
  STACK s;

  s.curs            = curs ;
  s.cursor_position = curs_pos;
  s.time_stamp      = time_stamp ;
  s.cont            = cont ;
  s.current_rule    = rule ;
#if NEGATION_OPTIMIZATION
  s.last_timestamp  = global_counter;
#endif
  insert(active,s) ;
}


void pop(void)
{
  /* Step 1: toss top of stack (there always is a top when
             pop is called */

  reset_start(active);

  /* Step 2: delete top of stack and continue deleting the top
             until the top item is valid or the stack is empty */

  do {
     delete(active);
     adv(active);
  } while ( !end_adv(active) && 
            !test_valid(active.cont, active.cursor_position));
}


/****************  execute_production_system  ******************/


void execute_production_system()
{
  while(1) {
    /* Get the top of the stack. */
    reset_start(top);

    if (end_adv(top)) {
      /* The stack is empty.  We're at a fix-point. */
      break;
    }
    else {
      /* The stack is not empty.  If the dominant object
         has not seeded a join (meaning that its cursor
         is null), set fresh to TRUE.  Otherwise, FRESH
         is FALSE.  Also, set the dominant timestamp and
         return rule to fire. */
      fresh = !top.curs;
      dom_timestamp = top.time_stamp;
      (*top.current_rule)();
    }
  }
}


/************** process keyboard input ***********************/
void process_keyboard_input ( void )
{
BOOLEAN done = FALSE;
char    *t_ptr, *t_ptr2;

  while (!done)
    {
      printf ("\nTop Level> ");
      gets (inp_line);
      t_ptr = strchr (inp_line, L_PAREN);
      if (t_ptr != NULL)
        {
          t_ptr2 = ++t_ptr;
          while (((char) *t_ptr2 != SPACE) &&
                 ((char) *t_ptr2 != R_PAREN))
            {
              t_ptr2++;
            }
          memset (token, 0, TOKEN_LEN);
          strncpy (token, t_ptr, (t_ptr2 - t_ptr));
          if (strcmp (token, EXIT) == 0)
            {
              printf ("Exiting system.\n");
              done = TRUE;
              continue;
            }
          if (strcmp (token, RUN) == 0)
            {
              execute_production_system ();
              fprintf (stderr,"No instances in conflict set.\n");
              continue;
            }
          if (strcmp (token, MAKE) == 0)
            {
               insert_data_tuple ();
               continue;
            }
          if (strcmp (token, WATCH) == 0) 
            {
               sscanf(t_ptr2,"%d", &watch);
               continue;
            }
        }
        printf("*** operation not recognized - no action taken\n");
    }
}


/*************** input format error **************************/

void input_format_error( void )
{
   fprintf(stderr,"input format error - exiting\n");
   exit(1);
}


/***************  main ***************************************/


int
main (void)
{
#if 0
   printf("OPS5c - LEAPS-based OPS5 Compiler\n");
   printf("Release 5.4 (under developement)\n");
   printf("(C) 1988,1989 D.P.Miranker, B.J.Lofaso, A.Chandra Univ. of Texas at Austin\n");
#else
   printf("P2/RL - Reengineered OPS5c - LEAPS-based OPS5 Compiler\n");
   printf("(C) 1994 Don Batory University of Texas at Austin\n");
#endif

   /* Step 1: Initialize all containers and cursors. */
   initialize();

   /* Step 2: Initialize data and start up production system. */
   process_keyboard_input() ; 

   /* Step 3: Finalize all containers. */
   finalize();

   /* Return 0 (EXIT_SUCCESS) */
   return 0;
}


