#ifndef QUADTREEDELETION_H
#define QUADTREEDELETION_H
#include "QuadTree.h"
#include "Stack.h"
#include "LinkedList.h"

/*
Remove um nó de uma instancia de QuadTree, insere os nós filhos desse nó na instancia de List.
*/
void quadTreeRemoveNode( QuadTree *qt, QuadTreeNode *node, List *dataList );

/*
Remove de uma instancia de QuadTree os nós fornecidos na instancia de Stack,
insere os nós filhos desses nós na instancia de List.
*/
void quadTreeRemoveNodes( QuadTree *qt, Stack *disabledNodes, List *dataList );

#endif
