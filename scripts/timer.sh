#!/bin/bash

# Usage: timer.sh tips

if [ $# -lt 1 ]; then
	echo "# Usage: timer.sh tips"
	exit 1
fi

current_time=$(date +"%m-%d %H:%M")

XDG_RUNTIME_DIR=/run/user/$(id -u) notify-send "Have a good health" "${current_time} : $1" -t 5000 -i dialog-warning
