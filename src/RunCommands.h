#ifndef RUNCOMMANDS_H
#define RUNCOMMANDS_H
#include "Args.h"
#include "LinkedList.h"
#include "Cidade.h"
#include "Resumo.h"
#include <stdio.h>

/*
Define uma estrutura com ponteiros para algumas streams e strings que carregam
parametros sobre arquivos.
*/
typedef struct _fileStuff FileStuff;

/*
Prepara o ambiente de execução, ou seja, abre os arquivos.
*args = Instancia da struct com os argumentos recebidos na linha de comando
*/
int prepareEnvironment( Args *args );

/*
Executa os comandos fornecidos nos arquivos de entrada.
*/
void runCommands( Args *args, FileStuff stuff );

/*
Executa os comandos fornecidos no arquivo .geo.
*/
void runCommandsGeo( List *objs, Cidade *cidade, Args *args, FileStuff stuff, Resumo *res );

/*
Executa os comandos fornecidos no arquivo .qry.
*/
void runCommandsQry( Cidade *cidade, FileStuff stuff, Resumo *res );

/*
Executa os comandos fornecidos no arquivo .ec.
*/
void runCommandsEc( Cidade *cidade, FileStuff stuff );

/*
Executa os comandos fornecidos no arquivo .pm.
*/
void runCommandsPm( Cidade *cidade, FileStuff stuff );

/*
Executa os comandos fornecidos no arquivo .tm.
*/
void runCommandsTm( Cidade *cidade, FileStuff stuff );

void runCommandsVia( Cidade *cidade, FileStuff stuff );

#endif
