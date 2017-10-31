#ifndef QUADRA_H
#define QUADRA_H

/*
Define a instancia de uma Quadra, com coordenadas x e y, largura, altura, cep, cor de preenchimento e de borda
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
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro x
*/
double getQuadraX(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro y
*/
double getQuadraY(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro width
*/
double getQuadraWidth(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro height
*/
double getQuadraHeight(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro *cep
*/
char *getQuadraCep(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro *fill
*/
char *getQuadraFill(Quadra *q);

/*
Recebe o ponteiro de uma instancia de Quadra e retorna seu parametro *stroke
*/
char *getQuadraStroke(Quadra *q);

#endif
