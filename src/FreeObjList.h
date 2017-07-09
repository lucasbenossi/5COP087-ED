#ifndef FREEOBJLIST_H
#define FREEOBJLIST_H
#include "LinkedList.h"

/*
**head = cabecalho da lista ligada
**tail = cauda da lista ligada
Limpa uma lista ligada, desalocando a memoria de todos os seus elementos
*/
void freeObjList( List *l );

#endif
