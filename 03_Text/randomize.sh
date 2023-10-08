#!/bin/sh

bytes=$(od -v -An -tx1)
row=0
col=0
max_row=0
if [ "$1" = ""]; then
    /bin/echo -e "Usage: randomize.sh <delay>\n\tdelay -- delay between displaying characters\n"
    exit
fi
tput clear
delay=$1
for byte in $bytes; do
    if [ $byte != "20" ]; then
        echo "$row $col $byte"
    fi
    if [ $byte = "0a" ]; then
        row=$((row+1))
        max_row=$row
        col=0
    fi
    col=$((col+1))
done | shuf | while read line
do
    if [ $row -gt $max_row ]; then
        max_row=$row
    fi
    row=$(echo $line | cut -d ' ' -f 1)
    col=$(echo $line | cut -d ' ' -f 2)
    byte=$(echo $line | cut -d ' ' -f 3)
    char=$(/bin/echo -e "\x$byte")
    tput cup $row $col
    echo $char
    tput cup $((max_row+1)) 0
    sleep $delay
done
