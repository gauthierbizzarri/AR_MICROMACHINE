#include "power.h"
#include <QGraphicsEllipseItem>
#include <QMovie>
#include <gameproperties.h>

Power::Power(int x, int y,QString name,int amount, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
}

QRectF Power::boundingRect() const
{
    return QRectF(0, 0,10,10); //GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Power::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::black);

    painter->drawEllipse(0, 0, 10,10 ); //GameProperties::getInstance()->checkpointRadius, 10 );GameProperties::getInstance()->checkpointRadius);

    QPixmap pixmap3(":/ressources/banana.png");

    painter->drawPixmap(10,10, GameProperties::getInstance()->rectangleWidth*3,GameProperties::getInstance()->rectangleHeight*3, this->get_image());
}

QPixmap Power::get_image()
{
    QPixmap pixmap3(":/ressources/banana.png");

    return pixmap3;

}
