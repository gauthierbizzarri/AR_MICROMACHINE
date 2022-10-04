#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "game_checkpoint.h"

QList<GameCheckpoint*> gameCheckpoints;

GameCheckpoint::GameCheckpoint(QWidget *parent, int x, int y, int r)
    : GameMapObject{parent, x, y}
{

    this->next = nullptr;
    this->id = 0;

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-r, -r, r*2, r*2);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    item->moveBy(x, y);

    this->m_item = item;

    gameCheckpoints.append(this);
}

GameCheckpoint::~GameCheckpoint() {
    gameCheckpoints.removeOne(this);
}
