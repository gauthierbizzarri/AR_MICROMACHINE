#ifndef GAMECIRCLE_H
#define GAMECIRCLE_H

#include "game_obstacle.h"

class GameCircle : public GameObstacle
{
    Q_OBJECT

public:
    GameCircle(QWidget *parent, int x, int y, int r);

    void updateProperties(GameProperties* properties);
};

#endif // GAMECIRCLE_H
