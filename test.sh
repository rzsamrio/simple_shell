#!/bin/bash

i=0

echo -e "Task 1 Check\n"
while [ $i -le 6 ]
do
	echo $((i + 2)) :
   	./checker.bash ./a.out ./task1/$i
	echo -e '\n'
	((i++))
done
