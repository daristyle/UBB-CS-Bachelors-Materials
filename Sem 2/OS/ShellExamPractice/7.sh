#!/bin/bash

list=""
for line in `cat $1`; do
    if [ $list != "" ]; then
        list="$list,"
    fi
    list="$list$line@scs.ubbcluj.ro"
done
echo $list
