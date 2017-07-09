#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
Struct para o TAD List<Node>, implementado como lista ligada.
*head = ponteiro para o primeiro elemento da lista
*tail = ponteiro para o último elemento da lista
*/
struct _list{
    struct _node *head;
    struct _node *tail;
};
typedef struct _list List;

/*
Struct para o TAD Node, que nessa inplementação, é o nó da lista ligada.
i = id
type = tipo de objeto
*data = ponteiro para a instancia do objeto que este nó da lista carrega
*next = ponteiro para o proximo elemento da lista
*/
struct _node{
    int id;
    int type;
    void *data;
    struct _node *next;
};
typedef struct _node Node;

/*
Aloca memoria para uma instancia de Node
*/
Node *createNode( int id, int type, void *data );

/*
Desaloca memória para uma instancia de Node
*/
void destroyNode( Node *n );

/*
Aloca memória para uma instancia de List
*/
List *createList();

/*
Desaloca memória para uma instancia de List
*/
void destroyList( List *l );

/*
Insere um nó na lista ligada
*l = struct que define a lista
*/
void insert( List *l, Node *node );

/*
Retorna o ponteiro para o no da lista com o id fornecido em "id"
*l = struct que define a lista
*id = id a ser procurado
*/
Node *getId( List *l, int id );

#endif
