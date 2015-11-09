/* $Id: make_3_j.c,v 45.0 1997/09/19 05:46:09 jthomas Exp $ */
/* Copyright (C) 1996, The University of Texas at Austin. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h> /* atan2() */

#ifndef PI
#define PI 3.1415927
#endif

#define MOD_NUM 100
#define get_y(val) (val % MOD_NUM)
#define get_x(val) ((int) (val)/MOD_NUM)

/******************************************************************************/
/***     Routines to calculate line intersections.                          ***/
/******************************************************************************/

float
get_angle (int p1, int p2)
{
  int delta_x, delta_y;

  /* Calculate (x2 - x1) and (y2 - y1).  The points are passed in the
   * form x1y1 and x2y2.  get_x() and get_y() are passed these points
   * and return the x and y values respectively.  For example,
   * get_x(1020) returns 10. */
  delta_x = get_x(p2) - get_x(p1);
  delta_y = get_y(p2) - get_y(p1);

  if (delta_x == 0) {
    if (delta_y > 0)
      return(PI/2);
    else if (delta_y < 0)
      return(-PI/2);
  }
  else if (delta_y == 0) {
    if (delta_x > 0)
      return(0.0);
    else if (delta_x < 0)
      return(PI);
  }
  return((float) atan2((double) delta_y,(double) delta_x));
}

float
inscribed_angle (int basepoint, int p1, int p2)
{
  float angle1, angle2, temp;

  /* Get the angle between line #1 and the origin and the angle
   * between line #2 and the origin, and then subtract these values. */
  angle1 = get_angle(basepoint,p1);
  angle2 = get_angle(basepoint,p2);
  temp = angle1 - angle2;
  if (temp < 0.0)
    temp = -temp;

  /* We always want the smaller of the two angles inscribed, so if the
   * answer is greater than 180 degrees, calculate the smaller angle and
   * return it. */
  if (temp > PI)
    temp = 2*PI - temp;
  if (temp < 0.0)
    return(-temp);
  return(temp);
}

#if STRING_OPTIMIZATION
int
#else
char *
#endif /* STRING_OPTIMIZATION */

make_3_junction (int base_point, int p1, int p2, int p3, junction *tj)
{
  int shaft,barb1,barb2;
  float angle12, angle13, angle23;
  float sum, sum1213, sum1223, sum1323;
  float delta;

  angle12 = inscribed_angle(base_point,p1,p2);
  angle13 = inscribed_angle(base_point,p1,p3);
  angle23 = inscribed_angle(base_point,p2,p3);

  sum1213 = angle12 + angle13;
  sum1223 = angle12 + angle23;
  sum1323 = angle13 + angle23;

  if   (sum1213 < sum1223) 
  {
    if   (sum1213 < sum1323) 
    {
      sum = sum1213;
      shaft = p1; barb1 = p2; barb2 = p3;
    }
    else 
    {
      sum = sum1323;
      shaft = p3; barb1 = p1; barb2 = p2;
    }
  }
  else 
  {
    if   (sum1223 < sum1323) 
    {
      sum = sum1223;
      shaft = p2; barb1 = p1; barb2 = p3;
    }
    else 
    {
      sum = sum1323;
      shaft = p3; barb1 = p1; barb2 = p2;
    }
  }

  delta = sum - PI;
  if (delta < 0.0)
    delta = -delta;

  tj->p1 = barb1;
  tj->p2 = shaft;
  tj->p3 = barb2;

#if STRING_OPTIMIZATION
  if   (delta < 0.001)
    return RL_tee ;
  else if   (sum > PI)
    return RL_fork ;
  else return RL_arrow ;
#else
  if   (delta < 0.001)
    return "tee" ;
  else if   (sum > PI)
    return "fork" ;
  else return "arrow" ;
#endif

  tj->p1 = barb1;
  tj->p2 = shaft;
  tj->p3 = barb2;
}
