#include "Args.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Args *createArgs(){
	Args *args;
	args = malloc( sizeof(Args) );
	return args;
}

void destroyArgs( Args *args ){
	free(args);
}

int procArgs( int argc, char **argv, Args *args ){
	args->acc0 = searchArgsBoolean(argc,argv,"-acc0");
	args->acc = searchArgsBoolean(argc,argv,"-acc");
	args->e = searchArgsString(argc,argv,"-e");
	args->f = searchArgsString(argc,argv,"-f");
	args->o = searchArgsString(argc,argv,"-o");
	args->q = searchArgsString(argc,argv,"-q");
	args->id = searchArgsBoolean(argc,argv,"-id");
	args->ec = searchArgsString(argc,argv,"-ec");
	args->pm = searchArgsString(argc,argv,"-pm");
	args->tm = searchArgsString(argc,argv,"-tm");
	args->v = searchArgsString(argc,argv,"-v");
	args->m = searchArgsString(argc,argv,"-m");
	args->t = searchArgsBoolean(argc,argv,"-t");
	args->noT2 = searchArgsBoolean(argc,argv,"-noT2");
	args->r = searchArgsString(argc,argv,"-r");
	args->g = searchArgsString(argc,argv,"-g");
	args->h = searchArgsString(argc,argv,"-h");
	args->od = searchArgsString(argc,argv,"-od");
	args->n = searchArgsString(argc,argv,"-n");
	if( args->f == NULL || args->o == NULL ){
		return 1;
	}
	return 0;
}

char *searchArgsString( int argc, char **argv, char *arg ){
	int i;
	for( i = 0; i < argc; i++ ){
		if( strcmp( arg, argv[i] ) == 0 ){
			if( *argv[i+1] == '-' ){
				return NULL;
			}
			return argv[i+1];
		}
	}
	return NULL;
}

int searchArgsBoolean( int argc, char **argv, char *arg ){
	int i;
	for( i= 0; i < argc; i++ ){
		if( strcmp( arg, argv[i] ) == 0 ){
			return 1;
		}
	}
	return 0;
}
