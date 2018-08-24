#ifndef QUICKSORT_H
#define QUICKSORT_H

/*
Defina o tipo de uma função usada para comparar dois elementos em uma ordenação.
Os valores de retorno são:
	-1 - primeiro argumento é menor que o segundo, ou deve ficar antes que o segundo
	0  - primeiro argumento é igual ao segundo, ou ocupam a mesma posição
	+1 - primeiro argumento é maior que o segundo, ou deve ficar depois que o segundo
*/
typedef int (*ComparatorFunc)(void*a,void*b,void*aux);

/*
Recebe um vetor de ponteiros void, o menor e o maior valor dos indices, um
ponteiro para a função que compara os elementos e ordena os elementos desde vetor.
*/
void quickSort( void **data, int left, int right, ComparatorFunc comparator, void *aux );

/*
Recebe um vetor de ponteiros void, troca o elemento do índice a com o elemento
do índice b.
*/
void swap( void **data, int a, int b );

#endif
