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
        event->accept();
        qDebug()<<event->type();
        if(event->type() == QEvent::Type::KeyRelease)
        {
            qDebug()<<"release";
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
            return true;
        }
        if(event->type() == QEvent::Type::KeyPress)
        {
            qDebug()<<"press";
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
            return true;
        }
        return QObject::eventFilter(watched, event);
    }
};

#endif // KEYBOARDCONTROLLER_H
