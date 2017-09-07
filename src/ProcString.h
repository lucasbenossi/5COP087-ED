#ifndef PROCSTRING_H
#define PROCSTRING_H

/*
- Aloca uma string e copia o conteúdo da string fornecida em "pString" para a
  string alocada, retorna o ponteiro para a string alocada.
- A string alocada tem o mesmo tamanho que a string fornecida em "pString".
*/
char *createString( char *pString );

/*
- Desaloca memória de uma string
*/
void destroyString( char *string );

/*
- Aloca memória para (size+1) caracteres, preenche a região alocada com caracteres
  "\0", retorna o endereço de memoria.
*/
char *allocChar( int size );

/*
- Aloca uma string e copia o conteúdo das strings fornecidas como paramentros
  para a string alocada, retorna o ponteiro para a string alocada.
- A string alocada tem o mesmo tamanho que as strings fornecidas como argumento.
- As strings fornecidas como argumento podem ser ponteiros NULL.
- Se todas as strings fornecidas como argumento forem pontiros NULL, retora NULL.
*/
char *createStringCat( char *s1, char *s2, char *s3, char *s4, char *s5 );

/*
- Concatena o conteúdo da string em **s, com o conteúdo da string *c.
- Realocação de memória é feito internamente.
*/
void catString( char **s, char *c );

/*
- Substitui o conteúdo da string em **s, com o conteúdo da string *c.
- Realocação de memória é feito internamente.
*/
void repString( char **s, char *c );

/*
- Recebe a string com o caminho para um arquivo fornecido como argumento na linha
  de comandos e retorna um ponteiro para string apenas com o nome do arquivo, sem
  a extencao ou o diretorio
*/
char *fileRemovePathExt( char *pathFileExt );

/*
- Recebe em *dir a string com o diretório, insere ".", "./" no início ou "/" no
  final conforme necessário, aloca uma nova string e retorna o seu endereço de
  memória.
  .         -> ok
  ./        -> ok
  ./pasta   -> ok
  .pasta    -> ./.pasta
  /pasta    -> ok
  pasta     -> ./pasta
*/
char *fixDir( char *dir );

#endif
