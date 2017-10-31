#include "QuadTreeDeletion.h"
#include "QuadTree.h"
#include "Stack.h"
#include "LinkedList.h"
#include <stdlib.h>

static void unlinkNodes( QuadTree *qt, QuadTreeNode *node, List *unlinkedNodes );

static void unlinkNodesRecursion( QuadTree *qt, QuadTreeNode *node, List *unlinkedNodes );

static int isNodeLinked( QuadTree *qt, QuadTreeNode *node );

static void unlinkNode( QuadTree *qt, QuadTreeNode *node );

/* ========================================================================== */

void quadTreeRemoveNode( QuadTree *qt, QuadTreeNode *node, List *dataList ){
	unlinkNodes( qt, node, dataList );
	destroyQuadTreeNode(node);
}

void quadTreeRemoveNodes( QuadTree *qt, Stack *disabledNodes, List *dataList ){
	QuadTreeNode *node;

    while( getStackSize(disabledNodes) > 0 ){
        node = pop(disabledNodes);
    	unlinkNodes( qt, node, dataList );
        destroyQuadTreeNode(node);
    }
}

static void unlinkNodes( QuadTree *qt, QuadTreeNode *node, List *dataList ){
    if( isNodeLinked(qt, node) == 1 ){
        unlinkNodesRecursion( qt, getQuadTreeNodeNW(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeNE(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeSW(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeSE(node), dataList );
        unlinkNode(qt, node);
        quadTreeSizeDec(qt);
    }
}

static void unlinkNodesRecursion( QuadTree *qt, QuadTreeNode *node, List *dataList ){
	if( node != NULL ){
        unlinkNodesRecursion( qt, getQuadTreeNodeNW(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeNE(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeSW(node), dataList );
        unlinkNodesRecursion( qt, getQuadTreeNodeSE(node), dataList );
        unlinkNode(qt, node);
        quadTreeSizeDec(qt);
        insert( dataList, destroyQuadTreeNode(node) );
	}
}

static int isNodeLinked( QuadTree *qt, QuadTreeNode *node ){
	if( getQuadTreeRoot(qt) == node ) return 1;
	if( getQuadTreeNodeParent(node) != NULL ) return 1;
	return 0;
}

static void unlinkNode( QuadTree *qt, QuadTreeNode *node ){
    QuadTreeNode *parent;

    parent = getQuadTreeNodeParent(node);

	if( getQuadTreeRoot(qt) == node ){
		setQuadTreeRoot(qt, NULL);
	}
    else if( parent != NULL ){
        if( getQuadTreeNodeNW(parent) == node ){
            setQuadTreeNodeNW(parent, NULL);
        }
        else if( getQuadTreeNodeNE(parent) == node ){
            setQuadTreeNodeNE(parent, NULL);
        }
        else if( getQuadTreeNodeSW(parent) == node ){
            setQuadTreeNodeSW(parent, NULL);
        }
        else if( getQuadTreeNodeSE(parent) == node ){
            setQuadTreeNodeSE(parent, NULL);
        }
        setQuadTreeNodeParent(node, NULL);
    }
    setQuadTreeNodeNW(node, NULL);
    setQuadTreeNodeNE(node, NULL);
    setQuadTreeNodeSW(node, NULL);
    setQuadTreeNodeSE(node, NULL);
}
