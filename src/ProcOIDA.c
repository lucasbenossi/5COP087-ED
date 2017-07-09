#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Circle.h"
#include "Rect.h"
#include "ProcString.h"
#include "Geometry.h"
#include "ProcOIDA.h"
#include "WriteTags.h"

void procA( List *l, char *line, char *file, char *fixedDir ){
    char color[10000], sufix[10000], *fileSufix, *fullPath;
    FILE *svg;
    int i;
    double r, x, y, w, h;
    Node *node;

	sscanf(line, "%*c %s %s", sufix, color);

    fileSufix = allocChar(0);
    catString( &fileSufix, file );
    catString( &fileSufix, "-" );
    catString( &fileSufix, sufix );

    fullPath = genFullPath(fixedDir, fileSufix, "svg");

    svg = fopen( fullPath, "w" );

    if( svg == NULL ){
        printf("Erro ao criar o arquivo %s\n",fullPath);
		free(fullPath);
		return;
    }

    i = 1;
    r = 5.0;

    node = l->head;

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
	while( node != NULL ){
		if( node->type == 1 ){
            /*writeCircleTag( node->data, svg );*/
            x = getCircleX( node->data );
            y = getCircleY( node->data );
            writeTag( i, r, x, y, color, svg );
            i++;
		}
        else if( node->type == 2 ){
            /*writeRectTag( node->data, svg );*/
            w = getRectWidth( node->data );
            h = getRectHeight( node->data );
            x = getRectX( node->data );
            y = getRectY( node->data );
            writeTag( i, r, x, y, color, svg );
            i++;
            writeTag( i, r, x+w, y, color, svg );
            i++;
            writeTag( i, r, x, y+h, color, svg );
            i++;
            writeTag( i, r, x+w, y+h, color, svg );
            i++;
        }
        /*printf("svg-sufix %d\n",node->id);*/
		node = node->next;
	}
    fprintf(svg, "</svg>");

    fclose(svg);

    free(fileSufix);
    free(fullPath);
}

void procO( char *line, List *l, char *file, char *fixedDir ){
	int j, k, i;
	double x1, y1, x2, y2;
	Node *objJ, *objK;

	sscanf(line, "%*c %d %d", &j, &k);
	objJ = getId(l,j);
	objK = getId(l,k);

    if( objJ == NULL && objK == NULL ){
        createTxtError( line, file, fixedDir, 2, j, k );
        return;
    }
    else if( objJ == NULL || objK == NULL ){
        if( objJ == NULL ){
            createTxtError( line, file, fixedDir, 1, j, 0 );
        }
        else if( objK == NULL ){
            createTxtError( line, file, fixedDir, 1, k, 0 );
        }
        return;
    }

	i = 0;

	if( objJ->type == 1 && objK->type == 1 ){
		if( circleCircleOverlap( objJ->data, objK->data ) == 1 ){
			edgesCircleCircle( objJ->data, objK->data, &x1, &y1, &x2, &y2 );
            insert( l, createNode( i, 3, createRect(i, x2-x1, y2-y1, x1, y1, allocChar(0)) ) );
            createTxt( line, file, fixedDir, "Sim" );
		}
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
	}
	else if( objJ->type == 2 && objK->type == 2 ){
		if( rectRectOverlap( objJ->data, objK->data ) == 1 ){
			edgesRectRect( objJ->data, objK->data, &x1, &y1, &x2, &y2 );
            insert( l, createNode( i, 3, createRect(i, x2-x1, y2-y1, x1, y1, allocChar(0)) ) );
            createTxt( line, file, fixedDir, "Sim" );
		}
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
	}
    else if( objJ->type == 1 && objK->type == 2 ){
        if( circleRectOverlap( objJ->data, objK->data ) == 1 ){
			edgesCircleRect( objJ->data, objK->data, &x1, &y1, &x2, &y2 );
            insert( l, createNode( i, 3, createRect(i, x2-x1, y2-y1, x1, y1, allocChar(0)) ) );
            createTxt( line, file, fixedDir, "Sim" );
		}
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
    }
    else if( objJ->type == 2 && objK->type == 1 ){
        if( circleRectOverlap( objK->data, objJ->data ) == 1 ){
			edgesCircleRect( objK->data, objJ->data, &x1, &y1, &x2, &y2 );
            insert( l, createNode( i, 3, createRect(i, x2-x1, y2-y1, x1, y1, allocChar(0)) ) );
            createTxt( line, file, fixedDir, "Sim" );
		}
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
    }
}

