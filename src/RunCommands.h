#ifndef RUNCOMMANDS_H
#define RUNCOMMANDS_H
#include "LinkedList.h"

/*
*pathFileExt = caminho do arquivo de entrada, fornecido pelo argumento "-f"
*dir = diretorio de saida, fornecido em "-o"
num = numero maximo de objetos, fornecido em "-n"
*/
int runCommands( char *pathFileExt, char *dir, int num );

/*
Processa o comando "c" (criar circulo)
*line = string com a linha recebida
**objListHead = cabecalho da lista ligada
**objListTail = cauda da lista ligada
*/
void procC( char *line, List *l );

/*
Processa o comando "r" (criar retangulo)
*line = string com a linha recebida
**objListHead = cabecalho da lista ligada
**objListTail = cauda da lista ligada
*/
void procR( char *line, List *l );

/*
Processa o comando "p" (imprimir todos os elementos criados,
junto com seus atributos)
*nome = cabecalho da lista ligada
*/
void procP( List *l );

#endif
