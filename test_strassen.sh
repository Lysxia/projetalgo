#!/bin/bash

cd `dirname $0`

UP="true"

# Affichage du nom du processeur
echo -n "Cpu: " 
cat /proc/cpuinfo | grep -m 1 "model name" | sed 's/model name\t: //' 
# Affichage de la version
echo -n "Revision: " 
git rev-parse HEAD | cut -c1-10

tmp=3

while [ -f ./strassen$tmp ]
do
  tmp=$(($tmp+1))
done

cp strassen1 strassen$tmp

for i in {100..1000..100} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen$tmp
done


for i in {2000..3000..500} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen$tmp
done


#for i in {2500..10000..500} # Start - stop - increment
#do 
#    echo -n $i","
#    ./rand2 $i $i $i | ./strassen$tmp
#done

rm -f strassen$tmp
