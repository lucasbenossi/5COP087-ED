#include <stdio.h>
#include <stdlib.h>
#include "CreateSvg.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "Object.h"
#include "WriteTags.h"
#include "Cidade.h"
#include "File.h"

void createSvg( List *l, Cidade *c, char *file, char *fixedDir, int method, int argT, int noT2 ){
    char *fullPath;
    FILE *svg;

    fullPath = createStringCat( 3, fixedDir, file, ".svg" );

    svg = openFileWrite(fullPath);
    if( svg == NULL ){
		destroyString(fullPath);
		return;
    }

    writeSvgStart(svg);

    writeCidadeTags( c, svg, method );

    if( argT == 1 ){
        writeCidadeTorresCoberturaTags( c, svg, method );
    }

    if( noT2 == 0 ){
        writeObjsTags( l, svg );
    }

    writeSvgEnd(svg);

	closeFile(svg);

	destroyString(fullPath);
}
