#!/bin/bash

echo "#lang format" > tmp.rkt
cat $1 >> tmp.rkt

echo "Running formatter on $1"

racket tmp.rkt > formatted.h

if [[ $? -ne 0 ]]; then
    echo "Running formatter on $1 failed!"
    exit
fi

g++-13 -E -dD -P -fpreprocessed $1 | tr -d '[:space:]' > orig.txt
g++-13 -E -dD -P -fpreprocessed formatted.h | tr -d '[:space:]' > preproc.txt

diff -w orig.txt preproc.txt

if [[ $? -ne 0 ]]; then
    echo "Formatting changed diff for $1!"
    exit
fi

cp formatted.h $1

rm tmp.rkt formatted.h orig.txt preproc.txt

echo "Successfully formatted $1!"