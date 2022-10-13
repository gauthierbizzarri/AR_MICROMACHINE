#include "position.h"

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX()
{
    return this->x;
}

int Position::getY()
{
    return this->y;
}

Position* Position::translate(int x, int y)
{
    return new Position(this->x+x, this->y+y);
}
