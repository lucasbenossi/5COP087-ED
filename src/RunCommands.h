#ifndef RUNCOMMANDS_H
#define RUNCOMMANDS_H
#include "LinkedList.h"
#include "Cidade.h"
#include "Args.h"

/*
Processa os comandos fornecidos nos arquivos de entrada
*args = Instancia da struct com os argumentos recebidos na linha de comando
*/
int runCommands( Args *args );

/*
Processa o comando "p" (imprimir todos os elementos criados,
junto com seus atributos)
*l = lista ligada
*c = instancia de Cidade
*/
void procP( List *objs, Cidade *cidade );

/*
Processa o comando "z" (imprimir fill e stroke padrões definidos na instancia
de Cidade)
*c = instancia de Cidade
*/
void procZ( Cidade *cidade );

#endif
