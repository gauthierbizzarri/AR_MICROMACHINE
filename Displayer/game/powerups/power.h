#ifndef POWER_H
#define POWER_H

#include <game/utils/position.h>
#include <game/mapobjects/circuitelement.h>
#include <QPainter>

class Power : public CircuitElement
{
public:
    /**
     * @brief Checkpoint graphical representation of a checkpoint
     * @param x x center position of checkpoint
     * @param y y center position of checkpoint
     * @param parent graphical item's parent
     */
    Power(int x, int y,QString name,int amount, QGraphicsItem* parent = nullptr);
//********interface***********//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QImage get_image();
};

#endif // POWER_H
