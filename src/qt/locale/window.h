#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private:
};

//! [0]

#endif
