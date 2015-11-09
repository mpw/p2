# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:46:12 jthomas Exp $
# Copyright (C) 1994, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

srcdir = .
srcroot = ./..
objroot = ..

include ../Makeconfig

#### End of system configuration section. ####

# The tools directory contains architecture-independent executables.

.PRECIOUS:	%.awk

SCRIPTS =	deliner.awk \
		liner.awk \
		xps.awk

OBJS =		$(patsubst %,%.o,$(notdir $(basename $(SRCS))))

all:		$(patsubst %,../share/%, $(SCRIPTS))

%.o:		%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

# This rule copies the $(SCRIPTS) files from this directory to the
# share directory.  This is necessary, because the $(SCRIPTS) files
# are under RCS control in this directory, but the P2 compiler expects
# to find the $(SCRIPTS) files in the share directory.

../share/%:	%
		$(RM) $@
		ln -s $(srcdir)/../tools/$* $@

install\
install-hetero:	all
		for file in $(SCRIPTS); do \
		  $(INSTALL_PROGRAM) ../share/$$file $(datadir)/$$file; \
		done

clean:		
		$(RM) $(patsubst %,../share/%,$(SCRIPTS)) $(OBJS)

mostlyclean:    clean

distclean: 	clean
		$(RM) Makefile *.dep

realclean: 	clean
		$(RM) Makefile *.dep

