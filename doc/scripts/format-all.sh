#!/usr/bin/env bash

find . -type f | grep -E ".*\.(cpp|h)$" |
	xargs clang-format -i --style=file

echo "Formatted:"
find . -type f | grep -E ".*\.(cpp|h)$"
