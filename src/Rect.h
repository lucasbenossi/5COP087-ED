#ifndef RECT_H
#define RECT_H

/*
Define um retangulo num plano 2D.
Possui como atributos valores de id, largura, altura, coordenada x e y (todos double) e
cor de preenchimento (string).
*/
typedef struct _rect Rect;

/*
Aloca memória para uma instancia de Rect e escreve os valores id, largura, altura,
x, y e fill nos seus atributos, retorna o ponteiro para o espaco de memoria alocado.
*/
Rect *createRect( int id, double width, double height, double x, double y, char *fill );

/*
Desaloca a memória de uma instancia de Rect.
*/
void destroyRect( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu id
*/
int getRectId( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu atributo width (largura)
*/
double getRectWidth( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu atributo height (altura)
*/
double getRectHeight( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu atributo X
*/
double getRectX( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu atributo Y
*/
double getRectY( Rect *r );

/*
Recebe o ponteiro para uma instancia de Rect e retorna seu atributo fill (preenchimento)
*/
char *getRectFill( Rect *r );

#endif
