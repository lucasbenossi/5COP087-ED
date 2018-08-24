#include "CommandsGeo.h"
#include "Cidade.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Resumo.h"
#include "Object.h"
#include "Point.h"
#include "Quadra.h"
#include "String.h"
#include "Operadora.h"
#include <stdlib.h>
#include <string.h>

void commandCidadeInsert( char *line, Cidade *c, Resumo *res, char *argR ){
	double x, y, width, height;
	char idCep[STRING_SIZE_LARGE], *errString;
	Point *torre;
	Object *obj;
	double *info, radius;

	if( argR != NULL ){
	    sscanf( argR, "%lf", &radius );
	}

	if( line[0] == 'q' ){
	    sscanf(line, "q %lf %lf %lf %lf %s", &x, &y, &width, &height, idCep);
	    errString = "Quadra de CEP %s ja inserida.\n";
	}
	else if( line[0] == 'h' ){
	    sscanf(line, "h %lf %lf %s", &x, &y, idCep);
	    errString = "Hidrante de ID %s ja inserido.\n";
	}
	else if( line[0] == 's' ){
	    sscanf(line, "s %lf %lf %s", &x, &y, idCep);
	    errString = "Semaforo de ID %s ja inserido.\n";
	}
	else if( line[0] == 't' ){
	    sscanf(line, "t %lf %lf %s", &x, &y, idCep);
	    errString = "Torre de ID %s ja inserida.\n";
	}
	else{
	    return;
	}

	if(searchCidadeObjTypeIdCep(c, line[0], idCep)){
	    fputs( line, stderr );
	    fprintf( stderr, errString, idCep );
	    return;
	}

	if( line[0] == 'q' ){
	    obj = createObject( idCep, 'q', createQuadra( x, y, width, height, idCep, getCidadeQuadrasFill(c), getCidadeQuadrasStroke(c) ) );
	}
	else if( line[0] == 'h' ){
	    obj = createObject( idCep, 'h', createPoint( x, y, idCep, getCidadeHidrantesFill(c), getCidadeHidrantesStroke(c) ) );
	}
	else if( line[0] == 's' ){
	    obj = createObject( idCep, 's', createPoint( x, y, idCep, getCidadeSemaforosFill(c), getCidadeSemaforosStroke(c) ) );
	}
	else if( line[0] == 't' ){
	    torre = createPoint( x, y, idCep, getCidadeTorresFill(c), getCidadeTorresStroke(c) );
	    if( argR != NULL ){
	        info = malloc(sizeof(double));
	        *info = radius;
	        setPointInfo(torre,info);
	    }
	    obj = createObject( idCep, 't', torre );
	}
	cidadeInsertObj( c, obj, line[0], res );
}

void commandCidadeColors( char *line, Cidade *c ){
	char fill[STRING_SIZE_LARGE], stroke[STRING_SIZE_LARGE], command;
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

void commandInsertInfo( char *line, Cidade *c ){
	HashTable *ht;
	double *info, infoValue;
	char command, id[STRING_SIZE_LARGE];
	Object *obj;
	Point *point;

	sscanf( line, "%cI %s %lf", &command, id, &infoValue );

	if( command == 'h' ){
		ht = getCidadeHidrantesHT(c);
	}
	else if( command == 's' ){
		ht = getCidadeSemaforosHT(c);
	}
	else if( command == 't' ){
		ht = getCidadeTorresHT(c);
	}

	obj = searchHashTable(ht, id);
	if( obj == NULL ){
	    fputs( line, stderr );
	    fprintf( stderr, "Objeto de id %s nao encontrado.\n\n", id );
	    return;
	}

	point = getObjData(obj);
	if( getPointInfo(point) != NULL ){
	    free( getPointInfo(point) );
	}
	info = malloc(sizeof(double));
	*info = infoValue;
	setPointInfo( point, info );
}

void commandSetTorreOwner( char *line, Cidade *c ){
	char id[STRING_SIZE], command[STRING_SIZE];
	Operadora *op;
	Object *torre;
	sscanf( line, "%s %s", command, id );

	if( strcmp( command, "su" ) == 0 ){
	    op = getCidadeSercomtuel(c);
	}
	else if( strcmp( command, "um" ) == 0 ){
	    op = getCidadeUelmobile(c);
	}
	else{
	    return;
	}

	torre = searchCidadeTorreId( c, id );
	if( torre == NULL ){
	    fprintf( stderr, "Torre de ID %s nao encontrada.\n", id );
	    return;
	}

	operadoraInsertTorre( op, torre );
}
