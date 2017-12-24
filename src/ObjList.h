#ifndef OBJLIST_H
#define OBJLIST_H
#include "LinkedList.h"

/*
Limpa uma lista ligada com instancias de Object, desalocando memória para todos
os nos da lista, todas as intancias de Object, as intancias (Quadra, Point,
Circle ou Rect) que a instancia de Object referencia, e a instancia de List.
*/
void destroyObjList( List *list );

#endif
