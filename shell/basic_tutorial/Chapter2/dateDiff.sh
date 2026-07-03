#!/bin/bash

date1="Jan 9, 2024"
date2="May 4, 2025"

time1=$(date -d "$date1" +%s)
time2=$(date -d "$date2" +%s)

diff=$(expr $time2 - $time1)
secondsinday=$[24 * 60 * 60]
days=$[$diff / $secondsinday]

echo "日期相差: " $days "天"
