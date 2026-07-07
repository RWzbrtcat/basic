#!/bin/bash

var1=10
while [ $var1 -gt 0 ]
do
	echo $var1
	var1=$[ $var1 - 1 ]
	if [ $var1 -lt 5 ]
	then
		break
	fi
done
