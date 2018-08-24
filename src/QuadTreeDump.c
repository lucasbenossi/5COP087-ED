#include "QuadTreeDump.h"
#include "LinkedList.h"
#include "ObjData.h"
#include "QuadTree.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>

static void dumpQuadTreeDotGenList( QuadTreeNode *node, List *levelList, int level, FILE *out, int *n );

static void dumpQuadTreeDotNodes( List *levelList, FILE *out );

static void dumpQuadTreeDotEdges( QuadTreeNode *node, FILE *out );

/* =============================================================== */

void dumpQuadTreeDot( QuadTree *qt, FILE *out ){
	List *levelList;
	int n = 0;

	fprintf( out, "digraph \"QuadTree\" {\n" );
	fprintf( out, "\tnode [shape=circle, style=filled, fillcolor=\"#80FF80\", fontname=\"monospace\"];\n" );

	levelList = createList();

	dumpQuadTreeDotGenList( getQuadTreeRoot(qt), levelList, 0, out, &n );
	dumpQuadTreeDotNodes( levelList, out );
	dumpQuadTreeDotEdges( getQuadTreeRoot(qt), out );

	destroyList(levelList);

	fprintf( out, "}\n" );
}

/* =============================================================== */

static void dumpQuadTreeDotGenList( QuadTreeNode *node, List *levelList, int level, FILE *out, int *n ){
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

	    dumpQuadTreeDotGenList( getQuadTreeNodeNW(node), levelList, level+1, out, n );
	    dumpQuadTreeDotGenList( getQuadTreeNodeNE(node), levelList, level+1, out, n );
	    dumpQuadTreeDotGenList( getQuadTreeNodeSW(node), levelList, level+1, out, n );
	    dumpQuadTreeDotGenList( getQuadTreeNodeSE(node), levelList, level+1, out, n );
	}
}

static void dumpQuadTreeDotNodes( List *levelList, FILE *out ){
	List *objList;
	Object *obj;
	int i, maxLevel;

	maxLevel = lenght(levelList);

	i = 0;
	while( ! isListEmpty(levelList) ){
	    fprintf( out, "\t{\n" );
	    fprintf( out, "\t\trank = same;\n" );
	    fprintf( out, "\t\tlevel%d [label=\"%d\", shape=plaintext, style=solid, fontsize=40];\n", i, i );

	    objList = removeFirst(levelList);
	    while( ! isListEmpty(objList) ){
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

	if( maxLevel > 0 ){
	    fprintf( out, "\t" );
	    fprintf( out, "\"level0\"" );
	    for( i = 1; i < maxLevel; i++ ){
	        fprintf( out, " -> \"level%d\"", i );
	    }
	    fprintf( out, ";\n" );
	}
}

static void dumpQuadTreeDotEdges( QuadTreeNode *node, FILE *out ){
	QuadTreeNode *nw, *ne, *sw, *se;
	Object *obj;

	if( node != NULL ){
	    nw = getQuadTreeNodeNW(node);
	    ne = getQuadTreeNodeNE(node);
	    sw = getQuadTreeNodeSW(node);
	    se = getQuadTreeNodeSE(node);
		obj = getQuadTreeNodeData(node);

	    if( nw != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"nw\"]\n", getObjId(obj), getObjId(getQuadTreeNodeData(nw)) );
	    if( ne != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"ne\"]\n", getObjId(obj), getObjId(getQuadTreeNodeData(ne)) );
	    if( sw != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"sw\"]\n", getObjId(obj), getObjId(getQuadTreeNodeData(sw)) );
	    if( se != NULL ) fprintf( out, "\t\"%s\" -> \"%s\" [label=\"se\"]\n", getObjId(obj), getObjId(getQuadTreeNodeData(se)) );

	    dumpQuadTreeDotEdges(nw, out);
	    dumpQuadTreeDotEdges(ne, out);
	    dumpQuadTreeDotEdges(sw, out);
	    dumpQuadTreeDotEdges(se, out);

	    if( getObjType(obj) == 'd' ){
	        destroyObject( disableQuadTreeNode(node) );
	    }
	}
}
