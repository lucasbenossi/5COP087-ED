#include "Parser.h"
#include <string.h>

struct _commandtable {
	char *command;
	int id;
};
typedef struct _commandtable CommandTable;

static int parser( char *command, const int size, const CommandTable table[] );

/* ========================================================================== */

static int parser( char *command, const int size, const CommandTable table[] ){
	int i;
	if( command == NULL ){
	    return 0;
	}
	for( i = 0; i < size; i++ ){
	    if( strcmp( command, table[i].command ) == 0 ){
	        return table[i].id;
	    }
	}
	return 0;
}

int parserGeo( char *command ){
	static const CommandTable table[] = {
	    { "c", 1 },
	    { "r", 2 },
	    { "o", 3 },
	    { "i", 4 },
	    { "d", 5 },
	    { "a", 6 },
	    { "q", 7 },
	    { "h", 8 },
	    { "s", 9 },
	    { "t", 10 },
	    { "cq", 11 },
	    { "ch", 12 },
	    { "ct", 13 },
	    { "cs", 14 },
	    { "hI", 15 },
	    { "sI", 16 },
	    { "tI", 17 },
	    { "su", 18 },
	    { "um", 19 }
	};
	static const int size =  sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}

int parserQry( char *command ){
	static const CommandTable table[] = {
	    { "dq", 1 },
	    { "dh", 2 },
	    { "ds", 3 },
	    { "dt", 4 },
	    { "Dq", 5 },
	    { "Dh", 6 },
	    { "Ds", 7 },
	    { "Dt", 8 },
	    { "crd?", 9 },
	    { "pc?", 10 },
	    { "ac?", 11 },
	    { "mv", 12 },
	    { "m?", 13 },
	    { "mr?", 14 },
	    { "dm?", 15 },
	    { "de?", 16 },
	    { "con", 17 },
	    { "mse?", 18 },
	    { "rip", 19 },
	    { "lk?", 20 },
	    { "rb?", 21 },
	    { "co?", 22 },
	    { "lnr?", 23 },
	    { "ecq?", 24 },
	    { "ecr?", 25 },
	    { "tecq?", 26 },
	    { "tecr?", 27 },
	    { "dc?", 28 },
	    { "lec?", 29 },
	    { "lcc?", 30 },
	    { "dpr", 31 },
	    { "@f?", 32 },
	    { "@m?", 33 },
	    { "@e?", 34 },
	    { "@g?", 35 },
	    { "@xy?", 36 },
		{ "@xy", 36 },
	    { "@tp?", 37 },
	    { "p?", 38 }
	};
	static const int size =  sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}

int parserEc( char *command ){
	static const CommandTable table[] = {
	    { "t", 1 },
	    { "e", 2 },
	    { "d", 3 }
	};
	static const int size = sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}

int parserPm( char *command ){
	static const CommandTable table[] = {
	    { "p", 1 },
	    { "m", 2 }
	};
	static const int size = sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}

int parserTm( char *command ){
	static const CommandTable table[] = {
	    { "su", 1 },
	    { "um", 2 }
	};
	static const int size = sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}

int parserVia( char *command ){
	static const CommandTable table[] = {
	    { "v", 1 },
	    { "e", 2 }
	};
	static const int size = sizeof(table)/sizeof(table[0]);
	return parser( command, size, table );
}
