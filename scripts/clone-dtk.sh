#!/bin/bash

# Usage: clone-dtk.sh ./repo

INIT_PATH="$(pwd)"
echo "Current path: $INIT_PATH"

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
cd $INIT_PATH

git clone git@github.com:FeiWang1119/dtkgui.git $DTKGUI
cd $DTKGUI_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/dtkgui.git
cd $INIT_PATH

git clone git@github.com:FeiWang1119/dtkwidget.git $DTKWIDGET
cd $DTKWIDGET_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/dtkwidget.git
cd $INIT_PATH

git clone git@github.com:FeiWang1119/qt5integration.git $QI
cd $QI_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/qt5integration.git
cd $INIT_PATH

git clone git@github.com:FeiWang1119/qt5platform-plugins.git $QP
cd $QP_PATH
git remote add linuxdeepin git@github.com:linuxdeepin/qt5platform-plugins.git
cd $INIT_PATH

