#include "player.h"
#include "qdebug.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>

Player::Player(int x, int y, float angle, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE","Player");
    // ROTATE
    this->setTransformOriginPoint(GameProperties::getInstance()->rectangleWidth/2, GameProperties::getInstance()->rectangleHeight/2);
    this->setRotation(angle);

}

void Player::set_data( QColor color0,int team0,float angle,int speed0 ,QString vehicule0)
{
    this->color = color0;
    this->team = team0;
    this->speed = speed0;
    this->vehicule = vehicule0;


}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 100., 100.);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(this->color);
    //painter->drawRect(0, 0, GameProperties::getInstance()->rectangleWidth, GameProperties::getInstance()->rectangleHeight);
    qDebug()<<this->vehicule;
    QPixmap pixmap3 = this->get_vehicle();
    painter->drawPixmap(10,10, GameProperties::getInstance()->rectangleWidth,GameProperties::getInstance()->rectangleHeight, pixmap3);

}

QPixmap Player::get_vehicle(){

     QPixmap pixmap3(":/ressources/car.png");
     QString color_str = this->get_color(this->color);

     if (this->vehicule.contains("truck"))
     {
         pixmap3 =QPixmap(":/ressources/"+color_str+"_truck.png");

     }

     else if (this->vehicule.contains("bike"))
     {
              pixmap3 =QPixmap(":/ressources/"+color_str+"_bike.png");

     }

     else if (this->vehicule.contains("car"))
     {
              pixmap3 =QPixmap(":/ressources/"+color_str+"_car.png");

     }

    return pixmap3;
}

QString Player::get_color(QColor color)
{
    if (color ==Qt::red)
    {
        return "red";
    }
    else if (color ==Qt::blue)
    {
             return "blue";
            }
    else if (color ==Qt::green)
    {
             return "green";
            }


}
