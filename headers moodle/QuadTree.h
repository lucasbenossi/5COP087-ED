#ifndef QUADTREE_H
#define QUADTREE_H

/*
Define uma QuadTree.
*/
typedef void QuadTree;

/*
Define o nó de uma QuadTree.
*/
typedef void QuadTreeNode;

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

/*
Insere algo na QuadTree.
*/
void quadTreeInsert( QuadTree *qt, double x, double y, void *data );

/*
Remove um nó de uma QuadTree, retorna o dado que o nó carregava.
*/
void *quadTreeRemove( QuadTree *qt, QuadTreeNode *node );

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

#endif
