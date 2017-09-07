#ifndef OBJLIST_H
#define OBJLIST_H
#include "Object.h"
#include "LinkedList.h"

/*
Procura na lista fornecida em "l" por uma instancia de Object, com id forcenido
em "id", e retorna o ponteiro para a instancia de Object que foi encontrada, ou
NULL se nada foi encontrado.
*l = struct que define a lista
id = id a ser procurado
*/
Object *getIdInt( List *l, int id );

/*
Limpa uma lista ligada com instancias de Object, desalocando memória para todos
os nos da lista, todas as intancias de Object, as intancias (Quadra, Point,
Circle ou Rect) que a instancia de Object referencia, e struct da lista.
*l = ponteiro para a instancia da lista ligada usada
*/
void destroyObjList( List *l );

#endif
