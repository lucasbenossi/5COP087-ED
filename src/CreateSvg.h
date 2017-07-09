#ifndef CREATESVG_H
#define CREATESVG_H
#include "LinkedList.h"

/*
Cria o arquivo <nome>.svg
*node = ponteiro para o primeiro no da lista ligada
*file = string com o nome do arquivo de saida
*fixedDir = string com o diretorio do arquivo de saida, ja corrigido pela funcao
    fixDir(), definida em "ProcString.h"
*/
void createSvg( List *l, char *file, char *dir );

#endif
