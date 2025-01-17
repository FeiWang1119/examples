#!/bin/bash

LOG_FILE="/home/fei/auto-commit.log"
MESSAGE="Auto-commit: $(date)"
REPO_PATH="/home/fei/repo/job-data"

echo "$(date): auto commit" >>$LOG_FILE

git -C "$REPO_PATH" add -A 2>>$LOG_FILE
git -C "$REPO_PATH" commit -m "$MESSAGE" 2>>$LOG_FILE
git -C "$REPO_PATH" push origin main -f 2>>$LOG_FILE
