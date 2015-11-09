/* $Id: P2_paces.h,v 45.2 1997/09/29 03:50:13 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

#ifndef INCLUDE_P2_PACES_H
#define INCLUDE_P2_PACES_H

/*****************************************************************************/
/*                  Booleans.                                                */
/*****************************************************************************/

/* Define FALSE, TRUE, and BOOLEAN if not already defined (e.g. by AIX) */
 
#ifndef FALSE
#define FALSE 0
#endif /* FALSE */
 
#ifndef TRUE
#define TRUE 1
#endif /* TRUE */
 
#ifndef BOOLEAN
#define BOOLEAN int
#endif /* BOOLEAN */

/*****************************************************************************/
/*                  Iterator and directions.                                 */
/*****************************************************************************/

#if 0

#define P2_ITERATOR      foreach
#define P2_ASCENDING     ascending
#define P2_DESCENDING    descending

#else

#define P2_ITERATOR      rofeach
#define P2_ASCENDING     descending
#define P2_DESCENDING    ascending

#endif

/*****************************************************************************/
/*                  Layers and annotations.                                  */
/*****************************************************************************/

/*** Retrieval layer. ***/

#if 0
#define P2_LAYER1        slist
#elif 0
#define P2_LAYER1        dlist
#elif 0
#define P2_LAYER1        odlist
#elif 1
#define P2_LAYER1        bintree
#else
#define P2_LAYER1        splaytree
#endif

#if 0
/* slist, dlist */
#define P2_LAYER1_ANNOTE(KEY)
#define P2_LAYER1_SCHEMA_ANNOTE(CONTAINER, KEY)
#else
/* odlist, bintree, splaytree. */
#define P2_LAYER1_ANNOTE(KEY) \
  P2_LAYER1 key is KEY
#define P2_LAYER1_SCHEMA_ANNOTE(CONTAINER, KEY) \
  P2_LAYER1 key of CONTAINER is KEY
#endif

/*** Orderby layer. ****/

#if 1
#define P2_ORDERBY_LAYER orderby_fast
#else
#define P2_ORDERBY_LAYER orderby_smart
#endif

/*** Bottom layer. ***/

/* The layers array and qsort should be interchangable (both import
   the mem realm and export the ds realm).  Paces files should use
   P2_BOTTOM_LAYER and P2_BOTTOM_ANNOTE or P2_BOTTOM_SCHEMA_ANNOTE
   instead of these layers, except in regression tests that
   demonstrate a bug that appeared in one, but not another. */

#if 0

#define P2_BOTTOM_LAYER \
   array[transient]
#define P2_BOTTOM_ANNOTE(KEY, SIZE) \
   array size is SIZE;
#define P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
   array size of CONTAINER is SIZE;

#elif 1

#define P2_BOTTOM_LAYER \
   hash[array[transient]]
#define P2_BOTTOM_ANNOTE(KEY, SIZE) \
   hash key is KEY with size SIZE; \
   array size is SIZE;
#define P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
   hash key of CONTAINER is KEY with size SIZE; \
   array size of CONTAINER is SIZE;

#else

#define P2_BOTTOM_LAYER \
   qsort[transient]
#define P2_BOTTOM_ANNOTE(KEY, SIZE) \
   qsort key is KEY with size SIZE;
#define P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
   qsort key of CONTAINER is KEY with size SIZE;

#endif

/*** Deletion layer ***/

/* The layers delflag and avail should be interchangable (both implement
   the special operation delete(), and import and export the ds realm).
   Paces files should use P2_DELFLAG_LAYER instead of these layers,
   except in regression tests that demonstrate a bug that appeared in
   one, but not the other. */

#if 0
#define P2_DELFLAG_LAYER delflag
#else
#define P2_DELFLAG_LAYER avail
#endif

/*****************************************************************************/
/*                  Transactions                                             */
/*****************************************************************************/

#if 1
/* Works??? */
#define P2_PROTOCOL_LAYER protocol_fine
#elif 1
/* Works: paces which sleep in the middle of a transaction
   that has acquired a lock in P2_LOCK_X mode
   must explicitly use a different protocol layer. */
