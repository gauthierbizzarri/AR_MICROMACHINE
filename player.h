#ifndef PLAYER_H
#define PLAYER_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Player : public CircuitElement
{
public:
    Player(int x, int y);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void set_data(char color, int team, float angle, int speed, char vehicule);
};

#endif // PLAYER_H
