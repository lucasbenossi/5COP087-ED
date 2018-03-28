#ifndef STACK_H
#define STACK_H

/*
Define uma pilha.
*/
typedef struct _stack Stack;

/*
Paramentros usandos nas funções aqui definidas:
  - stack	Tipo Stack*. Define uma instancia de uma pilha.
  - data	Tipo void*. Ponteiro com o elemento a ser inserido na pilha.
*/

/*
Cria uma pilha.
*/
Stack *createStack();

/*
Destroi uma pilha.
*/
void destroyStack(Stack *stack);

/*
Limpa uma pilha.
*/
void freeStack( Stack *stack );

/*
Insere um elemento no topo da pilha.
*/
void push(Stack *stack, void *data);

/*
Remove um elemento do topo da pilha. Retorna o elemento removido.
*/
void *pop(Stack *stack);

/*
Retorna o elemento do topo da pilha.
*/
void *top(Stack *stack);

/*
Retorna o elemento próximo ao topo da pilha.
*/
void *nextToTop(Stack *stack);

/*
Retorna o tamanho da pilha.
*/
int getStackSize(Stack *stack);

int isStackEmpty(Stack *stack);

#endif
