#!/bin/bash

# echo "#lang format" > tmp.rkt
# cat $1 >> tmp.rkt

echo "Running formatter on $1"

# racket /Users/seba/cp/format/format/run-direct.rkt $1 > formatted.h
# /Users/seba/cp/format/run-direct $1 > formatted.h

formatter="racket /Users/seba/cp/format/format/run-direct.rkt"

if [ -f ./run-formatter ]; then
    formatter="./run-formatter"
fi

$formatter $1 > formatted.h

if [[ $? -ne 0 ]]; then
    echo "Running formatter on $1 failed!"
    exit
fi

g++-13 -E -dD -P -fpreprocessed $1 2> /dev/null | tr -d '[:space:]' > orig.txt 
g++-13 -E -dD -P -fpreprocessed formatted.h 2> /dev/null | tr -d '[:space:]' > preproc.txt 
diff -w orig.txt preproc.txt

if [[ $? -ne 0 ]]; then
    echo "Formatting changed diff for $1!"
    exit
fi

cp formatted.h $1

rm formatted.h orig.txt preproc.txt

echo "Successfully formatted $1!"