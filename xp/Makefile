# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:46:57 jthomas Exp $
# Copyright (C) 1995, The University of Texas at Austin.
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
		adhoc-arg.c \
		field.c \
		gen-layerdef.c \
		rlist.c \
		ref-util.c \
		seen.c \
		xp-actions.c \
		xp-gram.tab.c \
		xp-io.c \
		xp-lex.c \
		xp-main.c \
		xp-string-util.c

OBJS =		$(patsubst %,%.o,$(notdir $(basename $(SRCS))))

all:		../bin/xp

install\
install-hetero:	all

# This rule appends a comment and $(LEX_TABLE_SIZE) to xp-lex.l.in
# and writes the results to xp-lex.l

# Note that we must write the fields in $(LEX_TABLE_SIZE) to separate
# lines of xp-lex.l, essentually replacing the space characters in
# $(LEX_TABLE_SIZE) with newline characters in xp-lex.l
# Formerly, we did this replacement with sed, rather than awk, but not
# all versions of sed support translation to newline characters.

xp-lex.l:	xp-lex.l.in
		echo "%{" \
		  > $@
		echo "/* Generated automatically from xp-lex.l.in by Makefile. */" \
		  >> $@
		echo "%}" \
		  >> $@
		if [ "$(LEX_TABLE_SIZE)x" != "x" ] ; then \
		  echo $(LEX_TABLE_SIZE) | \
		  $(AWK) '/$(LEX_TABLE_SIZE)/{ for (i = NF; i >= 1; i--) print $$i }' \
		  >> $@ ; \
		fi ; \
		exit 0
		cat $< \
		  >> $@

../bin/xp:	$(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LEXLIB) $(LIBS)

xp-gram.tab.h \
xp-gram.tab.c:	xp-gram.y
		$(YACC) $(YFLAGS) $(srcdir)/xp-gram.y
		mv -f y.tab.c xp-gram.tab.c
		mv -f y.tab.h xp-gram.tab.h

xp-lex.c:	xp-lex.l xp-gram.tab.h
		$(LEX) $(LFLAGS) xp-lex.l
		mv -f lex.yy.c $@

xp-lex.o:	xp-lex.c
		$(CC) $(LEX_CFLAGS) $(CPPFLAGS) -c $<

%.o:		../common/%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o:		%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
		$(RM) $(OBJS)
		$(RM) ../bin/xp

mostlyclean:	clean

distclean:	clean
		$(RM) Makefile *.dep

realclean:	clean
		$(RM) Makefile *.dep
		$(RM) xp-gram.tab.c xp-gram.tab.h xp-lex.c xp-lex.l

ifeq ($(INCLUDE),1)
include $(patsubst %,%.dep,$(notdir $(basename $(SRCS))))
endif
