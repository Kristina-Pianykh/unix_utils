#!/usr/bin/env bash

input_file=random.txt
cmp_file=output.z
dcmp_file=dcmp_$input_file

# generate a random file of 10MG
dd if=/dev/urandom of=$input_file bs=1M count=10

make wzip wunzip

./wzip $input_file > $cmp_file
./wunzip $cmp_file > $dcmp_file

diff $input_file $dcmp_file
rm $input_file $cmp_file $dcmp_file
