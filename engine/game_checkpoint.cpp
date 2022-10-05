#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "game_checkpoint.h"

QList<GameCheckpoint*> gameCheckpoints;

GameCheckpoint::GameCheckpoint(QWidget *parent, int x, int y, int r, int id, int pos)
    : GameMapObject{parent, x, y}, id(id), pos(pos)
{

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

int previousCheckpointId(int pos) {

    pos = pos -1;
    if(pos < 0)
        pos += gameCheckpoints.length();

    return gameCheckpoints[pos]->id;
}
