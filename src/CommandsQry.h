#ifndef COMMANDSQRY_H
#define COMMANDSQRY_H
#include "Cidade.h"
#include "Resumo.h"
#include "Tokens.h"
#include <stdio.h>

/*
Processa os comandos:
	"dq" (remove quadras que estão dentro do retangulo)
	"dh" (remove hidrantes que estão dentro do retangulo)
	"ds" (remove semaforos que estão dentro do retangulo)
	"dt" (remove torres que estão dentro do retangulo)
	"Dq" (remove quadras que estão dentro do circulo)
	"Dh" (remove hidrantes que estão dentro do circulo)
	"Ds" (remove semaforos que estão dentro do circulo)
	"Dt" (remove torres que estão dentro do circulo)
*/
void commandCidadeDelete( char *line, Cidade *c, FILE *outFileTxt, Resumo *res );

/*
Processa o comando crd? (procurar por elementos com cep ou id)
id = id ou cep a ser procurado
*/
void commandSearchIdCep( char *line, Cidade *c, FILE *outFileTxt );

/*
Processa o comando "pc?".
*/
void commandPoligonoCobertura( char *line, Cidade *cidade, char *nameFiles, char *outDir );

/*
Processa o comando "ac?".
*/
void commandPoligonoCoberturaArea( char *line, Cidade *cidade, FILE *outFileTxt );

void commandMoveCelular( char *line, Cidade *cidade, FILE *outFileTxt );

void commandConectaCelular( char *line, Cidade *cidade, FILE *outFileTxt );

void commandLimpaRegion( char *line, Cidade *cidade, FILE *outFileTxt );

void commandMatarPessoa( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaMoradoresQuadra( char *line, int commandId, Cidade *cidade, FILE *outFileTxt );

void commandDumpDadosMorador( char *line, Cidade *cidade, FILE *outFileTxt );

void commandDumpDadosEstabComercial( char *line, Cidade *cidade, FILE *outFileTxt );

void commandDumpMoradoresSexoCodtRegion( char *line, Cidade *cidade, FILE *outFileTxt );

void commandDumpConexoesTorre( char *line, Cidade *cidade, FILE *outFileTxt );

void commandTorreCelularConectado( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaClientesOperadora( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaConexoesTorresRegion( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaEstabComerciaisQuadra( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaEstabComerciaisTipoRegion( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaTiposCep( char *line, Cidade *cidade, FILE *outFileTxt );

void commandListaTiposRegion( char *line, Cidade *cidade, FILE *outFileTxt );

void commandDadosUsuarioLinhaMovel( char *line, int commandId, Cidade *cidade, FILE *outFileTxt );

void commandRegistrador( char *line, int commandId, Cidade *cidade, FILE *outFileTxt );

void commandDijkstra( char *line, Tokens *tokens, Cidade *cidade, FILE *outFileTxt, char *nameFileGeo, char *outDir );

#endif
