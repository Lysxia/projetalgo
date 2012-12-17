#!/bin/bash
# faire un ./test_print.sh | grep "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("

for i in {3..100} 
do
    for j in {1..100} 
    do
        for k in {1..100} 
        do
            ./demo2 $i $j $k
        done
    done
done
