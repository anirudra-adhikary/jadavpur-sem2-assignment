#!/bin/bash

# Check whether a number is provided
if [ $# -eq 0 ]
then
    echo "Usage: $0 <number>"
    exit 1
fi

num=$1

echo "Multiplication Table for $num"
echo "-----------------------------"

for i in {1..10}
do
    result=$((num * i))
    echo "$num x $i = $result"
done