#ifndef GRAPH_H
#define GRAPH_H
#include "HashTable.h"
#include "LinkedList.h"

typedef struct _graph Graph;
typedef struct _vertex Vertex;
typedef struct _edge Edge;

Graph *createGraph();
void destroyGraph( Graph *graph );
void freeGraph( Graph *graph );

Vertex *insertVertex( Graph *graph, char *key, void *data );
Vertex *searchVertex( Graph *graph, char *key );

Edge *insertEdge( Graph *graph, char *key_u, char *key_v, void *data );
Edge *searchEdge( Graph *graph, char *key_u, char *key_v );

HashTable *getGraphVertices( Graph *graph );
HashTable *getGraphEdges( Graph *graph );

/* ========================================================================== */

Vertex *createVertex( char *key, void *data );
void *destroyVertex( Vertex *vertex );
void destroyVertexVoid( void *vertex );

void setVertexCoords( Vertex *vertex, double x, double y );

char *getVertexKey( Vertex *vertex );
HashTable *getVertexEdges( Vertex *vertex );
void *getVertexData( Vertex *vertex );
double getVertexX( Vertex *vertex );
double getVertexY( Vertex *vertex );

/* ========================================================================== */

Edge *createEdge( char *key_u, char *key_v, void *data );
void *destroyEdge( Edge *edge );
void destroyEdgeVoid( void *edge );

void setEdgeLength( Edge *edge, double length );

char *getEdgeKeyU( Edge *edge );
char *getEdgeKeyV( Edge *edge );
void *getEdgeData( Edge *edge );

/* ========================================================================== */

List *dijkstra( Graph *graph, Vertex *source, Vertex *target );

#endif
