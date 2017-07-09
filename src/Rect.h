#ifndef RECT_H
#define RECT_H

/*
Struct para o TAD Rect
i = id
w = largura
h = altura
x, y = coordenadas do centro do retangulo
*fill = string com a cor
*/
struct _rect {
    int i;
    double w;
    double h;
    double x;
    double y;
    char *fill;
};
typedef struct _rect Rect;

/*
Na lista ligada, é definida como de tipo 2, quando adicionada pelo comando "r" e
como tipo 3 quando adicionada pelo comando "o"
*/

/*
Aloca memória para uma struct do tipo Rect e escreve os valores i, w, h, x, y e
fill nos seus atributos, retorna o ponteiro para o espaco de memoria alocado
*/
Rect *createRect( int i, double w, double h, double x, double y, char *fill );

/*
Desaloca a memória de uma struct do tipo Rect.
*/
void destroyRect( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "i" (id)
*/
int getRectId( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "w" (largura)
*/
double getRectWidth( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "h" (altura)
*/
double getRectHeight( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "x"
*/
double getRectX( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "y"
*/
double getRectY( Rect *r );

/*
Recebe o ponteiro para uma struct do tipo Rect e retorna o seu atributo "fill" (preenchimento)
*/
char *getRectFill( Rect *r );

#endif
