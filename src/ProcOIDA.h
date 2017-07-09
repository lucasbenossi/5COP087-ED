#ifndef PROCA_H
#define PROCA_H
#include "LinkedList.h"

/*
Variaveis usadas nas funcoes definidas por esse arquivo:
*node = ponteiro para o primeiro no da lista ligada
**objListHead = ponteiro para o primeiro elemento da lista ligada
**objListTail = ponteiro para o ultimo elemento da lista ligada
*line = string para a linha de comando sendo processada
*file = string com o nome do arquivo de saida
*fixedDir = string com o diretorio do arquivo de saida, ja corrigido pela funcao
    fixDir(), definida em "ProcString.h"
*/

/*
Processa o comando "a" (cria o arquivo <nome>-<sufixo>.svg)
*/
void procA( List *l, char *line, char *file, char *fixedDir );

/*
Processa o comando "o" (verifica sobreposição de duas formas geométricas)
*/
void procO( char *line, List *l, char *file, char *fixedDir );

/*
Processa o comando "i" (verifica se o ponto está dentro da forma geométrica)
*/
void procI( List *l, char *line, char *file, char *fixedDir );

/*
Processa o comando "d" (calcula a distancia dos centros de massa de
duas formas geométricas)
*/
void procD( List *l, char *line, char *file, char *fixedDir );

/*
Escreve uma tag svg do tipo <circle ...> na stream em "*svg"
Esta funcao e usada pelo comando "a" para escrever a tag <circle ...> no
arquivo "<nome>-<sufixo>.svg"
Os atributos "i", "r", "x", "y", e "*color" fazem parte da struct Circle, e estao
definidas em Circle.h
*/
void writeTag( int i, double r, double x, double y, char *color, FILE *svg );

/*
Usada pelos comandos "o", "i" e "d" para escrever o resultado do processo
no arquivo "<nome>.txt"
*string = string a ser escrita no arquivo <nome>.txt
*/
void createTxt( char *line, char *file, char *fixedDir, char *string );

/*
Usada pelos comandos "o", "i" e "d" para escrever uma mensagem de erro no
arquivo "<nome>.txt", caso não encontre um ou dois IDs fornecidos ao comando
*/
void createTxtError( char *line, char *file, char *fixedDir, int qtd, int id1, int id2 );

#endif
