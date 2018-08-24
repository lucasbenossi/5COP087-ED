#include "CommandsDebug.h"
#include "LinkedList.h"
#include "Array.h"
#include "Stack.h"
#include "QuadTree.h"
#include "QuadTreeSearch.h"
#include "Object.h"
#include "Cidade.h"
#include "EstabComercial.h"
#include "Pessoa.h"
#include "Operadora.h"
#include "Celular.h"
#include "Endereco.h"
#include "String.h"
#include "File.h"
#include "ConvexHull.h"
#include "WriteTags.h"
#include "ObjData.h"
#include "ObjQuadTree.h"
#include "QuadTreeDump.h"
#include "HashTable.h"
#include "HashTableDump.h"
#include "Graph.h"
#include "GraphDump.h"
#include "Geometry.h"
#include "Rua.h"
#include <stdio.h>
#include <stdlib.h>

static void dumpCidadeTxt( Cidade *cidade, char *outDir );

static void dumpQuadrasTxt( HashTable *quadrasHT, char *outDir );

static void dumpPointTxt( HashTable *objHT, char *obj, char *outDir, char *fileName );

static void dumpEstabComerciaisTxt( HashTable *estabComerciais, char *outDir );

static void dumpPessoasTxt( HashTable *pessoas, char *type, char *outDir, char *fileName );

static void dumpOperadoraTxt( Operadora *op, char *outDir );

static void dumpCidadeDataStructuresDot( Cidade *cidade, char *outDir );

static void dumpObjsTxt( List *objs, char *outDir );

static void dumpMalhaViariaSvg( Cidade *cidade, char *outDir );

static void dumpRuasTxt( Cidade *cidade, char *outDir );

static void dumpRegistradoresTxt( Cidade *cidade, char *outDir );

static void dumpRegistradoresSvg( Cidade *cidade, char *outDir );

/* ========================================================================== */

void convexHull( char *arg, int collinear, List *objs, Cidade *cidade, char *file, char *fixedDir ){
	List *objList, *chList, *polygonList;
	Array *array;
	Stack *stack;
	Node *node;
	char *fullPath, *fullPathSvg, *fullPathTxt;
	FILE *svg, *txt;
	Object *obj;
	int error;
	double x, y;
	Polygon *polygon;

	error = 0;
	txt = NULL;

	if( arg[0] == 'q' ){
		objList = getCidadeQuadrasList(cidade);
	}
	else if( arg[0] == 'h' ){
		objList = getCidadeHidrantesList(cidade);
	}
	else if( arg[0] == 's' ){
		objList = getCidadeSemaforosList(cidade);
	}
	else if( arg[0] == 't' ){
		objList = getCidadeTorresList(cidade);
	}
	else if( arg[0] == 'c' || arg[0] == 'r' ){
		objList = objs;
	}
	else if( arg[0] == 'v' ){
		objList = getCidadeVerticesList(cidade);
	}

	if( collinear == 1 ){
		fullPath = createStringCat( 3, fixedDir, file, "-convexhullcollinear" );
	}
	else{
		fullPath = createStringCat( 3, fixedDir, file, "-convexhull" );
	}
	fullPathSvg = createStringCat( 2, fullPath, ".svg" );
	fullPathTxt = createStringCat( 2, fullPath, ".txt" );

	svg = openFileWrite(fullPathSvg);
	if( svg == NULL ){
		error++;
		return;
	}

	if( error == 0 ){
		txt = openFileWrite(fullPathTxt);
	    if( txt == NULL ){
			error++;
			return;
	    }
	}

	if( error == 0 ){
		array = listToArray(objList);

		chList = createList();
		if( getArraySize(array) > 0 ){
			if( collinear == 1 ){
				while( sortAngleCollinear(array) == 0 ){
					stack = createStack();
					grahanScanCollinear(array,stack);
					insert(chList,stack);
				}
			}
			else{
				while( sortAngle(array) == 0 ){
					stack = createStack();
					grahanScan(array,stack);
					insert(chList,stack);
				}
			}
		}

		destroyArray(array);

		polygonList = createList();
		while( ! isListEmpty(chList) ){
			stack = removeLast(chList);
			polygon = createPolygon("","none","black");
			while( ! isStackEmpty(stack) ){
				obj = pop(stack);
				x = getX(obj);
				y = getY(obj);
				fprintf( txt, "%f %f %s\n", x, y, getObjId(obj) );
				polygonInsertNode(polygon,x,y);
			}
			fprintf( txt, "\n" );
			insert(polygonList,polygon);
			destroyStack(stack);
		}

		destroyList(chList);

		writeSvgStart(svg);
		for( node = getFirst(objList); node; node = getNext(node) ){
			obj = get(node);
			writeAnchorTag( getObjId(obj), getX(obj), getY(obj), ANCHOR_RADIUS, "green", ANCHOR_OPACITY, svg );
		}

		while( ! isListEmpty(polygonList) ){
			polygon = removeFirst(polygonList);
			writePolygonTag(polygon,svg);
			destroyPolygon(polygon);
		}

		destroyList(polygonList);

		writeSvgEnd(svg);
	}

	closeFile(svg);
	closeFile(txt);

	destroyString(fullPath);
	destroyString(fullPathTxt);
	destroyString(fullPathSvg);
}

