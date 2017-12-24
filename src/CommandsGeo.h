#ifndef COMMANDSGEO_H
#define COMMANDSGEO_H
#include "Cidade.h"
#include "Resumo.h"

/*
Processa os comandos
	"q" (inserir quadra)
	"h" (inserir hidrantes)
	"s" (inserir semaforo)
	"t" (inserir torre)
*/
void commandCidadeInsert( char *line, Cidade *c, Resumo *res, char *argR );

/*
Processa os comandos:
	"cq" (alterar cores de preenchimento e borda para quadras)
	"ch" (alterar cores de preenchimento e borda para hidrantes)
	"cs" (alterar cores de preenchimento e borda para semaforos)
	"ct" (alterar cores de preenchimento e borda para radios-base)
*/
void commandCidadeColors( char *line, Cidade *c );

/*
Processa os comandos hI, sI, tI.
*/
void commandInsertInfo( char *line, Cidade *c );

/*
Processa os comandos su e um do arquivo .geo.
*/
void commandSetTorreOwner( char *line, Cidade *c );

#endif
