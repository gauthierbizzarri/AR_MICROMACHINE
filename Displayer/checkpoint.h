#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Checkpoint : public CircuitElement
{
public:
    /**
     * @brief Checkpoint graphical representation of a checkpoint
     * @param x x center position of checkpoint
     * @param y y center position of checkpoint
     * @param parent graphical item's parent
     */
    Checkpoint(int x, int y, QGraphicsItem* parent = nullptr);
//********interface***********//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CHECKPOINT_H
