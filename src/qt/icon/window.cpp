// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"

#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qframe.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qpushbutton.h>

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QPushButton *button = new QPushButton;
    QIcon icon = QIcon::fromTheme("dialog-ok");
    button->setIcon(icon);
    layout->addWidget(button);
    setLayout(layout);
    qWarning() << "themeName:" << icon.themeName();

    /* QStringList paths; */
    /* // Add home directory first in search path */
    /* const QFileInfo homeIconDir(QDir::homePath() + "/.icons"); */
    /* if (homeIconDir.isDir()) */
    /*     paths.prepend(homeIconDir.absoluteFilePath()); */
    /**/
    /* paths.append(QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, */
    /*                                        QStringLiteral("icons"), */
    /*                                        QStandardPaths::LocateDirectory)); */
    /* qWarning() << QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation); */
    /* qWarning() << paths; */
}
