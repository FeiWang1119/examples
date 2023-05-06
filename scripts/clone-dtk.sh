#!/bin/bash

# Usage: clone-dtk.sh ./repo

init_path="$(pwd)"
echo "Current path: $init_path"

repos="dtkcommon dtkcore dtkgui dtkwidget qt5integration  qt5platform-plugins"

for repo in $repos
do
  current_path=""
  repo_path=""
  if [ -z "$1" ]; 
  then
    repo_path="./$repo"
  else
    current_path="$1/$repo"
    repo_path=$current_path
  fi
  git clone git@github.com:FeiWang1119/$repo.git $current_path
  cd $repo_path
  git remote add linuxdeepin git@github.com:linuxdeepin/$repo.git
  cd $init_path
done
