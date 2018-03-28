#include <stdio.h>
#include <string.h>
#include "WriteTags.h"
#include "Cidade.h"
#include "Object.h"
#include "Rect.h"
#include "Circle.h"
#include "Quadra.h"
#include "Point.h"
#include "Polygon.h"
#include "LinkedList.h"
#include "Endereco.h"
#include "HashTable.h"
#include "EstabComercial.h"
#include "Pessoa.h"
#include "Operadora.h"
#include "Celular.h"
#include "ObjData.h"

#define STROKE_WIDTH 0.5
#define STROKE_COLOR "black"

#define POLYGON_STROKE_WIDTH 2.0
#define POLYGON_OPACITY 0.3

#define ESTABCOMERCIAIS_SIZE 2.0
#define ESTABCOMERCIAIS_FILL "aqua"
#define ESTABCOMERCIAIS_OPACITY 0.5

#define PESSOA_RADIUS 1.0
#define PESSOA_FILL "#FF8080"
#define PESSOA_OPACITY 0.5

#define HIDRANTE_SIZE 5.0

#define SEMAFORO_SIZE 7.0

#define TORRE_SIZE 8.0

#define COBERTURA_TORRE_FILL "blue"
#define COBERTURA_TORRE_OPACITY 0.3

#define DEFUNTO_SIZE 8.0
#define DEFUNTO_FILL "black"
#define DEFUNTO_CRUZ_COLOR "white"

#define STRING_FONT_FAMILY "DejaVu Sans Mono"
#define STRING_FONT_SIZE "5px"
#define STRING_FILL "black"

typedef void (*funcWriteTag)(void*,FILE*);

static void writeTagRecursion( QuadTreeNode *node, FILE *svg, funcWriteTag writeTag );

static void writeCidadeTorresCoberturaTagsRecursion( QuadTreeNode *node, FILE *svg );

static void writeQuadraTag_Wrapper( void *data, FILE *svg ){
	writeQuadraTag(data, svg);
}

static void writeHidranteTag_Wrapper( void *data, FILE *svg ){
	writeHidranteTag(data, svg);
}

static void writeSemaforoTag_Wrapper( void *data, FILE *svg ){
	writeSemaforoTag(data, svg);
}

static void writeTorreTag_Wrapper( void *data, FILE *svg ){
	writeTorreTag(data, svg);
}

/* ========================================================================== */

