#include "HashTable.h"
#include "LinkedList.h"
#include "String.h"
#include "FuncDestroyData.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _hashtable{
	int size;
	int counter;
	List **array;
	FuncDestroyData *destroyData;
};

struct _iterator{
	HashTable *table;
	int i, j;
	Node *current, *next;
};

struct _entry{
	char *key;
	void *data;
};
typedef struct _entry Entry;

static int hashModKey( HashTable *table, char *key );

static List **getList( HashTable *table, int i );

static Node *searchNodeKey( List *list, char *key );

static Node *searchNodeData( List *list, void *data );

static Entry *createEntry( char *key, void *data );

static void *destroyEntry( Entry *entry );

static void getNextNode( Iterator *iterator );

/* ========================================================================== */

static int hashModKey( HashTable *table, char *key ){
	int N, i, sum;
	static const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };
	static const int Nprimes = sizeof(primes) / sizeof(primes[0]);

	sum = 0;
	N = strlen(key);
	if( N > Nprimes ){
		N = Nprimes;
	}
	for( i = 0; i < N; i++ ){
		sum += primes[i] * (int)key[i];
	}

	return sum % table->size;
}

static List **getList( HashTable *table, int i ){
	return &table->array[i];
}

static Node *searchNodeKey( List *list, char *key ){
	Node *node;
	for( node = getFirst(list); node != NULL; node = getNext(node) ){
		Entry *entry = get(node);
		if( strcmp( key, entry->key ) == 0 ){
			break;
		}
	}
	return node;
}

static Node *searchNodeData( List *list, void *data ){
	Node *node;
	for( node = getFirst(list); node; node = getNext(node) ){
		Entry *entry = get(node);
		if( data == entry->data ){
			break;
		}
	}
	return node;
}

static Entry *createEntry( char *key, void *data ){
	Entry *entry;
	entry = malloc(sizeof(Entry));
	entry->key = createString(key);
	entry->data = data;
	return entry;
}

static void *destroyEntry( Entry *entry ){
	void *data;
	destroyString(entry->key);
	data = entry->data;
	free(entry);
	return data;
}

/* ========================================================================== */

HashTable *createHashTable( int size ){
	HashTable *table;
	int i;

	if( size < 1 ) return NULL;

	table = malloc(sizeof(HashTable));
	table->size = size;
	table->counter = 0;
	table->array = malloc( size * sizeof(List*) );
	for( i = 0; i < size; i++ ){
		table->array[i] = NULL;
	}
	table->destroyData = NULL;
	return table;
}

void destroyHashTable( HashTable *table ){
	freeHashTable(table);
	free(table->array);
	free(table);
}

void freeHashTable( HashTable *table ){
	int i;
	List **list;

	for( i = 0; i < table->size; i++ ){
		list = getList(table, i);
		if(*list){
			while(!isListEmpty(*list)){
				void *data = destroyEntry(removeFirst(*list));
				if(table->destroyData){
					table->destroyData(data);
				}
			}
			destroyList(*list);
			*list = NULL;
		}
	}
	table->counter = 0;
	table->destroyData = NULL;
}

int insertHashTable( HashTable *table, char *key, void *data ){
	List **list = getList( table, hashModKey( table, key ) );
	if( *list && searchNodeKey( *list, key ) ){
		return 1;
	}
	table->counter++;
	if(!*list){
		*list = createList();
	}
	insert( *list, createEntry( key, data ) );

	return 0;
}

void *removeHashTable( HashTable *table, char *key, void *data ){
	List **list;
	Node *node;

	list = getList( table, hashModKey( table, key ) );
	if(*list){
		if(data){
			node = searchNodeData(*list, data);
		}
		else{
			node = searchNodeKey(*list, key);
		}
		if(node){
			Entry *entry = removeNode(*list, node);
			table->counter--;
			if(isListEmpty(*list)){
				destroyList(*list);
				*list = NULL;
			}
			return destroyEntry(entry);
		}
	}
	return NULL;
}

