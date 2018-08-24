#ifndef PESSOA_H
#define PESSOA_H
#include "Endereco.h"

typedef struct _pessoa Pessoa;

Pessoa *createPessoa( char *cpf, char *nome, char *sobrenome, char sexo, char *nasc );

void destroyPessoa( Pessoa *pessoa );
void destroyPessoaVoid( void *pessoa );

void setPessoaEndereco( Pessoa *pessoa, Endereco *endereco );
Endereco *resetPessoaEndereco( Pessoa *pessoa );

char *getPessoaCpf( Pessoa *pessoa );
char *getPessoaNome( Pessoa *pessoa );
char *getPessoaSobrenome( Pessoa *pessoa );
char getPessoaSexo( Pessoa *pessoa );
char *getPessoaNasc( Pessoa *pessoa );
Endereco *getPessoaEndereco( Pessoa *pessoa );

const char *getPessoaSexoString( Pessoa *pessoa );

#endif
