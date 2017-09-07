#ifndef COMMANDST3_H
#define COMMANDST3_H
#include "Cidade.h"
#include "Resumo.h"
#include <stdio.h>

/*
Variaveis usadas nas funcoes definidas por esse arquivo:
*l = ponteiro para a instancia da lista ligada usada
*c = ponteiro para a instancia de Cidade usada pela função
*line = string para a linha de comando sendo processada
*file = string com o nome do arquivo de saida
*fixedDir = string com o diretorio do arquivo de saida, ja corrigido pela funcao
    fixDir(), definida em "ProcString.h"
*/

/*
Processa os comandos
	"q" (inserir quadra)
	"h" (inserir hidrantes)
	"s" (inserir semaforo)
	"t" (inserir torre)
*/
void commandCidadeInsert( char *line, Cidade *c, Resumo *res );

/*
Processa os comandos:
	"cq" (alterar cores de preenchimento e borda para quadras)
	"ch" (alterar cores de preenchimento e borda para hidrantes)
	"cs" (alterar cores de preenchimento e borda para semaforos)
	"ct" (alterar cores de preenchimento e borda para radios-base)
*/
void commandCidadeColors( char *line, Cidade *c );

/*
Processa os comandos:
	"dq" (remove quadras que estão dentro do retangulo)
	"dh" (remove hidrantes que estão dentro do retangulo)
	"ds" (remove semaforos que estão dentro do retangulo)
	"dt" (remove torres que estão dentro do retangulo)
*/
void commandCidadeDeleteRect( char *line, Cidade *c, FILE *outFileTxt, Resumo *res );

/*
Processa os comandos:
	"Dq" (remove quadras que estão dentro do circulo)
	"Dh" (remove hidrantes que estão dentro do circulo)
	"Ds" (remove semaforos que estão dentro do circulo)
	"Dt" (remove torres que estão dentro do circulo)
*/
void commandCidadeDeleteCircle( char *line, Cidade *c, FILE *outFileTxt, Resumo *res );

/*
Processa o comando crd? (procurar por elementos com cep ou id)
id = id ou cep a ser procurado
*/
void commandSearchIdCep( char *line, Cidade *c, FILE *outFileTxt );

#endif
