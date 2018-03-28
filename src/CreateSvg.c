#include <stdio.h>
#include <stdlib.h>
#include "CreateSvg.h"
#include "String.h"
#include "LinkedList.h"
#include "Object.h"
#include "WriteTags.h"
#include "Cidade.h"
#include "File.h"

void createSvg( List *objs, Cidade *cidade, char *file, char *fixedDir, int argT, int noT2 ){
	char *fullPath;
	FILE *svg;

	fullPath = createStringCat( 3, fixedDir, file, ".svg" );

	svg = openFileWrite(fullPath);
	if( svg == NULL ){
		destroyString(fullPath);
		return;
	}

	writeSvgStart(svg);

	writeCidadeTags( cidade, svg );

	writeEstabComerciaisTag( cidade, svg );
	writeMoradoresTag( cidade, svg );
	writeConexoesTags( cidade, svg );
	writeDefuntosTags( cidade, svg );

	if( argT == 1 ){
	    writeCidadeTorresCoberturaTags( cidade, svg );
	}

	if( noT2 == 0 ){
	    writeObjsTags( objs, svg );
	}

	writeSvgEnd(svg);

	closeFile(svg);

	destroyString(fullPath);
}
