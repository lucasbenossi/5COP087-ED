#ifndef HASHTABLEDUMP_H
#define HASHTABLEDUMP_H
#include "HashTable.h"
#include <stdio.h>

/*
Dumpa em out, usando o formato dot, a tabela hash fornecida em table.
*/
void dumpHashTableDot( HashTable *table, FILE *out );

#endif
