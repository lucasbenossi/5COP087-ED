#include "Operadora.h"
#include "HashTable.h"
#include "QuadTree.h"
#include "QuadTreeSearch.h"
#include "LinkedList.h"
#include "Endereco.h"
#include "String.h"
#include "Celular.h"
#include "Pessoa.h"
#include "Object.h"
#include "Point.h"
#include "ObjQuadTree.h"
#include <stdlib.h>

/* ========================================================================== */

struct _operadora{
	char *nome;
	List *torresList; /* Object->Torre */
	QuadTree *torresQT; /* Object->Torre */
	HashTable *torresHT; /* id X Object->Torre */
	HashTable *clientes; /* cpf X Pessoa */
	HashTable *celularesNum; /* numero X Celular */
	HashTable *celularesCpf; /* cpf * Celular */
	HashTable *conexoesTorreId; /* torreId X ( numero X Celular ) */
	HashTable *conexoesQuadraCep; /* quadraCep X ( numero X Celular ) */
	int method;
};

Operadora *createOperadora( char *nome, int method ){
	Operadora *operadora;

	operadora = malloc(sizeof(Operadora));
	operadora->nome = createString(nome);
	operadora->torresList = createList();
	operadora->torresQT = createQuadTree();
	operadora->torresHT = createHashTable(HT_SIZE);
	operadora->clientes = createHashTable(HT_SIZE);
	operadora->celularesNum = createHashTable(HT_SIZE);
	operadora->celularesCpf = createHashTable(HT_SIZE);
	operadora->conexoesTorreId = createHashTable(HT_SIZE);
	operadora->conexoesQuadraCep = createHashTable(HT_SIZE);
	operadora->method = method;

	return operadora;
}

void destroyOperadora( Operadora *operadora ){
	destroyString(operadora->nome);
	destroyList(operadora->torresList);
	destroyQuadTree(operadora->torresQT);
	destroyHashTable(operadora->torresHT);
	destroyHashTable(operadora->clientes);
	setHashTableFuncDestroyData(operadora->celularesNum, destroyCelularVoid);
	destroyHashTable(operadora->celularesNum);
	destroyHashTable(operadora->celularesCpf);
	destroyDoubleHashTable(operadora->conexoesTorreId);
	destroyDoubleHashTable(operadora->conexoesQuadraCep);
	free(operadora);
}

void operadoraFillDataStructures( Operadora *operadora ){
	listToQt( operadora->torresList, operadora->torresQT, operadora->method );
	freeList( operadora->torresList );
}

void operadoraInsertTorre( Operadora *operadora, Object *torre ){
	char *torreId = getObjId(torre);
	insert( operadora->torresList, torre );
	insertHashTable( operadora->torresHT, torreId, torre );
}

void operadoraRemoveTorresRegion( Operadora *operadora, Object *region ){
	List *removed = createList();
	Node *node;
	Object *torre;
	char *torreId;
	HashTable *conexoes;
	Iterator *it;

	quadTreeRemoveObjsRegion( operadora->torresQT, removed, region, operadora->method );
	for( node = getFirst(removed); node; node = getNext(node) ){
		torre = get(node);
		torreId = getObjId(torre);

		removeHashTable( operadora->torresHT, torreId, torre );

		conexoes = removeHashTable( operadora->conexoesTorreId, torreId, NULL );
		if(conexoes){
			it = createIterator(conexoes);
			while( iteratorHasNext(it) ){
				destroyEndereco( operadoraDesconectaCelular(operadora, iteratorNext(it)) );
			}
			destroyIterator(it);
			destroyHashTable(conexoes);
		}
	}

	destroyList(removed);
}

int operadoraIsPessoaCliente( Operadora *operadora, Pessoa *pessoa ){
	if( searchHashTable(operadora->clientes, getPessoaCpf(pessoa)) ){
		return 1;
	}
	return 0;
}

void operadoraInsertCliente( Operadora *operadora, Pessoa *pessoa, Celular *celular ){
	insertHashTable( operadora->clientes, getPessoaCpf(pessoa), pessoa );
	insertHashTable( operadora->celularesNum, getCelularNumero(celular), celular );
	insertHashTable( operadora->celularesCpf, getCelularCpf(celular), celular );
}

