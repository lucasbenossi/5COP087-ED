#include <stdio.h>
#include <stdlib.h>
#include "CreateSvg.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "Rect.h"
#include "Circle.h"
#include "WriteTags.h"

void createSvg( List *l, char *file, char *fixedDir ){
    char *fullPath;
    FILE *svg;
    Node *node;

    fullPath = genFullPath(fixedDir, file, "svg");

    svg = fopen(fullPath,"w");

    if( svg == NULL ){
        printf("Erro ao criar o arquivo %s\n",fullPath);
		free(fullPath);
		return;
    }

    node = l->head;

    fprintf( svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    while( node != NULL ){
        if( node->type == 1 ){
            writeCircleTag( node->data, svg );
        }
        else if( node->type == 2 ){
            writeRectTag( node->data, svg );
        }
        else if( node->type == 3 ){
            writeOverlapTag( node->data, svg );
        }
        /*printf("svg %d\n",node->id);*/
		node = node->next;
    }
    fprintf(svg, "</svg>");

	fclose(svg);

	free(fullPath);
}
