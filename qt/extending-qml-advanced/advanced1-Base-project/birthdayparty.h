// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BIRTHDAYPARTY_H
#define BIRTHDAYPARTY_H

#include "person.h"

#include <QObject>
#include <QQmlListProperty>

class BirthdayParty : public QObject
{
    Q_OBJECT // support MOC
    // the property is usable from QML by MOC. NOTIFY for enabing property binding
    Q_PROPERTY(Person *host READ host WRITE setHost NOTIFY hostChanged FINAL) 
    Q_PROPERTY(QQmlListProperty<Person> guests READ guests NOTIFY guestsChanged FINAL)
    QML_ELEMENT // the class is registered using the macro, to allow it to be used from QML
public:
    using QObject::QObject;

    Person *host() const;
    void setHost(Person *);

    QQmlListProperty<Person> guests();
    void appendGuest(Person *);
    qsizetype guestCount() const;
    Person *guest(qsizetype) const;
    void clearGuests();
    void replaceGuest(qsizetype, Person *);
    void removeLastGuest();

signals:
    void hostChanged();
    void guestsChanged();

private:
    static void appendGuest(QQmlListProperty<Person> *, Person *);
    static qsizetype guestCount(QQmlListProperty<Person> *);
    static Person *guest(QQmlListProperty<Person> *, qsizetype);
    static void clearGuests(QQmlListProperty<Person> *);
    static void replaceGuest(QQmlListProperty<Person> *, qsizetype, Person *);
    static void removeLastGuest(QQmlListProperty<Person> *);

    Person *m_host = nullptr;
    QList<Person *> m_guests;
};

#endif // BIRTHDAYPARTY_H
