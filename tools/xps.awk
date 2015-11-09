# $Id: xps.awk,v 45.0 1997/09/19 05:46:13 jthomas Exp $
# Copyright (C) 1997, The University of Texas at Austin.
#
# Used to split a ".xp" file into 3 files: ".cdef", ".kdef", ".nxp" 
#
# Usage:
#   awk -f  xps.awk <FILENAME>-xps.xp 
#
# splits the -xps.xp file into .nxp, .cdef, and .kdef
#   .nxp - new .xp body
#   .cdef - cursor defintion body  
#   .kdef - container definition body
#
# For the purposes of compiling the .xp file, an 
# "rm -f <FILENAME>.cdef <FILENAME>.kdef" must be done before
# executing this awk command. This is in case the .xp file 
# no longer has default cursor/container functions. 
# The .nxp file will always be generated. 
#
# FILENAME in BEGIN block does not work with Gnu Awk (gawk) 2.15

BEGIN {
  outfile = "";
  basename = "";
  first = 1;
} 

/^def_cursor_func/ {
  if (basename == "")
  {
    i = length(FILENAME);
    extension = substr(FILENAME, (i-6));
    if (extension != "-xps.xp" )
    {
      print "xps.awk:error:" FILENAME ":extension " extension " should be -xps.xp";
      exit 1
    }
    basename = substr(FILENAME, 1, (i-7))
  }
  outfile = basename ".cdef";
  first = 1
} 

/^def_container_func/ {
  if (basename == "")
  {
    i = length(FILENAME);
    extension = substr(FILENAME, (i-6));
    if (extension != "-xps.xp" )
    {
      print "xps.awk:error:" FILENAME ":extension " extension " should be -xps.xp";
      exit 1
    }
    basename = substr(FILENAME, 1, (i-7))
  }
  outfile = basename ".kdef";
  first = 1
}

{
  if (outfile == "")
  {
    i = length(FILENAME);
    extension = substr(FILENAME, (i-6));
    if (extension != "-xps.xp" )
    {
      print "xps.awk:error:" FILENAME ":extension " extension " should be -xps.xp";
      exit 1
    }
    basename = substr(FILENAME, 1, (i-7));
    outfile = basename ".nxp"
  }
  if (first == 1) 
  {
    print $0 > outfile;
    first = 0;
  }
  else 
  {
    print $0 >> outfile
  }
} 
