#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <circuitelement.h>
#include <QPainter>

class Obstacle : public CircuitElement
{
private:
    float angle;
public:
    Obstacle(int id, Position* pos, float angle);
    float getAngle();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OBSTACLE_H
