#include "GraphDump.h"
#include "Graph.h"
#include "HashTable.h"
#include "WriteTags.h"
#include <stdio.h>

void dumpGraphDot( Graph *graph, FILE *out ){
	Iterator *it_u, *it_v;

	fprintf( out, "digraph \"Graph\" {\n" );
	fprintf( out, "\tnode [shape=circle, style=filled, fillcolor=\"white\", fontname=\"monospace\"];\n" );
	fprintf( out, "\tscale=5;\n" );

	it_u = createIterator(getGraphVertices(graph));
	while(iteratorHasNext(it_u)){
		Vertex *vertex = iteratorNext(it_u);
		fprintf( out, "\t\"%s\" [pos=\"%f,-%f!\"];\n", getVertexKey(vertex), getVertexX(vertex), getVertexY(vertex) );
		it_v = createIterator(getVertexEdges(vertex));
		while(iteratorHasNext(it_v)){
			fprintf( out, "\t\"%s\" -> \"%s\";\n", getVertexKey(vertex), getVertexKey(iteratorNext(it_v)) );
		}
		destroyIterator(it_v);
	}
	destroyIterator(it_u);

	fprintf( out, "}\n" );
}
