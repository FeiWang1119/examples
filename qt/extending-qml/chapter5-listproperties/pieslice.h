// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#ifndef PIESLICE_H
#define PIESLICE_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

//![0]
class PieSlice : public QQuickPaintedItem
{
    Q_OBJECT // support MOC
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL) // the property is usable from QML by MOC 
    Q_PROPERTY(int fromAngle READ fromAngle WRITE setFromAngle FINAL)
    Q_PROPERTY(int angleSpan READ angleSpan WRITE setAngleSpan FINAL)
    QML_ELEMENT // the class is registered using the macro, to allow it to be used from QML
//![0]

public:
    PieSlice(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    int fromAngle() const;
    void setFromAngle(int angle);

    int angleSpan() const;
    void setAngleSpan(int span);

    void paint(QPainter *painter) override;

private:
    QColor m_color;
    int m_fromAngle;
    int m_angleSpan;
};

#endif

