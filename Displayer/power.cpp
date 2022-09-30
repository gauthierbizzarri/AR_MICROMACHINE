#include "power.h"
#include <QGraphicsEllipseItem>
#include <QMovie>
#include <gameproperties.h>

Power::Power(int x, int y,QString name,int amount, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE",name);
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

    painter->drawPixmap(10,10, GameProperties::getInstance()->rectangleWidth*1.5,GameProperties::getInstance()->rectangleHeight*1.5, this->get_image());
}

QPixmap Power::get_image()
{
    if (this->property("TYPE").toString().contains("banana") )
    {
        QPixmap pixmap3(":/ressources/banana_power.png");

        return pixmap3;
    }

    else if (this->property("TYPE").toString().contains("bomb") )
    {
        QPixmap pixmap3(":/ressources/bomb_power.png");

        return pixmap3;
    }

    else if (this->property("TYPE").toString().contains("rocket") )
    {
        QPixmap pixmap3(":/ressources/rocket_power.png");

        return pixmap3;
    }

}
