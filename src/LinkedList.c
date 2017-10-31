#include "LinkedList.h"
#include <stdlib.h>

struct _list{
    struct _node *head;
    struct _node *tail;
    int size;
};

struct _node{
    void *data;
    struct _node *next;
    struct _node *previous;
};

/* ================================================================================================================ */

List *createList(){
    List *list;
    list = malloc( sizeof(List) );
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void destroyList( List *list ){
    freeList(list);
    free(list);
}

void freeList( List *list ){
    Node *node, *node0;

    node = list->head;
    while( node != NULL ){
        node0 = node;
        node = node->next;
        destroyNode(node0);
    }

    resetList(list);
}

void resetList( List *list ){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int lenght( List *list ){
    return list->size;
}

Node *insert( List *list, void *data ){
    Node *node;

    node = createNode(data);

    if( list->head == NULL ){
        list->head = node;
        list->tail = node;
	}
	else{
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
	}
    (list->size)++;
    return node;
}

Node *insertBefore( List *list, Node *node, void *data ){
    Node *newNode, *node0, *previousNode;

    newNode = NULL;
    node0 = node;

    if( list->head != NULL && node0 != NULL ){
        newNode = createNode(data);
        previousNode = node0->previous;
        if( previousNode == NULL ){
            list->head = newNode;
        }
        else{
            previousNode->next = newNode;
            newNode->previous = previousNode;
        }
        newNode->next = node0;
        node0->previous = newNode;
        (list->size)++;
    }
    return newNode;
}

Node *insertAfter( List *list, Node *node, void *data ){
    Node *newNode, *nextNode;

    newNode = NULL;

    if( list->tail != NULL && node != NULL ){
        newNode = createNode(data);
        nextNode = node->next;
        if( nextNode == NULL ){
            list->tail = newNode;
        }
        else{
            nextNode->previous = newNode;
            newNode->next = nextNode;
        }
        newNode->previous = node;
        node->next = newNode;
        (list->size)++;
    }
    return newNode;
}

void *removeFirst( List *list ){
    void *data;
    Node *node;

    data = NULL;

    if( list->head != NULL ){
        node = list->head;
        if( list->head == list->tail ){
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            list->head = list->head->next;
            list->head->previous = NULL;
        }
        data = destroyNode(node);
        (list->size)--;
    }
    return data;
}

void *removeLast( List *list ){
    void *data;
    Node *node;

    data = NULL;

    if( list->tail != NULL ){
        node = list->tail;
        if( list->tail == list->head ){
            list->tail = NULL;
            list->head = NULL;
        }
        else{
            list->tail = list->tail->previous;
            list->tail->next = NULL;
        }
        data = destroyNode(node);
        (list->size)--;
    }
    return data;
}

void *removeNode( List *list, Node *node ){
    void *data;
    Node *nextNode, *previousNode;

    data = NULL;

    if( list->head != NULL && node != NULL ){
        nextNode = node->next;
        previousNode = node->previous;
        if( previousNode == NULL ){
            list->head = nextNode;
        }
        else{
            previousNode->next = nextNode;
        }
        if( nextNode == NULL ){
            list->tail = previousNode;
        }
        else{
            nextNode->previous = previousNode;
        }
        data = destroyNode(node);
        (list->size)--;
    }
    return data;
}

Node *getFirst( List *list ){
    return list->head;
}

Node *getLast( List *list ){
    return list->tail;
}

/* ================================================================================================================ */

Node *createNode( void *data ){
    Node *node;
    node = malloc( sizeof( Node ) );
    node->data = data;
	node->next = NULL;
    node->previous = NULL;
	return node;
}

void *destroyNode( Node *node ){
    void *data;
    data = get(node);
    free(node);
    return data;
}

Node *getNext( Node *node ){
    return node->next;
}

Node *getPrevious( Node *node ){
    return node->previous;
}

void *get( Node *node ){
    return node->data;
}
