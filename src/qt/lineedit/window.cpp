// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"

#include "dlineeditex.h"

#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qframe.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include <DLineEdit>

#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardPaths>

DWIDGET_USE_NAMESPACE

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(100);
    layout->setSpacing(0);

    DLineEditEx *e = new DLineEditEx;
    e->setClearButtonEnabled(false);
    e->setEchoMode(QLineEdit::Password);
    e->setContextMenuPolicy(Qt::NoContextMenu);
    e->setFocusPolicy(Qt::StrongFocus);
    e->lineEdit()->setAlignment(Qt::AlignCenter);
    e->lineEdit()->setValidator(new QRegExpValidator(QRegExp("^[ -~]+$")));
    e->setFocus();
    QHBoxLayout *passwordLayout = new QHBoxLayout(e->lineEdit());
    passwordLayout->setContentsMargins(5, 0, 10, 0);
    passwordLayout->setSpacing(5);

    layout->addWidget(e);
    setLayout(layout);
    setFocusProxy(e);
}
