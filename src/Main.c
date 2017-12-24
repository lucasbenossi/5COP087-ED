#include <stdio.h>
#include "Args.h"
#include "RunCommands.h"

static void printId( FILE *out );

int main( int argc, char **argv ){
	Args *args;
	int ret, error;

	error = 0;

	args = createArgs();
	ret = procArgs(argc,argv,args);

	if( ret == 1 && args->id == 0 ){
		printf("ERRO: Linha de comando inválida\n");
		error++;
	}
	else if( ret == 1 && args->id == 1 ){
		printId(stdout);
		error++;
	}

	if( error == 0 ){
		if( args->id == 1 ){
			printId(stdout);
		}
		ret = prepareEnvironment(args);
	}

	destroyArgs(args);
	return ret;
}

static void printId( FILE *out ){
	fprintf(out, "Lucas Magalhães Benossi\n201600560228\n");
}
