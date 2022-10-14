#ifndef GAMERECTANGLE_H
#define GAMERECTANGLE_H

#include "game_obstacle.h"

class GameRectangle : public GameObstacle
{

    Q_OBJECT

    double m_angle;
    int m_width;
    int m_height;

public:
    GameRectangle(QWidget *parent, int x, int y, double angle, int w, int h);

    double angle();
    int W();
    int H();

    void updateProperties(GameProperties* properties);

};

#endif // GAMERECTANGLE_H
