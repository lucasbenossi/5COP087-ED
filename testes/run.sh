#!/bin/bash

export SIGUEL="../t5.5/siguel"
export VALGRIND="valgrind --error-exitcode=1 --leak-check=full"
PARALLEL="parallel --bar"

if [[ $3 == "n" ]]; then {
	VALGRIND=""
} fi

siguel(){
	cidade="$1"
	qry="$2"

	out="out"
	dump="dump"
	error="error"
	error_file="$error/$cidade.txt"

	mkdir -p $out $dump $error

	if ! { $VALGRIND $SIGUEL -e $cidade -f $cidade.geo -ec $cidade.ec -pm $cidade.pm -tm $cidade.tm -q $qry.qry -o $out -od $dump 1>$error_file 2>&1; } then {
		cat $error_file
	} fi
}

dot_()(
	cd dump
	$PARALLEL "dot -Tpdf {} -o {.}.pdf; rm {}" ::: *.dot
)

export -f siguel dot_

if [[ $1 ]]; then {
	if [[ $2 ]]; then {
		siguel $1 $2
	} else {
		siguel $1 $1
	} fi
	dot_
} fi
