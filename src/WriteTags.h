#ifndef WRITETAGS_H
#define WRITETAGS_H
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

#endif
