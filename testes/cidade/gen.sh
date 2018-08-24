#!/bin/bash

NAME=cidade
QTDI=10
QTDJ=10
WIDTH=30
HEIGHT=30
DIST=10
RADIUS=30
CODT=7
ESTAB=16
PESSOAS=32

# ./gen name qtdX qtdY width height dist radius codt estab pessoas
valgrind ../../generator/gen $NAME $QTDI $QTDJ $WIDTH $HEIGHT $DIST $RADIUS $CODT $ESTAB $PESSOAS
