#include "obstacle.h"

Obstacle::Obstacle(QWidget* parent, int id, Position* pos, float angle): CircuitElement(parent, id, pos)
{
    this->angle=angle;
}

float Obstacle::getAngle()
{
    return this->angle;
}

void Obstacle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QBrush brush(Qt::BrushStyle::SolidPattern);
    brush.setColor(Qt::green);
    painter.setBrush(brush);

    QPen pen;
    pen.setColor(Qt::green);

    painter.setPen(pen);
    painter.drawEllipse(0, 0, 50, 100);
}
