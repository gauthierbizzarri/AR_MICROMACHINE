#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "game_obstacle.h"

class GameEntity : public GameObstacle
{

    Q_OBJECT

public:
    GameEntity(QWidget* parent, int x, int y);
};

#endif // GAMEENTITY_H
