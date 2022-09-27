#ifndef POINT_H
#define POINT_H

#include <position.h>
#include <quuid.h>
#include <circuitelement.h>
#include <QPainter>

class Point : public CircuitElement
{
public:
    Point(QWidget* parent, int id, Position* pos);
    virtual void paintEvent(QPaintEvent* event);
};

#endif // POINT_H
