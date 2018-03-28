#include "CommandsVia.h"
#include "Cidade.h"
#include "String.h"
#include "Graph.h"
#include "Point.h"
#include "Rua.h"

void commandInsertVertice( char *line, Cidade *cidade ){
	char id[STRING_SIZE];
	double x, y;

	sscanf( line, "v %s %lf %lf", id, &x, &y );

	if(searchCidadeVerticeId(cidade, id)){
		fputs(line, stderr);
		fprintf( stderr, "Vertice %s ja inserido.\n\n", id );
		return;
	}

	cidadeInsertVertice(cidade, createPoint(x, y, id, "", ""));
}

void commandInsertRua( char *line, Cidade *cidade ){
	char i[STRING_SIZE], j[STRING_SIZE], ldir[STRING_SIZE], lesq[STRING_SIZE], nome[STRING_SIZE];
	double cmp, vm;
	Point *point_i, *point_j;
	Rua *rua;

	sscanf( line, "e %s %s %s %s %lf %lf %[^\r\n]", i, j, ldir, lesq, &cmp, &vm, nome );

	point_i = searchCidadeVerticeId(cidade, i);
	if(!point_i){
		fputs(line, stderr);
		fprintf( stderr, "Vertice de Id %s nao existe.\n\n", i );
		return;
	}

	point_j = searchCidadeVerticeId(cidade, j);
	if(!point_j){
		fputs(line, stderr);
		fprintf( stderr, "Vertice de Id %s nao existe.\n\n", j );
		return;
	}

	rua = createRua(nome, ldir, lesq, cmp, vm);
	cidadeInsertRua(cidade, point_i, point_j, rua);
}
