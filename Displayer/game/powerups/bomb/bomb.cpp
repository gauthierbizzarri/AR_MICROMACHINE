#include "bomb.h"
#include <QGraphicsEllipseItem>
#include <game/utils/properties/gameproperties.h>

Bomb::Bomb(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE","Bomb");
}

QRectF Bomb::boundingRect() const
{
    return QRectF(0, 0,10,10); //GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::darkRed);
    //painter->drawEllipse(0, 0, 10,10 ); //GameProperties::getInstance()->checkpointRadius, 10 );GameProperties::getInstance()->checkpointRadius);
    QPixmap pixmap3(":/ressources/bomb.png");

    painter->drawPixmap(10,10, GameProperties::getInstance()->rectangleWidth,GameProperties::getInstance()->rectangleHeight, pixmap3);
}
