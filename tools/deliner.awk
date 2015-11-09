# $Id: deliner.awk,v 45.0 1997/09/19 05:46:12 jthomas Exp $ 
# Copyright (C) 1997, The University of Texas at Austin.
#
# Used to report C syntax errors back to the original .p2 source
#
# This awk file replaces #pragma directives with #line directives
# The input file up to the "#pragma liner F <filename>" is copied verbatim
# The "F" pragma resets the filename, the "I" pragma resets the line number
# Once we have seen the first "F" pragma, the "#line <linenumber>" is placed 
# before every line.

BEGIN               { inbody = 0; }
/^#pragma liner F/  { printf("#line 1 \"%s\"\n", $4); inbody = 1; next; } 
/^#pragma liner I/  { lnnum = $4; next; } 
                    { if (inbody) printf("#line %d\n", lnnum); print $0; }
