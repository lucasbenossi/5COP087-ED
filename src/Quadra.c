#include <stdlib.h>
#include "Quadra.h"
#include "ProcString.h"

struct _quadra {
    double x;
    double y;
    double width;
    double height;
    char *cep;
    char *fill;
    char *stroke;
};

Quadra *createQuadra( double x, double y, double width, double height, char *cep, char *fill, char *stroke ){
    Quadra *q;
    q = malloc( sizeof(Quadra) );
    q->x = x;
    q->y = y;
    q->width = width;
    q->height = height;
    q->cep = createString(cep);
    q->fill = createString(fill);
    q->stroke = createString(stroke);
    return q;
}

void destroyQuadra(Quadra *q){
    destroyString( q->cep );
    destroyString( q->fill );
    destroyString( q->stroke );
    free(q);
}

double getQuadraX(Quadra *q){
    return q->x;
}

double getQuadraY(Quadra *q){
    return q->y;
}

double getQuadraWidth(Quadra *q){
    return q->width;
}

double getQuadraHeight(Quadra *q){
    return q->height;
}

char *getQuadraCep(Quadra *q){
    return q->cep;
}

char *getQuadraFill(Quadra *q){
    return q->fill;
}

char *getQuadraStroke(Quadra *q){
    return q->stroke;
}
