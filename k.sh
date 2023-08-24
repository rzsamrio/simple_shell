#!/bin/bash

i=11

while [ $i -le 20 ]
do
	echo $((i + 2)) : 
   	./checker.bash ./a.out $i
	echo -e '\n'
	((i++))
done
