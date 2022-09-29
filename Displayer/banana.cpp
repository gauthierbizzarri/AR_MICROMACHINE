#include "banana.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>

Banana::Banana(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE","Banana");
}

QRectF Banana::boundingRect() const
{
    return QRectF(0, 0,10,10); //GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Banana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(0, 0, 10,10 ); //GameProperties::getInstance()->checkpointRadius, 10 );GameProperties::getInstance()->checkpointRadius);
}
