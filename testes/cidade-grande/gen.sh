#!/bin/bash

NAME=cidade-grande
QTDX=30
QTDY=30
WIDTH=30
HEIGHT=30
DIST=10
RADIUS=30
CODT=7
ESTAB=16
PESSOAS=32

# ./gen name qtdX qtdY width height dist radius codt estab pessoas
valgrind ../../generator/gen $NAME $QTDX $QTDY $WIDTH $HEIGHT $DIST $RADIUS $CODT $ESTAB $PESSOAS
