#!/bin/bash

testuser=NoSuchUser

if grep $testuser /etc/passwd
then
	echo "用户$testuser目录下的文件有:"
	ls /home/$testuser/*
	echo
else
	echo "用户$testuser不存在该系统"
	echo
fi
