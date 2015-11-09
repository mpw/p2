/* $Id: ref-util.h,v 45.0 1997/09/19 05:47:00 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Reference utility declarations. */

#ifndef INCLUDE_REF_UTIL_H
#define INCLUDE_REF_UTIL_H

/************************************************************************/
/*              External declarations.                                  */
/************************************************************************/

extern int     cnum;
extern int     pnum;
extern char    *realm_param;

/************************************************************************/
/*              Function prototypes.                                    */
/************************************************************************/

void    kref_util(char *container);
void    kref_util_array(char *container);
void    iref_util(void);
void    iref_util_array(void);
void    ref_util(char *cursor);
void    ref_util_array(char *cursor);
void    sref_util(char *schema);

int     get_param_num(char *s);
int     get_path_num(char *s);

#endif /* INCLUDE_REF_UTIL_H */
