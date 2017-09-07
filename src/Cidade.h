#ifndef CIDADE_H
#define CIDADE_H
#include "LinkedList.h"

/*
Define uma instancia de Cidade.
Possui os seguintes atributos:
  - quadras = Lista de quadras da cidade (tipo List)
  - quadrasFill = Preenchimento das quadras (string)
  - quadrasStroke = Cor da borda das quadras (string)
  - hidrantes = Lista de hidrantes (tipo List)
  - hidrantesFill = Preenchimento dos hidrantes (string)
  - hidrantesStroke = Cor da borda dos hidrantes (string)
  - semaforos = Lista de semaforos (tipo List)
  - semaforosFill = Preenchimento dos semaforos (string)
  - semaforosStroke = Cor da borda dos semaforos (string)
  - torres = Lista de torres de radio (tipo List)
  - torresFill = Preenchimento das torres de radio (string)
  - torresStroke = Cor da borda das torres de radio (string)
*/
typedef void Cidade;

/*
Aloca a memoria para uma instancia de Cidade
*/
Cidade *createCidade();

/*
Desaloca memoria para uma instancia de Cidade
*/
void destroyCidade(Cidade *c);

/*
Recebe o ponteiro para uma instancia de Cidade e retorna seu parametro "quadras"
(getCidadeQuadras(), tipo List), "quadrasFill" (getCidadeQuadrasFill(), string),
ou "quadrasStroke" (getCidadeQuadrasStroke(), string).
*/
List *getCidadeQuadras(Cidade *c);
char *getCidadeQuadrasFill(Cidade *c);
char *getCidadeQuadrasStroke(Cidade *c);

/*
Recebe o ponteiro para uma instancia de Cidade e retorna seu parametro "hidrantes"
(getCidadeHidrantes(), tipo List), "hidrantesFill" (getCidadeHidrantesFill(), string),
ou "hidrantesStroke" (getCidadeHidrantesStroke(), string).
*/
List *getCidadeHidrantes(Cidade *c);
char *getCidadeHidrantesFill(Cidade *c);
char *getCidadeHidrantesStroke(Cidade *c);

/*
Recebe o ponteiro para uma instancia de Cidade e retorna seu parametro "semaforos"
(getCidadeSemaforos(), tipo List), "semaforosFill" (getCidadeSemaforosFill(), string),
ou "semaforosStroke" (getCidadeSemaforosStroke(), string).
*/
List *getCidadeSemaforos(Cidade *c);
char *getCidadeSemaforosFill(Cidade *c);
char *getCidadeSemaforosStroke(Cidade *c);

/*
Recebe o ponteiro para uma instancia de Cidade e retorna seu parametro "torres"
(getCidadeTorres(), tipo List), "torresFill" (getCidadeTorresFill(), string),
ou "torresStroke" (getCidadeTorresStroke(), string).
*/
List *getCidadeTorres(Cidade *c);
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
