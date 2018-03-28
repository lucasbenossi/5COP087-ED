#ifndef QUADTREE_H
#define QUADTREE_H
#include "LinkedList.h"
#include "Stack.h"

/*
Define uma QuadTree.
*/
typedef struct _quadtree QuadTree;

/*
Define o nó de uma QuadTree.
*/
typedef struct _quadtreenode QuadTreeNode;

/* ========================================== */

/*
Cria uma instancia de QuadTree.
*/
QuadTree *createQuadTree();

/*
Destroi uma instancia de QuadTree.
*/
void destroyQuadTree( QuadTree *qt );

/*
Limpa uma QuadTree removendo todos os nós.
*/
void freeQuadTree( QuadTree *qt );

/*
Reseta os parametros root e size de uma instancia de QuadTree.
*/
void resetQuadTree( QuadTree *qt );

/*
Retorna o primeiro nó de uma QuadTree (nó raiz).
*/
QuadTreeNode *getQuadTreeRoot( QuadTree *qt );

/*
Retorna o tamanho (quantidade de nós) de uma QuadTree.
*/
int getQuadTreeSize( QuadTree *qt );

int isQuadTreeEmpty( QuadTree *qt );

/*
Insere algo na QuadTree.
*/
QuadTreeNode *quadTreeInsert( QuadTree *qt, double x, double y, void *data );

/*
Remove de qt o nó fornecido em node.
*/
void *quadTreeRemoveNode( QuadTree *qt, QuadTreeNode *node, List *unlinkedNodes );

/* ========================================== */

/*
Cria um nó de uma QuadTree.
*/
QuadTreeNode *createQuadTreeNode( double x, double y, void *data );

/*
Destroi o nó de uma QuadTree.
*/
void *destroyQuadTreeNode( QuadTreeNode *node );

/*
Desativa um nó de uma QuadTree.
O nó deixa de carregar o dado que carregava (passa a carregar NULL).
Retorna o dado que o nó carregava.
*/
void *disableQuadTreeNode( QuadTreeNode *node );

/*
Reativa um nó desativado.
Se o nó ja está ativado, não faz nada.
Se o nó está desativado, reativa e passa a carregar *data;
*/
void reenableQuadTreeNode( QuadTreeNode *node, void *data );

/*
Retorna o dado que o nó de uma QuadTree carrega.
*/
void *getQuadTreeNodeData( QuadTreeNode *node );

/*
Retorna as coordenadas x ou y de um nó de uma QuadTree.
*/
double getQuadTreeNodeX( QuadTreeNode *node );
double getQuadTreeNodeY( QuadTreeNode *node );

/*
Retorna o nó do quadrante NW, NE, SW ou SE de uma nó de uma QuadTree.
*/
QuadTreeNode *getQuadTreeNodeNW( QuadTreeNode *node );
QuadTreeNode *getQuadTreeNodeNE( QuadTreeNode *node );
QuadTreeNode *getQuadTreeNodeSW( QuadTreeNode *node );
QuadTreeNode *getQuadTreeNodeSE( QuadTreeNode *node );

/*
Retorna o nó pai de um nó de uma QuadTree.
*/
QuadTreeNode *getQuadTreeNodeParent( QuadTreeNode *node );

#endif
