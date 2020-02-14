#! /bin/bash

FILE_LOCATION=~/Documents/Github/timeCard

PayStubLocation="C:/Users/luppu/Documents/GitHub/timeCard/bashFiles/"

echo $PayStubLocation

cd $FILE_LOCATION
echo "1 5 $PayStubLocation 6" | ./main.exe

#Username
#clockIn, clockOut, customTime, printPaystub, printAllPaystubs, exit

