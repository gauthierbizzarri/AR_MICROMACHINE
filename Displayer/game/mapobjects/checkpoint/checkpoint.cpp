#include "checkpoint.h"
#include <QGraphicsEllipseItem>
#include <game/utils/properties/gameproperties.h>

Checkpoint::Checkpoint(int x, int y, QGraphicsItem* parent) : CircuitElement(x, y, parent)
{
}

QRectF Checkpoint::boundingRect() const
{
    return QRectF(0, 0, GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::green);
    painter->drawEllipse(0, 0, GameProperties::getInstance()->checkpointRadius, GameProperties::getInstance()->checkpointRadius);
}
