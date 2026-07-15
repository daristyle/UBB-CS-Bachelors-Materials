#!/bin/bash

while true; do
    ps | tail -n +2 | while read -r line; do
        proc=`echo $line | awk '{print $4}'`
        pid=`echo $line | awk '{print $1}'`
        for arg in $@; do
            if [ $arg == $proc ]; then
                kill $pid
                echo Killed $proc with id $pid
            fi
        done
    done

    sleep 1
done
