#!/bin/bash

dir=${1:-.}

total_bytes=$(find "$dir" -type f -exec ls -l {} \; | awk '{sum += $5} END {print sum}')

echo "Total bytes used by files: $total_bytes"

today_bytes=$(find "$dir" -type f -daystart -mtime 0 -exec ls -l {} \; | awk '{sum += $5} END {print sum}')

echo "Total size of files created/modified today: $today_bytes"