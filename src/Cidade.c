#include <stdlib.h>
#include "Cidade.h"
#include "EstabComercial.h"
#include "Pessoa.h"
#include "ObjData.h"
#include "ObjQuadTree.h"
#include "ObjHashTable.h"
#include "LinkedList.h"
#include "String.h"
#include "QuadTree.h"
#include "QuadTreeSearch.h"
#include "HashTable.h"
#include "Operadora.h"
#include "Endereco.h"
#include "Graph.h"
#include "Rua.h"
#include "FuncDestroyData.h"

/* ========================================================================== */

struct _cidade{
	char *nome;
	List *quadrasList; /* Object->Quadra */
	QuadTree *quadrasQT; /* Object->Quadra */
	HashTable *quadrasHT; /* cep X Object->Quadra */
	char *quadrasFill;
	char *quadrasStroke;
	List *hidrantesList; /* Object->Point */
	QuadTree *hidrantesQT; /* Object->Point */
	HashTable *hidrantesHT; /* id X Object->Point */
	char *hidrantesFill;
	char *hidrantesStroke;
	List *semaforosList; /* Object->Point */
	QuadTree *semaforosQT; /* Object->Point */
	HashTable *semaforosHT; /* id X Object->Point */
	char *semaforosFill;
	char *semaforosStroke;
	List *torresList; /* Object->Point */
	QuadTree *torresQT; /* Object->Point */
	HashTable *torresHT; /* id X Object->Point */
	char *torresFill;
	char *torresStroke;
	HashTable *descricoes; /* codt X String */
	HashTable *estabComerciais;/* cnpj X EstabComercial */
	HashTable *pessoas; /* cpf X Pessoa */
	HashTable *defuntos; /* cpf X Pessoa */
	Operadora *sercomtuel;
	Operadora *uelmobile;
	List *verticesList; /* Object->Point */
	QuadTree *verticesQT; /* Object->Point */
	HashTable *verticesHT; /* id X Point */
	List *ruas;
	Graph *malhaViaria;
	HashTable *registradores; /* registrador X Point */
	int method;
};

Cidade *createCidade(char *nome, int method){
	Cidade *cidade = malloc(sizeof(Cidade));

	cidade->nome = createString(nome);

	cidade->quadrasList = createList();
	cidade->quadrasQT = createQuadTree();
	cidade->quadrasHT = createHashTable(HT_SIZE);
	cidade->quadrasFill = createString("rgb(153,204,255)");
	cidade->quadrasStroke = createString("black");

	cidade->hidrantesList = createList();
	cidade->hidrantesQT = createQuadTree();
	cidade->hidrantesHT = createHashTable(HT_SIZE);
	cidade->hidrantesFill = createString("rgb(255,0,0)");
	cidade->hidrantesStroke = createString("black");

	cidade->semaforosList = createList();
	cidade->semaforosQT = createQuadTree();
	cidade->semaforosHT = createHashTable(HT_SIZE);
	cidade->semaforosFill = createString("rgb(153,153,153)");
	cidade->semaforosStroke = createString("black");

	cidade->torresList = createList();
	cidade->torresQT = createQuadTree();
	cidade->torresHT = createHashTable(HT_SIZE);
	cidade->torresFill = createString("rgb(255,102,0)");
	cidade->torresStroke = createString("black");

	cidade->descricoes = createHashTable(HT_SIZE_SMALL);
	cidade->estabComerciais = createHashTable(HT_SIZE_LARGE);

	cidade->pessoas = createHashTable(HT_SIZE_LARGE);
	cidade->defuntos = createHashTable(HT_SIZE);

	cidade->sercomtuel = createOperadora("SercomtUEL", method);
	cidade->uelmobile = createOperadora("UELMobile", method);

	cidade->verticesList = createList();
	cidade->verticesQT = createQuadTree();
	cidade->verticesHT = createHashTable(HT_SIZE);
	cidade->ruas = createList();
	cidade->malhaViaria = createGraph();
	cidade->registradores = createHashTable(HT_SIZE_SMALL);

	cidade->method = method;

	return cidade;
}

