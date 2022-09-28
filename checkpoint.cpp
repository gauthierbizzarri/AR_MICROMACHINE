#include "checkpoint.h"
#include <QGraphicsEllipseItem>

Checkpoint::Checkpoint(int x, int y) : CircuitElement(x, y)
{
    this->setProperty("TYPE","Checkpoint");
}

QRectF Checkpoint::boundingRect() const
{
    return QRectF(0, 0, 100., 100.);
}

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(0, 0, 100, 100);
}
