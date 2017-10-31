#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "QuadTree.h"
#include "QuadTreeDeletion.h"
#include "ObjList.h"
#include "ObjQuadTree.h"
#include "Geometry.h"
#include "Cidade.h"
#include "Object.h"
#include "Quadra.h"
#include "Point.h"
#include "Rect.h"
#include "Circle.h"
#include "ProcString.h"
#include "CommandsT3.h"
#include "Resumo.h"

static int objInsideObj(Object *obj1, Object *obj2);

static void commandCidadeDeleteRecursion( QuadTreeNode *node, Object *obj2, FILE *outFileTxt, char *outString, Resumo *res, Stack *disabledNodes );
static int commandCidadeDeleteProcNode( Object *obj1, Object *obj2, FILE *outFileTxt, char *outString, Resumo *res );

static int commandSearchIdCepRecursion( QuadTreeNode *node, char *idCep, FILE *outFileTxt, char *outString );
static int commandSearchIdCepProcNode( Object *obj, char *idCep, FILE *outFileTxt, char *outString );

/* ==========================================================================================*/

void commandCidadeInsert( char *line, Cidade *c, Resumo *res, char *argR ){
    double x, y, width, height;
    char idCep[1000];
    Point *torre;
    double *info, radius;

    if( argR != NULL ){
        sscanf( argR, "%lf", &radius );
    }

    if( line[0] == 'q' ){
        sscanf(line, "q %lf %lf %lf %lf %[^\r\n]s", &x, &y, &width, &height, idCep);
        insert( getCidadeQuadras(c), createObject( idCep, 'q', createQuadra( x, y, width, height, idCep, getCidadeQuadrasFill(c), getCidadeQuadrasStroke(c) ) ) );
        if( res != NULL ){
            incIns(res);
            incCpi(res);
        }
    }
    else if( line[0] == 'h' ){
        sscanf(line, "h %lf %lf %s", &x, &y, idCep);
        insert( getCidadeHidrantes(c), createObject( idCep, 'h', createPoint( x, y, idCep, getCidadeHidrantesFill(c), getCidadeHidrantesStroke(c) ) ) );
    }
    else if( line[0] == 's' ){
        sscanf(line, "s %lf %lf %s", &x, &y, idCep);
        insert( getCidadeSemaforos(c), createObject( idCep, 's', createPoint( x, y, idCep, getCidadeSemaforosFill(c), getCidadeSemaforosStroke(c) ) ) );
    }
    else if( line[0] == 't' ){
        sscanf(line, "t %lf %lf %s", &x, &y, idCep);
        torre = createPoint( x, y, idCep, getCidadeTorresFill(c), getCidadeTorresStroke(c) );
        if( argR != NULL ){
            info = malloc(sizeof(double));
            *info = radius;
            setPointInfo(torre,info);
        }
        insert( getCidadeTorres(c), createObject( idCep, 't', torre ) );
    }
    else{
        return;
    }
}

void commandCidadeColors( char *line, Cidade *c ){
    char fill[1000], stroke[1000], command;
    sscanf(line,"c%c %s %[^\r\n]s", &command, fill, stroke);
    if( command == 'q' ){
        setCidadeQuadrasColors(c,fill,stroke);
    }
    else if( command == 'h' ){
        setCidadeHidrantesColors(c,fill,stroke);
    }
    else if( command == 's' ){
        setCidadeSemaforosColors(c,fill,stroke);
    }
    else if( command == 't' ){
        setCidadeTorresColors(c,fill,stroke);
    }
    else{
        return;
    }
}

void commandCidadeDelete( char *line, Cidade *c, FILE *outFileTxt, Resumo *res, int method ){
    double x, y, width, height, radius;
    char command, *outString;
    Object *obj2;
    List *list;
    QuadTree *qt;
    Node *node, *node0;
    Stack *disabledNodes;

    fputs(line,outFileTxt);

    if( line[0] == 'd' ){
        sscanf(line, "d%c %lf %lf %lf %lf", &command, &x, &y, &width, &height);
        obj2 = createObject( 0, 'r', createRect(0, width, height, x, y, "") );
    }
    else if( line[0] == 'D' ){
        sscanf(line, "D%c %lf %lf %lf", &command, &x, &y, &radius);
        obj2 = createObject( 0, 'c', createCircle(0, radius, x, y, "") );
    }

    if( command != 'q' ){
        res = NULL;
    }

    if( command == 'q' ){
        list = getCidadeQuadras(c);
        qt = getCidadeQuadrasQT(c);
        outString = "Quadra %s removida\n";
    }
    else if( command == 'h' ){
        list = getCidadeHidrantes(c);
        qt = getCidadeHidrantesQT(c);
        outString = "Hidrante %s removido\n";
    }
    else if( command == 's' ){
        list = getCidadeSemaforos(c);
        qt = getCidadeSemaforosQT(c);
        outString = "Semaforo %s removido\n";
    }
    else if( command == 't' ){
        list = getCidadeTorres(c);
        qt = getCidadeTorresQT(c);
        outString = "Torre %s removida\n";
    }
    else{
        return;
    }

    disabledNodes = createStack();

    if( method == 0 ){
        node = getFirst(list);
        while( node != NULL ){
            node0 = node;
            node = getNext(node);
            if( commandCidadeDeleteProcNode( get(node0), obj2, outFileTxt, outString, res ) == 1 ){
                destroyDataObj( removeNode( list, node0 ) );
            }
        }
    }
    else{
        commandCidadeDeleteRecursion( getQuadTreeRoot(qt), obj2, outFileTxt, outString, res, disabledNodes );
    }

    list = createList();
    quadTreeRemoveNodes(qt, disabledNodes, list);
    objListToQuadTree(list, qt);
    destroyList(list);

    destroyStack(disabledNodes);

    fprintf( outFileTxt, "\n" );

    destroyDataObj(obj2);
}

