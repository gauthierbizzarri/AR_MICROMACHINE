#include "game_entity.h"

GameEntity::GameEntity(QWidget* parent, int x, int y)
    : GameObstacle(parent, x, y)
{
    this->next = nullptr;
    this->prev = nullptr;
}
