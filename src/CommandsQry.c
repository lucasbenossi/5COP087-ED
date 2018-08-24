#include "CommandsQry.h"
#include "Cidade.h"
#include "Object.h"
#include "Quadra.h"
#include "Point.h"
#include "Polygon.h"
#include "Circle.h"
#include "Rect.h"
#include "LinkedList.h"
#include "Stack.h"
#include "HashTable.h"
#include "Array.h"
#include "QuadTree.h"
#include "QuadTreeSearch.h"
#include "ObjData.h"
#include "ObjQuadTree.h"
#include "Resumo.h"
#include "Geometry.h"
#include "String.h"
#include "Tokens.h"
#include "File.h"
#include "WriteTags.h"
#include "ConvexHull.h"
#include "Celular.h"
#include "Operadora.h"
#include "QuickSort.h"
#include <stdlib.h>
#include <string.h>
#include <complex.h>

static void genPolygonCobertura( List *torres, Polygon *polygon );

static void listarMoradoresQuadra( Cidade *cidade, Quadra *quadra, FILE *outFileTxt );

static void dumpConexoesTorre( Operadora *operadora, char *torreId, FILE *outFileTxt );

static int comparatorClientesOrdemNome( void *a, void *b, void *aux );

static void dumpDadosEstabComercial( EstabComercial *estab, FILE *outFileTxt );

/* ==========================================================================================*/

void commandCidadeDelete( char *line, Cidade *c, FILE *outFileTxt, Resumo *res ){
	double x, y, width, height, radius;
	char command, *outString;
	Object *obj, *region;
	List *removed;
	Node *node;

	fputs(line,outFileTxt);

	if( line[0] == 'd' ){
	    sscanf(line, "d%c %lf %lf %lf %lf", &command, &x, &y, &width, &height);
	    region = createObject( "", 'r', createRect(0, width, height, x, y, "") );
	}
	else if( line[0] == 'D' ){
	    sscanf(line, "D%c %lf %lf %lf", &command, &x, &y, &radius);
	    region = createObject( "", 'c', createCircle(0, radius, x, y, "") );
	}

	if( command == 'q' ){
	    outString = "Quadra %s removida\n";
	}
	else if( command == 'h' ){
	    outString = "Hidrante %s removido\n";
	}
	else if( command == 's' ){
	    outString = "Semaforo %s removido\n";
	}
	else if( command == 't' ){
	    outString = "Torre %s removida\n";
	}
	else{
	    return;
	}

	removed = cidadeRemoveObjsRegion( c, command, region, res );
	for( node = getFirst(removed); node; node = getNext(node) ){
	    obj = get(node);
	    fprintf( outFileTxt, outString, getObjId(obj) );
	    destroyObjData(obj);
	}
	destroyList(removed);

	fprintf( outFileTxt, "\n" );

	destroyObjData(region);
}

void commandSearchIdCep( char *line, Cidade *c, FILE *outFileTxt ){
	Object *obj;
	char objType[] = { 'q', 'h', 's', 't' };
	char *outString[] = { "Quadra", "Hidrante", "Semaforo", "Torre" };
	char idCep[STRING_SIZE];
	int i;

	fputs(line,outFileTxt);

	sscanf(line, "crd? %s", idCep);

	for( i = 0; i < 4; i++ ){
	    obj = searchCidadeObjTypeIdCep( c, objType[i], idCep );
	    if( obj != NULL ){
	        fprintf( outFileTxt, "Encontrado %s com coordenadas (%f,%f)\n\n", outString[i], getX(obj), getY(obj) );
	        return;
	    }
	}

	fprintf( outFileTxt, "Elemento com ID/Cep %s não encontrado\n\n", idCep );
}

void commandPoligonoCobertura( char *line, Cidade *cidade, char *nameFiles, char *outDir ){
	char *sufix, *fullPath;
	FILE *svg;
	int error;
	double x, y, width, height;
	List *qtNodesList, *torres;
	Object *region;
	Polygon *polygon;
	Node *node;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);
	defineTokens( tokens, line );
	if( strcmp( getToken(tokens,0), "pc?" ) != 0 ){
		return;
	}

	error = 0;

	sufix = getToken(tokens,1);
	fullPath = createStringCat(5, outDir, nameFiles, "-", sufix, ".svg");
	svg = openFileWrite(fullPath);
	if( svg == NULL ){
		error++;
	}

	if( error == 0 ){
		if( getToken(tokens,2) != NULL ){
			sscanf( getToken(tokens,2), "%lf", &x );
			sscanf( getToken(tokens,3), "%lf", &y );
			sscanf( getToken(tokens,4), "%lf", &width );
			sscanf( getToken(tokens,5), "%lf", &height );
			region = createObject( NULL, 'r', createRect( 0, width, height, x, y, NULL ) );
		}
		else{
			region = NULL;
		}

	    qtNodesList = createList();

	    searchQuadTreeRegion( getCidadeTorresQT(cidade), qtNodesList, region );

	    torres = createList();
	    while( ! isListEmpty(qtNodesList) ){
	        insert( torres, getQuadTreeNodeData(removeFirst(qtNodesList)) );
	    }
	    destroyList(qtNodesList);

		polygon = createPolygon( "cobertura", "red", "black" );
		genPolygonCobertura( torres, polygon );

		writeSvgStart(svg);

		writeCidadeTags( cidade, svg );

		node = getFirst(torres);
		while( node != NULL ){
			writeTorreCoberturaTag( getObjData(get(node)), svg );
			node = getNext(node);
		}

		writePolygonTag(polygon, svg);
		writeSvgEnd(svg);

		destroyPolygon(polygon);

		if( getToken(tokens,2) != NULL ){
			destroyObjData(region);
		}
		destroyList(torres);
	}

	destroyTokens(tokens);

	destroyString(fullPath);
	closeFile(svg);
}

