#include "CommandsPm.h"
#include "String.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Object.h"
#include "Pessoa.h"
#include "Quadra.h"
#include "Endereco.h"
#include <stdio.h>

void commandInsertPessoa( Cidade *cidade, char *line ){
	char cpf[STRING_SIZE], nome[STRING_SIZE], sobrenome[STRING_SIZE], sexo, nasc[STRING_SIZE];
	Pessoa *pessoa;

	sscanf( line, "p %s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc );

	if( searchCidadePessoaCpf( cidade, cpf ) != NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tPessoa de cpf %s ja inserida na cidade.\n\n", cpf );
		return;
	}

	if( sexo != 'M' && sexo != 'F' ){
		fputs( line, stderr );
		fprintf( stderr, "\tSexo invalido.\n\n" );
		return;
	}

	pessoa = createPessoa( cpf, nome, sobrenome, sexo, nasc );
	insertHashTable( getCidadePessoas(cidade), cpf, pessoa );
}

void commandMorador( Cidade *cidade, char *line ){
	char cpf[STRING_SIZE], cep[STRING_SIZE], face, compl[STRING_SIZE];
	int num;
	Pessoa *pessoa;
	Endereco *endereco;

	sscanf( line, "m %s %s %c %d %s", cpf, cep, &face, &num, compl );

	pessoa = searchCidadePessoaCpf( cidade, cpf );
	if( pessoa == NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tPessoa de cpf %s nao encontrada.\n\n", cpf );
		return;
	}

	if( searchCidadeQuadraCep( cidade, cep ) == NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tQuadra de cep %s nao encontrada.\n\n", cep );
		return;
	}

	if( checkFace(face) ){
		fputs( line, stderr );
		fprintf( stderr, "\tFace invalida.\n\n" );
		return;
	}

	if( getPessoaEndereco(pessoa) ){
		destroyEndereco(cidadeRemoveMorador(cidade, pessoa));
	}

	endereco = createEndereco( cep, face, num, compl );
	cidadeInsertMorador( cidade, pessoa, endereco );
}
