#ifndef OBJLIST_H
#define OBJLIST_H
#include "Object.h"
#include "LinkedList.h"

/*
Procura na lista fornecida em "l" por uma instancia de Object, que referencia
uma instancia de Circle ou Rect com id forcenido em "id", e retorna o ponteiro
para a instancia de Object que foi encontrada, ou NULL se nada foi encontrado.
*l = struct que define a lista
id = id a ser procurado
*/
Object *searchIdInt( List *l, int id );

/*
Desaloca memoria de uma instancia de Object e a intancia de Quadra, Point,
Circle ou Rect que a instancia de Object referencia.
*/
void destroyDataObj( Object *data );

/*
Limpa uma lista ligada com instancias de Object, desalocando memória para todos
os nos da lista, todas as intancias de Object, as intancias (Quadra, Point,
Circle ou Rect) que a instancia de Object referencia, e a instancia de List.
*/
void destroyObjList( List *list );

/*
Recebe uma instancia de Object, que referencia uma instancia de Circle, Rect,
Quadra ou Point, retorna o valor de X ou Y correspondente.
*/
double getX( Object *obj );
double getY( Object *obj );

/*
Recebe uma instancia de Object, que referencia uma instancia de Circle ou Rect,
retorna o id da instancia de Circle ou Rect.
*/
int getIdInt( Object *obj );

#endif
