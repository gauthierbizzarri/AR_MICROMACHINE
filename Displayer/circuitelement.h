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
    int x,y;
    /**
     * @brief CircuitElement Base class for graphical representation of circuit elements
     * @param x circuit element's center x
     * @param y circuit element's center y
     * @param parent graphical item's parent
     */
    CircuitElement(int x, int y, QGraphicsItem* parent = nullptr):QGraphicsObject(parent){
        this->setPos(x, y);
    }
};

#endif // CIRCUITELEMENT_H
