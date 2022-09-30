#include "gamepadcontroller.h"
#include <QtMath>
#include <QDebug>
#include <QWindow>

GamepadController::GamepadController()
{
    QList<int> gamepads_list = QGamepadManager::instance()->connectedGamepads();
    if (gamepads_list.size()>0){
        pad = new QGamepad(gamepads_list[0]);

        connect(pad, SIGNAL(buttonBChanged(bool)), this, SLOT(bpressed(bool)));
        connect(pad, SIGNAL(buttonXChanged(bool)), this, SLOT(xpressed(bool)));
        connect(pad, SIGNAL(buttonYChanged(bool)), this, SLOT(ypressed(bool)));
        connect(pad, SIGNAL(buttonLeftChanged(bool)), this, SLOT(leftpressed(bool)));
        connect(pad, SIGNAL(buttonRightChanged(bool)), this, SLOT(rightpressed(bool)));
        connect(pad, SIGNAL(buttonR2Changed(double)), this, SLOT(r2precise(double)));
        connect(pad, SIGNAL(buttonL2Changed(double)), this, SLOT(l2precise(double)));
        connect(pad, SIGNAL(axisLeftXChanged(double)),this ,SLOT(dirprecise(double)));
    }


    qDebug()<<"hey";
}

bool GamepadController::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    event->ignore();
    return false;
}

void GamepadController::bpressed(bool)
{
    emit bananaAction();
}

void GamepadController::xpressed(bool)
{
    emit rocketAction();
}

void GamepadController::ypressed(bool)
{
    emit bombAction();
}

void GamepadController::leftpressed(bool)
{
    emit computeStreering(M_PI/2);
}

void GamepadController::rightpressed(bool)
{
    emit computeStreering(-M_PI/2);
}

void GamepadController::r2precise(double value)
{
    acceleration=value;
    emit computeThrotle(acceleration-frein);
}

void GamepadController::l2precise(double value)
{
    frein = value;
    emit computeThrotle(acceleration-frein);
}

void GamepadController::dirPrecise(double value)
{
    emit computeStreering(value*M_PI/2);
}
