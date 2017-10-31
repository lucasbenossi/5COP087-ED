#include "ObjQuadTree.h"
#include "ObjList.h"
#include "LinkedList.h"
#include "QuadTree.h"
#include "Stack.h"
#include "Array.h"
#include "ConvexHull.h"
#include "Object.h"
#include <stdlib.h>

static void sortArrayDivTwo( List *list, void **data, int left, int right );

static void destroyObjQuadTreeRecusrion( QuadTreeNode *node );

/* =============================================================== */

void objListToQuadTree( List *objList, QuadTree *qt ){
	List *chPointsList, *chList;
	Array *chPointsArray, *objArray, *chArray;
	Stack *chPointsStack;
	Object *obj;

	chList = createList();

	objArray = listToArray(objList);
	if( getArraySize(objArray) > 0 ){
		while( sortAngleCollinear(objArray) == 0 ){
			chPointsStack = createStack();
			grahanScanCollinear(objArray,chPointsStack);
			chPointsArray = stackToArray(chPointsStack);
			destroyStack(chPointsStack);
			chPointsList = createList();
			sortArrayDivTwo( chPointsList, getArrayData(chPointsArray), 0, getArraySize(chPointsArray)-1 );
			destroyArray(chPointsArray);
			insert(chList,chPointsList);
		}
	}
	destroyArray(objArray);

	chArray = listToArray(chList);
	freeList(chList);
	sortArrayDivTwo( chList, getArrayData(chArray), 0, getArraySize(chArray)-1 );
	destroyArray(chArray);

	while( lenght(chList) > 0 ){
		chPointsList = removeFirst(chList);
		while( lenght(chPointsList) > 0 ){
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

    while( getStackSize(chStack) > 0 ){
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
			destroyDataObj(obj);
		}
	}
}
