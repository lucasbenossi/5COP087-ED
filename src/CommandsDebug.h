#ifndef COMMANDSDEBUG_H
#define COMMANDSDEBUG_H
#include "Cidade.h"
#include "LinkedList.h"

/*
Processa o argumento -g ou -h.
*/
void convexHull( char *arg, int collinear, List *objs, Cidade *cidade, char *file, char *fixedDir );

/*
Processa o argumento -d.
*/
void objListToTreeDump( char *arg, int method, List *objs, Cidade *cidade, char *nameFiles, char *outDir );

/*
Processa o comando I.
*/
void dumpPointInfo( Cidade *c, char *nameFiles, char *outDir );

#endif
