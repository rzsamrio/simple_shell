#!/bin/bash

i=0

echo -e "Task 3 Check\n"
while [ $i -le 29 ]
do
	echo $((i + 2)) :
   	./checker.bash ./a.out ./task3/$i
	echo -e '\n'
	((i++))
done
