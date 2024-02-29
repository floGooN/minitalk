#!/bin/bash

echo "PARASITE TEST TEST"
str="$(cat tmp.txt)"
if [ "$#" -ne 2 ]; then
	echo "Usage: $0 <S_PID>"
	echo "Usage: $1 <C_PID>"
	exit 1
fi

S_PID=$1
C_PID=$2

max_duration=7

start_time=$(date +%s)

while true; do
	current_time=$(date +%s)
	elapsed_time=$((current_time - start_time))
	if [ $elapsed_time -ge $max_duration ]; then
		break
	fi
	gnome-terminal --tab --command"./client $S_PID $ARG" &
	gnome-terminal --tab --command"kill -10 $S_PID" &
	gnome-terminal --tab --command="kill -12 $S_PID" &
	gnome-terminal --tab --command="kill -10 $C_PID" &
	gnome-terminal --tab --command="kill -12 $C_PID"
	sleep 1
done

echo "TESTS OVER"
