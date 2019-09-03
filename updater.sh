#!/bin/bash
clockpid=$(ps -ef | grep asciiclock | grep -vE '(grep|g++)' | awk '{print }')

myfetch=$(git fetch --dry-run)

if [ "$myfetch" -eq "" ]; then
	echo "No updates, exiting"
else
	echo "Update found"
fi