void destroyCidade(Cidade *cidade){
	destroyString(cidade->nome);

	destroyList(cidade->quadrasList);
	destroyQuadTree(cidade->quadrasQT);
	setHashTableFuncDestroyData(cidade->quadrasHT, destroyObjDataVoid);
	destroyHashTable(cidade->quadrasHT);
	destroyString(cidade->quadrasFill);
	destroyString(cidade->quadrasStroke);

	destroyList(cidade->hidrantesList);
	destroyQuadTree(cidade->hidrantesQT);
	setHashTableFuncDestroyData(cidade->hidrantesHT, destroyObjDataVoid);
	destroyHashTable(cidade->hidrantesHT);
	destroyString(cidade->hidrantesFill);
	destroyString(cidade->hidrantesStroke);

	destroyList(cidade->semaforosList);
	destroyQuadTree(cidade->semaforosQT);
	setHashTableFuncDestroyData(cidade->semaforosHT, destroyObjDataVoid);
	destroyHashTable(cidade->semaforosHT);
	destroyString(cidade->semaforosFill);
	destroyString(cidade->semaforosStroke);

	destroyList(cidade->torresList);
	destroyQuadTree(cidade->torresQT);
	setHashTableFuncDestroyData(cidade->torresHT, destroyObjDataVoid);
	destroyHashTable(cidade->torresHT);
	destroyString(cidade->torresFill);
	destroyString(cidade->torresStroke);

	setHashTableFuncDestroyData(cidade->descricoes, destroyStringVoid);
	destroyHashTable(cidade->descricoes);
	setHashTableFuncDestroyData(cidade->estabComerciais, destroyEstabComercialVoid);
	destroyHashTable(cidade->estabComerciais);

	setHashTableFuncDestroyData(cidade->pessoas, destroyPessoaVoid);
	destroyHashTable(cidade->pessoas);
	setHashTableFuncDestroyData(cidade->defuntos, destroyPessoaVoid);
	destroyHashTable(cidade->defuntos);

	destroyOperadora(cidade->sercomtuel);
	destroyOperadora(cidade->uelmobile);

	destroyList(cidade->verticesList);
	destroyObjQuadTree(cidade->verticesQT);
	destroyHashTable(cidade->verticesHT);
	setListFuncDestroyData(cidade->ruas, destroyRuaVoid);
	destroyList(cidade->ruas);
	destroyGraph(cidade->malhaViaria);
	setHashTableFuncDestroyData(cidade->registradores, destroyPointVoid);
	destroyHashTable(cidade->registradores);

	free(cidade);
}

/* ========================================================================== */

void cidadeFillDataStructures(Cidade *cidade){
	int i;
	List *list[5];
	QuadTree *qt[5];

	operadoraFillDataStructures(cidade->sercomtuel);
	operadoraFillDataStructures(cidade->uelmobile);

	list[0] = cidade->quadrasList;
	list[1] = cidade->hidrantesList;
	list[2] = cidade->semaforosList;
	list[3] = cidade->torresList;
	list[4] = cidade->verticesList;

	qt[0] = cidade->quadrasQT;
	qt[1] = cidade->hidrantesQT;
	qt[2] = cidade->semaforosQT;
	qt[3] = cidade->torresQT;
	qt[4] = cidade->verticesQT;

	for( i = 0; i < 5; i++ ){
	    listToQt( list[i], qt[i], cidade->method );
	    setListFuncDestroyData(list[i], NULL);
	    freeList( list[i] );
	}
}

void cidadeInsertObj( Cidade *cidade, Object *obj, char objType, Resumo *res ){
	List *list;
	HashTable *ht;

	list = getCidadeObjTypeList(cidade, objType);
	ht = getCidadeObjTypeHashTable(cidade, objType);

	if( objType == 'q' ){
		incIns(res);
		incCpi(res);
	}

	insert( list, obj );
	insertHashTable( ht, getObjId(obj), obj );
}

