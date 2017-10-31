#ifndef CIRCLE_H
#define CIRCLE_H

/*
Define um circulo num plano 2D.
Possui como atributos valores de id, raio, coordenada x e y (todos double) e
cor de preenchimento (string).
*/
typedef struct _circle Circle;

/*
Aloca memória para uma instancia de Circle e escreve os valores id, raio, x, y e
fill nos seus atributos, retorna o ponteiro para o espaco de memoria alocado.
*/
Circle *createCircle( int id, double radius, double x, double y, char *fill );

/*
Desaloca a memória de uma instancia de Circle.
*/
void destroyCircle( Circle *c );

/*
Retorna ou define o id de uma instanca de Circle.
*/
int getCircleId( Circle *c );
void setCircleId( Circle *c, int id );

/*
Recebe o ponteiro para uma instancia de Circle e retorna seu raio
*/
double getCircleRadius( Circle *c );

/*
Retorna ou define a coordenada X de uma instanca de Circle.
*/
double getCircleX( Circle *c );
void setCircleX( Circle *c, double x );

/*
Retorna ou define a coordenada Y de uma instanca de Circle.
*/
double getCircleY( Circle *c );
void setCircleY( Circle *c, double y );

/*
Recebe o ponteiro para uma instancia de Circle e retorna a string com o preenchimento
*/
char *getCircleFill( Circle *c );

#endif
