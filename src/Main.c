#include <stdio.h>
#include "Args.h"
#include "RunCommands.h"

int main( int argc, char **argv ){
	char *pathFileExt;
	char *dir;
	char *num;
	if( argc != 7 ){
		printf("Uso: %s -f arq.geo -o dir -n num\n",argv[0]);
		return 1;
	}

	pathFileExt = procArgs(argc,argv,"-f");
	dir = procArgs(argc,argv,"-o");
	num = procArgs(argc,argv,"-n");

	return runCommands(pathFileExt,dir,atoi(num));
}
