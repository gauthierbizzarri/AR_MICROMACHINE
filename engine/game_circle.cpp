#include <QGraphicsEllipseItem>
#include <QPen>
#include "game_circle.h"

GameCircle::GameCircle(QWidget *parent, int x, int y)
    : GameObstacle{parent, x, y}
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-25, -25, 50, 50);
    QPen pen;
    pen.setWidth(1);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::red));
    item->moveBy(x*0.6, y*0.6);

    this->m_item = item;
}
