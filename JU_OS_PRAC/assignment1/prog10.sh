#!/bin/bash

echo "Enter file name:"
read file

if [ -f "$file" ]
then
    lines=$(wc -l < "$file")
    echo "Number of lines in $file is $((lines + 1))"
else
    echo "File does not exist"
fi
