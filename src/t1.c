#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *procArgs( int argc, char **argv, char *arg );
void fixLineBreak( char **string );
char *takeString( char *line );
char *takeDir( char *line );
char *takeText( char *line );

char *allocChar( int size );
void freeChar( char **ptr );
void catContent( char **s, char *c );
void repContent( char **s, char *c );
void cleanAll( char **s );

char *genFullPath( char *dir, char *file, char *ext );
char *fixDir( char *dir );
void writeFile( FILE *file, char *string );
void runCommand( FILE *infile, char **dir );

int main( int argc, char **argv ){
	if( argc < 4 ){
		printf("Uso: %s -f arquivo -o dir\n",argv[0]);
		return 1;
	}

	char *dir;
	dir = allocChar(0);
	repContent(&dir,procArgs(argc,argv,"-o"));

	FILE *infile;
	infile = fopen(procArgs(argc,argv,"-f"),"r");
	//infile = stdin;
	if( infile == NULL ){
		printf("ERRO: Falha ao abrir o arquivo de entrada.\n");
		return 1;
	}

	runCommand( infile, &dir );

	fclose(infile);

	freeChar(&dir);

	return 0;

}

//Procura em **argv pela string fornecida em *arg e retorna a proxima string
//Exemplo:
//	Seja o comando "./t1 -o <arquivo> -f <entrada>"
//	procArgs(argc,argv,"-f") retorna um ponteiro para "<entrada>"
//	Se a string fornecida em *arg não for encontrada, retorna a string "(null)"
//argc = Quantidade de argumentos
//**argv = Vetor coms as strings dos argumentos
//*arg = Argumento a ser procurado
char *procArgs( int argc, char **argv, char *arg ){
	int i;
	for(i=0;i<argc;i++){
		if( strcmp( arg, *(argv+i) ) == 0 ){
			return *(argv+i+1);
		}
	}
	return "(null)";
}

//Recebe uma string em **string, procura por "\n" e substitui por quebra de linha
void fixLineBreak( char **string ){
	int i, j, size;
	char *newString;
	i = 0;
	j = 0;
	size = strlen( *string );
	newString = allocChar( size );
	while( i < size ){
		if( *(*string+i) == '\\' && *(*string+i+1) == 'n' ){
			*(newString+j) = '\n';
			i+=2;
		}
		else{
			*(newString+j) = *(*string+i);
			i++;
		}
		j++;
	}
	*(newString+j) = '\0';
	free( *string );
	*string = newString;
}

//Recebe em *line a string de uma linha de comando do tipo x "<string>", sendo x o comando,
//retorna um ponteiro para uma string contendo o conteúdo de <string>.
char *takeString( char *line ){
	int size;
	char *string;
	size = strlen(line) - 5;
	if( size > 0 ){
		string = allocChar(size);
		sscanf(line,"%*c \"%[^\"]s\"",string);
	}
	else{
		string = allocChar(0);
	}
	return string;
}

//Recebe em *line a string de uma linha de comando do tipo x <path>, sendo x o comando,
//retorna um ponteiro para uma string contendo o conteúdo de <path>.
char *takeDir( char *line ){
	int size;
	char *dir;
    size = strlen(line) - 3;
	if( size > 0 ){
		dir = allocChar(size);
		sscanf(line,"%*c %[^\n\r]s",dir);
	}
	else{
		dir = allocChar(0);
	}
	return dir;
}

//Recebe em *line a string de uma linha de comando do tipo x <texto>, sendo x o comando,
//retorna um ponteiro para uma string contendo o conteúdo de <texto>.
char *takeText( char *line ){
	int size;
	char *text;
    size = strlen(line) - 3;
	if( size > 0 ){
		text = allocChar(size);
		sscanf(line,"%*c %[^\n\r]s",text);
	}
	else{
		text = allocChar(0);
	}
	return text;
}

//Aloca memória para (size+1) caracteres, insere o caractere \0 na primeira,
//posição da região de memória alocada, retorna o endereço de memoria.
char *allocChar( int size ){
	char *ptr;
	ptr = malloc( (size+1) * sizeof(char) );
	*ptr = '\0';
	return ptr;
}

//Desaloca um ponteiro para string e o aponta para NULL;
void freeChar( char **ptr ){
	if( *ptr != NULL ){
		free( *ptr );
		*ptr = NULL;
	}
}

//Concatena o conteúdo da string em **s, com o conteúdo da string *c.
//Realocação de memória é feito internamente.
void catContent( char **s, char *c ){
	int sizeC;
	sizeC = strlen(c);
	if( sizeC > 0 ){
		int sizeS;
		char *newS;
		sizeS = strlen(*s);
		newS = allocChar( sizeS + sizeC );
		strcpy(newS, *s);
		strcat(newS, c);
		free(*s);
		*s = newS;
	}
}

//Substitui o conteúdo da string em **s, com o conteúdo da string *c.
//Realocação de memória é feito internamente.
void repContent( char **s, char *c ){
	int sizeC;
	sizeC = strlen(c);
	if( sizeC > 0 ){
		free(*s);
		*s = allocChar(sizeC);
		strcpy(*s,c);
	}
	else{
		cleanAll(s);
	}
}

//Desaloca uma string fornecida em **s, realoca com tamanho para um único char, e insere o caractere \0.
void cleanAll( char **s ){
	free(*s);
	*s = allocChar(0);
}

//Usa o conteúdo das string em *dir, *file e *ext para gerar uma string com o caminho
//completo do arquivo.
//Retorna o endereço de memória dessa string gerada.
char *genFullPath( char *dir, char *file, char *ext ){
	char *fullPath;
	char *fixedDir;
	fullPath = allocChar(0);
	fixedDir = fixDir(dir);
	catContent(&fullPath,fixedDir);
	catContent(&fullPath,file);
	catContent(&fullPath,".");
	catContent(&fullPath,ext);
	free(fixedDir);
	return fullPath;
}

