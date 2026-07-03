#!/bin/bash

val1=10

if (( $val1 ** 2 > 90))
then
	((val2 = $val1 ** 2))
	echo "val1 的平方为: " $val2
	echo "大于 90"
fi
