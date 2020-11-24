#!/usr/bin/env bash
find . -type f |
  grep -E ".*\.(cpp|h)$" |
  xargs -n1 clang-format-10 -style=file -output-replacements-xml |
  grep "<replacement " >/dev/null
if [ $? -ne 1 ]; then
    echo "Commit did not match clang-format"
    echo "Please run 'make format' and recommit"
    exit 1
fi
