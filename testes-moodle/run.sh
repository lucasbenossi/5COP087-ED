#!/bin/bash

export SIGUEL="../t6.1/siguel"
export VALGRIND="valgrind --error-exitcode=1 --leak-check=full"
PARALLEL="parallel --bar"

siguel(){
	basedir="$1"
	cidade="$2"
	qry="$3"

	out="out/$basedir-$qry"
	dump="$out/dump/"
	valgrind="$out/valgrind.txt"

	if [[ -f "$basedir/$cidade.ec" ]]; then arg_ec="-ec $cidade.ec"; else arg_ec=""; fi
	if [[ -f "$basedir/$cidade.pm" ]]; then arg_pm="-pm $cidade.pm"; else arg_pm=""; fi
	if [[ -f "$basedir/$cidade.tm" ]]; then arg_tm="-tm $cidade.tm"; else arg_tm=""; fi
	if [[ -f "$basedir/$cidade.via" ]]; then arg_via="-v $cidade.via"; else arg_via=""; fi
	if [[ -f "$basedir/$cidade/$qry.qry" ]]; then arg_qry="-q $cidade/$qry.qry"; else arg_qry=""; fi

	mkdir -p $out $dump

	if ! { $VALGRIND $SIGUEL -e $basedir -o $out -od $dump -f $cidade.geo $arg_ec $arg_pm $arg_tm $arg_via $arg_qry 1>$valgrind 2>&1; }; then
		cat $valgrind
	fi
}

export -f siguel

while [[ $1 ]]; do
	if ! [[ -x $SIGUEL ]]; then
		echo "$SIGUEL não existe ou não é executável"
		exit 1
	fi

	BASEDIR="${1%/}"
	CIDADE="$(basename $BASEDIR)"

	$PARALLEL "siguel $BASEDIR $CIDADE {1/.}" ::: $BASEDIR/$CIDADE/*.qry
	shift
done
