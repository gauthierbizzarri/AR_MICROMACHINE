#include "point.h"
#include <QGraphicsEllipseItem>

Point::Point(int id, Position* pos) : CircuitElement(id, pos)
{

}

QRectF Point::boundingRect() const
{
    return QRectF(-50, -50, 100., 100.);
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(this->pos->getX(), this->pos->getY(), 100, 100);
}
