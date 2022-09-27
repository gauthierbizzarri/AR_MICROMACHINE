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
    void setAngle(float);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool operator==(CircuitElement* el){
        return el->getId() == this->id;
    }
};

#endif // OBSTACLE_H
