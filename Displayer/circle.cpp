#include "circle.h"
#include <gameproperties.h>

Circle::Circle(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{

}

QRectF Circle::boundingRect() const
{
    return QRect(0, 0, GameProperties::getInstance()->circleRadius, GameProperties::getInstance()->circleRadius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, GameProperties::getInstance()->circleRadius, GameProperties::getInstance()->circleRadius);
}
