#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "game_checkpoint.h"

GameCheckpoint::GameCheckpoint(QWidget *parent, int x, int y)
    : GameMapObject{parent, x, y}
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-12.5, -12.5, 25, 25);

    item->setBrush(QBrush(Qt::red));
    QPen pen;
    pen.setWidth(5);
    item->setPen(pen);
    //rect->setBrush(Qt::red);
    //item->setBrush(Qt::red);
    item->moveBy(x*0.6, y*0.6);

    this->m_item = item;
}
