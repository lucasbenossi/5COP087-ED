#include "CommandsEc.h"
#include "Cidade.h"
#include "EstabComercial.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "String.h"
#include "Object.h"
#include "Quadra.h"
#include "Endereco.h"
#include <stdio.h>

void commandDescricao( Cidade *cidade, char *line ){
	char codt[STRING_SIZE], descricao[STRING_SIZE_LARGE];

	sscanf( line, "t %s %[^\r\n]", codt, descricao );

	if( searchCidadeDescricaoCodt( cidade, codt ) != NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tDescrição de %s ja inserida.\n\n", codt );
		return;
	}

	insertHashTable( getCidadeDescricoes(cidade), codt, createString(descricao) );
}

void commandInsertEstabComercial( Cidade *cidade, char *line ){
	char codt[STRING_SIZE], cep[STRING_SIZE], face, cnpj[STRING_SIZE], nome[STRING_SIZE_LARGE];
	int num;
	Object *obj;

	sscanf( line, "e %s %s %c %d %s %[^\r\n]", codt, cep, &face, &num, cnpj, nome );

	if( searchCidadeEstabComercialCnpj( cidade, cnpj ) != NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tEstabelecimento Comercial de CNPJ %s ja inserido.\n\n", cnpj );
		return;
	}

	if( searchCidadeDescricaoCodt( cidade, codt ) == NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tTipo de estabelecimento %s não definido.\n\n", codt );
		return;
	}

	obj = searchCidadeQuadraCep( cidade, cep );
	if( obj == NULL ){
		fputs( line, stderr );
		fprintf( stderr, "\tQuadra de Cep %s não existe.\n\n", cep );
		return;
	}

	if( checkFace(face) ){
		fputs( line, stderr );
		fprintf( stderr, "\tFace invalida.\n\n" );
		return;
	}

	cidadeInsertEstabComercial( cidade, createEstabComercial( cnpj, nome, codt, cep, face, num ) );
}

void commandRemoveEstabComercial( Cidade *cidade, char *line ){
	EstabComercial *estab;
	char cnpj[STRING_SIZE];

	sscanf( line, "d %s", cnpj );

	estab = searchCidadeEstabComercialCnpj( cidade, cnpj );
	if( estab != NULL ){
		cidadeRemoveEstabComercial( cidade, estab );
		destroyEstabComercial(estab);
	}
}
