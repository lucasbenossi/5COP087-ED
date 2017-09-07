#include <stdlib.h>
#include "Rect.h"
#include "ProcString.h"

struct _rect {
    int id;
    double width;
    double height;
    double x;
    double y;
    char *fill;
};
typedef struct _rect RectStr;

Rect *createRect( int id, double width, double height, double x, double y, char *fill ){
    RectStr *rect;
    rect = malloc( sizeof( RectStr ) );

    rect->id = id;
    rect->width = width;
    rect->height = height;
    rect->x = x;
    rect->y = y;
    rect->fill = createString(fill);

    return rect;
}

void destroyRect( Rect *r ){
    destroyString( ((RectStr*)r)->fill );
    free(r);
}

int getRectId( Rect *r ){
    return ((RectStr*)r)->id;
}

double getRectWidth( Rect *r ){
    return ((RectStr*)r)->width;
}

double getRectHeight( Rect *r ){
    return ((RectStr*)r)->height;
}

double getRectX( Rect *r ){
    return ((RectStr*)r)->x;
}

double getRectY( Rect *r ){
    return ((RectStr*)r)->y;
}

char *getRectFill( Rect *r ){
    return ((RectStr*)r)->fill;
}
