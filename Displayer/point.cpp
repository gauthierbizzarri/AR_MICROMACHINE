#include "point.h"

Point::Point(QWidget* parent, int id, Position* pos) : CircuitElement(parent, id, pos)
{

}

void Point::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QBrush brush(Qt::BrushStyle::SolidPattern);
    brush.setColor(Qt::green);
    painter.setBrush(brush);

    QPen pen;
    pen.setColor(Qt::green);

    painter.setPen(pen);
    int size = 20;
    painter.drawEllipse(this->pos->getX()-size/2, this->pos->getY()-size/2, size, size);
}
