#ifndef GAMEPADCONTROLLER_H
#define GAMEPADCONTROLLER_H

#include <QGamepad>
#include <game/controller/controlleradapter.h>
#include <QEvent>
#include <QApplication>

class GamepadController : public ControllerAdapter
{
private:
    QGamepad* pad;
    double acceleration=0, frein=0, puissance=0;
public:
    GamepadController();



    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void bpressed(bool);
    void xpressed(bool);
    void ypressed(bool);
    void leftpressed(bool);
    void rightpressed(bool);
    void r2precise(double value);
    void l2precise(double value);
    void dirPrecise(double value);

};

#endif // GAMEPADCONTROLLER_H
