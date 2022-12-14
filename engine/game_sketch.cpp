
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "game_sketch.h"

GameSketch::GameSketch(QWidget *parent, int x, int y, bool front)
    :GameMapObject(parent, x, y)
{

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-3, -3, 6, 6);
    item->setBrush(QBrush(front ? Qt::yellow : Qt::red));
    item->moveBy(x, y);
    this->m_item = item;

}

void GameSketch::setXY(int x, int y) {

    this->m_point.setX(x);
    this->m_point.setY(y);

    this->m_item->setX(x);
    this->m_item->setY(y);

}

void GameSketch::set(QPointF point) {

    this->setXY(point.x(), point.y());

}

void GameSketch::updateProperties(GameProperties* properties) {

}
