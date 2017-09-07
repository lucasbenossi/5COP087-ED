#include "Point.h"
#include <stdlib.h>
#include "ProcString.h"

struct _point{
    double x;
    double y;
    char *id;
    char *fill;
    char *stroke;
};
typedef struct _point PointStr;

Point *createPoint( double x, double y, char *id, char *fill, char *stroke ){
    PointStr *p;
    p = malloc( sizeof(PointStr) );
    p->x = x;
    p->y = y;
    p->id = createString(id);
    p->fill = createString(fill);
    p->stroke = createString(stroke);
    return p;
}

void destroyPoint( Point *p ){
    destroyString( ((PointStr*)p)->id );
    destroyString( ((PointStr*)p)->fill );
    destroyString( ((PointStr*)p)->stroke );
    free(p);
}

double getPointX( Point *p ){
    return ((PointStr*)p)->x;
}

double getPointY( Point *p ){
    return ((PointStr*)p)->y;
}

char *getPointId( Point *p ){
    return ((PointStr*)p)->id;
}

char *getPointFill( Point *p ){
    return ((PointStr*)p)->fill;
}

char *getPointStroke( Point *p ){
    return ((PointStr*)p)->stroke;
}
