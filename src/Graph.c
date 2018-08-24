#include "Graph.h"
#include "HashTable.h"
#include "String.h"
#include "LinkedList.h"
#include <stdlib.h>

struct _graph{
	HashTable *vertices; /* key X Vertex */
	HashTable *edges; /* keu_u X key_v X Edge */
	int q_vertex;
	int q_edge;
};

struct _vertex{
	char *key;
	HashTable *edges; /* key X Vertex */
	void *data;
	double x, y, dist;
	Vertex *prev;
};

struct _edge{
	char *key_u, *key_v;
	void *data;
	double length;
};

static Vertex *getVertexLeastDist( HashTable *unvisited );
static double getEdgeLength( Graph *graph, Vertex *u, Vertex *v );
static double compareDoubles( double dist1, double dist2 );

/* ========================================================================== */

Graph *createGraph(){
	Graph *graph = malloc( sizeof(Graph) );
	graph->vertices = createHashTable(HT_SIZE);
	graph->edges = createHashTable(HT_SIZE);
	graph->q_vertex = 0;
	graph->q_edge = 0;
	return graph;
}

void destroyGraph( Graph *graph ){
	freeGraph(graph);
	destroyHashTable(graph->vertices);
	destroyDoubleHashTable(graph->edges);
	free(graph);
}

void freeGraph( Graph *graph ){
	setHashTableFuncDestroyData(graph->vertices, destroyVertexVoid);
	freeHashTable(graph->vertices);
	setHashTableFuncDestroyData(graph->edges, destroyEdgeVoid);
	freeDoubleHashTable(graph->vertices);
	graph->q_vertex = 0;
	graph->q_edge = 0;
}

Vertex *insertVertex( Graph *graph, char *key, void *data ){
	Vertex *vertex = searchHashTable(graph->vertices, key);

	if(vertex){
	    return NULL;
	}

	vertex = createVertex(key, data);
	insertHashTable(graph->vertices, key, vertex);
	graph->q_vertex++;
	return vertex;
}

Vertex *searchVertex( Graph *graph, char *key ){
	return searchHashTable(graph->vertices, key);
}

Edge *insertEdge( Graph *graph, char *key_u, char *key_v, void *data ){
	Vertex *vertex_u, *vertex_v;
	Edge *edge;

	edge = searchEdge(graph, key_u, key_v);
	if(edge){
		return NULL;
	}

	vertex_u = searchVertex(graph, key_u);
	if(!vertex_u){
		return NULL;
	}

	vertex_v = searchVertex(graph, key_v);
	if(!vertex_v){
		return NULL;
	}

	edge = createEdge(key_u, key_v, data);
	insertDoubleHashTable(graph->edges, key_u, key_v, edge);
	insertHashTable(vertex_u->edges, key_v, vertex_v);

	return edge;
}

Edge *searchEdge( Graph *graph, char *key_u, char *key_v ){
	return searchDoubleHashTable(graph->edges, key_u, key_v);
}

HashTable *getGraphVertices( Graph *graph ){
	return graph->vertices;
}

HashTable *getGraphEdges( Graph *graph ){
	return graph->edges;
}

/* ========================================================================== */

Vertex *createVertex( char *key, void *data ){
	Vertex *vertex = malloc( sizeof(Vertex) );
	vertex->key = createString(key);
	vertex->edges = createHashTable(HT_SIZE_SMALL);
	vertex->data = data;
	vertex->x = 0;
	vertex->y = 0;
	return vertex;
}

void *destroyVertex( Vertex *vertex ){
	void *data = vertex->data;
	destroyString(vertex->key);
	destroyHashTable(vertex->edges);
	free(vertex);
	return data;
}

void destroyVertexVoid( void *vertex ){
	destroyVertex(vertex);
}

void setVertexCoords( Vertex *vertex, double x, double y ){
	vertex->x = x;
	vertex->y = y;
}

