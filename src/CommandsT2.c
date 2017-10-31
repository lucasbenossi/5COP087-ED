#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Circle.h"
#include "Rect.h"
#include "Object.h"
#include "ProcString.h"
#include "Geometry.h"
#include "CommandsT2.h"
#include "WriteTags.h"
#include "ObjList.h"
#include "File.h"

void procC( char *line, List *l ){
    int i;
    double r, x, y;
    char color[10000], *id;
	sscanf(line, "c %d %lf %lf %lf %s", &i, &r, &x, &y, color);
    id = createStringInt(i);
	insert( l, createObject( id, 'c', createCircle(i, r, x, y, color) ) );
    destroyString(id);
}

void procR( char *line, List *l ){
    int i;
    double w, h, x, y;
    char color[10000], *id;
	sscanf(line, "r %d %lf %lf %lf %lf %s", &i, &w, &h, &x, &y, color);
    id = createStringInt(i);
	insert( l, createObject( id, 'r', createRect(i, w, h, x, y, color) ) );
    destroyString(id);
}

void procA( char *line, List *l, char *file, char *fixedDir ){
    char fill[10000], sufix[10000], *fileSufix, *fullPath;
    FILE *svg;
    int i;
    double x, y, w, h;
    Node *node;
    Circle *c;
    void *objData;
    int objType;

	sscanf(line, "a %s %s", sufix, fill);

    fileSufix = createStringCat( 3, file, "-", sufix );
    fullPath = createStringCat( 3, fixedDir, fileSufix, ".svg" );

    svg = openFileWrite( fullPath );
    if( svg == NULL ){
        destroyString(fileSufix);
		destroyString(fullPath);
		return;
    }

    c = createCircle(0, 5.0, 0.0, 0.0, fill);

    writeSvgStart(svg);
    node = getFirst(l);
    i = 1;
	while( node != NULL ){
        objData = getObjData(get(node));
        objType = getObjType(get(node));
		if( objType == 'c' ){
            x = getCircleX( objData );
            y = getCircleY( objData );
            writeTag( c, i, x, y, svg );
            i++;
		}
        else if( objType == 'r' ){
            w = getRectWidth( objData );
            h = getRectHeight( objData );
            x = getRectX( objData );
            y = getRectY( objData );
            writeTag( c, i, x, y, svg );
            i++;
            writeTag( c, i, x+w, y, svg );
            i++;
            writeTag( c, i, x, y+h, svg );
            i++;
            writeTag( c, i, x+w, y+h, svg );
            i++;
        }
		node = getNext(node);
	}
    writeSvgEnd(svg);

    closeFile(svg);

    destroyCircle(c);

    destroyString(fileSufix);
    destroyString(fullPath);
}

void writeTag( Circle *c, int i, double x, double y, FILE *svg ){
    setCircleId(c,i);
    setCircleX(c,x);
    setCircleY(c,y);
    writeCircleTag( c, svg );
}

