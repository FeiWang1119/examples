// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"

#include <qguiapplication.h>
#include <qlogging.h>
#include <qmainwindow.h>

#include <QClipboard>
#include <QMimeData>

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, [clipboard] {
        qWarning() << "clipboard:" << clipboard->mimeData()->hasText();
        qWarning() << "clipboard:" << clipboard->mimeData()->text();
    });
}
