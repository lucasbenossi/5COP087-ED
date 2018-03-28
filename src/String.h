#ifndef STRING_H
#define STRING_H

#define STRING_SIZE 100
#define STRING_SIZE_LARGE 1000

/*
- Aloca uma string e copia o conteúdo da string fornecida em "string" para a
  string alocada, retorna o ponteiro para a string alocada.
- A string alocada tem o mesmo tamanho que a string fornecida em "string".
*/
char *createString( const char *string );

/*
- Desaloca memória de uma string
*/
void destroyString( char *string );
void destroyStringVoid( void *string );

/*
- Aloca memória para (size+1) caracteres, preenche a região alocada com caracteres
  "\0", retorna o endereço de memoria.
*/
char *allocChar( int size );

/*
- Concatena o conteũdo de n strings em uma nova string.
- Se n == 0, retorna NULL;
- Se todas as strings fornecidas forem NULL, retorna uma string vazia.
*/
char *createStringCat( int n, ... );

/*
Converte inteiro para string.
*/
char *createStringInt( int n );

/*
- Concatena o conteúdo da string em **s, com o conteúdo da string *c.
- Realocação de memória é feito internamente.
*/
void catString( char **s, const char *c );

/*
- Substitui o conteúdo da string em **s, com o conteúdo da string *c.
- Realocação de memória é feito internamente.
*/
void repString( char **s, const char *c );

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

/*
- Recebe a string com o caminho para um arquivo fornecido como argumento na linha
  de comandos e retorna um ponteiro para string apenas com o nome do arquivo, sem
  a extencao ou o diretorio
*/
char *fileRemovePathExt( char *pathFileExt );

#endif
