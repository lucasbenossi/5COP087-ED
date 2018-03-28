#include "Endereco.h"
#include "String.h"
#include "Point.h"
#include "Quadra.h"
#include <stdlib.h>

struct _endereco{
	char *cep;
	char face;
	int num;
	char *compl;
};

Endereco *createEndereco( char *cep, char face, int num, char *compl ){
	Endereco *endereco;

	endereco = malloc(sizeof(Endereco));
	endereco->cep = createString(cep);
	endereco->face = face;
	endereco->num = num;
	endereco->compl = createString(compl);

	return endereco;
}

void destroyEndereco( Endereco *endereco ){
	destroyString(endereco->cep);
	destroyString(endereco->compl);
	free(endereco);
}

char *getEnderecoCep( Endereco *endereco ){
	return endereco->cep;
}

char getEnderecoFace( Endereco *endereco ){
	return endereco->face;
}

int getEnderecoNum( Endereco *endereco ){
	return endereco->num;
}

char *getEnderecoCompl( Endereco *endereco ){
	return endereco->compl;
}

Point *getEnderecoCoords( Endereco *endereco, Quadra *quadra ){
	double x=0, y=0;

	if( endereco->face == 'N' ){
		x = getQuadraX(quadra) + endereco->num;
		y =	getQuadraY(quadra) + getQuadraHeight(quadra);
	}
	else if( endereco->face == 'L' ){
		x = getQuadraX(quadra);
		y = getQuadraY(quadra) + endereco->num;
	}
	else if( endereco->face == 'S' ){
		x = getQuadraX(quadra) + endereco->num;
		y = getQuadraY(quadra);
	}
	else if( endereco->face == 'O' ){
		x = getQuadraX(quadra) + getQuadraWidth(quadra);
		y = getQuadraY(quadra) + endereco->num;
	}

	return createPoint( x, y, endereco->cep, "", "" );
}

int checkFace( char face ){
	if( face != 'N' && face != 'L' && face != 'S' && face != 'O' ){
		return 1;
	}
	return 0;
}
