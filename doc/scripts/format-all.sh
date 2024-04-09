#!/usr/bin/env bash

echo "Compiling formatter..."
raco exe -o run-formatter ++lib format /Users/seba/cp/format/format/run-direct.rkt

find $1 -type f | grep -E ".*\.(cpp|h)$" |
	xargs -I '{}' zsh format.sh {}

# echo "Formatted:"
# find $1 -type f | grep -E ".*\.(cpp|h)$"
