#ifndef GAMEOBSTACLE_H
#define GAMEOBSTACLE_H

#include "game_map_object.h"

class GameObstacle : public GameMapObject
{
public:
    GameObstacle(QWidget *parent, int x, int y);
};

#endif // GAMEOBSTACLE_H
