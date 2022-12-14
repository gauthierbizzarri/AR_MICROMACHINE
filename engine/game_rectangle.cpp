#include <QGraphicsRectItem>
#include <QPen>
#include <math.h>
#include "game_rectangle.h"

GameRectangle::GameRectangle(QWidget *parent, int x, int y, double angle, int w, int h)
    : GameObstacle{parent, x, y}
{
    this->m_angle = angle;
    this->m_width = w;;
    this->m_height = h;

    QGraphicsRectItem* item = new QGraphicsRectItem(-w/2, -h/2, w, h);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::darkBlue);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::darkBlue));
    item->moveBy(x, y);
    item->setRotation(-angle/M_PI*180);

    this->m_item = item;
}

double GameRectangle::angle() {
    return this->m_angle;
}
int GameRectangle::W() {
    return this->m_width;
}
int GameRectangle::H() {
    return this->m_height;
}

void GameRectangle::updateProperties(GameProperties* properties) {

    auto item = (QGraphicsRectItem*) this->m_item;
    item->setRect(-properties->rectangleWidth/2, -properties->rectangleHeight/2, properties->rectangleWidth, properties->rectangleHeight);
}
