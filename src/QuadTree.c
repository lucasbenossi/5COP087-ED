#include "QuadTree.h"
#include "Stack.h"
#include "LinkedList.h"
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

static void freeQuadTreeRecursion( QuadTreeNode *node );

static void quadTreeInsertRecursion( QuadTreeNode *root, QuadTreeNode *node );

static QuadTreeNode **getQuadrantPointer( QuadTreeNode *root, QuadTreeNode *node );

static void unlinkNodes( QuadTree *qt, QuadTreeNode *node, List *unlinked );

static int isNodeLinked( QuadTree *qt, QuadTreeNode *node );

static void unlinkNode( QuadTree *qt, QuadTreeNode *node );

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

int getQuadTreeSize( QuadTree *qt ){
	return qt->size;
}

int isQuadTreeEmpty( QuadTree *qt ){
	return qt->size == 0;
}

QuadTreeNode *quadTreeInsert( QuadTree *qt, double x, double y, void *data ){
	QuadTreeNode *node;

	node = createQuadTreeNode( x, y, data );

	if( qt->root == NULL ){
		qt->root = node;
	}
	else{
		quadTreeInsertRecursion( qt->root, node );
	}

	qt->size++;

	return node;
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

void *quadTreeRemoveNode( QuadTree *qt, QuadTreeNode *node, List *unlinkedNodes ){
	if( isNodeLinked(qt, node) ){
	    unlinkNodes( qt, node, unlinkedNodes );
	}
	return disableQuadTreeNode(node);
}

static void unlinkNodes( QuadTree *qt, QuadTreeNode *node, List *unlinkedNodes ){
	if( node != NULL ){
	    unlinkNodes( qt, getQuadTreeNodeNW(node), unlinkedNodes );
	    unlinkNodes( qt, getQuadTreeNodeNE(node), unlinkedNodes );
	    unlinkNodes( qt, getQuadTreeNodeSW(node), unlinkedNodes );
	    unlinkNodes( qt, getQuadTreeNodeSE(node), unlinkedNodes );
	    unlinkNode(qt, node);
	    (qt->size)--;
	    insert( unlinkedNodes, node );
	}
}

static int isNodeLinked( QuadTree *qt, QuadTreeNode *node ){
	if( qt->root == node ) return 1;
	if( node->parent ) return 1;
	return 0;
}

static void unlinkNode( QuadTree *qt, QuadTreeNode *node ){
	if( qt->root == node ){
		qt->root = NULL;
	}
	else if( node->parent != NULL ){
	    if( node->parent->nw == node ){
	        node->parent->nw = NULL;
	    }
	    else if( node->parent->ne == node ){
	        node->parent->ne = NULL;
	    }
	    else if( node->parent->sw == node ){
	        node->parent->sw = NULL;
	    }
	    else if( node->parent->se == node ){
	        node->parent->se = NULL;
	    }
	    node->parent = NULL;
	}
	node->nw = NULL;
	node->ne = NULL;
	node->sw = NULL;
	node->se = NULL;
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
	void *data = node->data;
	free(node);
	return data;
}

void *disableQuadTreeNode( QuadTreeNode *node ){
	void *data = node->data;
	node->data = NULL;
	return data;
}

void reenableQuadTreeNode( QuadTreeNode *node, void *data ){
	if( node->data == NULL ){
		node->data = data;
	}
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

QuadTreeNode *getQuadTreeNodeNE( QuadTreeNode *node ){
	return node->ne;
}

QuadTreeNode *getQuadTreeNodeSW( QuadTreeNode *node ){
	return node->sw;
}

QuadTreeNode *getQuadTreeNodeSE( QuadTreeNode *node ){
	return node->se;
}

QuadTreeNode *getQuadTreeNodeParent( QuadTreeNode *node ){
	return node->parent;
}
