#ifndef CIDADE_H
#define CIDADE_H
#include "LinkedList.h"
#include "QuadTree.h"
#include "HashTable.h"
#include "Operadora.h"
#include "EstabComercial.h"
#include "Resumo.h"
#include "Graph.h"
#include "Rua.h"
#include "Object.h"
#include "Pessoa.h"
#include "EstabComercial.h"
#include "Point.h"

/*
Define uma instancia de Cidade.
Possui os seguintes atributos:
  - nome = Nome da cidade (tipo char*).
  - quadrasList = Lista de quadras da cidade (tipo List).
  - quadrasQT = QuadTree com as quadras da cidade (tipo QuadTree).
  - quadrasHT = Table Hash com as quadras da cidade (tipo HashTable).
  - quadrasFill = Preenchimento das quadras (string).
  - quadrasStroke = Cor da borda das quadras (string).
  - hidrantesList = Lista de hidrantes (tipo List).
  - hidrantesQT = QuadTree com os hidrantes (tipo QuadTree).
  - hidrantesHT = Table Hash com os hidrantes (tipo HashTable).
  - hidrantesFill = Preenchimento dos hidrantes (string).
  - hidrantesStroke = Cor da borda dos hidrantes (string).
  - semaforosList = Lista de semaforos (tipo List).
  - semaforosQT = QuadTree com os semaforos (tipo QuadTree).
  - semaforosHT = Table Hash com os semaforos (tipo HashTable).
  - semaforosFill = Preenchimento dos semaforos (string).
  - semaforosStroke = Cor da borda dos semaforos (string).
  - torresList = Lista de torres de radio (tipo List).
  - torresQT = QuadTree com as torres de radio (tipo QuadTree).
  - torresHT = Table Hash com as torres de radio (tipo HashTable).
  - torresFill = Preenchimento das torres de radio (string).
  - torresStroke = Cor da borda das torres de radio (string).
  - descricoes = Tabela Hash com as descições dos estabelecimentos comerciais (tipo HashTable).
  - estabComerciais = Tabela Hash com os estabelecimentos comerciais da cidade (tipo HashTable).
  - pessoas = Tabela Hash com as pessoas da cidade (tipo HashTable).
  - defuntos = Tabe Hash com os defuntos (tipo HashTable).
  - sercomtuel = Operadora SercomtUEL (tipo Operadora).
  - uelmobile = Operadora UELMobile (tipo Operadora).
  - verticesList = Lista com os vertices da cidade (tipo List).
  - verticesQT = QuadTree com os vertices da cidade (tipo QuadTree).
  - verticesHT = HashTable com os vertices da cidade (tipo HashTable).
  - ruas = Ruas da cidade (tipo List).
  - malhaViaria = Malha viaria da cidade (tipo Graph).
  - registradores = Registradores p/ clculo de rotas (tipo HashTable).
  - method = Método de inserção dos objetos nas QuadTrees correspondentes (tipo int).
	    1 = inserir usando envoltório convexo e ordenação.
	    2 = inserir usando envoltório convexo.
	    3 = inserir na ordem que foi inserido na lista.
*/
typedef struct _cidade Cidade;


/* ========================================================================== */


/*
Aloca ou desaloca memoria para uma instancia de Cidade
*/
Cidade *createCidade(char *nome, int method);
void destroyCidade(Cidade *cidade);


/* ========================================================================== */


/*
Para cada lista de elementos da instancia de Cidade, cria uma QuadTree com esses
elementos.
*/
void cidadeFillDataStructures(Cidade *cidade);

/*
Insere ou remove objetos do tipo objType na cidade.
Remove elementos que estao dentro da regiao definida por region.
*/
void cidadeInsertObj( Cidade *cidade, Object *obj, char objType, Resumo *res );
List *cidadeRemoveObjsRegion( Cidade *cidade, char objType, Object *region, Resumo *res ); /* Object */

void cidadeInsertEstabComercial( Cidade *cidade, EstabComercial *estab );
void cidadeRemoveEstabComercial( Cidade *cidade, EstabComercial *estab );

void cidadeInsertPessoa( Cidade *cidade, Pessoa *pessoa );
void cidadeRemovePessoa( Cidade *cidade, Pessoa *pessoa );

void cidadeInsertMorador( Cidade *cidade, Pessoa *pessoa, Endereco *endereco );
Endereco *cidadeRemoveMorador( Cidade *cidade, Pessoa *pessoa );

void cidadeRemoveEstabMoradorQuadra( Cidade *cidade, Quadra *quadra );

void cidadeMatarPessoa( Cidade *cidade, Pessoa *pessoa );

