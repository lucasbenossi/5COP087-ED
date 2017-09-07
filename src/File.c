#include "File.h"
#include <stdio.h>

FILE *openFileRead( char *fullPath ){
    FILE *file;
    file = fopen(fullPath,"r");
    if( file == NULL ){
		printf("ERRO: Falha ao abrir o arquivo %s\n",fullPath);
		return NULL;
	}
    return file;
}

FILE *openFileWrite( char *fullPath ){
    FILE *file;
    file = fopen(fullPath,"w");
    if( file == NULL ){
		printf("ERRO: Falha ao criar o arquivo %s\n",fullPath);
		return NULL;
	}
    return file;
}

FILE *openFileAppend( char *fullPath ){
    FILE *file;
    file = fopen(fullPath,"a");
    if( file == NULL ){
		printf("ERRO: Falha ao abrir/criar o arquivo %s\n",fullPath);
		return NULL;
	}
    return file;
}

void closeFile( FILE *file ){
    if( file != NULL ){
        fclose(file);
    }
}
