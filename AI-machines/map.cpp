#include "map.h"

Map::Map(QJsonObject map)
{
    m_width = map["mapWidth"].toInt();
    m_height = map["mapHeight"].toInt();

    foreach (const auto checkpoint, map["checkpoints"].toArray()) {
        m_checkpoints.append(Checkpoint(checkpoint.toObject()));
    }

    foreach (const auto obstacle, map["obstacles"].toArray()) {
        m_obstacles.append(Obstacle(obstacle.toObject()));
    }
}

QList<Checkpoint> Map::get_checkpoints() {
    return m_checkpoints;
}

Map Map::fromJson(QJsonDocument jsonMap) {
    return Map(jsonMap.object());
}

void Map::debug() {
    qDebug("Map debugging !");
    qDebug() << m_width;
    qDebug() << m_height;
    foreach(Checkpoint checkpoint, m_checkpoints) {
        checkpoint.debug();
    }
    foreach(Obstacle obstacle, m_obstacles) {
        obstacle.debug();
    }
}
