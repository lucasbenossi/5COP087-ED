#include "Args.h"
#include <string.h>

char *procArgs( int argc, char **argv, char *arg ){
	int i;
	for(i=0;i<argc;i++){
		if( strcmp( arg, *(argv+i) ) == 0 ){
			return *(argv+i+1);
		}
	}
	return "(null)";
}
