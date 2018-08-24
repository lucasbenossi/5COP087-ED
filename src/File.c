#include "File.h"
#include <stdio.h>
#include <string.h>

FILE *openFileRead( char *fullPath ){
	FILE *file;
	if( strcmp( fullPath, "stdin" ) == 0 ){
	    fprintf( stderr, "Usando stdin como arquivo de entrada.\n" );
	    return stdin;
	}
	file = fopen(fullPath,"r");
	if( file == NULL ){
		fprintf( stderr, "ERRO: Falha ao abrir o arquivo %s\n", fullPath );
		return NULL;
	}
	return file;
}

FILE *openFileWrite( char *fullPath ){
	FILE *file;
	file = fopen(fullPath,"w");
	if( file == NULL ){
		fprintf( stderr, "ERRO: Falha ao criar o arquivo %s\n", fullPath );
		return NULL;
	}
	return file;
}

FILE *openFileAppend( char *fullPath ){
	FILE *file;
	file = fopen(fullPath,"a");
	if( file == NULL ){
		fprintf( stderr, "ERRO: Falha ao abrir/criar o arquivo %s\n", fullPath );
		return NULL;
	}
	return file;
}

void closeFile( FILE *file ){
	if( file != NULL && file != stdin && file != stderr && file != stdout ){
	    fclose(file);
	}
}
