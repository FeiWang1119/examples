#!/bin/bash

LOG_FILE="/home/fei/auto-update.log"
REPO_PATH="/home/fei/repo/dtkwidget"
git -C "$1" pull linuxdeepin master:master --rebase
echo "$(date): auto update $1" >> "$LOG_FILE"