List *cidadeRemoveObjsRegion( Cidade *cidade, char objType, Object *region, Resumo *res ){
	List *removed;
	QuadTree *qt;
	HashTable *ht;
	Object *obj;
	Node *node;
	int comp;

	qt = getCidadeObjTypeQuadTree(cidade, objType);
	ht = getCidadeObjTypeHashTable(cidade, objType);

	if( objType == 't' ){
	    operadoraRemoveTorresRegion( cidade->sercomtuel, region );
	    operadoraRemoveTorresRegion( cidade->uelmobile, region );
	}

	removed = createList();
	comp = quadTreeRemoveObjsRegion( qt, removed, region, cidade->method );

	if( objType == 'q' ){
	    setResumoCpd(res, comp);
	    setResumoDel(res, lenght(removed));
	}

	for( node = getFirst(removed); node; node = getNext(node) ){
	    obj = get(node);
	    if( getObjType(obj) == 'q' ){
	        cidadeRemoveEstabMoradorQuadra( cidade, getObjData(obj) );
			operadoraDesconectaCelularesQuadra(cidade->sercomtuel, getObjData(obj));
			operadoraDesconectaCelularesQuadra(cidade->uelmobile, getObjData(obj));
	    }
	    removeHashTable( ht, getObjId(obj), obj );
	}

	return removed;
}

void cidadeInsertEstabComercial( Cidade *cidade, EstabComercial *estab ){
	Quadra *quadra = getObjData( searchCidadeQuadraCep( cidade, getEstabComercialCep(estab)) );

	insertHashTable( cidade->estabComerciais, getEstabComercialCNPJ(estab), estab );
	insertDoubleHashTable( getQuadraEstabComerciais(quadra), getEstabComercialCodt(estab), getEstabComercialCNPJ(estab), estab );
}

void cidadeRemoveEstabComercial( Cidade *cidade, EstabComercial *estab ){
	Quadra *quadra = getObjData( searchCidadeQuadraCep( cidade, getEstabComercialCep(estab) ) );

	removeDoubleHashTable( getQuadraEstabComerciais(quadra), getEstabComercialCodt(estab), getEstabComercialCNPJ(estab), estab );
	removeHashTable( cidade->estabComerciais, getEstabComercialCNPJ(estab), estab );
}

void cidadeInsertPessoa( Cidade *cidade, Pessoa *pessoa ){
	insertHashTable( cidade->pessoas, getPessoaCpf(pessoa), pessoa );
}

void cidadeRemovePessoa( Cidade *cidade, Pessoa *pessoa ){
	Operadora *op = getCidadeOperadoraPessoa(cidade, pessoa);

	if( getPessoaEndereco(pessoa) ){
		destroyEndereco(cidadeRemoveMorador(cidade, pessoa));
	}

	if(op){
		Celular *celular = searchOperadoraCelularCpf( op, getPessoaCpf(pessoa) );
		operadoraRemoveCliente( op, pessoa, celular );
		destroyCelular(celular);
	}

	removeHashTable(cidade->pessoas, getPessoaCpf(pessoa), pessoa);
}

void cidadeInsertMorador( Cidade *cidade, Pessoa *pessoa, Endereco *endereco ){
	Quadra *quadra = getObjData( searchCidadeQuadraCep( cidade, getEnderecoCep(endereco) ) );
	setPessoaEndereco( pessoa, endereco );
	insertHashTable( getQuadraMoradores(quadra), getPessoaCpf(pessoa), pessoa );
}

Endereco *cidadeRemoveMorador( Cidade *cidade, Pessoa *pessoa ){
	Quadra *quadra = getObjData( searchCidadeQuadraCep( cidade, getEnderecoCep(getPessoaEndereco(pessoa)) ) );
	removeHashTable( getQuadraMoradores(quadra), getPessoaCpf(pessoa), pessoa );
	return resetPessoaEndereco(pessoa);
}

