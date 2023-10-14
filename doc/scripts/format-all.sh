#!/usr/bin/env bash

find $1 -type f | grep -E ".*\.(cpp|h)$" |
	xargs -I '{}' zsh format.sh {}

# echo "Formatted:"
# find $1 -type f | grep -E ".*\.(cpp|h)$"
