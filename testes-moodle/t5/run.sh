#!/bin/bash

export SIGUEL="../../t5.5/siguel"
export VALGRIND="valgrind --error-exitcode=1 --leak-check=full"
PARALLEL="parallel --bar"

siguel(){
	cidade="$1"
	qry="$2"

	out="out/$cidade"
	error="error"
	dump="dump/$cidade-$qry"
	error_file="$error/$cidade-$qry.txt"

	mkdir -p $out $error $dump

	if ! { $VALGRIND $SIGUEL -e $cidade -f $cidade.geo -ec $cidade.ec -pm $cidade.pm -tm $cidade.tm -q $cidade/$qry.qry -o $out -od $dump 1>$error_file 2>&1; }; then
		cat $error_file
	fi
}

export -f siguel

while [[ $1 ]]; do {
	$PARALLEL "siguel $1 {1/.}" ::: $1/$1/*.qry
	shift
} done
