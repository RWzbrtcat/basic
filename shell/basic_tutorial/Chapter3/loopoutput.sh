#!/bin/bash

for file in /home/*
do
	if [ -d "$file" ]
	then 
		echo "$file is a directory"
	else
		echo "$file si a file"	
	fi
done > output.txt