void commandPoligonoCoberturaArea( char *line, Cidade *cidade, FILE *outFileTxt ){
	List *qtNodesList, *torres;
	Polygon *polygon;
	double x, y, width, height;
	Object *region;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);
	defineTokens( tokens, line );
	if( strcmp( getToken(tokens,0), "ac?" ) != 0 ){
		return;
	}

	fputs(line,outFileTxt);

	if( getToken(tokens,2) != NULL ){
		sscanf( getToken(tokens,1), "%lf", &x );
		sscanf( getToken(tokens,2), "%lf", &y );
		sscanf( getToken(tokens,3), "%lf", &width );
		sscanf( getToken(tokens,4), "%lf", &height );
	    region = createObject( NULL, 'r', createRect( 0, width, height, x, y, NULL ) );
	}
	else{
		region = NULL;
	}

	qtNodesList = createList();

	searchQuadTreeRegion( getCidadeTorresQT(cidade), qtNodesList, region );

	torres = createList();
	while( ! isListEmpty(qtNodesList) ){
	    insert( torres, getQuadTreeNodeData(removeFirst(qtNodesList)) );
	}
	destroyList(qtNodesList);

	polygon = createPolygon( "cobertura", NULL, NULL );
	genPolygonCobertura( torres, polygon );

	fprintf( outFileTxt, "%f\n\n", polygonArea(polygon) );

	destroyPolygon(polygon);

	if( getToken(tokens,2) != NULL ){
		destroyObjData(region);
	}
	destroyList(torres);

	destroyTokens(tokens);
}

static void genPolygonCobertura( List *torres, Polygon *polygon ){
	List *pointsList;
	Array *array;
	Stack *stack;
	Node *node;
	Object *obj;
	Point *torre, *point;
	double x, y, *radius, r, c;

	c = 0.707106781; /* sqrt(2)/2 */

	pointsList = createList();

	node = getFirst(torres);
	while( node != NULL ){
		obj = get(node);
		torre = getObjData(obj);
		radius = getPointInfo(torre);

		if( radius != NULL && *radius > 0 ){
			x = getPointX(torre);
			y = getPointY(torre);
			r = *radius;

			insert( pointsList, createObject( NULL, 't', createPoint( x  , y+r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y  , NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x  , y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y  , NULL, "blue", "black" ) ) );

			r = r*c;

			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y+r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x+r, y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y-r, NULL, "blue", "black" ) ) );
			insert( pointsList, createObject( NULL, 't', createPoint( x-r, y+r, NULL, "blue", "black" ) ) );
		}
		node = getNext(node);
	}

	array = listToArray(pointsList);
	stack = createStack();
	sortAngle(array);
	grahanScan(array,stack);
	destroyArray(array);
	while( ! isStackEmpty(stack) ){
		point = getObjData(pop(stack));
		polygonInsertNode( polygon, getPointX(point), getPointY(point) );
	}
	destroyStack(stack);

	setListFuncDestroyData(pointsList, destroyObjDataVoid);
	destroyList(pointsList);
}

void commandMoveCelular( char *line, Cidade *cidade, FILE *outFileTxt ){
	char opdest[STRING_SIZE], num[STRING_SIZE], *torreIdFrom;
	Operadora *opFrom, *opTo;
	Celular *celular;
	Endereco *endereco = NULL;
	Pessoa *pessoa;

	fputs( line, outFileTxt );

	sscanf( line, "mv %s %s", opdest, num );

	if( strcmp(opdest, "su") == 0 ){
		opFrom = getCidadeUelmobile(cidade);
		opTo = getCidadeSercomtuel(cidade);
	}
	else if( strcmp(opdest, "um") == 0 ){
		opFrom = getCidadeSercomtuel(cidade);
		opTo = getCidadeUelmobile(cidade);
	}
	else{
		return;
	}

	celular = searchOperadoraCelularNum( opFrom, num );
	if( celular == NULL ){
		fprintf( outFileTxt, "Numero %s nao existe na operadora de origem.\n\n", num );
		return;
	}

	if( searchOperadoraCelularNum( opTo, num ) ){
		fprintf( outFileTxt, "Numero %s ja existe na operadora destino\n\n", num );
		return;
	}

	pessoa = searchOperadoraClienteCpf( opFrom, getCelularCpf(celular) );
	torreIdFrom = createString(getCelularTorreId(celular));

	if(getCelularEndereco(celular)){
		endereco = operadoraDesconectaCelular( opFrom, celular );
	}
	operadoraRemoveCliente( opFrom, pessoa, celular );

	operadoraInsertCliente( opTo, pessoa, celular );
	fprintf( outFileTxt, "Celular %s, pertencente a pessoa %s, migrou de %s para a %s.", getCelularNumero(celular), getPessoaNome(pessoa), getOperadoraNome(opFrom), getOperadoraNome(opTo) );
	if( endereco != NULL ){
		Quadra *quadra = getObjData( searchCidadeQuadraCep( cidade, getEnderecoCep(endereco) ) );
		operadoraConectaCelular( opTo, celular, quadra, endereco );
		fprintf( outFileTxt, " Foi desconectado da rádio-base %s e reconectado na rádio-base %s.", torreIdFrom, getCelularTorreId(celular) );
	}
	fprintf( outFileTxt, "\n\n" );

	destroyString(torreIdFrom);
}

