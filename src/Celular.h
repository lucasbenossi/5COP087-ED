#ifndef CELULAR_H
#define CELULAR_H
#include "Endereco.h"

typedef struct _celular Celular;

Celular *createCelular( char *numero, char *cpf );

int destroyCelular( Celular *celular );
void destroyCelularVoid( void *celular );

void celularConecta( Celular *celular, char *torreId, Endereco *endereco );
Endereco *celularDesconecta( Celular *celular );

char *getCelularNumero( Celular *celular );
char *getCelularCpf( Celular *celular );
char *getCelularTorreId( Celular *celular );
Endereco *getCelularEndereco( Celular *celular );

#endif
