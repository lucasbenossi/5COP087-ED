#include <stdio.h>
#include <string.h>
#include "Rect.h"
#include "Circle.h"
#include "Quadra.h"
#include "Point.h"

void writeRectTag( Rect *rect, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%d\" ", getRectId(rect));
    fprintf(svg, "x=\"%f\" ", getRectX(rect));
    fprintf(svg, "y=\"%f\" ", getRectY(rect));
    fprintf(svg, "width=\"%f\" ", getRectWidth(rect));
    fprintf(svg, "height=\"%f\" ", getRectHeight(rect));
    fprintf(svg, "fill=\"%s\" ", getRectFill(rect));
    fprintf(svg, "stroke-width=\"%f\" ", 1.0);
    fprintf(svg, "stroke=\"%s\" ", "black");
    fprintf(svg, "/>\n");
}

void writeCircleTag( Circle *circle, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%d\" ", getCircleId(circle));
    fprintf(svg, "cx=\"%f\" ", getCircleX(circle));
    fprintf(svg, "cy=\"%f\" ", getCircleY(circle));
    fprintf(svg, "r=\"%f\" ", getCircleRadius(circle));
    fprintf(svg, "fill=\"%s\" ", getCircleFill(circle));
    fprintf(svg, "stroke-width=\"%f\" ", 1.0);
    fprintf(svg, "stroke=\"%s\" ", "black");
    fprintf(svg, "/>\n");
}

void writeOverlapTag( Rect *rect, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%d\" ", getRectId(rect));
    fprintf(svg, "x=\"%f\" ", getRectX(rect));
    fprintf(svg, "y=\"%f\" ", getRectY(rect));
    fprintf(svg, "width=\"%f\" ", getRectWidth(rect));
    fprintf(svg, "height=\"%f\" ", getRectHeight(rect));
    fprintf(svg, "fill=\"none\" ");
    fprintf(svg, "stroke-width=\"3.0\" ");
    fprintf(svg, "stroke=\"red\" ");
    fprintf(svg, "stroke-dasharray=\"5,5\" ");
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<text ");
    fprintf(svg, "x=\"%f\" ", getRectX(rect)+5);
    fprintf(svg, "y=\"%f\" ", getRectY(rect)+15);
    fprintf(svg, "fill=\"red\"");
    fprintf(svg, ">sobrepoe</text>\n");
}

void writeQuadraTag( Quadra *q, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%s\" ", getQuadraCep(q));
    fprintf(svg, "x=\"%f\" ", getQuadraX(q));
    fprintf(svg, "y=\"%f\" ", getQuadraY(q));
    fprintf(svg, "width=\"%f\" ", getQuadraWidth(q));
    fprintf(svg, "height=\"%f\" ", getQuadraHeight(q));
    fprintf(svg, "fill=\"%s\" ", getQuadraFill(q));
    fprintf(svg, "stroke-width=\"%f\" ", 1.0);
    fprintf(svg, "stroke=\"%s\" ", getQuadraStroke(q));
    fprintf(svg, "/>\n");
}

void writePointTag( Point *p, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 5.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", 0.5);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeHidranteTag( Point *p, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "x=\"%f\" ", getPointX(p)-2.5);
    fprintf(svg, "y=\"%f\" ", getPointY(p)-5.0);
    fprintf(svg, "width=\"%f\" ", 5.0);
    fprintf(svg, "height=\"%f\" ", 10.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", 0.5);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeSemaforoTag( Point *p, FILE *svg ){
    double stroke, circleRadius, distCircleY;
    char *red, *yellow, *green;

    stroke = 0.5;
    circleRadius = 2.5;
    distCircleY = 5.5;

    if( strcmp( getPointFill(p), "rgb(153,153,153)" ) == 0 ){
        red = "red";
        yellow = "yellow";
        green = "green";
    }
    else{
        red = "white";
        yellow = "white";
        green = "white";
    }

    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "x=\"%f\" ", getPointX(p)-3.5);
    fprintf(svg, "y=\"%f\" ", getPointY(p)-9.0);
    fprintf(svg, "width=\"%f\" ", 7.0);
    fprintf(svg, "height=\"%f\" ", 18.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", yellow);
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p)-distCircleY);
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", red);
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p)+distCircleY);
    fprintf(svg, "r=\"%f\" ", circleRadius);
    fprintf(svg, "fill=\"%s\" ", green);
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}

void writeTorreTag( Point *p, FILE *svg ){
    double stroke;
    stroke = 0.5;

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 8.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 6.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");

    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%s\" ", getPointId(p));
    fprintf(svg, "cx=\"%f\" ", getPointX(p));
    fprintf(svg, "cy=\"%f\" ", getPointY(p));
    fprintf(svg, "r=\"%f\" ", 4.0);
    fprintf(svg, "fill=\"%s\" ", getPointFill(p));
    fprintf(svg, "stroke-width=\"%f\" ", stroke);
    fprintf(svg, "stroke=\"%s\" ", getPointStroke(p));
    fprintf(svg, "/>\n");
}
