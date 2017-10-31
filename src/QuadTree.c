#include "QuadTree.h"
#include <stdio.h>
#include <stdlib.h>

struct _quadtree{
	struct _quadtreenode *root;
	int size;
};

struct _quadtreenode{
	double x;
	double y;
	void *data;
	struct _quadtreenode *nw;
	struct _quadtreenode *ne;
	struct _quadtreenode *sw;
	struct _quadtreenode *se;
	struct _quadtreenode *parent;
};

static void quadTreeInsertRecursion( QuadTreeNode *root, QuadTreeNode *node );

static QuadTreeNode **getQuadrantPointer( QuadTreeNode *root, QuadTreeNode *node );

static void freeQuadTreeRecursion( QuadTreeNode *node );

/* ================================================================================================ */

QuadTree *createQuadTree(){
	QuadTree *qt;
	qt = malloc( sizeof( QuadTree ) );
	qt->root = NULL;
	qt->size = 0;
	return qt;
}

void destroyQuadTree( QuadTree *qt ){
	freeQuadTree(qt);
	free(qt);
}

void freeQuadTree( QuadTree *qt ){
	freeQuadTreeRecursion(qt->root);
	resetQuadTree(qt);
}

static void freeQuadTreeRecursion( QuadTreeNode *node ){
	if( node != NULL ){
        freeQuadTreeRecursion(node->nw);
        freeQuadTreeRecursion(node->ne);
        freeQuadTreeRecursion(node->sw);
        freeQuadTreeRecursion(node->se);
        destroyQuadTreeNode(node);
    }
}

void resetQuadTree( QuadTree *qt ){
	qt->root = NULL;
	qt->size = 0;
}

QuadTreeNode *getQuadTreeRoot( QuadTree *qt ){
	return qt->root;
}

void setQuadTreeRoot( QuadTree *qt, QuadTreeNode *root ){
	qt->root = root;
}

int getQuadTreeSize( QuadTree *qt ){
	return qt->size;
}

void quadTreeSizeInc( QuadTree *qt ){
	(qt->size)++;
}

void quadTreeSizeDec( QuadTree *qt ){
	(qt->size)--;
}

void quadTreeInsert( QuadTree *qt, double x, double y, void *data ){
	QuadTreeNode *node;

	node = createQuadTreeNode( x, y, data );

	if( qt->root == NULL ){
		qt->root = node;
	}
	else{
		quadTreeInsertRecursion( qt->root, node );
	}
}

static void quadTreeInsertRecursion( QuadTreeNode *root, QuadTreeNode *node ){
	QuadTreeNode **next;

	next = getQuadrantPointer( root, node );
	if( *next == NULL ){
		*next = node;
		node->parent = root;
	}
	else{
		quadTreeInsertRecursion( *next, node );
	}
}

static QuadTreeNode **getQuadrantPointer( QuadTreeNode *root, QuadTreeNode *node ){
	if( node->x <  root->x && node->y >= root->y ) return &(root->nw);
	if( node->x >= root->x && node->y >= root->y ) return &(root->ne);
	if( node->x <  root->x && node->y <  root->y ) return &(root->sw);
	if( node->x >= root->x && node->y <  root->y ) return &(root->se);
	return NULL;
}

/* ================================================================================================ */

QuadTreeNode *createQuadTreeNode( double x, double y, void *data ){
	QuadTreeNode *qtn;
	qtn = malloc( sizeof(QuadTreeNode) );
	qtn->x = x;
	qtn->y = y;
	qtn->data = data;
	qtn->nw = NULL;
	qtn->ne = NULL;
	qtn->sw = NULL;
	qtn->se = NULL;
	qtn->parent = NULL;
	return qtn;
}

void *destroyQuadTreeNode( QuadTreeNode *node ){
	void *data;
    data = node->data;
    free(node);
    return data;
}

void *getQuadTreeNodeData( QuadTreeNode *node ){
	return node->data;
}

double getQuadTreeNodeX( QuadTreeNode *node ){
	return node->x;
}

double getQuadTreeNodeY( QuadTreeNode *node ){
	return node->y;
}

QuadTreeNode *getQuadTreeNodeNW( QuadTreeNode *node ){
	return node->nw;
}

void setQuadTreeNodeNW( QuadTreeNode *node, QuadTreeNode *nw ){
	node->nw = nw;
}

QuadTreeNode *getQuadTreeNodeNE( QuadTreeNode *node ){
	return node->ne;
}

void setQuadTreeNodeNE( QuadTreeNode *node, QuadTreeNode *ne ){
	node->ne = ne;
}

QuadTreeNode *getQuadTreeNodeSW( QuadTreeNode *node ){
	return node->sw;
}

void setQuadTreeNodeSW( QuadTreeNode *node, QuadTreeNode *sw ){
	node->sw = sw;
}

QuadTreeNode *getQuadTreeNodeSE( QuadTreeNode *node ){
	return node->se;
}

void setQuadTreeNodeSE( QuadTreeNode *node, QuadTreeNode *se ){
	node->se = se;
}

QuadTreeNode *getQuadTreeNodeParent( QuadTreeNode *node ){
	return node->parent;
}

void setQuadTreeNodeParent( QuadTreeNode *node, QuadTreeNode *parent ){
	node->parent = parent;
}

void *disableQuadTreeNode( QuadTreeNode *node ){
	void *data;

	data = node->data;
	node->data = NULL;

	return data;
}

void reenableQuadTreeNode( QuadTreeNode *node, void *data ){
	if( node->data == NULL ){
		node->data = data;
	}
}
