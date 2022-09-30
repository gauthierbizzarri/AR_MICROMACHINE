#ifndef GAMEOBSTACLE_H
#define GAMEOBSTACLE_H

#include "game_map_object.h"

class GameObstacle : public GameMapObject
{
    Q_OBJECT

public:
    GameObstacle(QWidget *parent, int x, int y);
};

#endif // GAMEOBSTACLE_H
