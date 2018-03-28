#include "QuadTreeSearch.h"
#include "LinkedList.h"
#include "QuadTree.h"
#include "Object.h"
#include "Quadra.h"
#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include "Geometry.h"
#include "ObjData.h"
#include <stdlib.h>

static void searchQuadTreeRecursion( QuadTreeNode *node, List *list, Object *region, int *comp );

static int objInsideRegion(Object *obj, Object *region);

static void searchQuadTreeNearestToPointRecursion( QuadTreeNode *node, double x, double y, Object **nearest, double *d );

/* ========================================================================== */

int searchQuadTreeRegion( QuadTree *qt, List *list, Object *region ){
	int comp;

	comp = 0;
	searchQuadTreeRecursion( getQuadTreeRoot(qt), list, region, &comp );

	return comp;
}

static void searchQuadTreeRecursion( QuadTreeNode *node, List *list, Object *region, int *comp ){
	Object *obj;
	if( node != NULL ){
	    (*comp)++;
	    obj = getQuadTreeNodeData(node);
	    if( obj != NULL ){
			if( region != NULL ){
				if( objInsideRegion( obj, region ) ){
	                insert( list, node );
	            }
			}
			else{
				insert( list, node );
			}
	    }
	    searchQuadTreeRecursion( getQuadTreeNodeNW(node), list, region, comp );
	    searchQuadTreeRecursion( getQuadTreeNodeNE(node), list, region, comp );
	    searchQuadTreeRecursion( getQuadTreeNodeSW(node), list, region, comp );
	    searchQuadTreeRecursion( getQuadTreeNodeSE(node), list, region, comp );
	}
}

static int objInsideRegion(Object *obj, Object *region){
	typedef int (*funcQuadraInside)(Quadra*,void*);
	typedef int (*funcPointInside)(double,double,void*);

	char typeRegion, typeObj;
	void *dataRegion, *dataObj;
	funcQuadraInside quadraInside;
	funcPointInside pointInside;

	typeRegion = getObjType(region);
	typeObj = getObjType(obj);
	dataRegion = getObjData(region);
	dataObj = getObjData(obj);

	if( typeRegion == 'c' ){
	    quadraInside = (funcQuadraInside)quadraInsideCircle;
	    pointInside = (funcPointInside)pointInsideCircle;
	}
	else if( typeRegion == 'r' ){
	    quadraInside = (funcQuadraInside)quadraInsideRect;
	    pointInside = (funcPointInside)pointInsideRect;
	}

	if( typeObj == 'q' ){
	    return quadraInside( dataObj, dataRegion );
	}
	if( typeObj == 'h' || typeObj == 's' || typeObj == 't' ){
	    return pointInside( getPointX(dataObj), getPointY(dataObj), dataRegion );
	}

	return 0;
}

Object *searchQuadTreeNearestToPoint( double x, double y, QuadTree *qt ){
	Object *nearest = NULL;
	QuadTreeNode *node = getQuadTreeRoot(qt);
	double d = -1;

	searchQuadTreeNearestToPointRecursion( node, x, y, &nearest, &d );

	return nearest;
}

static void searchQuadTreeNearestToPointRecursion( QuadTreeNode *node, double x, double y, Object **nearest, double *d ){
	Object *obj;
	double D;
	int dontGo = 0;

	if( node != NULL ){
		obj = getQuadTreeNodeData(node);
		if( obj != NULL ){
			D = distancePointsSquared( x, y, getX(obj), getY(obj) );
			if( *d == -1 || D < *d ){
				*d = D;
				*nearest = obj;
			}
			dontGo = quadrantPointRoot( x, y, getQuadTreeNodeX(node), getQuadTreeNodeY(node) );
		}
		if( dontGo != NE ) searchQuadTreeNearestToPointRecursion( getQuadTreeNodeNE(node), x, y, nearest, d );
		if( dontGo != NW ) searchQuadTreeNearestToPointRecursion( getQuadTreeNodeNW(node), x, y, nearest, d );
		if( dontGo != SW ) searchQuadTreeNearestToPointRecursion( getQuadTreeNodeSW(node), x, y, nearest, d );
		if( dontGo != SE ) searchQuadTreeNearestToPointRecursion( getQuadTreeNodeSE(node), x, y, nearest, d );
	}
}
