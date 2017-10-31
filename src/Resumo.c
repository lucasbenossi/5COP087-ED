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
    (res->ins)++;
}

void incCpi(Resumo *res){
    (res->cpi)++;
}


void incDel(Resumo *res){
    (res->del)++;
}


void incCpd(Resumo *res){
    (res->cpd)++;
}


void printResumo( Resumo *res, char *fileGeo, FILE *txt ){
    fprintf( txt, "%s\t#%d\t#%d\t#%d\t#%d\n", fileGeo, res->ins, res->cpi, res->del, res->cpd );
}
