#ifndef GAMECHECKPOINT_H
#define GAMECHECKPOINT_H

#include <QList>
#include "game_map_object.h"

class GameCheckpoint : public GameMapObject
{
    Q_OBJECT

public:
    GameCheckpoint(QWidget *parent, int x, int y);
    ~GameCheckpoint();
};

extern QList<GameCheckpoint*> gameCheckpoints;

#endif // GAMECHECKPOINT_H
