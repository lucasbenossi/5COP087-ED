#include "Pessoa.h"
#include "String.h"
#include "Endereco.h"
#include "Quadra.h"
#include <stdlib.h>

struct _pessoa{
	char *cpf;
	char *nome;
	char *sobrenome;
	char sexo;
	char *nasc;
	Endereco *endereco;
};

Pessoa *createPessoa( char *cpf, char *nome, char *sobrenome, char sexo, char *nasc ){
	Pessoa *pessoa;
	pessoa = malloc(sizeof(Pessoa));
	pessoa->cpf = createString(cpf);
	pessoa->nome = createString(nome);
	pessoa->sobrenome = createString(sobrenome);
	pessoa->sexo = sexo;
	pessoa->nasc = createString(nasc);
	pessoa->endereco = NULL;
	return pessoa;
}

void destroyPessoa( Pessoa *pessoa ){
	destroyString(pessoa->cpf);
	destroyString(pessoa->nome);
	destroyString(pessoa->sobrenome);
	destroyString(pessoa->nasc);
	if(pessoa->endereco){
	    destroyEndereco(pessoa->endereco);
	}
	free(pessoa);
}

void destroyPessoaVoid( void *pessoa ){
	destroyPessoa(pessoa);
}

void setPessoaEndereco( Pessoa *pessoa, Endereco *endereco ){
	pessoa->endereco = endereco;
}

Endereco *resetPessoaEndereco( Pessoa *pessoa ){
	Endereco *endereco = pessoa->endereco;
	pessoa->endereco = NULL;
	return endereco;
}

char *getPessoaCpf( Pessoa *pessoa ){
	return pessoa->cpf;
}

char *getPessoaNome( Pessoa *pessoa ){
	return pessoa->nome;
}

char *getPessoaSobrenome( Pessoa *pessoa ){
	return pessoa->sobrenome;
}

char getPessoaSexo( Pessoa *pessoa ){
	return pessoa->sexo;
}

char *getPessoaNasc( Pessoa *pessoa ){
	return pessoa->nasc;
}

Endereco *getPessoaEndereco( Pessoa *pessoa ){
	return pessoa->endereco;
}

const char *getPessoaSexoString( Pessoa *pessoa ){
	if( pessoa->sexo == 'M' ) return "Masculino";
	if( pessoa->sexo == 'F' ) return "Feminino";
	return "";
}
