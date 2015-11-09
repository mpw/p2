# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:40:59 jthomas Exp $
# Copyright (C) 1994, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

srcdir = .

srcroot = ./..
objroot = ..

include ../Makeconfig

#### End of system configuration section. ####

SRCS =		../common/error.c \
		../common/getopt.c \
		../common/getopt1.c \
		../common/io.c \
		../common/lex.c \
		../common/main.c \
	       	../common/op-tab.c \
		../common/string-util.c \
		../common/token-queue.c \
		../common/type.c \
		../common/util.c \
		../common/version.c \
		../common/xmalloc.c \
		ddl.c \
		ddl-gram.tab.c \
		ddl-lex.c \
		ddl-main.c

OBJS =		$(patsubst %,%.o,$(notdir $(basename $(SRCS))))

all:		$(DDL)

install:	all
		$(INSTALL_PROGRAM) $(DDL) $(bindir)/ddl

install-hetero:	all
		$(INSTALL_PROGRAM) $(DDL) $(bindir)/$(config_guess)/ddl

$(DDL):		$(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LEXLIB) $(LIBS)

ddl-gram.tab.h \
ddl-gram.tab.c: ddl-gram.y
		$(YACC) $(YFLAGS) $(srcdir)/ddl-gram.y
		mv -f y.tab.c ddl-gram.tab.c
		mv -f y.tab.h ddl-gram.tab.h

ddl-lex.c:	ddl-lex.l ddl-gram.tab.h
		$(LEX) $(LFLAGS) $(srcdir)/ddl-lex.l
		mv -f lex.yy.c ddl-lex.c

ddl-lex.o: 	ddl-lex.c
		$(CC) $(LEX_CFLAGS) $(CPPFLAGS) -c $<

%.o:		../common/%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o:		%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
		$(RM) $(DDL) $(OBJS)

mostlyclean:	clean

distclean:	clean
		$(RM) Makefile *.dep

realclean:	clean
		$(RM) ddl-gram.tab.c ddl-gram.tab.h ddl-lex.c
		$(RM) Makefile *.dep

ifeq ($(INCLUDE),1)
include $(patsubst %,%.dep,$(notdir $(basename $(SRCS))))
endif
