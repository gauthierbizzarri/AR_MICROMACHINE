#ifndef POINT_H
#define POINT_H

#include <position.h>
#include <quuid.h>
#include <circuitelement.h>
#include <QPainter>

class Point : public CircuitElement
{
public:
    Point(int id, Position* pos);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool operator==(CircuitElement* el){
        return el->getId() == this->id;
    }
};

#endif // POINT_H
