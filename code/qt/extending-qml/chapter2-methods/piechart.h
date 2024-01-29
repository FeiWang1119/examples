// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#ifndef PIECHART_H
#define PIECHART_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

//![0]
class PieChart : public QQuickPaintedItem // to override QQuickPaintedItem::paint()
{
//![0]
    Q_OBJECT // support MOC
    Q_PROPERTY(QString name READ name WRITE setName FINAL) // the property is usable from QML by MOC 
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL) // like above
    QML_ELEMENT // the class is registered using the macro, to allow it to be used from QML
//![1]
public:
//![1]

    PieChart(QQuickItem *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter) override;

//![2]
    Q_INVOKABLE void clearChart(); // Q_INVOKABLE makes the method available to Qt MOC, and in turn, to QML

signals:
    void chartCleared();
//![2]

private:
    QString m_name;
    QColor m_color;

//![3]
};
//![3]

#endif

