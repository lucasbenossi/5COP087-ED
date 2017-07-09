#ifndef ARGS_H
#define ARGS_H

/*
Procura em **argv pela string fornecida em *arg e retorna a proxima string
Exemplo:
	Seja o comando "./t2 -o <arquivo> -f <entrada>"
	procArgs(argc,argv,"-f") retorna um ponteiro para "<entrada>"
	Se a string fornecida em *arg não for encontrada, retorna a string "(null)"
argc = Quantidade de argumentos
**argv = Vetor coms as strings dos argumentos
*arg = Argumento a ser procurado
*/
char *procArgs( int argc, char **argv, char *arg );

#endif
