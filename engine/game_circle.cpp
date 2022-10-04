#include <QGraphicsEllipseItem>
#include <QPen>
#include "game_circle.h"

GameCircle::GameCircle(QWidget *parent, int x, int y, int r)
    : GameObstacle{parent, x, y}
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-r, -r, r*2, r*2);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::red));
    item->moveBy(x, y);

    this->m_item = item;
}
