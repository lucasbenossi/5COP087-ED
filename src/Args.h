#ifndef ARGS_H
#define ARGS_H

/*
Objeto que carrega os argumentos fornecidos na linha de comando, com os
seguintes parametros:
  acc0 = -acc0, 1 ou 0
  acc = -acc, 1 ou 0
  e = -e, string
  f = -f, string
  o = -o, string
  q = -q, string
*/
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
Recebe uma instancia de Args e retorna o parametro correspondente.
*/
int getArgsAcc0( Args *args );
int getArgsAcc( Args *args );
char *getArgsE( Args *args );
char *getArgsF( Args *args );
char *getArgsO( Args *args );
char *getArgsQ( Args *args );
int getArgsId( Args *args );
char *getArgsM( Args *args );
char *getArgsD( Args *args );
int getArgsT( Args *args );
int getArgsNoT2( Args *args );
char *getArgsR( Args *args );
char *getArgsG( Args *args );
char *getArgsH( Args *args );
int getArgsI( Args *args );

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
