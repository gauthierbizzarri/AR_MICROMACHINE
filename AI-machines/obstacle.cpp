#include "obstacle.h"

Obstacle::Obstacle(QJsonObject obstacle)
    : Entity{
      obstacle["x"].toInt(),
      obstacle["y"].toInt(),
      obstacle["angle"].toDouble()
    }
{
    m_id = obstacle["id"].toInt();
}

Obstacle Obstacle::fromJson(QJsonDocument jsonObstacle) {
    return Obstacle(jsonObstacle.object());
}

void Obstacle::debug() {
    qDebug("Obstacle Debugging !");
    qDebug() << m_id;
    qDebug() << get_x();
    qDebug() << get_y();
    qDebug() << get_angle();
}