void commandConectaCelular( char *line, Cidade *cidade, FILE *outFileTxt ){
	char numcel[STRING_SIZE], cep[STRING_SIZE], face;
	int i, num;
	Operadora *op[2];
	Celular *celular;
	Quadra *quadra;
	Endereco *endereco;
	Pessoa *pessoa;
	Point *coords;
	Object *obj, *torre;
	double d;

	fputs(line, outFileTxt);

	sscanf( line, "con %s %s %c %d", numcel, cep, &face, &num );

	op[0] = getCidadeSercomtuel(cidade);
	op[1] = getCidadeUelmobile(cidade);
	for( i = 0; i < 2; i++ ){
		celular = searchOperadoraCelularNum( op[i], numcel );
		if( celular ){
			break;
		}
	}

	if( celular == NULL ){
		fprintf( outFileTxt, "Celular de numero %s nao encontrado em nenhuma das operadoras.\n\n", numcel );
		return;
	}

	obj = searchCidadeQuadraCep( cidade, cep );
	if( obj == NULL ){
		fprintf( outFileTxt, "Quadra de cep %s não encontrada.\n\n", cep );
		return;
	}
	quadra = getObjData(obj);

	if( checkFace(face) ){
		fprintf( outFileTxt, "Face invalida.\n\n" );
		return;
	}

	if( getCelularEndereco(celular) ){
		destroyEndereco(operadoraDesconectaCelular(op[i], celular));
	}

	endereco = createEndereco( cep, face, num, "" );
	operadoraConectaCelular( op[i], celular, quadra, endereco );

	pessoa = searchOperadoraClienteCpf( op[i], getCelularCpf(celular) );
	coords = getEnderecoCoords( endereco, quadra );
	torre = searchOperadoraTorreId( op[i], getCelularTorreId(celular) );
	d = distancePoints( getPointX(coords), getPointY(coords), getX(torre), getY(torre) );

	fprintf( outFileTxt, "Nome: %s %s, Cpf: %s, Operadora %s, Torre: %s, (%f,%f), %f\n\n", getPessoaNome(pessoa), getPessoaSobrenome(pessoa), getPessoaCpf(pessoa), getOperadoraNome(op[i]), getObjId(torre), getPointX(coords), getPointY(coords), d );

	destroyPoint(coords);
}

void commandLimpaRegion( char *line, Cidade *cidade, FILE *outFileTxt ){
	double x, y, width, height;
	Object *region;
	List *objs[4];
	Node *node;
	char *outString[4];
	int i;

	fputs(line, outFileTxt);

	sscanf( line, "dpr %lf %lf %lf %lf", &x, &y, &width, &height );

	region = createObject( "", 'r', createRect( 0, width, height, x, y, "") );

	objs[0] = searchCidadeObjTypeRegion( cidade, 'q', region );
	for( node = getFirst(objs[0]); node; node = getNext(node) ){
		Quadra *quadra = getObjData(get(node));
		Iterator *it;
		it = createIterator(getQuadraMoradores(quadra));
		while( iteratorHasNext(it) ){
			Pessoa *pessoa = iteratorNext(it);
			fprintf( outFileTxt, "Removido morador de CPF %s\n", getPessoaCpf(pessoa) );
		}
		destroyIterator(it);
		it = createIterator(getQuadraEstabComerciais(quadra));
		while( iteratorHasNext(it) ){
			Iterator *itCnpj = createIterator(iteratorNext(it));
			while(iteratorHasNext(itCnpj)){
				EstabComercial *estab = iteratorNext(itCnpj);
				fprintf( outFileTxt, "Removido estabelecimento comercial de CNPJ %s\n", getEstabComercialCNPJ(estab) );
			}
			destroyIterator(itCnpj);
		}
		destroyIterator(it);
	}
	destroyList(objs[0]);

	objs[0] = cidadeRemoveObjsRegion( cidade, 'q', region, NULL );
	objs[1] = cidadeRemoveObjsRegion( cidade, 'h', region, NULL );
	objs[2] = cidadeRemoveObjsRegion( cidade, 's', region, NULL );
	objs[3] = cidadeRemoveObjsRegion( cidade, 't', region, NULL );

	outString[0] = "Quadra %s removida\n";
	outString[1] = "Hidrante %s removido\n";
	outString[2] = "Semaforo %s removido\n";
	outString[3] = "Torre %s removida\n";

	for( i = 0; i < 4; i++ ){
		for( node = getFirst(objs[i]); node; node = getNext(node) ){
			Object *obj = get(node);
			fprintf( outFileTxt, outString[i], getObjId(obj) );
			destroyObjData(obj);
		}
		destroyList(objs[i]);
	}

	destroyObjData(region);

	fprintf( outFileTxt, "\n" );
}

void commandMatarPessoa( char *line, Cidade *cidade, FILE *outFileTxt ){
	char cpf[STRING_SIZE];
	Pessoa *pessoa;
	Endereco *endereco;
	Celular *celular;
	Operadora *operadora[2];
	int i;

	fputs(line,outFileTxt);

	sscanf( line, "rip %s", cpf );

	pessoa = searchCidadePessoaCpf(cidade, cpf);
	if( pessoa == NULL ){
		fprintf( outFileTxt, "Pessoa de CPF %s nao encontrada.\n\n", cpf );
		return;
	}

	fprintf( outFileTxt, "%s, portador CPF %s, do sexo %s, nascido à %s.\n", getPessoaNome(pessoa), getPessoaCpf(pessoa), getPessoaSexoString(pessoa), getPessoaNasc(pessoa) );

	endereco = getPessoaEndereco(pessoa);
	if(endereco){
		fprintf( outFileTxt, "Residia no endereço %s/%d/%c.\n", getEnderecoCep(endereco), getEnderecoNum(endereco), getEnderecoFace(endereco) );
	}

	operadora[0] = getCidadeSercomtuel(cidade);
	operadora[1] = getCidadeUelmobile(cidade);
	for( i = 0; i < 2; i++ ){
		if( operadoraIsPessoaCliente( operadora[i], pessoa ) ){
			celular = searchOperadoraCelularCpf( operadora[i], getPessoaCpf(pessoa) );
			fprintf( outFileTxt, "Usuário da linha móvel %s da operadora %s.\n", getCelularNumero(celular), getOperadoraNome(operadora[i]) );
			break;
		}
	}

	fprintf( outFileTxt, "\n" );

	cidadeMatarPessoa(cidade, pessoa);
}

