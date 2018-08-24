#include "Rua.h"
#include "String.h"
#include <stdlib.h>

struct _rua{
	char *nome;
	char *ldir;
	char *lesq;
	double cmp;
	double vm;
};

Rua *createRua( char *nome, char *ldir, char *lesq, double cmp, double vm ){
	Rua *rua = malloc(sizeof(Rua));
	rua->nome = createString(nome);
	rua->ldir = createString(ldir);
	rua->lesq = createString(lesq);
	rua->cmp = cmp;
	rua->vm = vm;
	return rua;
}

void destroyRua( Rua *rua ){
	destroyString(rua->nome);
	destroyString(rua->ldir);
	destroyString(rua->lesq);
	free(rua);
}

void destroyRuaVoid( void *rua ){
	destroyRua(rua);
}

char *getRuaNome( Rua *rua ){
	return rua->nome;
}

char *getRuaLdir( Rua *rua ){
	return rua->ldir;
}

char *getRuaLesq( Rua *rua ){
	return rua->lesq;
}

double getRuaCmp( Rua *rua ){
	return rua->cmp;
}

double getRuaVm( Rua *rua ){
	return rua->vm;
}

double getRuaTempo( Rua *rua ){
	if(rua->cmp == 0){
		return 0;
	}
	if(rua->vm == 0){
		return -1;
	}
	return rua->cmp / rua->vm;
}
