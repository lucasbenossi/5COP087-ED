#ifndef CIRCLE_H
#define CIRCLE_H

/*
Struct para o TAD Circle
i = id
r = raio
x, y = coordenadas do centro do circulo
*fill = string com a cor de preenchimento
*/
struct _circle {
    int i;
    double r;
    double x;
    double y;
    char *fill;
};
typedef struct _circle Circle;

/*
Na lista ligada, é definida como de tipo 1, quando adicionada pelo comanando "c"
*/

/*
Aloca memória para uma struct do tipo Circle e escreve os valores i, r, x, y e
fill nos seus atributos, retorna o ponteiro para o espaco de memoria alocado
*/
Circle *createCircle( int i, double r, double x, double y, char *fill );

/*
Desaloca a memória de uma struct do tipo Circle.
*/
void destroyCircle( Circle *c );

/*
Recebe o ponteiro para uma struct do tipo Circle e retorna o seu atributo "i" (id)
*/
int getCircleId( Circle *c );

/*
Recebe o ponteiro para uma struct do tipo Circle e retorna o seu atributo "r" (raio)
*/
double getCircleRadius( Circle *c );

/*
Recebe o ponteiro para uma struct do tipo Circle e retorna o seu atributo "x"
*/
double getCircleX( Circle *c );

/*
Recebe o ponteiro para uma struct do tipo Circle e retorna o seu atributo "y"
*/
double getCircleY( Circle *c );

/*
Recebe o ponteiro para uma struct do tipo Circle e retorna o seu atributo "fill" (preenchimento)
*/
char *getCircleFill( Circle *c );

#endif
