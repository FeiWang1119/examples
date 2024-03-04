// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WINDOW_H
#define WINDOW_H

#include <dtkwidget_global.h>
#include <qobjectdefs.h>
#include <qwidget.h>

#include <DBlurEffectWidget>
#include <DClipEffectWidget>

#include <QWidget>
DWIDGET_USE_NAMESPACE

class Widget;

//! [0]
class Window : public DBlurEffectWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

    /* protected: */
    /*     virtual void resizeEvent(QResizeEvent *event) override; */

private:
    Widget *w = nullptr;
};

class Panel : public QWidget
{
    Q_OBJECT
public:
    Panel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    DClipEffectWidget *clipEffectWidget = nullptr;
    QWidget *w = nullptr;
};

//! [0]

#endif
