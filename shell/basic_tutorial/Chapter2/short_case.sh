#!/bin/bash

case $USER in
rich | christine)
	echo "Welcome $USER";;
barbara | tim)
	echo "Hi, there, $USER";;
*)
	echo "Sorry";;
esac
