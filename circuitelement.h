#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include <position.h>
#include <quuid.h>
#include <QWidget>
#include <QPaintEvent>
#include <QGraphicsItem>

class CircuitElement : public QGraphicsObject
{
protected:
    CircuitElement(int x, int y, QGraphicsItem* parent = nullptr):QGraphicsObject(parent){
        this->setPos(x, y);
    }
};

#endif // CIRCUITELEMENT_H
