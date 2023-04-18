#!/bin/bash

git clone git@github.com:FeiWang1119/dtkcore.git $1/dtkcore
cd $1/dtkcore
git remote add linuxdeepin git@github.com:linuxdeepin/dtkcore.git

git clone git@github.com:FeiWang1119/dtkgui.git $1/dtkgui
cd $1/dtkgui
git remote add linuxdeepin git@github.com:linuxdeepin/dtkgui.git

git clone git@github.com:FeiWang1119/dtkwidget.git $1/dtkwidget
cd $1/dtkwidget
git remote add linuxdeepin git@github.com:linuxdeepin/dtkwidget.git

git clone git@github.com:FeiWang1119/qt5integration.git $1/qt5integration
cd $1/qt5integration
git remote add linuxdeepin git@github.com:linuxdeepin/qt5integration.git

git clone git@github.com:FeiWang1119/qt5platform-plugins.git $1/qt5platform-plugins
cd $1/qt5platform-plugins
git remote add linuxdeepin git@github.com:linuxdeepin/qt5platform-plugins.git


