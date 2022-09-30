#include "keyboardcontroller.h"

KeyboardController::KeyboardController() : ControllerAdapter()
{

}

bool KeyboardController::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Type::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(!keyEvent->isAutoRepeat())
        {
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
            if(keyEvent->key() == Qt::Key_Q || keyEvent->key() == Qt::Key_D)
            {
                emit computeStreering(0);
            }
        }
    }
    if(event->type() == QEvent::Type::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(!keyEvent->isAutoRepeat())
        {
            if(keyEvent->key() == Qt::Key_Z)
            {
                emit computeThrotle(20);
            }
            if(keyEvent->key() == Qt::Key_S)
            {
                emit computeThrotle(-20);
            }
            if(keyEvent->key() == Qt::Key_D)
            {
                emit computeStreering(-M_PI/8.);
            }
            if(keyEvent->key() == Qt::Key_Q)
            {
                emit computeStreering(M_PI/8.);
            }
        }
    }
    event->ignore();
    return QObject::eventFilter(watched, event);
}
