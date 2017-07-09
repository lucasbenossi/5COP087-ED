#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Circle.h"
#include "Rect.h"
#include "FreeObjList.h"

void freeObjList( List *l ){
    if( l->head != NULL ){
		Node *node1, *node2;
		node1 = l->head;
		node2 = node1->next;
		while( node1 != NULL ){
            /*printf("free %d\n",node1->id);*/
			if( node1->type == 1 ){
                free( getCircleFill(node1->data) );
				destroyCircle(node1->data);
			}
			else if( node1->type == 2 || node1->type == 3 ){
                free( getRectFill(node1->data) );
				destroyRect(node1->data);
			}
            destroyNode(node1);
			node1 = node2;
			if( node2 != NULL ){
				node2 = node2->next;
			}
		}
		l->head = NULL;
        l->tail = NULL;
	}
}
