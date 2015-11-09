# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:45:41 jthomas Exp $
# Copyright (C) 1995, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

srcdir = .
srcroot = ./..
objroot = ..

include ../Makeconfig

#### End of system configuration section. ####

ifeq ($(INCLUDE),1)
include ../Makefile.layers
endif

SRCS =		../common/error.c \
		../common/getopt.c \
		../common/getopt1.c \
		../common/io.c \
		../common/layer-util.c \
		../common/lex.c \
		../common/link.c \
		../common/main.c \
		../common/op-tab.c \
		../common/string-util.c \
		../common/token-queue.c \
		../common/type.c \
		../common/typex.c \
		../common/util.c \
		../common/version.c \
		../common/xform.c \
		../common/xmalloc.c \
		annotation.c \
		call-down.c \
		compcurs.c \
		data-type.c \
		debug.c \
		drc.c \
		layer-tab.c \
		pb-actions.c \
		pb-gram.tab.c \
		pb-io.c \
		pb-lex.c \
		pb-main.c \
		pb-type.c \
		pb-xform.c

OBJS =		$(patsubst %,%.o,$(notdir $(basename $(SRCS))))
LAYEROBJS =	$(patsubst %,../x/%.o,$(LAYERNAMES))

all:		$(PB)

install:	all
		$(INSTALL_PROGRAM) $(PB) $(bindir)/pb

install-hetero:	all
		$(INSTALL_PROGRAM) $(PB) $(bindir)/$(config_guess)/pb

# This rule appends a comment and $(LEX_TABLE_SIZE) to pb-lex.l.in
# and writes the results to pb-lex.l

# Note that we must write the fields in $(LEX_TABLE_SIZE) to separate
# lines of pb-lex.l, essentually replacing the space characters in
# $(LEX_TABLE_SIZE) with newline characters in pb-lex.l
# Formerly, we did this replacement with sed, rather than awk, but not
# all versions of sed support translation to newline characters.

pb-lex.l:	pb-lex.l.in
		echo "%{" \
		  > pb-lex.l
		echo "/* Generated automatically from pb-lex.l.in by Makefile. */" \
		  >> pb-lex.l
		echo "%}" \
		  >> pb-lex.l
		if [ "$(LEX_TABLE_SIZE)x" != "x" ]; then \
		  echo $(LEX_TABLE_SIZE) | \
		  $(AWK) '/$(LEX_TABLE_SIZE)/{ for (i = NF; i >= 1; i--) print $$i }' \
		  >> pb-lex.l; \
		fi; \
		exit 0
		cat $< \
		  >> pb-lex.l

$(PB):		$(OBJS) $(LAYEROBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LAYEROBJS) $(LEXLIB) $(LIBS)

pb-gram.tab.h \
pb-gram.tab.c:	pb-gram.y
		$(YACC) $(YFLAGS) $(srcdir)/pb-gram.y
		mv -f y.tab.c pb-gram.tab.c
		mv -f y.tab.h pb-gram.tab.h

pb-lex.c:	pb-lex.l pb-gram.tab.h
		$(LEX) $(LFLAGS) pb-lex.l
		mv -f lex.yy.c pb-lex.c

pb-lex.o:	pb-lex.c
		$(CC) $(LEX_CFLAGS) $(CPPFLAGS) -c $<

%.o:		../common/%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o:		%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -I../x -c $<

clean:
		$(RM) $(OBJS) $(PB)

mostlyclean:	clean

distclean:	clean
		rm -f Makefile *.dep

realclean:	clean
		rm -f pb-gram.tab.c pb-gram.tab.h pb-lex.c
		rm -f Makefile *.dep

ifeq ($(INCLUDE),1)
include $(patsubst %,%.dep,$(notdir $(basename $(SRCS))))
endif
