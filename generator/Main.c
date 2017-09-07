#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ){
    int qtdX, qtdY, startX, startY, distX, distY, i, j;
    int id , x, y, width, height;
    char command;

    if( argc >= 2 ){
        command = *argv[1];
    }
    else{
        printf("Uso: %s {aq} qtdX qtdY startX startY width height distX distY\n", argv[0]);
        printf("Uso: %s {hst} qtdX qtdY startX startY distX distY\n", argv[0]);
        return 1;
    }

    if( (command == 'a' || command == 'q') && argc != 10 ){
        printf("Uso: %s %c qtdX qtdY startX startY width height distX distY\n", argv[0], command);
        return 1;
    }
    else if( (command == 'h' || command == 's' || command == 't') && argc != 8 ){
        printf("Uso: %s %c qtdX qtdY startX startY distX distY\n", argv[0], command);
        return 1;
    }
    else if( command != 'a' && command != 'q' && command != 'h' && command != 's' && command != 't' ){
        printf("Uso: %s {aq} qtdX qtdY startX startY width height distX distY\n", argv[0]);
        printf("Uso: %s {hst} qtdX qtdY startX startY distX distY\n", argv[0]);
        return 1;
    }

    qtdX = atoi(argv[2]);
    qtdY = atoi(argv[3]);
    startX = atoi(argv[4]);
    startY = atoi(argv[5]);

    if( command == 'q' ){
        width = atoi(argv[6]);
        height = atoi(argv[7]);
        distX = atoi(argv[8]);
        distY = atoi(argv[9]);

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
    else if( command == 'a' ){
        width = atoi(argv[6]);
        height = atoi(argv[7]);
        distX = atoi(argv[8]);
        distY = atoi(argv[9]);

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
                x = x + width+distX;
                id++;
            }
            y = y + height+distY;
        }
    }
    else{
        distX = atoi(argv[6]);
        distY = atoi(argv[7]);

        id = 1;
        y = startY;
        for( i = 0; i < qtdX; i++ ){
            x = startX;
            for( j = 0; j < qtdY; j++ ){
                printf("%c %d %d %c%d\n", command, x, y, command, id);
                x = x + width+distX;
                id++;
            }
            y = y + height+distY;
        }
    }

    printf("#\n");

    return 0;
}
