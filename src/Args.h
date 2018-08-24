#ifndef ARGS_H
#define ARGS_H

/*
Estrutura que carrega os argumentos fornecidos na linha de comando.
*/
struct _args{
	int acc0;
	int acc;
	char *e;
	char *f;
	char *o;
	char *q;
	int id;
	char *ec;
	char *pm;
	char *tm;
	char *v;
	char *m;
	int t;
	int noT2;
	char *r;
	char *g;
	char *h;
	char *od;
	char *n;
};
typedef struct _args Args;

/*
Aloca memória para uma instancia de Args
*/
Args *createArgs();

/*
Desaloca memória de uma instancia de Args
*/
void destroyArgs( Args *args );

/*
Processa os argumentos fornecidos na linha de comando
argc = Quantidade de argumentos
**argv = Vetor com as strings dos argumentos
*args = Instancia de Args onde serão definidos os argumentos recebidos
*/
int procArgs( int argc, char **argv, Args *args );

/*
- Procura na linha de comando por argumentos do tipo -a <string>
- Se o argumento foi encontrado, retorna o ponteiro para a string do argumento
  seguinte, caso contrário, retorna NULL
- Ex:
	Seja a linha de comando: "a.out -a string"
	searchArgsString(arc,argv,"-a") returna um ponteiro para "string"
argc = Quantidade de argumentos
**argv = Vetor com as strings dos argumentos
*arq = String com o argumento a ser procurado
*/
char *searchArgsString( int argc, char **argv, char *arg );

/*
- Procura na linha de comando por argumentos do tipo -a
- Se o argumento foi encontrado, retorna 1 (true), caso contrário,
  retorna 0 (false)
- Ex:
	Seja a linha de comando: "a.out -a"
	searchArgsString(argc,argv,"-a") returna 1
	searchArgsString(argc,argv,"-b") returna 0
argc = Quantidade de argumentos
**argv = Vetor com as strings dos argumentos
*arg = String com o argumento a ser procurado
*/
int searchArgsBoolean( int argc, char **argv, char *arg );

#endif
