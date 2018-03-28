#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"

#define NE 1
#define NW 2
#define SW 3
#define SE 4

/*
Calcula a distancia entre os pontos (x1,y1) e (x2,y2)
*/
double distancePoints( double x1, double y1, double x2, double y2 );

/*
Calcula o quadrado da distancia entre os pontos (x1,y1) e (x2,y2)
*/
double distancePointsSquared( double x1, double y1, double x2, double y2 );

double *getQuadraticCurve( double xu, double yu, double xv, double yv );

/*
Ponto raiz divide o plano em quatro quadrantes.
Retorna em qual plano o ponto (x,y) está:
	1 = NE
	2 = NW
	3 = SW
	4 = SE
*/
int quadrantPointRoot( double rootX, double rootY, double x, double y );

/*
Se os circulos "circle1" e "circle2" se sobrepoem, retora 1, caso contrário,
retorna 0
*/
int circleCircleOverlap( Circle *c1, Circle *c2 );

/*
Se os retangulos "rect1" e "rect2" se sobrepoem, retora 1, caso contrário,
retorna 0
*/
int rectRectOverlap( Rect *r1, Rect *r2 );

/*
Se o circulo "circle1" sobrepoe com o retangulo "rect1", retorna 1, caso
contrário, retorna 0
*/
int circleRectOverlap( Circle *c, Rect *r );

/*
Verifica se o ponto (x,y) está dentro do circulo "circle", retorna 1 caso
positivo ou 0 caso negativo
*/
int pointInsideCircle( double x, double y, Circle *c );

/*
Verifica se o ponto (x,y) está dentro do retangulo "rect", retorna 1 caso
positivo ou 0 caso negativo
*/
int pointInsideRect( double x, double y, Rect *r );

/*
Verifica se uma instancia de Quadra está completamente dentro de uma instancia
de Circle, retorna 1 caso positivo ou 0 caso negativo
*/
int quadraInsideCircle( Quadra *q, Circle *c );

/*
Verifica se uma instancia de Quadra está completamente dentro de uma instancia
de Rect, retorna 1 caso positivo ou 0 caso negativo
*/
int quadraInsideRect( Quadra *q, Rect *r );

/*
Calcula as coordenadas dos pontos superior esquerdo e inferior direito
de dois circulos definidos por "c1" e "c2", escreve os valores das coordenadas
dos dois pontos em x1, y1, x2, y2
*/
void edgesCircleCircle( Circle *c1, Circle *c2, double *x1, double *y1, double *x2, double *y2 );

/*
Calcula as coordenadas dos pontos superior esquerdo e inferior direito
de dois retangulos definidos por "r1" e "r2", escreve os valores das coordenadas
dos dois pontos em x1, y1, x2, y2
*/
void edgesRectRect( Rect *r1, Rect *r2, double *x1, double *y1, double *x2, double *y2 );

/*
Calcula as coordenadas dos pontos superior esquerdo e inferior direito
de um circulo definido por "c" e de um retangulo definido por "r", escreve os
valores das coordenadas dos dois pontos em x1, y1, x2, y2
*/
void edgesCircleRect( Circle *c, Rect *r, double *x1, double *y1, double *x2, double *y2 );

#endif
