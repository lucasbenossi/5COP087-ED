#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "FuncDestroyData.h"

/*
Define uma lista ligada.
*/
typedef struct _list List;

/*
Define um no da lista ligada.
*/
typedef struct _node Node;

/*
Paramentros usandos nas funções aqui definidas:
  - list	Tipo List*. Define a instancia de List.
  - node	Tipo Node*. Define uma instancia de Node.
  - data	Tipo void*. Ponteiro com o elemento a ser inserido na lista.
*/

/* ================================================================================================================ */

/*
Aloca memória para uma instancia de List
*/
List *createList();

/*
Desaloca memória para uma instancia de List
*/
void destroyList( List *list );

/*
Limpa uma instancia de List.
*/
void freeList( List *list );

/*
Reseta os parametros head, tail e size de uma instancia de List.
*/
void resetList( List *list );

/*
Retorna o tamanho da lista ligada.
*/
int lenght( List *list );

int isListEmpty( List *list );

void setListFuncDestroyData( List *list, FuncDestroyData *destroyData );

/*
Insere um nó no final da lista ligada e retorna um ponteiro para o nó inserido
*/
Node *insert( List *list, void *data );
Node *insertFirst( List *list, void *data );

/*
Insere um nó na lista ligada, antes do nó definido por "node"
*/
Node *insertBefore( List *list, Node *node, void *data );

/*
Insere um nó na lista ligada, após o nó definido por "node"
*/
Node *insertAfter( List *list, Node *node, void *data );

/*
Recebe uma instancia de List e remove o primeiro nó, retorna o dado que o nó carregava
*/
void *removeFirst( List *list );

/*
Recebe uma instancia de List e remove o ultimo nó, retorna o dado que o nó carregava
*/
void *removeLast( List *list );

/*
Remove da lista o nó definido por "node", retorna o dado que o nó carregava
*/
void *removeNode( List *list, Node *node );

/*
Recebe uma lista ligada, retorna o primeiro nó dessa lista
*/
Node *getFirst( List *list );

/*
Recebe uma lista ligada, retorna o ultimo nó dessa lista
*/
Node *getLast( List *list );

/* ================================================================================================================ */

/*
Aloca memoria para uma instancia de Node
*/
Node *createNode( void *data );

/*
Desaloca memória para uma instancia de Node
*/
void *destroyNode( Node *node );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o dado que esse nó carrega
*/
void *get( Node *node );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o próximo nó
*/
Node *getNext( Node *node );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o nó anterior
*/
Node *getPrevious( Node *node );

#endif
