#ifndef PROCSTRING_H
#define PROCSTRING_H

/*
Aloca uma string e copia o conteudo de *color dentro dela, retorna o ponteiro
para essa string
*/
char *allocColor( char *color );

/*
Recebe o caminho para um arquivo fornecido em "-f" e retorna um ponteiro para
string apenas com o nome do arquivo, sem a extencao ou o diretorio
*/
char *fileRemovePathExt( char *pathFileExt );

/*
Recebe em *dir a string com o diretório, insere ".", "./" no início ou "/" no
final conforme necessário, gera uma nova string e retorna o seu endereço de
memória.
  .         -> ok
  ./        -> ok
  ./pasta   -> ok
  .pasta    -> ./.pasta
  /pasta    -> ok
  pasta     -> ./pasta
*/
char *fixDir( char *dir );

/*
Aloca memória para (size+1) caracteres, insere o caractere \0 na primeira,
posição da região de memória alocada, retorna o endereço de memoria.
*/
char *allocChar( int size );

/*
Concatena o conteúdo da string em **s, com o conteúdo da string *c.
Realocação de memória é feito internamente.
*/
void catString( char **s, char *c );

/*
Substitui o conteúdo da string em **s, com o conteúdo da string *c.
Realocação de memória é feito internamente.
*/
void repString( char **s, char *c );

/*
Desaloca uma string fornecida em **s, realoca com tamanho para um único char, e insere o caractere \0.
*/
void cleanString( char **s );

/*
Usa o conteúdo das string em *fixedDir, *fixedFile e *ext para gerar uma string com o caminho
completo do arquivo.
Retorna o endereço de memória dessa string gerada.
*/
char *genFullPath( char *fixedDir, char *fixedFile, char *ext );

#endif
