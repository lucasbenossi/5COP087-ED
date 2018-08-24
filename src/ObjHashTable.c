#include "ObjHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Object.h"
#include "ObjData.h"
#include <stdlib.h>

void listToHT( List *list, HashTable *table ){
	Node *node;
	for( node = getFirst(list); node; node = getNext(node) ){
	    Object *obj = get(node);
	    insertHashTable( table, getObjId(obj), obj );
	}
}
