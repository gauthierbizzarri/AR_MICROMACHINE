#include "rectangle.h"
#include <QGraphicsEllipseItem>

Rectangle::Rectangle(int x, int y, float angle, QGraphicsItem* parent): CircuitElement(x, y, parent)
{
    this->setTransformOriginPoint(50, 50);
    this->setRotation(angle);
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(0, 0, 100., 100.);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, 100, 100);
}