void *searchHashTable( HashTable *table, char *key ){
	List *list = *getList(table, hashModKey(table, key));
	if(list){
		Node *node = searchNodeKey(list, key);
		if( node != NULL ){
			Entry *entry = get(node);
			return entry->data;
		}
	}
	return NULL;
}

void setHashTableFuncDestroyData( HashTable *table, FuncDestroyData *destroyData ){
	table->destroyData = destroyData;
}

int getHashTableSize( HashTable *table ){
	return table->size;
}

int getHashTableCounter( HashTable *table ){
	return table->counter;
}

int isHashTableEmpty( HashTable *table ){
	return table->counter == 0;
}

/* ========================================================================== */

void destroyDoubleHashTable( HashTable *table ){
	freeDoubleHashTable(table);
	destroyHashTable(table);
}

void freeDoubleHashTable( HashTable *table ){
	Iterator *it = createIterator(table);
	while( iteratorHasNext(it) ){
		HashTable *table2 = iteratorNext(it);
		table2->destroyData = table->destroyData;
		destroyHashTable(table2);
		iteratorRemove(it);
	}
	destroyIterator(it);
}

int insertDoubleHashTable( HashTable *table, char *key1, char *key2, void *data ){
	HashTable *table2 = searchHashTable( table, key1 );
	if( ! table2 ){
		table2 = createHashTable(table->size);
		insertHashTable( table, key1, table2 );
	}
	return insertHashTable( table2, key2, data );
}

void *removeDoubleHashTable( HashTable *table, char *key1, char *key2, void *data ){
	HashTable *table2 = searchHashTable( table, key1 );
	void *data2 = NULL;
	if(table2){
		data2 = removeHashTable( table2, key2, data );
		if( table2->counter == 0 ){
			removeHashTable( table, key1, table2 );
			destroyHashTable(table2);
		}
	}
	return data2;
}

void *searchDoubleHashTable( HashTable *table, char *key1, char *key2 ){
	HashTable *table2 = searchHashTable(table, key1);
	void *data = NULL;
	if(table2){
		data = searchHashTable(table2, key2);
	}
	return data;
}

/* ========================================================================== */

static void getNextNode( Iterator *iterator ){
	while( iterator->j < iterator->table->size ){
		List *list = *getList(iterator->table, iterator->j);
		if(list){
			iterator->next = getFirst(list);
			return;
		}
		iterator->j++;
	}
}

Iterator *createIterator( HashTable *table ){
	Iterator *iterator;
	iterator = malloc(sizeof(Iterator));
	iterator->table = table;
	iterator->current = NULL;
	iterator->i = 0;
	iterator->next = NULL;
	iterator->j = 0;
	getNextNode(iterator);
	return iterator;
}

void destroyIterator( Iterator *iterator ){
	free(iterator);
}

int iteratorHasNext( Iterator *iterator ){
	if( iterator->next ){
		return 1;
	}
	return 0;
}

void *iteratorNext( Iterator *iterator ){
	iterator->current = iterator->next;
	iterator->i = iterator->j;

	if( iterator->next ){
		iterator->next = getNext(iterator->next);
		if( iterator->next == NULL ){
			iterator->j++;
			getNextNode(iterator);
		}
	}

	if( iterator->current != NULL ){
		Entry *entry = get(iterator->current);
		return entry->data;
	}
	return NULL;
}

char *iteratorKey( Iterator *iterator ){
	if( iterator->current != NULL ){
		Entry *entry = get(iterator->current);
		return entry->key;
	}
	return NULL;
}

void iteratorRemove( Iterator *iterator ){
	if( iterator->current != NULL ){
		destroyEntry( removeNode( *getList( iterator->table, iterator->i ), iterator->current ) );
		iterator->current = NULL;
		iterator->i = 0;
	}
}

int getIteratorI( Iterator *iterator ){
	return iterator->i;
}

int getIteratorJ( Iterator *iterator ){
	return iterator->j;
}
