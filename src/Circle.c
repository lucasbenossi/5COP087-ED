#include <stdlib.h>
#include "Circle.h"

Circle *createCircle( int i, double r, double x, double y, char *fill ){
    Circle *circle;
    circle = malloc( sizeof( Circle ) );

    circle->i = i;
    circle->r = r;
    circle->x = x;
    circle->y = y;
    circle->fill = fill;

    return circle;
}

void destroyCircle( Circle *c ){
    free( c );
}

int getCircleId( Circle *c ){
    return c->i;
}

double getCircleRadius( Circle *c ){
    return c->r;
}

double getCircleX( Circle *c ){
    return c->x;
}

double getCircleY( Circle *c ){
    return c->y;
}

char *getCircleFill( Circle *c ){
    return c->fill;
}