void commandListaMoradoresQuadra( char *line, int commandId, Cidade *cidade, FILE *outFileTxt ){
	char cep[STRING_SIZE];
	double x, y, width, height;

	fputs(line,outFileTxt);

	if( commandId == 13 ){
		Object *obj;
		Quadra *quadra;
		sscanf( line, "m? %s", cep );
		obj = searchCidadeQuadraCep(cidade, cep);
	    if( obj == NULL ){
	        fprintf( outFileTxt, "Quadra de CEP %s nao encontrada.\n\n", cep );
	        return;
	    }
	    quadra = getObjData(obj);
		listarMoradoresQuadra(cidade, quadra, outFileTxt);
	}
	else if( commandId == 14 ){
		Object *region;
		List *list;
		Node *node;
		sscanf( line, "mr? %lf %lf %lf %lf", &x, &y, &width, &height );
		region = createObject( "", 'r', createRect( 0, width, height, x, y, "" ));

		list = searchCidadeObjTypeRegion(cidade, 'q', region);
		node = getFirst(list);
		while(node){
			listarMoradoresQuadra(cidade, getObjData(get(node)), outFileTxt);
			node = getNext(node);
		}
		destroyList(list);

		destroyObjData(region);
	}
	else{
		return;
	}

	fprintf( outFileTxt, "\n" );
}

static void listarMoradoresQuadra( Cidade *cidade, Quadra *quadra, FILE *outFileTxt ){
	Iterator *it = createIterator(getQuadraMoradores(quadra));
	while(iteratorHasNext(it)){
	    Pessoa *pessoa = iteratorNext(it);
	    Endereco *endereco = getPessoaEndereco(pessoa);
	    Operadora *operadora = getCidadeOperadoraPessoa(cidade, pessoa);

	    fprintf( outFileTxt, "Nome: %s %s;", getPessoaNome(pessoa), getPessoaSobrenome(pessoa) );
	    if(endereco){
	        fprintf( outFileTxt, " Endereco: %s/%c/%d;", getEnderecoCep(endereco), getEnderecoFace(endereco), getEnderecoNum(endereco) );
	    }

	    if(operadora){
	        fprintf( outFileTxt, " Operadora: %s", getOperadoraNome(operadora) );
	    }
	    fprintf( outFileTxt, "\n" );
	}
	destroyIterator(it);
}

void commandDumpDadosMorador( char *line, Cidade *cidade, FILE *outFileTxt ){
	char cpf[STRING_SIZE];
	Pessoa *pessoa;

	fputs(line,outFileTxt);

	sscanf( line, "dm? %s", cpf );

	pessoa = searchCidadePessoaCpf( cidade, cpf );
	if(pessoa){
	    Endereco *endereco = getPessoaEndereco(pessoa);
	    Operadora *operadora = getCidadeOperadoraPessoa(cidade, pessoa);
	    fprintf( outFileTxt, "Nome: %s %s, Cpf: %s, Nascimento: %s, Sexo: %c\n",
			getPessoaNome(pessoa),
			getPessoaSobrenome(pessoa),
			getPessoaCpf(pessoa),
			getPessoaNasc(pessoa),
			getPessoaSexo(pessoa)
		);
	    if(endereco){
	        Point *coords = getEnderecoCoords(endereco, getObjData(searchCidadeQuadraCep(cidade, getEnderecoCep(endereco))));
	        fprintf( outFileTxt, "Endereco: %s/%c/%d, Coords: %f,%f\n", getEnderecoCep(endereco), getEnderecoFace(endereco), getEnderecoNum(endereco), getPointX(coords), getPointY(coords) );
	        destroyPoint(coords);
	    }
	    if(operadora){
	        fprintf( outFileTxt, "Operadora: %s, Celular: %s\n", getOperadoraNome(operadora), getCelularNumero(searchOperadoraCelularCpf(operadora, getPessoaCpf(pessoa))) );
	    }
	}
	else{
	    fprintf( outFileTxt, "Pessoa de cpf %s não encontrada.\n", cpf );
	}

	fprintf( outFileTxt, "\n" );
}

void commandDumpDadosEstabComercial( char *line, Cidade *cidade, FILE *outFileTxt ){
	char cnpj[STRING_SIZE];
	EstabComercial *estab;

	fputs(line,outFileTxt);

	sscanf( line, "de? %s", cnpj );

	estab = searchCidadeEstabComercialCnpj( cidade, cnpj );
	if(estab){
		fprintf( outFileTxt, "Nome: %s, Cnpj: %s, Codt: %s, Endereco: %s/%c/%d\n\n",
			getEstabComercialNome(estab),
			getEstabComercialCNPJ(estab),
			getEstabComercialCodt(estab),
			getEstabComercialCep(estab),
			getEstabComercialFace(estab),
			getEstabComercialNum(estab)
		);
	}
	else{
		fprintf( outFileTxt, "Estabelecimento comercial de CNPJ %s nao encontrado.\n\n", cnpj );
	}
}

void commandDumpMoradoresSexoCodtRegion( char *line, Cidade *cidade, FILE *outFileTxt ){
	char sexo, codt[STRING_SIZE];
	double x, y, width, height;
	Object *region;
	List *list;
	Node *node;

	fputs(line,outFileTxt);

	sscanf( line, "mse? %c %s %lf %lf %lf %lf", &sexo, codt, &x, &y, &width, &height );

	if( sexo != 'M' && sexo != 'F' ){
		fprintf( outFileTxt, "Sexo invalido.\n\n" );
		return;
	}

	if( ! searchCidadeDescricaoCodt( cidade, codt ) ){
		fprintf( outFileTxt, "Codt %s nao existe.\n\n", codt );
		return;
	}

	region = createObject( "", 'r', createRect( 0, width, height, x, y, "" ) );
	list = searchCidadeObjTypeRegion( cidade, 'q', region );
	for( node = getFirst(list); node; node = getNext(node) ){
		Quadra *quadra = getObjData(get(node));
		if( searchHashTable( getQuadraEstabComerciais(quadra), codt ) ){
			HashTable *moradores = getQuadraMoradores(quadra);
			Iterator *it = createIterator(moradores);
			while(iteratorHasNext(it)){
				Pessoa *pessoa = iteratorNext(it);
				if( getPessoaSexo(pessoa) == sexo ){
					Endereco *endereco = getPessoaEndereco(pessoa);
					fprintf( outFileTxt, "Nome: %s %s, Endereco: %s/%c/%d\n",
						getPessoaNome(pessoa),
						getPessoaSobrenome(pessoa),
						getEnderecoCep(endereco),
						getEnderecoFace(endereco),
						getEnderecoNum(endereco)
					);
				}
			}
			destroyIterator(it);
		}
	}
	destroyList(list);
	destroyObjData(region);

	fprintf( outFileTxt, "\n" );
}

