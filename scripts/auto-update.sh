#!/bin/bash

# Usage: auto-update.sh $HOME/repo/dtkwidget

if [ $# -lt 1 ]; then
  echo "Usage: $0  repoDir"
  exit 1
fi

log_file="/home/fei/auto-update.log"

echo "$(date): auto update $1" >> $log_file
git -C "$1" pull linuxdeepin master:master --rebase 2>>$log_file
if [ $? -eq 0 ]; then
  echo "update success!"  >> $log_file
else
  echo "first update fail. try to stash changes and pull again!" >> $log_file
  git -C "$1" stash  
  git -C "$1" pull linuxdeepin master:master --rebase 2>>$log_file
  if [ $? -eq 0 ]; then
    echo "update success!"  >> $log_file
  else 
    echo "update fail!"  >> $log_file
   fi
  git -C "$1" stash pop
fi
