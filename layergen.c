/* $Id: layergen.c,v 45.0 1997/09/19 05:40:43 jthomas Exp $ */
/* Copyright (C) 1994, The University of Texas at Austin. */

/* Generate Makefile.layers and pb/layer-tab.c */
/* Re-write this as a shell script??? (JAT) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>  /* rewind() */
#include <stdlib.h> /* exit() */
#include <string.h> /* strcpy() */

/************************************************************************/
/*              Generate Makefile                                       */
/************************************************************************/

void
generate_makefile_layers (FILE *layers, char *make_file_name)
{
  FILE *target;
  int  result;
  char layername[100];
  char nextname[100];

  /* Step 1:  Rewind layers file */

  rewind(layers);

  /* Step 2:  Create target file */

  target = fopen(make_file_name, "w");
  if (target == NULL) {
    fprintf(stderr, "layergen: error: can't open %s\n", make_file_name);
    exit(EXIT_FAILURE);
  }

  /* Step 3:  output simple header */

  fprintf(target, "\nLAYERNAMES =\t\\\n");

  /* Step 4:  output list of layer names */

  result = fscanf(layers, "%s", layername);
  while(result != EOF) {
    result = fscanf(layers, "%s", nextname);
    fprintf(target, "      %s", layername);
    if (result != EOF)
      fprintf(target," \\\n");
    strcpy(layername, nextname);
  }

  /* Step 5: close the target file */

  fprintf(target,"\n\n");
  fclose(target);
}

/************************************************************************/
/*              Generate layer-tab.c                                    */
/************************************************************************/

void
generate_layer_tab (FILE *layers, char *file_name)
{
  FILE *target;
  int  result;
  char layername[100];
  char nextname[100];

  /* Step 1: Rewind layers file and create target file. */

  rewind(layers);
  target = fopen(file_name, "w");
  if (target == NULL) {
    fprintf(stderr, "layergen: error: can't open %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  /* Step 3: Output extern declarations. */

  fprintf(target,"#include \"xform.h\"\n\n");
  fprintf(target,"extern LAYER_DEF\n");

  result = fscanf(layers, "%s", layername);
  while(result != EOF) {
    result = fscanf(layers, "%s", nextname);      
    fprintf(target, "      P2_%s_", layername);
    if (result != EOF)
      fprintf(target,",\n");
    strcpy(layername, nextname);
  }
  fprintf(target,";\n\n\n");


  /* Step 4: Print layer_tab */

  rewind(layers);
  fprintf(target, "LAYER_DEF *layer_tab[] = {\n");
  for(result = fscanf(layers, "%s", layername);
      result != EOF;
      result = fscanf(layers, "%s", layername)) {
    fprintf(target, "      &P2_%s_,\n", layername);
  }
  fprintf(target,   "   0 };\n");

  /* Step 5: Close the target file. */

  fprintf(target,"\n");
  fclose(target);
}

/************************************************************************/
/*              Main block.                                             */
/************************************************************************/

void
main ()
{
  FILE *layers;

  layers = fopen("layers", "r");
  if (layers == NULL) {
    fprintf(stderr, "layergen: error can't open layers file\n");
    exit(EXIT_FAILURE);
  }

  generate_makefile_layers(layers, "Makefile.layers");
  generate_layer_tab(layers, "pb/layer-tab.c");

  fclose(layers);
  exit(EXIT_SUCCESS);
}
