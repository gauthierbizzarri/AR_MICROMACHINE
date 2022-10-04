#ifndef GAMECHECKPOINT_H
#define GAMECHECKPOINT_H

#include <QList>
#include "game_map_object.h"

class GameCheckpoint : public GameMapObject
{
    Q_OBJECT

public:

    GameCheckpoint* next;
    int id;


    GameCheckpoint(QWidget *parent, int x, int y, int r);
    ~GameCheckpoint();
};

extern QList<GameCheckpoint*> gameCheckpoints;

#endif // GAMECHECKPOINT_H