void operadoraRemoveCliente( Operadora *operadora, Pessoa *pessoa, Celular *celular ){
	if(getCelularEndereco(celular)){
		destroyEndereco(operadoraDesconectaCelular(operadora, celular));
	}
	removeHashTable(operadora->clientes, getPessoaCpf(pessoa), pessoa);
	removeHashTable(operadora->celularesNum, getCelularNumero(celular), celular);
	removeHashTable(operadora->celularesCpf, getPessoaCpf(pessoa), celular);
}

void operadoraConectaCelular( Operadora *operadora, Celular *celular, Quadra *quadra, Endereco *endereco ){
	Point *coords = getEnderecoCoords( endereco, quadra );
	Object *torre = searchQuadTreeNearestToPoint( getPointX(coords), getPointY(coords), operadora->torresQT );
	char *torreId = getObjId(torre);
	char *quadraCep = getQuadraCep(quadra);
	char *numero = getCelularNumero(celular);

	celularConecta( celular, torreId, endereco );
	insertDoubleHashTable( operadora->conexoesTorreId, torreId, numero, celular );
	insertDoubleHashTable( operadora->conexoesQuadraCep, quadraCep, numero, celular );

	destroyPoint(coords);
}

Endereco *operadoraDesconectaCelular( Operadora *operadora, Celular *celular ){
	char *quadraCep = getEnderecoCep(getCelularEndereco(celular));
	char *torreId = getCelularTorreId(celular);
	char *numero = getCelularNumero(celular);

	removeDoubleHashTable( operadora->conexoesTorreId, torreId, numero, celular );
	removeDoubleHashTable( operadora->conexoesQuadraCep, quadraCep, numero, celular );

	return celularDesconecta(celular);
}

void operadoraDesconectaCelularesQuadra( Operadora *operadora, Quadra *quadra ){
	HashTable *conexoes = removeHashTable( operadora->conexoesQuadraCep, getQuadraCep(quadra), NULL );
	if(conexoes){
		Iterator *it = createIterator(conexoes);
		while(iteratorHasNext(it)){
			destroyEndereco(operadoraDesconectaCelular(operadora, iteratorNext(it)));
		}
		destroyIterator(it);
		destroyHashTable(conexoes);
	}
}

List *searchOperadoraTorresRegion( Operadora *operadora, Object *region ){
	List *nodes, *torres;

	nodes = createList();
	searchQuadTreeRegion( operadora->torresQT, nodes, region );

	torres = createList();
	while( ! isListEmpty(nodes) ){
		insert( torres, getQuadTreeNodeData(removeFirst(nodes)) );
	}
	destroyList(nodes);

	return torres;
}

Object *searchOperadoraTorreId( Operadora *operadora, char *torreId ){
	return searchHashTable( operadora->torresHT, torreId );
}

Pessoa *searchOperadoraClienteCpf( Operadora *operadora, char *cpf ){
	return searchHashTable( operadora->clientes, cpf );
}

Celular *searchOperadoraCelularNum( Operadora *operadora, char *num ){
	return searchHashTable( operadora->celularesNum, num );
}

Celular *searchOperadoraCelularCpf( Operadora *operadora, char *cpf ){
	return searchHashTable( operadora->celularesCpf, cpf );
}

HashTable *searchOperadoraConexoesTorreId( Operadora *operadora, char *torreId ){
	return searchHashTable( operadora->conexoesTorreId, torreId );
}

HashTable *searchOperadoraConexoesQuadraCep( Operadora *operadora, char *quadraCep ){
	return searchHashTable( operadora->conexoesQuadraCep, quadraCep );
}

char *getOperadoraNome( Operadora *operadora ){
	return operadora->nome;
}

HashTable *getOperadoraTorresHT( Operadora *operadora ){
	return operadora->torresHT;
}

QuadTree *getOperadoraTorresQT( Operadora *operadora ){
	return operadora->torresQT;
}

HashTable *getOperadoraClientes( Operadora *operadora ){
	return operadora->clientes;
}

HashTable *getOperadoraCelularesNum( Operadora *operadora ){
	return operadora->celularesNum;
}

HashTable *getOperadoraCelularesCpf( Operadora *operadora ){
	return operadora->celularesCpf;
}

HashTable *getOperadoraConexoesTorreId( Operadora *operadora ){
	return operadora->conexoesTorreId;
}

HashTable *getOperadoraConexoesQuadraCep( Operadora *operadora ){
	return operadora->conexoesQuadraCep;
}
