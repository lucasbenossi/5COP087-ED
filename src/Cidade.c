#include <stdlib.h>
#include "Cidade.h"
#include "ObjList.h"
#include "LinkedList.h"
#include "ProcString.h"

struct _cidade{
    List *quadras;
    char *quadrasFill;
    char *quadrasStroke;
    List *hidrantes;
    char *hidrantesFill;
    char *hidrantesStroke;
    List *semaforos;
    char *semaforosFill;
    char *semaforosStroke;
    List *torres;
    char *torresFill;
    char *torresStroke;
};
typedef struct _cidade CidadeStr;

Cidade *createCidade(){
    CidadeStr *c;
    c = malloc( sizeof(CidadeStr) );

    c->quadras = createList();
    c->quadrasFill = createString("rgb(153,204,255)");
    c->quadrasStroke = createString("black");

    c->hidrantes = createList();
    c->hidrantesFill = createString("rgb(255,0,0)");
    c->hidrantesStroke = createString("black");

    c->semaforos = createList();
    c->semaforosFill = createString("rgb(153,153,153)");
    c->semaforosStroke = createString("black");

    c->torres = createList();
    c->torresFill = createString("rgb(255,102,0)");
    c->torresStroke = createString("black");

    return c;
}

void destroyCidade(Cidade *c){
    CidadeStr *c0;
    c0 = c;

    destroyObjList(c0->quadras);
    destroyString(c0->quadrasFill);
    destroyString(c0->quadrasStroke);

    destroyObjList(c0->hidrantes);
    destroyString(c0->hidrantesFill);
    destroyString(c0->hidrantesStroke);

    destroyObjList(c0->semaforos);
    destroyString(c0->semaforosFill);
    destroyString(c0->semaforosStroke);

    destroyObjList(c0->torres);
    destroyString(c0->torresFill);
    destroyString(c0->torresStroke);

    free(c);
}

List *getCidadeQuadras(Cidade *c){
    return ((CidadeStr*)c)->quadras;
}

char *getCidadeQuadrasFill(Cidade *c){
    return ((CidadeStr*)c)->quadrasFill;
}

char *getCidadeQuadrasStroke(Cidade *c){
    return ((CidadeStr*)c)->quadrasStroke;
}

List *getCidadeHidrantes(Cidade *c){
    return ((CidadeStr*)c)->hidrantes;
}

char *getCidadeHidrantesFill(Cidade *c){
    return ((CidadeStr*)c)->hidrantesFill;
}

char *getCidadeHidrantesStroke(Cidade *c){
    return ((CidadeStr*)c)->hidrantesStroke;
}

List *getCidadeSemaforos(Cidade *c){
    return ((CidadeStr*)c)->semaforos;
}

char *getCidadeSemaforosFill(Cidade *c){
    return ((CidadeStr*)c)->semaforosFill;
}

char *getCidadeSemaforosStroke(Cidade *c){
    return ((CidadeStr*)c)->semaforosStroke;
}

List *getCidadeTorres(Cidade *c){
    return ((CidadeStr*)c)->torres;
}

char *getCidadeTorresFill(Cidade *c){
    return ((CidadeStr*)c)->torresFill;
}

char *getCidadeTorresStroke(Cidade *c){
    return ((CidadeStr*)c)->torresStroke;
}

void setCidadeQuadrasColors(Cidade *c, char *fill, char *stroke){
    repString( &( ((CidadeStr*)c)->quadrasFill ), fill );
    repString( &( ((CidadeStr*)c)->quadrasStroke ), stroke );
}

void setCidadeHidrantesColors(Cidade *c, char *fill, char *stroke){
    repString( &( ((CidadeStr*)c)->hidrantesFill ), fill );
    repString( &( ((CidadeStr*)c)->hidrantesStroke ), stroke );
}

void setCidadeSemaforosColors(Cidade *c, char *fill, char *stroke){
    repString( &( ((CidadeStr*)c)->semaforosFill ), fill );
    repString( &( ((CidadeStr*)c)->semaforosStroke ), stroke );
}

void setCidadeTorresColors(Cidade *c, char *fill, char *stroke){
    repString( &( ((CidadeStr*)c)->torresFill ), fill );
    repString( &( ((CidadeStr*)c)->torresStroke ), stroke );
}
