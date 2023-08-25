#!/bin/bash

i=0

echo -e "Task 1 Check\n"
while [ $i -le 29 ]
do
	echo $((i + 2)) :
   	./checker.bash ./a.out ./task1/$i
	echo -e '\n'
	((i++))
done

i=0
echo -e "Task 1 Memory Check\n"
while [ $i -le 29 ]
do
	echo $((i + 2)) :
   	./checker.bash --valgrind ./a.out ./task1/$i
	echo -e '\n'
	((i++))
done
