#include "DumpQuadTree.h"
#include "LinkedList.h"
#include "ObjList.h"
#include "QuadTree.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>

static void dumpTreeDotGenList( QuadTreeNode *node, List *levelList, int level, FILE *out, int *n );

static void dumpTreeDotNodes( List *levelList, FILE *out );

static void dumpTreeDotEdges( QuadTreeNode *node, FILE *out );

/* =============================================================== */

void dumpTree( QuadTreeNode *node, int level, int quadrant, FILE *out ){
    int i;
    Object *obj;

    for( i=0; i<level; i++ ){
        fprintf(out,"\t");
    }

    if( quadrant == 0 ){
        fprintf(out,"Root: ");
    }
    else if( quadrant == 1 ){
        fprintf(out,"NW: ");
    }
    else if( quadrant == 2 ){
        fprintf(out,"NE: ");
    }
    else if( quadrant == 3 ){
        fprintf(out,"SW: ");
    }
    else if( quadrant == 4 ){
        fprintf(out,"SE: ");
    }

    if( node != NULL ){
        fprintf( out, "%f, %f, ", getQuadTreeNodeX(node), getQuadTreeNodeY(node) );

        obj = getQuadTreeNodeData(node);
        if( obj == NULL ){
            fprintf( out, "disabled\n" );
        }
        else{
            fprintf( out, "%s\n", getObjId(obj) );
        }


        dumpTree( getQuadTreeNodeNW(node), level+1, 1, out );
        dumpTree( getQuadTreeNodeNE(node), level+1, 2, out );
        dumpTree( getQuadTreeNodeSW(node), level+1, 3, out );
        dumpTree( getQuadTreeNodeSE(node), level+1, 4, out );
    }
    else{
        fprintf(out,"NULL\n");
    }
}

void dumpTreeDot( QuadTree *qt, FILE *out ){
    List *levelList;
    int *n;

    n = malloc(sizeof(int));
    *n = 0;

    fprintf( out, "digraph QuadTree {\n" );
    fprintf( out, "\tnode [shape=circle, style=filled, fillcolor=\"#80FF80\", fontname=\"monospace\"];\n" );

    levelList = createList();

    dumpTreeDotGenList( getQuadTreeRoot(qt), levelList, 0, out, n );
    dumpTreeDotNodes( levelList, out );
    dumpTreeDotEdges( getQuadTreeRoot(qt), out );

    destroyList(levelList);
    free(n);

    fprintf( out, "}\n" );
}

/* =============================================================== */

static void dumpTreeDotGenList( QuadTreeNode *node, List *levelList, int level, FILE *out, int *n ){
    Node *levelNode;
    int i;
    Object *obj;
    char string[1000];

    if( node != NULL ){
        if( getFirst(levelList) == NULL ){
            insert( levelList, createList() );
        }
        levelNode = getFirst(levelList);

        for( i = 0; i < level; i++ ){
            if( getNext(levelNode) == NULL ){
                insert( levelList, createList() );
            }
            levelNode = getNext(levelNode);
        }

        obj = getQuadTreeNodeData(node);
        if( obj == NULL ){
            sprintf( string, "disabled%d", *n);
            (*n)++;
            obj = createObject( string, 'd', NULL );
            reenableQuadTreeNode(node, obj);
        }

        insert( get(levelNode), obj );

        dumpTreeDotGenList( getQuadTreeNodeNW(node), levelList, level+1, out, n );
        dumpTreeDotGenList( getQuadTreeNodeNE(node), levelList, level+1, out, n );
        dumpTreeDotGenList( getQuadTreeNodeSW(node), levelList, level+1, out, n );
        dumpTreeDotGenList( getQuadTreeNodeSE(node), levelList, level+1, out, n );
    }
}

static void dumpTreeDotNodes( List *levelList, FILE *out ){
    List *objList;
    Object *obj;
    int i, maxLevel;

    i = 0;
    while( lenght(levelList) > 0 ){
        fprintf( out, "\t{\n" );
        fprintf( out, "\t\trank = same;\n" );
        fprintf( out, "\t\tlevel%d [label=\"%d\", shape=plaintext, style=solid, fontsize=40];\n", i, i );

        objList = removeFirst(levelList);
        while( lenght(objList) > 0 ){
            obj = removeFirst(objList);
            if( getObjType(obj) == 'd' ){
                fprintf( out, "\t\t\"%s\" [label=\" \", fillcolor=\"#FF8080\"];\n", getObjId(obj) );
            }
            else{
                fprintf( out, "\t\t\"%s\";\n", getObjId(obj) );
            }
        }
        destroyList(objList);

        fprintf( out, "\t}\n" );
        i++;
    }

    maxLevel = i;

    fprintf( out, "\t" );
    for( i = 0; i < (maxLevel - 1); i++ ){
        fprintf( out, "\"level%d\" -> ", i );
    }
    fprintf( out, "\"level%d\";\n", i );
}

static void dumpTreeDotEdges( QuadTreeNode *node, FILE *out ){
    QuadTreeNode *nw, *ne, *sw, *se;
    Object *obj;

    if( node != NULL ){
        nw = getQuadTreeNodeNW(node);
        ne = getQuadTreeNodeNE(node);
        sw = getQuadTreeNodeSW(node);
        se = getQuadTreeNodeSE(node);

        if( nw != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"nw\"]\n", getObjId(getQuadTreeNodeData(node)), getObjId(getQuadTreeNodeData(nw)) );
        if( ne != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"ne\"]\n", getObjId(getQuadTreeNodeData(node)), getObjId(getQuadTreeNodeData(ne)) );
        if( sw != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"sw\"]\n", getObjId(getQuadTreeNodeData(node)), getObjId(getQuadTreeNodeData(sw)) );
        if( se != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"se\"]\n", getObjId(getQuadTreeNodeData(node)), getObjId(getQuadTreeNodeData(se)) );

        dumpTreeDotEdges(nw, out);
        dumpTreeDotEdges(ne, out);
        dumpTreeDotEdges(sw, out);
        dumpTreeDotEdges(se, out);

        obj = getQuadTreeNodeData(node);
        if( getObjType(obj) == 'd' ){
            destroyObject( disableQuadTreeNode(node) );
        }
    }
}
