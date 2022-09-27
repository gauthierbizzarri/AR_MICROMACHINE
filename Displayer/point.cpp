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
    painter.drawEllipse(0, 0, 50, 100);
}
