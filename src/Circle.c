#include <stdlib.h>
#include "Circle.h"
#include "String.h"

struct _circle {
	int id;
	double radius;
	double x;
	double y;
	char *fill;
};
typedef struct _circle CircleStr;

Circle *createCircle( int id, double radius, double x, double y, char *fill ){
	CircleStr *circle;
	circle = malloc( sizeof( CircleStr ) );

	circle->id = id;
	circle->radius = radius;
	circle->x = x;
	circle->y = y;
	circle->fill = createString(fill);

	return circle;
}

void destroyCircle( Circle *c ){
	destroyString( ((CircleStr*)c)->fill );
	free(c);
}

int getCircleId( Circle *c ){
	return ((CircleStr*)c)->id;
}

void setCircleId( Circle *c, int id ){
	((CircleStr*)c)->id = id;
}

double getCircleRadius( Circle *c ){
	return ((CircleStr*)c)->radius;
}

double getCircleX( Circle *c ){
	return ((CircleStr*)c)->x;
}

void setCircleX( Circle *c, double x ){
	((CircleStr*)c)->x = x;
}

double getCircleY( Circle *c ){
	return ((CircleStr*)c)->y;
}

void setCircleY( Circle *c, double y ){
	((CircleStr*)c)->y = y;
}

char *getCircleFill( Circle *c ){
	return ((CircleStr*)c)->fill;
}
