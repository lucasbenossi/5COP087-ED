#ifndef TOKENS_H
#define TOKENS_H

#define DELIMITERS " \t\r\n"

typedef struct _tokens Tokens;

Tokens *createTokens( char *delimiters );

void destroyTokens( Tokens *tokens );

void defineTokens( Tokens *tokens, char *string );

void freeTokens( Tokens *tokens );

int getTokensSize( Tokens *tokens );

char *getToken( Tokens *tokens, int i );

#endif
