#include "Args.h"
#include <string.h>
#include <stdlib.h>

struct _args{
    int acc0;
    int acc;
    char *e;
    char *f;
    char *o;
    char *q;
};
typedef struct _args ArgsStr;

Args *createArgs(){
	ArgsStr *args;
	args = malloc( sizeof(ArgsStr) );
	args->acc0 = 0;
	args->acc = 0;
	args->e = NULL;
	args->f = NULL;
	args->o = NULL;
	args->q = NULL;
	return args;
}

void destroyArgs( Args *args ){
	free(args);
}

int getArgsAcc0( Args *args ){
	return ((ArgsStr*)args)->acc0;
}

int getArgsAcc( Args *args ){
	return ((ArgsStr*)args)->acc;
}

char *getArgsE( Args *args ){
	return ((ArgsStr*)args)->e;
}

char *getArgsF( Args *args ){
	return ((ArgsStr*)args)->f;
}

char *getArgsO( Args *args ){
	return ((ArgsStr*)args)->o;
}

char *getArgsQ( Args *args ){
	return ((ArgsStr*)args)->q;
}

int procArgs( int argc, char **argv, Args *args ){
	((ArgsStr*)args)->acc0 = searchArgsBoolean(argc,argv,"-acc0");
	((ArgsStr*)args)->acc = searchArgsBoolean(argc,argv,"-acc");
	((ArgsStr*)args)->e = searchArgsString(argc,argv,"-e");
	((ArgsStr*)args)->f = searchArgsString(argc,argv,"-f");
	((ArgsStr*)args)->o = searchArgsString(argc,argv,"-o");
	((ArgsStr*)args)->q = searchArgsString(argc,argv,"-q");
	if( ((ArgsStr*)args)->f == NULL || ((ArgsStr*)args)->o == NULL ){
		return 1;
	}
	return 0;
}

char *searchArgsString( int argc, char **argv, char *arg ){
	int i;
	for(i=0;i<argc;i++){
		if( strcmp( arg, *(argv+i) ) == 0 ){
			if( **(argv+i+1) == '-' ){
				return NULL;
			}
			return *(argv+i+1);
		}
	}
	return NULL;
}

int searchArgsBoolean( int argc, char **argv, char *arg ){
	int i;
	for(i=0;i<argc;i++){
		if( strcmp( arg, *(argv+i) ) == 0 ){
			return 1;
		}
	}
	return 0;
}