void writeSvgStart( FILE *svg ){
	fprintf( svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void writeSvgEnd( FILE *svg ){
	fprintf(svg, "</svg>\n");
}

void writeObjsTags( List *objs, FILE *svg ){
	Node *node;
	Object *obj;
	void *objData;
	char objType;

	node = getFirst(objs);
	while( node != NULL ){
	    obj = get(node);
	    objData = getObjData( obj );
	    objType = getObjType( obj );

	    if( objType == 'c' ){
	        writeCircleTag( objData, svg );
	    }
	    else if( objType == 'r' ){
	        writeRectTag( objData, svg );
	    }
	    else if( objType == 'o' ){
	        writeOverlapTag( objData, svg );
	    }

	    node = getNext(node);
	}
}

void writeCidadeTags( Cidade *cidade, FILE *svg ){
	writeTagRecursion( getQuadTreeRoot(getCidadeQuadrasQT(cidade)), svg, writeQuadraTag_Wrapper );
	writeTagRecursion( getQuadTreeRoot(getCidadeHidrantesQT(cidade)), svg, writeHidranteTag_Wrapper );
	writeTagRecursion( getQuadTreeRoot(getCidadeSemaforosQT(cidade)), svg, writeSemaforoTag_Wrapper );
	writeTagRecursion( getQuadTreeRoot(getCidadeTorresQT(cidade)), svg, writeTorreTag_Wrapper );
}

static void writeTagRecursion( QuadTreeNode *node, FILE *svg, funcWriteTag writeTag ){
	void *data;
	if( node != NULL ){
	    data = getQuadTreeNodeData(node);
	    if( data != NULL ){
	        writeTag( getObjData(data), svg );
	    }
	    writeTagRecursion( getQuadTreeNodeNW(node), svg, writeTag );
	    writeTagRecursion( getQuadTreeNodeNE(node), svg, writeTag );
	    writeTagRecursion( getQuadTreeNodeSW(node), svg, writeTag );
	    writeTagRecursion( getQuadTreeNodeSE(node), svg, writeTag );
	}
}

void writeCidadeTorresCoberturaTags( Cidade *cidade, FILE *svg ){
	writeCidadeTorresCoberturaTagsRecursion( getQuadTreeRoot(getCidadeTorresQT(cidade)), svg );
}

static void writeCidadeTorresCoberturaTagsRecursion( QuadTreeNode *node, FILE *svg ){
	void *data;
	if( node != NULL ){
	    data = getQuadTreeNodeData(node);
	    if( data != NULL ){
	        writeTorreCoberturaTag( getObjData(data), svg );
	    }
	    writeCidadeTorresCoberturaTagsRecursion( getQuadTreeNodeNW(node), svg );
	    writeCidadeTorresCoberturaTagsRecursion( getQuadTreeNodeNE(node), svg );
	    writeCidadeTorresCoberturaTagsRecursion( getQuadTreeNodeSW(node), svg );
	    writeCidadeTorresCoberturaTagsRecursion( getQuadTreeNodeSE(node), svg );
	}
}

void writeRectTag( Rect *rect, FILE *svg ){
	fprintf(svg, "\t<rect ");
	fprintf(svg, "id=\"%d\" ", getRectId(rect));
	fprintf(svg, "x=\"%f\" ", getRectX(rect));
	fprintf(svg, "y=\"%f\" ", getRectY(rect));
	fprintf(svg, "width=\"%f\" ", getRectWidth(rect));
	fprintf(svg, "height=\"%f\" ", getRectHeight(rect));
	fprintf(svg, "fill=\"%s\" ", getRectFill(rect));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", STROKE_COLOR);
	fprintf(svg, "/>\n");
}

void writeCircleTag( Circle *circle, FILE *svg ){
	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%d\" ", getCircleId(circle));
	fprintf(svg, "cx=\"%f\" ", getCircleX(circle));
	fprintf(svg, "cy=\"%f\" ", getCircleY(circle));
	fprintf(svg, "r=\"%f\" ", getCircleRadius(circle));
	fprintf(svg, "fill=\"%s\" ", getCircleFill(circle));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", STROKE_COLOR);
	fprintf(svg, "/>\n");
}

void writeOverlapTag( Rect *rect, FILE *svg ){
	fprintf(svg, "\t<rect ");
	fprintf(svg, "id=\"%d\" ", getRectId(rect));
	fprintf(svg, "x=\"%f\" ", getRectX(rect));
	fprintf(svg, "y=\"%f\" ", getRectY(rect));
	fprintf(svg, "width=\"%f\" ", getRectWidth(rect));
	fprintf(svg, "height=\"%f\" ", getRectHeight(rect));
	fprintf(svg, "fill=\"none\" ");
	fprintf(svg, "stroke-width=\"3.0\" ");
	fprintf(svg, "stroke=\"red\" ");
	fprintf(svg, "stroke-dasharray=\"5,5\" ");
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<text ");
	fprintf(svg, "x=\"%f\" ", getRectX(rect)+5);
	fprintf(svg, "y=\"%f\" ", getRectY(rect)+15);
	fprintf(svg, "fill=\"red\"");
	fprintf(svg, ">sobrepoe</text>\n");
}

void writeAnchorTag( char *i, double x, double y, double r, char *fill, double opacity, FILE *svg ){
	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s\" ", i);
	fprintf(svg, "cx=\"%f\" ", x);
	fprintf(svg, "cy=\"%f\" ", y);
	fprintf(svg, "r=\"%f\" ", r);
	fprintf(svg, "fill=\"%s\" ", fill);
	fprintf(svg, "opacity=\"%f\" ", opacity);
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", STROKE_COLOR);
	fprintf(svg, "/>\n");
}