void cidadeInsertVertice( Cidade *cidade, Point *vertice );

void cidadeInsertRua( Cidade *cidade, Point *i, Point *j, Rua *rua );

void cidadeSetRegistrador( Cidade *cidade, char *registrador, double x, double y );
void cidadeCleanRegistrador( Cidade *cidade, char *registrador );
Point *cidadeGetRegistrador( Cidade *cidade, char *registrador );

/* ========================================================================== */


/*
Busca por elementos de uma cidade.
*/
List *searchCidadeObjTypeRegion( Cidade *cidade, char objType, Object *region ); /* Object */
Object *searchCidadeQuadraCep( Cidade *cidade, char *cep );
Object *searchCidadeHidranteId( Cidade *cidade, char *id );
Object *searchCidadeSemaforoId( Cidade *cidade, char *id );
Object *searchCidadeTorreId( Cidade *cidade, char *id );
Object *searchCidadeObjTypeIdCep( Cidade *cidade, char objType, char *idCep );
char *searchCidadeDescricaoCodt( Cidade *cidade, char *codt );
EstabComercial *searchCidadeEstabComercialCnpj( Cidade *cidade, char *cnpj );
Pessoa *searchCidadePessoaCpf( Cidade *cidade, char *cpf );
Pessoa *searchCidadeDefuntoCpf( Cidade *cidade, char *cpf );
Point *searchCidadeVerticeId( Cidade *cidade, char *id );


/* ========================================================================== */


/*
Define os parametros fill e stroke para as instancias de Quadra, hidrante,
Semáforo e Torres de Rádio;
*/
void setCidadeQuadrasColors(Cidade *cidade, char *fill, char *stroke);
void setCidadeHidrantesColors(Cidade *cidade, char *fill, char *stroke);
void setCidadeSemaforosColors(Cidade *cidade, char *fill, char *stroke);
void setCidadeTorresColors(Cidade *cidade, char *fill, char *stroke);


/* ========================================================================== */


/*
Retorna parametros da cidade.
*/
char *getCidadeNome(Cidade *cidade);
List *getCidadeQuadrasList(Cidade *cidade);
QuadTree *getCidadeQuadrasQT(Cidade *cidade);
HashTable *getCidadeQuadrasHT(Cidade *cidade);
char *getCidadeQuadrasFill(Cidade *cidade);
char *getCidadeQuadrasStroke(Cidade *cidade);
List *getCidadeHidrantesList(Cidade *cidade);
QuadTree *getCidadeHidrantesQT(Cidade *cidade);
HashTable *getCidadeHidrantesHT(Cidade *cidade);
char *getCidadeHidrantesFill(Cidade *cidade);
char *getCidadeHidrantesStroke(Cidade *cidade);
List *getCidadeSemaforosList(Cidade *cidade);
QuadTree *getCidadeSemaforosQT(Cidade *cidade);
HashTable *getCidadeSemaforosHT(Cidade *cidade);
char *getCidadeSemaforosFill(Cidade *cidade);
char *getCidadeSemaforosStroke(Cidade *cidade);
List *getCidadeTorresList(Cidade *cidade);
QuadTree *getCidadeTorresQT(Cidade *cidade);
HashTable *getCidadeTorresHT(Cidade *cidade);
char *getCidadeTorresFill(Cidade *cidade);
char *getCidadeTorresStroke(Cidade *cidade);
HashTable *getCidadeDescricoes(Cidade *cidade);
HashTable *getCidadeEstabComerciais(Cidade *cidade);
HashTable *getCidadePessoas(Cidade *cidade);
HashTable *getCidadeDefuntos(Cidade *cidade);
Operadora *getCidadeSercomtuel(Cidade *cidade);
Operadora *getCidadeUelmobile(Cidade *cidade);
List *getCidadeVerticesList(Cidade *cidade);
QuadTree *getCidadeVerticesQT(Cidade *cidade);
HashTable *getCidadeVerticesHT(Cidade *cidade);
List *getCidadeRuas(Cidade *cidade);
Graph *getCidadeMalhaViaria(Cidade *cidade);
HashTable *getCidadeRegistradores(Cidade *cidade);
int getCidadeMethod(Cidade *cidade);

List *getCidadeObjTypeList( Cidade *cidade, char objType );
QuadTree *getCidadeObjTypeQuadTree( Cidade *cidade, char objType );
HashTable *getCidadeObjTypeHashTable( Cidade *cidade, char objType );

Operadora *getCidadeOperadoraPessoa( Cidade *cidade, Pessoa *pessoa );

Operadora **getCidadeOperadoras( Cidade *cidade );

#endif