#define P2_PROTOCOL_LAYER protocol_coarse
#elif 1
/* Works: paces which sleep in the middle of a transaction
   (all transactions acquire a lock in P2_LOCK_X mode)
   must explicitly use a different protocol layer. */
#define P2_PROTOCOL_LAYER protocol_xact_mutex
#else
/* Works. */
#define P2_PROTOCOL_LAYER null
#endif

#if 1

#if !defined(P2_LOG_LAYER)
#define P2_LOG_LAYER log_async
#endif /* P2_LOG_LAYER */

#define P2_XACT_TYPEX(PROTOCOL, BOTTOM_LAYER) \
  conceptual[P2_LOG_LAYER[ \
    xact[PROTOCOL[lock[process[ \
      avail[BOTTOM_LAYER]]]]]]]
#define P2_XACT_ANNOTE(CONTAINER, KEY, SIZE) \
  P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE)

#elif 0

#if !defined(P2_LOG_LAYER)
#define P2_LOG_LAYER log_transient
#endif /* P2_LOG_LAYER */

#define P2_XACT_TYPEX(PROTOCOL, BOTTOM_LAYER) \
  conceptual[P2_LOG_LAYER[xact[PROTOCOL[lock[process[ \
    cardinality[avail[BOTTOM_LAYER]]]]]]]]
#define P2_XACT_ANNOTE(CONTAINER, KEY, SIZE) \
  P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE)

#else

#if !defined(P2_LOG_LAYER)
#define P2_LOG_LAYER log_tid_hack
#endif /* P2_LOG_LAYER */

#define P2_XACT_TYPEX(PROTOCOL, BOTTOM_LAYER) \
  conceptual[P2_LOG_LAYER[xact[PROTOCOL[lock[process[ \
    cardinality[avail[BOTTOM_LAYER]]]]]]]]
#define P2_XACT_ANNOTE(CONTAINER, KEY, SIZE) \
  P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE)

#endif

/*****************************************************************************/
/*                  Element.                                                 */
/*****************************************************************************/

typedef struct {
  int i;
} P2_PACES_ELEMENT;

/*****************************************************************************/
/*                  Type expressions and annotations.                        */
/*****************************************************************************/

#define P2_PACES_TYPEX \
   conceptual[P2_LAYER1[P2_DELFLAG_LAYER[P2_BOTTOM_LAYER]]]
#define P2_PACES_ANNOTE(KEY, SIZE) \
   P2_BOTTOM_ANNOTE(KEY, SIZE) \
   P2_LAYER1_ANNOTE(KEY)
#define P2_PACES_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
   P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
   P2_LAYER1_SCHEMA_ANNOTE(CONTAINER, KEY)

#if 0
/* No orderby. */
#define P2_COMPCURS_TYPEX       top2link[nloops[linkterm[ \
                                 top2ds[inbetween[qualify[ \
                                   P2_DELFLAG_LAYER[P2_BOTTOM_LAYER]]]]]]]
#elif 1
/* orderby, but no conceptual. */
#define P2_COMPCURS_TYPEX       top2link[nloops[linkterm[ \
                                 top2ds[P2_ORDERBY_LAYER[inbetween[qualify[ \
                                   P2_DELFLAG_LAYER[P2_BOTTOM_LAYER]]], \
                                   slist[malloc[transient]]]]]]]
#else
/* concential. */
#define P2_COMPCURS_TYPEX       top2link[nloops[linkterm[ \
                                 conceptual[ \
                                   P2_DELFLAG_LAYER[P2_BOTTOM_LAYER]]]]]
#endif

#define P2_COMPCURS_ANNOTE(KEY, SIZE) \
          P2_BOTTOM_ANNOTE(KEY, SIZE)
#define P2_COMPCURS_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE) \
          P2_BOTTOM_SCHEMA_ANNOTE(CONTAINER, KEY, SIZE)

#endif /* INCLUDE_P2_PACES_H */
