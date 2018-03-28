#include "EstabComercial.h"
#include "String.h"
#include "Endereco.h"
#include <stdlib.h>

struct _estabcomercial{
	char *cnpj;
	char *nome;
	char *codt;
	Endereco *endereco;
};

EstabComercial *createEstabComercial(char *cnpj, char *nome, char *codt, char *cep, char face, int num){
	EstabComercial *estab;
	estab = malloc(sizeof(EstabComercial));
	estab->cnpj = createString(cnpj);
	estab->nome = createString(nome);
	estab->codt = createString(codt);
	estab->endereco = createEndereco( cep, face, num, "" );
	return estab;
}

void destroyEstabComercial( EstabComercial *estab ){
	destroyString(estab->cnpj);
	destroyString(estab->nome);
	destroyString(estab->codt);
	destroyEndereco(estab->endereco);
	free(estab);
}

void destroyEstabComercialVoid( void *estab ){
	destroyEstabComercial(estab);
}

char *getEstabComercialCNPJ( EstabComercial *estab ){
	return estab->cnpj;
}

char *getEstabComercialNome( EstabComercial *estab ){
	return estab->nome;
}

char *getEstabComercialCodt( EstabComercial *estab ){
	return estab->codt;
}

Endereco *getEstabComercialEndereco( EstabComercial *estab ){
	return estab->endereco;
}

char *getEstabComercialCep( EstabComercial *estab ){
	return getEnderecoCep(estab->endereco);
}

char getEstabComercialFace( EstabComercial *estab ){
	return getEnderecoFace(estab->endereco);
}

int getEstabComercialNum( EstabComercial *estab ){
	return getEnderecoNum(estab->endereco);
}
