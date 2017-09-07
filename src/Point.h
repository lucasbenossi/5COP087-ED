#ifndef POINT_H
#define POINT_H

/*
Define uma instancia de Point, com id e coordenadas x e y
*/
typedef void Point;

/*
Aloca memória para uma instancia de Point e retorna seu ponteiro
*/
Point *createPoint( double x, double y, char *id, char *fill, char *stroke );

/*
Desaloca memória de uma instancia de Point
*/
void destroyPoint( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro x
*/
double getPointX( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro y
*/
double getPointY( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro id
*/
char *getPointId( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro *fill
*/
char *getPointFill( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro *stroke
*/
char *getPointStroke( Point *p );

#endif