void commandDumpConexoesTorre( char *line, Cidade *cidade, FILE *outFileTxt ){
	char torreId[STRING_SIZE];
	Operadora **operadoras;
	int i;

	fputs( line, outFileTxt );

	sscanf( line, "lk? %s", torreId );

	if( ! searchCidadeTorreId(cidade, torreId) ){
		fprintf( outFileTxt, "Torre %s nao existe.\n\n", torreId );
		return;
	}

	operadoras = getCidadeOperadoras(cidade);
	for( i = 0; i < 2; i++ ){
		if( searchOperadoraTorreId(operadoras[i], torreId) ){
			dumpConexoesTorre(operadoras[i], torreId, outFileTxt);
			break;
		}
	}

	fprintf( outFileTxt, "\n" );
}

static void dumpConexoesTorre( Operadora *operadora, char *torreId, FILE *outFileTxt ){
	HashTable *conexoes = searchOperadoraConexoesTorreId(operadora, torreId);
	fprintf( outFileTxt, "%s: ", torreId );
	if(conexoes){
		Iterator *it = createIterator(conexoes);
		if( iteratorHasNext(it) ){
			fprintf( outFileTxt, "%s", getCelularNumero(iteratorNext(it)) );
			while( iteratorHasNext(it) ){
				fprintf( outFileTxt, ", %s", getCelularNumero(iteratorNext(it)) );
			}
		}
		destroyIterator(it);
	}
	fprintf( outFileTxt, ";\n" );
}

void commandTorreCelularConectado( char *line, Cidade *cidade, FILE *outFileTxt ){
	char numcel[STRING_SIZE];
	Celular *celular;

	fputs(line, outFileTxt);

	sscanf( line, "rb? %s", numcel );

	celular = searchOperadoraCelularNum( getCidadeSercomtuel(cidade), numcel );
	if( ! celular ){
	    celular = searchOperadoraCelularNum( getCidadeUelmobile(cidade), numcel );
	}
	if( ! celular ){
	    fprintf( outFileTxt, "Celular de numero %s nao encontrado.\n\n", numcel );
	    return;
	}

	if( getCelularEndereco(celular) ){
	    fprintf( outFileTxt, "%s\n\n", getCelularTorreId(celular) );
	}
	else{
	    fprintf( outFileTxt, "Celular nao conectado.\n\n" );
	}
}

void commandListaClientesOperadora( char *line, Cidade *cidade, FILE *outFileTxt ){
	char op[STRING_SIZE];
	int n, i, size;
	void **data;
	Operadora *operadora;
	Array *array;
	Tokens *tokens;

	fputs(line, outFileTxt);

	tokens = createTokens(DELIMITERS);
	defineTokens( tokens, line );

	sscanf( line, "co? %s", op );

	if( strcmp( op, "su" ) == 0 ){
	    operadora = getCidadeSercomtuel(cidade);
	}
	else if( strcmp( op, "um" ) == 0 ){
	    operadora = getCidadeUelmobile(cidade);
	}

	array = hashTableToArray(getOperadoraClientes(operadora));
	size = getArraySize(array);
	data = getArrayData(array);
	quickSort( data, 0, size-1, comparatorClientesOrdemNome, NULL );

	if( getToken(tokens, 2) ){
	    n = atoi(getToken(tokens, 2));
	    if( n < size ){
	        size = n;
	    }
	}

	for( i = 0; i < size; i++ ){
	    Pessoa *pessoa = data[i];
	    Celular *celular = searchOperadoraCelularCpf(operadora, getPessoaCpf(pessoa));
	    fprintf( outFileTxt, "Nome: %s %s, Celular: %s \n", getPessoaNome(pessoa), getPessoaSobrenome(pessoa), getCelularNumero(celular) );
	}
	fprintf( outFileTxt, "\n" );

	destroyArray(array);
	destroyTokens(tokens);
}

static int comparatorClientesOrdemNome( void *a, void *b, void *aux ){
	char *nomeA, *nomeB;
	int ret;

	destroyString(aux);

	nomeA = createStringCat( 3, getPessoaNome(a), " ", getPessoaSobrenome(a) );
	nomeB = createStringCat( 3, getPessoaNome(b), " ", getPessoaSobrenome(b) );

	ret = strcmp(nomeA, nomeB);

	destroyString(nomeA);
	destroyString(nomeB);

	return ret;
}

void commandListaConexoesTorresRegion( char *line, Cidade *cidade, FILE *outFileTxt ){
	double x, y, width, height;
	char *op;
	Tokens *tokens;
	List *torresSu, *torresUm;
	Object *region;
	Node *node;

	fputs( line, outFileTxt );

	sscanf( line, "lnr? %lf %lf %lf %lf", &x, &y, &width, &height );

	tokens = createTokens(DELIMITERS);
	defineTokens(tokens, line);

	region = createObject( "", 'r', createRect( 0, width, height, x, y, "" ) );

	op = getToken(tokens, 5);
	if(op){
		if( strcmp(op, "su") == 0 ){
			torresSu = searchOperadoraTorresRegion( getCidadeSercomtuel(cidade), region );
			torresUm = NULL;
		}
		else if( strcmp(op, "um") == 0 ){
			torresUm = searchOperadoraTorresRegion( getCidadeUelmobile(cidade), region );
			torresSu = NULL;
		}
	}
	else{
		torresSu = searchOperadoraTorresRegion( getCidadeSercomtuel(cidade), region );
		torresUm = searchOperadoraTorresRegion( getCidadeUelmobile(cidade), region );
	}

	if(torresSu){
		for( node = getFirst(torresSu); node; node = getNext(node) ){
			dumpConexoesTorre( getCidadeSercomtuel(cidade), getObjId(get(node)), outFileTxt );
		}
		destroyList(torresSu);
	}

	if(torresUm){
		for( node = getFirst(torresUm); node; node = getNext(node) ){
			dumpConexoesTorre( getCidadeUelmobile(cidade), getObjId(get(node)), outFileTxt );
		}
		destroyList(torresUm);
	}

	fprintf( outFileTxt, "\n" );

	destroyObjData(region);
	destroyTokens(tokens);
}

