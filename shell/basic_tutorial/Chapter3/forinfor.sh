#!/bin/bash

for (( a = 1; a <= 3; a++ ))
do
	echo "外层循环第 " $a " 轮"
	for (( b = 1; b <= 3; b++ ))
	do
		echo "    内层循环第 " $b " 轮"
	done
done
