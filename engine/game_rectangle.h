#ifndef GAMERECTANGLE_H
#define GAMERECTANGLE_H

#include "game_obstacle.h"

class GameRectangle : public GameObstacle
{

    Q_OBJECT

public:
    GameRectangle(QWidget *parent, int x, int y, double angle);
};

#endif // GAMERECTANGLE_H
