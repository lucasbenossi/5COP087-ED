#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "Geometry.h"
#include "Cidade.h"
#include "Quadra.h"
#include "Point.h"
#include "Rect.h"
#include "Circle.h"
#include "Object.h"
#include "ProcString.h"
#include "CommandsT3.h"
#include "Resumo.h"

void commandCidadeInsert( char *line, Cidade *c, Resumo *res ){
    double x, y, width, height;
    char idCep[1000];
    if( line[0] == 'q' ){
        sscanf(line, "q %lf %lf %lf %lf %[^\r\n]s", &x, &y, &width, &height, idCep);
        insert( getCidadeQuadras(c), createObject( 0, 'q', createQuadra( x, y, width, height, idCep, getCidadeQuadrasFill(c), getCidadeQuadrasStroke(c) ) ) );
        if( res != NULL ){
            incIns(res);
            incCpi(res);
        }
    }
    else if( line[0] == 'h' ){
        sscanf(line, "h %lf %lf %s", &x, &y, idCep);
        insert( getCidadeHidrantes(c), createObject( 0, 'h', createPoint( x, y, idCep, getCidadeHidrantesFill(c), getCidadeHidrantesStroke(c) ) ) );
    }
    else if( line[0] == 's' ){
        sscanf(line, "s %lf %lf %s", &x, &y, idCep);
        insert( getCidadeSemaforos(c), createObject( 0, 's', createPoint( x, y, idCep, getCidadeSemaforosFill(c), getCidadeSemaforosStroke(c) ) ) );
    }
    else if( line[0] == 't' ){
        sscanf(line, "t %lf %lf %s", &x, &y, idCep);
        insert( getCidadeTorres(c), createObject( 0, 't', createPoint( x, y, idCep, getCidadeTorresFill(c), getCidadeTorresStroke(c) ) ) );
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

void commandCidadeDeleteRect( char *line, Cidade *c, FILE *outFileTxt, Resumo *res ){
    double x, y, width, height;
    char command;
    Rect *rect;
    List *list;
    Node *node, *node0;
    void *objData;

    fputs(line,outFileTxt);

    sscanf(line, "d%c %lf %lf %lf %lf", &command, &x, &y, &width, &height);
    rect = createRect(0, width, height, x, y, "");

    if( command == 'q' ){
        list = getCidadeQuadras(c);
        node = getFirst(list);
        while( node != NULL ){
            if( res != NULL ){
                incCpd(res);
            }
            if( quadraInsideRect( rect, getObjData(get(list,node)) ) == 1 ){
                fprintf( outFileTxt, "Quadra %s removida\n", getQuadraCep(getObjData(get(list,node))) );
                node0 = node;
                node = getNext(list,node);
                destroyQuadra( destroyObject( removeNode( list, node0 ) ) );
                if( res != NULL ){
                    incDel(res);
                }
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 'h' ){
        list = getCidadeHidrantes(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideRect( rect, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Hidrante %s removido\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 's' ){
        list = getCidadeSemaforos(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideRect( rect, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Semaforo %s removido\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 't' ){
        list = getCidadeTorres(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideRect( rect, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Torre %s removida\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else{
        return;
    }

    fprintf( outFileTxt, "\n" );

    destroyRect(rect);
}

void commandCidadeDeleteCircle( char *line, Cidade *c, FILE *outFileTxt, Resumo *res ){
    double x, y, radius;
    char command;
    Circle *circle;
    List *list;
    Node *node, *node0;
    void *objData;

    fputs(line,outFileTxt);

    sscanf(line, "D%c %lf %lf %lf", &command, &x, &y, &radius);
    circle = createCircle(0, radius, x, y, "");

    if( command == 'q' ){
        list = getCidadeQuadras(c);
        node = getFirst(list);
        while( node != NULL ){
            if( res != NULL ){
                incCpd(res);
            }
            if( quadraInsideCircle( circle, getObjData(get(list,node)) ) == 1 ){
                fprintf( outFileTxt, "Quadra %s removida\n", getQuadraCep(getObjData(get(list,node))) );
                node0 = node;
                node = getNext(list,node);
                destroyQuadra( destroyObject( removeNode( list, node0 ) ) );
                if( res != NULL ){
                    incDel(res);
                }
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 'h' ){
        list = getCidadeHidrantes(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideCircle( circle, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Hidrante %s removido\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 's' ){
        list = getCidadeSemaforos(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideCircle( circle, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Semaforo %s removido\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else if( command == 't' ){
        list = getCidadeTorres(c);
        node = getFirst(list);
        while( node != NULL ){
            objData = getObjData(get(list,node));
            if( pointInsideCircle( circle, getPointX(objData), getPointY(objData) ) == 1 ){
                fprintf( outFileTxt, "Torre %s removida\n", getPointId(objData) );
                node0 = node;
                node = getNext(list,node);
                destroyPoint( destroyObject( removeNode( list, node0 ) ) );
            }
            else{
                node = getNext(list,node);
            }
        }
    }
    else{
        return;
    }

    fprintf( outFileTxt, "\n" );

    destroyCircle(circle);
}

void commandSearchIdCep( char *line, Cidade *c, FILE *outFileTxt ){
    List *list;
    Node *node;
    void *objData;
    char idCep[1000];

    fputs(line,outFileTxt);

    sscanf(line, "crd? %[^\r\n]s", idCep);

    list = getCidadeQuadras(c);
    node = getFirst(list);
    while( node != NULL ){
        objData = getObjData(get(list,node));
        if( strcmp( getQuadraCep(objData), idCep ) == 0 ){
            fprintf( outFileTxt, "Encontrado Quadra com coordenadas (%f,%f)\n\n", getQuadraX(objData), getQuadraY(objData) );
            return;
        }
        node = getNext(list,node);
    }

    list = getCidadeHidrantes(c);
    node = getFirst(list);
    while( node != NULL ){
        objData = getObjData(get(list,node));
        if( strcmp( getPointId(objData), idCep ) == 0 ){
            fprintf( outFileTxt, "Encontrado Hidrante com coordenadas (%f,%f)\n\n", getPointX(objData), getPointY(objData) );
            return;
        }
        node = getNext(list,node);
    }

    list = getCidadeSemaforos(c);
    node = getFirst(list);
    while( node != NULL ){
        objData = getObjData(get(list,node));
        if( strcmp( getPointId(objData), idCep ) == 0 ){
            fprintf( outFileTxt, "Encontrado Semaforo com coordenadas (%f,%f)\n\n", getPointX(objData), getPointY(objData) );
            return;
        }
        node = getNext(list,node);
    }

    list = getCidadeTorres(c);
    node = getFirst(list);
    while( node != NULL ){
        objData = getObjData(get(list,node));
        if( strcmp( getPointId(objData), idCep ) == 0 ){
            fprintf( outFileTxt, "Encontrada Torre com coordenadas (%f,%f)\n\n", getPointX(objData), getPointY(objData) );
            return;
        }
        node = getNext(list,node);
    }

    fprintf( outFileTxt, "Elemento com ID/Cep %s não encontrado\n\n", idCep );
}
