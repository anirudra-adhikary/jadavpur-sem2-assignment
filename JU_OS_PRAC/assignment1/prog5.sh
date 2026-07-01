#!/bin/bash

dir=${1:-.}

file_count=$(find "$dir" -type f | wc -l)
dir_count=$(find "$dir" -type d | wc -l)

echo "Total Files: $file_count"
echo "Total Directories: $dir_count"

echo
echo "Files:"
find "$dir" -type f

echo
echo "Directories:"
find "$dir" -type d

echo
echo "Files created/modified in the past 7 days:"
find "$dir" -type f -mtime -7

echo
echo "Total size of files created/modified in past week:"
find "$dir" -type f -mtime -7 -exec du -ch {} + | tail -1