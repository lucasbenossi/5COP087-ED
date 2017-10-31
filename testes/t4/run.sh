#!/bin/bash

for i in t04-bsc-000 t04-bsc-001 t04-bsc-002; do
	parallel --bar "../../t4\ \(5\)/siguel -f $i.geo -q {} -o ../out/ -r 30 -t \"rgba(0,0,255,0.3)\" -d q" ::: $i/*.qry
done
