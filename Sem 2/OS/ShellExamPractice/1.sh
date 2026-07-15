#!/bin/bash


cat who.fake | while read -r line; do
    user=`echo $line | awk '{print $1}'`
    cnt=`grep -E -c  "^$user" ps.fake`
    echo $user $cnt
done
