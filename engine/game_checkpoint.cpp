
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "game_checkpoint.h"

// ////////////////////////////////////////////////////////////////////////////
// Globals
// ////////////////////////////////////////////////////////////////////////////

QList<GameCheckpoint*> gameCheckpoints;

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

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

// ////////////////////////////////////////////////////////////////////////////
// Methods
// ////////////////////////////////////////////////////////////////////////////

void GameCheckpoint::updateProperties(GameProperties* properties) {

    auto item = (QGraphicsEllipseItem*) this->m_item;
    item->setRect(-properties->checkpointRadius, -properties->checkpointRadius, 2*properties->checkpointRadius, 2*properties->checkpointRadius);
}

// ////////////////////////////////////////////////////////////////////////////
// Functions
// ////////////////////////////////////////////////////////////////////////////

int previousCheckpointId(int pos) {

    pos = pos -1;
    if(pos < 0)
        pos += gameCheckpoints.length();

    return pos >= 0 ? gameCheckpoints[pos]->id : -1;
}
