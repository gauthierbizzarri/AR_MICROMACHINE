#include "rectangle.h"
#include "qdebug.h"
#include <QGraphicsEllipseItem>

Rectangle::Rectangle(int x, int y, float angle, QGraphicsItem* parent): CircuitElement(x, y, parent)
{
    this->setTransformOriginPoint(50, 50);
    this->setRotation(angle);

    this->setProperty("TYPE","Rectangle");
    qDebug()<<"Created"<<this->property("TYPE");
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
