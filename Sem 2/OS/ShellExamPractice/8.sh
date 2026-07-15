#!/bin/bash

cat df.fake | tail -n +2 | while read -r line; do
    size=`echo $line | awk '{print $2}' | sed -E 's/M//g'`
    usage=`echo $line | awk '{print $5}' | sed -E 's/%//g'`
    name=`echo $line | awk '{print $6}'`
    if [ $size -lt 1000 ] || [ $usage -gt 80 ]; then
        echo $name
    fi
done
