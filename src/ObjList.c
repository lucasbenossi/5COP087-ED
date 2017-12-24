#include "ObjList.h"
#include "LinkedList.h"
#include "ObjData.h"
#include <stdlib.h>

void destroyObjList( List *list ){
	Node *node, *node0;
	node = getFirst(list);
    while( node != NULL ){
		node0 = node;
		node = getNext(node);
		destroyObjData( destroyNode(node0) );
    }
	resetList(list);
	destroyList(list);
}
