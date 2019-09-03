#!/bin/bash
clockpid=$(ps -ef | grep asciiclock | grep -vE '(grep|g++)' | awk '{print }')

myfetch=$((git fetch --dry-run) 2>&1)

echo $clockpid

if [ -z "$myfetch" ]; then
	echo "No updates, exiting"
else
	echo "Update found"
fi

