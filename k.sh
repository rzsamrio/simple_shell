#!/bin/bash

i=0

while [ $i -le 6 ]
do
	echo $((i + 2)) : 
   	./checker.bash ./a.out $i
	echo -e '\n'
	((i++))
done
