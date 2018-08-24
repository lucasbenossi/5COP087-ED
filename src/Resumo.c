#include "Resumo.h"
#include <stdlib.h>
#include <stdio.h>

struct _resumo{
	int ins;
	int cpi;
	int del;
	int cpd;
};

Resumo *createResumo(){
	Resumo *res;
	res = malloc( sizeof( Resumo ) );
	res->ins = 0;
	res->cpi = 0;
	res->del = 0;
	res->cpd = 0;
	return res;
}

void destroyResumo(Resumo *res){
	free(res);
}

void incIns(Resumo *res){
	if(res) (res->ins)++;
}

void incCpi(Resumo *res){
	if(res) (res->cpi)++;
}

void incDel(Resumo *res){
	if(res) (res->del)++;
}

void incCpd(Resumo *res){
	if(res) (res->cpd)++;
}

void setResumoIns(Resumo *res, int value){
	if(res) res->ins = value;
}

void setResumoCpi(Resumo *res, int value){
	if(res) res->cpi = value;
}

void setResumoDel(Resumo *res, int value){
	if(res) res->del = value;
}

void setResumoCpd(Resumo *res, int value){
	if(res) res->cpd = value;
}

void printResumo( Resumo *res, char *fileGeo, FILE *txt ){
	fprintf( txt, "%s\t#%d\t#%d\t#%d\t#%d\n", fileGeo, res->ins, res->cpi, res->del, res->cpd );
}
