#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

input_file=${SCRIPT_DIR}/random.txt
cmp_file=$SCRIPT_DIR/output.z
dcmp_file=${SCRIPT_DIR}/dcmp_random.txt

# generate a random file of 10MG
dd if=/dev/urandom of=$input_file bs=1M count=10

make wzip wunzip

./wzip $input_file > $cmp_file
./wunzip $cmp_file > $dcmp_file

diff $input_file $dcmp_file
rm $input_file $cmp_file $dcmp_file
