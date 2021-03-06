# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:40:40 jthomas Exp $
# Copyright (C) 1994, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

# Actual location of source directory.
srcdir = .

# Where to search when trying to build stuff.
# Search path for source (dependency, intermediate) files.

# Source and object directory roots.
srcroot = .
objroot = .

# Since Makeconfig references the srcdir variable, this include of
# Makeconfig must follow the definition of srcdir above.
# Note that Makeconfig cannot reference the . autoconf variable
# rather than the srcdir makefile variable, because . is
# different in every Makefile (JAT).
include Makeconfig

#### End of system configuration section. ####

# Make gc and tools first, xp and x before pb, paces last. (JAT)
SUBDIRS =	$(GC) tools info ddl xp x pb rl paces

# Object-only (ie non-source) directories.
# Some of the sub-directories (eg ddl, pb, paces) make output
# in these directories, so they must exist before we make in those
# sub-directories. (JAT)
OBJDIRS =	bin include lib share

SRCS =		cppgen.c layergen.c

LAYERGEN_OBJS =	Makefile.layers pb/layer-tab.c

version =	$(shell grep 'version_string' $(srcdir)/common/version.c \
		  | $(SED) -e 's/[^"]*"//' -e 's/".*//')

# Absolute (non-relative) source and object roots.
# Note that these may contain /tmp_mnt, so their use should be avoided
# as much as possible.  Currently, they are only used for (1) the dist
# rule and (2) the un-installed (ie devleoper rather than user) defaults
# for directory names in P2.in (JAT)
abs_srcroot =	$(shell cd $(srcdir); pwd)
abs_objroot =	$(shell pwd)

.PHONY:		top dist

# This rule DOES run the regression tests.
check:		all
		$(MAKE) -C paces check

# This directory and sub-directories.
# Since bin, include, and lib don't contain a Makefile, configure does not
# automatically create them, and thus we must create them manually.
# This rule does NOT run the regression tests.
all:		top mkinstalldirs
		$(srcdir)/mkinstalldirs $(OBJDIRS)
		@for dir in $(SUBDIRS); do \
		  $(MAKE) -C $$dir $@; \
		  if [ $$? -ne 0 ]; then \
		    exit 1; \
		  fi; \
		done; \
		exit 0

# This directory only.
top:		layers.all $(LAYERGEN_OBJS) $(OBJDIRS) $(CPPGEN) $(P2)

# Object-only directories.
$(OBJDIRS):
		$(SHELL) $(srcdir)/mkinstalldirs $@

# Normal install.

install:	top installdirs INSTALL-P2
		for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done
		$(INSTALL_PROGRAM) $(RL) $(bindir)/rl
		$(INSTALL_PROGRAM) INSTALL-P2 $(bindir)/P2
		$(RM) INSTALL-P2

installdirs:	mkinstalldirs
		$(srcdir)/mkinstalldirs \
		  $(bindir) $(datadir) $(includedir) $(libdir) $(infodir)

# Heterogeneous install.

install-hetero:	top installdirs-hetero INSTALL-P2-HETERO
		for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done
		$(INSTALL_PROGRAM) $(RL) $(bindir)/$(config_guess)/rl
		$(INSTALL_PROGRAM) $(srcdir)/config.guess $(bindir)/config.guess
		$(INSTALL_PROGRAM) INSTALL-P2-HETERO $(bindir)/P2
		$(RM) INSTALL-P2-HETERO

installdirs-hetero:	mkinstalldirs config.guess
			$(srcdir)/mkinstalldirs \
			  $(bindir)/$(config_guess) $(datadir) $(includedir) \
			  $(libdir)/$(config_guess) $(infodir)

# This rule replaces the __ constants in P2.in with the values of
# autoconf make variables and writes the results to $(P2) or INSTALL-P2.
# Note: do not change the name of the target INSTALL-P2
# (P2.in depends on it).

### P2:		P2.in config.status
###		$(SHELL) config.status

P2:		P2.in stamp-conf

$(P2)\
INSTALL-P2\
INSTALL-P2-HETERO:	P2 stamp-conf common/version.c
			$(SED) \
			   -e 's:__ABS_OBJROOT:$(abs_objroot):g' \
			   -e 's:__ABS_SRCROOT:$(abs_srcroot):g' \
			   -e 's:__BINDIR:$(bindir):g' \
			   -e 's:__DATADIR:$(datadir):g' \
			   -e 's:__INCLUDEDIR:$(includedir):g' \
			   -e 's:__LIBDIR:$(libdir):g' \
			   -e 's:__OPT_CFLAGS:$(OPT_CFLAGS):g' \
			   -e 's:__PREFIX:$(prefix):g' \
			   -e 's:__SRCDIR:$(srcdir):g' \
			   -e 's:__TARGET:$@:g' \
			   -e 's:__VERSION:$(version):g' \
			   $< > $@
			chmod +x $@

