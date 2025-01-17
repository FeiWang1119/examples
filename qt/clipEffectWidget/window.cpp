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
#include <qwidget.h>

#include <DPaletteHelper>

#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPainter>
#include <QPushButton>
#include <QStandardPaths>

DWIDGET_USE_NAMESPACE

//! [0]
Window::Window(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(100);
    layout->setSpacing(0);

    w = new Widget;
    w->setFixedSize(100, 100);
    layout->addWidget(w);

    setLayout(layout);
}

Panel::Panel(QWidget *parent)
    : QWidget(parent)
{
}

void Panel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);
    painter.drawRect(rect());
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    w = new Panel;

    clipEffectWidget = new DClipEffectWidget(w);

    layout->addWidget(w);

    setLayout(layout);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    QPainterPath path;
    path.addRoundedRect(rect(), 18, 18);
    if (clipEffectWidget) {
        clipEffectWidget->setClipPath(path);
    }
}
