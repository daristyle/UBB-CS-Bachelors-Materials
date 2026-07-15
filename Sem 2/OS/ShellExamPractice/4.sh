#!/bin/bash

for file in `find dir`; do
    if [ -L $file ] && [ ! -e $file ]; then
        echo $file
    fi
done
