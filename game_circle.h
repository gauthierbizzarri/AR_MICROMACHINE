#ifndef GAMECIRCLE_H
#define GAMECIRCLE_H

#include "game_obstacle.h"

class GameCircle : public GameObstacle
{
public:
    GameCircle(QWidget *parent, int x, int y);
};

#endif // GAMECIRCLE_H