void cidadeRemoveEstabMoradorQuadra( Cidade *cidade, Quadra *quadra ){
	Iterator *itCpf, *itCodt, *itCnpj;

	itCpf = createIterator( getQuadraMoradores(quadra) );
	while( iteratorHasNext(itCpf) ){
	    Pessoa *pessoa = iteratorNext(itCpf);
	    destroyEndereco(resetPessoaEndereco(pessoa));
	    iteratorRemove(itCpf);
	}
	destroyIterator(itCpf);

	itCodt = createIterator( getQuadraEstabComerciais(quadra) );
	while( iteratorHasNext(itCodt) ){
	    HashTable *ht = iteratorNext(itCodt);

	    itCnpj = createIterator(ht);
	    while( iteratorHasNext(itCnpj) ){
	        EstabComercial *estab = iteratorNext(itCnpj);
	        removeHashTable( cidade->estabComerciais, getEstabComercialCNPJ(estab), estab );
	        destroyEstabComercial(estab);
	        iteratorRemove(itCnpj);
	    }
	    destroyIterator(itCnpj);

	    destroyHashTable(ht);
	    iteratorRemove(itCodt);
	}
	destroyIterator(itCodt);
}

void cidadeMatarPessoa( Cidade *cidade, Pessoa *pessoa ){
	Endereco *endereco = NULL;

	if(getPessoaEndereco(pessoa)){
		endereco = cidadeRemoveMorador(cidade, pessoa);
	}

	cidadeRemovePessoa(cidade, pessoa);

	if(endereco){
		setPessoaEndereco(pessoa, endereco);
	}
	insertHashTable( cidade->defuntos, getPessoaCpf(pessoa), pessoa );
}

void cidadeInsertVertice( Cidade *cidade, Point *vertice ){
	insert(cidade->verticesList, createObject(getPointId(vertice), '\0', vertice));
	insertHashTable(cidade->verticesHT, getPointId(vertice), vertice);
	setVertexCoords(insertVertex(cidade->malhaViaria, getPointId(vertice), vertice), getPointX(vertice), getPointY(vertice));
}

void cidadeInsertRua( Cidade *cidade, Point *i, Point *j, Rua *rua ){
	insert(cidade->ruas, rua);
	insertEdge(cidade->malhaViaria, getPointId(i), getPointId(j), rua);
}

void cidadeSetRegistrador( Cidade *cidade, char *registrador, double x, double y ){
	Point *coords;

	cidadeCleanRegistrador(cidade, registrador);

	coords = createPoint(x, y, registrador, "", "");
	insertHashTable(cidade->registradores, registrador, coords);
}

void cidadeCleanRegistrador( Cidade *cidade, char *registrador ){
	Point *coords = cidadeGetRegistrador(cidade, registrador);

	if(coords){
	    removeHashTable(cidade->registradores, registrador, coords);
	    destroyPoint(coords);
	}
}

Point *cidadeGetRegistrador( Cidade *cidade, char *registrador ){
	return searchHashTable(cidade->registradores, registrador);
}

/* ========================================================================== */

List *searchCidadeObjTypeRegion( Cidade *cidade, char objType, Object *region ){
	List *nodes, *objs;
	QuadTree *qt;

	if( objType == 'q' ){
	    qt = cidade->quadrasQT;
	}
	else if( objType == 'h' ){
	    qt = cidade->hidrantesQT;
	}
	else if( objType == 's' ){
	    qt = cidade->semaforosQT;
	}
	else if( objType == 't' ){
	    qt = cidade->torresQT;
	}

	nodes = createList();
	searchQuadTreeRegion( qt, nodes, region );

	objs = createList();
	while( ! isListEmpty(nodes) ){
		insert( objs, getQuadTreeNodeData(removeFirst(nodes)) );
	}
	destroyList(nodes);

	return objs;
}

