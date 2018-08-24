#ifndef QUADTREEDUMP_H
#define QUADTREEDUMP_H
#include "QuadTree.h"
#include <stdio.h>

/*
Dumpa uma instancia de QuadTree em um arquivo .dot, para depois ser processado
pelo comando dot.
*/
void dumpQuadTreeDot( QuadTree *qt, FILE *out );

#endif
