#ifndef COMMANDSDEBUG_H
#define COMMANDSDEBUG_H
#include "Cidade.h"
#include "LinkedList.h"

/*
Processa o argumento -g ou -h.
*/
void convexHull( char *arg, int collinear, List *objs, Cidade *cidade, char *file, char *fixedDir );

/*
Processa o argumento -od.
*/
void dumpData( List *objs, Cidade *cidade, char *outDir );

void nearestPoint( char *arg, Cidade *cidade, char *outDir );

#endif
