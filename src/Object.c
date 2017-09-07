#include "Object.h"
#include <stdlib.h>

struct _object{
    int id;
    char type;
    void *data;
};
typedef struct _object ObjectStr;

Object *createObject( int id, char type, void *data ){
    ObjectStr *obj;
    obj = malloc( sizeof( ObjectStr ) );
    obj->id = id;
    obj->type = type;
    obj->data = data;
    return obj;
}

void *destroyObject( Object *obj ){
    void *data;
    data = ((ObjectStr*)obj)->data;
    free(obj);
    return data;
}

int getObjId( Object *obj ){
    return ((ObjectStr*)obj)->id;
}

char getObjType( Object *obj ){
    return ((ObjectStr*)obj)->type;
}

void *getObjData( Object *obj ){
    return ((ObjectStr*)obj)->data;
}
