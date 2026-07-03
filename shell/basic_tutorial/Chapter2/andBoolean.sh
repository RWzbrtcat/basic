#!/bin/bash

filename="test"
if [ -d $HOME ] && [ -w $HOME/$filename ]
then
	echo "文件存在并且可写"
else
	echo "文件不可写"
fi
