#!/bin/bash
CC='clang++'

WARNINGS='-Wall -Werror'
STANDARD='-std=c++14 -fsanitize=address'
FLAGS=' -g '
FLAGS+=$WARNINGS
FLAGS+=' '
FLAGS+=$STANDARD
echo flags: $FLAGS
echo

filename=$1
$CC $FLAGS $filename.cpp -c -o $filename.o
$CC $FLAGS $filename.o -o $filename
rm *.o
read -p 'OK?' status
if (( ${#status}==0 ))
then
    clear
    chmod +x $filename
    ./$filename
fi