void dumpData( List *objs, Cidade *cidade, char *outDir ){
	outDir = fixDir(outDir);

	dumpCidadeTxt( cidade, outDir );

	dumpQuadrasTxt( getCidadeQuadrasHT(cidade), outDir );
	dumpPointTxt( getCidadeHidrantesHT(cidade), "Hidrante", outDir, "Hidrantes" );
	dumpPointTxt( getCidadeSemaforosHT(cidade), "Semaforo", outDir, "Semaforos" );
	dumpPointTxt( getCidadeTorresHT(cidade), "Torre", outDir, "Torres" );
	dumpEstabComerciaisTxt( getCidadeEstabComerciais(cidade), outDir );
	dumpPessoasTxt( getCidadePessoas(cidade), "Pessoa", outDir, "Pessoas" );
	dumpPessoasTxt( getCidadeDefuntos(cidade), "Defunto", outDir, "Defuntos" );
	dumpOperadoraTxt( getCidadeSercomtuel(cidade), outDir );
	dumpOperadoraTxt( getCidadeUelmobile(cidade), outDir );
	dumpMalhaViariaSvg( cidade, outDir );
	dumpRuasTxt(cidade, outDir);
	dumpRegistradoresTxt( cidade, outDir );
	dumpRegistradoresSvg( cidade, outDir );

	dumpCidadeDataStructuresDot( cidade, outDir );

	dumpObjsTxt( objs, outDir );

	destroyString(outDir);
}

