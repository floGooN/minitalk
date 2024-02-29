#!/bin/bash

echo "PARASITE SERVER TEST"
if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <S_PID>"
	exit 1
fi

S_PID=$1

max_duration=12

start_time=$(date +%s)

while true; do
	current_time=$(date +%s)
	elapsed_time=$((current_time - start_time))
	if [ $elapsed_time -ge $max_duration ]; then
		break
	fi
	gnome-terminal --tab --command"kill -10 $S_PID" &
	gnome-terminal --tab --command="kill -12 $S_PID" &
	gnome-terminal --tab --command="kill -10 $S_PID" &
	gnome-terminal --tab --command="kill -12 $S_PID"
	#sleep 1
done

echo "TESTS OVER"

