#include "Celular.h"
#include "Endereco.h"
#include "String.h"
#include <stdlib.h>

struct _celular{
	char *numero;
	char *cpf;
	Endereco *endereco;
	char *torreId;
};

Celular *createCelular( char *numero, char *cpf ){
	Celular *celular;

	celular = malloc(sizeof(Celular));
	celular->numero = createString(numero);
	celular->cpf = createString(cpf);
	celular->endereco = NULL;
	celular->torreId = NULL;

	return celular;
}

int destroyCelular( Celular *celular ){
	destroyString(celular->numero);
	destroyString(celular->cpf);
	if(celular->endereco){
		destroyEndereco(celular->endereco);
	}
	destroyString(celular->torreId);
	free(celular);
	return 0;
}

void destroyCelularVoid( void *celular ){
	destroyCelular(celular);
}

void celularConecta( Celular *celular, char *torreId, Endereco *endereco ){
	celular->torreId = createString(torreId);
	celular->endereco = endereco;
}

Endereco *celularDesconecta( Celular *celular ){
	Endereco *endereco = celular->endereco;

	celular->endereco = NULL;
	destroyString(celular->torreId);
	celular->torreId = NULL;

	return endereco;
}

char *getCelularNumero( Celular *celular ){
	return celular->numero;
}

char *getCelularCpf( Celular *celular ){
	return celular->cpf;
}

char *getCelularTorreId( Celular *celular ){
	return celular->torreId;
}

Endereco *getCelularEndereco( Celular *celular ){
	return celular->endereco;
}
