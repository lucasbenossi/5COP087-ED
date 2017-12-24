#!/bin/bash

for i in t04-bsc-000 t04-bsc-001; do
	parallel --bar "valgrind ../../t5.5/siguel -f $i.geo -q {} -o out -r 30 -t" ::: $i/*.qry
done

parallel --bar "../../t5.5/siguel -f t04-bsc-002.geo -q {} -o out -r 30 -t" ::: t04-bsc-002/*.qry
