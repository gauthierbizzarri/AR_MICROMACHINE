#include <QGraphicsEllipseItem>
#include "game_circle.h"

GameCircle::GameCircle(QWidget *parent, int x, int y)
    : GameObstacle{parent, x, y}
{
    QGraphicsEllipseItem* rect = new QGraphicsEllipseItem(-25, -25, 50, 50);

    //rect->setBrush(Qt::red);
    rect->moveBy(x*0.6, y*0.6);

    this->m_item = rect;
}
