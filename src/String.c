#include "String.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

char *createString( const char *string ){
	char *string0;
	int size;

	if( string == NULL ) return NULL;

	size = strlen(string);
	if( size > 0 ){
	    string0 = allocChar( size );
	    strcpy(string0,string);
	}
	else{
	    string0 = allocChar(0);
	}

	return string0;
}

void destroyString( char *string ){
	if( string ){
	    free(string);
	}
}

void destroyStringVoid( void *string ){
	destroyString(string);
}

char *allocChar( int size ){
	char *string;
	int i;

	size = size + 1;
	string = malloc( size * sizeof(char) );

	for(i = 0; i < size; i++){
	    *(string+i) = '\0';
	}

	return string;
}

char *createStringCat( int n, ... ){
	va_list args;
	char *string;
	const char *arg;
	int size, i;

	if( n == 0 ) return NULL;

	size = 0;

	va_start(args,n);
	for( i = 0; i < n; i++){
	    arg = va_arg(args, const char*);
	    if( arg != NULL ){
	        size += strlen( arg );
	    }
	}
	va_end(args);

	if( size > 0 ){
	    string = allocChar(size);
	    va_start(args,n);
	    for( i = 0; i < n; i++){
	        arg = va_arg(args, const char*);
	        if( arg != NULL ){
	            strcat( string, arg );
	        }
	    }
	    va_end(args);
	}
	else{
	    string = allocChar(0);
	}

	return string;
}

char *createStringInt( int n ){
	char string[100];
	sprintf( string, "%d", n );
	return createString( string );
}

void catString( char **s, const char *c ){
	int sizeC, sizeS;
	char *newS;

	if( c != NULL ){
	    sizeC = strlen(c);
	    if( *s != NULL ){
	        if( sizeC > 0 ){
	    		sizeS = strlen(*s);
	    		newS = allocChar( sizeS + sizeC );
	    		strcpy(newS, *s);
	    		strcat(newS, c);
	    		destroyString(*s);
	    		*s = newS;
	    	}
	    }
	    else{
	        if( sizeC > 0 ){
	            *s = createString(c);
	        }
	        else{
	            *s = allocChar(0);
	        }
	    }
	}
}

void repString( char **s, const char *c ){
	destroyString(*s);
	*s = createString(c);
}

char *fixDir( char *dir ){
	char *newDir;

	if( dir == NULL ) return NULL;

	newDir = allocChar(0);
	if( *dir == '.' ){
		if( *(dir+1) == '\0' ){
			catString(&newDir,dir);
		}
		else if( *(dir+1) == '/' ){
			catString(&newDir,dir);
		}
		else{
			catString(&newDir,"./");
			catString(&newDir,dir);
		}
	}
	else if( *dir == '/' ){
		catString(&newDir,dir);
	}
	else{
		catString(&newDir,"./");
		catString(&newDir,dir);
	}
	if( *(newDir+strlen(newDir)-1) != '/' ){
		catString(&newDir,"/");
	}
	return newDir;
}

char *fileRemovePathExt( char *pathFileExt ){
	char *lastDot, *lastSlash;
	char string[1000], *aux1, *aux2;

	if( pathFileExt == NULL ) return NULL;

	lastDot = NULL;
	lastSlash = NULL;

	aux1 = pathFileExt;
	while( *aux1 != '\0' ){
	    if( *aux1 == '/' ){
	        lastSlash = aux1;
	    }
	    else if( *aux1 == '.' ){
	        lastDot = aux1;
	    }
	    aux1++;
	}

	if( lastSlash != NULL ){
	    aux1 = lastSlash + 1;
	}
	else{
	    aux1 = pathFileExt;
	}
	aux2 = string;
	while( *aux1 != '\0' && aux1 != lastDot ){
	    *aux2 = *aux1;
	    aux1++;
	    aux2++;
	}
	*aux2 = '\0';

	return createString(string);
}
