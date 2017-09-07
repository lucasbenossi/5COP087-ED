#!/bin/bash

for i in d* cdq-*; do valgrind ../../t3\ 0.84/siguel -f t03-bsc-001.geo -q $i -e "/home/lucas/Files/Desktop/Uel/2017/Estrutura de Dados/Trabalho03/testes/t3/" -o ../out/ -acc; done
