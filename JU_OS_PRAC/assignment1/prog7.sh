#!/bin/bash

# Store PATH variable directories separated by ':'
IFS=':' read -ra dirs <<< "$PATH"

echo "Directories in PATH:"
echo "---------------------"

for dir in "${dirs[@]}"
do
    echo "Directory: $dir"

    ls -ld "$dir"

    echo "---------------------"
done