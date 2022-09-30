#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QJsonObject>
#include "game_obstacle.h"

class GameEntity : public GameObstacle
{

    Q_OBJECT

public:
    GameEntity(QWidget* parent, int x, int y);

    virtual QJsonObject toJson() = 0;
    virtual void update() = 0;

};

#endif // GAMEENTITY_H
