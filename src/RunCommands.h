#ifndef RUNCOMMANDS_H
#define RUNCOMMANDS_H
#include "Args.h"
#include <stdio.h>

/*
Prepara o ambiente de execução, ou seja, abre os arquivos.
*args = Instancia da struct com os argumentos recebidos na linha de comando
*/
int prepareEnvironment( Args *args );

/*
Executa os comandos fornecidos nos arquivos de entrada.
*/
void runCommands( Args *args, char *outDir, char *nameFileGeo, char *nameFiles, FILE *inFileGeo, FILE *inFileQry, FILE *outFileTxt, FILE *outResumoTxt );

#endif
