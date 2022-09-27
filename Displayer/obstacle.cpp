#include "obstacle.h"
#include <QGraphicsEllipseItem>

Obstacle::Obstacle(int id, Position* pos, float angle): CircuitElement(id, pos)
{
    this->angle=angle;
}

float Obstacle::getAngle()
{
    return this->angle;
}

void Obstacle::setAngle(float angle)
{
    this->angle = angle;
}

QRectF Obstacle::boundingRect() const
{
    if(this->id%2 == 0)
    {
        return QRectF(-50, -50, 100., 100.);
    }
    return QRectF(-60, -50, 120., 100.);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    if(this->id%2 == 0)
    {
        painter->drawEllipse(0, 0, 100, 100);
    }
    else
    {
        painter->drawRect(0, 0, 120, 100);
    }
}
