#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <position.h>
#include <circuitelement.h>
#include <QPainter>

class Checkpoint : public CircuitElement
{
public:
    Checkpoint(int x, int y);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CHECKPOINT_H
