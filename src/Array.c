#include "Array.h"
#include "LinkedList.h"
#include "Stack.h"
#include "HashTable.h"
#include <stdlib.h>

struct _array{
	void **data;
	int size;
};

static Array *createArray( int size );

/* ========================================================================== */

static Array *createArray( int size ){
	Array *array;
	array = malloc( sizeof(Array) );
	if( size > 0 ){
	    array->data = malloc( size * sizeof(void*) );
	}
	else{
	    array->data = NULL;
	}
	array->size = size;
	return array;
}

/* ========================================================================== */

void destroyArray( Array *array ){
	if( getArrayData(array) != NULL ){
	    free( getArrayData(array) );
	}
	free(array);
}

int getArraySize( Array *array ){
	return array->size;
}

void **getArrayData( Array *array ){
	return array->data;
}

/* ========================================================================== */

Array *listToArray( List *list ){
	int i, size;
	Array *array;
	Node *node;

	size = lenght(list);
	array = createArray(size);

	if( size > 0 ){
	    node = getFirst(list);
	    for( i = 0; i < size; i++ ){
	        array->data[i] = get(node);
	        node = getNext(node);
	    }
	}

	return array;
}

void arrayToList( Array *array, List *list ){
	int i, size;
	void **data;

	size = getArraySize(array);
	data = getArrayData(array);
	for( i = 0; i < size; i++ ){
	    if( data[i] != NULL ){
	        insert( list, data[i] );
	    }
	}
}

/* ========================================================================== */

Array *stackToArray( Stack *stack ){
	int size, i;
	Array *array;

	size = getStackSize(stack);
	array = createArray(size);

	if( size > 0 ){
	    for( i = size-1; i >= 0; i-- ){
	        array->data[i] = pop(stack);
	    }
	}

	return array;
}

void arrayToStack( Array *array, Stack *stack ){
	int i, size;
	void **data;

	size = getArraySize(array);
	data = getArrayData(array);
	for( i = 0; i < size; i++ ){
	    if( data[i] != NULL ){
	        push( stack, data[i] );
	    }
	}
}

/* ========================================================================== */

Array *hashTableToArray( HashTable *ht ){
	int i, size;
	Array *array;
	Iterator *it;

	size = getHashTableCounter(ht);
	array = createArray(size);

	if( size > 0 ){
	    i = 0;
	    it = createIterator(ht);
	    while(iteratorHasNext(it)){
	        array->data[i] = iteratorNext(it);
	        i++;
	    }
	    destroyIterator(it);
	}

	return array;
}
