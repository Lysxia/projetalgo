#!/bin/bash

cd `dirname $0`

make strassen

i=$((RANDOM%5000))
j=$((RANDOM%5000))
k=$((RANDOM%5000))


echo $i,$j,$k,\
`./rand2 $i $j $k| ./strassen` >> data$(hostname)rand.txt&
