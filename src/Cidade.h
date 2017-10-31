#ifndef CIDADE_H
#define CIDADE_H
#include "LinkedList.h"
#include "QuadTree.h"

/*
Define uma instancia de Cidade.
Possui os seguintes atributos:
  - quadras = Lista de quadras da cidade (tipo List)
  - quadrasQT = QuadTree com as quadras da cidade (tipo QuadTree)
  - quadrasFill = Preenchimento das quadras (string)
  - quadrasStroke = Cor da borda das quadras (string)
  - hidrantes = Lista de hidrantes (tipo List)
  - hidrantesQT = QuadTree com os hidrantes (tipo QuadTree)
  - hidrantesFill = Preenchimento dos hidrantes (string)
  - hidrantesStroke = Cor da borda dos hidrantes (string)
  - semaforos = Lista de semaforos (tipo List)
  - semaforosQT = QuadTree com os semaforos (tipo QuadTree)
  - semaforosFill = Preenchimento dos semaforos (string)
  - semaforosStroke = Cor da borda dos semaforos (string)
  - torres = Lista de torres de radio (tipo List)
  - torresQT = QuadTree com as torres de radio (tipo QuadTree)
  - torresFill = Preenchimento das torres de radio (string)
  - torresStroke = Cor da borda das torres de radio (string)
*/
typedef struct _cidade Cidade;

/*
Aloca a memoria para uma instancia de Cidade
*/
Cidade *createCidade();

/*
Desaloca memoria para uma instancia de Cidade
*/
void destroyCidade(Cidade *c);

/*
Para cada lista de elementos da instancia de Cidade, cria uma QuadTree com esses
elementos, usando a técnica de inserção na QuadTree definida por "method".
Valores de method:
 - 0 = não inserir na QuadTree e deixar na lista.
 - 1 = inserir usando envoltório convexo e ordenação.
 - 2 = inserir usando envoltório convexo.
 - 3 = inserir na ordem que foi inserido na lista.
*/
void cidadeListToQuadTree(Cidade *c, int method);

/*
Retorna parametros para as quadras.
*/
List *getCidadeQuadras(Cidade *c);
QuadTree *getCidadeQuadrasQT(Cidade *c);
char *getCidadeQuadrasFill(Cidade *c);
char *getCidadeQuadrasStroke(Cidade *c);

/*
Retorna parametros para os hidrantes.
*/
List *getCidadeHidrantes(Cidade *c);
QuadTree *getCidadeHidrantesQT(Cidade *c);
char *getCidadeHidrantesFill(Cidade *c);
char *getCidadeHidrantesStroke(Cidade *c);

/*
Retorna parametros para os semaforos.
*/
List *getCidadeSemaforos(Cidade *c);
QuadTree *getCidadeSemaforosQT(Cidade *c);
char *getCidadeSemaforosFill(Cidade *c);
char *getCidadeSemaforosStroke(Cidade *c);

/*
Retorna parametros para as torres.
*/
List *getCidadeTorres(Cidade *c);
QuadTree *getCidadeTorresQT(Cidade *c);
char *getCidadeTorresFill(Cidade *c);
char *getCidadeTorresStroke(Cidade *c);

/*
Recebe o ponteiro para uma instancia de Cidade, e altera os parametros "quadrasFill"
e "quadrasStroke".
  - fill = String a ser definida no parametro quadrasFill
  - stroke = String a ser definida no parametro quadrasStroke
*/
void setCidadeQuadrasColors(Cidade *c, char *fill, char *stroke);

/*
Recebe o ponteiro para uma instancia de Cidade, e altera os parametros "hidrantesFill"
e "hidrantesStroke".
  - fill = String a ser definida no parametro hidrantesFill
  - stroke = String a ser definida no parametro hidrantesStroke
*/
void setCidadeHidrantesColors(Cidade *c, char *fill, char *stroke);

/*
Recebe o ponteiro para uma instancia de Cidade, e altera os parametros "semaforosFill"
e "semaforosStroke".
  - fill = String a ser definida no parametro semaforosFill
  - stroke = String a ser definida no parametro semaforosStroke
*/
void setCidadeSemaforosColors(Cidade *c, char *fill, char *stroke);

/*
Recebe o ponteiro para uma instancia de Cidade, e altera os parametros "torresFill"
e "torresStroke".
  - fill = String a ser definida no parametro torresFill
  - stroke = String a ser definida no parametro torresStroke
*/
void setCidadeTorresColors(Cidade *c, char *fill, char *stroke);

#endif
