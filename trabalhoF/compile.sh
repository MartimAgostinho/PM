#!/bin/sh

file=${1%.*}
gcc -o $file $file.c -Wall && echo Compiled! && read -p "continue?(y/n): " confirm && [[ $confirm == [y] ]] && ./$file
