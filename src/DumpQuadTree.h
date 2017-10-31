#ifndef DUMPQUADTREE_H
#define DUMPQUADTREE_H
#include "QuadTree.h"
#include <stdio.h>

/*
Dumpa uma instancia de QuadTree em um arquivo .txt.
*/
void dumpTree( QuadTreeNode *node, int level, int quadrant, FILE *out );

/*
Dumpa uma instancia de QuadTree em um arquivo .dot, para depois ser processado
pelo comando dot.
*/
void dumpTreeDot( QuadTree *qt, FILE *out );

#endif
