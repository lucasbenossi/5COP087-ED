#include "Stack.h"
#include <stdlib.h>

struct _stack{
	struct _node *top;
	int size;
};

struct _node{
	struct _node *previous;
	void *data;
};
typedef struct _node Node;

static Node *createNode(void *data);

static void *destroyNode(Node *node);

/* ================================================================================================================ */

static Node *createNode(void *data){
	Node *node;
	node = malloc( sizeof(Node) );
	node->data = data;
	node->previous = NULL;
	return node;
}

static void *destroyNode(Node *node){
	void *data;
	data = node->data;
	free(node);
	return data;
}

/* ================================================================================================================ */

Stack *createStack(){
	Stack *stack;
	stack = malloc( sizeof(Stack) );
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void destroyStack(Stack *stack){
	freeStack(stack);
	free(stack);
}

void freeStack( Stack *stack ){
	Node *node, *node0;

	node = stack->top;
	while( node != NULL ){
	    node0 = node;
	    node = node->previous;
	    destroyNode(node0);
	}

	stack->top = NULL;
	stack->size = 0;
}

void push(Stack *stack, void *data){
	Node *node;

	node = createNode(data);

	node->previous = stack->top;
	stack->top = node;

	(stack->size)++;
}

void *pop(Stack *stack){
	Node *node;
	void *data;

	node = stack->top;
	data = NULL;

	if( node != NULL ){
	    stack->top = node->previous;
	    data = destroyNode(node);
	    (stack->size)--;
	}

	return data;
}

void *top(Stack *stack){
	if( stack->top != NULL ){
	    return stack->top->data;
	}
	return NULL;
}

void *nextToTop(Stack *stack){
	if( stack->top != NULL && stack->top->previous != NULL ){
	    return stack->top->previous->data;
	}
	return NULL;
}

int getStackSize(Stack *stack){
	return stack->size;
}

int isStackEmpty(Stack *stack){
	return stack->size == 0;
}
