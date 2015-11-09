# $Id: liner.awk,v 45.0 1997/09/19 05:46:12 jthomas Exp $
# Copyright (C) 1997, The University of Texas at Austin.
#
# Liner.awk
# 
# Used in p2 to report errors for line numbers in the source code.
# Print the filename at the beginning & report the line number after
# each line
#
# indef is used to NOT put pragmas in the middle of multiline #defines, 
# which all end in "\". The last line of the #define is printed & then
# before the next line is printed the new pragma. This will also not 
# put pragmas between any set of continuation lines.
#
# FILENAME in BEGIN block does not work with Gnu Awk (gawk) 2.15

BEGIN {
        indef = 0;
	printedfilename = 0;
      }
           
$0 ~ /\\$/ {
        if (indef == 0) {
	  printf("#pragma liner I  %d\n", NR);
	  indef = 1; }
	if (printedfilename == 0) {
	  printf("#pragma liner F  %s\n", FILENAME);
	  printedfilename = 1; }
	print $0;
	next;
      }

      {
	if (indef == 0)
	  printf("#pragma liner I  %d\n", NR);
	else
	  indef = 0;
	if (printedfilename == 0) {
	  printf("#pragma liner F  %s\n", FILENAME);
	  printedfilename = 1; }
	print $0;
      }
