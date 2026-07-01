#! /bin/bash

read -p "Enter the name of the employee: " name
read -p "Enter the basic salary: " sal
read -p "Enter the house rent allowance: " ha
read -p "Enter the dearness allowance: " da

net=$(echo "$sal + $ha + $da" | bc)

echo "____________________________SALARY SLIP____________________________"
echo "Name : $name"
echo "Name : $net"