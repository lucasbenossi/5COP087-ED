#ifndef WRITETAGS_H
#define WRITETAGS_H
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include <stdio.h>

/*
Recebe o ponteiro para uma struct Rect e escreve em "*svg" a sua tag
correspondente;
*/
void writeRectTag( Rect *rect, FILE *svg );

/*
Recebe o ponteiro para uma struct Circle e escreve em "*svg" a sua tag
correspondente;
*/
void writeCircleTag( Circle *circle, FILE *svg );

/*
Escreve a tag svg do retangulo pontilhado usado para destacar quando dois
objetos se sobrepoem
*rect = retangulo definido
*svg = stream de saida
*/
void writeOverlapTag( Rect *rect, FILE *svg );

/*
Recebe o ponteiro para uma struct Quadra e escreve em "*svg" a sua tag
correspondente;
*/
void writeQuadraTag( Quadra *q, FILE *svg );

/*
Recebe o ponteiro para uma struct Point e escreve em "*svg" a sua tag
correspondente;
*/
void writePointTag( Point *p, FILE *svg );

/*
Recebe o ponteiro para uma struct Point e escreve em "*svg" as suas tags
correspondentes, quando a struct Point define um hidrante;
*/
void writeHidranteTag( Point *p, FILE *svg );

/*
Recebe o ponteiro para uma struct Point e escreve em "*svg" as suas tags
correspondentes, quando a struct Point define um semaforo;
*/
void writeSemaforoTag( Point *p, FILE *svg );

/*
Recebe o ponteiro para uma struct Point e escreve em "*svg" as suas tags
correspondentes, quando a struct Point define uma torre;
*/
void writeTorreTag( Point *p, FILE *svg );

#endif
