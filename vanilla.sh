#!/bin/bash

cd `dirname $0`

make strassen1

i=$((RANDOM%50000))
j=$((RANDOM%50000))
k=$((RANDOM%50000))


echo $i,$j,$k,\
`./rand2 $i $j $k| ./strassen1` >> data$(hostname)rand.txt
