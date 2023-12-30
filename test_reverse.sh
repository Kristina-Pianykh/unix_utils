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
			echo "test_1 failed"
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
			echo "test_2 failed"
			echo "./reverse $input_file and ./reverse $input_file $out_file differ"
			rm $input_file $redirecred_output $output_file
			exit 1
	fi
}


test_3() {
	# test if ./reverse $input_file | ./reverse 
	# produces the same result as the original file $input_file
	make $prg_name	
	# Generate lines with random content
	for i in {1..10}; do
		# Use head -c to limit the length of each line
		head -c $((RANDOM % 20 + 1)) /dev/urandom | tr -dc '[:print:]' >> "$input_file"
		echo >> "$input_file"  # Add a newline after each line
	done

	./reverse $input_file | ./reverse > $redirecred_output
	diff -q $redirecred_output $input_file

	if [ $? -ne 0 ]; then
			echo "test_3 failed"
			echo "Double reverse of $input_file differ from the original file"
			rm $input_file $redirecred_output
			exit 1
	fi
}


make $prg_name
test_1
test_2
rm $input_file $redirecred_output $output_file
test_3
rm $input_file $redirecred_output

if [ $? -eq 0 ]; then
	echo ""
	echo "================================All tests passed================================"
	echo ""
fi

make clean
