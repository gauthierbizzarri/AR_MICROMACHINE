#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <controlleradapter.h>
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>

class KeyboardController: public ControllerAdapter
{
public:
    KeyboardController();

public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // KEYBOARDCONTROLLER_H
