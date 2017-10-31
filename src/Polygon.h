#ifndef POLYGON_H
#define POLYGON_H
#include "LinkedList.h"

/*
Define um polígono.
*/
typedef struct _polygon Polygon;

/*
Cria uma instancia de Polygon.
*/
Polygon *createPolygon( char *id, char *fill, char *stroke );

/*
Destroi uma instancia de Polygon.
*/
void destroyPolygon( Polygon *polygon );

/*
Insere um nó com coordenadas (x,y) em uma instancia de Polygon.
*/
void polygonInsertNode( Polygon *polygon, double x, double y );

/*
Retorna uma instancia de List com instancias de Point, cada instancia de Point
representa o nó de uma instancia de Polygon.
*/
List *getPolygonNodes( Polygon *polygon );

/*
Retorna atributos de uma instancia de Polygon.
*/
char *getPolygonId( Polygon *polygon );
char *getPolygonFill( Polygon *polygon );
char *getPolygonStroke( Polygon *polygon );
int getPolygonNumNodes( Polygon *polygon );

/*
Calcula a área do polígono que uma instancia de Polygon define.
*/
double polygonArea( Polygon *polygon );

#endif
