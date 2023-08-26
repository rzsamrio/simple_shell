#!/bin/bash

i=0

echo -e "Task 5 Check\n"
while [ $i -le 2 ] 
do
	echo $((i + 2)) :
   	./checker.bash ./a.out ./task5/$i
	echo -e '\n'
	((i++))
done

i=0
echo -e "Task 5 Memory Check\n"
while [ $i -le 2 ]
do
	echo $((i + 2)) :
   	./checker.bash --valgrind ./a.out ./task5/$i
	echo -e '\n'
	((i++))
done
