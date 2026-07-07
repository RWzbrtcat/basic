#!/bin/bash

var1=100
# var1 等于 0 时退出循环
until [ $var1 -eq 0 ]
do
	echo $var1
	var1=$[ $var1 - 25 ]
done
