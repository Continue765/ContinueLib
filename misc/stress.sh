#!/bin/bash
# bash stress.sh ./sol ./brute ./gen
set -e
for ((i = 1; ; i++)); do
    "$3" > in.txt
    "$1" < in.txt > out.txt
    "$2" < in.txt > ans.txt
    if ! diff -w out.txt ans.txt > diff.txt; then
        printf '\nWA %d\n' "$i"
        break
    fi
    printf '\rAC %d' "$i"
done