#include <stdlib.h>
#include <stdio.h>
#include "Circle.h"
#include "Rect.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "ProcOIDA.h"
#include "CreateSvg.h"
#include "FreeObjList.h"
#include "RunCommands.h"

int runCommands( char *pathFileExt, char *dir, int num ){
	FILE *inFile;
	char line[1000000], *file, *fixedDir;
	List *objs;
	int qtdObjs;

	file = fileRemovePathExt(pathFileExt);

	inFile = fopen(pathFileExt,"r");
    if( inFile == NULL ){
		printf("ERRO: Falha ao abrir o arquivo %s\n",pathFileExt);
		free(file);
		return 1;
	}

	fixedDir = fixDir(dir);

	objs = createList();

	qtdObjs = 0;

	while( fgets(line,1000000,inFile) != NULL ){
		switch( line[0] ){
			case 'c':
                /*c i r x y cor */
				/* type 1 */
				if( qtdObjs == num ){
					printf("Quantidade máxima de objetos atingida.\n");
					break;
				}
				else{
					procC(line, objs);
					qtdObjs++;
				}
				break;
			case 'r':
                /*r i w h x y cor */
				/*type 2 */
				if( qtdObjs == num ){
					printf("Quantidade máxima de objetos atingida.\n");
					break;
				}
				else{
					procR(line, objs);
					qtdObjs++;
				}
				break;
			case 'o':
				procO( line, objs, file, fixedDir );
				break;
			case 'i':
				procI( objs, line, file, fixedDir );
				break;
			case 'd':
				procD( objs, line, file, fixedDir );
				break;
			case 'a':
				procA( objs, line, file, fixedDir );
				break;
            case 'p':
				procP(objs);
				break;
		}
	}

    createSvg(objs, file, fixedDir);

    freeObjList(objs);
	destroyList(objs);

	free(fixedDir);

    fclose(inFile);

	free(file);
	return 0;
}

void procC( char *line, List *l ){
    int k, i;
    double r, x, y;
    char color[10000];
	sscanf(line, "%*s %d %lf %lf %lf %[^\n]s\n", &i, &r, &x, &y, &color);
	insert( l, createNode( i, 1, createCircle(i, r, x, y, allocColor(color)) ) );
}

void procR( char *line, List *l ){
    int k, i;
    double w, h, x, y;
    char color[10000];
	sscanf(line, "%*s %d %lf %lf %lf %lf %[^\n]s\n", &i, &w, &h, &x, &y, &color);
	insert( l, createNode( i, 2, createRect(i, w, h, x, y, allocColor(color)) ) );
}

void procP( List *l ){
	int k;
	Node *node;
	k = 0;
	node = l->head;
	while( node != NULL ){
		printf("[%d]\n",k);
		printf("\ttype = %d\n", node->type );
		if( node->type == 1 ){
			printf("\ti = %d\n",   getCircleId( node->data ) );
			printf("\tr = %f\n",   getCircleRadius( node->data ) );
			printf("\tx = %f\n",   getCircleX( node->data ) );
			printf("\ty = %f\n",   getCircleY( node->data ) );
			printf("\tcor = %s\n", getCircleFill( node->data ) );
		}
		else if( node->type == 2 || node->type == 3 ){
			printf("\ti = %d\n",   getRectId( node->data ) );
			printf("\tw = %f\n",   getRectWidth( node->data ) );
			printf("\th = %f\n",   getRectHeight( node->data ) );
			printf("\tx = %f\n",   getRectX( node->data ) );
			printf("\ty = %f\n",   getRectY( node->data ) );
			printf("\tcor = %s\n", getRectFill( node->data ) );
		}
		k++;
		node = node->next;
	}
}