void commandListaEstabComerciaisQuadra( char *line, Cidade *cidade, FILE *outFileTxt ){
	char cep[STRING_SIZE];
	Quadra *quadra;
	Object *obj;
	Iterator *itCodt, *itCnpj;

	fputs(line, outFileTxt);

	sscanf( line, "ecq? %s", cep );

	obj = searchCidadeQuadraCep(cidade, cep);
	if( ! obj ){
		fprintf( outFileTxt, "Quadra nao existe.\n\n" );
		return;
	}
	quadra = getObjData(obj);

	itCodt = createIterator(getQuadraEstabComerciais(quadra));
	while( iteratorHasNext(itCodt) ){
		HashTable *ht = iteratorNext(itCodt);
		itCnpj = createIterator(ht);
		while( iteratorHasNext(itCnpj) ){
			dumpDadosEstabComercial( iteratorNext(itCnpj), outFileTxt );
		}
		destroyIterator(itCnpj);
	}
	destroyIterator(itCodt);
	fprintf( outFileTxt, "\n" );
}

static void dumpDadosEstabComercial( EstabComercial *estab, FILE *outFileTxt ){
	fprintf( outFileTxt, "Cnpj: %s, Nome: %s, Tipo: %s, Endereco %s/%c/%d\n",
		getEstabComercialCNPJ(estab),
		getEstabComercialNome(estab),
		getEstabComercialCodt(estab),
		getEstabComercialCep(estab),
		getEstabComercialFace(estab),
		getEstabComercialNum(estab)
	);
}

void commandListaEstabComerciaisTipoRegion( char *line, Cidade *cidade, FILE *outFileTxt ){
	char codt[STRING_SIZE];
	double x, y, width, height;
	Tokens *tokens;
	Object *region = NULL;
	List *quadras;
	Node *node;

	fputs(line, outFileTxt);

	sscanf( line, "ecr? %s", codt );

	if( ! searchCidadeDescricaoCodt(cidade, codt) ){
		fprintf( outFileTxt, "Tipo nao definido.\n" );
		return;
	}

	tokens = createTokens(DELIMITERS);
	defineTokens(tokens, line);

	if( getToken(tokens, 2) ){
		sscanf( getToken(tokens, 2), "%lf", &x );
		sscanf( getToken(tokens, 3), "%lf", &y );
		sscanf( getToken(tokens, 4), "%lf", &width );
		sscanf( getToken(tokens, 5), "%lf", &height );
		region = createObject( "", 'r', createRect( 0, width, height, x, y, "" ) );
	}

	quadras = searchCidadeObjTypeRegion(cidade, 'q', region);
	for( node = getFirst(quadras); node; node = getNext(node) ){
		Quadra *quadra = getObjData(get(node));
		HashTable *ht = searchHashTable( getQuadraEstabComerciais(quadra), codt );
		if(ht){
			Iterator *it = createIterator(ht);
			while(iteratorHasNext(it)){
				dumpDadosEstabComercial(iteratorNext(it), outFileTxt);
			}
			destroyIterator(it);
		}
	}
	destroyList(quadras);

	fprintf( outFileTxt, "\n" );

	if(region) destroyObjData(region);

	destroyTokens(tokens);
}

void commandListaTiposCep( char *line, Cidade *cidade, FILE *outFileTxt ){
	char cep[STRING_SIZE];
	Object *obj;

	fputs(line, outFileTxt);

	sscanf( line, "tecq? %s", cep );

	obj = searchCidadeQuadraCep(cidade, cep);
	if( ! obj ){
		fprintf( outFileTxt, "Quadra nao existe.\n\n" );
	}
	else{
		Quadra *quadra = getObjData(obj);
		Iterator *itCodt, *itCnpj;

		itCodt = createIterator(getQuadraEstabComerciais(quadra));
		while( iteratorHasNext(itCodt) ){
			HashTable *ht = iteratorNext(itCodt);
			fprintf( outFileTxt, "%s: ", iteratorKey(itCodt) );

			itCnpj = createIterator(ht);
			fprintf( outFileTxt, "%s", getEstabComercialNome( iteratorNext(itCnpj) ) );
			while( iteratorHasNext(itCnpj) ){
				fprintf( outFileTxt, ", %s", getEstabComercialNome( iteratorNext(itCnpj) ) );
			}
			destroyIterator(itCnpj);
			fprintf( outFileTxt, "\n" );
		}
		destroyIterator(itCodt);

		fprintf( outFileTxt, "\n" );
	}
}

void commandListaTiposRegion( char *line, Cidade *cidade, FILE *outFileTxt ){
	double x, y, width, height;
	List *quadras;
	Node *node;
	Object *region;
	HashTable *codt;
	Iterator *it;

	fputs(line, outFileTxt);

	sscanf( line, "tecr? %lf %lf %lf %lf", &x, &y, &width, &height );

	region = createObject( "", 'r', createRect( 0, width, height, x, y, "" ) );
	quadras = searchCidadeObjTypeRegion(cidade, 'q', region);
	destroyObjData(region);

	codt = createHashTable(HT_SIZE);

	for( node = getFirst(quadras); node; node = getNext(node) ){
		it = createIterator(getQuadraEstabComerciais(getObjData(get(node))));
		while(iteratorHasNext(it)){
			iteratorNext(it);
			insertHashTable( codt, iteratorKey(it), NULL );
		}
		destroyIterator(it);
	}

	it = createIterator(codt);
	while(iteratorHasNext(it)){
		iteratorNext(it);
		fprintf( outFileTxt, "%s\n", iteratorKey(it) );
	}
	destroyIterator(it);

	destroyHashTable(codt);

	destroyList(quadras);

	fprintf( outFileTxt, "\n" );
}

