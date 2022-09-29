#include "rocket.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>

Rocket::Rocket(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE","Banana");
}

QRectF Rocket::boundingRect() const
{
    return QRectF(0, 0,10,10); //GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Rocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::darkRed);
    painter->drawEllipse(0, 0, 10,10 ); //GameProperties::getInstance()->checkpointRadius, 10 );GameProperties::getInstance()->checkpointRadius);
    QPixmap pixmap3(":/ressources/rocket.png");

    painter->drawPixmap(10,10,100,100, pixmap3);
}
