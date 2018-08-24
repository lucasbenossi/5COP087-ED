#include <math.h>
#include "Geometry.h"
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"

double distancePoints( double x1, double y1, double x2, double y2 ){
	return sqrt( distancePointsSquared(x1, y1, x2, y2) );
}

double distancePointsSquared( double x1, double y1, double x2, double y2 ){
	return pow(x1-x2,2) + pow(y1-y2,2);
}

double *getQuadraticCurve( double xu, double yu, double xv, double yv ){
	double x, y, m, x0, y0, x1, y1, x2, y2;
	const double d=50;
	static double coords[2];

	x = xv-xu;
	y = yv-yu;
	m = y/x;

	x0 = x/2;
	y0 = y/2;

	x1 = d * cos(atan(m)) + x0;
	y1 = d * sin(atan(m)) + y0;

	x2 = -(y1-y0) + x0;
	y2 =  (x1-x0) + y0;

	coords[0] = x2 + xu;
	coords[1] = y2 + yu;

	return coords;
}

int quadrantPointRoot( double rootX, double rootY, double x, double y ){
	if( x <  rootX && y >= rootY ) return NW;
	if( x >= rootX && y >= rootY ) return NE;
	if( x <  rootX && y <  rootY ) return SW;
	if( x >= rootX && y <  rootY ) return SE;
	return 0;
}

int circleCircleOverlap( Circle *c1, Circle *c2 ){
	double x1, y1, r1, x2, y2, r2;
	x1 = getCircleX(c1);
	y1 = getCircleY(c1);
	r1 = getCircleRadius(c1);
	x2 = getCircleX(c2);
	y2 = getCircleY(c2);
	r2 = getCircleRadius(c2);
	if( distancePoints(x1,y1,x2,y2) <= (r1+r2) ){
	    return 1;
	}
	else{
	    return 0;
	}
}

int rectRectOverlap( Rect *r1, Rect *r2 ){
	double x1, y1, w1, h1, x2, y2, w2, h2;
	x1 = getRectX(r1);
	y1 = getRectY(r1);
	w1 = getRectWidth(r1);
	h1 = getRectHeight(r1);
	x2 = getRectX(r2);
	y2 = getRectY(r2);
	w2 = getRectWidth(r2);
	h2 = getRectHeight(r2);
	if( x1+w1<x2 || x2+w2<x1 || y1+h1<y2 || y2+h2<y1 ){
	    return 0;
	}
	else{
	    return 1;
	}
}

int circleRectOverlap( Circle *c, Rect *r ){
	double x1, y1, x2, y2, cx, cy;
	x1 = getRectX(r);
	y1 = getRectY(r);
	x2 = getRectX(r) + getRectWidth(r);
	y2 = getRectY(r) + getRectHeight(r);
	cx = getCircleX(c);
	cy = getCircleY(c);
	if( pointInsideRect( cx, cy, r ) == 1 ){
	    return 1;
	}
	else if( cx < x1 && cx < x2 && cy < y1 && cy < y2 ){
	    return pointInsideCircle( x1, y1, c );
	}
	else if( cx >= x1 && cx <= x2 && cy < y1 && cy < y2 ){
	    return pointInsideCircle( cx, y1, c );
	}
	else if( cx > x1 && cx > x2 && cy < y1 && cy < y2 ){
	    return pointInsideCircle( x2, y1, c );
	}
	else if( cx > x1 && cx > x2 && cy >= y1 && cy <= y2 ){
	    return pointInsideCircle( x2, cy, c );
	}
	else if( cx > x1 && cx > x2 && cy > y1 && cy > y2 ){
	    return pointInsideCircle( x2, y2, c );
	}
	else if( cx >= x1 && cx <= x2 && cy > y1 && cy > y2 ){
	    return pointInsideCircle( cx, y2, c );
	}
	else if( cx < x1 && cx < x2 && cy > y1 && cy > y2 ){
	    return pointInsideCircle( x1, y2, c );
	}
	else if( cx < x1 && cx < x2 && cy >= y1 && cy <= y2 ){
	    return pointInsideCircle( x1, cy, c );
	}
	return 0;
}

int pointInsideCircle( double x, double y, Circle *c ){
	if( distancePoints( getCircleX(c), getCircleY(c), x, y ) <= getCircleRadius(c) ){
	    return 1;
	}
	return 0;
}

int pointInsideRect( double x, double y, Rect *r ){
	if( x >= getRectX(r) && x <= getRectX(r) + getRectWidth(r) && y >= getRectY(r) && y <= getRectY(r) + getRectHeight(r) ){
	    return 1;
	}
	return 0;
}

