#!/bin/bash

files=0
users=0
others=0

while true; do
    read -r X
    if [ $X == "stop" ]; then
        break
    fi
    found=0
    while read -r line; do
        user=`echo $line | grep -E -o '^[^:]*'`
        if [ $user == $X ]; then
            found=1
            dir=`echo $line | sed -E 's/:/ /g' | awk '{print$6}'`
            cnt=`find $dir -name '*.txt' -type f | wc -l`
            echo $cnt
        fi
    done < /etc/passwd
    if [ $found -eq 1 ]; then
        users=`expr $users + 1`
    elif [ -f $X ]; then
        files=`expr $files + 1`
        grep -E -v -i "^.*ana.*$" $X  > temp
        mv temp $X
    else
        others=`expr $others + 1`
    fi
done

((total = files + users + others))
if [ $total -gt 0 ]; then
    ((files = files * 100 / total))
    ((users = users * 100 / total))
    ((others = others * 100 / total))
    echo FILES: $files% 
    echo USERS: $users%
    echo OTHER: $others%
else
    echo NOTHING WAS READ
fi
