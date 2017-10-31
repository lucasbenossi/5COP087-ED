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

#define STROKE 0.5
#define STROKE_POLYGON 2.0
#define OPACITY 0.3

typedef void (*funcWriteTag)(void*,FILE*);

static void processList( Node *node, FILE *svg, funcWriteTag writeTag );

static void processTree( QuadTreeNode *node, FILE *svg, funcWriteTag writeTag );

static void writeCidadeTorresCoberturaTagsRecursion( QuadTreeNode *node, FILE *svg );

/* ========================================================================== */

void writeSvgStart( FILE *svg ){
    fprintf( svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void writeSvgEnd( FILE *svg ){
    fprintf(svg, "</svg>");
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

void writeCidadeTags( Cidade *cidade, FILE *svg, int method ){
    if( method == 0 ){
        processList( getFirst(getCidadeQuadras(cidade)), svg, (funcWriteTag)writeQuadraTag );
        processList( getFirst(getCidadeHidrantes(cidade)), svg, (funcWriteTag)writeHidranteTag );
        processList( getFirst(getCidadeSemaforos(cidade)), svg, (funcWriteTag)writeSemaforoTag );
        processList( getFirst(getCidadeTorres(cidade)), svg, (funcWriteTag)writeTorreTag );
    }
    else{
        processTree( getQuadTreeRoot(getCidadeQuadrasQT(cidade)), svg, (funcWriteTag)writeQuadraTag );
        processTree( getQuadTreeRoot(getCidadeHidrantesQT(cidade)), svg, (funcWriteTag)writeHidranteTag );
        processTree( getQuadTreeRoot(getCidadeSemaforosQT(cidade)), svg, (funcWriteTag)writeSemaforoTag );
        processTree( getQuadTreeRoot(getCidadeTorresQT(cidade)), svg, (funcWriteTag)writeTorreTag );
    }
}

void writeCidadeTorresCoberturaTags( Cidade *cidade, FILE *svg, int method ){
    Node *node;

    if( method == 0 ){
        node = getFirst( getCidadeTorres(cidade) );
        while( node != NULL ){
            writeTorreCoberturaTag( getObjData(get(node)), svg );
            node = getNext(node);
        }
    }
    else{
        writeCidadeTorresCoberturaTagsRecursion( getQuadTreeRoot(getCidadeTorresQT(cidade)), svg );
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
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", "black");
    fprintf(svg, "/>\n");
}

void writeCircleTag( Circle *circle, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%d\" ", getCircleId(circle));
    fprintf(svg, "cx=\"%f\" ", getCircleX(circle));
    fprintf(svg, "cy=\"%f\" ", getCircleY(circle));
    fprintf(svg, "r=\"%f\" ", getCircleRadius(circle));
    fprintf(svg, "fill=\"%s\" ", getCircleFill(circle));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", "black");
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

void writeQuadraTag( Quadra *q, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%s\" ", getQuadraCep(q));
    fprintf(svg, "x=\"%f\" ", getQuadraX(q));
    fprintf(svg, "y=\"%f\" ", getQuadraY(q));
    fprintf(svg, "width=\"%f\" ", getQuadraWidth(q));
    fprintf(svg, "height=\"%f\" ", getQuadraHeight(q));
    fprintf(svg, "fill=\"%s\" ", getQuadraFill(q));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getQuadraStroke(q));
    fprintf(svg, "/>\n");
    /*writeStringTag( getQuadraCep(q), getQuadraX(q), getQuadraY(q), svg );*/
}

void writePointTag( Point *p, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 5.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeHidranteTag( Point *p, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "x=\"%f\" ", getPointX(p)-2.5);
    fprintf(svg, "y=\"%f\" ", getPointY(p)-5.0);
    fprintf(svg, "width=\"%f\" ", 5.0);
    fprintf(svg, "height=\"%f\" ", 10.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeSemaforoTag( Point *p, FILE *svg ){
    double circleRadius, distCircleY;
    char *red, *yellow, *green;

    circleRadius = 2.5;
    distCircleY = 5.5;

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
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "x=\"%f\" ", getPointX(p)-3.5);
    fprintf(svg, "y=\"%f\" ", getPointY(p)-9.0);
    fprintf(svg, "width=\"%f\" ", 7.0);
    fprintf(svg, "height=\"%f\" ", 18.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", yellow);
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p)-distCircleY);
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", red);
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p)+distCircleY);
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", green);
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeTorreTag( Point *p, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 8.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 6.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 4.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", STROKE);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeTorreCoberturaTag( Point *p, FILE *svg ){
    double *radius;

    radius = getPointInfo(p);
    if( radius != NULL && *radius > 0 ){
        fprintf(svg, "\t<circle ");
        fprintf(svg, "id=\"%s\" ", getPointId(p));
        fprintf(svg, "cx=\"%f\" ", getPointX(p));
        fprintf(svg, "cy=\"%f\" ", getPointY(p));
        fprintf(svg, "r=\"%f\" ", *radius);
        fprintf(svg, "fill=\"%s\" ", "blue");
        fprintf(svg, "fill-opacity=\"%f\"\n", OPACITY);
        fprintf(svg, "stroke-width=\"%f\" ", STROKE);
        fprintf(svg, "stroke=\"%s\" ", "black");
        fprintf(svg, "/>\n");
    }
}

void writePolygonTag( Polygon *polygon, FILE *svg ){
    Node *node;
    Point *point;

    fprintf( svg, "\t<polygon id=\"%s\" ", getPolygonId(polygon) );
    fprintf( svg, "stroke-width=\"%f\" ", STROKE_POLYGON );
    fprintf( svg, "stroke=\"%s\" ", getPolygonStroke(polygon) );
    fprintf( svg, "fill=\"%s\" ", getPolygonFill(polygon) );
    fprintf( svg, "fill-opacity=\"%f\" ", OPACITY );
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
    fprintf(svg, "\t<text x=\"%f\" y=\"%f\">%s</text>\n", x, y, string);
}

/* ========================================================================== */

static void processList( Node *node, FILE *svg, funcWriteTag writeTag ){
    while( node != NULL ){
        writeTag( getObjData(get(node)), svg );
        node = getNext(node);
    }
}

static void processTree( QuadTreeNode *node, FILE *svg, funcWriteTag writeTag ){
    void *data;
    if( node != NULL ){
        data = getQuadTreeNodeData(node);
        if( data != NULL ){
            writeTag( getObjData(data), svg );
        }
        processTree( getQuadTreeNodeNW(node), svg, writeTag );
        processTree( getQuadTreeNodeNE(node), svg, writeTag );
        processTree( getQuadTreeNodeSW(node), svg, writeTag );
        processTree( getQuadTreeNodeSE(node), svg, writeTag );
    }
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
