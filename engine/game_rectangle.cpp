#include <QGraphicsRectItem>
#include <QPen>
#include "game_rectangle.h"

GameRectangle::GameRectangle(QWidget *parent, int x, int y, double angle)
    : GameObstacle{parent, x, y}
{
    QGraphicsRectItem* item = new QGraphicsRectItem(-25, -25, 50, 50);
    QPen pen;
    pen.setWidth(1);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::red));
    item->moveBy(x*0.6, y*0.6);

    this->m_item = item;
}
