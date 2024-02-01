// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#ifndef PIECHART_H
#define PIECHART_H

#include <QtQuick/QQuickItem>

class PieSlice;

//![0]
class PieChart : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(PieSlice* pieSlice READ pieSlice WRITE setPieSlice FINAL)
//![0]
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_MOC_INCLUDE("pieslice.h") // the generated code will include this header. tell the MOC to add an include. 
                                // This is useful if the types you use as properties or signal/slots arguments are forward declared.
    QML_ELEMENT // the PieSlice type has to be exposted to QML using QML_ELEMENT.
//![1]
public:
//![1]

    PieChart(QQuickItem *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

//![2]
    PieSlice *pieSlice() const;
    void setPieSlice(PieSlice *pieSlice);
//![2]

private:
    QString m_name;
    PieSlice *m_pieSlice;

//![3]
};
//![3]

#endif