void procI( List *l, char *line, char *file, char *fixedDir ){
    Node *obj;
    double x, y;
    int j;

	sscanf(line, "%*c %d %lf %lf", &j, &x, &y);
	obj = getId(l,j);

    if( obj == NULL ){
        createTxtError( line, file, fixedDir, 1, j, 0 );
        return;
    }

    if( obj->type == 1 ){
        if( pointInsideCircle( obj->data, x, y ) == 1 ){
            createTxt( line, file, fixedDir, "Sim" );
        }
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
    }
    else if( obj->type == 2 ){
        if( pointInsideRect( obj->data, x, y ) == 1 ){
            createTxt( line, file, fixedDir, "Sim" );
        }
        else{
            createTxt( line, file, fixedDir, "Nao" );
        }
    }
}

void procD( List *l, char *line, char *file, char *fixedDir ){
	int j, k;
    double x1, y1, x2, y2, d;
    char string[10000];
	Node *objJ, *objK;

	sscanf(line, "%*c %d %d", &j, &k);
	objJ = getId(l,j);
	objK = getId(l,k);

	if( objJ == NULL && objK == NULL ){
        createTxtError( line, file, fixedDir, 2, j, k );
        return;
    }
    else if( objJ == NULL || objK == NULL ){
        if( objJ == NULL ){
            createTxtError( line, file, fixedDir, 1, j, 0 );
        }
        else if( objK == NULL ){
            createTxtError( line, file, fixedDir, 1, k, 0 );
        }
        return;
    }

    if( objJ->type == 1 ){
        x1 = getCircleX(objJ->data);
        y1 = getCircleY(objJ->data);
    }
    else if( objJ->type == 2 ){
        x1 = getRectX(objJ->data) + ( getRectWidth(objJ->data) / 2 );
        y1 = getRectY(objJ->data) + ( getRectHeight(objJ->data) / 2 );
    }

    if( objK->type == 1 ){
        x2 = getCircleX(objK->data);
        y2 = getCircleY(objK->data);
    }
    else if( objK->type == 2 ){
        x2 = getRectX(objK->data) + ( getRectWidth(objK->data) / 2 );
        y2 = getRectY(objK->data) + ( getRectHeight(objK->data) / 2 );
    }

    d = distancePoints( x1, y1, x2, y2 );
    sprintf(string,"%f",d);
    createTxt( line, file, fixedDir, string );
}

void writeTag( int i, double r, double x, double y, char *color, FILE *svg ){
    void *obj;
    obj = createCircle(i, r, x, y, color);
    writeCircleTag( obj, svg );
    destroyCircle(obj);
}

void createTxt( char *line, char *file, char *fixedDir, char *string ){
    char *fullPath;
    FILE *txt;

    fullPath = genFullPath(fixedDir, file, "txt");

    txt = fopen(fullPath,"a");

    if( txt == NULL ){
        printf("Erro ao criar o arquivo %s\n",fullPath);
		free(fullPath);
		return;
    }

    fputs(line,txt);
    fprintf(txt, "%s\n", string);

    fclose(txt);

    free(fullPath);
}

void createTxtError( char *line, char *file, char *fixedDir, int qtd, int id1, int id2 ){
    char *fullPath;
    FILE *txt;

    fullPath = genFullPath(fixedDir, file, "txt");

    txt = fopen(fullPath,"a");

    if( txt == NULL ){
        printf("Erro ao criar o arquivo %s\n",fullPath);
		free(fullPath);
		return;
    }

    fputs(line,txt);
    if( qtd == 1 ){
        fprintf( txt, "ID %d nao encontrado\n", id1 );
    }
    else if( qtd == 2 ){
        fprintf( txt, "ID %d e %d nao encontrados\n", id1, id2 );
    }

    fclose(txt);

    free(fullPath);
}