Object *searchCidadeQuadraCep( Cidade *cidade, char *cep ){
	return searchHashTable( cidade->quadrasHT, cep );
}

Object *searchCidadeHidranteId( Cidade *cidade, char *id ){
	return searchHashTable( cidade->hidrantesHT, id );
}

Object *searchCidadeSemaforoId( Cidade *cidade, char *id ){
	return searchHashTable( cidade->semaforosHT, id );
}

Object *searchCidadeTorreId( Cidade *cidade, char *id ){
	return searchHashTable( cidade->torresHT, id );
}

Object *searchCidadeObjTypeIdCep( Cidade *cidade, char objType, char *idCep ){
	HashTable *ht = getCidadeObjTypeHashTable(cidade, objType);
	return searchHashTable(ht, idCep);
}

char *searchCidadeDescricaoCodt( Cidade *cidade, char *codt ){
	return searchHashTable( cidade->descricoes, codt );
}

EstabComercial *searchCidadeEstabComercialCnpj( Cidade *cidade, char *cnpj ){
	return searchHashTable( cidade->estabComerciais, cnpj );
}

Pessoa *searchCidadePessoaCpf( Cidade *cidade, char *cpf ){
	return searchHashTable( cidade->pessoas, cpf );
}

Pessoa *searchCidadeDefuntoCpf( Cidade *cidade, char *cpf ){
	return searchHashTable( cidade->defuntos, cpf );
}

Point *searchCidadeVerticeId( Cidade *cidade, char *id ){
	return searchHashTable(cidade->verticesHT, id);
}

/* ========================================================================== */

void setCidadeQuadrasColors(Cidade *cidade, char *fill, char *stroke){
	repString( &( cidade->quadrasFill ), fill );
	repString( &( cidade->quadrasStroke ), stroke );
}

void setCidadeHidrantesColors(Cidade *cidade, char *fill, char *stroke){
	repString( &( cidade->hidrantesFill ), fill );
	repString( &( cidade->hidrantesStroke ), stroke );
}

void setCidadeSemaforosColors(Cidade *cidade, char *fill, char *stroke){
	repString( &( cidade->semaforosFill ), fill );
	repString( &( cidade->semaforosStroke ), stroke );
}

void setCidadeTorresColors(Cidade *cidade, char *fill, char *stroke){
	repString( &( cidade->torresFill ), fill );
	repString( &( cidade->torresStroke ), stroke );
}

/* ========================================================================== */

char *getCidadeNome(Cidade *cidade){
	return cidade->nome;
}

List *getCidadeQuadrasList(Cidade *cidade){
	return cidade->quadrasList;
}

QuadTree *getCidadeQuadrasQT(Cidade *cidade){
	return cidade->quadrasQT;
}

HashTable *getCidadeQuadrasHT(Cidade *cidade){
	return cidade->quadrasHT;
}

char *getCidadeQuadrasFill(Cidade *cidade){
	return cidade->quadrasFill;
}

char *getCidadeQuadrasStroke(Cidade *cidade){
	return cidade->quadrasStroke;
}

List *getCidadeHidrantesList(Cidade *cidade){
	return cidade->hidrantesList;
}

QuadTree *getCidadeHidrantesQT(Cidade *cidade){
	return cidade->hidrantesQT;
}

HashTable *getCidadeHidrantesHT(Cidade *cidade){
	return cidade->hidrantesHT;
}

char *getCidadeHidrantesFill(Cidade *cidade){
	return cidade->hidrantesFill;
}

char *getCidadeHidrantesStroke(Cidade *cidade){
	return cidade->hidrantesStroke;
}

List *getCidadeSemaforosList(Cidade *cidade){
	return cidade->semaforosList;
}

QuadTree *getCidadeSemaforosQT(Cidade *cidade){
	return cidade->semaforosQT;
}

