#ifndef CIRCLE_H
#define CIRCLE_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Circle : public CircuitElement
{
public:
    /**
     * @brief Circle graphical representation of a circle obstacle
     * @param x x central position of the circle
     * @param y y central position of the circle
     * @param parent graphical item's parent
     */
    Circle(int x, int y, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIRCLE_H
