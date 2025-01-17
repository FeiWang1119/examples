#include "window.h"

#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qframe.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qpushbutton.h>

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

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QLocale locale;
    locale.firstDayOfWeek();

    qInfo() << locale.name() << locale.language() << locale.country() << locale.script();
    qInfo() << locale.firstDayOfWeek();

    QLocale zhlocale("zh_CN");
    qInfo() << zhlocale.name() << zhlocale.language() << zhlocale.country() << zhlocale.script();
    qInfo() << zhlocale.firstDayOfWeek();
}
