#include "banana.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>
#include <QDebug>

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
    painter->setBrush(Qt::red);

    painter->drawEllipse(0, 0, 10,10 ); //GameProperties::getInstance()->checkpointRadius, 10 );GameProperties::getInstance()->checkpointRadius);

    QPixmap pixmap3(":/ressources/banana.png");

    qDebug()<<this->x;
    qDebug()<<this->y;
    painter->drawPixmap(10,10,100,100, pixmap3);
    //QImage logo;
    //logo.load("ressources/banana.png");
    //QPixmap pix("C:/Users/BIZZARRI/Documents/graphics/Displayer/ressources/banana.png");
    //painter->drawImage(QRect(0,0,50,50),pix);
}
