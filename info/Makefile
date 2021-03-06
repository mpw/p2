# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 45.0 1997/09/19 05:41:59 jthomas Exp $ 
# Copyright (C) 1994, The University of Texas at Austin.
# This file requires GNU make -- it will not work with the normal Unix make.
# Generated automatically from Makefile.in by configure.

#### Start of system configuration section. ####

srcdir = .
srcroot = ./..
objroot = ..

include ../Makeconfig

#### End of system configuration section. ####

MAKEINFO = makeinfo
TEXI2DVI = texi2dvi

# DVIPS is a dvi to postscript converter

DVIPS =		dvips

# PSNUP is a program which will be used to convert a postscript
# file in letter mode into a postscript file printed in landscape
# mode in 2 columns. 

PSNUP =		psnup

edition =	$(shell grep '@set EDITION' $(srcdir)/edition.texi \
		  | $(SED) -e 's/@set EDITION \(.*\)/\1/')

SRCS =		agreement.texi \
		distribution.texi \
		edition.texi \
		installation.texi \
		intro-agreement.texi \
		intro-concept-index.texi \
		intro-function-index.texi \
		intro-introduction.texi \
		intro-invoking.texi \
		language.texi \
		layers.texi \
		operations.texi \
		p2-intro.texinfo \
		p2-intro.top.texinfo \
		prime.p2.texi \
		sample.p2.texi \
		version.texi

ADV_SRCS =	adv-agreement.texi \
		adv-concept-index.texi \
		adv-function-index.texi \
		adv-introduction.texi \
		adv-invoking.texi \
		agreement.texi \
		dlist.xp.texi \
		drc.texi \
		edition.texi \
		p2-adv.texinfo \
		p2-adv.top.texinfo \
		version.texi \
		xp-manual.texi \
		xp-operations.texi

TITEX =		texinfo.tex

# Different versions of texinfo.tex which use either
# Metafont or PostScript fonts.

DVITEX =	$(srcdir)/texinfocm.tex
PSTEX =		$(srcdir)/texinfops.tex

# Files in the manual distribution.

DIST_FILES =	p2-intro.ps p2-adv.ps p2-intro.dvi p2-adv.dvi

.PHONY:		man info dvi ps ps2up dist

man:		info ps

all:

# Install info files by copying them into $(infodir) with
# (INSTALL_DATA), and then run install-info only if it exists.
# Use `if' instead of just prepending `-' to the line so we notice real
# errors from install-info.  We use `$(SHELL) -c' because some shells do
# not fail gracefully when there is an unknown command.

install\
install-hetero:	man
		for file in p2-intro.info* p2-adv.info*; do \
		  $(INSTALL_DATA) $$file $(infodir)/$$file; \
		done
                if $(SHELL) -c 'install-info --version' > /dev/null 2>&1; then \
                  install-info --infodir=$(infodir) $$d/p2-intro.info; \
                  install-info --infodir=$(infodir) $$d/p2-adv.info; \
                fi; \
                exit 0

info:		p2-intro.info p2-adv.info README

dvi:		p2-intro.dvi p2-adv.dvi

ps:		p2-intro.ps p2-adv.ps

ps2up:		p2-intro.2up.ps p2-adv.2up.ps


# Extract the P2 version from ../common/version.c
# Save the P2 version as the argument of a @set VERSION command
# embedded in the file version.texi.

version.texi:	../common/version.c
		$(RM) $@
		grep version_string $< \
		  | $(SED) -e 's/[^"]*"/@set VERSION /' -e 's/".*//' > $@

# Make example p2.texi files from paces .p2 files.
# Replace "@{" and "@}" with "{" and "}".

# Both files are used as running examples throughout the text.
# sample.p2.texi is used particularly in info/intro-invoking.texi,
# info/language.texi, and info/p2-intro.top.texinfo.
# prime.p2.texi is used particularly info/language.texi.

%.p2.texi:	../paces/%.p2
		echo "/* Generated automatically by make from $< /*" > $@
		$(SED) 's/\([@{}]\)/@\1/g' < $< >> $@

# How to build info, dvi, and PostScript files for the Introductory
# P2 manual

p2-intro.info:	$(SRCS)

p2-intro.dvi:	$(SRCS)

p2-intro.ps:	$(SRCS)

# How to build info, dvi, and PostScript files for the Advanced
# P2 manual

p2-adv.info:	$(ADV_SRCS)

p2-adv.dvi:	$(ADV_SRCS)

p2-adv.ps:	$(ADV_SRCS)

# How to build the plain-text README file

README:		edition.texi version.texi readme.texinfo \
		abstract.texi distribution.texi installation.texi
		$(MAKEINFO) -I $(srcdir) --no-headers --no-validate \
		  readme.texinfo -o $@

# Pattern rules.

%.info:		%.texinfo
		$(MAKEINFO) -I $(srcdir) $<

%.dvi:		%.texinfo $(DVITEX)
		$(RM) $(TITEX); ln -s $(DVITEX) $(TITEX)
		-$(TEXI2DVI) $<

%.ps:		%.texinfo $(DVITEX)
		$(RM) $(TITEX); ln -s $(DVITEX) $(TITEX)
		-$(TEXI2DVI) $<
		$(DVIPS) -o $@ $*.dvi

%.2up.ps:	%.texinfo $(PSTEX)
		$(RM) $(TITEX); ln -s $(PSTEX) $(TITEX)
		-$(TEXI2DVI) $<
		$(DVIPS) -o $*.ps $*.dvi
		$(PSNUP) -l -2 $*.ps $@

# Clean.

clean:	
		$(RM) *.cp  *.fn  *.ky	*.pg  *.vr 
		$(RM) *.cps *.fns *.kys *.pgs *.vrs
		$(RM) *.aux *.log *.toc *.tp
		$(RM) $(TITEX)

mostlyclean:	clean

distclean:	clean
		$(RM) Makefile

# Can't depend on distclean, since distclean removes the Makefile.
realclean:	clean
		$(RM) version.texi prime.p2.texi sample.p2.texi
		$(RM) p2-intro.info* p2-intro.dvi p2-intro.ps
		$(RM) p2-adv.info* p2-adv.dvi p2-adv.ps
		$(RM) p2-intro.2up.ps p2-adv.2up.ps
		$(RM) README
		$(RM) Makefile

# The postscript and dvi distribution.

dist:		$(DIST_FILES)
		distname=p2-manuals-$(edition); \
		rm -rf $$distname; \
		mkdir $$distname; \
		cp $(DIST_FILES) $$distname; \
		chmod -R go=u,go-w,u+w $$distname; \
		$(RM) $$distname.tar $$distname.tar.Z; \
		tar cvf $$distname.tar $$distname; \
		compress $$distname.tar; \
		$(RM) -r $$distname
