#ifndef OPERADORA_H
#define OPERADORA_H
#include "HashTable.h"
#include "QuadTree.h"
#include "LinkedList.h"
#include "Object.h"
#include "Pessoa.h"
#include "Celular.h"
#include "Endereco.h"

typedef struct _operadora Operadora;

Operadora *createOperadora( char *nome, int method );
void destroyOperadora( Operadora *operadora );

void operadoraFillDataStructures( Operadora *operadora );

void operadoraInsertTorre( Operadora *operadora, Object *torre );
void operadoraRemoveTorresRegion( Operadora *operadora, Object *region );

int operadoraIsPessoaCliente( Operadora *operadora, Pessoa *pessoa );

void operadoraInsertCliente( Operadora *operadora, Pessoa *pessoa, Celular *celular );
void operadoraRemoveCliente( Operadora *operadora, Pessoa *pessoa, Celular *celular );

void operadoraConectaCelular( Operadora *operadora, Celular *celular, Quadra *quadra, Endereco *endereco );
Endereco *operadoraDesconectaCelular( Operadora *operadora, Celular *celular );

void operadoraDesconectaCelularesQuadra( Operadora *operadora, Quadra *quadra );

List *searchOperadoraTorresRegion( Operadora *operadora, Object *region );
Object *searchOperadoraTorreId( Operadora *operadora, char *torreId );
Pessoa *searchOperadoraClienteCpf( Operadora *operadora, char *cpf );
Celular *searchOperadoraCelularNum( Operadora *operadora, char *num );
Celular *searchOperadoraCelularCpf( Operadora *operadora, char *cpf );
HashTable *searchOperadoraConexoesTorreId( Operadora *operadora, char *torreId );
HashTable *searchOperadoraConexoesQuadraCep( Operadora *operadora, char *quadraCep );

char *getOperadoraNome( Operadora *operadora );
HashTable *getOperadoraTorresHT( Operadora *operadora );
QuadTree *getOperadoraTorresQT( Operadora *operadora );
HashTable *getOperadoraClientes( Operadora *operadora );
HashTable *getOperadoraCelularesNum( Operadora *operadora );
HashTable *getOperadoraCelularesCpf( Operadora *operadora );
HashTable *getOperadoraConexoesTorreId( Operadora *operadora );
HashTable *getOperadoraConexoesQuadraCep( Operadora *operadora );

#endif
