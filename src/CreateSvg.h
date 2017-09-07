#ifndef CREATESVG_H
#define CREATESVG_H
#include "LinkedList.h"
#include "Cidade.h"

/*
Cria o arquivo <nome>.svg
*l = ponteiro para a instancia da lista ligada usada
*file = string com o nome do arquivo de saida
*fixedDir = string com o diretorio do arquivo de saida, ja corrigido pela funcao
    fixDir(), definida em "ProcString.h"
*/
void createSvg( List *l, Cidade *c, char *file, char *fixedDir );

#endif
