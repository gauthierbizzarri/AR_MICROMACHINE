#include <QGraphicsRectItem>
#include "game_rectangle.h"

GameRectangle::GameRectangle(QWidget *parent, int x, int y, double angle)
    : GameObstacle{parent, x, y}
{
    QGraphicsRectItem* rect = new QGraphicsRectItem(-25, -25, 50, 50);
    //rect->setBrush(Qt::red);
    rect->moveBy(x*0.6, y*0.6);

    this->m_item = rect;
}
