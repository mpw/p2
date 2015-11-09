/* $Id: pb-options.h,v 45.0 1997/09/19 05:45:56 jthomas Exp $ */

/* This file contains information related to command-line options.
   In order to use the GNU version of getopt_long() to parse
   the command-line, we must supply a `struct option' array that
   contains option names, etc.  However, `struct option' does not
   include a field for describing the option (for use in the `--help'
   command).  Therefore, this header file provides a technique for
   specifying in a single list the `struct option' information and the
   help descriptions. */

/* This header file expects that the CMD_LINE_OPTION macro has
   already been defined. */

/* The arguments to the macro are:
   1)  the long name of the command-line option
   2)  a flag indicating whether the option takes an argument
       (either "required_argument" or "no_argument")
   3)  if #2 is "required_argument", then 0; if #2 is "no_argument",
       then the address of a variable where the option's value is stored
   4)  if #2 is "required_argument", then the short name
       of the option; if #2 is "no_argument", then the value of the
       option
   5)  a help string */

/* Remember that if an option has a single-letter short name, the format
   argument of getopt_long() must contain that letter. */

/* The order of the items below determines the output of the help
   command. */

CMD_LINE_OPTION("attribute-file", required_argument, 0, 'a',
                "File of design-rule check attributes")

CMD_LINE_OPTION("hierarchy-comments", no_argument, 0, 'c',
                "Generate hierarchy comments")

CMD_LINE_OPTION("debug-yacc", no_argument, 0, 'd',
                "Print yacc debugging information")

CMD_LINE_OPTION("help", no_argument, 0, 'h',
                "Print a list of valid command line options")

CMD_LINE_OPTION("warnings", no_argument, 0, 'w',
                "Generate warnings")

CMD_LINE_OPTION ("version", no_argument, 0, 'v',
                 "Print the version number and exit.")

CMD_LINE_OPTION(NULL, 0, 0, 0, "")
