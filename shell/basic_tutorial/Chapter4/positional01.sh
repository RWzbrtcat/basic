#!/bin/bash

var=1
for (( num = 1; num <= $1; num++ ))
do
	var=$[ $var * $num ]
done
echo "乘积为: " $var
exit
