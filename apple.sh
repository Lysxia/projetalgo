#!/bin/bash

cd `dirname $0`

make strassen

i=0

while [ -f opti$(hostname)$i.txt ]
do
	i=$(($i+1))
done

./test_opti.sh > opti$(hostname)$i.txt&
