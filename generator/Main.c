#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 100

static const char *getStringId( int id, int max );

static const char *getRandonString();

static int hashString(char *string);

static char getFace();

static const char *getEndereco( int id, int width, int height );

static const char *getCodt( int codt );

static const char *getDescricao();

static const char *getCnpj();

static const char *getCpf();

static const char *getNomeSobrenome();

static char getSexo();

static const char *getNascimento();

static const char *getOperadora();

static const char *getCelular();

static const char *getEdge(int u, int v);

static const char *getNomeRua();

static const char *getSpeed();

/* ========================================================================== */

int main( int argc, char *argv[] ){
    char *name, nameGeo[STRING_SIZE], nameEc[STRING_SIZE], namePm[STRING_SIZE], nameTm[STRING_SIZE], nameVia[STRING_SIZE];
    int lines, columns, width, height, dist, radius, codt, estab, pessoas;
    int i, j, k, id, x, y;
    FILE *geo, *ec, *pm, *tm, *via;

    if( argc < 11 ){
        /*               0  1    2     3    4     5      6    7      8    9     10                  */
        fprintf(stderr, "%s name lines columns width height dist radius codt estab pessoas\n", argv[0]);
        return 1;
    }

    name = argv[1];
    lines = atoi(argv[2]);
    columns = atoi(argv[3]);
    width = atoi(argv[4]);
    height = atoi(argv[5]);
    dist = atoi(argv[6]);
    radius = atoi(argv[7]);
    codt = atoi(argv[8]);
    estab = atoi(argv[9]);
    pessoas = atoi(argv[10]);

	srand(hashString(name));

    sprintf( nameGeo, "%s.geo", name );
    sprintf( nameEc, "%s.ec", name );
    sprintf( namePm, "%s.pm", name );
    sprintf( nameTm, "%s.tm", name );
    sprintf( nameVia, "%s.via", name );

    geo = fopen( nameGeo, "w" );
    ec = fopen( nameEc, "w" );
    pm = fopen( namePm, "w" );
    tm = fopen( nameTm, "w" );
    via = fopen( nameVia, "w" );


    for( i = 0; i < codt; i++ ){
        fprintf( ec, "t codt%d %s\n", i+1, getDescricao() );
    }

	getStringId( 0, lines*columns );

    id = 1;
    for( i = 0, y = dist; i < lines; i++, y += height+dist ){
        for( j = 0, x = dist; j < columns; j++, x += width+dist ){
			/* q x y larg alt cep */
            fprintf( geo, "q %d %d %d %d cep%s\n", x, y, width, height, getStringId(id,0) );
			/* h x y id */
            fprintf( geo, "h %d %d h%s.1\n", x+width, y+height/2, getStringId(id,0) );
            fprintf( geo, "h %d %d h%s.2\n", x+width/2, y+height, getStringId(id,0) );
			/* t x y id */
            fprintf( geo, "t %d %d t%s\n", x+width/2, y+height/2, getStringId(id,0) );
			/* tI id raio */
            fprintf( geo, "tI t%s %d\n", getStringId(id,0), radius );
			/* {su,um} id */
            fprintf( geo, "%s t%s\n", getOperadora(), getStringId(id,0) );

            for( k = 0; k < estab; k++ ){
				/* e codt cep face num cnpj nome */
				fprintf( ec, "e %s %s %s %s\n", getCodt(codt), getEndereco(id, width, height), getCnpj(), getRandonString() );
            }

            for( k = 0; k < pessoas; k++ ){
				const char *cpf = getCpf();
				/* p cpf nome sobrenome sexo nasc */
				fprintf( pm, "p %s %s %c %s\n", cpf, getNomeSobrenome(), getSexo(), getNascimento() );
				/* m cpf cep face num compl */
				fprintf( pm, "m %s %s %s\n", cpf, getEndereco(id, width, height), getRandonString() );
				/* {su,um} cpf numero */
				fprintf( tm, "%s %s %s\n", getOperadora(), cpf, getCelular() );
            }

            id++;
        }
    }

    lines++;
    columns++;

    getStringId(0, lines*columns);

    id = 1;
    for( i = 0, y = dist; i < lines; i++, y += height+dist ){
        for( j = 0, x = dist; j < columns; j++, x += width+dist ){
            /* s x y id */
            fprintf( geo, "s %d %d s%s\n", x-dist/2, y-dist/2, getStringId(id,0) );
            /* v id x y */
            fprintf( via, "v v%s %d %d\n", getStringId(id,0), x-dist/2, y-dist/2 );

            id++;
        }
    }

    id = 1;
    for( i = 0; i < lines; i++ ){
        for( j = 0; j < columns; j++ ){
            /* e i j ldir lesq cmp vm nome */

            if( j < columns-1 ){
				fprintf( via, "e %s - - %d %s %s\n", getEdge(id, id+1), width+dist/2, getSpeed(), getNomeRua() );
            	fprintf( via, "e %s - - %d %s %s\n", getEdge(id+1, id), width+dist/2, getSpeed(), getNomeRua() );
			}

            if( i < lines-1 ){
				fprintf( via, "e %s - - %d %s %s\n", getEdge(id, id+lines), height+dist/2, getSpeed(), getNomeRua() );
            	fprintf( via, "e %s - - %d %s %s\n", getEdge(id+lines, id), height+dist/2, getSpeed(), getNomeRua() );
			}

            id++;
        }
    }

    fclose(geo);
    fclose(ec);
    fclose(pm);
    fclose(tm);
    fclose(via);

    return 0;
}

