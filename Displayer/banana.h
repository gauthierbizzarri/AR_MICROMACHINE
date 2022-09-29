#ifndef BANANA_H
#define BANANA_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Banana : public CircuitElement
{
public:
    /**
     * @brief Checkpoint graphical representation of a checkpoint
     * @param x x center position of checkpoint
     * @param y y center position of checkpoint
     * @param parent graphical item's parent
     */
    Banana(int x, int y, QGraphicsItem* parent = nullptr);
//********interface***********//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BANANA_H
