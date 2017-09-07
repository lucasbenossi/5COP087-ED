#include <stdlib.h>
#include "LinkedList.h"

struct _list{
    struct _node *head;
    struct _node *tail;
    int size;
};
typedef struct _list ListStr;

List *createList(){
    ListStr *l;
    l = malloc( sizeof(ListStr) );
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void destroyList( List *list ){
    free(list);
}

struct _node{
    void *data;
    struct _node *next;
    struct _node *previous;
};
typedef struct _node NodeStr;

Node *createNode( void *data ){
    NodeStr *node;
    node = malloc( sizeof( NodeStr ) );
    node->data = data;
	node->next = NULL;
    node->previous = NULL;
	return node;
}

void destroyNode( Node *node ){
    free(node);
}

int lenght( List *list ){
    return ((ListStr*)list)->size;
}

Node *insert( List *pList, void *data ){
    NodeStr *node;
    ListStr *list;

    node = createNode(data);
    list = pList;

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

Node *insertBefore( List *pList, Node *pNode, void *data ){
    NodeStr *newNode, *node, *previousNode;
    ListStr *list;

    newNode = NULL;
    node = pNode;
    list = pList;

    if( list->head != NULL && node != NULL ){
        newNode = createNode(data);
        previousNode = node->previous;
        if( previousNode == NULL ){
            list->head = newNode;
        }
        else{
            previousNode->next = newNode;
            newNode->previous = previousNode;
        }
        newNode->next = node;
        node->previous = newNode;
        (list->size)++;
    }
    return newNode;
}

Node *insertAfter( List *pList, Node *pNode, void *data ){
    NodeStr *newNode, *node, *nextNode;
    ListStr *list;

    newNode = NULL;
    node = pNode;
    list = pList;

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

void *removeFirst( List *pList ){
    void *data;
    NodeStr *node;
    ListStr *list;

    data = NULL;
    list = pList;

    if( list->head != NULL ){
        node = list->head;
        data = node->data;
        if( list->head == list->tail ){
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            list->head = list->head->next;
            list->head->previous = NULL;
        }
        destroyNode(node);
        (list->size)--;
    }
    return data;
}

void *removeLast( List *pList ){
    void *data;
    NodeStr *node;
    ListStr *list;

    data = NULL;
    list = pList;

    if( list->tail != NULL ){
        node = list->tail;
        data = node->data;
        if( list->tail == list->head ){
            list->tail = NULL;
            list->head = NULL;
        }
        else{
            list->tail = list->tail->previous;
            list->tail->next = NULL;
        }
        destroyNode(node);
        (list->size)--;
    }
    return data;
}

void *removeNode( List *pList, Node *pNode ){
    void *data;
    NodeStr *node, *nextNode, *previousNode;
    ListStr *list;

    data = NULL;
    node = pNode;
    list = pList;

    if( list->head != NULL && node != NULL ){
        nextNode = node->next;
        previousNode = node->previous;
        data = node->data;
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
        destroyNode(node);
        (list->size)--;
    }
    return data;
}

void *get( List *list, Node *node ){
    if( list != NULL && node != NULL ){
        return ((NodeStr*)node)->data;
    }
    return NULL;
}

Node *getFirst( List *list ){
    if( list != NULL && ((ListStr*)list)->head != NULL ){
        return ((ListStr*)list)->head;
    }
    return NULL;
}

Node *getLast( List *list ){
    if( list != NULL && ((ListStr*)list)->tail != NULL ){
        return ((ListStr*)list)->tail;
    }
    return NULL;
}

Node *getNext( List *list, Node *node ){
    if( list != NULL && node != NULL ){
        return ((NodeStr*)node)->next;
    }
    return NULL;
}

Node *getPrevious( List *list, Node *node ){
    if( list != NULL && node != NULL ){
        return ((NodeStr*)node)->previous;
    }
    return NULL;
}
