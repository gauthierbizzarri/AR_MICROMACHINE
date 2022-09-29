#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <controlleradapter.h>
#include <QKeyEvent>
#include <QDebug>

class KeyboardController: public ControllerAdapter
{
public:
    KeyboardController() : ControllerAdapter()
    {

    }

public:
    bool eventFilter(QObject *watched, QEvent *event)
    {
        if(event->type() == QEvent::Type::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_E)
            {
                emit bombAction();
            }
            if(keyEvent->key() == Qt::Key_R)
            {
                emit bananaAction();
            }
            if(keyEvent->key() == Qt::Key_F)
            {
                emit rocketAction();
            }
            if(keyEvent->key() == Qt::Key_Z || keyEvent->key() == Qt::Key_S)
            {
                emit computeThrotle(0);
            }
        }
        if(event->type() == QEvent::Type::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Z)
            {
                emit computeThrotle(100);
            }
            if(keyEvent->key() == Qt::Key_S)
            {
                emit computeThrotle(-100);
            }
            if(keyEvent->key() == Qt::Key_D)
            {
                emit computeStreering(90);
            }
            if(keyEvent->key() == Qt::Key_Q)
            {
                emit computeStreering(-90);
            }
        }
        event->ignore();
        return QObject::eventFilter(watched, event);
    }
};

#endif // KEYBOARDCONTROLLER_H
