#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <circuitelement.h>
#include <QPainter>

class Rectangle : public CircuitElement
{
public:
    /**
     * @brief Rectangle graphical representation of a rectangle obstacle
     * @param x x center position of the rectangle
     * @param y y center porision of the rectangle
     * @param angle rotation of the rectangle
     * @param parent graphical item's parent
     */
    Rectangle(int x, int y, float angle, QGraphicsItem* parent = nullptr);

//********interface***********//
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RECTANGLE_H
