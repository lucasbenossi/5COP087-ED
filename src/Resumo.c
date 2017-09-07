#include "Resumo.h"
#include <stdlib.h>
#include <stdio.h>

struct _resumo{
    int ins;
    int cpi;
    int del;
    int cpd;
};
typedef struct _resumo ResumoStr;

Resumo *createResumo(){
    ResumoStr *res;
    res = malloc( sizeof( ResumoStr ) );
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
    (((ResumoStr*)res)->ins)++;
}

void incCpi(Resumo *res){
    (((ResumoStr*)res)->cpi)++;
}


void incDel(Resumo *res){
    (((ResumoStr*)res)->del)++;
}


void incCpd(Resumo *res){
    (((ResumoStr*)res)->cpd)++;
}


void printResumo( Resumo *res, char *fileGeo, FILE *txt ){
    ResumoStr *res0;
    res0 = res;
    fprintf( txt, "%s\t#%d\t#%d\t#%d\t#%d\n", fileGeo, res0->ins, res0->cpi, res0->del, res0->cpd );
}
