#!/bin/bash

cd `dirname $0`

for i in {0..1}
do
  ./orange.sh&
  ./raspberry.sh&
done
