#include "ConvexHull.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Array.h"
#include "Object.h"
#include "Quadra.h"
#include "Point.h"
#include "Circle.h"
#include "ObjList.h"
#include "QuickSort.h"
#include <stdio.h>

static int comparatorAngle( void *a, void *b );

static int comparatorCollinear( void *a, void *b );

static int findLowestY( void **data, int size );

static int isTurnCCW( Object *a, Object *b, Object *c );

/* ======================================================================================================================= */

static double X0;
static double Y0;

/* ======================================================================================================================= */

int sortAngle( Array *array ){
	int size, index;
	void **data;

	size = getArraySize(array);
	data = getArrayData(array);

	index = findLowestY(data,size);
	if( index == -1 ){
		return 1;
	}
	swap( data, index, 0 );

	X0 = getX(data[0]);
	Y0 = getY(data[0]);

	quickSort( data, 1, size-1, comparatorAngle );
	return 0;
}

int sortAngleCollinear( Array *array ){
	int size, i, left, right;
	void **data;

	if( sortAngle(array) == 1 ){
		return 1;
	}

	size = getArraySize(array);
	data = getArrayData(array);

	i = size - 1;
	while( data[i] == NULL ){
		i--;
	}

	if( i < 2 ){
		return 0;
	}

	if( isTurnCCW( data[0], data[i], data[i-1] ) != 0 ){
		return 0;
	}

	right = i;
	i--;

	while( i-1 > 0 && isTurnCCW( data[0], data[i], data[i-1] ) == 0 ){
		i--;
	}

	left = i;

	quickSort( data, left, right, comparatorCollinear );

	return 0;
}

void grahanScan( Array *array, Stack *stack ){
	int i, k, size;
	void **data;

	size = getArraySize(array);
	data = getArrayData(array);

	if( size == 0 ){
		return;
	}

	if( data[0] == NULL ){
		return;
	}
	push(stack,data[0]);
	data[0] = NULL;
	k = 0;

	i = 1;
	while( i+1 < size && data[i+1] != NULL && isTurnCCW( top(stack), data[i], data[i+1] ) != 1 ){
		i++;
	}

	if( i < size ){
		if( data[i] == NULL ){
			return;
		}
		push(stack,data[i]);
		data[i] = NULL;
	}

	if( i+1 < size ){
		if( data[i+1] == NULL ){
			return;
		}
		push(stack,data[i+1]);
		data[i+1] = NULL;
	}

	i+=2;
	if( i >= size ){
		return;
	}
	while( i < size && data[i] != NULL ){
		while( isTurnCCW( nextToTop(stack), top(stack), data[i] ) != 1 ){
			data[k] = pop(stack);
			while( data[k] != NULL ){
				k++;
			}
		}
		push(stack,data[i]);
		data[i] = NULL;
		i++;
	}
}

void grahanScanCollinear( Array *array, Stack *stack ){
	int i, k, size;
	void **data;

	size = getArraySize(array);
	data = getArrayData(array);

	for( i = 0; i < size && i < 3; i++ ){
		if( data[i] == NULL ){
			return;
		}
		push( stack, data[i] );
		data[i] = NULL;
	}
	k = 0;

	i = 3;
	while( i < size && data[i] != NULL ){
		while( isTurnCCW( nextToTop(stack), top(stack), data[i] ) == -1 ){
			data[k] = pop(stack);
			while( data[k] != NULL ){
				k++;
			}
		}
		push(stack,data[i]);
		data[i] = NULL;
		i++;
	}
}

/* ======================================================================================================================= */

static int comparatorAngle( void *a, void *b ){
	double Xa, Ya, Xb, Yb, cotanA, cotanB;

	if( a == NULL && b != NULL ){
		return 1;
	}
	if( a != NULL && b == NULL ){
		return -1;
	}
	if( a == NULL && b == NULL ){
		return 0;
	}

	Xa = getX(a) - X0;
	Ya = getY(a) - Y0;
	Xb = getX(b) - X0;
	Yb = getY(b) - Y0;

	if( Ya == 0 && Yb != 0 ){
		return -1;
	}
	if( Ya != 0 && Yb == 0 ){
		return 1;
	}
	if( Ya == 0 && Yb == 0 ){
		if( Xa < Xb ){
			return -1;
		}
		if( Xa > Xb ){
			return 1;
		}
		return 0;
	}

	cotanA = -1 * Xa/Ya;
	cotanB = -1 * Xb/Yb;

	if( cotanA < cotanB ){
		return -1;
	}
	if( cotanA > cotanB ){
		return 1;
	}
	if( cotanA == cotanB ){
		if( Ya < Yb ){
			return -1;
		}
		if( Ya > Yb ){
			return 1;
		}
	}
	return 0;
}

static int comparatorCollinear( void *a, void *b ){
	double Xa, Ya, Xb, Yb;

	Xa = getX(a) - X0;
	Ya = getY(a) - Y0;
	Xb = getX(b) - X0;
	Yb = getY(b) - Y0;

	if( Ya == 0 && Yb == 0 ){
		if( Xa < Xb ){
			return 1;
		}
		if( Xa > Xb ){
			return -1;
		}
		return 0;
	}

	if( Ya < Yb ){
		return 1;
	}
	if( Ya > Yb ){
		return -1;
	}
	return 0;
}

static int findLowestY( void **data, int size ){
	int i, j, index;
	double X, Y, lowestX, lowestY;

	j = 0;
	while( j < size && data[j] == NULL ){
		j++;
	}
	if( j == size ){
		return -1;
	}

	lowestX = getX(data[j]);
	lowestY = getY(data[j]);
	index = j;

	for( i = j+1; i < size; i++ ){
		if( data[i] != NULL ){
			Y = getY(data[i]);
			X = getX(data[i]);
			if( Y < lowestY ){
				lowestY = Y;
				lowestX = X;
				index = i;
			}
			else if( Y == lowestY ){
				if( X < lowestX ){
					lowestX = X;
					index = i;
				}
			}
		}
	}

	return index;
}

static int isTurnCCW( Object *a, Object *b, Object *c ){
	double area, aX, aY, bX, bY, cX, cY;

	aX = getX(a);
	aY = getY(a);
	bX = getX(b);
	bY = getY(b);
	cX = getX(c);
	cY = getY(c);

	area = (bX - aX)*(cY-aY) - (bY-aY)*(cX-aX);

	if( area > 0 ){
		return 1; /* ccw */
	}
	if( area < 0 ){
		return -1; /* cw */
	}
	return 0;
}
