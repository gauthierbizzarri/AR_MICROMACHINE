#ifndef GAMECHECKPOINT_H
#define GAMECHECKPOINT_H

#include <QList>
#include "game_map_object.h"

class GameCheckpoint : public GameMapObject
{
    Q_OBJECT

public:

    int id;
    int pos;


    GameCheckpoint(QWidget *parent, int x, int y, int r, int id, int pos);
    ~GameCheckpoint();
};

extern QList<GameCheckpoint*> gameCheckpoints;

int previousCheckpointId(int pos);

#endif // GAMECHECKPOINT_H
