#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <circuitelement.h>
#include <QPainter>

class Obstacle : public CircuitElement
{
private:
    float angle;
public:
    Obstacle(QWidget* parent, int id, Position* pos, float angle);
    float getAngle();
    virtual void paintEvent(QPaintEvent* event);
};

#endif // OBSTACLE_H
