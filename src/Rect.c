#include <stdlib.h>
#include "Rect.h"

Rect *createRect( int i, double w, double h, double x, double y, char *fill ){
    Rect *rect;
    rect = malloc( sizeof( Rect ) );

    rect->i = i;
    rect->w = w;
    rect->h = h;
    rect->x = x;
    rect->y = y;
    rect->fill = fill;

    return rect;
}

void destroyRect( Rect *r ){
    free( r );
}

int getRectId( Rect *r ){
    return r->i;
}

double getRectWidth( Rect *r ){
    return r->w;
}

double getRectHeight( Rect *r ){
    return r->h;
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
