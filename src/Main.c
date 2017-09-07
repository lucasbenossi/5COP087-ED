#include <stdio.h>
#include "Args.h"
#include "RunCommands.h"

int main( int argc, char **argv ){
	Args *args;
	int ret;

	args = createArgs();
	if( procArgs(argc,argv,args) == 1 ){
		printf("ERRO: Linha de comando inválida\n");
		destroyArgs(args);
		return 1;
	}

	ret = runCommands(args);

	destroyArgs(args);

	return ret;
}
