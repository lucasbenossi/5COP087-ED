#include <math.h>
#include "Geometry.h"
#include "Circle.h"
#include "Rect.h"

double distancePoints( double x1, double y1, double x2, double y2 ){
    return sqrt( pow(x1-x2,2) + pow(y1-y2,2) );
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
    if( pointInsideRect( r, cx, cy ) == 1 ){
        return 1;
    }
    else if( cx < x1 && cx < x2 && cy < y1 && cy < y2 ){
        return pointInsideCircle( c, x1, y1 );
    }
    else if( cx >= x1 && cx <= x2 && cy < y1 && cy < y2 ){
        return pointInsideCircle( c, cx, y1 );
    }
    else if( cx > x1 && cx > x2 && cy < y1 && cy < y2 ){
        return pointInsideCircle( c, x2, y1 );
    }
    else if( cx > x1 && cx > x2 && cy >= y1 && cy <= y2 ){
        return pointInsideCircle( c, x2, cy );
    }
    else if( cx > x1 && cx > x2 && cy > y1 && cy > y2 ){
        return pointInsideCircle( c, x2, y2 );
    }
    else if( cx >= x1 && cx <= x2 && cy > y1 && cy > y2 ){
        return pointInsideCircle( c, cx, y2 );
    }
    else if( cx < x1 && cx < x2 && cy > y1 && cy > y2 ){
        return pointInsideCircle( c, x1, y2 );
    }
    else if( cx < x1 && cx < x2 && cy >= y1 && cy <= y2 ){
        return pointInsideCircle( c, x1, cy );
    }
}

int pointInsideCircle( Circle *c, double x, double y ){
    if( distancePoints( getCircleX(c), getCircleY(c), x, y ) <= getCircleRadius(c) ){
        return 1;
    }
    else{
        return 0;
    }
}

int pointInsideRect( Rect *r, double x, double y ){
    if( x >= getRectX(r) && x <= getRectX(r) + getRectWidth(r) && y >= getRectY(r) && y <= getRectY(r) + getRectHeight(r) ){
        return 1;
    }
    else{
        return 0;
    }
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
