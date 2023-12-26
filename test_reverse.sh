#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

prg_name=reverse
input_file=${SCRIPT_DIR}/random.txt
redirecred_output=$SCRIPT_DIR/out_stdout.txt
output_file=${SCRIPT_DIR}/output_file.txt


test_1() {
	# test if too many arguments are passed
	./reverse $input_file $input_file $input_file 2> /dev/null

	if [ $? -eq 0 ]; then
			echo "./reverse $input_file $input_file $input_file should fail"
			echo "too many arguments passed"
			exit 1
	fi
}

test_2() {
	# test if ./reverse $input_file and ./reverse $input_file $out_file produce the same result

	# generate a random file of 10MG
	dd if=/dev/urandom of=$input_file bs=1M count=10

	./reverse $input_file > $redirecred_output
	./reverse $input_file $output_file
	diff $redirecred_output $output_file

	if [ $? -ne 0 ]; then
			echo "./reverse $input_file and ./reverse $input_file $out_file differ"
			exit 1
	fi
}

make $prg_name
test_1
test_2

if [ $? -eq 0 ]; then
	echo ""
	echo "================================All tests passed================================"
	echo ""
fi

make clean
rm $input_file $redirecred_output $output_file
