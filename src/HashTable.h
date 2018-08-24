#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "LinkedList.h"
#include "FuncDestroyData.h"

#define HT_SIZE_SMALL 13
#define HT_SIZE 97
#define HT_SIZE_LARGE 997

typedef struct _hashtable HashTable;

typedef struct _iterator Iterator;

/* ========================================================================== */

HashTable *createHashTable( int size );

void destroyHashTable( HashTable *table );
void freeHashTable( HashTable *table );

int insertHashTable( HashTable *table, char *key, void *data );

void *removeHashTable( HashTable *table, char *key, void *data );

void *searchHashTable( HashTable *table, char *key );

void setHashTableFuncDestroyData( HashTable *table, FuncDestroyData *destroyData );

int getHashTableSize( HashTable *table );
int getHashTableCounter( HashTable *table );
int isHashTableEmpty( HashTable *table );

/* ========================================================================== */

void destroyDoubleHashTable( HashTable *table );
void freeDoubleHashTable( HashTable *table );

int insertDoubleHashTable( HashTable *table, char *key1, char *key2, void *data );

void *removeDoubleHashTable( HashTable *table, char *key1, char *key2, void *data );

void *searchDoubleHashTable( HashTable *table, char *key1, char *key2 );

/* ========================================================================== */

/*

Iterator *iterator = createIterator(table);
while( iteratorHasNext(iterator) ){
	void *data = iteratorNext(iterator);
	char *key = iteratorKey(iterator);
	iteratorRemove(iterator);
}
destroyIterator(iterator);

*/

Iterator *createIterator( HashTable *table );
void destroyIterator( Iterator *iterator );

int iteratorHasNext( Iterator *iterator );
void *iteratorNext( Iterator *iterator );

char *iteratorKey( Iterator *iterator );

void iteratorRemove( Iterator *iterator );

int getIteratorI( Iterator *iterator );
int getIteratorJ( Iterator *iterator );

#endif
