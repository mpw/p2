/* $Id: qopt.h,v 45.0 1997/09/19 05:40:52 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Query optimization declarations. */

#ifndef INCLUDE_QOPT_H
#define INCLUDE_QOPT_H

/*****************************************************************************/
/*                  Cost: "Asymptotic Complexity" aka "big-O"                */
/*****************************************************************************/

/* Retrieval costs. */

#define CONSTANT_TIME_QOPT_COST  1    /* Cost of primary key retrieval O(1) */
#define LOG_TIME_QOPT_COST       10   /* Cost of binary search O(log n) */
#define LINEAR_TIME_QOPT_COST    1000 /* Cost of scanning O(n) */
#define QSORT_QOPT_COST          2500 /* Cost of quicksorting O(n log n) */
#define NLOOPS_QOPT_COST         5000 /* Cost of nested loops O(n^2) */

/* The designated layer will process the join. */
#define MIN_QOPT_COST            0

/* If a query has cost MAX_QOPT_COST, then the query cannot be processed. */
#define MAX_QOPT_COST            100000  /* Maximum cost O(infinity) */

/*****************************************************************************/
/*                  Selectivities                                            */
/*****************************************************************************/

#define RANGE_QOPT_SEL          0.25     /* selectivity of range predicate */

/*****************************************************************************/
/*                  Factor: "Constant Factor" aka "c"                        */
/*****************************************************************************/

#define PTR_FOLLOWING_QOPT_FACTOR     1.1  /* cost of following a pointer */
#define ARRAY_QOPT_FACTOR             1.2  /* cost of array retrieval */
#define HASH_COMPUTATION_QOPT_FACTOR 10.0  /* cost of computing a hash fn */
#define HASH_BUCKET_QOPT_FACTOR       3.0  /* ratio empty/non-empty buckets */

#endif /* INCLUDE_QOPT_H */
