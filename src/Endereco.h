#ifndef ENDERECO_H
#define ENDERECO_H
#include "Point.h"
#include "Quadra.h"

typedef struct _endereco Endereco;

Endereco *createEndereco( char *cep, char face, int num, char *compl );

void destroyEndereco( Endereco *endereco );

char *getEnderecoCep( Endereco *endereco );
char getEnderecoFace( Endereco *endereco );
int getEnderecoNum( Endereco *endereco );
char *getEnderecoCompl( Endereco *endereco );

Point *getEnderecoCoords( Endereco *endereco, Quadra *quadra );

int checkFace( char face );

#endif
