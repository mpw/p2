/* $Id: io.h,v 45.0 1997/09/19 05:40:47 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* Common Input/Output declarations. */

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#include <stdlib.h> /* size_t */
#include "type.h"   /* NODE */

/*****************************************************************************/
/*                  Constants.                                               */
/*****************************************************************************/

#define SPRINT_BUF_SIZE 100000

/*****************************************************************************/
/*                  External declarations.                                   */
/*****************************************************************************/

extern int print_liner_pragma;

/*****************************************************************************/
/*                  Function prototypes.                                     */
/*****************************************************************************/

void    assert_all_chars_printable(const char *s);
void    esprint(char *s1, size_t *len1, const char *s2, size_t len2);
void    esprint_ptree(char *s, const NODE *n);
void    esprintf(char *s1, const char *format, ...);
char    *pclass_enum_const_string(PCLASS pclass);
void    print_ptree(const NODE *n);
void    print_ptree1(char *s, size_t *len, const NODE *n);
void    print1(char *s1, size_t *len1, const char *s2);
void    print2(char *s1, size_t *len1, const char *s2, size_t len2);
void    printf1(char *s1, size_t *len1, const char *format, ...);
char    *qclass_enum_const_string(QCLASS qclass);
void    sprint_ctype_as_new_ctype_call(char *s, const CTYPE *ctype);
void    sprint_ptree(char *s, const NODE *n);

#endif /* INCLUDE_IO_H */
