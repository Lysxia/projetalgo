#!/bin/bash
rm -f $(hostname).txt

i=0

while [ -f $(hostname)$i.txt ]
do
	i=$(($i+1))
done

./test_strassen.sh > $(hostname)$i.txt&
