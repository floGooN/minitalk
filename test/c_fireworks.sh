#!/bin/bash

echo "PARASITE CLIENT TEST"
if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <C_PID>"
	exit 1
fi

C_PID=$1

max_duration=9

start_time=$(date +%s)

while true; do
	current_time=$(date +%s)
	elapsed_time=$((current_time - start_time))
	if [ $elapsed_time -ge $max_duration ]; then
		break
	fi
	gnome-terminal --tab --command"kill -10 $C_PID" &
	gnome-terminal --tab --command="kill -12 $C_PID" &
	gnome-terminal --tab --command="kill -10 $C_PID" &
	gnome-terminal --tab --command="kill -12 $C_PID"
	#sleep 1
done
echo "TESTS OVER"
