#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
Define uma lista ligada.
*/
typedef void List;

/*
Define um no da lista ligada.
*/
typedef void Node;

/*
Paramentros usandos nas funções aqui definidas:
  - list	Tipo List*. Define a instancia de List.
  - node	Tipo Node*. Define uma instancia de Node.
  - data	Tipo void*. Ponteiro com o elemento a ser inserido na lista.
*/

/*
Aloca memória para uma instancia de List
*/
List *createList();

/*
Desaloca memória para uma instancia de List
*/
void destroyList( List *list );

/*
Aloca memoria para uma instancia de Node
*/
Node *createNode( void *data );

/*
Desaloca memória para uma instancia de Node
*/
void destroyNode( Node *node );

/*
Retorna o tamanho da lista ligada.
*/
int lenght( List *list );

/*
Insere um nó no final da lista ligada e retorna um ponteiro para o nó inserido
*/
Node *insert( List *pList, void *data );

/*
Insere um nó na lista ligada, antes do nó definido por "node"
*/
Node *insertBefore( List *pList, Node *pNode, void *data );

/*
Insere um nó na lista ligada, após o nó definido por "node"
*/
Node *insertAfter( List *pList, Node *pNode, void *data );

/*
Recebe uma instancia de List e remove o primeiro nó, retorna o dado que o nó carregava
*/
void *removeFirst( List *pList );

/*
Recebe uma instancia de List e remove o ultimo nó, retorna o dado que o nó carregava
*/
void *removeLast( List *pList );

/*
Remove da lista o nó definido por "node", retorna o dado que o nó carregava
*/
void *removeNode( List *pList, Node *pNode );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o dado que esse nó carrega
*/
void *get( List *list, Node *node );

/*
Recebe uma lista ligada, retorna o primeiro nó dessa lista
*/
Node *getFirst( List *list );

/*
Recebe uma lista ligada, retorna o ultimo nó dessa lista
*/
Node *getLast( List *list );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o próximo nó
*/
Node *getNext( List *list, Node *node );

/*
Recebe uma lista ligada e um nó dessa lista, retorna o nó anterior
*/
Node *getPrevious( List *list, Node *node );

#endif
