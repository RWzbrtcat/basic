#!/bin/bash

for (( i = 1; i <= 3; ++i ))
do
	echo $i
	for (( j = 1; j <= 3; ++j ))
	do
		echo "    " $j
		if [ $j -ge 2 ]
		then
			break 2
		fi
	done
done
