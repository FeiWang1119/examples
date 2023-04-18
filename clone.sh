#!/bin/bash

# example : clone.sh ./ repo dtkcore dtkwidget

if [ $# -lt 2 ]; then
  echo "Usage: $0 path repo"
  exit 1
fi

INIT_PATH="$(pwd)"
echo "Current path: $INIT_PATH"

for arg in "${@:2}"
do
  echo "The current repo is $arg" 
  git clone git@github.com:FeiWang1119/$arg.git $1/$arg 
  cd "$1/$arg"
  git remote add linuxdeepin git@github.com:linuxdeepin/$arg.git
  cd $INIT_PATH
done 