static const char *getStringId( int id, int max ){
	static char string[STRING_SIZE];
	static int lenght = 0;

	if( max != 0 ){
		sprintf( string, "%d", max );
		lenght = strlen(string);
		return NULL;
	}

	sprintf( string, "%0*d", lenght, id );
	return string;
}

static const char *getRandonString(){
	static char string[STRING_SIZE];
	int size, c, i;

	size = 5 + rand()%6;
	for( i = 0; i < size; i++ ){
		c = 'a' + rand()%26;
		string[i] = c;
	}
	string[i] = '\0';
	string[0] += 'A' - 'a';

	return string;
}

static int hashString(char *string){
	int N, i, sum;
	static const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109 };
	static const int Nprimes = sizeof(primes) / sizeof(primes[0]);

	sum = 0;
	N = strlen(string);
	if( N > Nprimes ){
		N = Nprimes;
	}
	for( i = 0; i < N; i++ ){
		sum += primes[i] * (int)string[i];
	}

	return sum;
}

static char getFace(){
	int a = rand()%4;
	if( a == 0 ){
		return 'N';
	}
	if( a == 1 ){
		return 'S';
	}
	if( a == 2 ){
		return 'L';
	}
	if( a == 3 ){
		return 'O';
	}
	return ' ';
}

static const char *getEndereco( int id, int width, int height ){
	static char string[STRING_SIZE];
	char face = getFace();
	int num = 0;
	if( face == 'N' || face == 'S' ){
		num = rand()%width;
	}
	else if( face == 'L' || face == 'O' ){
		num = rand()%height;
	}

	sprintf( string, "cep%s %c %d", getStringId(id,0), face, num );

	return string;
}

static const char *getCodt( int codt ){
	static char string[STRING_SIZE];
    static int t = -1;
    t++;
    t = t%codt;
	sprintf( string, "codt%d", t+1 );
    return string;
}

static const char *getDescricao(){
	static char string[STRING_SIZE];

	string[0] = '\0';
	strcat( string, getRandonString() );
	strcat( string, " " );
	strcat( string, getRandonString() );
	strcat( string, " " );
	strcat( string, getRandonString() );
	strcat( string, " " );
	strcat( string, getRandonString() );
	strcat( string, " " );
	strcat( string, getRandonString() );

	return string;
}

static const char *getCnpj(){
	static char string[STRING_SIZE];
	int a, b, c, d, e;

	a = rand()%100;
	b = rand()%1000;
	c = rand()%1000;
	d = rand()%10000;
	e = rand()%100;

	sprintf( string, "%02d.%03d.%03d/%04d-%02d", a, b, c, d, e );

	return string;
}

static const char *getCpf(){
	static char string[STRING_SIZE];
	int a, b, c, d;

	a = rand()%1000;
	b = rand()%1000;
	c = rand()%1000;
	d = rand()%100;

	sprintf( string, "%03d.%03d.%03d-%02d", a, b, c, d );

	return string;
}

static const char *getNomeSobrenome(){
	static char string[STRING_SIZE];

	string[0] = '\0';
	strcat( string, getRandonString() );
	strcat( string, " " );
	strcat( string, getRandonString() );

	return string;
}

static char getSexo(){
	int a = rand()%2;
	if( a == 0 ){
		return 'M';
	}
	if( a == 1 ){
		return 'F';
	}
	return ' ';
}

static const char *getNascimento(){
	static char string[STRING_SIZE];
	int dia, mes, ano;

	dia = 1 + rand() % 30;
	mes = 1 + rand() % 12;
	ano = 1918 + rand()%101;

	sprintf( string, "%02d/%02d/%04d", dia, mes, ano );
	return string;
}

static const char *getOperadora(){
	static int i=-1;
    i++;
    i = i%2;
    if( i == 0 ){
		return "su";
    }
    if( i == 1 ){
		return "um";
    }
	return "";
}

static const char *getCelular(){
    static char string[STRING_SIZE];
    int a, b;

	a = rand()%10000;
	b = rand()%10000;
	sprintf( string, "%04d-%04d", a, b );

    return string;
}

static const char *getEdge(int u, int v){
    static char string[STRING_SIZE];

    string[0] = '\0';
    strcat(string, "v");
    strcat(string, getStringId(u, 0));
    strcat(string, " v");
    strcat(string, getStringId(v, 0));

    return string;
}

static const char *getNomeRua(){
    static char string[STRING_SIZE];

    string[0] = '\0';
    strcat(string, "Rua ");
    strcat(string, getRandonString());
    strcat(string, " ");
    strcat(string, getRandonString());

    return string;
}

static const char *getSpeed(){
    static char string[STRING_SIZE];
    double speed = 1 + rand()%30;

    sprintf( string, "%f", speed );

    return string;
}
