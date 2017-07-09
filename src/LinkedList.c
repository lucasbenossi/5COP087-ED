#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

Node *createNode( int id, int type, void *data ){
    Node *node;
    node = malloc( sizeof( Node ) );
    node->id = id;
    node->type = type;
	node->data = data;
	node->next = NULL;
	return node;
}

void destroyNode( Node *n ){
    free(n);
}

List *createList(){
    List *l;
    l = malloc( sizeof(List) );
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void destroyList( List *l ){
    free(l);
}

void insert( List *l, Node *node ){
	if( l->head == NULL ){
        l->head = node;
        l->tail = node;
	}
	else{
        l->tail->next = node;
        l->tail = node;
	}
}

Node *getId( List *l, int id ){
    Node *node;
    node = l->head;
    while( node != NULL && node->id != id ){
        node = node->next;
    }
    return node;
}
