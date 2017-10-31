#ifndef CREATESVG_H
#define CREATESVG_H
#include <stdio.h>
#include "LinkedList.h"
#include "Cidade.h"

/*
Cria o arquivo <nome>.svg
*/
void createSvg( List *l, Cidade *c, char *file, char *fixedDir, int insert, int argT, int noT2 );

#endif
