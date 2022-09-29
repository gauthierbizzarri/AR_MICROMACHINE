#ifndef GAMECHECKPOINT_H
#define GAMECHECKPOINT_H

#include "game_map_object.h"

class GameCheckpoint : public GameMapObject
{
public:
    GameCheckpoint(QWidget *parent, int x, int y);
};

#endif // GAMECHECKPOINT_H
