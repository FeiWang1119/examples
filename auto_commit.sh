#!/bin/bash
MESSAGE="Auto-commit: $(date)"
REPO_PATH="/home/fei/repo/job-data"
git -C "$REPO_PATH" add -A
git -C "$REPO_PATH" commit -m "$MESSAGE"
git -C "$REPO_PATH" push origin main -f
