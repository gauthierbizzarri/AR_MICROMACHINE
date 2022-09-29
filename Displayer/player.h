#ifndef PLAYER_H
#define PLAYER_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Player : public CircuitElement
{
public:
    /**
     * @brief Circle graphical representation of a circle obstacle
     * @param x x central position of the circle
     * @param y y central position of the circle
     * @param parent graphical item's parent
     */
    Player(int x, int y, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void set_data(char color0, int team, float angle, int speed, char vehicule);
};

#endif // PLAYER_H