# If layers does not exist, link layers.all to layers.
# Execute $(LAYERGEN) in order to make $(LAYERGEN_OBJS).
# We use the stamp-layers target so that we execute $(LAYERGEN) only once,
# rather than once per target in $(LAYERGEN_OBJS) (JAT)

$(LAYERGEN_OBJS):	stamp-layers

stamp-layers:	layers $(LAYERGEN)
		touch stamp-layers
		./$(LAYERGEN)

layers:
		ln -s $(srcdir)/layers.all layers

%:		%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $<

# Autoconf stuff.  Rules to automatically update the configuration
# information when you change the configuration files, adapted from
# Autoconf 2.1 info node "automatic remaking".

configure:	configure.in
		cd $(srcdir); $(AUTOCONF)

# autoheader might not change config.h.in, so touch a stamp file.
config.h.in:	stamp-conf.in
stamp-conf.in:	configure.in acconfig.h
		cd $(srcdir); $(AUTOHEADER)
		touch $(srcdir)/stamp-conf.in

# config.status might not change config.h, so touch a stamp file.
config.h:	stamp-conf
stamp-conf:	config.h.in config.status
		$(SHELL) config.status
		touch stamp-conf

Makefile:	Makefile.in config.status
		$(SHELL) config.status

config.status:	configure
		$(SHELL) config.status --recheck

# Clean.

clean:
		for dir in $(SUBDIRS); do \
		  $(MAKE) INCLUDE=0 -C $$dir $@; \
		done
		$(RM) stamp-layers $(CPPGEN) $(LAYERGEN)

mostlyclean:	clean
		for dir in $(SUBDIRS); do \
		  $(MAKE) INCLUDE=0 -C $$dir $@; \
		done

distclean:	clean
		for dir in $(SUBDIRS); do \
		  $(MAKE) INCLUDE=0 -C $$dir $@; \
		done
		$(RM) $(LAYERGEN_OBJS)
		$(RM) INSTALL-P2 $(P2) P2
		$(RM) layers stamp-layers
		$(RM) Makefile Makeconfig config.status *.dep
		$(RM) config.h config.log config.cache stamp-conf

# Can't depend on distclean, since distclean removes the Makefile.
realclean:	clean
		for dir in $(SUBDIRS); do \
		  $(MAKE) INCLUDE=0 -C $$dir $@; \
		done
		$(RM) $(LAYERGEN_OBJS)
		$(RM) INSTALL-P2 $(P2) P2
		$(RM) layers stamp-layers
		$(RM) Makefile Makeconfig *.dep
		$(RM) config.h config.status config.log config.cache stamp-conf

# Distribution.

# Make the README file in the info directory.
# Make the distribution directory and its sub-directories.
# co all source files into the distribution directory and its sub-directories.
# Remove $(EXCLUDE_PACES)
#   i.e., specifically exclude these files from the distribution, since they
#   (1) they are intended to generate errors,
#   (2) they have non-deterministic output, or
#   (3) are very resource-intensive (would take to long to compile and/or run).
# Copy README to the distribution directory.
# Run autoconf and autoheader.
# Touch the stamp files.
# tar and compress the distribution directory.

EXCLUDE_PACES=	P2_error* P2_print* P2_warm-restart* waltz-rl* waltzdb-old* waltzdb-rl*
EXCLUDE_FILES=  $(patsubst %,paces/%,$(EXCLUDE_PACES))

dist:		common/version.c
		$(MAKE) -C info README
		set -x; \
		distname=p2-$(version); \
		rm -rf $$distname; \
		mkdir $$distname; \
		cp info/README $$distname;\
		cd $$distname; \
		co $(abs_srcroot)/RCS/*,v; \
		for dir in $(SUBDIRS) common; do \
		  mkdir $$dir; \
		  cd $$dir; \
		  co $(abs_srcroot)/$$dir/RCS/*,v; \
                  cd ..; \
		done; \
		$(RM) $(EXCLUDE_FILES); \
		$(AUTOCONF); \
		$(AUTOHEADER); \
		touch stamp-conf.in; \
		touch stamp-conf; \
		cd ..; \
		chmod -R go=u,go-w,u+w $$distname; \
		$(RM) $$distname.tar $$distname.tar.Z; \
		tar cvf $$distname.tar $$distname; \
		compress $$distname.tar; \
		$(RM) -r $$distname

ifeq ($(INCLUDE),1)
include $(patsubst %,%.dep,$(basename $(SRCS)))
endif
