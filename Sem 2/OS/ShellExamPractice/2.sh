#!/bin/bash

D=$1
count=0

for file in `find $D -type f -name "*.c"`; do
    lines=`cat $file | wc -l`
    if [ $lines -gt 500 ] && [ $count -lt 2 ]; then
        echo $file
        count+=1
    fi
done
