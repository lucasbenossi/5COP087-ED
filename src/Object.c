#include "Object.h"
#include <stdlib.h>
#include "String.h"

struct _object{
	char *id;
	char type;
	void *data;
	void *info;
};

Object *createObject( char *id, char type, void *data ){
	Object *obj;
	obj = malloc( sizeof( Object ) );
	obj->id = createString(id);
	obj->type = type;
	obj->data = data;
	obj->info = NULL;
	return obj;
}

void *destroyObject( Object *obj ){
	void *data;

	data = obj->data;

	destroyString(obj->id);
	free(obj);

	return data;
}

char *getObjId( Object *obj ){
	return obj->id;
}

char getObjType( Object *obj ){
	return obj->type;
}

void *getObjData( Object *obj ){
	return obj->data;
}

void setObjInfo( Object *obj, void *info ){
	obj->info = info;
}

void *getObjInfo( Object *obj ){
	return obj->info;
}
