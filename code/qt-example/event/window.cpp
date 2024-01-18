// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"

#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qframe.h>
#include <qmainwindow.h>

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

Child::Child(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(400, 400);
    setStyleSheet("background: red");
    installEventFilter(this);
}

bool Child::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        qWarning() << "Child eventFilter: Key Press";
    }
    if (event->type() == QEvent::MouseButtonPress) {
        qWarning() << "Child eventFilter: Button Press";
    }
    return QWidget::eventFilter(watched, event);
}

bool Child::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        qWarning() << "Child event: Key Press";
    }
    if (e->type() == QEvent::MouseButtonPress) {
        qWarning() << "Child eventFilter: Button Press";
    }
    return QWidget::event(e);
}

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    Child *child = new Child;
    layout->addWidget(child);
    setLayout(layout);

    installEventFilter(this);
}

bool Window::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        qWarning() << "Parent eventFilter: Key Press";
    }
    if (event->type() == QEvent::MouseButtonPress) {
        qWarning() << "Parent eventFilter: Button Press";
    }
    return QWidget::eventFilter(watched, event);
}

bool Window::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        qWarning() << "Parent event: Key Press";
    }
    if (e->type() == QEvent::MouseButtonPress) {
        qWarning() << "Parent eventFilter: Button Press";
    }
    return QWidget::event(e);
}
