#include <stdlib.h>
#include "Quadra.h"
#include "String.h"
#include "HashTable.h"
#include "Pessoa.h"

/* ========================================================================== */

struct _quadra {
	double x;
	double y;
	double width;
	double height;
	char *cep;
	char *fill;
	char *stroke;
	HashTable *estabComerciais; /* codt X ( cnpj X EstabComercial ) */
	HashTable *moradores; /* cpf X Pessoa */
};

Quadra *createQuadra( double x, double y, double width, double height, char *cep, char *fill, char *stroke ){
	Quadra *q;
	q = malloc(sizeof(Quadra));
	q->x = x;
	q->y = y;
	q->width = width;
	q->height = height;
	q->cep = createString(cep);
	q->fill = createString(fill);
	q->stroke = createString(stroke);
	q->estabComerciais = createHashTable(HT_SIZE_SMALL);
	q->moradores = createHashTable(HT_SIZE);
	return q;
}

void destroyQuadra(Quadra *q){
	destroyString( q->cep );
	destroyString( q->fill );
	destroyString( q->stroke );
	destroyDoubleHashTable( q->estabComerciais );
	destroyHashTable( q->moradores );
	free(q);
}

double getQuadraX(Quadra *q){
	return q->x;
}

double getQuadraY(Quadra *q){
	return q->y;
}

double getQuadraWidth(Quadra *q){
	return q->width;
}

double getQuadraHeight(Quadra *q){
	return q->height;
}

char *getQuadraCep(Quadra *q){
	return q->cep;
}

char *getQuadraFill(Quadra *q){
	return q->fill;
}

char *getQuadraStroke(Quadra *q){
	return q->stroke;
}

HashTable *getQuadraEstabComerciais(Quadra *q){
	return q->estabComerciais;
}

HashTable *getQuadraMoradores(Quadra *q){
	return q->moradores;
}
