#/!bin/bash

var1=$(echo "scale=4;v1=5;v2=6;v1/v2" | bc)
echo $var1
