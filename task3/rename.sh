#!/bin/bash

i=23

while [ $i -le 31 ]
do
	mv $i $((i-2))
	((i++))
done
