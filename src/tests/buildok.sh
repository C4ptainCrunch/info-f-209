#!/bin/sh

if [ -f $1/build.ok ]
then
    printf "%-10s   \e[1;32m[ OK ]\e[0m\n" $1
else
    printf "%-10s   \e[1;31m[FAIL]\e[0m\n" $1
fi