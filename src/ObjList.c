#include "ObjList.h"
#include <stdlib.h>
#include <stdio.h>
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "Polygon.h"
#include "ProcString.h"
#include "LinkedList.h"

Object *searchIdInt( List *l, int id ){
    Node *node;
    node = getFirst(l);
    while( node != NULL && getIdInt(get(node)) != id ){
        node = getNext(node);
    }
    if( node != NULL ){
        return get(node);
    }
    return NULL;
}

void destroyDataObj( Object *data ){
    char objType;
    void *objData, *info;

    objType = getObjType(data);
    objData = getObjData(data);

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

    destroyObject(data);
}

void destroyObjList( List *list ){
	Node *node, *node0;
	node = getFirst(list);
    while( node != NULL ){
		node0 = node;
		node = getNext(node);
		destroyDataObj( destroyNode(node0) );
    }
	resetList(list);
	destroyList(list);
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
	return 0;
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
