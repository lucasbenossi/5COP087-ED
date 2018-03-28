#ifndef RESUMO_H
#define RESUMO_H
#include <stdio.h>

/*
- Objeto que define uma instancia de Resumo.
- Esse objeto guarda as informações que depois serão salvas no arquivo resumo.txt,
  quando usados os argumentos -acc ou -acc0.
- Possui os atributos:
	- ins = Quadras inseridas
	- cpi = Comparações para inserir uma quadras
	- del = Quadras deletedas
	- cpd = Comparações para deletar uma quadra
*/
typedef struct _resumo Resumo;

/*
Aloca memória para uma instancia de Resumo
*/
Resumo *createResumo();

/*
Desaloca memória de uma instancia de Resumo
*/
void destroyResumo(Resumo *res);

/*
Recebe uma instancia de Resumo e incrementa o atributo correspondente em uma unidade.
*/
void incIns(Resumo *res);
void incCpi(Resumo *res);
void incDel(Resumo *res);
void incCpd(Resumo *res);

/*
Recebe uma instancia de Resumo e define o atributo correspondente.
*/
void setResumoIns(Resumo *res, int value);
void setResumoCpi(Resumo *res, int value);
void setResumoDel(Resumo *res, int value);
void setResumoCpd(Resumo *res, int value);

/*
Imprime as informações no arquivo resumo.txt
*/
void printResumo( Resumo *res, char *fileGeo, FILE *txt );

#endif
