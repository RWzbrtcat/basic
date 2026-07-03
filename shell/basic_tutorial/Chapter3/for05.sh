#!/bin/bash

IFS=$'/'
# 逐级输出工作目录
for word in $(pwd); do
	echo $word
done
