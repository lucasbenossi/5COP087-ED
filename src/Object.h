#ifndef OBJECT_H
#define OBJECT_H

/*
- Uma instancia de Object é usada em conjunto com outras estruturas de dados
  para indexar e identificar objetos de um plano 2D.
- Contem parametros como id (int), type (char), data (void*) e info (void*).
- O parametro data define a instancia do objeto no plano 2D que a instancia de Object carrega.
- O parametro info carrega informções específicas do objeto que a instancia de Object carrega.
- O parametro type carrega o tipo do objeto que a instancia de Object carrega.
- O parametro id carrega o ID do objeto que a instancia de Object carrega.
*/
typedef struct _object Object;

/*
Aloca memoria para uma instancia de Object
*/
Object *createObject( char *id, char type, void *data );

/*
Desaloca memoria para uma instancia de Object e retorna o ponteiro do
parametro *data
*/
void *destroyObject( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "id"
*/
char *getObjId( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "type"
*/
char getObjType( Object *obj );

/*
Recebe o ponteiro para uma instancia de Object e retorna seu parametro "data"
*/
void *getObjData( Object *obj );

/*
Define ou retorna a informação específica do objeto.
*/
void setObjInfo( Object *obj, void *info );
void *getObjInfo( Object *obj );

#endif