void commandDadosUsuarioLinhaMovel( char *line, int commandId, Cidade *cidade, FILE *outFileTxt ){
	char num[STRING_SIZE];
	Celular *celular;
	Pessoa *pessoa;
	Operadora **operadoras;
	int i;

	fputs(line, outFileTxt);

	sscanf( line, "%*s %s", num );

	operadoras = getCidadeOperadoras(cidade);

	for( i = 0; i < 2; i++ ){
		celular = searchOperadoraCelularNum( operadoras[i], num );
		if(celular){
			pessoa = searchOperadoraClienteCpf(operadoras[i], getCelularCpf(celular));
			break;
		}
	}

	if( ! celular ){
		fprintf( outFileTxt, "Celular nao existe.\n\n" );
		return;
	}

	if( commandId == 29 || commandId == 30 ){
		if( ! getCelularEndereco(celular) ){
			fprintf( outFileTxt, "Celular nao conectado.\n\n" );
			return;
		}
	}

	fprintf( outFileTxt, "Nome: %s %s, Cpf: %s", getPessoaNome(pessoa), getPessoaSobrenome(pessoa), getPessoaCpf(pessoa) );

	if( commandId == 28 ){
		fprintf( outFileTxt, ", Operadora: %s", getOperadoraNome(operadoras[i]) );
	}
	else if( commandId == 29 ){
		Endereco *endereco = getCelularEndereco(celular);
		fprintf( outFileTxt, ", Endereco: %s/%c/%d", getEnderecoCep(endereco), getEnderecoFace(endereco), getEnderecoNum(endereco) );
	}
	else if( commandId == 30 ){
		Endereco *endereco = getCelularEndereco(celular);
		Quadra *quadra = getObjData(searchCidadeQuadraCep(cidade, getEnderecoCep(endereco)));
		Point *coords = getEnderecoCoords(endereco, quadra);
		fprintf( outFileTxt, ", Coordenadas: %f,%f", getPointX(coords), getPointY(coords) );
		destroyPoint(coords);
	}

	fprintf( outFileTxt, "\n\n" );
}

void commandRegistrador( char *line, int commandId, Cidade *cidade, FILE *outFileTxt ){
	Point *coords = NULL;
	Endereco *endereco = NULL;
	Quadra *quadra = NULL;
	char registrador[STRING_SIZE];

	fputs(line, outFileTxt);

	if(commandId == 32){
	    Celular *celular = NULL;
	    Operadora **ops = getCidadeOperadoras(cidade);
	    int i;
	    char num[STRING_SIZE];

	    sscanf( line, "@f? %s %s", registrador, num );

	    for( i = 0; i < 2; i++ ){
	        celular = searchOperadoraCelularNum(ops[i], num);
	        if(celular){
	            break;
	        }
	    }

	    if(!celular){
	        fprintf( outFileTxt, "Celular nao existe.\n\n" );
	        return;
	    }

	    endereco = getCelularEndereco(celular);
	    if(!endereco){
	        fprintf( outFileTxt, "Celular nao conectado.\n\n" );
	        return;
	    }
	}
	else if(commandId == 33){
	    Pessoa *pessoa = NULL;
	    char cpf[STRING_SIZE];

	    sscanf( line, "@m? %s %s", registrador, cpf );

	    pessoa = searchCidadePessoaCpf(cidade, cpf);

	    if(!pessoa){
	        fprintf( outFileTxt, "Pessoa nao existe.\n\n" );
	        return;
	    }

	    endereco = getPessoaEndereco(pessoa);
	    if(!endereco){
	        fprintf( outFileTxt, "Pessoa nao e morador.\n\n" );
	        return;
	    }
	}
	else if(commandId == 34){
	    char cep[STRING_SIZE], face;
	    int num;
	    Object *obj = NULL;

	    sscanf( line, "@e? %s %s %c %d", registrador, cep, &face, &num );

	    obj = searchCidadeQuadraCep(cidade, cep);
	    if(!obj){
	        fprintf( outFileTxt, "Cep nao existe.\n\n" );
	        return;
	    }
	    quadra = getObjData(obj);

	    endereco = createEndereco(cep, face, num, "");
	    coords = getEnderecoCoords(endereco, quadra);
	    destroyEndereco(endereco);
	    endereco = NULL;
	}
	else if(commandId == 35){
		char id[STRING_SIZE];
		Object *obj;
		char *type = "hst";
		int i;

		sscanf( line, "@g? %s %s", registrador, id );

		for( i = 0; i < 3; i++ ){
			obj = searchCidadeObjTypeIdCep(cidade, type[i], id);
			if(obj){
				break;
			}
		}

		if(!obj){
			fprintf( outFileTxt, "Equipamento %s nao encontrado.\n\n", id );
			return;
		}

		coords = createPoint( getX(obj), getY(obj), getObjId(obj), "", "");
	}
	else if(commandId == 36){
	    double x, y;

	    sscanf( line, "%*s %s %lf %lf", registrador, &x, &y );

	    coords = createPoint(x, y, "", "", "");
	}
	else if(commandId == 37){
	    char registrador2[STRING_SIZE], codt[STRING_SIZE];
		Point *coordsRegist;
		Iterator *it;
		List *list;
		QuadTree *qt;
		EstabComercial *estab;
		Object *obj;

	    sscanf( line, "@tp? %s %s %s", registrador, codt, registrador2 );

		coordsRegist = cidadeGetRegistrador(cidade, registrador2);
		if(!coordsRegist){
			fprintf( outFileTxt, "Registrador r2 nao definido.\n\n" );
			return;
		}

	    if(!searchCidadeDescricaoCodt(cidade, codt)){
			fprintf( outFileTxt, "Tipo nao existe.\n\n" );
			return;
		}

		list = createList();

		it = createIterator(getCidadeEstabComerciais(cidade));
		while(iteratorHasNext(it)){
			estab = iteratorNext(it);
			if( strcmp(codt, getEstabComercialCodt(estab)) == 0 ){
				endereco = getEstabComercialEndereco(estab);
				quadra = getObjData(searchCidadeQuadraCep(cidade, getEnderecoCep(endereco)));
				coords = getEnderecoCoords(endereco, quadra);
				insert(list, createObject(getEstabComercialCNPJ(estab), '\0', coords));
			}
		}
		destroyIterator(it);

		qt = createQuadTree();
		listToQt(list, qt, getCidadeMethod(cidade));
		destroyList(list);

		if(isQuadTreeEmpty(qt)){
			fprintf( outFileTxt, "Nao existe estabelecimento comercial do tipo inserido.\n\n" );
			destroyObjQuadTree(qt);
			return;
		}

		obj = searchQuadTreeNearestToPoint(getPointX(coordsRegist), getPointY(coordsRegist), qt);
		estab = searchCidadeEstabComercialCnpj(cidade, getObjId(obj));
		endereco = getEstabComercialEndereco(estab);

		destroyObjQuadTree(qt);
	}

	if(endereco){
		quadra = getObjData(searchCidadeQuadraCep(cidade, getEnderecoCep(endereco)));
		coords = getEnderecoCoords(endereco, quadra);
	}

	cidadeSetRegistrador(cidade, registrador, getPointX(coords), getPointY(coords));

	destroyPoint(coords);

	fprintf( outFileTxt, "\n" );
}

