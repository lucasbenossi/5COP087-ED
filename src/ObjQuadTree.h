#ifndef OBJQUADTREE_H
#define OBJQUADTREE_H
#include "LinkedList.h"
#include "QuadTree.h"
#include "Object.h"

/*
Insere os elementos de uma lista em uma QuadTree, usando o método:
- 1 = inserir com objListToQuadTree().
- 2 = inserir com objListToQuadTreeNoSort().
- 3 = inserir com objListToQuadTreeNoConvexHull().
*/
void listToQt( List *objList, QuadTree *qt, int method );

int quadTreeRemoveObjsRegion( QuadTree *qt, List *removed, Object *region, int method );

/*
Insere os elementos de uma lista em uma QuadTree, criando envoltórios convexos e
fazendo algumas ordenações para otimizar a altura da QuadTree.
*/
void objListToQuadTree( List *objList, QuadTree *qt );

/*
Insere os elementos de uma lista em uma QuadTree, criando uma pilha de envoltórios
convexos, desempilhando dessa pilha e inserindo os nós na sequencia.
*/
void objListToQuadTreeNoSort( List *objList, QuadTree *qt );

/*
Insere os elementos de uma lista em uma QuadTree, na mesma ordem que os elementos
foram inseridos na lista.
*/
void objListToQuadTreeNoConvexHull( List *objList, QuadTree *qt );

/*
Limpa uma QuadTree com instancias de Object, desalocando memória para todos
os nos da árvore, todas as intancias de Object, as intancias (Quadra, Point,
Circle ou Rect) que a instancia de Object referencia, e a instancia de List.
*/
void destroyObjQuadTree( QuadTree *qt );

#endif
