#ifndef FILE_H
#define FILE_H
#include <stdio.h>

/*
Recebe a string com o caminho do arquivo em *fullPath e abre o arquivo
para leitura, retorna o ponteiro para o arquivo aberto, se o arquivos não
pode ser aberto, retorna NULL e escreve uma mensagem de erro no stdout.
*/
FILE *openFileRead( char *fullPath );

/*
Recebe a string com o caminho do arquivo em *fullPath e abre o arquivo
para escrita, retorna o ponteiro para o arquivo aberto, se o arquivos não
pode ser aberto, retorna NULL e escreve uma mensagem de erro no stdout.
Se o arquivo ja existir, sera sobreescrito.
*/
FILE *openFileWrite( char *fullPath );

/*
Recebe a string com o caminho do arquivo em *fullPath e abre o arquivo
para escrita no fim do arquivo, retorna o ponteiro para o arquivo aberto, se o arquivos não
pode ser aberto, retorna NULL e escreve uma mensagem de erro no stdout.
Se o arquivo ja existir, será aberto para escrita no final do arquivo (conteúdo
não será sobreescrito), se o arquivo não existir, será criado.
*/
FILE *openFileAppend( char *fullPath );

/*
Recebe o ponteiro para um arquivo aberto e fecha esse arquivo.
*/
void closeFile( FILE *file );

#endif
