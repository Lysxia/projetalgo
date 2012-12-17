#!/bin/bash

cd `dirname $0`

make strassen1

i=0

while [ -f data$(hostname)$i.txt ]
do
	i=$(($i+1))
done

./test_strassen.sh > data$(hostname)$i.txt&
