#!/bin/bash

export SIGUEL="../t6.1/siguel"
export VALGRIND="valgrind --error-exitcode=1 --leak-check=full"
PARALLEL="parallel --bar"

if [[ $3 == "n" ]]; then
	VALGRIND=""
fi

siguel() {
	cidade="$1"
	qry="$2"

	if [[ $qry == "nao" ]]; then
		qry=""
	fi

	out="out"
	dump="$out/dump"
	valgrind="$out/valgrind.txt"

	if [[ -f "$cidade/$cidade.ec" ]]; then arg_ec="-ec $cidade.ec"; else arg_ec=""; fi
	if [[ -f "$cidade/$cidade.pm" ]]; then arg_pm="-pm $cidade.pm"; else arg_pm=""; fi
	if [[ -f "$cidade/$cidade.tm" ]]; then arg_tm="-tm $cidade.tm"; else arg_tm=""; fi
	if [[ -f "$cidade/$cidade.via" ]]; then arg_via="-v $cidade.via"; else arg_via=""; fi
	if [[ -f "$cidade/$qry.qry" ]]; then arg_qry="-q $qry.qry"; else arg_qry=""; fi

	mkdir -p $out $dump $error

	if ! { $VALGRIND $SIGUEL -e $cidade -f $cidade.geo $arg_ec $arg_pm $arg_tm $arg_via $arg_qry -o $out -od $dump 1>$valgrind 2>&1; } then
		cat $valgrind
	fi
}

dot_() {
	if { echo $1 | grep "Graph" &> /dev/null; }; then
		neato -n -Tpdf $1 -o $(basename $1 .dot).pdf
	else
		dot -Tpdf $1 -o $(basename $1 .dot).pdf
	fi
}
export -f dot_

parallel_dot()(
	cd out/dump
	$PARALLEL "dot_ {}" ::: *.dot
)

if [[ $1 ]]; then
	if ! [[ -x $SIGUEL ]]; then
		echo "$SIGUEL não existe ou não é executável"
		exit 1
	fi

	if [[ $2 ]]; then
		siguel $1 $2
	else
		siguel $1 $1
	fi

	parallel_dot
else
	echo "Nenhuma cidade informada"
fi
