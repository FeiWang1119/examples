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
    /* w->setStyleSheet("border-color: red; border-width: 1px;"); */
    /* QPalette pt = w->palette(); */
    /* pt.setBrush(QPalette::Base, Qt::transparent); */
    /* w->setPalette(pt); */
    /* w->setAutoFillBackground(true); */
    w->setMinimumSize(200, 200);
    layout->addWidget(w);

    /* QPainterPath path; */
    /* path.addRoundedRect(w->rect(), 18, 18); */

    /* qWarning() << w->rect(); */
    /* clipEffectWidget = new DClipEffectWidget(w); */
    /* clipEffectWidget->setClipPath(path); */

    setLayout(layout);
}

/* void Window::resizeEvent(QResizeEvent *event) */
/* { */
/*     QPainterPath path; */
/*     path.addRoundedRect(w->rect(), 18, 18); */
/*     qWarning() << w->rect(); */
/**/
/*     clipEffectWidget->setClipPath(path); */
/**/
/*     DBlurEffectWidget::resizeEvent(event); */
/* } */
Panel::Panel(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(10);

    QPalette pt = palette();
    // QFrame doesn't draw Background using QPalette::Window.
    pt.setBrush(QPalette::Base, Qt::transparent);
    setPalette(pt);
    setAutoFillBackground(true);

    layout->addWidget(new QListView);
    setLayout(layout);
}

void Panel::paintEvent(QPaintEvent *event)
{
    QColor color =
        DPaletteHelper::instance()->palette(this->topLevelWidget()).color(QPalette::Base);
    color.setAlpha(100);

    QPainter painter(this);
    painter.fillRect(rect(), color);
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
    path.addRoundedRect(rect(), 28, 28);
    qWarning() << "resizeEvent:" << w->rect();
    qWarning() << "path:" << path;
    if (clipEffectWidget) {
        clipEffectWidget->setClipPath(path);
    }
}

/* w->setFrameShape(QFrame::Box); */
/* w->setStyleSheet("background: gray"); */
/* clipEffectWidget->setStyleSheet("border-color: red; border-width: 1px;"); */
/* clipEffectWidget->setMargins(QMargins(4, 4, 0, 0)); */
