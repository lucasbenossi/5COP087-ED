#include "Tokens.h"
#include "String.h"
#include "LinkedList.h"
#include <string.h>
#include <stdlib.h>

struct _tokens{
	char *string;
	char *delimiters;
	int size;
	char **array;
};

Tokens *createTokens( char *delimiters ){
	Tokens *tokens;
	tokens = malloc(sizeof(Tokens));
	tokens->string = NULL;
	tokens->delimiters = createString(delimiters);
	tokens->size = 0;
	tokens->array = NULL;
	return tokens;
}

void destroyTokens( Tokens *tokens ){
	freeTokens(tokens);
	destroyString(tokens->delimiters);
	free(tokens);
}

void defineTokens( Tokens *tokens, char *string ){
	List *list;
	char *token;
	int i;

	freeTokens(tokens);

	tokens->string = createString(string);
	list = createList();

	token = strtok( tokens->string, tokens->delimiters );
	while( token != NULL ){
		insert( list, token );
		token = strtok( NULL, tokens->delimiters );
	}

	tokens->size = lenght(list);
	if( tokens->size > 0 ){
		tokens->array = malloc( tokens->size * sizeof(char*) );
		for( i = 0; i < tokens->size; i++ ){
			tokens->array[i] = removeFirst(list);
		}
	}

	destroyList(list);
}

void freeTokens( Tokens *tokens ){
	destroyString( tokens->string );
	tokens->string = NULL;
	if( tokens->array != NULL ){
		free( tokens->array );
	    tokens->array = NULL;
	}
}

int getTokensSize( Tokens *tokens ){
	return tokens->size;
}

char *getToken( Tokens *tokens, int i ){
	if( i < tokens->size ){
		return tokens->array[i];
	}
	return NULL;
}
