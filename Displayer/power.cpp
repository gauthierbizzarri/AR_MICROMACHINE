#include "power.h"
#include <QGraphicsEllipseItem>
#include <QMovie>
#include <gameproperties.h>
#include <resourceloader.h>

Power::Power(int x, int y,QString name,int amount, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE",name);
}

QRectF Power::boundingRect() const
{
    return QRectF(0, 0,GameProperties::getInstance()->rectangleWidth,GameProperties::getInstance()->rectangleHeight); //GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Power::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::black);

    painter->drawImage(0,0, get_image().scaled(GameProperties::getInstance()->rectangleWidth,GameProperties::getInstance()->rectangleHeight));
}

QImage Power::get_image()
{
    return ResourceLoader::getInstance()->get("power:"+this->property("TYPE").toString());

}
