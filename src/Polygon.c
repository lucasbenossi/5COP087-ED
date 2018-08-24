#include "Polygon.h"
#include "LinkedList.h"
#include "String.h"
#include "Point.h"
#include <stdlib.h>

static double expression( Point *I, Point *J );

/* ========================================================================== */

struct _polygon{
	char *id;
	char *fill;
	char *stroke;
	List *nodes;
	int numNodes;
};

Polygon *createPolygon( char *id, char *fill, char *stroke ){
	Polygon *polygon;
	polygon = malloc(sizeof(Polygon));
	polygon->id = createString(id);
	polygon->fill = createString(fill);
	polygon->stroke = createString(stroke);
	polygon->nodes = createList();
	polygon->numNodes = 0;
	return polygon;
}

void destroyPolygon( Polygon *polygon ){
	destroyString(polygon->id);
	destroyString(polygon->fill);
	destroyString(polygon->stroke);

	setListFuncDestroyData(polygon->nodes, destroyPointVoid);
	destroyList(polygon->nodes);
	free(polygon);
}

void polygonInsertNode( Polygon *polygon, double x, double y ){
	List *list;
	Point *node;
	char *numNodes;

	list = polygon->nodes;

	numNodes = createStringInt(polygon->numNodes);
	node = createPoint( x, y, numNodes, NULL, NULL );
	destroyString(numNodes);
	insert( list, node );

	(polygon->numNodes)++;
}

List *getPolygonNodes( Polygon *polygon ){
	return polygon->nodes;
}

char *getPolygonId( Polygon *polygon ){
	return polygon->id;
}

char *getPolygonFill( Polygon *polygon ){
	return polygon->fill;
}

char *getPolygonStroke( Polygon *polygon ){
	return polygon->stroke;
}

int getPolygonNumNodes( Polygon *polygon ){
	return polygon->numNodes;
}

double polygonArea( Polygon *polygon ){
	double area;
	List *list;
	Node *nodeI, *nodeJ;

	list = getPolygonNodes(polygon);

	if( getFirst(list) == NULL ) return 0;

	nodeI = getFirst(list);
	nodeJ = getLast(list);
	area = expression( get(nodeI), get(nodeJ) );

	nodeJ = nodeI;
	nodeI = getNext(nodeI);
	while( nodeI != NULL ){
		area += expression( get(nodeI), get(nodeJ) );
		nodeJ = nodeI;
		nodeI = getNext(nodeI);
	}

	return area/2;
}

static double expression( Point *I, Point *J ){
	return ( getPointX(J) + getPointX(I) ) * ( getPointY(J) - getPointY(I) );
}
