#!/bin/bash

list="Hello "
# 可追加
list=$list"World"
for var in $list; do
	echo $var
done
