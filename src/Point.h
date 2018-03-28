#ifndef POINT_H
#define POINT_H

/*
- Define uma instancia de Point, com id (string) e coordenadas x e y (double).
- Infomação específica seria vazão (caso o ponto represente um hidrante), raio
  de alcance (caso o ponto represente uma torre de radio), ou o tempo do ciclo
  (caso o ponto represente um semaforo).
*/
typedef struct _point Point;

/*
Aloca memória para uma instancia de Point e retorna seu ponteiro
*/
Point *createPoint( double x, double y, char *id, char *fill, char *stroke );

/*
Desaloca memória de uma instancia de Point
*/
void destroyPoint( Point *p );
void destroyPointVoid( void *p );

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
Retorna o preenchimento de uma instancia de Point.
*/
char *getPointFill( Point *p );

/*
Recebe o ponteiro para uma instancia de Point e retorna seu parametro *stroke
*/
char *getPointStroke( Point *p );

/*
Retorna ou define a informação específica do ponto.
*/
void *getPointInfo( Point *p );
void setPointInfo( Point *p, void *info );

#endif
