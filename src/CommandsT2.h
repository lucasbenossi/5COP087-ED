#ifndef COMMANDST2_H
#define COMMANDST2_H
#include "LinkedList.h"
#include <stdio.h>

/*
Variaveis usadas nas funcoes definidas por esse arquivo:
*l = ponteiro para a instancia da lista ligada usada
*line = string para a linha de comando sendo processada
*file = string com o nome do arquivo de saida
*fixedDir = string com o diretorio do arquivo de saida, ja corrigido pela funcao
    fixDir(), definida em "ProcString.h"
*/

/*
Processa o comando "c" (criar circulo)
*/
void procC( char *line, List *l );

/*
Processa o comando "r" (criar retangulo)
*/
void procR( char *line, List *l );

/*
Processa o comando "a" (cria o arquivo <nome>-<sufixo>.svg)
*/
void procA( char *line, List *l, char *file, char *fixedDir );

/*
Escreve uma tag svg do tipo <circle ...> na stream em "*svg"
Esta funcao e usada pelo comando "a" para escrever a tag <circle ...> no
arquivo "<nome>-<sufixo>.svg"
Os atributos "i", "x" e "y"fazem parte da struct Circle, e estao
definidas em Circle.h
*/
void writeTag( Circle *c, int i, double x, double y, FILE *svg );

/*
Processa o comando "o" (verifica sobreposição de duas formas geométricas)
*/
void procO( char *line, List *l, FILE *outFileTxt );

/*
Processa o comando "i" (verifica se o ponto está dentro da forma geométrica)
*/
void procI( char *line, List *l, FILE *outFileTxt );

/*
Processa o comando "d" (calcula a distancia dos centros de massa de
duas formas geométricas)
*/
void procD( char *line, List *l, FILE *outFileTxt );

#endif
