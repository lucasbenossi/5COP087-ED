#ifndef QUADRA_H
#define QUADRA_H
#include "HashTable.h"

/*
Define a instancia de uma Quadra, com coordenadas x e y, largura, altura, cep,
cor de preenchimento e de borda
*/
typedef struct _quadra Quadra;

/*
Aloca memoria para uma instancia de Quadra e retorna seu ponteiro
*/
Quadra *createQuadra( double x, double y, double width, double height, char *cep, char *fill, char *stroke );

/*
Desaloca memória de uma instancia de Quadra
*/
void destroyQuadra(Quadra *q);

/*
Retorna o parametro correspondente de uma instancia de Quadra.
*/
double getQuadraX(Quadra *q);
double getQuadraY(Quadra *q);
double getQuadraWidth(Quadra *q);
double getQuadraHeight(Quadra *q);
char *getQuadraCep(Quadra *q);
char *getQuadraFill(Quadra *q);
char *getQuadraStroke(Quadra *q);
HashTable *getQuadraEstabComerciais(Quadra *q);
HashTable *getQuadraMoradores(Quadra *q);

#endif
