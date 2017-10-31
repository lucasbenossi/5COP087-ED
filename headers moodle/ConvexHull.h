#ifndef CONVEXHULL_H
#define CONVEXHULL_H
#include "Stack.h"
#include "Array.h"

/*
Recebe uma instancia de Array com pontos de um plano cartesiano, procura o
ponto com o menor valor da coordenada Y e ordena os outros pontos com base
no angulo com o eixo X, usando este ponto como origem.
*/
int sortAngle( Array *array );

/*
Recebe uma instancia de Array com pontos de um plano cartesiano ja ordenado por
sortAngle(), procura o valor do maior angulo, se existem mais de um ponto com
esse valor de angulo, ordena esses pontos de forma que o ponto mais distante
venha primeiro.
*/
int sortAngleCollinear( Array *array );

/*
Recebe uma instancia de Array com pontos de um plano cartesiano, gera o envoltório
convexo do conjunto de pontos, empilha esses pontos numa instancia de Stack.
*/
void grahanScan( Array *array, Stack *stack );

/*
Recebe uma instancia de Array com pontos de um plano cartesiano, gera o envoltório
convexo do conjunto de pontos considerando os pontos colineares como fazendo parte
do envoltório, empilha esses pontos numa instancia de Stack.
*/
void grahanScanCollinear( Array *array, Stack *stack );

#endif
