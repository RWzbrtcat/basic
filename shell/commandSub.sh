#!/bin/bash

# command substitution

# 简单示例
time=$(date)
echo "The date and time are: " $time

# 获取当前日期并用其来生成唯一文件名

today=$(date +%y%m%d) # 将日期显示为两位数的年月日组合
# 将 /usr/bin 目录下的文件列表复制到日志文件中
ls /usr/bin -al > log.$today

