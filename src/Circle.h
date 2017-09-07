#ifndef CIRCLE_H
#define CIRCLE_H

/*
Define um circulo num plano 2D.
Possui como atributos valores de id, raio, coordenada x e y (todos double) e
cor de preenchimento (string).
*/
typedef void Circle;

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
Recebe o ponteiro para uma instancia de Circle e retorna seu id
*/
int getCircleId( Circle *c );

/*
Recebe o ponteiro para uma instancia de Circle e um valor de id, e define esse
valor de id na instancia de Circle
*/
void setCircleId( Circle *c, int id );

/*
Recebe o ponteiro para uma instancia de Circle e retorna seu raio
*/
double getCircleRadius( Circle *c );

/*
Recebe o ponteiro para uma instancia de Circle e retorna sua coordenada x
*/
double getCircleX( Circle *c );

/*
Recebe o ponteiro para uma instancia de Circle e um valor de X, e define esse
valor de X na instancia de Circle
*/
void setCircleX( Circle *c, int x );

/*
Recebe o ponteiro para uma instancia de Circle e retorna sua coordenada y
*/
double getCircleY( Circle *c );

/*
Recebe o ponteiro para uma instancia de Circle e um valor de Y, e define esse
valor de Y na instancia de Circle
*/
void setCircleY( Circle *c, int y );

/*
Recebe o ponteiro para uma instancia de Circle e retorna a string com o preenchimento
*/
char *getCircleFill( Circle *c );

#endif
