#!/bin/bash

# 参数使用绝对路径， 如果路径不存在会自动创建。
# 如果使用相对路径，会出现路径嵌套。例如 /tmp/clone-dtk.sh ./repo  (不加参数时 默认./ 同样出现嵌套)
# repo目录下有dtkcore，dtkcore目录下有dktgui, 依次嵌套。可能git clone 后当前路径会变成克隆后的路径。

if [ $# -ne 2 ]; then
  echo "Usage: $0 absolutePath repoName"
  exit 1
fi

DTKCORE=""
DTKGUI=""
DTKWIDGET=""
QI=""
QP=""

DTKCORE_PATH=""
DTKGUI_PATH=""
DTKWIDGET_PATH=""
QI_PATH=""
QP_PATH=""

if [ -z "$1" ]; 
then
    DTKCORE_PATH="./dtkcore"
    DTKGUI_PATH="./dtkgui"
    DTKWIDGET_PATH="./dtkwidget"
    QI_PATH="./qt5integration"
    QP_PATH="./qt5platform-plugins"
    echo "clone to  current directory"
else
    DTKCORE="$1/dtkcore"
    DTKGUI="$1/dtkgui"
    DTKWIDGET="$1/dtkwidget"
    QI="$1/qt5integration"
    QP="$1/qt5platform-plugins"

    DTKCORE_PATH=$DTKCORE
    DTKGUI_PATH=$DTKGUI
    DTKWIDGET_PATH=$DTKWIDGET
    QI_PATH=$QI
    QP_PATH=$QP
fi

git clone git@github.com:FeiWang1119/dtkcore.git $DTKCORE
cd $DTKCORE_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/dtkcore.git

git clone git@github.com:FeiWang1119/dtkgui.git $DTKGUI
cd $DTKGUI_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/dtkgui.git

git clone git@github.com:FeiWang1119/dtkwidget.git $DTKWIDGET
cd $DTKWIDGET_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/dtkwidget.git

git clone git@github.com:FeiWang1119/qt5integration.git $QI
cd $QI_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/qt5integration.git

git clone git@github.com:FeiWang1119/qt5platform-plugins.git $QP
cd $QP_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/qt5platform-plugins.git


