#include "QuickSort.h"

static int partition( void **data, int left, int right, ComparatorFunc comparator, void *aux );

/* ========================================================================== */

void quickSort( void **data, int left, int right, ComparatorFunc comparator, void *aux ){
	int part;

	if( right > left ){
		part = partition( data, left, right, comparator, aux );
		quickSort( data, left, part-1, comparator, aux );
		quickSort( data, part+1, right, comparator, aux );
	}
}

static int partition( void **data, int left, int right, ComparatorFunc comparator, void *aux ){
	int i, j;
	void *pivot;

	pivot = data[right];

	i = left;
	j = right - 1;

	while(1){
		while( comparator( data[i], pivot, aux ) == -1 ){
			i++;
		}

		while( j > i && comparator( data[j], pivot, aux ) == 1 ){
			j--;
		}

		if( i >= j ){
			break;
		}
		else{
			swap( data, i, j );
			i++;
			j--;
		}
	}

	swap( data, i, right );
	return i;
}

void swap( void **data, int a, int b ){
	void *temp;
	if( a != b ){
		temp = data[a];
		data[a] = data[b];
		data[b] = temp;
	}
}
