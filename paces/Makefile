# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.2 1997/09/28 07:46:23 jthomas Exp $
# Copyright (C) 1994, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

srcdir = .
srcroot = ./..
objroot = ..

include ../Makeconfig

# The value returned by a processed killed by sh.
SH_KILL_EXIT_STATUS = 143

# Timeout in seconds--if a paces file does not complete execution
# within TIMEOUT seconds, we assume that it is incorrect, and we kill it.
TIMEOUT = 60

#### End of system configuration section. ####

.PHONY:		check pixie
.PRECIOUS:	%.ops %.p2 %.ddl %.pb %.c %.o

C_SRCS =	P2.c \
		P2_fastmalloc.c \
		P2_mmap.c \
		P2_process-pthread.c \
		P2_process-unix.c

P2_SRCS =	P2_lock-manager.p2 \
		P2_log-manager.p2 \
		P2_op-vec-manager.p2 \
		P2_trace-manager.p2 \
		P2_xact-manager.p2

SRCS =		$(C_SRCS) $(P2_SRCS)

OBJS =		$(patsubst %,%.o,$(basename $(SRCS)))

PACES =		$(notdir $(basename $(wildcard $(srcdir)/*.out)))
STAMPS =	$(patsubst %,stamp-%,$(PACES))

# P2 and layer-specific header files.
# See analogous deinition, header_files, in P2.in

P2_HDRS =	P2.h \
		P2_fastmalloc.h \
		P2_lock-manager.h \
		P2_log-manager.h \
		P2_mmap.h \
		P2_op-vec-manager.h \
		P2_process-manager.h \
		P2_trace-manager.h \
		P2_xact-manager.h

INCLUDE_P2_HDRS = $(patsubst %,../include/%,$(P2_HDRS))

# P2_HDRS plus the files common/print-log.h and common/op-id.h

HDRS =		$(P2_HDRS) \
		../common/print-log.h \
		../common/op-id.h 

INCLUDE_HDRS =	$(patsubst %,../include/%,$(notdir $(HDRS)))

# RL flags.

RL_FLAGS = -acghp

# P2 flags.

# I've removed the --cppflags from P2_CPPFLAGS, since P2.in is smart
# enough to recognize -I, -D, etc. as CPP options. (JAT)
# I think we don't need to distinguish between P2_CPPFLAGS and P2_FLAGS. (JAT)

###	   --cppflags=-DNDEBUG -DP2_NEDEBUG
###	   --cppflags=-DTRACE \
###	   --cppflags=-DABS_SRCDIR="$(abs_srcdir)" \

P2_CPPFLAGS =	-I$(srcdir) \
                -I$(srcdir)/../rl \
		$(CPPFLAGS)

P2_FLAGS =	--datadir=../share \
		--includedir=../include \
		--libdir=../lib \
		--no-drc --no-lines

# Build and execute all of the paces files, calculate the number of
# successes and failures.

# This rule has the nice property that if the user interrupts
# execution of $(MAKE) -k $(STAMPS) (for example, via pressing
# control-C) the number of successes and failures will still be
# calculated and reported correctly for those files that were built
# and executed before the user pressed control-C.  Nevertheless, the
# total reported may not match the sum of the number of
# successes+failures, since P2_total is updated as soon as possible
# (so that files are numbered correctly in a multi-process build),
# whereas P2_successes or P2_failures is not updated until their build
# and execution either succeeds or fails.

# Note that $(MAKE) -k $(STAMPS) is executed only for $(STAMPS)
# non-empty [ "$(STAMPS)x" != "x" ], because if $(STAMPS) is empty,
# then the $(MAKE) -k $(STAMPS) will have a null target, so the
# target will default to "check", and this rule will be executed
# recursively, ad infinitum.

check:		all paces P2_paces.h
		-rm -f P2_total P2_successes P2_failures
		touch P2_total P2_successes P2_failures
		-@if [ "$(STAMPS)x" != "x" ]; then \
		  $(MAKE) -k $(STAMPS); \
		fi
		@num_failures=`wc -l P2_failures | awk '{print $$1}'`; \
		num_successes=`wc -l P2_successes | awk '{print $$1}'`; \
		num_total=`wc -l P2_total | awk '{print $$1}'`; \
		echo "$$num_successes tests succeeded"; \
		if [ \( $$num_successes -ne 0 \) \
		     -a \( $$num_successes -le $$num_failures \) ]; then \
		  cat P2_successes | sed 's:^:  :'; \
		fi; \
		echo "$$num_failures tests failed"; \
		if [ $$num_failures -ne 0 ]; then \
		  cat P2_failures | sed 's:^:  :'; \
		fi; \
		echo "$$num_total tests total"; \
		if [ $$num_failures -eq 0 ]; then \
		  echo "*** paces succeeded ***"; \
		else \
		  echo "*** paces failed ***"; \
		fi; \
		checksum=`echo $$num_successes + $$num_failures | bc -l`; \
		if [ $$num_total -ne $$checksum ]; then \
		  echo "warning: num_total != num_successes + num_failures"; \
		fi; \
		exit 0

# Copy $(HDRS) to ../include
# Generate the P2_cpp.h cpp-command-only file from $(HDRS)
#  and copy it to ../include
# Make libp2.a

all:		$(INCLUDE_HDRS) ../include/P2_cpp.h ../lib/libp2.a

# These rules are experimental (JAT).

PIXIE_OBJ =	tpcbApiCT
#PIXIE_IN =	$(srcdir)/$(PIXIE_OBJ).in
PIXIE_IN =	/dev/null

# pb
#
# pixie:	$(PIXIE_OBJ)
# 		pixie -o pb.pixie $(PB)
#		pb.pixie $(PIXIE_OBJ).pb > /dev/null
#		prof -pixie $(PB) pb.Addrs pb.Counts > pb.prof

# paces file

pixie:		$(PIXIE_OBJ)
		pixie -o $(PIXIE_OBJ).pixie $(PIXIE_OBJ)
		./$(PIXIE_OBJ).pixie < $(PIXIE_IN) > /dev/null 2> /dev/null
		prof -pixie $(PIXIE_OBJ) $(PIXIE_OBJ).Addrs \
		  $(PIXIE_OBJ).Counts > $(PIXIE_OBJ).prof

# These rules make P2_cpp.h from the $(P2_HDRS) files by concatinating together
# only those lines of $(P2_HDRS) that are cpp-commands OTHER THAN #include.

# Should P2_cpp.h depend on Makefile.in, since Makefile.in determines
# $(P2_HDRS) and $(INCLUDE_P2_HDRS), and thus the contents of
# P2_cpp.h, or would depending on Makefile.in cause too many re-makes?
# (JAT)

P2_cpp.h:	$(INCLUDE_P2_HDRS) $(CPPGEN) Makefile
		echo "/* Generated automatically by $(CPPGEN) */" > $@
		cat $(INCLUDE_P2_HDRS) | $(CPPGEN) | grep -v '# *include' >> $@

../include/P2_cpp.h:	P2_cpp.h
			-rm -f $@
			cp $< $@

# These rules copy the $(HDRS) files from this or the common directory
# to the include directory.  This is necessary, because the $(HDRS)
# files are under RCS control in this directory, but the P2 compiler
# expects to find the $(HDRS) files in the include directory.

../include/%:	%
		-rm -f $@
		cp $< $@

../include/%:	../common/%
		-rm -f $@
		cp $< $@

# Make dependencies from .p2 files.
# We trick $(CPP) -M into generating dependencies for %.p2 as follows:
# (1) Select ONLY the #include lines from $(INCLUDE_P2_HDRS)
#     (sort-of the opposite of P2_cpp.h) and place the result in %.c
# (2) Append %.p2 to %.c
# (3) Replace %.c with %.p2 in the .dep file
# (4) Delete %.c
# See analogous rule to make dependecies from .xp files in x/Makefile.in

# It is necessary to name the dependency files .p2.dep (rather than
# just .dep), because there is a rule in Makeconfig.in to generate
# dependency files (named .dep) from .c files, and we don't want the
# rule in Makeconfig.in to make the dependency files (from the
# intermediate .c file produced by P2.in).

%.p2.dep:	%.p2 $(INCLUDE_P2_HDRS)
		@echo $(ECHO_N) "Generating $@ ... $(ECHO_C)"
		@-rm -f $*.c
		@cat $(INCLUDE_P2_HDRS) | $(CPPGEN) | grep '# *include' > $*.c
		@cat $< >> $*.c
		$(CPP) -M -I$(srcroot)/pb $(P2_CPPFLAGS) $*.c \
		  | $(SED) -e 's%$*.c%$*.p2%g' \
		  > $(notdir $@)
		@-rm -f $*.c
		@echo "done"

# Make .o files from .p2 files.
# Note: don't pass too many options to P2; instead, use the defaults
# in P2 which distinguish between what a user wants and what a
# developer wants. (JAT)

%.o:		%.p2 $(PB) $(DDL) $(P2)
		echo "P2 $*"
		$(SPEW) $(P2) $(P2_CPPFLAGS) $(P2_FLAGS) -c $<

# Normal install.

install:	all
		for file in $(INCLUDE_HDRS); do \
		  $(INSTALL_DATA) $$file $(includedir)/$$file; \
		done
		$(INSTALL_DATA) ../include/P2_cpp.h $(includedir)/P2_cpp.h
		$(INSTALL_DATA) $(srcdir)/P2_attr.txt $(datadir)/P2_attr.txt
		$(INSTALL_DATA) ../lib/libp2.a $(libdir)/libp2.a
		$(RANLIB) $(libdir)/libp2.a

# Heterogenous install.

install-hetero:	all
		for file in $(INCLUDE_HDRS); do \
		  $(INSTALL_DATA) $$file $(includedir)/$$file; \
		done
		$(INSTALL_DATA) ../include/P2_cpp.h $(includedir)/P2_cpp.h
		$(INSTALL_DATA) $(srcdir)/P2_attr.txt $(datadir)/P2_attr.txt
		$(INSTALL_DATA) ../lib/libp2.a \
		  $(libdir)/$(config_guess)/libp2.a
		$(RANLIB) $(libdir)/$(config_guess)/libp2.a

# libp2.a

../lib/libp2.a:	$(OBJS)
		$(AR) $(ARFLAGS) $@ $(OBJS)
		$(RANLIB) $@

# This rule makes $(OBJS) .o files from $(C_SRCS) .c files

%.o:		%.c
		$(CC) $(PB_CFLAGS) $(CPPFLAGS) -c $<

# Absolute (non-relative) source directory.
# Note that this may contain /tmp_mnt, so its use should be avoided
# as much as possible.  Currently, it is only used for by paces
# programs which need a pathname for ftok. (JAT)
abs_srcdir =	$(shell cd $(srcdir); pwd)

# This rule makes executables from .p2 files.
# Most of the work is done by the the rule to make .o files from .p2 files.

%:		%.p2 $(PB) $(DDL) $(P2) ../lib/libp2.a
		echo "P2 $*"
		$(SPEW) $(P2) $(P2_CPPFLAGS) $(P2_FLAGS) $<

# If necessary, call $(MAKE) to build, and $(srcdir)/paces to execute
# the paces file.

# The dependency on the P2_total file forces this rule to always be
# executed.  If the stamp file is up-to-date (except for the dependency
# on the P2_total file), this indicates that if we re-built the object
# file it would not change, and if we re-executed to object file it
# would execute correctly; thus, in this case, this rule merely updates
# the P2_total and P2_successes files.  Otherwise, this rule calls
# $(MAKE) to build, and $(srcdir)/paces to execute the paces file.

# Note that this rule must re-run paces not only if the object file has
# changed, but also if it failed last time (so that we don't report
# success for the file).  The easiest way to do this would be to delete
# the failed objects, but we'd like to retain the failed objcts so we
# can debug them, so we use a stamp file to indicate success.  It sort
# of bothers me that we have two indicators of success: (1) the
# P2_successes file, and (2) the existance of .out file together with a
# stamp file.  Think of (1) as a cache of (2).  (JAT)

stamp-%:	%.p2 $(PB) $(DDL) $(P2) ../lib/libp2.a P2_total
		@echo $* >> P2_total; \
		num_total=`wc -l P2_total | awk '{print $$1}'`; \
		echo "$$num_total: $*"
		@if [ "$?" = "P2_total" ]; then \
		  echo $* >> P2_successes; \
		  exit 0; \
		fi; \
		$(MAKE) $*; \
		if [ $$? -ne 0 ]; then \
		  echo "$*: make failed" >> P2_failures; \
		  exit 1; \
		fi; \
		$(srcdir)/paces $(srcdir) $(SH_KILL_EXIT_STATUS) $(TIMEOUT) $*

# This rule makes .p2 files from .ops files.

%.p2:		%.ops $(RL)
		-rm -f $@
		$(RL) $(RL_FLAGS) -s $< > $@

# Only delete files we've generated, (in Makefile, paces, or P2).
# Note that either of the extensions ~ and .BAK may be generated by
# indent (in P2).

# Note that this rule is extremely difficult to maintain, but I can't
# think of a better solution that will work if $(srcdir) == $(objdir).
# (JAT)

clean:
		-rm -f P2_total P2_successes P2_failures
		-rm -f $(INCLUDE_HDRS) ../include/P2_cpp.h ../lib/libp2.a
		-rm -f P2_cpp.h
		-rm -f $(OBJS)
		for file in $(basename $(P2_SRCS)) $(PACES); do \
		  rm -f \
		    $$file-liner.c \
		    $$file-copy.c \
		    $$file-include.c \
		    $$file-include.i \
		    $$file.ddl \
		    $$file.pb \
		    $$file.pb~ $$file.BAK \
		    $$file-pb.c \
		    $$file-pb.c~ $$file.pb-c.BAK \
		    $$file-deliner.c \
		    $$file-deliner.c~ $$file-deliner.c.BAK \
		    $$file.c \
		    $$file.o \
		    $$file $$file.BAK \
		    $$file \
		    $$file.err.tmp \
		    $$file.out.tmp \
		    stamp-$$file \
		    $$file; \
		done
		for file in $(notdir $(basename $(wildcard $(srcdir)/*.ops)));\
                do \
		  rm -f $$file.p2; \
		done

mostlyclean:	clean

distclean:	clean
		-rm -f Makefile *.dep

realclean:	clean
		-rm -f Makefile *.dep

ifeq ($(INCLUDE),1)
include $(patsubst %.c,%.dep,$(C_SRCS))
include $(patsubst %.p2,%.p2.dep,$(P2_SRCS))
include $(patsubst %,%.p2.dep,$(PACES))
endif
