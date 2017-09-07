#ifndef OBJECT_H
#define OBJECT_H

/*
- Uma instancia de Object é usada em conjunto com uma lista para indexar e identificar
  objetos de um plano 2D.
- Contem parametros como id (int), type (char) e data (void*).
- O parametro data é um ponteiro para a instancia do objeto no plano 2D que essa
  instancia de Object referencia.
- O parametro type carrega o tipo do objeto que a instancia de Object referencia.
- O parametro id carrega o ID do objeto que a instancia de Object referencia.
*/
typedef void Object;

/*
Aloca memoria para uma instancia de Object
*/
Object *createObject( int id, char type, void *data );

/*
Desaloca memoria para uma instancia de Object e retorna o ponteiro do
parametro *data
*/
void *destroyObject( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "id"
*/
int getObjId( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "type"
*/
char getObjType( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "data"
*/
void *getObjData( Object *obj );

#endif
