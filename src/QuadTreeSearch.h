#ifndef QUADTREESEARCH_H
#define QUADTREESEARCH_H
#include "LinkedList.h"
#include "QuadTree.h"
#include "Object.h"

/*
- qt define uma instancia de QuadTree.
- Os elementos que qt carrega são instancias de Object, contendo uma instancia de
  Quadra ou Point.
- list define uma instancia de List.
- region define uma instancia de Object, que contém uma instancia de Circle ou
  Rect, region pode ser NULL.

Procura em qt por elementos que estejam dentro da área definida por region, insere
em list os nós (QuadTreeNode) que carregam esses elementos. Se region for NULL,
insere todos os elementos de qt.
*/
int searchQuadTreeRegion( QuadTree *qt, List *list, Object *region );

Object *searchQuadTreeNearestToPoint( double x, double y, QuadTree *qt );

#endif
