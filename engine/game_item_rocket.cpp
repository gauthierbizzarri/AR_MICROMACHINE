
#include <QPen>
#include <QBrush>
#include "game_item_rocket.h"
#include "game_checkpoint.h"
#include "math.h"

GameRocket::GameRocket(QWidget* parent, GameProperties* properties)
    : GameEntity(parent, 0, 0)
{

    this->m_uuid = QUuid::createUuid().toString();
    this->m_speed = properties->rocketSpeed;
    this->m_angle = 0;

    // QItem

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(
                -properties->rocketRadius, -properties->rocketRadius,
                properties->rocketRadius*2, properties->rocketRadius*2);
    QPen pen;
    pen.setWidth(2);
    item->setBrush(QBrush(Qt::gray));
    item->setPen(pen);
    item->moveBy(0, 0);

    this->m_item = item;

}

void GameRocket::set(int x, int y, double angle) {

    this->m_point.setX(x);
    this->m_point.setY(y);
    this->m_angle = angle;

    this->m_item->setPos(x, y);
}

void GameRocket::updateProperties(GameProperties* properties) {

    this->m_speed = properties->rocketSpeed;

    auto item = (QGraphicsEllipseItem*) this->m_item;
    item->setRect(-properties->rocketRadius, -properties->rocketRadius, 2*properties->rocketRadius, 2*properties->rocketRadius);

}

QJsonObject GameRocket::toJson() {

    QJsonObject json
    {
        {"x", this->point().x()},
        {"y", this->point().y()},
        {"angle", this->m_angle},
        {"status", "flying"},
        {"type", "rocket"},
        {"uuid", this->m_uuid}
    };

    return json;
}

void GameRocket::update() {

    auto F = QPointF(cos(this->m_angle), -sin(this->m_angle)) *this->m_speed /10.0;
    this->m_point = this->m_point +F;

    // Draw

    this->m_item->setX(this->X());
    this->m_item->setY(this->Y());

    this->checkCollision();
}

void GameRocket::checkCollision() {

    if(this->m_point.x() < 0 || this->m_point.x() > 1000 || this->m_point.y() < 0 || this->m_point.y() > 1000) {
        emit this->endOfLife(this);
        return;
    }

    for(GameMapObject* object : gameObjects) {
        if(this != object)
            if(this->m_item->collidesWithItem(object->getItem())) {

                auto entity = qobject_cast<GameEntity*>(object);
                if(entity) {
                    entity->getHit();
                    emit this->endOfLife(this);
                    break;
                }

                auto check = qobject_cast<GameCheckpoint*>(object);
                if(!check) {
                    emit this->endOfLife(this);
                    break;
                }
            }
    }
}

void GameRocket::getHit() {
    emit this->endOfLife(this);
}
