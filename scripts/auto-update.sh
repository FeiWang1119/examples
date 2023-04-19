#!/bin/bash

LOG_FILE="/home/fei/auto-update.log"
REPO_PATH="/home/fei/repo/dtkwidget"

echo "$(date): auto update $1" >> $LOG_FILE
git -C "$1" pull linuxdeepin master:master --rebase 2>>$LOG_FILE
