#ifndef WRITETAGS_H
#define WRITETAGS_H
#include "Cidade.h"
#include "Object.h"
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "Polygon.h"
#include <stdio.h>

#define ANCHOR_RADIUS 5.0
#define ANCHOR_OPACITY 1.0

/*
Escreve "<svg>" em *svg;
*/
void writeSvgStart( FILE *svg );

/*
Escreve "</svg>" em *svg;
*/
void writeSvgEnd( FILE *svg );

/*
Escreve em *svg as tags para os objetos do T2 (circulos e retangulos)
*/
void writeObjsTags( List *objs, FILE *svg );

/*
Escreve em *svg as tags dos elementos que formam uma instancia de Cidade
(intancias de Quadra e Point).
*/
void writeCidadeTags( Cidade *cidade, FILE *svg );

/*
Escreve em *svg as tags que formam as coberturas das torres de uma instancia de
Cidade.
*/
void writeCidadeTorresCoberturaTags( Cidade *cidade, FILE *svg );

/*
Recebe uma instancia de Rect e escreve em *svg as suas tags correspondentes.
*/
void writeRectTag( Rect *rect, FILE *svg );

/*
Recebe uma instancia de Circle e escreve em *svg as suas tags correspondentes.
*/
void writeCircleTag( Circle *circle, FILE *svg );

/*
Escreve a tag svg do retangulo pontilhado usado para destacar quando dois
objetos se sobrepoem
*/
void writeOverlapTag( Rect *rect, FILE *svg );

/*
Escreve a tag svg do circulo que define os pontos que o comando "a" cria.
*/
void writeAnchorTag( char *i, double x, double y, double r, char *fill, double opacity, FILE *svg );

/*
Recebe uma instancia de Quadra e escreve em *svg as suas tags correspondentes.
*/
void writeQuadraTag( Quadra *q, FILE *svg );

/*
- Recebe uma instancia de Point e escreve em *svg as suas tags correspondentes.
- A intancia de Point pode definir um ponto qualquer, um Hidrante, um Semáforo
  ou uma Torre.
*/
void writeHidranteTag( Point *p, FILE *svg );
void writeSemaforoTag( Point *p, FILE *svg );
void writeTorreTag( Point *p, FILE *svg );

/*
Recebe uma instancia de Point que define uma torre, escreve em *svg uma tag para
mostrar o raio de cobertura da torre.
*/
void writeTorreCoberturaTag( Point *p, FILE *svg );

/*
Recebe uma instancia de Polygon e escreve em *svg as suas tags correspondentes.
*/
void writePolygonTag( Polygon *polygon, FILE *svg );

/*
Recebe uma string e coordenadas x e y e escreve sua tag correspondente.
*/
void writeStringTag( char *string, double x, double y, FILE *svg );

void writeEstabComerciaisTag( Cidade *cidade, FILE *svg );

void writeMoradoresTag( Cidade *cidade, FILE *svg );

void writeConexoesTags( Cidade *cidade, FILE *svg );

void writeDefuntosTags( Cidade *cidade, FILE *svg );

#endif
