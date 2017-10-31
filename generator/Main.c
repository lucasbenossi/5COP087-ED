#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ){
    int qtdX, qtdY, startX, startY, distX, distY, width, height, radius;
    int i, j, id, x, y;
    char command;

    if( argc >= 2 ){
        command = *argv[1];
    }
    else{
        /*           0  1    2    3    4      5      6     7     8     9      10                   */
        fprintf(stderr, "Uso: %s a    qtdX qtdY startX startY distX distY width height radius\n", argv[0]);
        fprintf(stderr, "Uso: %s q    qtdX qtdY startX startY distX distY width height\n", argv[0]);
        fprintf(stderr, "Uso: %s {hs} qtdX qtdY startX startY distX distY\n", argv[0]);
        fprintf(stderr, "Uso: %s t    qtdX qtdY startX startY distX distY radius\n", argv[0]);
        return 1;
    }

    qtdX = atoi(argv[2]);
    qtdY = atoi(argv[3]);
    startX = atoi(argv[4]);
    startY = atoi(argv[5]);
    distX = atoi(argv[6]);
    distY = atoi(argv[7]);

    if( command == 'a' ){
        width = atoi(argv[8]);
        height = atoi(argv[9]);
        radius = atoi(argv[10]);

        id = 1;
        y = startY;
        for( i = 0; i < qtdX; i++ ){
            x = startX;
            for( j = 0; j < qtdY; j++ ){
                printf("q %d %d %d %d cep%d\n", x, y, width, height, id);
                printf("h %d %d h%d\n", x+width, y+height/2, id);
                printf("h %d %d h%d\n", x+width/2, y+height, id);
                printf("s %d %d s%d\n", x+width+distX/2, y+height+distY/2, id);
                printf("t %d %d t%d\n", x+width/2, y+height/2, id);
                printf("tI t%d %d\n", id, radius);
                x = x + width+distX;
                id++;
            }
            y = y + height+distY;
        }
    }
    else if( command == 'q' ){
        width = atoi(argv[8]);
        height = atoi(argv[9]);

        id = 1;
        y = startY;
        for( i = 0; i < qtdX; i++ ){
            x = startX;
            for( j = 0; j < qtdY; j++ ){
                printf("q %d %d %d %d cep%d\n", x, y, width, height, id);
                x = x + width+distX;
                id++;
            }
            y = y + height+distY;
        }
    }
    else if( command == 't' ){
        radius = atoi(argv[8]);

        id = 1;
        y = startY;
        for( i = 0; i < qtdX; i++ ){
            x = startX;
            for( j = 0; j < qtdY; j++ ){
                printf("t %d %d t%d\n", x, y, id);
                printf("tI t%d %d\n", id, radius);
                x = x + distX;
                id++;
            }
            y = y + distY;
        }
    }
    else{
        id = 1;
        y = startY;
        for( i = 0; i < qtdX; i++ ){
            x = startX;
            for( j = 0; j < qtdY; j++ ){
                printf("%c %d %d %c%d\n", command, x, y, command, id);
                x = x + distX;
                id++;
            }
            y = y + distY;
        }
    }

    printf("#\n");

    return 0;
}