void writeQuadraTag( Quadra *q, FILE *svg ){
	fprintf(svg, "\t<rect ");
	fprintf(svg, "id=\"%s\" ", getQuadraCep(q));
	fprintf(svg, "x=\"%f\" ", getQuadraX(q));
	fprintf(svg, "y=\"%f\" ", getQuadraY(q));
	fprintf(svg, "width=\"%f\" ", getQuadraWidth(q));
	fprintf(svg, "height=\"%f\" ", getQuadraHeight(q));
	fprintf(svg, "fill=\"%s\" ", getQuadraFill(q));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getQuadraStroke(q));
	fprintf(svg, "/>\n");
}

void writeHidranteTag( Point *p, FILE *svg ){
	double width, height;

	width = HIDRANTE_SIZE;
	height = HIDRANTE_SIZE * 2;

	fprintf(svg, "\t<rect ");
	fprintf(svg, "id=\"%s\" ", getPointId(p));
	fprintf(svg, "x=\"%f\" ", getPointX(p)-width/2);
	fprintf(svg, "y=\"%f\" ", getPointY(p)-height/2);
	fprintf(svg, "width=\"%f\" ", width);
	fprintf(svg, "height=\"%f\" ", height);
	fprintf(svg, "fill=\"%s\" ", getPointFill(p));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");
}

void writeSemaforoTag( Point *p, FILE *svg ){
	double width, height, circleRadius, distCircleY, prop;
	char *red, *yellow, *green;

	prop = SEMAFORO_SIZE/7.0;

	width = prop * 7.0;
	height = prop * 18.0;
	circleRadius = prop * 2.5;
	distCircleY = prop * 5.5;

	if( strcmp( getPointFill(p), "rgb(153,153,153)" ) == 0 ){
	    red = "red";
	    yellow = "yellow";
	    green = "green";
	}
	else{
	    red = "white";
	    yellow = "white";
	    green = "white";
	}

	fprintf(svg, "\t<rect ");
	fprintf(svg, "id=\"%s-back\" ", getPointId(p));
	fprintf(svg, "x=\"%f\" ", getPointX(p)-width/2);
	fprintf(svg, "y=\"%f\" ", getPointY(p)-height/2);
	fprintf(svg, "width=\"%f\" ", width);
	fprintf(svg, "height=\"%f\" ", height);
	fprintf(svg, "fill=\"%s\" ", getPointFill(p));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-yellow\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p));
	fprintf(svg, "r=\"%f\" ", circleRadius);
	fprintf(svg, "fill=\"%s\" ", yellow);
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-red\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p)-distCircleY);
	fprintf(svg, "r=\"%f\" ", circleRadius);
	fprintf(svg, "fill=\"%s\" ", red);
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-green\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p)+distCircleY);
	fprintf(svg, "r=\"%f\" ", circleRadius);
	fprintf(svg, "fill=\"%s\" ", green);
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");
}

void writeTorreTag( Point *p, FILE *svg ){
	double prop;

	prop = TORRE_SIZE/8.0;

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-1\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p));
	fprintf(svg, "r=\"%f\" ", prop*8.0);
	fprintf(svg, "fill=\"%s\" ", getPointFill(p));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-2\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p));
	fprintf(svg, "r=\"%f\" ", prop*6.0);
	fprintf(svg, "fill=\"%s\" ", getPointFill(p));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");

	fprintf(svg, "\t<circle ");
	fprintf(svg, "id=\"%s-3\" ", getPointId(p));
	fprintf(svg, "cx=\"%f\" ", getPointX(p));
	fprintf(svg, "cy=\"%f\" ", getPointY(p));
	fprintf(svg, "r=\"%f\" ", prop*4.0);
	fprintf(svg, "fill=\"%s\" ", getPointFill(p));
	fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
	fprintf(svg, "/>\n");
}

void writeTorreCoberturaTag( Point *p, FILE *svg ){
	double *radius;

	radius = getPointInfo(p);
	if( radius != NULL && *radius > 0 ){
	    fprintf(svg, "\t<circle ");
	    fprintf(svg, "id=\"%s-cobertura\" ", getPointId(p));
	    fprintf(svg, "cx=\"%f\" ", getPointX(p));
	    fprintf(svg, "cy=\"%f\" ", getPointY(p));
	    fprintf(svg, "r=\"%f\" ", *radius);
	    fprintf(svg, "fill=\"%s\" ", COBERTURA_TORRE_FILL);
	    fprintf(svg, "fill-opacity=\"%f\"\n", COBERTURA_TORRE_OPACITY);
	    fprintf(svg, "stroke-width=\"%f\" ", STROKE_WIDTH);
	    fprintf(svg, "stroke=\"%s\" ", STROKE_COLOR);
	    fprintf(svg, "/>\n");
	}
}

