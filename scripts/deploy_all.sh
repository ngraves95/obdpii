#!/bin/bash

for f in `ls . -r`; do
    if [ "./$f" != "$0" ]
    then
	echo Running $f
	./$f
    fi
done