void commandDijkstra( char *line, Tokens *tokens, Cidade *cidade, FILE *outFileTxt, char *nameFileGeo, char *outDir ){
	Graph *graph = getCidadeMalhaViaria(cidade);
	char *tipoSaida, *sufixo, *r1, *r2, *cor, *peso;
	Iterator *it, *it2;
	Vertex *source, *target;
	Point *pointR1, *pointR2;
	List *percurso;

	if( strcmp(getToken(tokens, 0), "p?") != 0 ){
		return;
	}

	fputs(line, outFileTxt);

	tipoSaida = getToken(tokens, 1);
	if(tipoSaida[0] == 't'){
		sufixo = NULL;
		peso = getToken(tokens, 2);
		r1 = getToken(tokens, 3);
		r2 = getToken(tokens, 4);
		cor = NULL;
	}
	else if(tipoSaida[0] == 'p'){
		sufixo = getToken(tokens, 2);
		peso = getToken(tokens, 3);
		r1 = getToken(tokens, 4);
		r2 = getToken(tokens, 5);
		cor = getToken(tokens, 6);
	}
	else{
		return;
	}

	pointR1 = cidadeGetRegistrador(cidade, r1);
	pointR2 = cidadeGetRegistrador(cidade, r2);

	if(!pointR1){
		fprintf( outFileTxt, "Registrador %s nao definido.\n\n", r1 );
		return;
	}
	if(!pointR2){
		fprintf( outFileTxt, "Registrador %s nao definido.\n\n", r2 );
		return;
	}

	it = createIterator(getGraphEdges(graph));
	while(iteratorHasNext(it)){
		it2 = createIterator(iteratorNext(it));
		while(iteratorHasNext(it2)){
			Edge *edge = iteratorNext(it2);
			Rua *rua = getEdgeData(edge);
			double value;
			if(peso[0] == 'D'){
				value = getRuaCmp(rua);
			}
			else if(peso[0] == 'T'){
				value = getRuaTempo(rua);
			}
			setEdgeLength(edge, value);
		}
		destroyIterator(it2);
	}
	destroyIterator(it);

	source = searchVertex(graph, getObjId(searchQuadTreeNearestToPoint(getPointX(pointR1), getPointY(pointR1), getCidadeVerticesQT(cidade))));
	target = searchVertex(graph, getObjId(searchQuadTreeNearestToPoint(getPointX(pointR2), getPointY(pointR2), getCidadeVerticesQT(cidade))));
	percurso = dijkstra(graph, source, target);

	if(!percurso){
		fprintf( outFileTxt, "Nao existe percurso para os dois registradores.\n" );
	}
	else{
		if(tipoSaida[0] == 't'){
			Node *node;
			for( node = getFirst(percurso); node; node = getNext(node) ){
				fprintf( outFileTxt, "%s\n", getPointId(getVertexData((get(node)))) );
			}
		}
		else if(tipoSaida[0] == 'p'){
			char *fullPath = createStringCat(5, outDir, nameFileGeo, "-", sufixo, ".svg");
			FILE *svg = openFileWrite(fullPath);
			Node *node;
			Point *point;

			if(svg){
				writeSvgStart(svg);

				writeCidadeTags(cidade, svg);

				writeAnchorTag( getPointId(pointR1), getPointX(pointR1), getPointY(pointR1), ANCHOR_RADIUS, "blue", ANCHOR_OPACITY, svg );
				writeAnchorTag( getPointId(pointR2), getPointX(pointR2), getPointY(pointR2), ANCHOR_RADIUS, "blue", ANCHOR_OPACITY, svg );

				node = getFirst(percurso);
				if(node){
					point = getVertexData(get(node));
					fprintf( svg, "\t<path stroke=\"%s\" stroke-width=\"3\" fill=\"none\" d=\"M %f %f", cor, getPointX(point), getPointY(point) );
					while(node){
						point = getVertexData(get(node));
						fprintf( svg, " L %f %f", getPointX(point), getPointY(point) );
						node = getNext(node);
					}
					fprintf( svg, "\" />\n" );
				}

				/*point = getVertexData(source);
				writeAnchorTag( getPointId(point), getPointX(point), getPointY(point), ANCHOR_RADIUS, cor, ANCHOR_OPACITY, svg );
				point = getVertexData(target);
				writeAnchorTag( getPointId(point), getPointX(point), getPointY(point), ANCHOR_RADIUS, cor, ANCHOR_OPACITY, svg );*/

				writeSvgEnd(svg);
			}
			closeFile(svg);
			destroyString(fullPath);
		}
		destroyList(percurso);
	}


	fprintf( outFileTxt, "\n" );
}
