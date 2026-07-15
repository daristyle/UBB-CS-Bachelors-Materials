#!/bin/bash

D=$1

for file in `find $D -type f -name "*.log"`; do
    sort "$file" > temp
    mv temp "$file"
    rm -rf temp
done
