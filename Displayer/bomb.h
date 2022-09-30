#ifndef BOMB_H
#define BOMB_H

#include <bomb.h>
#include <circuitelement.h>
#include <QPainter>

class Bomb : public CircuitElement
{
public:
    /**
     * @brief Checkpoint graphical representation of a checkpoint
     * @param x x center position of checkpoint
     * @param y y center position of checkpoint
     * @param parent graphical item's parent
     */
    Bomb(int x, int y, QGraphicsItem* parent = nullptr);
//********interface***********//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMB_H
