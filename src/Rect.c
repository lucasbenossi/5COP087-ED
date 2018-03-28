#include <stdlib.h>
#include "Rect.h"
#include "String.h"

struct _rect {
	int id;
	double width;
	double height;
	double x;
	double y;
	char *fill;
};

Rect *createRect( int id, double width, double height, double x, double y, char *fill ){
	Rect *rect;
	rect = malloc( sizeof( Rect ) );

	rect->id = id;
	rect->width = width;
	rect->height = height;
	rect->x = x;
	rect->y = y;
	rect->fill = createString(fill);

	return rect;
}

void destroyRect( Rect *r ){
	destroyString( r->fill );
	free(r);
}

int getRectId( Rect *r ){
	return r->id;
}

double getRectWidth( Rect *r ){
	return r->width;
}

double getRectHeight( Rect *r ){
	return r->height;
}

double getRectX( Rect *r ){
	return r->x;
}

double getRectY( Rect *r ){
	return r->y;
}

char *getRectFill( Rect *r ){
	return r->fill;
}
