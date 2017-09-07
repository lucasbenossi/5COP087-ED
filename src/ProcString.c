#include <stdlib.h>
#include <string.h>
#include "ProcString.h"

char *createString( char *pString ){
    char *string;
    int size;

    if( pString != NULL ){
        size = strlen(pString);
        if( size > 0 ){
            string = allocChar( size );
            strcpy(string,pString);
        }
        else{
            string = allocChar(0);
        }
    }
    else{
        string = NULL;
    }
    return string;
}

void destroyString( char *string ){
    if( string != NULL ){
        free(string);
    }
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

char *createStringCat( char *s1, char *s2, char *s3, char *s4, char *s5 ){
    char *string;
    int size;

    string = NULL;
    size = 0;

    if( s1 == NULL && s2 == NULL && s3 == NULL && s4 == NULL && s5 == NULL ){
        string = NULL;
    }
    else{
        if( s1 != NULL ) size += strlen(s1);
        if( s2 != NULL ) size += strlen(s2);
        if( s3 != NULL ) size += strlen(s3);
        if( s4 != NULL ) size += strlen(s4);
        if( s5 != NULL ) size += strlen(s5);
        if( size > 0 ){
            string = allocChar(size);
            if( s1 != NULL ) strcpy(string,s1);
            if( s2 != NULL ) strcat(string,s2);
            if( s3 != NULL ) strcat(string,s3);
            if( s4 != NULL ) strcat(string,s4);
            if( s5 != NULL ) strcat(string,s5);
        }
        else{
            string = allocChar(0);
        }
    }

    return string;
}

void catString( char **s, char *c ){
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

void repString( char **s, char *c ){
	destroyString(*s);
    *s = createString(c);
}

char *fixDir( char *dir ){
	char *newDir;
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
