#include "player.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>
#include <QtMath>
#include <QDebug>

const QString Player::BIKE = "bike";
const QString Player::CAR = "car";
const QString Player::TRUCK = "truck";

const QImage Player::DEFAULT = QImage(":/ressources/car.png");
const QImage Player::RED_CAR = QImage(":/ressources/red_car.png");
const QImage Player::BLUE_CAR = QImage(":/ressources/blue_car.png");
const QImage Player::GREEN_CAR = QImage(":/ressources/green_car.png");
const QImage Player::RED_TRUCK= QImage(":/ressources/red_truck.png");
const QImage Player::BLUE_TRUCK = QImage(":/ressources/blue_truck.png");
const QImage Player::GREEN_TRUCK = QImage(":/ressources/green_catruck.png");
const QImage Player::RED_BIKE = QImage(":/ressources/red_bike.png");
const QImage Player::BLUE_BIKE = QImage(":/ressources/blue_bike.png");
const QImage Player::GREEN_BIKE = QImage(":/ressources/green_bike.png");

Player::Player(int x, int y, float angle, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
    this->setProperty("TYPE","Player");
    // ROTATE
    this->setTransformOriginPoint(GameProperties::getInstance()->rectangleWidth/2, GameProperties::getInstance()->rectangleHeight/2);
    qDebug()<<qRadiansToDegrees(angle)-90;
    this->setRotation(qRadiansToDegrees(angle)+90);

}

void Player::set_data( QColor color0,int team0,int speed0 ,QString vehicule0)
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
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // painter->drawRect(0, 0, GameProperties::getInstance()->rectangleWidth, GameProperties::getInstance()->rectangleHeight);
    QImage image = this->get_vehicle();
    painter->drawImage(0, 0, image.scaled(GameProperties::getInstance()->rectangleWidth ,GameProperties::getInstance()->rectangleHeight*1.6));
    //painter->drawPixmap(0,0, GameProperties::getInstance()->rectangleWidth,GameProperties::getInstance()->rectangleHeight, pixmap3);

}

QImage Player::get_vehicle(){

     QImage image = DEFAULT;
     QString color_str = this->get_color(this->color);

     if (this->vehicule.contains(TRUCK))
     {
         if(color_str == "red")
             return RED_TRUCK;
         if(color_str == "blue")
             return BLUE_TRUCK;
         if(color_str == "green")
             return GREEN_TRUCK;
     }

     else if (this->vehicule.contains(BIKE))
     {
         if(color_str == "red")
             return RED_BIKE;
         if(color_str == "blue")
             return BLUE_BIKE;
         if(color_str == "green")
             return GREEN_BIKE;
     }

     else if (this->vehicule.contains(CAR))
     {
         if(color_str == "red")
             return RED_CAR;
         if(color_str == "blue")
             return BLUE_CAR;
         if(color_str == "green")
             return GREEN_CAR;
     }
     return image;
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
    return "black";
}
