#include <stdlib.h>
#include "Cidade.h"
#include "ObjList.h"
#include "ObjQuadTree.h"
#include "LinkedList.h"
#include "ProcString.h"
#include "QuadTree.h"

struct _cidade{
    List *quadras;
    QuadTree *quadrasQT;
    char *quadrasFill;
    char *quadrasStroke;
    List *hidrantes;
    QuadTree *hidrantesQT;
    char *hidrantesFill;
    char *hidrantesStroke;
    List *semaforos;
    QuadTree *semaforosQT;
    char *semaforosFill;
    char *semaforosStroke;
    List *torres;
    QuadTree *torresQT;
    char *torresFill;
    char *torresStroke;
};

Cidade *createCidade(){
    Cidade *c;
    c = malloc( sizeof(Cidade) );

    c->quadras = createList();
    c->quadrasQT = createQuadTree();
    c->quadrasFill = createString("rgb(153,204,255)");
    c->quadrasStroke = createString("black");

    c->hidrantes = createList();
    c->hidrantesQT = createQuadTree();
    c->hidrantesFill = createString("rgb(255,0,0)");
    c->hidrantesStroke = createString("black");

    c->semaforos = createList();
    c->semaforosQT = createQuadTree();
    c->semaforosFill = createString("rgb(153,153,153)");
    c->semaforosStroke = createString("black");

    c->torres = createList();
    c->torresQT = createQuadTree();
    c->torresFill = createString("rgb(255,102,0)");
    c->torresStroke = createString("black");

    return c;
}

void destroyCidade(Cidade *c){
    destroyObjList(c->quadras);
    destroyObjQuadTree(c->quadrasQT);
    destroyString(c->quadrasFill);
    destroyString(c->quadrasStroke);

    destroyObjList(c->hidrantes);
    destroyObjQuadTree(c->hidrantesQT);
    destroyString(c->hidrantesFill);
    destroyString(c->hidrantesStroke);

    destroyObjList(c->semaforos);
    destroyObjQuadTree(c->semaforosQT);
    destroyString(c->semaforosFill);
    destroyString(c->semaforosStroke);

    destroyObjList(c->torres);
    destroyObjQuadTree(c->torresQT);
    destroyString(c->torresFill);
    destroyString(c->torresStroke);

    free(c);
}

void cidadeListToQuadTree(Cidade *c, int method){
    int i;
    List *list[4];
    QuadTree *qt[4];
    void (*listToQt)(List*,QuadTree*);

    if( method == 0 ){
        return;
    }
    else if( method == 1 ){
        listToQt = objListToQuadTree;
    }
    else if( method == 2 ){
        listToQt = objListToQuadTreeNoSort;
    }
    else if( method == 3 ){
        listToQt = objListToQuadTreeNoConvexHull;
    }

    list[0] = getCidadeQuadras(c);
    list[1] = getCidadeHidrantes(c);
    list[2] = getCidadeSemaforos(c);
    list[3] = getCidadeTorres(c);
    qt[0] = getCidadeQuadrasQT(c);
    qt[1] = getCidadeHidrantesQT(c);
    qt[2] = getCidadeSemaforosQT(c);
    qt[3] = getCidadeTorresQT(c);

    for( i = 0; i < 4; i++ ){
        listToQt( list[i], qt[i] );
        freeList( list[i] );
    }
}

List *getCidadeQuadras(Cidade *c){
    return c->quadras;
}

QuadTree *getCidadeQuadrasQT(Cidade *c){
    return c->quadrasQT;
}

char *getCidadeQuadrasFill(Cidade *c){
    return c->quadrasFill;
}

char *getCidadeQuadrasStroke(Cidade *c){
    return c->quadrasStroke;
}

List *getCidadeHidrantes(Cidade *c){
    return c->hidrantes;
}

QuadTree *getCidadeHidrantesQT(Cidade *c){
    return c->hidrantesQT;
}

char *getCidadeHidrantesFill(Cidade *c){
    return c->hidrantesFill;
}

char *getCidadeHidrantesStroke(Cidade *c){
    return c->hidrantesStroke;
}

List *getCidadeSemaforos(Cidade *c){
    return c->semaforos;
}

QuadTree *getCidadeSemaforosQT(Cidade *c){
    return c->semaforosQT;
}

char *getCidadeSemaforosFill(Cidade *c){
    return c->semaforosFill;
}

char *getCidadeSemaforosStroke(Cidade *c){
    return c->semaforosStroke;
}

List *getCidadeTorres(Cidade *c){
    return c->torres;
}

QuadTree *getCidadeTorresQT(Cidade *c){
    return c->torresQT;
}

char *getCidadeTorresFill(Cidade *c){
    return c->torresFill;
}

char *getCidadeTorresStroke(Cidade *c){
    return c->torresStroke;
}

void setCidadeQuadrasColors(Cidade *c, char *fill, char *stroke){
    repString( &( c->quadrasFill ), fill );
    repString( &( c->quadrasStroke ), stroke );
}

void setCidadeHidrantesColors(Cidade *c, char *fill, char *stroke){
    repString( &( c->hidrantesFill ), fill );
    repString( &( c->hidrantesStroke ), stroke );
}

void setCidadeSemaforosColors(Cidade *c, char *fill, char *stroke){
    repString( &( c->semaforosFill ), fill );
    repString( &( c->semaforosStroke ), stroke );
}

void setCidadeTorresColors(Cidade *c, char *fill, char *stroke){
    repString( &( c->torresFill ), fill );
    repString( &( c->torresStroke ), stroke );
}
