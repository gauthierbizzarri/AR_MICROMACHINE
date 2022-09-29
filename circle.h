#ifndef CIRCLE_H
#define CIRCLE_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Circle : public CircuitElement
{
public:
    Circle(int x, int y, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIRCLE_H
