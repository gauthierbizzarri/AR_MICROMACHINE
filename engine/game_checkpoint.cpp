#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "game_checkpoint.h"

QList<GameCheckpoint*> gameCheckpoints;

GameCheckpoint::GameCheckpoint(QWidget *parent, int x, int y)
    : GameMapObject{parent, x, y}
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-12.5, -12.5, 25, 25);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    //item->setBrush(QBrush(Qt::red));
    item->moveBy(x*0.6, y*0.6);

    this->m_item = item;

    gameCheckpoints.append(this);
}

GameCheckpoint::~GameCheckpoint() {
    gameCheckpoints.removeOne(this);
}
