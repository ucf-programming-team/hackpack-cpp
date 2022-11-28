#!/usr/bin/env bash

find $1 -type f | grep -E ".*\.(cpp|h)$" |
	xargs clang-format-15 -i -style=file

echo "Formatted:"
find $1 -type f | grep -E ".*\.(cpp|h)$"
