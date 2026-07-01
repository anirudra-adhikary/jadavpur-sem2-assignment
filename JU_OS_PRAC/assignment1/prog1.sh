#!/bin/bash

while true
do
    read -p "Enter the first number: " userv1
    read -p "Enter the second number: " userv2

    # Regex check
    if [[ $userv1 =~ ^-?[0-9]+(\.[0-9]+)?$ && \
          $userv2 =~ ^-?[0-9]+(\.[0-9]+)?$ ]]
    then
        sum=$(echo "$userv1 + $userv2" | bc)
        prod=$(echo "$userv1 * $userv2" | bc)
        diff=$(echo "$userv1 - $userv2" | bc)

        echo "Sum = $sum"
        echo "Product = $prod"
        echo "Difference = $diff"

        if (( $(echo "$userv2 == 0" | bc) )); then
            echo "Denominator is zero. Division not possible"
        else
            div=$(echo "scale=2; $userv1 / $userv2" | bc)
            echo "Division = $div"
        fi
    else
        echo "Inputs are not numbers"
    fi

    echo "----------------------------------"
    read -p "Do you want to continue? (y/n): " choice

    if [[ "$choice" != "y" && "$choice" != "Y" ]]
    then
        echo "Exiting program..."
        break
    fi

done