HashTable *getCidadeSemaforosHT(Cidade *cidade){
	return cidade->semaforosHT;
}

char *getCidadeSemaforosFill(Cidade *cidade){
	return cidade->semaforosFill;
}

char *getCidadeSemaforosStroke(Cidade *cidade){
	return cidade->semaforosStroke;
}

List *getCidadeTorresList(Cidade *cidade){
	return cidade->torresList;
}

QuadTree *getCidadeTorresQT(Cidade *cidade){
	return cidade->torresQT;
}

HashTable *getCidadeTorresHT(Cidade *cidade){
	return cidade->torresHT;
}

char *getCidadeTorresFill(Cidade *cidade){
	return cidade->torresFill;
}

char *getCidadeTorresStroke(Cidade *cidade){
	return cidade->torresStroke;
}

HashTable *getCidadeDescricoes(Cidade *cidade){
	return cidade->descricoes;
}

HashTable *getCidadeEstabComerciais(Cidade *cidade){
	return cidade->estabComerciais;
}

HashTable *getCidadePessoas(Cidade *cidade){
	return cidade->pessoas;
}

HashTable *getCidadeDefuntos(Cidade *cidade){
	return cidade->defuntos;
}

Operadora *getCidadeSercomtuel(Cidade *cidade){
	return cidade->sercomtuel;
}

Operadora *getCidadeUelmobile(Cidade *cidade){
	return cidade->uelmobile;
}

List *getCidadeVerticesList(Cidade *cidade){
	return cidade->verticesList;
}

QuadTree *getCidadeVerticesQT(Cidade *cidade){
	return cidade->verticesQT;
}

HashTable *getCidadeVerticesHT(Cidade *cidade){
	return cidade->verticesHT;
}

List *getCidadeRuas(Cidade *cidade){
	return cidade->ruas;
}

Graph *getCidadeMalhaViaria(Cidade *cidade){
	return cidade->malhaViaria;
}

HashTable *getCidadeRegistradores(Cidade *cidade){
	return cidade->registradores;
}

int getCidadeMethod(Cidade *cidade){
	return cidade->method;
}

List *getCidadeObjTypeList( Cidade *cidade, char objType ){
	if( objType == 'q' ){
	    return cidade->quadrasList;
	}
	if( objType == 'h' ){
	    return cidade->hidrantesList;
	}
	if( objType == 's' ){
	    return cidade->semaforosList;
	}
	if( objType == 't' ){
	    return cidade->torresList;
	}
	return NULL;
}

QuadTree *getCidadeObjTypeQuadTree( Cidade *cidade, char objType ){
	if( objType == 'q' ){
	    return cidade->quadrasQT;
	}
	if( objType == 'h' ){
	    return cidade->hidrantesQT;
	}
	if( objType == 's' ){
	    return cidade->semaforosQT;
	}
	if( objType == 't' ){
	    return cidade->torresQT;
	}
	return NULL;
}

HashTable *getCidadeObjTypeHashTable( Cidade *cidade, char objType ){
	if( objType == 'q' ){
	    return cidade->quadrasHT;
	}
	if( objType == 'h' ){
	    return cidade->hidrantesHT;
	}
	if( objType == 's' ){
	    return cidade->semaforosHT;
	}
	if( objType == 't' ){
	    return cidade->torresHT;
	}
	return NULL;
}

Operadora *getCidadeOperadoraPessoa( Cidade *cidade, Pessoa *pessoa ){
	if( operadoraIsPessoaCliente( cidade->sercomtuel, pessoa ) ){
	    return cidade->sercomtuel;
	}
	if( operadoraIsPessoaCliente( cidade->uelmobile, pessoa ) ){
	    return cidade->uelmobile;
	}
	return NULL;
}

Operadora **getCidadeOperadoras( Cidade *cidade ){
	static Operadora *operadoras[2];
	operadoras[0] = cidade->sercomtuel;
	operadoras[1] = cidade->uelmobile;
	return operadoras;
}
