#include "CommandsT4.h"
#include "LinkedList.h"
#include "QuadTree.h"
#include "Stack.h"
#include "Array.h"
#include "ObjList.h"
#include "Cidade.h"
#include "Object.h"
#include "Point.h"
#include "Rect.h"
#include "Geometry.h"
#include "ProcString.h"
#include "File.h"
#include "WriteTags.h"
#include "ConvexHull.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void polygonTorres( List *torres, Polygon *polygon );

static void genListTorres( List *list, Cidade *cidade, Rect *rect, int method );
static void genListTorresRecursion( QuadTreeNode *node, List *list, Rect *rect );
static void genListTorresProcNode( Object *obj, List *list, Rect *rect );

/* ========================================================================== */

void commandInsertInfo( char *line, Cidade *c ){
	List *list;
	Node *node;
	double *info, infoValue;
	char command, id[1000];
	Object *obj;
	Point *point;

	sscanf( line, "%cI %s %lf", &command, id, &infoValue );

	if( command == 'h' ){
		list = getCidadeHidrantes(c);
	}
	else if( command == 's' ){
		list = getCidadeSemaforos(c);
	}
	else if( command == 't' ){
		list = getCidadeTorres(c);
	}

	node = getLast(list);
	while( node != NULL ){
        obj = get(node);
		point = getObjData(obj);
        if( strcmp( getObjId(obj), id ) == 0 ){
			if( getPointInfo(point) != NULL ){
				free( getPointInfo(point) );
			}
			info = malloc(sizeof(double));
			*info = infoValue;
			setPointInfo( point, info );
            return;
        }
		node = getPrevious(node);
	}
}

void commandPoligonoCobertura( char *line, Cidade *cidade, char *nameFiles, char *outDir, int method ){
	char line2[1000], *tokens[6], *sufix, *fullPath;
	FILE *svg;
	char *delimiters;
	int i, error;
	double x, y, width, height;
	List *list;
	Rect *rect;
	Polygon *polygon;
	Node *node;

	strcpy(line2, line);
	delimiters = " \t\n\r";
	tokens[0] = strtok(line2, delimiters);
	for( i = 1; i < 6; i++){
		tokens[i] = strtok(NULL, delimiters);
	}

	if( strcmp( tokens[0], "pc?" ) != 0 ){
		return;
	}

	error = 0;

	sufix = tokens[1];
	fullPath = createStringCat(5, outDir, nameFiles, "-", sufix, ".svg");
	svg = openFileWrite(fullPath);
	if( svg == NULL ){
		error++;
	}

	if( error == 0 ){
		list = createList();

		if( tokens[2] != NULL ){
			sscanf( tokens[2], "%lf", &x );
			sscanf( tokens[3], "%lf", &y );
			sscanf( tokens[4], "%lf", &width );
			sscanf( tokens[5], "%lf", &height );
			rect = createRect( 0, width, height, x, y, NULL );
			genListTorres( list, cidade, rect, method );
		}
		else{
			genListTorres( list, cidade, NULL, method );
		}

		polygon = createPolygon( "cobertura", "red", "black" );
		polygonTorres( list, polygon );

		writeSvgStart(svg);

		writeCidadeTags( cidade, svg, method );

		node = getFirst(list);
		while( node != NULL ){
			writeTorreCoberturaTag( getObjData(get(node)), svg );
			node = getNext(node);
		}

		writePolygonTag(polygon, svg);
		writeSvgEnd(svg);

		destroyPolygon(polygon);

		if( tokens[2] != NULL ){
			destroyRect(rect);
		}
		destroyList(list);
	}

	destroyString(fullPath);
	closeFile(svg);
}