int quadraInsideCircle( Quadra *q, Circle *c ){
	int c1, c2, c3, c4;
	c1 = pointInsideCircle( getQuadraX(q), getQuadraY(q), c );
	c2 = pointInsideCircle( getQuadraX(q)+getQuadraWidth(q), getQuadraY(q), c );
	c3 = pointInsideCircle( getQuadraX(q)+getQuadraWidth(q), getQuadraY(q)+getQuadraHeight(q), c );
	c4 = pointInsideCircle( getQuadraX(q), getQuadraY(q)+getQuadraHeight(q), c );
	return c1*c2*c3*c4;
}

int quadraInsideRect( Quadra *q, Rect *r ){
	double rX1, rY1, rX2, rY2;
	double qX1, qY1, qX2, qY2;
	rX1 = getRectX(r);
	rY1 = getRectY(r);
	rX2 = getRectX(r)+getRectWidth(r);
	rY2 = getRectY(r)+getRectHeight(r);
	qX1 = getQuadraX(q);
	qY1 = getQuadraY(q);
	qX2 = getQuadraX(q)+getQuadraWidth(q);
	qY2 = getQuadraY(q)+getQuadraHeight(q);
	if( rX1 <= qX1 && rY1 <= qY1 && rX2 >= qX2 && rY2 >= qY2 ){
	    return 1;
	}
	return 0;
}

void edgesCircleCircle( Circle *c1, Circle *c2, double *x1, double *y1, double *x2, double *y2 ){
	if( getCircleX(c1) - getCircleRadius(c1) < getCircleX(c2) - getCircleRadius(c2) ){
	    *x1 = getCircleX(c1) - getCircleRadius(c1);
	}
	else{
	    *x1 = getCircleX(c2) - getCircleRadius(c2);
	}

	if( getCircleY(c1) - getCircleRadius(c1) < getCircleY(c2) - getCircleRadius(c2) ){
	    *y1 = getCircleY(c1) - getCircleRadius(c1);
	}
	else{
	    *y1 = getCircleY(c2) - getCircleRadius(c2);
	}

	if( getCircleX(c1) + getCircleRadius(c1) > getCircleX(c2) + getCircleRadius(c2) ){
	    *x2 = getCircleX(c1) + getCircleRadius(c1);
	}
	else{
	    *x2 = getCircleX(c2) + getCircleRadius(c2);
	}

	if( getCircleY(c1) + getCircleRadius(c1) > getCircleY(c2) + getCircleRadius(c2) ){
	    *y2 = getCircleY(c1) + getCircleRadius(c1);
	}
	else{
	    *y2 = getCircleY(c2) + getCircleRadius(c2);
	}
}

void edgesRectRect( Rect *r1, Rect *r2, double *x1, double *y1, double *x2, double *y2 ){
	if( getRectX(r1) < getRectX(r2) ){
	    *x1 = getRectX(r1);
	}
	else{
	    *x1 = getRectX(r2);
	}

	if( getRectY(r1) < getRectY(r2) ){
	    *y1 = getRectY(r1);
	}
	else{
	    *y1 = getRectY(r2);
	}

	if( getRectX(r1) + getRectWidth(r1) > getRectX(r2) + getRectWidth(r2) ){
	    *x2 = getRectX(r1) + getRectWidth(r1);
	}
	else{
	    *x2 = getRectX(r2) + getRectWidth(r2);
	}

	if( getRectY(r1) + getRectHeight(r1) > getRectY(r2) + getRectHeight(r2) ){
	    *y2 = getRectY(r1) + getRectHeight(r1);
	}
	else{
	    *y2 = getRectY(r2) + getRectHeight(r2);
	}
}

void edgesCircleRect( Circle *c, Rect *r, double *x1, double *y1, double *x2, double *y2 ){
	if( getCircleX(c) - getCircleRadius(c) < getRectX(r) ){
	    *x1 = getCircleX(c) - getCircleRadius(c);
	}
	else{
	    *x1 = getRectX(r);
	}

	if( getCircleY(c) - getCircleRadius(c) < getRectY(r) ){
	    *y1 = getCircleY(c) - getCircleRadius(c);
	}
	else{
	    *y1 = getRectY(r);
	}

	if( getCircleX(c) + getCircleRadius(c) > getRectX(r) + getRectWidth(r) ){
	    *x2 = getCircleX(c) + getCircleRadius(c);
	}
	else{
	    *x2 = getRectX(r) + getRectWidth(r);
	}

	if( getCircleY(c) + getCircleRadius(c) > getRectY(r) + getRectHeight(r) ){
	    *y2 = getCircleY(c) + getCircleRadius(c);
	}
	else{
	    *y2 = getRectY(r) + getRectHeight(r);
	}
}
