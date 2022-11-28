#!/usr/bin/env bash
find . -type f |
  grep -E ".*\.(cpp|h)$" |
  xargs -n1 clang-format-15 -style=file -output-replacements-xml |
  grep "<replacement " >/dev/null
if [ $? -ne 1 ]; then
    echo "Commit did not match clang-format-15"
    echo "Please run 'make format' and recommit"
    exit 1
fi
