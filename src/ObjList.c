#include <stdlib.h>
#include "ObjList.h"
#include "LinkedList.h"
#include "Object.h"
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"

Object *getIdInt( List *l, int id ){
    Node *node;
    node = getFirst(l);
    while( node != NULL && getObjId(get(l,node)) != id ){
        node = getNext(l,node);
    }
    if( node != NULL ){
        return get(l,node);
    }
    return NULL;
}

void destroyObjList( List *l ){
    Node *node1, *node2;
    Object *obj;
    int objType;
    void *objData;

    if( getFirst(l) != NULL  ){
		node1 = getFirst(l);
		node2 = getNext(l,node1);
		while( node1 != NULL ){
            obj = get(l,node1);
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
                destroyPoint(objData);
            }
            destroyObject(obj);
            destroyNode(node1);
			node1 = node2;
			if( node2 != NULL ){
				node2 = getNext(l,node2);
			}
		}
    }
	destroyList(l);
}
