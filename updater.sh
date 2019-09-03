#!/bin/bash
clockpid=$(ps -ef | grep asciiclock | grep -vE '(grep|g++)' | awk '{print }')





