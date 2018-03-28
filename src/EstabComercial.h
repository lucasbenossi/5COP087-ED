#ifndef ESTABCOMERCIAL_H
#define ESTABCOMERCIAL_H
#include "Endereco.h"

typedef struct _estabcomercial EstabComercial;

EstabComercial *createEstabComercial(char *cnpj, char *nome, char *codt, char *cep, char face, int num);

void destroyEstabComercial( EstabComercial *estab );
void destroyEstabComercialVoid( void *estab );

char *getEstabComercialCNPJ( EstabComercial *estab );
char *getEstabComercialNome( EstabComercial *estab );
char *getEstabComercialCodt( EstabComercial *estab );
Endereco *getEstabComercialEndereco( EstabComercial *estab );
char *getEstabComercialCep( EstabComercial *estab );
char getEstabComercialFace( EstabComercial *estab );
int getEstabComercialNum( EstabComercial *estab );

#endif
