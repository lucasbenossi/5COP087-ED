#include "CommandsDebug.h"
#include "LinkedList.h"
#include "Array.h"
#include "Stack.h"
#include "QuadTree.h"
#include "Object.h"
#include "Circle.h"
#include "Cidade.h"
#include "ProcString.h"
#include "File.h"
#include "ConvexHull.h"
#include "WriteTags.h"
#include "ObjList.h"
#include "ObjQuadTree.h"
#include "DumpQuadTree.h"
#include <stdio.h>

void convexHull( char *arg, int collinear, List *objs, Cidade *cidade, char *file, char *fixedDir ){
	List *objList, *chList, *polygonList;
	Array *array;
	Stack *stack;
	Node *node;
	char *fullPath, *fullPathSvg, *fullPathTxt;
	FILE *svg, *txt;
	Object *obj;
	Circle *c;
	int error, i;
	double x, y;
	Polygon *polygon;

	error = 0;
	txt = NULL;

	if( arg[0] == 'q' ){
		objList = getCidadeQuadras(cidade);
	}
	else if( arg[0] == 'h' ){
		objList = getCidadeHidrantes(cidade);
	}
	else if( arg[0] == 's' ){
		objList = getCidadeSemaforos(cidade);
	}
	else if( arg[0] == 't' ){
		objList = getCidadeTorres(cidade);
	}
	else if( arg[0] == 'c' || arg[0] == 'r' ){
		objList = objs;
	}

	if( collinear == 1 ){
		fullPath = createStringCat( 3, fixedDir, file, "-convexhullcollinear" );
	}
	else{
		fullPath = createStringCat( 3, fixedDir, file, "-convexhull" );
	}
	fullPathSvg = createStringCat( 2, fullPath, ".svg" );
	fullPathTxt = createStringCat( 2, fullPath, ".txt" );

    svg = openFileWrite(fullPathSvg);
    if( svg == NULL ){
		error++;
		return;
    }

	if( error == 0 ){
		txt = openFileWrite(fullPathTxt);
	    if( txt == NULL ){
			error++;
			return;
	    }
	}

	if( error == 0 ){
		array = listToArray(objList);

		chList = createList();
		if( getArraySize(array) > 0 ){
			if( collinear == 1 ){
				while( sortAngleCollinear(array) == 0 ){
					stack = createStack();
					grahanScanCollinear(array,stack);
					insert(chList,stack);
				}
			}
			else{
				while( sortAngle(array) == 0 ){
					stack = createStack();
					grahanScan(array,stack);
					insert(chList,stack);
				}
			}
		}

		destroyArray(array);

		polygonList = createList();
		while( lenght(chList) > 0 ){
			stack = removeLast(chList);
			polygon = createPolygon("","none","black");
			while( getStackSize(stack) > 0 ){
				obj = pop(stack);
				x = getX(obj);
				y = getY(obj);
				fprintf( txt, "%f %f %s\n", x, y, getObjId(obj) );
				polygonInsertNode(polygon,x,y);
			}
			fprintf( txt, "\n" );
			insert(polygonList,polygon);
			destroyStack(stack);
		}

		destroyList(chList);

		writeSvgStart(svg);

		node = getFirst(objList);
		c = createCircle(0, 5.0, 0.0, 0.0, "green");
		i = 1;
		while( node != NULL ){
			obj = get(node);
			setCircleId(c,i);
			setCircleX(c,getX(obj));
			setCircleY(c,getY(obj));
			writeCircleTag(c,svg);
			node = getNext(node);
			i++;
		}
		destroyCircle(c);

		while( lenght(polygonList) > 0 ){
			polygon = removeFirst(polygonList);
			writePolygonTag(polygon,svg);
			destroyPolygon(polygon);
		}

		destroyList(polygonList);

		writeSvgEnd(svg);
	}

	closeFile(svg);
	closeFile(txt);

	destroyString(fullPath);
	destroyString(fullPathTxt);
	destroyString(fullPathSvg);
}

void objListToTreeDump( char *arg, int method, List *objs, Cidade *cidade, char *nameFiles, char *outDir ){
    QuadTree *objsQT;
    char *fullPath, *fullPathTxt, *fullPathDot;
    FILE *outFileTxt, *outFileDot;
	char obj, methodString[2], objString[2];
	int error;

	error = 0;

	obj = arg[0];
	sprintf( methodString, "%d", method );
	sprintf( objString, "%c", obj );

    outFileDot = NULL;

	if( method == 0 ){
		return;
	}

    fullPath = createStringCat( 6, outDir, nameFiles, "-qt-", objString, "-", methodString );
    fullPathTxt = createStringCat( 2, fullPath, ".txt" );
    fullPathDot = createStringCat( 2, fullPath, ".dot" );

    outFileTxt = openFileWrite(fullPathTxt);
    if( outFileTxt == NULL ) error++;

    outFileDot = openFileWrite(fullPathDot);
    if( outFileDot == NULL ) error++;

	if( error == 0 ){
		if( obj == 'q' ){
			objsQT = getCidadeQuadrasQT(cidade);
		}
		else if( obj == 'h' ){
			objsQT = getCidadeHidrantesQT(cidade);
		}
		else if( obj == 's' ){
			objsQT = getCidadeSemaforosQT(cidade);
		}
		else if( obj == 't' ){
			objsQT = getCidadeTorresQT(cidade);
		}
		else if( obj == 'c' || obj == 'r' ){
			objsQT = createQuadTree();
			if( method == 1 ){
				objListToQuadTree(objs,objsQT);
			}
			else if( method == 2 ){
				objListToQuadTreeNoSort(objs,objsQT);
			}
			else if( method == 3 ){
				objListToQuadTreeNoConvexHull(objs,objsQT);
			}
		}

	    dumpTree( getQuadTreeRoot(objsQT), 0, 0, outFileTxt );
	    dumpTreeDot( objsQT, outFileDot );

	    if( obj == 'c' || obj == 'r' ){
			destroyQuadTree(objsQT);
		}
	}

    destroyString(fullPath);
    destroyString(fullPathTxt);
    destroyString(fullPathDot);

    closeFile(outFileTxt);
    closeFile(outFileDot);
}

void dumpPointInfo( Cidade *c, char *nameFiles, char *outDir ){
	List *list[3];
	Node *node;
	int i;
	FILE *out;
	char *fullPath;
	Object *obj;
	void *info;

	fullPath = createStringCat( 3, outDir, nameFiles, "-info.txt" );

	out = openFileWrite(fullPath);
	if( out == NULL ){
		destroyString(fullPath);
		return;
	}

	list[0] = getCidadeHidrantes(c);
	list[1] = getCidadeSemaforos(c);
	list[2] = getCidadeTorres(c);

	for( i = 0; i < 3; i++ ){
		node = getFirst(list[i]);
		while( node != NULL ){
			obj = get(node);
			info = getPointInfo(getObjData(obj));
			if( info != NULL ){
				fprintf( out, "%s %f\n", getObjId(obj), *(double*)info );
			}
			else{
				fprintf( out, "%s NULL\n", getObjId(obj) );
			}
			node = getNext(node);
		}
	}

	closeFile(out);
	destroyString(fullPath);
}