static void commandCidadeDeleteRecursion( QuadTreeNode *node, Object *obj2, FILE *outFileTxt, char *outString, Resumo *res, Stack *disabledNodes ){
    void *data;
    if( node != NULL ){
        data = getQuadTreeNodeData(node);
        if( data != NULL ){
            if( commandCidadeDeleteProcNode( data, obj2, outFileTxt, outString, res ) == 1 ){
                destroyDataObj( disableQuadTreeNode(node) );
                push( disabledNodes, node );
            }
        }
        commandCidadeDeleteRecursion( getQuadTreeNodeNW(node), obj2, outFileTxt, outString, res, disabledNodes );
        commandCidadeDeleteRecursion( getQuadTreeNodeNE(node), obj2, outFileTxt, outString, res, disabledNodes );
        commandCidadeDeleteRecursion( getQuadTreeNodeSW(node), obj2, outFileTxt, outString, res, disabledNodes );
        commandCidadeDeleteRecursion( getQuadTreeNodeSE(node), obj2, outFileTxt, outString, res, disabledNodes );
    }
}

static int commandCidadeDeleteProcNode( Object *obj1, Object *obj2, FILE *outFileTxt, char *outString, Resumo *res ){
    if( res != NULL ){
        incCpd(res);
    }
    if( objInsideObj( obj1, obj2 ) == 1 ){
        fprintf( outFileTxt, outString, getObjId(obj1) );
        if( res != NULL ){
            incDel(res);
        }
        return 1;
    }
    return 0;
}

void commandSearchIdCep( char *line, Cidade *c, FILE *outFileTxt, int method ){
    List *list[4];
    QuadTree *qt[4];
    char *outString[4];
    Node *node;
    char idCep[1000];
    int i, ret;

    fputs(line,outFileTxt);

    sscanf(line, "crd? %s", idCep);

    list[0] = getCidadeQuadras(c);
    list[1] = getCidadeHidrantes(c);
    list[2] = getCidadeSemaforos(c);
    list[3] = getCidadeTorres(c);

    qt[0] = getCidadeQuadrasQT(c);
    qt[1] = getCidadeHidrantesQT(c);
    qt[2] = getCidadeSemaforosQT(c);
    qt[3] = getCidadeTorresQT(c);

    outString[0] = "Quadra";
    outString[1] = "Hidrante";
    outString[2] = "Semaforo";
    outString[3] = "Torre";

    ret = 0;

    if( method == 0 ){
        for( i = 0; i < 4; i++ ){
            node = getFirst(list[i]);
            while( node != NULL && ret == 0 ){
                ret = commandSearchIdCepProcNode( get(node), idCep, outFileTxt, outString[i] );
                node = getNext(node);
            }
        }
    }
    else{
        for( i = 0; i < 4; i++ ){
            if( commandSearchIdCepRecursion( getQuadTreeRoot(qt[i]), idCep, outFileTxt, outString[i] ) == 1 ) return;
        }
    }

    if( ret == 0 ){
        fprintf( outFileTxt, "Elemento com ID/Cep %s não encontrado\n\n", idCep );
    }
}

static int commandSearchIdCepRecursion( QuadTreeNode *node, char *idCep, FILE *outFileTxt, char *outString ){
    Object *obj;
    if( node != NULL ){
        obj = getQuadTreeNodeData(node);
        if( obj != NULL ){
            if( commandSearchIdCepProcNode( obj, idCep, outFileTxt, outString ) == 1 ) return 1;
        }
        if( commandSearchIdCepRecursion( getQuadTreeNodeNW(node), idCep, outFileTxt, outString ) == 1 ) return 1;
        if( commandSearchIdCepRecursion( getQuadTreeNodeNE(node), idCep, outFileTxt, outString ) == 1 ) return 1;
        if( commandSearchIdCepRecursion( getQuadTreeNodeSW(node), idCep, outFileTxt, outString ) == 1 ) return 1;
        if( commandSearchIdCepRecursion( getQuadTreeNodeSE(node), idCep, outFileTxt, outString ) == 1 ) return 1;
    }
    return 0;
}

static int commandSearchIdCepProcNode( Object *obj, char *idCep, FILE *outFileTxt, char *outString ){
    if( strcmp( getObjId(obj), idCep ) == 0 ){
        fprintf( outFileTxt, "Encontrado %s com coordenadas (%f,%f)\n\n", outString, getX(obj), getY(obj) );
        return 1;
    }
    return 0;
}

static int objInsideObj(Object *obj1, Object *obj2){
    typedef int (*funcQuadraInside)(void*,Quadra*);
    typedef int (*funcPointInside)(void*,double,double);

    char type1, type2;
    void *data1, *data2;
    funcQuadraInside quadraInside;
    funcPointInside pointInside;

    type1 = getObjType(obj1);
    type2 = getObjType(obj2);
    data1 = getObjData(obj1);
    data2 = getObjData(obj2);

    if( type2 == 'c' ){
        quadraInside = (funcQuadraInside)quadraInsideCircle;
        pointInside = (funcPointInside)pointInsideCircle;
    }
    else if( type2 == 'r' ){
        quadraInside = (funcQuadraInside)quadraInsideRect;
        pointInside = (funcPointInside)pointInsideRect;
    }

    if( type1 == 'q' ){
        return quadraInside( data2, data1 );
    }
    if( type1 == 'h' || type1 == 's' || type1 == 't' ){
        return pointInside( data2, getPointX(data1), getPointY(data1) );
    }

    return 0;
}
