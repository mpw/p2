/***************  standard leaps/ops5 include file **************/
/*--------------  standard #defines  ---------------------------*/

#include <stdio.h>
#include <string.h>

#define NEG_TIME  -1
#define FIX_POINT -1

#define L_PAREN '('
#define R_PAREN ')'
#define SPACE ' '

#define RUN "run"
#define MAKE "make"
#define EXIT "exit"

#define LINE_LEN 255
#define TOKEN_LEN 40
#define STRLENGTH 25

#define NUM_RULES 4
#define TUPLE_getsize 2

#define from_wait_list    !from_stack

#define test_valid( container_num, obj_ptr )   \
         (*valid_vect[container_num])(obj_ptr)

#define frule5_1(fire,curs) \
   fire(&curs,&c->b,&c->c,&c->d,&c->e)

#define frule5_2(fire,curs) \
   fire(&c->a,&curs,&c->c,&c->d,&c->e)

#define frule5_3(fire,curs) \
   fire(&c->a,&c->b,&curs,&c->d,&c->e)

#define frule5_4(fire,curs) \
   fire(&c->a,&c->b,&c->c,&curs,&c->e)

#define frule5_5(fire,curs) \
   fire(&c->a,&c->b,&c->c,&c->d,&curs)

#define frule4_1(fire,curs) \
   fire(&curs,&c->b,&c->c,&c->d)

#define frule4_2(fire,curs) \
   fire(&c->a,&curs,&c->c,&c->d)

#define frule4_3(fire,curs) \
   fire(&c->a,&c->b,&curs,&c->d)

#define frule4_4(fire,curs) \
   fire(&c->a,&c->b,&c->c,&curs)

#define frule3_1(fire,curs) \
   fire(&curs,&c->b,&c->c)

#define frule3_2(fire,curs) \
   fire(&c->a,&curs,&c->c)

#define frule3_3(fire,curs) \
   fire(&c->a,&c->b,&curs)

#define frule2_1(fire,curs) \
   fire(&curs,&c->b)

#define frule2_2(fire,curs) \
   fire(&c->a,&curs)

#define frule1_1(fire,curs) \
   fire(&curs)

#define next_rule( f ) wsc.current_rule = f; fresh = TRUE; f(); return;

#define init_c( cursor_type, dom_curs ) \
   cursor_type *c;\
   if (fresh) { \
      c = (cursor_type *) malloc(sizeof( cursor_type )); \
      initk(*c); \
   } \
   else { c = (c_rule2_1 *) wsc.curs; } \
   pos(dom_curs,wsc.cursor_position);
  
#define try( next ) \
   advk( *c ); if (endk(*c)) { next_rule( next ); } 

#define trylast advk(*c); if (endk(*c)) { pop_ws(); return; };
#define trylastc adv(*c); if (end_adv(*c)) { goto fail; }

#define meta( curs1, curs2 ) \
   foreach(curs1) { goto cnt;}; foreach(curs2) { goto cnt; };

#define meta_test( curs ) foreach(curs) { goto fail; }

#define first_stand( curstype, domcurs, nextrule, frule, firerule ) \
     curstype *c; \
     pos( domcurs, wsc.cursor_position ); \
     if (fresh) { \
        c = (curstype *) malloc(sizeof(curstype)); \
        initk(*c); \
     } else { \
        c = (curstype *) wsc.curs; \
        goto cnt; \
     } \
     foreachk( *c ) { 

#define last_stand( curstype, domcurs, nextrule, frule, firerule ) \
        frule(firerule,domcurs); \
        return; \
cnt: }; \
     free(c); wsc.current_rule = nextrule; fresh = TRUE; nextrule();


#define stand( curstype, domcurs, nextrule, frule, firerule ) \
     first_stand( curstype, domcurs, nextrule, frule, firerule ) \
     last_stand( curstype, domcurs, nextrule, frule, firerule )

typedef enum { FALSE, TRUE } BOOL;
typedef BOOL  (*BOOL_FUNC)();
typedef void  (*VOID_FUNC)();



/******************* forward references *************************/

void push_wl(void *ob, int time_stamp, int cont);
void pop_wl(void);
void push_ws(void *curs, void *curs_pos, 
             int time_stamp, int cont, VOID_FUNC rule);
void pop_ws(void);



/******************* container record types *********************/
/*----------- wss, wls are standard includes -------------------*/

typedef struct                   /* wait stack struct */
{
  void       *curs;              /* pointer to stacked cursor */
  void       *cursor_position;   /* pointer to dominant object */
  int        time_stamp ;        /* time stamp of dominant object */
  int        cont ;              /* container id of dominant object */
  VOID_FUNC  current_rule;       /* current rule to fire */
} WSS;

typedef struct              /* wait list struct */
{
  void *cursor_position ;   /* pointer to dominant object */
  int time_stamp ;          /* time stamp of dominant object */
  int cont ;                /* container id of dominant object */
} WLS;


/***************** global variables ******************************/

char inp_line[LINE_LEN] ;   /* input line */
char token[TOKEN_LEN] ;     /* token */

BOOL   from_stack ;         /* is dominant object from wait-stack? */
BOOL   fresh ;              /* should we allocate new cursor?  */
int    global_counter = 0;  /* global timestamp counter */
int    dom_timestamp;       /* dominant timestamp */



/***************** typex declarations ****************************/

/*------------ all are standard includes ------------------------*/

typex {

   ws_x          = top2ds[qualify[inbetween[dlist[malloc[transient]]]]];

   wl_x          = top2ds[qualify[inbetween[dlist[malloc[transient]]]]];

   no_scan_x     = top2ds[qualify[inbetween[ predindx[ vtimestamp[ 
                   delflag[ malloc[ transient ]]]]]]];

   mix_x         = top2ds[qualify[inbetween[ predindx[ dlist[ vtimestamp[
                   delflag[ malloc[ transient ]]]]]]]];

   only_scan_x  = top2ds[qualify[inbetween[ dlist[ vtimestamp[
                  delflag[ malloc[ transient ]]]]]]];

   nostruct_x   = top2ds[qualify[inbetween[ vtimestamp[ delflag[ malloc[ transient ]]]]]];
}

/* note: ws_x is the wait-stack typex; wl_x is the wait-list typex;
         no_scan_x is the typex for containers that are accessed only
            by predicate indices;
         mix_x is the typex for containers that have predicate indices
            and are scanned.
         only_scan_x is the typex for containers that are only scanned */

/**************** standard container declarations **********************/

container <WLS> stored_as wl_x with { } wl;

container <WSS> stored_as ws_x with { } ws;

/****************  wait list and wait stack cursors *****************/

cursor <wl>   wlc;
cursor <ws>   wsc;
