#include "Args.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct _args{
    int acc0;
    int acc;
    char *e;
    char *f;
    char *o;
    char *q;
    int id;
    char *m;
    char *d;
    int t;
    int noT2;
    char *r;
    char *g;
    char *h;
    int I;
};

Args *createArgs(){
	Args *args;
	args = malloc( sizeof(Args) );
	args->acc0 = 0;
	args->acc = 0;
	args->e = NULL;
	args->f = NULL;
	args->o = NULL;
	args->q = NULL;
    args->id = 0;
    args->m = NULL;
    args->d = NULL;
    args->t = 0;
    args->noT2 = 0;
    args->r = NULL;
    args->g = NULL;
    args->h = NULL;
    args->I = 0;
	return args;
}

void destroyArgs( Args *args ){
	free(args);
}

int getArgsAcc0( Args *args ){
	return args->acc0;
}

int getArgsAcc( Args *args ){
	return args->acc;
}

char *getArgsE( Args *args ){
	return args->e;
}

char *getArgsF( Args *args ){
	return args->f;
}

char *getArgsO( Args *args ){
	return args->o;
}

char *getArgsQ( Args *args ){
	return args->q;
}

int getArgsId( Args *args ){
    return args->id;
}

char *getArgsM( Args *args ){
    return args->m;
}

char *getArgsD( Args *args ){
    return args->d;
}

int getArgsT( Args *args ){
    return args->t;
}

int getArgsNoT2( Args *args ){
    return args->noT2;
}

char *getArgsR( Args *args ){
    return args->r;
}

char *getArgsG( Args *args ){
    return args->g;
}

char *getArgsH( Args *args ){
    return args->h;
}

int getArgsI( Args *args ){
    return args->I;
}

int procArgs( int argc, char **argv, Args *args ){
	args->acc0 = searchArgsBoolean(argc,argv,"-acc0");
	args->acc = searchArgsBoolean(argc,argv,"-acc");
	args->e = searchArgsString(argc,argv,"-e");
	args->f = searchArgsString(argc,argv,"-f");
	args->o = searchArgsString(argc,argv,"-o");
	args->q = searchArgsString(argc,argv,"-q");
    args->id = searchArgsBoolean(argc,argv,"-id");
    args->m = searchArgsString(argc,argv,"-m");
    args->d = searchArgsString(argc,argv,"-d");
    args->t = searchArgsBoolean(argc,argv,"-t");
    args->noT2 = searchArgsBoolean(argc,argv,"-noT2");
    args->r = searchArgsString(argc,argv,"-r");
    args->g = searchArgsString(argc,argv,"-g");
    args->h = searchArgsString(argc,argv,"-h");
    args->I = searchArgsBoolean(argc,argv,"-I");
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