void writePolygonTag( Polygon *polygon, FILE *svg ){
	Node *node;
	Point *point;

	fprintf( svg, "\t<polygon id=\"%s\" ", getPolygonId(polygon) );
	fprintf( svg, "stroke-width=\"%f\" ", POLYGON_STROKE_WIDTH );
	fprintf( svg, "stroke=\"%s\" ", getPolygonStroke(polygon) );
	fprintf( svg, "fill=\"%s\" ", getPolygonFill(polygon) );
	fprintf( svg, "fill-opacity=\"%f\" ", POLYGON_OPACITY );
	fprintf( svg, "points=\"" );

	node = getFirst(getPolygonNodes(polygon));
	while( node != NULL ){
	    point = get(node);
	    fprintf( svg, "%f,%f ", getPointX(point), getPointY(point) );
	    node = getNext(node);
	}

	fprintf( svg, "\" />\n" );
}

void writeStringTag( char *string, double x, double y, FILE *svg ){
	fprintf( svg, "\t<text x=\"%f\" y=\"%f\" font-family=\"%s\" font-size=\"%s\" fill=\"%s\">%s</text>\n", x, y, STRING_FONT_FAMILY, STRING_FONT_SIZE, STRING_FILL, string );
}

void writeEstabComerciaisTag( Cidade *cidade, FILE *svg ){
	Iterator *it;
	EstabComercial *estab;
	Point *point;
	Quadra *quadra;
	Endereco *endereco;

	it = createIterator( getCidadeEstabComerciais(cidade) );
	while( iteratorHasNext(it) ){
		estab = iteratorNext(it);
	    endereco = getEstabComercialEndereco( estab );
	    quadra = getObjData( searchCidadeQuadraCep( cidade, getEnderecoCep(endereco) ) );
	    point = getEnderecoCoords( endereco, quadra );
	    fprintf( svg, "\t<rect ");
	    fprintf( svg, "id=\"%s\" ", getEstabComercialCNPJ(estab) );
	    fprintf( svg, "x=\"%f\" ", getPointX(point) - ESTABCOMERCIAIS_SIZE/2 );
	    fprintf( svg, "y=\"%f\" ", getPointY(point) - ESTABCOMERCIAIS_SIZE/2 );
	    fprintf( svg, "width=\"%f\" ", ESTABCOMERCIAIS_SIZE );
	    fprintf( svg, "height=\"%f\" ", ESTABCOMERCIAIS_SIZE );
	    fprintf( svg, "fill=\"%s\" ", ESTABCOMERCIAIS_FILL );
	    fprintf( svg, "stroke-width=\"%f\" ", STROKE_WIDTH );
	    fprintf( svg, "stroke=\"%s\" ", STROKE_COLOR );
	    fprintf( svg, "opacity=\"%f\" ", ESTABCOMERCIAIS_OPACITY );
	    fprintf( svg, "/>\n" );
	    destroyPoint(point);
	}
	destroyIterator(it);
}

void writeMoradoresTag( Cidade *cidade, FILE *svg ){
	Iterator *it;
	Point *point;
	Pessoa *pessoa;
	Quadra *quadra;
	Endereco *endereco;
	int i;

	it = createIterator( getCidadePessoas(cidade) );
	while( iteratorHasNext(it) ){
		pessoa = iteratorNext(it);
	    endereco = getPessoaEndereco(pessoa);
	    if( endereco != NULL ){
	        quadra = getObjData( searchCidadeQuadraCep( cidade, getEnderecoCep(endereco) ) );
	        point = getEnderecoCoords( endereco, quadra );
	        writeAnchorTag( getPessoaCpf(pessoa), getPointX(point), getPointY(point), PESSOA_RADIUS, PESSOA_FILL, PESSOA_OPACITY, svg );
	        i++;
	        destroyPoint(point);
	    }
	}
	destroyIterator(it);
}

