
#include <QPen>
#include <QBrush>
#include "main.h"
#include "game_item_bomb.h"

GameBomb::GameBomb(QWidget* parent, GameProperties* properties)
    : GameEntity(parent, 0, 0)
{

    this->m_uuid = QUuid::createUuid().toString();
    this->m_ttl = properties->bombTtl *1000;
    this->m_explosionTtl = this->m_ttl +1000;
    this->m_age = 0;
    this->m_explosionRadius = properties->bombExplostionSize;
    this->m_exploding = false;

    // QItem

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(
                -properties->bombSize, -properties->bombSize,
                properties->bombSize*2, properties->bombSize*2);
    QPen pen;
    pen.setWidth(2);
    item->setBrush(QBrush(Qt::black));
    item->setPen(pen);
    item->moveBy(0, 0);

    this->m_item = item;

}

void GameBomb::set(int x, int y) {

    this->m_point.setX(x);
    this->m_point.setY(y);
    this->m_item->setPos(x, y);

}

void GameBomb::updateProperties(GameProperties* properties) {

    this->m_ttl = properties->bombTtl *1000;
    this->m_explosionTtl = this->m_ttl + 1000;
    this->m_explosionRadius = properties->bombExplostionSize;

    if(this->m_exploding) {
        auto item = (QGraphicsEllipseItem*) this->m_item;
        item->setRect(-properties->bombExplostionSize, -properties->bombExplostionSize, 2*properties->bombExplostionSize, 2*properties->bombExplostionSize);
    }
    else {
        auto item = (QGraphicsEllipseItem*) this->m_item;
        item->setRect(-properties->bombSize, -properties->bombSize, 2*properties->bombSize, 2*properties->bombSize);
    }

}

QJsonObject GameBomb::toJson() {

    QJsonObject json
    {
        {"x", this->point().x()},
        {"y", this->point().y()},
        {"angle", 0.0},
        {"status", this->m_exploding ? "exploding" : "waiting"},
        {"type", "bomb"},
        {"uuid", this->m_uuid}
    };

    return json;
}

void GameBomb::update() {
    this->m_age += GAME_TICK;

    if(!this->m_exploding && (this->m_age >= this->m_ttl)) {
        this->m_exploding = true;

        auto item = (QGraphicsEllipseItem*) this->m_item;
        item->setRect(-this->m_explosionRadius, -this->m_explosionRadius, 2*this->m_explosionRadius, 2*this->m_explosionRadius);
        item->setBrush(QBrush(Qt::red));

        this->checkCollision();
    }

    if(this->m_age >= this->m_explosionTtl) {
        emit this->endOfLife(this);
    }

}

void GameBomb::checkCollision() {

    for(GameMapObject* object : gameObjects) {
        if(this != object)
            if(this->m_item->collidesWithItem(object->getItem())) {

                auto entity = qobject_cast<GameEntity*>(object);
                if(entity) {
                    entity->getHit();
                }

            }
    }
}

void GameBomb::getHit() {

    if(!this->m_exploding && this->m_age < this->m_ttl -GAME_TICK*2) {
        this->m_age = this->m_ttl -GAME_TICK *2;
    }

}
