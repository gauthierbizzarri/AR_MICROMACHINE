
#include <QPen>
#include <QBrush>
#include "game_item_banana.h"
#include "main.h"

GameBanana::GameBanana(QWidget* parent, GameProperties* properties)
    : GameEntity(parent, 0, 0)
{

    this->m_ttl = properties->bananaTtl *1000;
    this->m_age = 0;

    // QItem

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(
                -properties->bananaRadius, -properties->bananaRadius,
                properties->bananaRadius*2, properties->bananaRadius*2);
    QPen pen;
    pen.setWidth(2);
    item->setBrush(QBrush(Qt::yellow));
    item->setPen(pen);
    item->moveBy(0, 0);

    this->m_item = item;

}

void GameBanana::set(int x, int y) {

    this->m_point.setX(x);
    this->m_point.setY(y);
    this->m_item->setPos(x, y);

}

void GameBanana::updateProperties(GameProperties* properties) {

    this->m_ttl = properties->bananaTtl *1000;

    auto item = (QGraphicsEllipseItem*) this->m_item;
    item->setRect(-properties->bananaRadius, -properties->bananaRadius, 2*properties->bananaRadius, 2*properties->bananaRadius);

}

QJsonObject GameBanana::toJson() {

    QJsonObject json
    {
        {"x", this->m_point.x()},
        {"y", this->m_point.y()},
        {"angle", 0.0},
        {"status", "placed"},
        {"type", "banana"}
    };

    return json;
}

void GameBanana::update() {
    this->m_age += GAME_TICK;

    qDebug() << this->m_point;

    if(this->m_age > this->m_ttl)
        emit this->endOfLife(this);

}

void GameBanana::getHit() {
    emit this->endOfLife(this);
}
