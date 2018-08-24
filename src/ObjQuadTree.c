#include "ObjQuadTree.h"
#include "ObjData.h"
#include "LinkedList.h"
#include "QuadTree.h"
#include "QuadTreeSearch.h"
#include "Stack.h"
#include "Array.h"
#include "ConvexHull.h"
#include "Object.h"
#include <stdlib.h>

static void sortArrayDivTwo( List *list, void **data, int left, int right );

static void destroyObjQuadTreeRecusrion( QuadTreeNode *node );

/* =============================================================== */

void listToQt( List *objList, QuadTree *qt, int method ){
	if( method == 1 ){
	    objListToQuadTree( objList, qt );
	}
	else if( method == 2 ){
	    objListToQuadTreeNoSort( objList, qt );
	}
	else if( method == 3 ){
	    objListToQuadTreeNoConvexHull( objList, qt );
	}
}

int quadTreeRemoveObjsRegion( QuadTree *qt, List *removed, Object *region, int method ){
	List *nodes, *unlinked, *objs;
	Node *node;
	Object *obj;
	int comp;

	nodes = createList();
	unlinked = createList();
	objs = createList();

	comp = searchQuadTreeRegion( qt, nodes, region );

	for( node = getFirst(nodes); node; node = getNext(node) ){
	    insert( removed, quadTreeRemoveNode( qt, get(node), unlinked ) );
	}

	for( node = getFirst(unlinked); node; node = getNext(node) ){
	    obj = destroyQuadTreeNode(get(node));
	    if( obj ){
	        insert( objs, obj );
	    }
	}

	listToQt( objs, qt, method );

	destroyList(nodes);
	destroyList(unlinked);
	destroyList(objs);

	return comp;
}

void objListToQuadTree( List *objList, QuadTree *qt ){
	List *chPointsList, *chList;
	Array *chPointsArray, *objArray, *chArray;
	Stack *chPointsStack;
	Object *obj;

	chList = createList();

	objArray = listToArray(objList);
	chPointsStack = createStack();
	if( getArraySize(objArray) > 0 ){
		while( sortAngleCollinear(objArray) == 0 ){
			grahanScanCollinear(objArray, chPointsStack);
			chPointsArray = stackToArray(chPointsStack);
			chPointsList = createList();
			sortArrayDivTwo(chPointsList, getArrayData(chPointsArray), 0, getArraySize(chPointsArray)-1);
			destroyArray(chPointsArray);
			insert(chList, chPointsList);
		}
	}
	destroyArray(objArray);
	destroyStack(chPointsStack);

	chArray = listToArray(chList);
	freeList(chList);
	sortArrayDivTwo( chList, getArrayData(chArray), 0, getArraySize(chArray)-1 );
	destroyArray(chArray);

	while( ! isListEmpty(chList) ){
		chPointsList = removeFirst(chList);
		while( ! isListEmpty(chPointsList) ){
			obj = removeFirst(chPointsList);
			quadTreeInsert( qt, getX(obj), getY(obj), obj );
		}
		destroyList(chPointsList);
	}

	destroyList(chList);
}

static void sortArrayDivTwo( List *list, void **data, int left, int right ){
	int i;
	if( right > left ){
	    i = (right+left)/2;
	    insert( list, data[i] );
	    sortArrayDivTwo( list, data, left, i-1 );
	    sortArrayDivTwo( list, data, i+1, right );
	}
	else if( right == left ){
		i = left;
		insert( list, data[i] );
	}
}

void objListToQuadTreeNoSort( List *objList, QuadTree *qt ){
	Stack *chStack;
	Array *objArray;
	Object *obj;

	chStack = createStack();

	objArray = listToArray(objList);
	if( getArraySize(objArray) > 0 ){
	    while( sortAngle(objArray) == 0 ){
	        grahanScan(objArray,chStack);
	    }
	}
	destroyArray(objArray);

	while( ! isStackEmpty(chStack) ){
	    obj = pop(chStack);
	    quadTreeInsert( qt, getX(obj), getY(obj), obj );
	}

	destroyStack(chStack);
}

void objListToQuadTreeNoConvexHull( List *objList, QuadTree *qt ){
	Node *node;
	Object *obj;

	node = getFirst(objList);
	while( node != NULL ){
	    obj = get(node);
	    quadTreeInsert( qt, getX(obj), getY(obj), obj );
	    node = getNext(node);
	}
}

void destroyObjQuadTree( QuadTree *qt ){
	destroyObjQuadTreeRecusrion( getQuadTreeRoot(qt) );
	resetQuadTree(qt);
	destroyQuadTree(qt);
}

static void destroyObjQuadTreeRecusrion( QuadTreeNode *node ){
	Object *obj;
	if( node != NULL ){
		destroyObjQuadTreeRecusrion( getQuadTreeNodeNW(node) );
		destroyObjQuadTreeRecusrion( getQuadTreeNodeNE(node) );
		destroyObjQuadTreeRecusrion( getQuadTreeNodeSW(node) );
		destroyObjQuadTreeRecusrion( getQuadTreeNodeSE(node) );
		obj = destroyQuadTreeNode(node);
		if( obj != NULL ){
			destroyObjData(obj);
		}
	}
}