void procO( char *line, List *l, FILE *outFileTxt ){
	int j, k, i;
    char *id;
	double x1, y1, x2, y2;
	Object *objJ, *objK;

    fputs(line,outFileTxt);

	sscanf(line, "o %d %d", &j, &k);
	objJ = searchIdInt(l,j);
	objK = searchIdInt(l,k);

    if( objJ == NULL && objK == NULL ){
        fprintf( outFileTxt, "IDs %d e %d nao encontrados\n\n", j, k );
        return;
    }
    else if( objJ == NULL || objK == NULL ){
        if( objJ == NULL ){
            fprintf( outFileTxt, "ID %d nao encontrado\n\n", j );
        }
        else if( objK == NULL ){
            fprintf( outFileTxt, "ID %d nao encontrado\n\n", k );
        }
        return;
    }

	i = 0;
    id = NULL;

	if( getObjType(objJ) == 'c' && getObjType(objK) == 'c' ){
		if( circleCircleOverlap( getObjData(objJ), getObjData(objK) ) == 1 ){
			edgesCircleCircle( getObjData(objJ), getObjData(objK), &x1, &y1, &x2, &y2 );
            insert( l, createObject( id, 'o', createRect(i, x2-x1, y2-y1, x1, y1, "") ) );
            fprintf(outFileTxt, "Sim\n");
		}
        else{
            fprintf(outFileTxt, "Não\n");
        }
	}
	else if( getObjType(objJ) == 'r' && getObjType(objK) == 'r' ){
		if( rectRectOverlap( getObjData(objJ), getObjData(objK) ) == 1 ){
			edgesRectRect( getObjData(objJ), getObjData(objK), &x1, &y1, &x2, &y2 );
            insert( l, createObject( id, 'o', createRect(i, x2-x1, y2-y1, x1, y1, "") ) );
            fprintf(outFileTxt, "Sim\n");
		}
        else{
            fprintf(outFileTxt, "Não\n");
        }
	}
    else if( getObjType(objJ) == 'c' && getObjType(objK) == 'r' ){
        if( circleRectOverlap( getObjData(objJ), getObjData(objK) ) == 1 ){
			edgesCircleRect( getObjData(objJ), getObjData(objK), &x1, &y1, &x2, &y2 );
            insert( l, createObject( id, 'o', createRect(i, x2-x1, y2-y1, x1, y1, "") ) );
            fprintf(outFileTxt, "Sim\n");
		}
        else{
            fprintf(outFileTxt, "Não\n");
        }
    }
    else if( getObjType(objJ) == 'r' && getObjType(objK) == 'c' ){
        if( circleRectOverlap( getObjData(objK), getObjData(objJ) ) == 1 ){
			edgesCircleRect( getObjData(objK), getObjData(objJ), &x1, &y1, &x2, &y2 );
            insert( l, createObject( id, 'o', createRect(i, x2-x1, y2-y1, x1, y1, "") ) );
            fprintf(outFileTxt, "Sim\n");
		}
        else{
            fprintf(outFileTxt, "Não\n");
        }
    }
    fprintf(outFileTxt, "\n");
}

void procI( char *line, List *l, FILE *outFileTxt ){
    Object *obj;
    double x, y;
    int j, ret;

    fputs(line,outFileTxt);

	sscanf(line, "i %d %lf %lf", &j, &x, &y);
	obj = searchIdInt(l,j);

    if( obj == NULL ){
        fprintf( outFileTxt, "ID %d nao encontrados\n\n", j );
        return;
    }

    if( getObjType(obj) == 'c' ){
        ret = pointInsideCircle( getObjData(obj), x, y );
    }
    else if( getObjType(obj) == 'r' ){
        ret = pointInsideRect( getObjData(obj), x, y );
    }

    if( ret == 1 ){
        fprintf(outFileTxt, "Sim\n");
    }
    else{
        fprintf(outFileTxt, "Não\n");
    }

    fprintf(outFileTxt, "\n");
}

void procD( char *line, List *l, FILE *outFileTxt ){
	int j, k;
    double x1, y1, x2, y2, d;
	Object *objJ, *objK;

    fputs(line,outFileTxt);

	sscanf(line, "d %d %d", &j, &k);
	objJ = searchIdInt(l,j);
	objK = searchIdInt(l,k);

	if( objJ == NULL && objK == NULL ){
        fprintf( outFileTxt, "IDs %d e %d nao encontrados\n\n", j, k );
        return;
    }
    else if( objJ == NULL || objK == NULL ){
        if( objJ == NULL ){
            fprintf( outFileTxt, "ID %d nao encontrado\n\n", j );
        }
        else if( objK == NULL ){
            fprintf( outFileTxt, "ID %d nao encontrado\n\n", k );
        }
        return;
    }

    if( getObjType(objJ) == 'c' ){
        x1 = getCircleX( getObjData(objJ) );
        y1 = getCircleY( getObjData(objJ) );
    }
    else if( getObjType(objJ) == 'r' ){
        x1 = getRectX( getObjData(objJ) ) + ( getRectWidth( getObjData(objJ) ) / 2 );
        y1 = getRectY( getObjData(objJ) ) + ( getRectHeight( getObjData(objJ) ) / 2 );
    }

    if( getObjType(objK) == 'c' ){
        x2 = getCircleX( getObjData(objK) );
        y2 = getCircleY( getObjData(objK) );
    }
    else if( getObjType(objK) == 'r' ){
        x2 = getRectX( getObjData(objK) ) + ( getRectWidth( getObjData(objK) ) / 2 );
        y2 = getRectY( getObjData(objK) ) + ( getRectHeight( getObjData(objK) ) / 2 );
    }

    d = distancePoints( x1, y1, x2, y2 );
    fprintf(outFileTxt,"%f\n\n",d);
}
