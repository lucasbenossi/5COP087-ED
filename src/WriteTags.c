#include <stdio.h>
#include "Rect.h"
#include "Circle.h"

void writeRectTag( Rect *rect, FILE *svg ){
    fprintf(svg, "\t<rect ");
    fprintf(svg, "id=\"%d\" ", getRectId(rect));
    fprintf(svg, "x=\"%f\" ", getRectX(rect));
    fprintf(svg, "y=\"%f\" ", getRectY(rect));
    fprintf(svg, "width=\"%f\" ", getRectWidth(rect));
    fprintf(svg, "height=\"%f\" ", getRectHeight(rect));
    fprintf(svg, "fill=\"%s\" ", getRectFill(rect));
    fprintf(svg, "stroke-width=\"1.0\" ");
    fprintf(svg, "stroke=\"black\" ");
    fprintf(svg, "/>\n");
}

void writeCircleTag( Circle *circle, FILE *svg ){
    fprintf(svg, "\t<circle ");
    fprintf(svg, "id=\"%d\" ", getCircleId(circle));
    fprintf(svg, "cx=\"%f\" ", getCircleX(circle));
    fprintf(svg, "cy=\"%f\" ", getCircleY(circle));
    fprintf(svg, "r=\"%f\" ", getCircleRadius(circle));
    fprintf(svg, "fill=\"%s\" ", getCircleFill(circle));
    fprintf(svg, "stroke-width=\"1.0\" ");
    fprintf(svg, "stroke=\"black\" ");
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
