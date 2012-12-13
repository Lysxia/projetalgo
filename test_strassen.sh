#!/bin/bash

# Affichage du nom du processeur
echo -n "Cpu: " 
cat /proc/cpuinfo | grep -m 1 "model name" | sed 's/model name\t: //' 
# Affichage de la version
echo -n "Revision: " 
git rev-parse HEAD | cut -c1-10

for i in {100..1000..1} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen
done


for i in {1000..2000..100} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen
done


for i in {2000..10000..1000} # Start - stop - increment
do 
    echo $i","
    ./rand2 $i $i $i | ./strassen
done
