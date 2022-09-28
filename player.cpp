#include "player.h"
#include <QGraphicsEllipseItem>

Player::Player(int x, int y ) : CircuitElement(x, y)

{
}

void Player::set_data( char color0,int team,float angle,int speed ,char vehicule)
{

}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 100., 100.);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(0, 0, 20, 20);
}