void writeConexoesTags( Cidade *cidade, FILE *svg ){
	Operadora **operadoras;
	int i;

	operadoras = getCidadeOperadoras(cidade);
	for( i = 0; i < 2; i++ ){
		Iterator *itTorreId = createIterator(getOperadoraConexoesTorreId(operadoras[i]));
		while(iteratorHasNext(itTorreId)){
			Iterator *itNum = createIterator(iteratorNext(itTorreId));
			while(iteratorHasNext(itNum)){
				Celular *celular = iteratorNext(itNum);
				Endereco *endereco = getCelularEndereco(celular);
				Quadra *quadra = getObjData(searchCidadeQuadraCep(cidade, getEnderecoCep(endereco)));
				Object *torre = searchOperadoraTorreId(operadoras[i], getCelularTorreId(celular));
				Point *coords = getEnderecoCoords(endereco, quadra);

				fprintf( svg, "\t<line " );
				fprintf( svg, "x1=\"%f\" ", getX(torre) );
				fprintf( svg, "y1=\"%f\" ", getY(torre) );
				fprintf( svg, "x2=\"%f\" ", getPointX(coords) );
				fprintf( svg, "y2=\"%f\" ", getPointY(coords) );
		        fprintf( svg, "stroke-width=\"%f\" ", STROKE_WIDTH );
		        fprintf( svg, "stroke=\"%s\" ", STROKE_COLOR );
				fprintf( svg, "/>\n" );

				destroyPoint(coords);
			}
			destroyIterator(itNum);
		}
		destroyIterator(itTorreId);
	}
}

void writeDefuntosTags( Cidade *cidade, FILE *svg ){
	Iterator *it = createIterator(getCidadeDefuntos(cidade));
	while(iteratorHasNext(it)){
		Pessoa *pessoa = iteratorNext(it);
		Endereco *endereco = getPessoaEndereco(pessoa);
		if(endereco){
			Object *obj = searchCidadeQuadraCep(cidade, getEnderecoCep(endereco));
			if(obj){
				Quadra *quadra = getObjData(obj);
				Point *coords = getEnderecoCoords(endereco, quadra);
				double x = getPointX(coords);
				double y = getPointY(coords);
				double a = DEFUNTO_SIZE/2;
				double b = DEFUNTO_SIZE/4;

				fprintf( svg, "\t<polygon id=\"%s-back\" ", getPessoaCpf(pessoa) );
			    fprintf( svg, "stroke-width=\"%f\" ", STROKE_WIDTH );
			    fprintf( svg, "stroke=\"%s\" ", STROKE_COLOR );
			    fprintf( svg, "fill=\"%s\" ", DEFUNTO_FILL );
			    fprintf( svg, "points=\"" );
				fprintf( svg, "%f,%f ", x   , y+a );
				fprintf( svg, "%f,%f ", x+a , y   );
				fprintf( svg, "%f,%f ", x   , y-a );
				fprintf( svg, "%f,%f ", x-a , y   );
			    fprintf( svg, "\" />\n" );

				fprintf( svg, "\t<line " );
				fprintf( svg, "x1=\"%f\" ", x   );
				fprintf( svg, "y1=\"%f\" ", y+b );
				fprintf( svg, "x2=\"%f\" ", x   );
				fprintf( svg, "y2=\"%f\" ", y-b );
				fprintf( svg, "stroke-width=\"%f\" ", STROKE_WIDTH );
				fprintf( svg, "stroke=\"%s\" ", DEFUNTO_CRUZ_COLOR );
				fprintf( svg, "/>\n" );

				fprintf( svg, "\t<line " );
				fprintf( svg, "x1=\"%f\" ", x-b );
				fprintf( svg, "y1=\"%f\" ", y   );
				fprintf( svg, "x2=\"%f\" ", x+b );
				fprintf( svg, "y2=\"%f\" ", y   );
				fprintf( svg, "stroke-width=\"%f\" ", STROKE_WIDTH );
				fprintf( svg, "stroke=\"%s\" ", DEFUNTO_CRUZ_COLOR );
				fprintf( svg, "/>\n" );

				destroyPoint(coords);
			}
		}
	}
	destroyIterator(it);
}