static void dumpCidadeTxt( Cidade *cidade, char *outDir ){
	char *fullPath;
	FILE *outTxt;

	fullPath = createStringCat( 2, outDir, "Cidade.txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		fprintf( outTxt, "Cidade %p {\n", (void*)cidade );
		fprintf( outTxt, "\tnome: %s;\n", getCidadeNome(cidade) );
		fprintf( outTxt, "\tquadrasFill: %s;\n", getCidadeQuadrasFill(cidade) );
		fprintf( outTxt, "\tquadrasStroke: %s;\n", getCidadeQuadrasStroke(cidade) );
		fprintf( outTxt, "\thidrantesFill: %s;\n", getCidadeHidrantesFill(cidade) );
		fprintf( outTxt, "\thidrantesStroke: %s;\n", getCidadeHidrantesStroke(cidade) );
		fprintf( outTxt, "\tsemaforosFill: %s;\n", getCidadeSemaforosFill(cidade) );
		fprintf( outTxt, "\tsemaforosStroke: %s;\n", getCidadeSemaforosStroke(cidade) );
		fprintf( outTxt, "\ttorresFill: %s;\n", getCidadeTorresFill(cidade) );
		fprintf( outTxt, "\ttorresStroke: %s;\n", getCidadeTorresStroke(cidade) );
		fprintf( outTxt, "\tmethod: %d\n", getCidadeMethod(cidade) );
		fprintf( outTxt, "}\n\n" );
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpQuadrasTxt( HashTable *quadrasHT, char *outDir ){
	Quadra *quadra;
	char *fullPath;
	FILE *outTxt;
	Iterator *itQuadras, *itCodt, *itCnpj, *itCpf;

	fullPath = createStringCat( 2, outDir, "Quadras.txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		itQuadras = createIterator(quadrasHT);
		while( iteratorHasNext(itQuadras) ){
			quadra = getObjData( iteratorNext(itQuadras) );

			fprintf( outTxt, "Quadra %p {\n", (void*)quadra );
			fprintf( outTxt, "\tcep: %s;\n", getQuadraCep(quadra) );
			fprintf( outTxt, "\tfill: %s;\n", getQuadraFill(quadra) );
			fprintf( outTxt, "\tstroke: %s;\n", getQuadraStroke(quadra) );
			fprintf( outTxt, "\tx: %f;\n", getQuadraX(quadra) );
			fprintf( outTxt, "\ty: %f;\n", getQuadraY(quadra) );
			fprintf( outTxt, "\twidth: %f;\n", getQuadraWidth(quadra) );
			fprintf( outTxt, "\theight: %f;\n", getQuadraHeight(quadra) );

			fprintf( outTxt, "\testabComerciais {\n" );
			itCodt = createIterator(getQuadraEstabComerciais(quadra));
			while( iteratorHasNext(itCodt) ){
				HashTable *ht = iteratorNext(itCodt);
				fprintf( outTxt, "\t\t%s: ", iteratorKey(itCodt) );

				itCnpj = createIterator(ht);
				fprintf( outTxt, "%s", getEstabComercialCNPJ( iteratorNext(itCnpj) ) );
				while( iteratorHasNext(itCnpj) ){
					fprintf( outTxt, ", %s", getEstabComercialCNPJ( iteratorNext(itCnpj) ) );
				}
				destroyIterator(itCnpj);
				fprintf( outTxt, ";\n" );
			}
			destroyIterator(itCodt);
			fprintf( outTxt, "\t}\n" );

			fprintf( outTxt, "\tmoradores: " );
			itCpf = createIterator(getQuadraMoradores(quadra));
			if( iteratorHasNext(itCpf) ){
				fprintf( outTxt, "%s", getPessoaCpf( iteratorNext(itCpf) ) );
				while( iteratorHasNext(itCpf) ){
					fprintf( outTxt, ", %s", getPessoaCpf( iteratorNext(itCpf) ) );
				}
			}
			destroyIterator(itCpf);
			fprintf( outTxt, ";\n" );

			fprintf( outTxt, "}\n\n" );
		}
		destroyIterator(itQuadras);
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpPointTxt( HashTable *objHT, char *obj, char *outDir, char *fileName ){
	Point *point;
	char *fullPath;
	FILE *outTxt;
	Iterator *it;

	fullPath = createStringCat( 3, outDir, fileName, ".txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		it = createIterator(objHT);
		while( iteratorHasNext(it) ){
			point = getObjData( iteratorNext(it) );
			fprintf( outTxt, "%s %p {\n", obj, (void*)point );
			fprintf( outTxt, "\tid: %s;\n", getPointId(point) );
			fprintf( outTxt, "\tfill: %s;\n", getPointFill(point) );
			fprintf( outTxt, "\tstroke: %s;\n", getPointStroke(point) );
			fprintf( outTxt, "\tx: %f;\n", getPointX(point) );
			fprintf( outTxt, "\ty: %f;\n", getPointY(point) );
			if( getPointInfo(point) != NULL ){
				fprintf( outTxt, "\tinfo: %f;\n", *(double*)getPointInfo(point) );
			}
			fprintf( outTxt, "}\n\n" );
		}
		destroyIterator(it);
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpEstabComerciaisTxt( HashTable *estabComerciais, char *outDir ){
	char *fullPath;
	FILE *outTxt;
	Iterator *it;
	EstabComercial *estab;

	fullPath = createStringCat( 2, outDir, "EstabComerciais.txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		it = createIterator(estabComerciais);
		while( iteratorHasNext(it) ){
			estab = iteratorNext(it);
			fprintf( outTxt, "EstabComercial %p {\n", (void*)estab );
			fprintf( outTxt, "\tcnpj: %s;\n", getEstabComercialCNPJ(estab) );
			fprintf( outTxt, "\tnome: %s;\n", getEstabComercialNome(estab) );
			fprintf( outTxt, "\tcodt: %s;\n", getEstabComercialCodt(estab) );
			fprintf( outTxt, "\tcep: %s;\n", getEstabComercialCep(estab) );
			fprintf( outTxt, "\tface: %c;\n", getEstabComercialFace(estab) );
			fprintf( outTxt, "\tnum: %d;\n", getEstabComercialNum(estab) );
			fprintf( outTxt, "}\n\n" );
		}
		destroyIterator(it);
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpPessoasTxt( HashTable *pessoas, char *type, char *outDir, char *fileName ){
	char *fullPath;
	FILE *outTxt;
	Iterator *it;
	Pessoa *pessoa;
	Endereco *endereco;

	fullPath = createStringCat( 3, outDir, fileName, ".txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		it = createIterator(pessoas);
		while( iteratorHasNext(it) ){
			pessoa = iteratorNext(it);
			endereco = getPessoaEndereco(pessoa);
			fprintf( outTxt, "%s %p {\n", type, (void*)pessoa );
			fprintf( outTxt, "\tcpf: %s;\n", getPessoaCpf(pessoa) );
			fprintf( outTxt, "\tnome: %s;\n", getPessoaNome(pessoa) );
			fprintf( outTxt, "\tsobrenome: %s;\n", getPessoaSobrenome(pessoa) );
			fprintf( outTxt, "\tsexo: %c;\n", getPessoaSexo(pessoa) );
			fprintf( outTxt, "\tnasc: %s;\n", getPessoaNasc(pessoa) );
			if(endereco){
				fprintf( outTxt, "\tEndereco %p {\n", (void*)endereco );
				fprintf( outTxt, "\t\tcep: %s;\n", getEnderecoCep(endereco) );
				fprintf( outTxt, "\t\tface: %c;\n", getEnderecoFace(endereco) );
				fprintf( outTxt, "\t\tnum: %d;\n", getEnderecoNum(endereco) );
				fprintf( outTxt, "\t\tcompl: %s;\n", getEnderecoCompl(endereco) );
				fprintf( outTxt, "\t}\n" );
			}
			fprintf( outTxt, "}\n\n" );
		}
		destroyIterator(it);
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpOperadoraTxt( Operadora *op, char *outDir ){
	char *fullPath;
	FILE *outTxt;
	Iterator *it;

	fullPath = createStringCat( 4, outDir, "Operadora-", getOperadoraNome(op), ".txt" );
	outTxt = openFileWrite(fullPath);
	if( outTxt != NULL ){
		fprintf( outTxt, "Operadora %p{\n", (void*)op );
		fprintf( outTxt, "\ttorres: " );
		it = createIterator(getOperadoraTorresHT(op));
		if( iteratorHasNext(it) ){
			fprintf( outTxt, "%s", getObjId(iteratorNext(it)) );
			while( iteratorHasNext(it) ){
				fprintf( outTxt, ", %s", getObjId(iteratorNext(it)) );
			}
		}
		destroyIterator(it);
		fprintf( outTxt, ";\n" );

		fprintf( outTxt, "\tclientes: " );
		it = createIterator(getOperadoraClientes(op));
		if( iteratorHasNext(it) ){
			fprintf( outTxt, "%s", getPessoaCpf(iteratorNext(it)) );
			while( iteratorHasNext(it) ){
				fprintf( outTxt, ", %s", getPessoaCpf(iteratorNext(it)) );
			}
		}
		destroyIterator(it);
		fprintf( outTxt, ";\n" );

		fprintf( outTxt, "\tconexoesTorreId {\n" );
		it = createIterator(getOperadoraConexoesTorreId(op));
		while( iteratorHasNext(it) ){
			Iterator *itNum = createIterator(iteratorNext(it));
			fprintf( outTxt, "\t\t%s: ", iteratorKey(it) );
			if( iteratorHasNext(itNum) ){
				fprintf( outTxt, "%s", getCelularNumero(iteratorNext(itNum)) );
				while( iteratorHasNext(itNum) ){
					fprintf( outTxt, ", %s", getCelularNumero(iteratorNext(itNum)) );
				}
			}
			destroyIterator(itNum);
			fprintf( outTxt, ";\n" );
		}
		fprintf( outTxt, "\t}\n" );
		destroyIterator(it);

		fprintf( outTxt, "\tconexoesQuadraCep {\n" );
		it = createIterator(getOperadoraConexoesQuadraCep(op));
		while( iteratorHasNext(it) ){
			Iterator *itNum = createIterator(iteratorNext(it));
			fprintf( outTxt, "\t\t%s: ", iteratorKey(it) );
			if( iteratorHasNext(itNum) ){
				fprintf( outTxt, "%s", getCelularNumero(iteratorNext(itNum)) );
				while( iteratorHasNext(itNum) ){
					fprintf( outTxt, ", %s", getCelularNumero(iteratorNext(itNum)) );
				}
			}
			destroyIterator(itNum);
			fprintf( outTxt, ";\n" );
		}
		fprintf( outTxt, "\t}\n" );
		destroyIterator(it);

		fprintf( outTxt, "}\n" );

		it = createIterator(getOperadoraCelularesNum(op));
		while( iteratorHasNext(it) ){
			Celular *celular = iteratorNext(it);
			Endereco *endereco = getCelularEndereco(celular);
			char *torreId = getCelularTorreId(celular);
			fprintf( outTxt, "\n" );
			fprintf( outTxt, "Celular %p {\n", (void*)celular );
			fprintf( outTxt, "\tnumero: %s;\n", getCelularNumero(celular) );
			fprintf( outTxt, "\tcpf: %s;\n", getCelularCpf(celular) );
			if( endereco != NULL ){
				fprintf( outTxt, "\tEndereco %p {\n", (void*)endereco );
				fprintf( outTxt, "\t\tcep: %s;\n", getEnderecoCep(endereco) );
				fprintf( outTxt, "\t\tface: %c;\n", getEnderecoFace(endereco) );
				fprintf( outTxt, "\t\tnum: %d;\n", getEnderecoNum(endereco) );
				fprintf( outTxt, "\t\tcompl: %s;\n", getEnderecoCompl(endereco) );
				fprintf( outTxt, "\t}\n" );
			}
			if( torreId != NULL ){
				fprintf( outTxt, "\ttorreId: %s;\n", torreId );
			}
			fprintf( outTxt, "}\n" );
		}
		destroyIterator(it);
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpCidadeDataStructuresDot( Cidade *cidade, char *outDir ){
	char *fullPath, method[2];
	int i, size;
	FILE *outDot;

	struct{
		char *name;
		HashTable *ht;
		QuadTree *qt;
		Graph *graph;
	} ds[] = {
		{ "Quadras", NULL, NULL, NULL },
		{ "Hidrantes", NULL, NULL, NULL },
		{ "Semaforos", NULL, NULL, NULL },
		{ "Torres", NULL, NULL, NULL },
		{ "Codt", NULL, NULL, NULL },
		{ "EstabComerciais", NULL, NULL, NULL },
		{ "Pessoas", NULL, NULL, NULL },
		{ "Vertices", NULL, NULL, NULL },
		{ "MalhaViaria", NULL, NULL, NULL }
	};

	sprintf( method, "%d", getCidadeMethod(cidade) );

	ds[0].ht = getCidadeQuadrasHT(cidade);
	ds[1].ht = getCidadeHidrantesHT(cidade);
	ds[2].ht = getCidadeSemaforosHT(cidade);
	ds[3].ht = getCidadeTorresHT(cidade);
	ds[4].ht = getCidadeDescricoes(cidade);
	ds[5].ht = getCidadeEstabComerciais(cidade);
	ds[6].ht = getCidadePessoas(cidade);
	ds[7].ht = getCidadeVerticesHT(cidade);

	ds[0].qt = getCidadeQuadrasQT(cidade);
	ds[1].qt = getCidadeHidrantesQT(cidade);
	ds[2].qt = getCidadeSemaforosQT(cidade);
	ds[3].qt = getCidadeTorresQT(cidade);
	ds[7].qt = getCidadeVerticesQT(cidade);

	ds[8].graph = getCidadeMalhaViaria(cidade);

	size = sizeof(ds)/sizeof(ds[0]);
	for( i = 0; i < size; i++ ){
		if( ds[i].qt ){
			fullPath = createStringCat( 5, outDir, ds[i].name, "-QT-", method, ".dot" );
			outDot = openFileWrite(fullPath);
			if( outDot ){
				dumpQuadTreeDot( ds[i].qt, outDot );
			}
			closeFile(outDot);
			destroyString(fullPath);
		}
		if( ds[i].ht ){
			fullPath = createStringCat( 3, outDir, ds[i].name, "-HT.dot" );
			outDot = openFileWrite(fullPath);
			if( outDot ){
				dumpHashTableDot( ds[i].ht, outDot );
			}
			closeFile(outDot);
			destroyString(fullPath);
		}
		if( ds[i].graph ){
			fullPath = createStringCat( 3, outDir, ds[i].name, "-Graph.dot" );
			outDot = openFileWrite(fullPath);
			if( outDot ){
				dumpGraphDot( ds[i].graph, outDot );
			}
			closeFile(outDot);
			destroyString(fullPath);
		}
	}
}

static void dumpObjsTxt( List *objs, char *outDir ){
	char *fullPathObjs;
	FILE *outObjsTxt;
	Node *node;
	Object *obj;
	void *objData;
	char objType;

	fullPathObjs = createStringCat( 2, outDir, "Objs.txt" );
	outObjsTxt = openFileWrite(fullPathObjs);
	if( outObjsTxt != NULL ){
		node = getFirst(objs);
		while( node != NULL ){
			obj = get(node);
			objData = getObjData(obj);
			objType = getObjType(obj);

			if( objType == 'c' ){
				fprintf( outObjsTxt, "Circle %p {\n", objData );
				fprintf( outObjsTxt, "\tid: %d;\n", getCircleId(objData) );
				fprintf( outObjsTxt, "\tradius: %f;\n", getCircleRadius(objData) );
				fprintf( outObjsTxt, "\tx: %f;\n", getCircleX(objData) );
				fprintf( outObjsTxt, "\ty: %f;\n", getCircleY(objData) );
				fprintf( outObjsTxt, "\tfill: %s;\n", getCircleFill(objData) );
				fprintf( outObjsTxt, "}\n\n" );
			}
			else if( objType == 'r' ){
				fprintf( outObjsTxt, "Rect %p {\n", objData );
				fprintf( outObjsTxt, "\tid: %d;\n", getRectId(objData) );
				fprintf( outObjsTxt, "\twidth: %f;\n", getRectWidth(objData) );
				fprintf( outObjsTxt, "\theight: %f;\n", getRectHeight(objData) );
				fprintf( outObjsTxt, "\tx: %f;\n", getRectX(objData) );
				fprintf( outObjsTxt, "\ty: %f;\n", getRectY(objData) );
				fprintf( outObjsTxt, "\tfill: %s;\n", getRectFill(objData) );
				fprintf( outObjsTxt, "}\n\n" );
			}
			else if( objType == 'o' ){
				fprintf( outObjsTxt, "Rect (overlap) %p {\n", objData );
				fprintf( outObjsTxt, "\tid: %d;\n", getRectId(objData) );
				fprintf( outObjsTxt, "\twidth: %f;\n", getRectWidth(objData) );
				fprintf( outObjsTxt, "\theight: %f;\n", getRectHeight(objData) );
				fprintf( outObjsTxt, "\tx: %f;\n", getRectX(objData) );
				fprintf( outObjsTxt, "\ty: %f;\n", getRectY(objData) );
				fprintf( outObjsTxt, "\tfill: %s;\n", getRectFill(objData) );
				fprintf( outObjsTxt, "}\n\n" );
			}
			node = getNext(node);
		}
	}
	closeFile(outObjsTxt);
	destroyString(fullPathObjs);
}

void nearestPoint( char *arg, Cidade *cidade, char *outDir ){
	char obj, *fullPath;
	FILE *svg;
	double x, y;
	QuadTree *qt;

	sscanf( arg, "%c,%lf,%lf", &obj, &x, &y );

	if( obj == 'q' ){
		qt = getCidadeQuadrasQT(cidade);
	}
	else if( obj == 'h' ){
		qt = getCidadeHidrantesQT(cidade);
	}
	else if( obj == 's' ){
		qt = getCidadeSemaforosQT(cidade);
	}
	else if( obj == 't' ){
		qt = getCidadeTorresQT(cidade);
	}
	else if( obj == 'v' ){
		qt = getCidadeVerticesQT(cidade);
	}
	else{
		return;
	}

	fullPath = createStringCat( 2, outDir, "nearest.svg" );
	svg = openFileWrite(fullPath);
	if( svg != NULL ){
		Object *nearest = searchQuadTreeNearestToPoint( x, y, qt );

		writeSvgStart(svg);

		writeCidadeTags(cidade, svg);

		writeAnchorTag( 0, getX(nearest), getY(nearest), 5, "fuchsia", 1, svg );
		writeAnchorTag( 0, x, y, 5, "blue", 1, svg );

		writeSvgEnd(svg);
	}

	closeFile(svg);
	destroyString(fullPath);
}

static void dumpMalhaViariaSvg( Cidade *cidade, char *outDir ){
	char *fullPath;
	FILE *svg;
	Iterator *it, *it_u, *it_v;

	fullPath = createStringCat( 2, outDir, "MalhaViaria.svg" );
	svg = openFileWrite(fullPath);

	if(svg){
		writeSvgStart(svg);

		writeCidadeTags(cidade, svg);

		it_u = createIterator(getGraphVertices(getCidadeMalhaViaria(cidade)));
		while(iteratorHasNext(it_u)){
			Vertex *vertex_u = iteratorNext(it_u);
			HashTable *edges = getVertexEdges(vertex_u);
			if(edges){
				it_v = createIterator(edges);
				while(iteratorHasNext(it_v)){
					Vertex *vertex_v = iteratorNext(it_v);
					double xu = getVertexX(vertex_u);
					double yu = getVertexY(vertex_u);
					char *idu = getVertexKey(vertex_u);
					double xv = getVertexX(vertex_v);
					double yv = getVertexY(vertex_v);
					char *idv = getVertexKey(vertex_v);

					fprintf( svg, "\t<line id=\"%s-%s\" stroke=\"black\" stroke-width=\"1\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />\n", idu, idv, xu, yu, xv, yv );
				}
				destroyIterator(it_v);
			}
		}
		destroyIterator(it_u);

		it = createIterator(getGraphVertices(getCidadeMalhaViaria(cidade)));
		while(iteratorHasNext(it)){
			Vertex *vertex = iteratorNext(it);
			writeAnchorTag( getVertexKey(vertex), getVertexX(vertex), getVertexY(vertex), 1.5, "black", 1.0, svg );
		}
		destroyIterator(it);

		writeSvgEnd(svg);
	}

	closeFile(svg);
	destroyString(fullPath);
}

static void dumpRuasTxt( Cidade *cidade, char *outDir ){
	char *fullPath = createStringCat( 2, outDir, "Ruas.txt" );
	FILE *outTxt = openFileWrite(fullPath);

	if(outTxt){
		Node *node;
		for( node = getFirst(getCidadeRuas(cidade)); node; node = getNext(node) ){
			Rua *rua = get(node);
			fprintf( outTxt, "Rua %p {\n", (void*)rua );
			fprintf( outTxt, "\tnome: %s;\n", getRuaNome(rua) );
			fprintf( outTxt, "\tldir: %s;\n", getRuaLdir(rua) );
			fprintf( outTxt, "\tlesq: %s;\n", getRuaLesq(rua) );
			fprintf( outTxt, "\tcpm: %f;\n", getRuaCmp(rua) );
			fprintf( outTxt, "\tvm: %f;\n", getRuaVm(rua) );
			fprintf( outTxt, "}\n\n" );
		}
	}

	closeFile(outTxt);
	destroyString(fullPath);
}

static void dumpRegistradoresTxt( Cidade *cidade, char *outDir ){
	char *fullPath;
	FILE *out;
	Iterator *it;

	fullPath = createStringCat( 2, outDir, "Registradores.txt" );
	out = openFileWrite(fullPath);

	if(out){
		it = createIterator(getCidadeRegistradores(cidade));
		while(iteratorHasNext(it)){
			Point *coords = iteratorNext(it);
			fprintf( out, "%s %p {\n", iteratorKey(it), (void*)coords );
			fprintf( out, "\tid: %s;\n", getPointId(coords) );
			fprintf( out, "\tx: %f;\n", getPointX(coords) );
			fprintf( out, "\ty: %f;\n", getPointY(coords) );
			fprintf( out, "}\n\n" );
		}
		destroyIterator(it);
	}

	closeFile(out);
	destroyString(fullPath);
}

static void dumpRegistradoresSvg( Cidade *cidade, char *outDir ){
	char *fullPath;
	FILE *svg;
	Iterator *it;

	fullPath = createStringCat( 2, outDir, "Registradores.svg" );
	svg = openFileWrite(fullPath);

	if(svg){
		writeSvgStart(svg);

		writeCidadeTags(cidade, svg);

		it = createIterator(getCidadeRegistradores(cidade));
		while(iteratorHasNext(it)){
			Point *coords = iteratorNext(it);
			writeAnchorTag( getPointId(coords), getPointX(coords), getPointY(coords), 5.0, "blue", 1.0, svg );
			writeStringTag( getPointId(coords), getPointX(coords), getPointY(coords), svg );
		}
		destroyIterator(it);

		writeSvgEnd(svg);
	}

	closeFile(svg);
	destroyString(fullPath);
}
