#include "Point.h"
#include <stdlib.h>
#include "String.h"

struct _point{
	double x;
	double y;
	char *id;
	char *fill;
	char *stroke;
	void *info;
};

Point *createPoint( double x, double y, char *id, char *fill, char *stroke ){
	Point *p;
	p = malloc( sizeof(Point) );
	p->x = x;
	p->y = y;
	p->id = createString(id);
	p->fill = createString(fill);
	p->stroke = createString(stroke);
	p->info = NULL;
	return p;
}

void destroyPoint( Point *p ){
	destroyString( p->id );
	destroyString( p->fill );
	destroyString( p->stroke );
	free(p);
}

void destroyPointVoid( void *p ){
	destroyPoint(p);
}

double getPointX( Point *p ){
	return p->x;
}

double getPointY( Point *p ){
	return p->y;
}

char *getPointId( Point *p ){
	return p->id;
}

char *getPointFill( Point *p ){
	return p->fill;
}

char *getPointStroke( Point *p ){
	return p->stroke;
}

void *getPointInfo( Point *p ){
	return p->info;
}

void setPointInfo( Point *p, void *info ){
	p->info = info;
}
