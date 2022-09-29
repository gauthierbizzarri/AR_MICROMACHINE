#include "rectangle.h"
#include <QGraphicsEllipseItem>
#include <gameproperties.h>

Rectangle::Rectangle(int x, int y, float angle, QGraphicsItem* parent): CircuitElement(x, y, parent)
{
    this->setTransformOriginPoint(GameProperties::getInstance()->rectangleWidth/2, GameProperties::getInstance()->rectangleHeight/2);
    this->setRotation(angle);
    this->setProperty("TYPE","Rectangle");
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(0, 0, GameProperties::getInstance()->rectangleWidth, GameProperties::getInstance()->rectangleHeight);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, GameProperties::getInstance()->rectangleWidth, GameProperties::getInstance()->rectangleHeight);
}
