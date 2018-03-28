#ifndef RUA_H
#define RUA_H

typedef struct _rua Rua;

Rua *createRua( char *nome, char *ldir, char *lesq, double cmp, double vm );
void destroyRua( Rua *rua );
void destroyRuaVoid( void *rua );

char *getRuaNome( Rua *rua );
char *getRuaLdir( Rua *rua );
char *getRuaLesq( Rua *rua );
double getRuaCmp( Rua *rua );
double getRuaVm( Rua *rua );

double getRuaTempo( Rua *rua );

#endif
