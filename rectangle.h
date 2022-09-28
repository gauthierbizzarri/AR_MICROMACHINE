#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <circuitelement.h>
#include <QPainter>

class Rectangle : public CircuitElement
{
public:
    Rectangle(int x, int y, float angle, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RECTANGLE_H
