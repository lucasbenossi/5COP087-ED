#ifndef COMMANDST4_H
#define COMMANDST4_H
#include <stdio.h>
#include "Cidade.h"

/*
Processa os comandos hI, sI, tI.
*/
void commandInsertInfo( char *line, Cidade *c );

/*
Processa o comando "pc?".
*/
void commandPoligonoCobertura( char *line, Cidade *cidade, char *nameFiles, char *outDir, int method );

/*
Processa o comando "ac?".
*/
void commandPoligonoCoberturaArea( char *line, Cidade *cidade, FILE *outFileTxt, int method );

#endif
