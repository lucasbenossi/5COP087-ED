#include <stdio.h>
#include <stdlib.h>
#include "CreateSvg.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "Object.h"
#include "WriteTags.h"
#include "Cidade.h"
#include "File.h"

void createSvg( List *l, Cidade *c, char *file, char *fixedDir ){
    char *fullPath;
    FILE *svg;
    List *list;
    Node *node;
    void *objData;
    char objType;

    fullPath = createStringCat( fixedDir, file, ".svg", NULL, NULL );
    svg = openFileWrite(fullPath);
    if( svg == NULL ){
		destroyString(fullPath);
		return;
    }

    fprintf( svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    list = getCidadeQuadras(c);
    node = getFirst(list);
    while( node != NULL ){
        writeQuadraTag( getObjData(get(list,node)), svg );
		node = getNext(list,node);
    }

    list = getCidadeHidrantes(c);
    node = getFirst(list);
    while( node != NULL ){
        writeHidranteTag( getObjData(get(list,node)), svg );
        node = getNext(list,node);
    }

    list = getCidadeSemaforos(c);
    node = getFirst(list);
    while( node != NULL ){
        writeSemaforoTag( getObjData(get(list,node)), svg );
        node = getNext(list,node);
    }

    list = getCidadeTorres(c);
    node = getFirst(list);
    while( node != NULL ){
        writeTorreTag( getObjData(get(list,node)), svg );
        node = getNext(list,node);
    }

    list = l;
    node = getFirst(list);
    while( node != NULL ){
        objData = getObjData( get(list,node) );
        objType = getObjType( get(list,node) );
        if( objType == 'c' ){
            writeCircleTag( objData, svg );
        }
        else if( objType == 'r' ){
            writeRectTag( objData, svg );
        }
        else if( objType == 'o' ){
            writeOverlapTag( objData, svg );
        }
		node = getNext(list,node);
    }

    fprintf(svg, "</svg>");

	closeFile(svg);

	destroyString(fullPath);
}
