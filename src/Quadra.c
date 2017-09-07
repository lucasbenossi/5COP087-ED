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
typedef struct _quadra QuadraStr;

Quadra *createQuadra( double x, double y, double width, double height, char *cep, char *fill, char *stroke ){
    QuadraStr *q;
    q = malloc( sizeof(QuadraStr) );
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
    destroyString( ((QuadraStr*)q)->cep );
    destroyString( ((QuadraStr*)q)->fill );
    destroyString( ((QuadraStr*)q)->stroke );
    free(q);
}

double getQuadraX(Quadra *q){
    return ((QuadraStr*)q)->x;
}

double getQuadraY(Quadra *q){
    return ((QuadraStr*)q)->y;
}

double getQuadraWidth(Quadra *q){
    return ((QuadraStr*)q)->width;
}

double getQuadraHeight(Quadra *q){
    return ((QuadraStr*)q)->height;
}

char *getQuadraCep(Quadra *q){
    return ((QuadraStr*)q)->cep;
}

char *getQuadraFill(Quadra *q){
    return ((QuadraStr*)q)->fill;
}

char *getQuadraStroke(Quadra *q){
    return ((QuadraStr*)q)->stroke;
}