char *getVertexKey( Vertex *vertex ){
	return vertex->key;
}

HashTable *getVertexEdges( Vertex *vertex ){
	return vertex->edges;
}

void *getVertexData( Vertex *vertex ){
	return vertex->data;
}

double getVertexX( Vertex *vertex ){
	return vertex->x;
}

double getVertexY( Vertex *vertex ){
	return vertex->y;
}

/* ========================================================================== */

Edge *createEdge( char *key_u, char *key_v, void *data ){
	Edge *edge = malloc( sizeof(Edge) );
	edge->key_u = createString(key_u);
	edge->key_v = createString(key_v);
	edge->data = data;
	return edge;
}

void *destroyEdge( Edge *edge ){
	void *data = edge->data;
	destroyString(edge->key_u);
	destroyString(edge->key_v);
	free(edge);
	return data;
}

void destroyEdgeVoid( void *edge ){
	destroyEdge(edge);
}

void setEdgeLength( Edge *edge, double length ){
	edge->length = length;
}

char *getEdgeKeyU( Edge *edge ){
	return edge->key_u;
}

char *getEdgeKeyV( Edge *edge ){
	return edge->key_v;
}

void *getEdgeData( Edge *edge ){
	return edge->data;
}

/* ========================================================================== */

List *dijkstra( Graph *graph, Vertex *source, Vertex *target ){
	HashTable *unvisited;
	Iterator *it;
	List *list;
	Vertex *vertex;

	unvisited = createHashTable(HT_SIZE);

	it = createIterator(getGraphVertices(graph));
	while(iteratorHasNext(it)){
		vertex = iteratorNext(it);
		vertex->dist = -1;
		vertex->prev = NULL;
		insertHashTable(unvisited, vertex->key, vertex);
	}
	destroyIterator(it);

	source->dist = 0;

	while(!isHashTableEmpty(unvisited)){
		vertex = getVertexLeastDist(unvisited);
		removeHashTable(unvisited, vertex->key, vertex);

		if(vertex == target){
			break;
		}

		it = createIterator(vertex->edges);
		while(iteratorHasNext(it)){
			Vertex *neighbor = iteratorNext(it);

			if(searchHashTable(unvisited, neighbor->key)){
				double alt = vertex->dist + getEdgeLength(graph, vertex, neighbor);

				if(compareDoubles(alt, neighbor->dist) == -1){
					neighbor->dist = alt;
					neighbor->prev = vertex;
				}
			}
		}
		destroyIterator(it);
	}

	destroyHashTable(unvisited);

	list = createList();
	vertex = target;
	while(vertex){
		insertFirst(list, vertex);
		vertex = vertex->prev;
	}

	if(get(getFirst(list)) != source){
		destroyList(list);
		list = NULL;
	}

	return list;
}

static Vertex *getVertexLeastDist( HashTable *unvisited ){
	Iterator *it = createIterator(unvisited);
	Vertex *leastDistVertex = NULL;
	double leastDist;

	if(iteratorHasNext(it)){
		Vertex *vertex = iteratorNext(it);

		leastDistVertex = vertex;
		leastDist = vertex->dist;

		while(iteratorHasNext(it)){
			vertex = iteratorNext(it);

			if( compareDoubles(vertex->dist, leastDist) == -1 ){
				leastDistVertex = vertex;
				leastDist = vertex->dist;
			}
		}
	}
	destroyIterator(it);

	return leastDistVertex;
}

static double getEdgeLength( Graph *graph, Vertex *u, Vertex *v ){
	Edge *edge = searchDoubleHashTable(graph->edges, u->key, v->key);
	return edge->length;
}

static double compareDoubles( double a, double b ){
	if(a < 0 && b >= 0){
		return 1;
	}
	if(a >= 0 && b < 0){
		return -1;
	}
	if(a < 0 && b < 0){
		return 0;
	}

	if(a < b){
		return -1;
	}
	if(a > b){
		return 1;
	}

	return 0;
}
