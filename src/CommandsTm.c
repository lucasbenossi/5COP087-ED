#include "CommandsTm.h"
#include "Cidade.h"
#include "Operadora.h"
#include "String.h"
#include "Pessoa.h"
#include "Celular.h"
#include <stdio.h>

void commandInsertClienteOperadora( char *line, int commandId, Cidade *cidade ){
	Operadora *operadora;
	Pessoa *pessoa;
	Celular *celular;
	char cpf[STRING_SIZE], numero[STRING_SIZE];

	sscanf( line, "%*s %s %s", cpf, numero );

	if( commandId == 1 ){
	    operadora = getCidadeSercomtuel(cidade);
	}
	else if( commandId == 2 ){
	    operadora = getCidadeUelmobile(cidade);
	}
	else{
	    return;
	}

	pessoa = searchCidadePessoaCpf( cidade, cpf );
	if( pessoa == NULL ){
	    fputs( line, stderr );
	    fprintf( stderr, "Pessoa de Cpf %s não encontrada.\n\n", cpf );
	    return;
	}

	if( searchOperadoraCelularCpf( operadora, getPessoaCpf(pessoa) ) ){
		fputs( line, stderr );
	    fprintf( stderr, "Pessoa de Cpf %s ja possui celular na operadora %s.\n\n", cpf, getOperadoraNome(operadora) );
	    return;
	}

	if( searchOperadoraCelularNum( operadora, numero ) ){
		fputs( line, stderr );
	    fprintf( stderr, "Celular %s ja existe em %s.\n\n", numero, getOperadoraNome(operadora) );
	    return;
	}

	celular = createCelular( numero, getPessoaCpf(pessoa) );
	operadoraInsertCliente(operadora, pessoa, celular);
}
