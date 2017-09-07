#!/bin/bash

INDIR="/home/lucas/Files/Desktop/Uel/2017/Estrutura de Dados/Trabalho03/testes/t"
OUTDIR="/home/lucas/Files/Desktop/Uel/2017/Estrutura de Dados/Trabalho03/testes/out"

for i in t03-bsc-000 t03-bsc-001 t03-bsc-002; do
	for j in $(ls "/home/lucas/Files/Desktop/Uel/2017/Estrutura de Dados/Trabalho03/testes/t/$i/"); do
		./siguel -e "$INDIR" -f $i.geo -q $i/$j -o "$OUTDIR" -acc
	done
done
