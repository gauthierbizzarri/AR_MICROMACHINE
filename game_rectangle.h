#ifndef GAMERECTANGLE_H
#define GAMERECTANGLE_H

#include "game_obstacle.h"

class GameRectangle : public GameObstacle
{
public:
    GameRectangle(QWidget *parent, int x, int y, double angle);
};

#endif // GAMERECTANGLE_H
