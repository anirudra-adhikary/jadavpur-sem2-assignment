#!/bin/bash

# Input
read -p "Enter a 4-digit number: " num

if [[ $num =~ ^-?[0-9]{4}$ ]]; then

    sign=""

    if [[ $num == -* ]]; then
        sign="-"
        num=${num#-}   # Rem
    fi

    d1=$((num / 1000))
    d2=$(((num / 100) % 10))
    d3=$(((num / 10) % 10))
    d4=$((num % 10))


    sum=$((d1 + d2 + d3 + d4))


    reverse="${sign}${d4}${d3}${d2}${d1}"

    echo "-----------------------------"
    echo "Sum of digits = $sum"
    echo "Reversed number = $reverse"
    echo "-----------------------------"

else
    echo "Invalid input! Please enter exactly a 4-digit integer."
fi