//Recebe em *dir a string com o diretório, insere ".", "./" no início ou "/" no final conforme necessário,
//gera uma nova string e retorna o seu endereço de memória.
//  .       -> ok
//  ./		-> ok
//  ./pasta -> ok
//  .pasta  -> ./.pasta
//  /pasta  -> ok
//  pasta   -> ./pasta
char *fixDir( char *dir ){
	char *newDir;
	newDir = allocChar(0);
	if( *dir == '.' ){
		if( *(dir+1) == '\0' ){
			catContent(&newDir,dir);
		}
		else if( *(dir+1) == '/' ){
			catContent(&newDir,dir);
		}
		else{
			catContent(&newDir,"./");
			catContent(&newDir,dir);
		}
	}
	else if( *dir == '/' ){
		catContent(&newDir,dir);
	}
	else{
		catContent(&newDir,"./");
		catContent(&newDir,dir);
	}
	if( *(dir+strlen(dir)-1) != '/' ){
		catContent(&newDir,"/");
	}
	return newDir;
}

//Escreve o conteúdo de *string no arquivo aberto em *file, se o arquivo estiver aberto.
void writeFile( FILE *file, char *string ){
	if( file != NULL ){
		fputs(string,file);
		fprintf(file,"\n");
	}
	else{
		printf("ERRO: Arquivo não aberto.\n");
	}
}

//Processa e executa os comandos fornecidos no arquivo em *infile, recebe o diretório de saída em *dir.
void runCommand( FILE *infile, char **dir ){
	char line[1000000], *X, *Y, *Z, *file, *ext;
	char *string, *path, *fullPath, *text;
	FILE *outfile;

	outfile = NULL;

	X = allocChar(0);
	Y = allocChar(0);
	Z = allocChar(0);
    file = allocChar(0);
    ext = allocChar(0);

	string = NULL;
	path = NULL;
	fullPath = NULL;
	text = NULL;

	while( fgets(line,1000000,infile) != NULL ){
		switch( line[0] ){
			case 'x' :
				string = takeString(line);
				catContent(&X,string);
				freeChar(&string);
				break;
			case 'y' :
				string = takeString(line);
				catContent(&Y,string);
				freeChar(&string);
				break;
			case 'z' :
				string = takeString(line);
				catContent(&Z,string);
				freeChar(&string);
				break;
			case 'l' :
				switch( line[1] ){
					case 'x' :
						cleanAll(&X);
						break;
					case 'y' :
						cleanAll(&Y);
						break;
					case 'z' :
						cleanAll(&Z);
						break;
				}
				break;
			case 'd' :
				if( line[2] == '#' ){
					switch( line[3] ){
						case 'x' :
							repContent(dir,X);
							break;
						case 'y' :
							repContent(dir,Y);
							break;
						case 'z' :
							repContent(dir,Z);
							break;
					}
				}
				else{
					path = takeDir(line);
					repContent(dir,path);
					freeChar(&path);
				}
				break;
			case 'a' :
				if( line[2] == '#' ){
					switch( line[3] ){
						case 'x' :
							repContent(&file,X);
							break;
						case 'y' :
							repContent(&file,Y);
							break;
						case 'z' :
							repContent(&file,Z);
							break;
					}
				}
				else{
					string = takeString(line);
					repContent(&file,string);
					freeChar(&string);
				}
				break;
			case 'e' :
				if( line[2] == '#' ){
					switch( line[3] ){
						case 'x' :
							repContent(&ext,X);
							break;
						case 'y' :
							repContent(&ext,Y);
							break;
						case 'z' :
							repContent(&ext,Z);
							break;
					}
				}
				else{
					string = takeString(line);
					repContent(&ext,string);
					freeChar(&string);
				}
				break;
			case 'c' :
				fullPath = genFullPath(*dir,file,ext);
				outfile = fopen(fullPath,"w");
				freeChar(&fullPath);
				break;
			case 'o' :
				fullPath = genFullPath(*dir,file,ext);
				outfile = fopen(fullPath,"a");
				freeChar(&fullPath);
				break;
			case 'w' :
				if( line[2] == '#' ){
					switch( line[3] ){
						case 'x' :
							writeFile(outfile,X);
							break;
						case 'y' :
							writeFile(outfile,Y);
							break;
						case 'z' :
							writeFile(outfile,Z);
							break;
					}
				}
				else{
					text = takeText(line);
					writeFile(outfile,text);
					freeChar(&text);
				}
				break;
			case 'f' :
				if( outfile != NULL ){
					fclose(outfile);
					outfile = NULL;
				}
				break;
			case 'p' :
				switch ( line[1] ) {
					case 'x': printf("Conteudo de X: %s\n",X); break;
					case 'y': printf("Conteudo de Y: %s\n",Y); break;
					case 'z': printf("Conteudo de Z: %s\n",Z); break;
					case 'd': printf("Conteudo de dir: %s\n",*dir); break;
					case 'a': printf("Conteudo de file: %s\n",file); break;
					case 'e': printf("Conteudo de ext: %s\n",ext); break;
					case 'c':
						fullPath = genFullPath(*dir,file,ext);
						printf("Conteudo de fullPath: %s\n",fullPath);
						freeChar(&fullPath);
						break;
					case 'o':
						fullPath = genFullPath(*dir,file,ext);
						printf("Conteudo de fullPath: %s\n",fullPath);
						freeChar(&fullPath);
						break;
				}
		}
	}
	freeChar(&X);
	freeChar(&Y);
	freeChar(&Z);
	freeChar(&file);
	freeChar(&ext);
}
