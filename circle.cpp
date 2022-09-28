#include "circle.h"

Circle::Circle(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{

}

QRectF Circle::boundingRect() const
{
    return QRect(0, 0, 100, 100);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, 100, 100);
}
