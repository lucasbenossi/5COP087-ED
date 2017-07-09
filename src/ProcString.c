#include <stdlib.h>
#include <string.h>
#include "ProcString.h"

char *allocColor( char *color ){
    int size;
    char *newColor;
    size = strlen(color);
    newColor = allocChar(size);
    strcpy(newColor,color);
    return newColor;
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
	if( *(dir+strlen(dir)-1) != '/' ){
		catString(&newDir,"/");
	}
	return newDir;
}

char *fileRemovePathExt( char *pathFileExt ){
    char *file, *lastDot, *lastSlash, *c, *d, *e;
    int size;

    lastDot = NULL;
    lastSlash = NULL;

    c = pathFileExt;
    while( *c != '\0' ){
        if( *c == '/' ){
            lastSlash = c;
        }
        if( *c == '.' ){
            lastDot = c;
        }
        c++;
    }

    if( lastSlash == NULL && lastDot == NULL ){
        file = allocChar( strlen(pathFileExt) );
        strcpy(file, pathFileExt);
    }
    else if( lastSlash != NULL && lastDot == NULL ){
        file = allocChar( strlen( lastSlash+1 ) );
        strcpy(file, lastSlash+1);
    }
    else if( lastSlash == NULL && lastDot != NULL ){
        c = malloc( strlen(pathFileExt) );
        d = pathFileExt;
        e = c;
        while( d != lastDot ){
            *e = *d;
            d++;
            e++;
        }
        *e = '\0';
        file = allocChar( strlen(c) );
        strcpy(file, c);
        free(c);
    }
    else{
        c = malloc( strlen(lastSlash+1) );
        d = lastSlash+1;
        e = c;
        while( d != lastDot ){
            *e = *d;
            d++;
            e++;
        }
        *e = '\0';
        file = allocChar( strlen(c) );
        strcpy(file, c);
        free(c);
    }

    return file;
}

char *allocChar( int size ){
	char *ptr;
    int i;
	ptr = malloc( (size+1) * sizeof(char) );
	for(i=0; i<(size+1); i++){
        *(ptr+i) = '\0';
    }
	return ptr;
}

void catString( char **s, char *c ){
	int sizeC;
	sizeC = strlen(c);
	if( sizeC > 0 ){
		int sizeS;
		char *newS;
		sizeS = strlen(*s);
		newS = allocChar( sizeS + sizeC );
		strcpy(newS, *s);
		strcat(newS, c);
		free(*s);
		*s = newS;
	}
}

void repString( char **s, char *c ){
	int sizeC;
	sizeC = strlen(c);
	if( sizeC > 0 ){
		free(*s);
		*s = allocChar(sizeC);
		strcpy(*s,c);
	}
	else{
		cleanString(s);
	}
}

void cleanString( char **s ){
	free(*s);
	*s = allocChar(0);
}

char *genFullPath( char *fixedDir, char *fixedFile, char *ext ){
	char *fullPath;
	fullPath = allocChar(0);
	catString(&fullPath,fixedDir);
	catString(&fullPath,fixedFile);
	catString(&fullPath,".");
	catString(&fullPath,ext);
	return fullPath;
}
