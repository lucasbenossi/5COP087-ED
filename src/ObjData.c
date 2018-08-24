#include "ObjData.h"
#include <stdlib.h>
#include <stdio.h>
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "Polygon.h"
#include "String.h"
#include "LinkedList.h"

Object *searchIdInt( List *l, int id ){
	Node *node;
	for( node = getFirst(l); node != NULL; node = getNext(node) ){
	    Object *obj = get(node);
	    if( getIdInt(obj) == id ){
	        return obj;
	    }
	}
	return NULL;
}

int getIdInt( Object *obj ){
	char objType;
	void *objData;

	objType = getObjType(obj);
	objData = getObjData(obj);

	if( objType == 'c' ){
	    return getCircleId(objData);
	}
	if( objType == 'r' ){
	    return getRectId(objData);
	}
	return 0;
}

void destroyObjData( Object *obj ){
	char objType;
	void *objData, *info;

	objType = getObjType(obj);
	objData = getObjData(obj);

	if( objType == 'c' ){
	    destroyCircle(objData);
	}
	else if( objType == 'r' || objType == 'o' ) {
	    destroyRect(objData);
	}
	else if( objType == 'q' ){
	    destroyQuadra(objData);
	}
	else if( objType == 'h' || objType == 's' || objType == 't' ){
	    info = getPointInfo(objData);
	    if( info != NULL ){
	        free(info);
	    }
	    destroyPoint(objData);
	}
	else if( objType == 'z' ){
		destroyPolygon(objData);
	}
	else if( objType == 'd' ){
		/* dummy, objData == NULL */
	}
	else{
		destroyPoint(objData);
	}

	destroyObject(obj);
}

void destroyObjDataVoid( void *obj ){
	destroyObjData(obj);
}

double getX( Object *obj ){
	char objType;
	void *objData;

	objType = getObjType(obj);
	objData = getObjData(obj);

	if( objType == 'c' ){
		return getCircleX(objData);
	}
	if( objType == 'r' ){
		return getRectX(objData);
	}
	if( objType == 'q' ){
		return getQuadraX(objData);
	}
	if( objType == 's' || objType == 'h' || objType == 't' ){
		return getPointX(objData);
	}
	else{
		return getPointX(objData);
	}
	return 0;
}

double getY( Object *obj ){
	char objType;
	void *objData;

	objType = getObjType(obj);
	objData = getObjData(obj);

	if( objType == 'c' ){
		return getCircleY(objData);
	}
	if( objType == 'r' ){
		return getRectY(objData);
	}
	if( objType == 'q' ){
		return getQuadraY(objData);
	}
	if( objType == 's' || objType == 'h' || objType == 't' ){
		return getPointY(objData);
	}
	else{
		return getPointY(objData);
	}
	return 0;
}
