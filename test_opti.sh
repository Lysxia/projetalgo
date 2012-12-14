#!/bin/bash

cd `dirname $0`

UP="true"

# Affichage du nom du processeur
echo -n "Cpu: " 
cat /proc/cpuinfo | grep -m 1 "model name" | sed 's/model name\t: //' 
# Affichage de la version
echo -n "Revision: " 
git rev-parse HEAD | cut -c1-10

tmp=0

while [ -f ./strassen$tmp ]
do
  tmp=$(($tmp+1))
done

cp strassen strassen$tmp

#for i in {100..1000..10} # Start - stop - increment
#do 
#    echo -n $i","
#    ./rand2 $i $i $i | ./strassen$tmp
#done


for i in {1100..2000..100} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen$tmp
done


for i in {2500..10000..500} # Start - stop - increment
do 
    echo -n $i","
    ./rand2 $i $i $i | ./strassen$tmp
done

if [ true ]
then

  for i in {11000..20000..1000}
  do
      echo -n $i","
      ./rand2 $i $i $i | ./strassen$tmp
  done

  for i in {25000..50000..5000}
  do
      echo -n $i","
      ./rand2 $i $i $i | ./strassen$tmp
  done
fi

rm -f strassen$tmp