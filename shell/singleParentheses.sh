#!/bin/bash

echo $BASH_SUBSHELL

if (echo $BASH_SUBSHELL)
then
	echo "子shell命令执行成功"
else
	echo "子shell命令执行失败"
fi
