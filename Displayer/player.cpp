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
    painter->drawRect(0, 0, GameProperties::getInstance()->rectangleWidth, GameProperties::getInstance()->rectangleHeight);
}
