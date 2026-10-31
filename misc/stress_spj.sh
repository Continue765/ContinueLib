#!/bin/bash
# bash stress_spj.sh ./sol ./spj ./gen
set -e
for ((i = 1; ; i++)); do
    "$3" > in.txt
    "$1" < in.txt > out.txt
    if ! "$2" in.txt out.txt; then
        printf '\nWA %d\n' "$i"
        break
    fi
    printf '\rAC %d' "$i"
done