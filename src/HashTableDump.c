#include "HashTableDump.h"
#include "HashTable.h"
#include <stdio.h>

void dumpHashTableDot( HashTable *table, FILE *out ){
	int i, size;
	Iterator *it;

	size = getHashTableSize(table);

	fprintf( out, "digraph \"HashTable\" {\n" );
	fprintf( out, "\tnode [shape=box, fontname=\"monospace\"];\n" );

	fprintf( out, "\t{\n" );
	fprintf( out, "\t\tnode [style=filled, fillcolor=\"#DCDCDC\"];\n" );
	for( i = 0; i < size; i++ ){
		fprintf( out, "\t\tlevel%d [label=\"%d\"];\n", i, i );
	}
	fprintf( out, "\t\t\"level0\"" );
	for( i = 1; i < size; i++ ){
	    fprintf( out, " -> \"level%d\"", i );
	}
	fprintf( out, ";\n" );
	fprintf( out, "\t}\n" );

	it = createIterator(table);
	while( iteratorHasNext(it) ){
		iteratorNext(it);

		fprintf( out, "\t{\n" );
	    fprintf( out, "\t\trank = same;\n" );
		fprintf( out, "\t\tlevel%d", getIteratorI(it) );

		fprintf( out, " -> \"%s\"", iteratorKey(it) );
		while( getIteratorI(it) == getIteratorJ(it) ){
			iteratorNext(it);
			fprintf( out, " -> \"%s\"", iteratorKey(it) );
		}

		fprintf( out, ";\n" );
		fprintf( out, "\t}\n" );
	}
	destroyIterator(it);

	fprintf( out, "}\n" );
}
