#ifndef ROCKET_H
#define ROCKET_H

#include <game/powerups/rocket/rocket.h>
#include <game/mapobjects/circuitelement.h>
#include <QPainter>

class Rocket : public CircuitElement
{
public:
    /**
     * @brief Checkpoint graphical representation of a checkpoint
     * @param x x center position of checkpoint
     * @param y y center position of checkpoint
     * @param parent graphical item's parent
     */
    Rocket(int x, int y, QGraphicsItem* parent = nullptr);
//********interface***********//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ROCKET_H
