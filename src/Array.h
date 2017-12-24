#ifndef ARRAY_H
#define ARRAY_H
#include "LinkedList.h"
#include "Stack.h"
#include "HashTable.h"

/*
Define um vetor com os elementos de uma lista ligada.
*/
typedef struct _array Array;

/* ========================================================================== */

/*
Desaloca memória para uma instancia de Array
*/
void destroyArray( Array *array );

/*
Recebe uma instancia de Array e retorna o seu tamanho
*/
int getArraySize( Array *array );

/*
Recebe uma instancia de Array e retorna o seu vetor
*/
void **getArrayData( Array *array );

/* ========================================================================== */

/*
Cria uma instancia de Array com os elementos de uma instancia de List
*/
Array *listToArray( List *list );

/*
Insere os elementos não nulos de uma instancia de Array em uma instancia de List
*/
void arrayToList( Array *array, List *list );

/* ========================================================================== */

/*
Cria uma instancia de Array e move os elementos de uma instancia de Stack para
essa instancia de Array
*/
Array *stackToArray( Stack *stack );

/*
Insere os elementos não nulos de uma instancia de Array em uma instancia de Stack
*/
void arrayToStack( Array *array, Stack *stack );

/* ========================================================================== */

Array *hashTableToArray( HashTable *ht );

#endif