void commandPoligonoCoberturaArea( char *line, Cidade *cidade, FILE *outFileTxt, int method ){
	char line2[1000], *tokens[5], *delimiters;
	int i;
	List *list;
	Polygon *polygon;
	double x, y, width, height;
	Rect *rect;

	strcpy(line2, line);
	delimiters = " \t\n\r";
	tokens[0] = strtok(line2, delimiters);
	for( i = 1; i < 5; i++){
		tokens[i] = strtok(NULL, delimiters);
	}

	if( strcmp( tokens[0], "ac?" ) != 0 ){
		return;
	}

	fputs(line,outFileTxt);

	list = createList();

	if( tokens[2] != NULL ){
		sscanf( tokens[1], "%lf", &x );
		sscanf( tokens[2], "%lf", &y );
		sscanf( tokens[3], "%lf", &width );
		sscanf( tokens[4], "%lf", &height );
		rect = createRect( 0, width, height, x, y, NULL );
		genListTorres( list, cidade, rect, method );
	}
	else{
		genListTorres( list, cidade, NULL, method );
	}

	polygon = createPolygon( "cobertura", NULL, NULL );
	polygonTorres( list, polygon );

	fprintf( outFileTxt, "%f\n\n", polygonArea(polygon) );

	destroyPolygon(polygon);

	if( tokens[2] != NULL ){
		destroyRect(rect);
	}
	destroyList(list);
}

/* ========================================================================== */

static void polygonTorres( List *torres, Polygon *polygon ){
	List *pointsList;
	Array *array;
	Stack *stack;
	Node *node;
	Object *obj;
	Point *torre, *point;
	double x, y, *radius, r, c;

	c = 0.707106781; /* sqrt(2)/2 */

	pointsList = createList();

	node = getFirst(torres);
	while( node != NULL ){
		obj = get(node);
		torre = getObjData(obj);
		radius = getPointInfo(torre);

		if( radius != NULL && *radius > 0 ){
			x = getPointX(torre);
			y = getPointY(torre);
			r = *radius;

			insert( pointsList, createObject( NULL, 't', createPoint( x  , y+r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y  , NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x  , y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y  , NULL, "blue", "black" ) ) );

			r = r*c;

			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y+r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y+r, NULL, "blue", "black" ) ) );
		}
		node = getNext(node);
	}

	array = listToArray(pointsList);
	stack = createStack();
	sortAngle(array);
	grahanScan(array,stack);
	destroyArray(array);
	while( getStackSize(stack) > 0 ){
		point = getObjData(pop(stack));
		polygonInsertNode( polygon, getPointX(point), getPointY(point) );
	}
	destroyStack(stack);

	destroyObjList(pointsList);
}

static void genListTorres( List *list, Cidade *cidade, Rect *rect, int method ){
	Node *node;
	void *data;

	if( method == 0 ){
		node = getFirst(getCidadeTorres(cidade));
		while( node != NULL ){
			data = get(node);
			genListTorresProcNode( data, list, rect );
			node = getNext(node);
		}
	}
	else{
		genListTorresRecursion( getQuadTreeRoot(getCidadeTorresQT(cidade)), list, rect );
	}
}

static void genListTorresRecursion( QuadTreeNode *node, List *list, Rect *rect ){
	void *data;
	if( node != NULL ){
		data = getQuadTreeNodeData(node);
		genListTorresProcNode( data, list, rect );
		genListTorresRecursion( getQuadTreeNodeNW(node), list, rect );
		genListTorresRecursion( getQuadTreeNodeNE(node), list, rect );
		genListTorresRecursion( getQuadTreeNodeSW(node), list, rect );
		genListTorresRecursion( getQuadTreeNodeSE(node), list, rect );
	}
}

static void genListTorresProcNode( Object *obj, List *list, Rect *rect ){
	Point *torre;

	if( obj != NULL ){
		torre = getObjData(obj);
		if( rect != NULL ){
			if( pointInsideRect(rect, getPointX(torre), getPointY(torre)) == 1 ){
				insert( list, obj );
			}
		}
		else{
			insert( list, obj );
		}
	}
}
