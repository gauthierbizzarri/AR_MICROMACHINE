#ifndef CONTROLLERADAPTER_H
#define CONTROLLERADAPTER_H

#include <QWidget>

class ControllerAdapter : public QObject
{
    Q_OBJECT
protected:
    ControllerAdapter();


signals:
    void computeThrotle(float);
    void computeStreering(float);
    void bombAction();
    void bananaAction();
    void rocketAction();

public:
    virtual bool eventFilter(QObject *watched, QEvent *event) = 0;
};

#endif // CONTROLLERADAPTER_H
